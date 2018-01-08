// Standard Library
#include <string>
#include <direct.h>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <cstddef>
#include <ctime>
#include <dirent.h>
#include <cstdlib>

// Header
#include "class.h"
#include "extern.h"
#include "constant.h"
#include "command-function.h"

using namespace dfcls;
using namespace std;

bool command::mdir(int CommandNumber, const string &dirname)
{
	try
	{
		if(CommandNumber < 2)throw 1;

		if(!_mkdir(dirname.c_str()))
		{
			if(WriteLog)
			{
				LogProcess log;
				log.write("info", "Made a directory \"" + dirname + "\"");
			}
			return true;
		}
		else throw 1;
	}
	catch(...)
	{
		if(WriteLog)
		{
			LogProcess log;
			log.write("error", "Failed make a directory");
		}
		return false;
	}
}

bool command::rdir(int CommandNumber, const string &dirname)
{
	try
	{
		if(CommandNumber < 2)throw 1;

		if(!_rmdir(dirname.c_str()))
		{
			if(WriteLog)
			{
				LogProcess log;
				log.write("info", "Removed a directory \"" + dirname + "\"");
			}
			return true;
		}
		else throw 1;
	}
	catch(...)
	{
		if(WriteLog)
		{
			LogProcess log;
			log.write("error", "Failed remove a directory");
		}
		return false;
	}
}

bool command::chdir(int CommandNumber, const string &dirname)
{
	try
	{
		if(CommandNumber < 2)throw 1;

		if(!_chdir(dirname.c_str()))
		{
			if(WriteLog)
			{
				LogProcess log;
				log.write("info", "Changed current working directory to \"" + dirname + "\"");
			}
			return true;
		}
		else throw 1;
	}
	catch(...)
	{
		if(WriteLog)
		{
			LogProcess log;
			log.write("error", "Failed change current working directory");
		}
		return false;
	}
}

bool command::cwdir()
{
	try
	{
		char buf[FILENAME_MAX];
		if(_getcwd(buf, (sizeof(buf) / sizeof(char))))
		{
			cout << buf << endl;
			if(WriteLog)
			{
				LogProcess log;
				log.write("info", "Succeeded get current working directory");
			}
			return true;
		}
		else throw 1;
	}
	catch(...)
	{
		if(WriteLog)
		{
			LogProcess log;
			log.write("error", "Failed get current working directory");
		}
		return false;
	}
}

bool command::mfile(int CommandNumber, const string &filename)
{
	try
	{
		if(CommandNumber < 2)throw 1;

		ofstream fs(filename);
		if(fs.fail())throw 1;
	}
	catch(...)
	{
		if(WriteLog)
		{
			LogProcess log;
			log.write("error", "Failed make a file");
		}
		return false;
	}

	if(WriteLog)
	{
		LogProcess log;
		log.write("info", "Made a file \"" + filename + "\"");
	}
	return true;
}

bool command::rfile(int CommandNumber, const string &filename)
{
	try
	{
		if(CommandNumber < 2)throw 1;

		if(!remove(filename.c_str()))
		{
			if(WriteLog)
			{
				LogProcess log;
				log.write("info", "Removed a file \"" + filename + "\"");
			}
			return true;
		}
		else throw 1;
	}
	catch(...)
	{
		if(WriteLog)
		{
			LogProcess log;
			log.write("error", "Failed remove a file");
		}
		return false;
	}
}

bool command::cfile(int CommandNumber, const string &from, const string &to)
{
	try
	{
		if(CommandNumber < 3)throw 1;

		ifstream ifs(from, ios_base::in | ios_base::binary);
		ofstream ofs(to, ios_base::out | ios_base::binary);
		if(ifs.fail() || ofs.fail())
			throw 1;

		char	buf[FILE_SIZE_MAX];
		size_t	byte = ifs.read(buf, (sizeof(buf) / sizeof(char))).gcount();
		ofs.write(buf, byte);
	}
	catch(...)
	{
		if(WriteLog)
		{
			LogProcess log;
			log.write("error", "Failed copy file");
		}
		return false;
	}

	if(WriteLog)
	{
		LogProcess log;
		log.write("info", "Copied file \"" + from + "\" -> \"" + to + "\"");
	}
	return true;
}

