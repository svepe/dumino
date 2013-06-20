#include "VirtualHID.hpp"
#include "Dictionary.hpp"
#include "Analyser.hpp"
#include <fstream>

int main (int argc, char* argv[])
{
	Dictionary dict("./dict/bg/bg8.dic");

	std::cout << "[dumino.cpp] Loaded " << std::endl;

	VirtualHID vhid;

	cv::Mat image;
	vhid.TakeScreenshot(image);
	std::cout << "[dumino.cpp] Screeshot taken " << std::endl;

	Analyser::LoadTemplates("./letters/letters.list", "./letters/");
	Analyser::LoadSettings("./roi.settings");

	char key;
	while(true)
	{
		key = cv::waitKey(50);
		if(key == 'q') break;

		imshow("Screen", image);

		//vhid.ClickKey(XK_A);
		//vhid.MouseClick(Button1);
	}
	return 0;
	}
