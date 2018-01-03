// Standard Libraries
#include <iostream>
#include <cstdlib>

// Header
#include "normal-function.h"

using namespace std;
using namespace dfcls;

int main()
{
	// prepering
	cout << "Prepering DFCLS...";
	if(!prepering())
	{
		cerr << "Failed." << endl;
		return EXIT_FAILURE;
	}
	cout << "Done." << endl;

	welcome();
	cout << endl;
	CommandLine();
}
