#ifndef _CLASS_H_
#define _CLASS_H_

// Standard Library
#include <string>

namespace dfcls
{
	class LogProcess
	{
	public:
		bool init();
		void write(const std::string &type, const std::string &message);

	private:
		static std::string filename;
	};
}

#endif
