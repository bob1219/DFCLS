#ifndef _COMMAND_FUNCTION_H_
#define _COMMAND_FUNCTION_H_

// Standard Library
#include <string>

namespace dfcls
{
	namespace command
	{
		// directory
		bool mdir(int CommandNumber, std::string dirname);
		bool rdir(int CommandNumber, std::string dirname);
		bool chdir(int CommandNumber, std::string dirname);
		bool cwdir();

		// file
		bool mfile(int CommandNumber, std::string filename);
		bool rfile(int CommandNumber, std::string filename);
		bool cfile(int CommandNumber, std::string from, std::string to);
		bool lfile(int CommandNumber, std::string dirname);

		// directory & file
		bool rename(int CommandNumber, std::string oldname, std::string newname);

		// file-view
		bool tview(int CommandNumber, std::string filename);
		bool bview(int CommandNumber, std::string filename);

		// other
		bool version();
		bool app(int CommandNumber, std::string *commands);
		bool date();
		bool time();
		bool now();
	}
}
