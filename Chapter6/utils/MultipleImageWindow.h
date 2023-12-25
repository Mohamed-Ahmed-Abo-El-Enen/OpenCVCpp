#ifndef MIW_h
#define MIW_h

#include <string>
#include <iostream>
using namespace std;

// OpenCV includes
#include <X11/Xlib.h>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

class MultipleImageWindow
{
    private:
        int cols;
        int rows;
        int canvas_width;
        int canvas_height;
        string window_title;
        vector<string> titles;
        vector<Mat> images; 
        Mat canvas;

        public:
        /**
         * Constructor
         * Create new window with a max of cols*row images
         *
         * @param string window_title 
         * @param int cols number of cols
         * @param int rows number of rows
         * @param int flags see highgui window documentation
         */
        MultipleImageWindow(string window_title, int cols, int rows, int flags);

        /**
         * Add new image to stack of window
         * @param Mat image
         * @param string title caption of image to show
         * @return int position of image in stack
         */
        int AddImage(string title, Mat image, bool render= false);

        /**
         * Remove a image from position n
         */
        void RemoveImage(int pos);

        /**
         * Render/redraw/update window
         */
        void Render();

        /**
         * GetDesktopResolution
         */
        void GetDesktopResolution(int& horizontal, int& vertical);
};


#endif
