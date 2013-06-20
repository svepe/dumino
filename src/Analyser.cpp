
#include "Analyser.hpp"
#include <fstream>

using namespace cv;

std::vector<cv::Mat> Analyser::templates;
cv::Rect Analyser::roi;

std::vector<std::vector<unsigned char>> Analyser::MatchLetter(cv::Mat& image)
{
	std::vector<std::vector<unsigned char>> res(5);
	for (size_t i = 0; i < 5; ++i) res[i].resize(5);

	int width =  (roi.width - 4 * LETTER_OFFSET_PX) / 5;
	int height = (roi.height - 4 * LETTER_OFFSET_PX) / 5;
	
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			cv::Rect sroi(roi.x + j * width + j* LETTER_OFFSET_PX,
						  roi.y + i * height + i * LETTER_OFFSET_PX,
						  width,
						  height);
			cv::Mat sample = image(sroi).clone();

			// imshow("sample", sample);
			// cv::waitKey(0);
			unsigned int all_best_idx = 0;
			unsigned int all_min_value = 1e9;
			for (size_t idx = 0; idx < templates.size(); ++idx)
			{
				if(!templates[idx].data) continue;
				cv::Mat result(sample.cols, sample.rows, CV_32FC1 );
				matchTemplate(sample, templates[idx], result, CV_TM_SQDIFF);
				//normalize(result, result, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
				
				double min_val = result.at<float>(0, 0);
				//std::cout << "Max " << min_val << std::endl;
				if (min_val < all_min_value)
				{
					all_best_idx = idx;
					all_min_value = min_val;
				}
			}
			res[i][j] = all_best_idx;
		}
	}
	return res;
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
			// std::cout << fname << std::endl;
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