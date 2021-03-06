#include "VirtualHID.hpp"
#include "Dictionary.hpp"
#include "Analyser.hpp"
#include "DuminoSolver.hpp"
#include "EncodingUtils.hpp"
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
	auto grid = Analyser::MatchLetter(image);
	for (int x = 0; x < 5; ++x)
	{
		for (int y = 0; y < 5; ++y)
		{
			std::cout << EncodingUtils::IndexToUTF8(grid[x][y]) << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "Playing..." << std::endl;
	DuminoSolver::Play(grid, dict);
	std::cout << "Done!" << std::endl;
	//	vhid.ClickKey(XK_A);
	//	vhid.MouseClick(Button1);
	return 0;
}
