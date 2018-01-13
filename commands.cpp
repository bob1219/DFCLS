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
#include <cctype>
#include <regex>
#include <cstring>

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

		unsigned char	buf[FILE_SIZE_MAX];
		size_t		byte = ifs.read(reinterpret_cast<char*>(buf), (sizeof(buf) / sizeof(char))).gcount();

		cout << "\t" << "+0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F 0123456789ABCDEF" << endl;

		int line_start;
		for(unsigned int i = 0 ; i < (byte / BVIEW_PRINT_BYTE_MAX + 1) ; i++)
		{
			line_start = BVIEW_PRINT_BYTE_MAX * i;

			printf("%X:\t", line_start);
			
			for(unsigned int j = 0 ; j < BVIEW_PRINT_BYTE_MAX ; j++)
				printf("%02X ", buf[line_start + j]);

			for(unsigned int k = 0 ; k < BVIEW_PRINT_BYTE_MAX ; k++)
				printf("%c", (isprint(static_cast<int>(buf[line_start + k]))) ? buf[line_start + k] : '.');

			cout << endl;
		}
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

bool command::find(int CommandNumber, const string &filename)
{
	string reg;

	try
	{
		if(CommandNumber < 2)throw 1;

		cout << "regex: ";
		getline(cin, reg);

		ifstream ifs(filename);
		if(ifs.fail())throw 1;

		string line;
		smatch result;
		for(unsigned int i = 1 ; getline(ifs, line) ; i++)
			if(regex_search(line, result, regex(reg)))
				cout << "Match in line " << i << " (\"" << result.str() << "\" ; \"" << line << "\")" << endl;
	}
	catch(...)
	{
		if(WriteLog)
		{
			LogProcess log;
			log.write("error", "Failed find a regex");
		}
		return false;
	}

	if(WriteLog)
	{
		LogProcess log;
		log.write("info", "Found a regex \"" + reg + "\" in a file \"" + filename + "\"");
	}
	return true;
}

bool command::diff(int CommandNumber, const string &filename1, const string &filename2)
{
	try
	{
		if(CommandNumber < 3)throw 1;

		ifstream a_ifs(filename1), b_ifs(filename2);
		if(a_ifs.fail() || b_ifs.fail())
			throw 1;

		cout << "a: " << filename1 << endl;
		cout << "b: " << filename2 << endl;
		cout << endl;

		string a_line, b_line;
		for(unsigned int i = 1 ;; i++)
		{
			getline(a_ifs, a_line);
			getline(b_ifs, b_line);

			if(a_ifs.fail() && b_ifs.fail())break;

			if(a_line == b_line)
				cout << "\t" << i << ":\t" << a_line << endl;
			else if(a_ifs.good() && b_ifs.eof())
				cout << "a\t" << i << ":\t" << a_line << endl;
			else if(b_ifs.good() && a_ifs.eof())
				cout << "b\t" << i << ":\t" << b_line << endl;
			else if(a_line != b_line)
			{
				cout << "a\t" << i << ":\t" << a_line << endl;
				cout << "b\t" << i << ":\t" << b_line << endl;
			}
		}
	}
	catch(...)
	{
		if(WriteLog)
		{
			LogProcess log;
			log.write("error", "Failed print difference of 2 files");
		}
		return false;
	}

	if(WriteLog)
	{
		LogProcess log;
		log.write("info", "Printed difference of 2 files \"" + filename1 + "\" and \"" + filename2 + "\"");
	}
	return true;
}

bool config(int CommandNumber, const string &SettingName, const string &SettingContent)
{
	try
	{
		if(CommandNumber < 3)throw 1;

		if(SettingName == "LogDirectory")
		{
			char LogDirectory_c[FILENAME_MAX] = SettingContent.c_str();
			if(LogDirectory_c[strlen(LogDirectory_c) - 1] == PATH_BREAK_CHARACTER)
				LogDirectory_c[strlen(LogDirectory_c) - 1] = '\0';
			LogDirectory = LogDirectory_c;
		}
		else if(SettingName == "prompt")
			prompt = SettingContent;
		else if(SettingName == "WriteLog")
		{
			if(SettingContent == "true")
				WriteLog = true;
			else if(SettingContent == "false")
				WriteLog = false;
			else
				throw 1;
		}
		else throw 1;

		char SettingFileName[FILENAME_MAX];
		sprintf(SettingFileName, ".%cSETTING", PATH_BREAK_CHARACTER);
		ofstream ofs(SettingFileName);
		if(ofs.fail())throw 1;

		ofs << "LogDirectory=" << LogDirectory << endl;
		ofs << "prompt=" << prompt << endl;
		ofs << "WriteLog=" << WriteLog << endl;
	}
	catch(...)
	{
		if(WriteLog)
		{
			LogProcess log;
			log.write("error", "Failed configure");
		}
		return false;
	}

	if(WriteLog)
	{
		LogProcess log;
		log.write("info", "Configured setting \"" + SettingName + "\" to \"" + SettingContent + "\"");
	}
	return true;
}
