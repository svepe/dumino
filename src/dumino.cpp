#include "VirtualHID.hpp"
#include "Dictionary.hpp"
#include <fstream>

int main (int argc, char* argv[])
{
	Dictionary dict("./dict/bg/bg8.dic");

	std::cout << "[dumino.cpp] Loaded " << std::endl;

	VirtualHID vhid;

	cv::Mat image;
	vhid.TakeScreenshot(image);

	std::cout << "[dumino.cpp] Screeshot taken " << std::endl;

	char key;
	while(true)
	{
		key = cv::waitKey(2);
		if(key == 'q') break;

		imshow("Screen", image);

		std::cout << "[dumino.cpp] new key ";
		vhid.ClickKey(XK_A);
		std::cout << std::endl;
	}
	return 0;
}