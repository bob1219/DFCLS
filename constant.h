#ifndef _CONSTANT_H_
#define _CONSTANT_H_

// Standard Library
#include <cstddef>
#include <string>

namespace dfcls
{
	static const char		PATH_BREAK_CHARACTER	= '\\';
	static const std::string	VERSION			= "1.0";
	static const std::size_t	SETTING_NAME_MAX	= 13;
	static const std::size_t	SETTING_CONTENT_MAX	= 200;
	static const std::size_t	FORMAT_MAX		= 100;
	static const std::size_t	COMMAND_NUMBER_MAX	= 10;
	static const std::size_t	COMMAND_MAX		= 200;
	static const std::size_t	FILE_SIZE_MAX		= 102400;
	static const std::size_t	DATE_MAX		= 5;
}

#endif
