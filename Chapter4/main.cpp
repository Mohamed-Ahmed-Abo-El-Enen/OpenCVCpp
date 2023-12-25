#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;

#include "header/PhotoTool.hpp"

// OpenCV command line parser functions
// Keys accecpted by command line parser
const char* keys =
{
	"{help h usage ? | | print this message}"
    "{@image | | Image to process}"
};

int main(int argc, const char** argv)
{
    CommandLineParser parser(argc, argv, keys);
    parser.about("Chapter 4");
    //If requires help show
    if (parser.has("help"))
	{
	    parser.printMessage();
	    return 0;
	}

	String imgFile = parser.get<String>(0);

	// Check if params are correctly parsed in his variables
	if (!parser.check())
	{
	    parser.printErrors();
	    return 0;
	}

    imgFile = "data/raw/photo.jpg";

    PhotoTool(imgFile);

    return 0;
}