// Standard Library
#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <direct.h>

// Header
#include "constant.h"
#include "class.h"

using namespace std;
using namespace dfcls;

// Gloval variables
string	LogDirectory = "", prompt = ">";
bool	WriteLog = false;

bool prepering()
{
	char LogDirectory_c[FILENAME_MAX];
	if(!_getcwd(LogDirectory_c, (sizeof(LogDirectory_c) / sizeof(char))))
		return false;
	LogDirectory = LogDirectory_c;

	char SettingFileName[FILENAME_MAX];
	sprintf(SettingFileName, ".%cSETTING", PATH_BREAK_CHARACTER);
	ifstream ifs(SettingFileName);
	if(ifs.fail())return false;

	string	line;
	string	SettingName, SettingContent;
	char	SettingName_c[SETTING_NAME_MAX], SettingContent[SETTING_CONTENT_MAX];
	char	format[FORMAT_MAX];
	sprintf(format, "%%%u[^=]=%%%us", SETTING_NAME_MAX, SETTING_CONTENT_MAX);
	while(getline(ifs, line))
	{
		sscanf(line.c_str(), format, SettingName_c, SettingContent);

		SettingName	= SettingName_c;
		SettingContent	= SettingContent_c;

		if(SettingName == "prompt")
			prompt = SettingContent;
		else if(SettingName == "LogDirectory")
			LogDirectory = SettingContent;
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
	if(!log.init())return false;

	return true;
}
