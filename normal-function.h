#ifndef _NORMAL_FUNCTION_H_
#define _NORMAL_FUNCTION_H_

// Standard Libraries
#include <iostream>
#include <string>

// Headers
#include "class.h"
#include "constant.h"
#include "extern.h"

namespace dfcls
{
	bool prepering();
	void CommandLine();
	bool CommandProcess(std::string command);

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
