// Standard Libraries
#include <string>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <ctime>

// Headers
#include "class.h"
#include "extern.h"
#include "constant.h"

using namespace dfcls;
using namespace std;

string LogProcess::filename = "";

bool LogProcess::init()
{
	char filename_c[FILENAME_MAX];
	if(LogDirectory[strlen(LogDirectory) - 1] == PATH_BREAK_CHARACTER)
		LogDirectory[strlen(LogDirectory) - 1] = '\0';
	sprintf(filename_c, "%s%cDFCLS.log", LogDirectory, PATH_BREAK_CHARACTER);
	filename = filename_c;

	fstream fs(filename, ios_base::trunc);
	if(fs.fail())return false;

	return true;
}

void LogProcess::write(string type, string message)
{
	ofstream ofs(filename, ios_base::out | ios_base::app);
	if(ofs.fail())
	{
		cout << "Error: Cannot open logfile \"" << filename << "\"." << endl;
		return;
	}

	// write
	time_t		timer = time(NULL);
	struct tm	*local = localtime(&timer);
	char date[DATE_MAX];
	sprintf(date, "[%02d/%02d/%04d %02d:%02d:%02d]", local->tm_mon + 1, local->tm_mday, local->tm_year + 1900, local->tm_hour, local->tm_min, local->tm_sec);
	char _type[LOGTYPE_MAX];
	sprintf(_type, "[%s]", type);
	ofs << date << _type << message << "." << endl;
}
