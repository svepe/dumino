#ifndef ANALYSER_HEADER
#define ANALYSER_HEADER

#include <opencv2/opencv.hpp>
#include <vector>

const int  LETTER_OFFSET_PX = 5;


class Analyser
{
public:
	static bool LoadTemplates(std::string filename, std::string data_dir);
	static bool LoadSettings(std::string filename);
	static std::vector<std::vector<unsigned char>> MatchLetter(cv::Mat& image);

private:
	static std::vector<cv::Mat> templates;
	static cv::Rect roi;
};

#endif
