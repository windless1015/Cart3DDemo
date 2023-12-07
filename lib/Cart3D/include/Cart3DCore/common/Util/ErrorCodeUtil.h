#ifndef CART3D_ERRORCODE_UTIL_H
#define CART3D_ERRORCODE_UTIL_H
#include <string>
#include <map>

namespace Cart3D
{
	using ErrorStatus = std::pair<int, std::string>;
	const ErrorStatus errorcode[] = {
		std::make_pair(0,"run_ok"),

	};
}


#endif