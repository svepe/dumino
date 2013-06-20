#ifndef DICTIONARY_ITEM_HEADER
#define DICTIONARY_ITEM_HEADER

#include <string>
#include <cstdlib> 

const int ALPHABET_LETTERS = 32; //Russian without ё
const char FIRST_LETTER = 0xb0; //Cyrilic а = 0xd0b0

class DictionaryItem
{
	public:
		char value;
		bool endOfWord;
		DictionaryItem** children;

		DictionaryItem(char v = 0)
		{
			value = v;

			endOfWord = false;

			children = new DictionaryItem*[ALPHABET_LETTERS];
			for (int i = 0; i < ALPHABET_LETTERS; ++i)
			{
				children[i] = NULL;
			}
		}
		
		void AddChildren(DictionaryItem* item, int index)
		{
			children[index] = item;
		}

		bool IsLeaf()
		{
			for (int i = 0; i < ALPHABET_LETTERS; ++i)
			{
				if(children[i] != NULL)
					return false;
			}	

			return true;
		}

};

class Dictionary
{
	public:
		Dictionary();
		Dictionary(std::string filename);

		void InsertWord(const std::string& word_utf8);
		bool ContainsWord(const std::string& word);	
	
		DictionaryItem* root;
		
	private:

		void InsertWord(DictionaryItem* item, std::string word);
		bool ContainsWord(DictionaryItem* item, std::string word);
};
#endif