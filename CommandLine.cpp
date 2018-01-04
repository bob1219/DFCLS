// Standard Library
#include <string>
#include <iostream>

// Header
#include "normal-function.h"

using namespace std;
using namespace dfcls;

void CommandLine()
{
	string command;

	while(true)
	{
		getline(cin, command);
		if(CommandLine(command))
			cout << "succeeded." << endl;
		else
			cerr << "failed." << endl;

		cout << endl;
	}
}
