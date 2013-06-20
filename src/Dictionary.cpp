#include "Dictionary.hpp"

#include <iostream>
#include <fstream>
#include "EncodingUtils.hpp"

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
	InsertWord(root, EncodingUtils::UTF8ToIndex(word_utf8));
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

