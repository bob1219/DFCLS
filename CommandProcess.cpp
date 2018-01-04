// Standard Libraries
#include <string>
#include <cstdio>
#include <cstdlib>
#include <iostream>

// Headers
#include "constant.h"
#include "command-function.h"

using namespace std;
using namespace dfcls;

bool CommandProcess(string command)
{
	char commands_c[COMMAND_NUMBER_MAX][COMMAND_MAX];
	char format[FORMAT_MAX];
	sprintf(format, "%%%us %%%us %%%us %%%us %%%us %%%us %%%us %%%us %%%us %%%us", COMMAND_MAX, COMMAND_MAX, COMMAND_MAX, COMMAND_MAX, COMMAND_MAX, COMMAND_MAX, COMMAND_MAX, COMMAND_MAX, COMMAND_MAX, COMMAND_MAX);
	int CommandNumber = sscanf(command.c_str(), format, commands_c[0], commands_c[1], commands_c[2], commands_c[3], commands_c[4], commands_c[5], commands_c[6], commands_c[7], commands_c[8], commands_c[9]);
	string commands[COMMAND_NUMBER_MAX] = {
		commands_c[0],
		commands_c[1],
		commands_c[2],
		commands_c[3],
		commands_c[4],
		commands_c[5],
		commands_c[6],
		commands_c[7],
		commands_c[8],
		commands_c[9]
	}

	if(CommandNumber == EOF)
		return false;

	if(commands[0] == "mdir")
		return command::mdir(CommandNumber, commands[1]);
	else if(commands[0] == "rdir")
		return command::rdir(CommandNumber, commands[1]);
	else if(commands[0] == "chdir")
		return command::chdir(CommandNumber, commands[1]);
	else if(commands[0] == "cwdir")
		return command::cwdir();
	else if(commands[0] == "mfile")
		return command::mfile(CommandNumber, commands[1]);
	else if(commands[0] == "rfile")
		return command::rfile(CommandNumber, commands[1]);
	else if(commands[0] == "cfile")
		return command::cfile(CommandNumber, commands[1], commands[2]);
	else if(commands[0] == "lfile")
		return command::lfile(CommandNumber, commands[1]);
	else if(commands[0] == "rename")
		return command::rename(CommandNumber, commands[1], commands[2]);
	else if(commands[0] == "tview")
		return command::tview(CommandNumber, commands[1]);
	else if(commands[0] == "bview")
		return command::bview(CommandNumber, commands[1]);
	else if(commands[0] == "version")
		return command::version();
	else if(commands[0] == "app")
		return command::app(CommandNumber, commands);
	else if(commands[0] == "date")
		return command::date();
	else if(commands[0] == "time")
		return command::time();
	else if(commands[0] == "now")
		return command::now();
	else if(commands[0] == "exit")
		exit(EXIT_SUCCESS);
	else
	{
		cerr << "Error: Unknown command \"" << commands[0] << "\"." << endl;
		return false;
	}
}