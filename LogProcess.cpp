// Standard Libraries
#include <string>
#include <cstdio>
#include <iostream>
#include <fstream>

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
