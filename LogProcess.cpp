// Standard Library
#include <string>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>

// Header
#include "class.h"
#include "extern.h"
#include "constant.h"

using namespace dfcls;
using namespace std;

string LogProcess::filename = "";

bool LogProcess::init()
{
	char filename_c[FILENAME_MAX];
	sprintf(filename_c, "%s%cDFCLS.log", LogDirectory.c_str(), PATH_BREAK_CHARACTER);
	filename = filename_c;

	ofstream ofs(filename);
	if(ofs.fail())return false;

	return true;
}

void LogProcess::write(const string &type, const string &message)
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
	char		str[MESSAGE_MAX];
	sprintf(str, "[%02d/%02d/%04d %02d:%02d:%02d][%s]%s", local->tm_mon + 1, local->tm_mday, local->tm_year + 1900, local->tm_hour, local->tm_min, local->tm_sec, type.c_str(), message.c_str());
	ofs << str << endl;
}
