#include "header/BasicWindowControl1.hpp"
#include "header/BasicWindowControl2.hpp"
#include "header/WindowControlButtons.hpp"
#include "header/WindowControlMouse.hpp"
#include "header/OpenGLWindow.hpp"
#include "header/VizWindow.hpp"

// OpenCV command line parser functions
// Keys accecpted by command line parser
const char* keys =
{
	"{help h usage ? | | print this message}"
    "{@image | | image to load}"
};


int main( int argc, const char** argv )
{
	CommandLineParser parser(argc, argv, keys);
    parser.about("Chapter 3");
    //If requires help show
    if (parser.has("help"))
	{
	    parser.printMessage();
	    return 0;
	}

	string image= parser.get<string>(0);

	// Check if params are correctly parsed in his variables
	if (!parser.check())
	{
	    parser.printErrors();
	    return 0;
	}

	// BasicWindowControl1(argc, argv);
	// BasicWindowControl2(argc, argv);
	// WindowControlButtons(argc, argv);
	// WindowControlMouse(argc, argv);
	VizWindow();

	return 0;
}