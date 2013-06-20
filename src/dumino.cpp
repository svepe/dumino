#include "VirtualHID.hpp"
#include "Dictionary.hpp"
#include "Analyser.hpp"
#include "DuminoSolver.hpp"
#include <fstream>
#include <unistd.h>

int main (int argc, char* argv[])
{
	Dictionary dict("./dict/bg/bg8.dic");

	std::cout << "[dumino.cpp] Loaded " << std::endl;

	VirtualHID vhid;

	sleep(5);
	cv::Mat image;
	vhid.TakeScreenshot(image);
	std::cout << "[dumino.cpp] Screeshot taken " << std::endl;

	Analyser::LoadTemplates("./letters/letters.list", "./letters/");
	Analyser::LoadSettings("./roi.settings");
	std::cout << "Matching..." << std::endl;
	auto res = Analyser::MatchLetter(image);
	for (int x = 0; x < 5; ++x)
	{
		for (int y = 0; y < 5; ++y)
		{
			std::cout << (unsigned int)res[x][y] << " ";
		}
		std::cout << std::endl;
	}

	cv::waitKey(0);
	char key;
	while(true)
	{
		key = cv::waitKey(50);
		if(key == 'q') break;

		//imshow("Screen", image);

		//vhid.ClickKey(XK_A);
		//vhid.MouseClick(Button1);
	}
	return 0;
	}
