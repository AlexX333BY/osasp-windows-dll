#include <Windows.h>
#include <string>
#include <iostream>

std::string psReplacement;

int main()
{
	const DWORD dwSleepTime = 1000;

	std::cout << "Enter string to be replaced by demo: ";
	std::cin >> psReplacement;
	while (TRUE)
	{
		std::cout << psReplacement << std::endl;
		Sleep(dwSleepTime);
	}
}
