#ifndef VIRTUAL_HID_HEADER
#define VIRTUAL_HID_HEADER

#include <opencv2/opencv.hpp>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>

class VirtualHID
{
	public:
		VirtualHID();
		~VirtualHID();

		void TakeScreenshot(cv::Mat& image);
		void ClickKey(KeySym keysym);
	private:
		Display* display;


};



#endif
