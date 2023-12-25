#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/text.hpp>

#include <vector>
#include <iostream>

using namespace std;
using namespace cv;
using namespace cv::text;

vector<Mat> SeperateChannels(const Mat& src)
{
    vector<Mat> channels;
    // Grayscale image
    if(src.type() == CV_8U || src.type() == CV_8UC1)
    {
        channels.push_back(src);
        channels.push_back(255-src);
        return channels;
    }

    // Colored images
    if(src.type() == CV_8UC3)
    {
        computeNMChannels(src, channels);
        int size = static_cast<int>(channels.size())-1;
        for(int c=0; c<size; c++)
        {
            channels.push_back(255-channels[c]);
        }
        return channels;
    }

    // Other types
    cout<<"Invalid image format"<<endl;
    exit(-1);
}

int DetectText(int argc, const char* argv[])
{
    // const char* image = argc < 2 ? "easel.png":argv[1];
    const char* image = "data/raw/easel.png";
    auto input = imread(image);

    // Convert the input image to grayscale
    // Just do 
    // Mat processed = input; // to work with colors

    Mat processed;
    cvtColor(input, processed, COLOR_BGR2GRAY);

    auto channels = SeperateChannels(processed);

    // Create ERFilter objects with the 1st and 2nd stage classifiers
    auto filter1 = createERFilterNM1(loadClassifierNM1("resources/trained_classifierNM1.xml"), 15, 0.00015f, 0.13f, 0.2f, true, 0.1f);
    auto filter2 = createERFilterNM2(loadClassifierNM2("resources/trained_classifierNM2.xml"), 0.5);

    // Extract text region using Newmann & Matas alogrithms
    cout<<"Processing "<<channels.size()<<" channels..."<< endl;
    vector<vector<ERStat>> regions(channels.size());
    for(int c=0; c < channels.size(); c++)
    {
        cout<<" Channel "<<(c+1)<<endl;
        filter1->run(channels[c], regions[c]);
        filter2->run(channels[c], regions[c]);
    }
    filter1.release();
    filter2.release();

    // Separate character groups from regions
    vector<vector<Vec2i>> groups;
    vector<Rect> groupRects;
    erGrouping(input, channels, regions, groups, groupRects, ERGROUPING_ORIENTATION_HORIZ);
    // erGrouping(input, channels, regions, groups, groupRects, ERGROUPING_ORIENTATION_ANY, "resources/trained_classifier_erGrouping.xml", 0.5);

    // Draw group boxes
    for(const auto& rect:groupRects)
    {
        rectangle(input, rect, Scalar(0, 255, 0), 3);
    }
    imshow("grouping", input);
    waitKey(0);

    return 0;
}
