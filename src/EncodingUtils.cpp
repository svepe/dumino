#include "EncodingUtils.hpp"

std::string EncodingUtils::UTF8ToIndex(const std::string& utf8)
{
	std::string index;
	
	for(unsigned int i = 0; i < utf8.length(); i += 2)
	{
		char idx = 0;
		if ((utf8[i] & 0xff) == 0xd0)
		{
			idx = (utf8[i + 1]  & 0xff) - 0xb0;
		} 
		else if ((utf8[i] & 0xff) == 0xd1)
		{
			idx = 0x10 + (utf8[i + 1]  & 0xff) - 0x80;	
		}

		// std::cout << "[Dictionary.cpp] utf8 " << std::hex << (unsigned int)utf8[i] 
		// 	<< " " << std::hex << (unsigned int)utf8[i + 1] << " " << std::endl;
		// std::cout << "[Dictionary.cpp] idx " << idx << std::endl;

		index += idx;
	}

	return index;
}

std::string EncodingUtils::IndexToUTF8(const std::string& index)
{
	std::string utf8;
	
	for(unsigned int i = 0; i < index.length(); ++i)
	{
		utf8 += IndexToUTF8(index[i]);
	}

	return utf8;
}

inline std::string EncodingUtils::IndexToUTF8(const char& index)
{
	std::string utf8;
	
	if(index <= 0x0f)
	{
		utf8.push_back(0xd0);
		utf8.push_back(index + 0xb0);
	} 
	else
	{
		utf8.push_back(0xd1);
		utf8.push_back(index + 0x80 - 0x10);	
	}

	return utf8;
}