#ifndef ENCODING_UTILS_HEADER
#define ENCODING_UTILS_HEADER

#include <string>

class EncodingUtils
{
	public:
		static std::string UTF8ToIndex(const std::string& utf8);
		static std::string IndexToUTF8(const std::string& index);
		static std::string IndexToUTF8(const char& index);
};

#endif