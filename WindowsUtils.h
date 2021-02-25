#pragma once
#include <string>
#include <Windows.h>
#include <filesystem>
#include <iostream>

class WindowsUtils
{
public:
	WindowsUtils();
	~WindowsUtils();

	static std::wstring StringToWString(const std::string& s);
	static std::string WStringToString(const std::wstring& s);

};