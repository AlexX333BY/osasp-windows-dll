#include <Windows.h>
#include <string>
#include <iostream>

std::string psReplacement = "will be replaced soon";

int main()
{
	const DWORD dwSleepTime = 1000;

	while (TRUE)
	{
		std::cout << psReplacement << std::endl;
		Sleep(dwSleepTime);
	}
}
