#ifndef _COMMAND_FUNCTION_H_
#define _COMMAND_FUNCTION_H_

// Standard Library
#include <string>
#include <iostream>
#include <cstdio>

// Header
#include "constant.h"

namespace dfcls
{
	namespace command
	{
		// directory
		bool mdir(int CommandNumber, const std::string &dirname);
		bool rdir(int CommandNumber, const std::string &dirname);
		bool chdir(int CommandNumber, const std::string &dirname);
		bool cwdir();

		// file
		bool mfile(int CommandNumber, const std::string &filename);
		bool rfile(int CommandNumber, const std::string &filename);
		bool cfile(int CommandNumber, const std::string &from, const std::string &to);
		bool lfile(int CommandNumber, const std::string &dirname);

		// directory & file
		bool rename(int CommandNumber, const std::string &oldname, const std::string &newname);

		// file-view
		bool tview(int CommandNumber, const std::string &filename);
		bool bview(int CommandNumber, const std::string &filename);

		// other
		bool app(int CommandNumber, const std::string *commands);
		bool date();
		bool time();
		bool now();

		inline bool pause()
		{
			std::cout << "Press ENTER key to continue..." << std::endl;
			std::getchar();
			return true;
		}

		inline bool version()
		{
			std::cout << "DFCLS version " << dfcls::VERSION << std::endl;
			return true;
		}
	}
}

#endif
