#include "header/SegmentTool.hpp"

// OpenCV command line parser functions
// Keys accecpted by command line parser
const char* keys =
{
	"{help h usage ? | | print this message}"
	"{@image || Image to process}"
	"{@lightPattern || Image light pattern to apply to image input}"
	"{lightMethod | 1 | Method to remove backgroun light, 0 differenec, 1 div, 2 no light removal' }"
	"{segMethod | 1 | Method to segment: 1 connected Components, 2 connectec components with stats, 3 find Contours }"
};

int main(int argc, const char** argv)
{
    CommandLineParser parser(argc, argv, keys);
	parser.about("Chapter 5");
	//If requires help show
	if (parser.has("help"))
	{
		parser.printMessage();
		return 0;
	}

	String imgFile= parser.get<String>(0);
	String lightPatternFile= parser.get<String>(1);
	auto methodLight= parser.get<int>("lightMethod");
	auto methodSeg= parser.get<int>("segMethod");
    

	// Check if params are correctly parsed in his variables
	if (!parser.check())
	{
		parser.printErrors();
		return 0;
	}

    imgFile = "data/raw/test.pgm";
    lightPatternFile = "data/raw/light.pgm";
    methodLight= 1;
    methodSeg = 1;

    SegmentTool(imgFile, lightPatternFile, methodLight, methodSeg);
}