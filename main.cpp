// Standard Library
#include <iostream>
#include <cstdlib>

// Header
#include "normal-function.h"

using namespace std;
using namespace dfcls;

int main(int argc, char **argv)
{
	// prepering
	cout << "Prepering DFCLS...";
	if(!prepering())
	{
		cerr << "Failed." << endl;
		return EXIT_FAILURE;
	}
	cout << "Done." << endl;

	if(argc >= 2)
	{
		if(script(argv[1]))
		{
			cout << "Succeeded run a script \"" << argv[1] << "\"." << endl;
			return EXIT_SUCCESS;
		}
		else
		{
			cout << "Failed run a script \"" << argv[1] << "\"." << endl;
			return EXIT_FAILURE;
		}
	}

	welcome();
	cout << endl;
	CommandLine();
}
