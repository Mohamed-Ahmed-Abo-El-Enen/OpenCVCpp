#include <fstream>
#include <sstream>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace dnn;
using namespace std;

// Initialize the parameters
float confThreshold = 0.5;      // Confidence threshold
float nmsThreshold = 0.4;       // Non-maximum suppression threshold
int inpWidth = 416;             // Width of network's input image
int inpHeight = 416;            // Height of network's input image
vector<string> classes;

// Draw the predicted bounding box
void DrawPred(int classId, float conf, int left, int top, int right, int bottom, Mat& frame)
{
    // Draw a rectangle displaying the bounding box
    rectangle(frame, Point(left, top), Point(right, bottom), Scalar(255, 255, 255), 1);

    // Get The label for the class name and its confidence
    string conf_label = format("%.2f", conf);
    string label = "";
    if(!classes.empty())
    {
        label = classes[classId] + ":"+ conf_label;
    }

    // Display the label at the top of the bounding box
    int baseline;
    Size labelSize = getTextSize(label, FONT_HERSHEY_COMPLEX, 0.5, 1, &baseline);
    top = max(top, labelSize.height);
    rectangle(frame, Point(left, top - labelSize.height), Point(left + labelSize.width, top + baseline), Scalar(255,255,255), FILLED);
    putText(frame, label, Point(left, top), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,0), 1, LINE_AA);
}

// Remove the label at the top of the bounding box
void postprocess(Mat& frame, const vector<Mat>& outs)
{
    vector<int> classIds;
    vector<float> confidences;
    vector<Rect> boxes;

    for(size_t i=0; i<outs.size(); ++i)
    {
        // Scane through all the bounding boxes output from the network and keep only the
        // ones with high confidence socres. Assign the box's class label as the class
        // with the highest score for box
        float* data = (float*)outs[i].data;
        for(int j=0; j < outs[i].rows; ++j, data += outs[i].cols)
        {
            Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
            Point classIdPoint;
            double confidence;

            // get the value and location of the maximum score
            minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
            if(confidence > confThreshold)
            {
                int centerX = (int)(data[0]*frame.cols);
                int centerY = (int)(data[1]*frame.rows);
                int width = (int) (data[2]*frame.cols);
                int height = (int) (data[2]*frame.rows);
                int left = centerX - width / 2;
                int top = centerY - height / 2;

                classIds.push_back(classIdPoint.x);
                confidences.push_back((float)confidence);
                boxes.push_back(Rect(left, top, width, height));

            }
        }
    }

    // Perform non maximum suppression to eliminate redundent overlapping boxes with
    // lower confidence 
    vector<int> indices;
    NMSBoxes(boxes, confidences, confThreshold, nmsThreshold, indices);
    for(size_t i=0; i<indices.size(); ++i)
    {
        int idx = indices[i];
        Rect box = boxes[idx];
        DrawPred(classIds[idx], confidences[idx], box.x, box.y, box.x+box.width, box.y+box.height, frame);
    }
}