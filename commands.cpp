// Standard Libraries
#include <string>
#include <direct.h>

// Header
#include "class.h"

using namespace dfcls;
using namespace std;

bool command::mdir(int CommandNumber, string dirname)
{
	if(CommandNumber < 2)goto mdir_error;

	if(!_mkdir(dirname.c_str()))
	{
		LogProcess log;
		log.write("info", "Made a directory \"" + dirname + "\"");
		return true;
	}
	else goto mdir_error;

mdir_error:
	LogProcess log;
	log.write("error", "Failed make a directory");
	return false;
}

bool command::rdir(int CommandNumber, string dirname)
{
	if(CommandNumber < 2)goto rdir_error;

	if(!_rmdir(dirname.c_str()))
	{
		LogProcess log;
		log.write("info", "Removed a directory \"" + dirname + "\"");
		return true;
	}
	else goto rdir_error;

rdir_error:
	LogProcess log;
	log.write("error", "Failed remove a directory");
	return false;
}
