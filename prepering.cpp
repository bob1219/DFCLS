// Standard Libraries
#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>

// Headers
#include "constant.h"
#include "class.h"

using namespace std;
using namespace dfcls;

// Gloval variables
string	LogDirectory = ".", prompt = ">";
bool	WriteLog = false;

bool prepering()
{
	char SettingFileName[FILENAME_MAX];
	sprintf(SettingFileName, ".%cSETTING", PATH_BREAK_CHARACTER);
	ifstream ifs(SettingFileName);
	if(ifs.fail())return false;

	string	line;
	char	SettingName[SETTING_NAME_MAX], SettingContent[SETTING_CONTENT_MAX];
	char	format[FORMAT_MAX];
	while(getline(ifs, line))
	{
		sprintf(format, "%%%u[^=]=%%%us", SETTING_NAME_MAX, SETTING_CONTENT_MAX);
		sscanf(line.c_str(), format, SettingName, SettingContent);
		if(SettingName == "prompt")
			prompt = SettingContent;
		else if(SettingName == "LogDirectory")
			LogDirectory = SettingContent;
		else if(SettingName == "WriteLog")
		{
			string SettingContent_s = SettingContent;
			if(SettingContent_s == "true")
				WriteLog = true;
			else if(SettingContent_s == "false")
				WriteLog = false;
			else return false;
		}
		else return false;
	}

	LogProcess log;
	if(!log.init())return false;

	return true;
}
