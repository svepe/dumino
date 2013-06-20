#include "DuminoSolver.hpp"
#include "EncodingUtils.hpp"

bool DuminoSolver::used[5][5];

const cv::Point nbrs[8] =
{
	cv::Point(-1, -1),
	cv::Point(0, -1),
	cv::Point(1, -1),
	cv::Point(-1, 0),
	cv::Point(1, 0),
	cv::Point(-1, 1),
	cv::Point(0, 1),
	cv::Point(1, 1)
};

void DuminoSolver::Play(const std::vector<std::vector<unsigned char>> &grid,
                        const Dictionary &dict)
{
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			used[i][j] = false;
		}
	}
	
	FindWord(grid, dict.root, cv::Point(0, 0), "");
}

void DuminoSolver::FindWord(const DuminoGrid &grid,
              DictionaryItem* item,
              cv::Point p,
              std::string word)
{

	for (int i = 0; i < 8; ++i)
	{
		cv::Point new_p = p + nbrs[i];

		if(new_p.x < 0 || new_p.x >= 5 || new_p.y < 0 || new_p.y >= 5)
			continue;

		used[new_p.y][new_p.x] = true;
		int index = grid[new_p.y][new_p.x];
		if(item->children[index] != NULL)
		{
			word.push_back(item->children[index]->value);

			if(item->children[index]->endOfWord)
			{
				Type(word);
			}

			FindWord(grid, item->children[index], new_p, word);
		}

		word.pop_back();
		used[new_p.y][new_p.x] = false;
	}
}

void DuminoSolver::Type(std::string word)
{
	std::cout << "[DuminoSolver.cpp] Word " << EncodingUtils::IndexToUTF8(word) << std::endl;
}