#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// OpenCV includes
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

int ReadImage(int argc, const char** argv)
{
	// Read images
	Mat color= imread("data/raw/lena.jpg");
	Mat gray= imread("data/raw/lena.jpg", IMREAD_GRAYSCALE);
	
	if(! color.data ) // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl ;
	 	return -1;
	}

	// Write images
	imwrite("data/processed/lenaGray.jpg", gray);
	
	// Get same pixel with opencv function
	int myRow=color.cols-1;
	int myCol=color.rows-1;
	auto pixel= color.at<Vec3b>(myRow, myCol);
	cout << "Pixel value (B,G,R): (" << (int)pixel[0] << "," << (int)pixel[1] << "," << (int)pixel[2] << ")" << endl;
	
	// show images
	imshow("Lena BGR", color);
	imshow("Lena Gray", gray);
	
	// wait for any key press
	waitKey(0);

	return 0;
}