bool command::lfile(int CommandNumber, const string &dirname)
{
	try
	{
		if(CommandNumber < 2)throw 1;

		DIR		*dp;
		struct dirent	*dir;
		dp = opendir(dirname.c_str());
		if(!dp)throw 1;

		while(dir = readdir(dp))
			cout << dir->d_name << endl;
	}
	catch(...)
	{
		if(WriteLog)
		{
			LogProcess log;
			log.write("error", "Failed print list of files in directory");
		}
		return false;
	}

	if(WriteLog)
	{
		LogProcess log;
		log.write("info", "Printed list of files in directory \"" + dirname + "\"");
	}
	return true;
}

bool command::rename(int CommandNumber, const string &oldname, const string &newname)
{
	try
	{
		if(CommandNumber < 3)throw 1;

		if(!std::rename(oldname.c_str(), newname.c_str()))
		{
			if(WriteLog)
			{
				LogProcess log;
				log.write("info", "Renamed file \"" + oldname + "\" -> \"" + newname + "\"");
			}
			return true;
		}
		else throw 1;
	}
	catch(...)
	{
		if(WriteLog)
		{
			LogProcess log;
			log.write("error", "Failed rename file");
		}
		return false;
	}
}

bool command::tview(int CommandNumber, const string &filename)
{
	try
	{
		if(CommandNumber < 2)throw 1;

		ifstream ifs(filename);
		if(ifs.fail())throw 1;

		string line;
		for(unsigned int i = 1 ; getline(ifs, line) ; i++)
			cout << i << ":\t" << line << endl;
	}
	catch(...)
	{
		if(WriteLog)
		{
			LogProcess log;
			log.write("error", "Failed print contents of file in text");
		}
		return false;
	}
	
	if(WriteLog)
	{
		LogProcess log;
		log.write("info", "Printed contents of file \"" + filename + "\" in text");
	}
	return true;
}

bool command::bview(int CommandNumber, const string &filename)
{
	try
	{
		if(CommandNumber < 2)throw 1;

		ifstream ifs(filename, ios_base::in | ios_base::binary);
		if(ifs.fail())throw 1;

		char buf[FILE_SIZE_MAX];
		size_t byte = ifs.read(buf, (sizeof(buf) / sizeof(char))).gcount();

		for(unsigned int i = 0 ; i < byte ; i++)
		{
			if(i == 0)
				printf("%02X", buf[i]);
			else
				printf("-%02X", buf[i]);
		}

		cout << endl;
	}
	catch(...)
	{
		if(WriteLog)
		{
			LogProcess log;
			log.write("error", "Failed print contents of file in binary");
		}
		return false;
	}

	if(WriteLog)
	{
		LogProcess log;
		log.write("info", "Printed contents of file \"" + filename + "\" in binary");
	}
	return true;
}

bool command::app(int CommandNumber, const string *commands)
{
	try
	{
		if(CommandNumber < 2 || !system(NULL))throw 1;

		string command = commands[1];
		for(unsigned int i = 2 ; i < CommandNumber ; i++)
			command += " " + commands[i];

		int ret = system(command.c_str());
		cout << "Return value: " << ret << endl;
		if(WriteLog)
		{
			LogProcess log;
			log.write("info", "Executed application \"" + commands[1] + "\", Return value is " + to_string(ret));
		}
		return true;
	}
	catch(...)
	{
		if(WriteLog)
		{
			LogProcess log;
			log.write("error", "Failed execution application");
		}
		return false;
	}
}

bool command::date()
{
	time_t		timer	= std::time(NULL);
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

	printf("%s %s, %04d\n", month.c_str(), date, local->tm_year + 1900);
	return true;
}

bool command::time()
{
	time_t		timer	= std::time(NULL);
	struct tm	*local	= localtime(&timer);

	printf("%02d:%02d:%02d\n", local->tm_hour, local->tm_min, local->tm_sec);
	return true;
}

bool command::now()
{
	time_t		timer	= std::time(NULL);
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

	printf("%s %s, %04d %02d:%02d:%02d\n", month.c_str(), date, local->tm_year + 1900, local->tm_hour, local->tm_min, local->tm_sec);

	return true;
}
