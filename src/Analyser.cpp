
#include "Analyser.hpp"
#include <fstream>

std::vector<cv::Mat> Analyser::templates;
cv::Rect Analyser::roi;

std::vector<std::vector<char>> Analyser::MatchLetter(cv::Mat& image)
{

}

bool Analyser::LoadTemplates(std::string filename, std::string data_dir)
{
	templates.clear();
	std::fstream temps;
	temps.open(filename);
	while(!temps.eof())
	{
		std::string fname;
		temps >> fname;
		if (fname == "\n") continue;
		if (fname != "-1")
		{
			std::string full_name = data_dir;
			full_name += fname;
			std::cout << fname << std::endl;
			templates.push_back(cv::imread(full_name));
		}
		else
		{
			templates.push_back(cv::Mat());
		}
		// cv::imshow(fname, templates.back());
		// cv::waitKey(0);
	}
	temps.close();
	
	return templates.size() != 0;
}

bool Analyser::LoadSettings(std::string filename)
{
	std::fstream settings;
	settings.open(filename);
	int x, y, w, h;
	settings >> x >> y >> w >> h;
	roi = cv::Rect(x, y, w, h);
	settings.close();
	return roi.area();
}