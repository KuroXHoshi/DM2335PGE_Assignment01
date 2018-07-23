#ifndef ANDROIDCOMPILE_H
#define ANDROIDCOMPILE_H

#include <string>
#include <sstream>

template <typename T>
static std::string to_string(T value)
{
	std::ostringstream os;
	os << value;
	return os.str();
}

#endif