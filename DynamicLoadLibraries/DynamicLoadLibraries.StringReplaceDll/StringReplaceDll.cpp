#include "StringReplaceDll.h"
#include <Windows.h>

__declspec(dllexport) INT64 ReplaceString(LPCSTR lpsToReplace, LPCSTR lpsNewString)
{
	int iReplacementLength = lstrlen(lpsToReplace);
	if ((iReplacementLength == 0) || (iReplacementLength != lstrlen(lpsNewString)))
	{
		return -1;
	}

	HANDLE hCurrentProcess = GetCurrentProcess();
	SYSTEM_INFO siSystemInfo;
	GetSystemInfo(&siSystemInfo);

	CHAR *pcPage = (CHAR *)calloc(siSystemInfo.dwPageSize, sizeof(CHAR));
	size_t sLastPageSymbol = (size_t)siSystemInfo.dwPageSize - iReplacementLength;

	MEMORY_BASIC_INFORMATION mbiPageInfo;
	BOOL bIsStringFound, bShouldWritePage;
	UINT64 iWrittenCount = 0;

	for (LPVOID lpPageAddress = siSystemInfo.lpMinimumApplicationAddress; lpPageAddress < siSystemInfo.lpMaximumApplicationAddress; lpPageAddress = (LPVOID)((ULONGLONG)lpPageAddress + siSystemInfo.dwPageSize))
	{
		VirtualQuery(lpPageAddress, &mbiPageInfo, sizeof(MEMORY_BASIC_INFORMATION));

		if ((mbiPageInfo.State == MEM_COMMIT) && (mbiPageInfo.Protect | PAGE_READWRITE))
		{
			if (ReadProcessMemory(hCurrentProcess, lpPageAddress, pcPage, siSystemInfo.dwPageSize, NULL))
			{
				bShouldWritePage = FALSE;

				for (size_t sCurPageChar = 0; sCurPageChar < sLastPageSymbol; ++sCurPageChar)
				{
					bIsStringFound = TRUE;
					for (int sCurStrChar = 0; (sCurStrChar < iReplacementLength) && bIsStringFound; ++sCurStrChar)
					{
						bIsStringFound = pcPage[sCurPageChar + sCurStrChar] == lpsToReplace[sCurStrChar];
					}

					if (bIsStringFound)
					{
						for (int sCurStrChar = 0; sCurStrChar < iReplacementLength; ++sCurStrChar)
						{
							pcPage[sCurPageChar + sCurStrChar] = lpsNewString[sCurStrChar];
						}
						++iWrittenCount;
						bShouldWritePage = TRUE;
					}
				}

				if (bShouldWritePage)
				{
					WriteProcessMemory(hCurrentProcess, lpPageAddress, pcPage, siSystemInfo.dwPageSize, NULL);
				}
			}
		}
	}

	free(pcPage);

	return iWrittenCount;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	return TRUE;
}
