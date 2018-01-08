// Standard Library
#include <string>
#include <iostream>
#include <fstream>

// Header
#include "normal-function.h"

using namespace std;

namespace dfcls
{
	bool script(const string &filename)
	{
		ifstream ifs(filename);
		if(ifs.fail())return false;

		string line;
		for(unsigned int i = 1 ; getline(ifs, line) ; i++)
		{
			if(CommandProcess(line))
				cout << "Succeeded in line " << i << "." << endl;
			else
				cerr << "Failed in line " << i << "." << endl;
		}

		return true;
	}
}
