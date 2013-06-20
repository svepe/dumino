#ifndef DUMINO_SOLVER_HEADER
#define DUMINO_SOLVER_HEADER

#include <vector>
#include <string>
#include <opencv2/opencv.hpp>
#include "Dictionary.hpp"


typedef std::vector<std::vector<unsigned char>> DuminoGrid;


class DuminoSolver
{
	public:
		static void Play(const DuminoGrid& grid,
		                 const Dictionary& dict);

	private:
		static void FindWord(const DuminoGrid& grid, 
		                     DictionaryItem* item,
		                     cv::Point p,
		                     std::string word); 
		static void Type(std::string word);

		static bool used[5][5];

};

#endif