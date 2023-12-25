#include "header/MLOpenCV.hpp"

// OpenCV command line parser functions
// Keys accecpted by command line parser
const char* keys =
{
   "{help h usage ? | | print this message}"
   "{@image || Image to classify}"
};

int main(int argc, const char** argv)
{
    CommandLineParser parser(argc, argv, keys);
    parser.about("Chapter 6");
    //If requires help show
    if (parser.has("help"))
    {
        parser.printMessage();
        return 0;
    }

    String imgFile= parser.get<String>(0);
    String lightPatternFile= "data/raw/pattern.pgm";
    
    // Check if params are correctly parsed in his variables
    if (!parser.check())
    {
        parser.printErrors();
        return 0;
    }

    imgFile = "data/raw/test.pgm";
    MLOpenCV(imgFile, lightPatternFile);

    return 0;
}