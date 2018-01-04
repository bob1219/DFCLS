// Standard Library
#include <const string &>
#include <direct.h>
#include <cstdio>
#include <fstream>
#include <iostream>

// Header
#include "class.h"
#include "extern.h"

using namespace dfcls;
using namespace std;

bool command::mdir(int CommandNumber, const string &dirname)
{
	if(CommandNumber < 2)goto mdir_error;

	if(!_mkdir(dirname.c_str()))
	{
		if(WriteLog)
		{
			LogProcess log;
			log.write("info", "Made a directory \"" + dirname + "\"");
		}
		return true;
	}
	else goto mdir_error;

mdir_error:
	if(WriteLog)
	{
		LogProcess log;
		log.write("error", "Failed make a directory");
	}
	return false;
}

bool command::rdir(int CommandNumber, const string &dirname)
{
	if(CommandNumber < 2)goto rdir_error;

	if(!_rmdir(dirname.c_str()))
	{
		if(WriteLog)
		{
			LogProcess log;
			log.write("info", "Removed a directory \"" + dirname + "\"");
		}
		return true;
	}
	else goto rdir_error;

rdir_error:
	if(WriteLog)
	{
		LogProcess log;
		log.write("error", "Failed remove a directory");
	}
	return false;
}

bool command::chdir(int CommandNumber, const string &dirname)
{
	if(CommandNumber < 2)goto chdir_error;

	if(!_chdir(dirname))
	{
		if(WriteLog)
		{
			LogProcess log;
			log.write("info", "Changed current working directory to \"" + dirname + "\"");
		}
		return true;
	}
	else goto chdir_error;

chdir_error:
	if(WriteLog)
	{
		LogProcess log;
		log.write("error", "Failed change current working directory");
	}
	return false;
}

bool command::cwdir()
{
	char buf[FILENAME_MAX];
	if(getcwd(buf, (sizeof(buf) / sizeof(char))))
	{
		cout << "Current Working Directory: " << buf << endl;
		if(WriteLog)
		{
			LogProcess log;
			log.write("info", "Succeeded get current working directory");
		}
		return true;
	}
	else goto cwdir_error;

cwdir_error:
	if(WriteLog)
	{
		LogProcess log;
		log.write("error", "Failed get current working directory");
	}
	return false;
}

bool command::mfile(int CommandNumber, const string &filename)
{
	if(CommandNumber < 2)goto mfile_error;

	fstream fs(filename, ios_base::trunc);
	if(fs.fail())goto mfile_error;

	if(WriteLog)
	{
		LogProcess log;
		log.write("info", "Made a file \"" + filename "\"");
	}
	return true;

mfile_error:
	if(WriteLog)
	{
		LogProcess log;
		log.write("error", "Failed make a file");
	}
	return false;
}

bool command::rfile(int CommandNumber, const string &filename)
{
	if(CommandNumber < 2)goto rfile_error;

	if(!remove(filename))
	{
		if(WriteLog)
		{
			LogProcess log;
			log.write("info", "Removed a file \"" + filename + "\"");
		}
		return true;
	}
	else goto rfile_error;

rfile_error:
	if(WriteLog)
	{
		LogProcess log;
		log.write("error", "Failed remove a file");
	}
	return false;
}
