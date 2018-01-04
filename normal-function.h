#ifndef _NORMAL_FUNCTION_H_
#define _NORMAL_FUNCTION_H_

// Standard Library
#include <iostream>
#include <string>

// Header
#include "class.h"
#include "constant.h"
#include "extern.h"

namespace dfcls
{
	bool prepering();
	void CommandLine();
	bool CommandProcess(const std::string &command);

	inline void welcome()
	{
		std::cout << "Welcome to DFCLS version " << VERSION << std::endl;
		if(WriteLog)
		{
			LogProcess log;
			log.write("info", "DFCLS version " + VERSION);
		}
	}
}

#endif
