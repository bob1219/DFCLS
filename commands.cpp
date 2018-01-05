// Standard Library
#include <string>
#include <direct.h>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <cstddef>
#include <filesystem>
#include <algorithm>
#include <cstdlib>
#include <ctime>

// Header
#include "class.h"
#include "extern.h"
#include "constant.h"

using namespace dfcls;
using namespace std;
using namespace std::tr2::sys;

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

bool command::cfile(int CommandNumber, const string &from, const string &to)
{
	if(CommandNumber < 3)goto cfile_error;

	ifstream ifs(from, ios_base::in | ios_base::binary);
	ofstream ofs(to, ios_base::out | ios_base::binary);
	if(ifs.fail() || ofs.fail())
		goto cfile_error;

	char	buf[FILE_SIZE_MAX];
	size_t	byte = ifs.read(buf, (sizeof(buf) / sizeof(char))).gcout();
	ofs.write(buf, byte);

	if(WriteLog)
	{
		LogProcess log;
		log.write("info", "Copied file \"" + from + "\" -> \"" + to + "\"");
	}
	return true;

cfile_error:
	if(WriteLog)
	{
		LogProcess log;
		log.write("error", "Failed copy file");
	}
	return false;
}

bool command::lfile(int CommandNumber, const string &dirname)
{
	if(CommandNumber < 2)goto lfile_error;

	path p(dirname);
	for_each(directory_iterator(p), directory_iterator(),
		[](const path &p)
		{
			if(is_regular_file(p))
				cout << "file:\t" << p << endl;
			else if(is_directory(p))
				cout << "dir:\t" << p << endl;
		}
	);

	if(WriteLog)
	{
		LogProcess log;
		log.write("info", "Printed list of files in directory \"" + dirname + "\"");
	}
	return true;

lfile_error:
	if(WriteLog)
	{
		LogProcess log;
		log.write("error", "Failed print list of files in directory");
	}
	return false;
}

bool command::rename(int CommandNumber, const string &oldname, const string &newname)
{
	if(CommandNumber < 3)goto rename_error;

	if(!rename(oldname, newname))
	{
		if(WriteLog)
		{
			LogProcess log;
			log.write("info", "Renamed file \"" + oldname + "\" -> \"" + newname + "\"");
		}
		return true;
	}
	else goto rename_error;

rename_error:
	if(WriteLog)
	{
		LogProcess log;
		log.write("error", "Failed rename file");
	}
	return false;
}

bool command::tview(int CommandNumber, const string &filename)
{
	if(CommandNumber < 2)goto tview_error;

	ifstream ifs(filename);
	if(ifs.fail())goto tview_error;

	string line;
	for(unsigned int i = 1 ; getline(ifs, line) ; i++)
		cout << i << ":\t" << line << "\n";

	if(WriteLog)
	{
		LogProcess log;
		log.write("info", "Printed contents of file \"" + filename + "\" in text");
	}
	return true;

tview_error:
	if(WriteLog)
	{
		LogProcess log;
		log.write("error", "Failed print contents of file in text");
	}
	return false;
}

bool command::bview(int CommandNumber, const string &filename)
{
	if(CommandNumber < 2)goto bview_error;

	ifstream ifs(filename, ios_base::in | ios_base::binary);
	if(ifs.fail())goto bview_error;

	char buf[FILE_SIZE_MAX];
	size_t byte = ifs.read(buf, (sizeof(buf) / sizeof(char))).gcount();

	for(unsigned int i = 0 ; i < byte ; i++)
		printf("%02X", buf[i]);

	if(WriteLog)
	{
		LogProcess log;
		log.write("info", "Printed contents of file \"" + filename + "\" in binary");
	}
	return true;

bview_error:
	if(WriteLog)
	{
		LogProcess log;
		log.write("error", "Failed print contents of file in binary");
	}
	return false;
}

bool command::app(int CommandNumber, string *commands)
{
	if(CommandNumber < 2 || !system(NULL))goto app_error;

	string command;
	for(unsigned int i = 1 ; i < CommandNumber ; i++)
	{
		if(i == 1)
			command = commands[1];
		else
			command += " " + commands[i];
	}

	int ret = system(command);
	cout << "Return value: " << ret << endl;
	if(WriteLog)
	{
		LogProcess log;
		log.write("info", "Executed application \"" + commands[1] + "\", Return value is " + to_string(ret));
	}
	return true;

app_error:
	if(WriteLog)
	{
		LogProcess log;
		log.write("error", "Failed execution application");
	}
	return false;
}

bool command::date()
{
	time_t		timer	= time(NULL);
	struct tm	*local	= localtime(&timer);

	string month;
	switch(local->tm_mon)
	{
	case 0:
		month = "January";
		break;

	case 1:
		month = "February";
		break;

	case 2:
		month = "March";
		break;

	case 3:
		month = "April";
		break;

	case 4:
		month = "May";
		break;

	case 5:
		month = "June";
		break;

	case 6:
		month = "July";
		break;

	case 7:
		month = "August";
		break;

	case 8:
		month = "September";
		break;

	case 9:
		month = "October";
		break;

	case 10:
		month = "November";
		break;

	case 11:
		month = "December";
		break;
	}

	char date[DATE_MAX];
	switch(local->tm_mday)
	{
	case 1:
	case 21:
	case 31:
		sprintf(date, "%dst", local->tm_mday);
		break;

	case 2:
	case 22:
		sprintf(date, "%dnd", local->tm_mday);
		break;

	case 3:
	case 23:
		sprintf(date, "%drd", local->tm_mday);
		break;

	default:
		sprintf(date, "%dth", local->tm_mday);
		break;
	}

	cout << month << " " << date << ", " << local->tm_year + 1900 << endl;
	return true;
}
