#ifndef _CLASS_H_
#define _CLASS_H_

// Standard Library
#include <string>

namespace dfcls
{
	class LogProcess
	{
	public:
		LogProcess();
		bool init();
		void write(std::string type, std::string message);

	private:
		std::string filename;
	};
}

#endif
