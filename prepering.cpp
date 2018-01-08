// Standard Library
#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <direct.h>
#include <cstring>

// Header
#include "constant.h"
#include "class.h"

using namespace std;

// Gloval variables
namespace dfcls
{
	string	LogDirectory = "", prompt = ">";
	bool	WriteLog = false;

	bool prepering()
	{
		char LogDirectory_c[FILENAME_MAX];
		if(!_getcwd(LogDirectory_c, (sizeof(LogDirectory_c) / sizeof(char))))
			return false;
		if(LogDirectory_c[strlen(LogDirectory_c) - 1] == PATH_BREAK_CHARACTER)
			LogDirectory_c[strlen(LogDirectory_c) - 1] = '\0';
		LogDirectory = LogDirectory_c;

		char SettingFileName[FILENAME_MAX];
		sprintf(SettingFileName, ".%cSETTING", PATH_BREAK_CHARACTER);
		ifstream ifs(SettingFileName);
		if(ifs.fail())return true; // If setting file is not found, use default value. So, return success value.

		string	line;
		string	SettingName, SettingContent;
		char	SettingName_c[SETTING_NAME_MAX], SettingContent_c[SETTING_CONTENT_MAX];
		char	format[FORMAT_MAX];
		sprintf(format, "%%%u[^=]=%%%us", SETTING_NAME_MAX, SETTING_CONTENT_MAX);
		while(getline(ifs, line))
		{
			sscanf(line.c_str(), format, SettingName_c, SettingContent_c);

			SettingName	= SettingName_c;
			SettingContent	= SettingContent_c;

			if(SettingName == "prompt")
				prompt = SettingContent;
			else if(SettingName == "LogDirectory")
			{
				if(SettingContent_c[strlen(SettingContent_c) - 1] == PATH_BREAK_CHARACTER)
					SettingContent_c[strlen(SettingContent_c) - 1] = '\0';

				LogDirectory = SettingContent_c;
			}
			else if(SettingName == "WriteLog")
			{
				if(SettingContent == "true")
					WriteLog = true;
				else if(SettingContent == "false")
					WriteLog = false;
				else return false;
			}
			else return false;
		}

		LogProcess log;
		return log.init();
	}
}
