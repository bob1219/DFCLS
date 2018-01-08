// Standard Library
#include <string>
#include <iostream>

// Header
#include "normal-function.h"
#include "extern.h"

using namespace std;

namespace dfcls
{
	void CommandLine()
	{
		string command;

		while(true)
		{
			cout << prompt;
			getline(cin, command);
			if(CommandProcess(command))
				cout << "succeeded." << endl;
			else
				cerr << "failed." << endl;

			cout << endl;
		}
	}
}
