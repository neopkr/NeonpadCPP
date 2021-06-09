#include "WindowsUtils.h"
#include <shlobj.h>
#include <winerror.h> 
#include <comutil.h> 
#include <iostream>
#include <fstream>
#pragma comment(lib, "comsuppw")
#include <tlhelp32.h>
#include <cctype>
#include <string>
#include <algorithm>
#include <filesystem>

WindowsUtils::WindowsUtils()
{
}


WindowsUtils::~WindowsUtils()
{
}



std::wstring WindowsUtils::StringToWString(const std::string& s)
{
	std::wstring temp(s.length(), L' ');
	std::copy(s.begin(), s.end(), temp.begin());
	return temp;
}

std::string WindowsUtils::WStringToString(const std::wstring& s)
{
	std::string temp(s.length(), ' ');
	std::copy(s.begin(), s.end(), temp.begin());
	return temp;
}
