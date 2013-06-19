#include "Dictionary.hpp"

#include <iostream>
#include <fstream>

Dictionary::Dictionary()
{
	root = new DictionaryItem();
}

Dictionary::Dictionary(std::string filename)
{
	root = new DictionaryItem();

	std::ifstream dict(filename);

	std::string word, word_utf8;
	while(!dict.eof())
	{
		dict >> word_utf8;

//		if(word_utf8.length() > 2) return;

		//std::cout << "[Dictionary.cpp] " << word_utf8 << std::endl;
		InsertWord(word_utf8);
	}

	dict.close();
}

inline void Dictionary::InsertWord(const std::string& word_utf8)
{
	InsertWord(root, UTF8toIndex(word_utf8));
}

inline bool Dictionary::ContainsWord(const std::string& word)
{
	return ContainsWord(root, word);
}

void Dictionary::InsertWord(DictionaryItem* item, std::string word)
{
	if(word.length() == 0) 
	{
		item->endOfWord = true;
		return;
	}

	int children_idx = word[0]; 
	if(item->children[children_idx] == NULL)
	{
		item->AddChildren(new DictionaryItem(word[0]), children_idx);
	}
	
	InsertWord(item->children[children_idx], word.substr(1, word.length() - 1));

}

bool Dictionary::ContainsWord(DictionaryItem* item, std::string word)
{
	if(word.length() == 0)
	{
		if(!item->endOfWord) 
			return false;
		else
			return true;
	}
	
	int children_idx = word[0]; 
	if(item->children[children_idx] == NULL) return false;

	return ContainsWord(item->children[children_idx], word.substr(1, word.length() - 1));
}

std::string Dictionary::UTF8toIndex(const std::string& utf8)
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