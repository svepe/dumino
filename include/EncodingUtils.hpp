#ifndef ENCODING_UTILS_HEADER
#define ENCODING_UTILS_HEADER

#include <string>
#include <X11/Xutil.h>

class EncodingUtils
{
	public:
		static std::string UTF8ToIndex(const std::string& utf8);
		static std::string IndexToUTF8(const std::string& index);
		static std::string IndexToUTF8(const char& index);
		
		static KeySym IndexToKeySym(char c);
};

#endif