#include "MultipleImageWindow.h"

void MultipleImageWindow::GetDesktopResolution(int& horizontal, int& vertical)
{
    Display* disp = XOpenDisplay(NULL);
    Screen*  scrn = DefaultScreenOfDisplay(disp);
    horizontal = scrn->height;
    vertical = scrn->width;
}

MultipleImageWindow::MultipleImageWindow(string window_title, int cols, int rows, int flags)
{
    this->windowTitle= window_title;
    this->cols= cols;
    this->rows= rows;
    namedWindow(window_title, flags);

    int horizontal;
    int vertical;
    GetDesktopResolution(horizontal, vertical);
    this->canvasWidth= vertical;
    this->canvasHeight= horizontal;

    this->canvas= Mat(this->canvasHeight, this->canvasWidth, CV_8UC3);     
    imshow(this->windowTitle, this->canvas);
}

int MultipleImageWindow::AddImage(string title, Mat image, bool render)
{
    this->titles.push_back(title);
    this->images.push_back(image);
    if(render)
        this->Render();
    return this->images.size()-1;
}

void MultipleImageWindow::RemoveImage(int pos)
{
    this->titles.erase(this->titles.begin()+pos);
    this->images.erase(this->images.begin()+pos);
}

void MultipleImageWindow::Render()
{
    // Clean our canvas
    this->canvas.setTo( Scalar(20,20,20) );
    // width and height of cell. add 10 px of padding between images
    int cell_width= (canvasWidth/cols);
    int cell_height= (canvasHeight/rows);
    int margin= 10;
    int max_images=(this->images.size()>cols*rows)?cols*rows:this->images.size();
    int i=0;
    vector<string>::iterator titles_it= this->titles.begin();
    for(vector<Mat>::iterator it= this->images.begin(); it!= this->images.end(); ++it)
    {
        string title= *titles_it;
        int cell_x= (cell_width)*((i)%cols);
        int cell_y= (cell_height)*floor((i)/(float)cols);
        Rect mask(cell_x, cell_y, cell_width, cell_height);
        // Draw a rectangle for each cell mat 
        rectangle(canvas, Rect(cell_x, cell_y, cell_width, cell_height), Scalar(200,200,200), 1);
        //For each cell draw an image if exists
        Mat cell(this->canvas, mask);
        // resize image to cell size
        Mat resized;
        double cell_aspect= (double)cell_width/(double)cell_height;
        Mat img= *it;
        double img_aspect= (double)img.cols/(double)img.rows;
        double f=(cell_aspect<img_aspect)?(double)cell_width/(double)img.cols:(double)cell_height/(double)img.rows;
        
        resize(img, resized, Size(0,0), f, f);
        if(resized.channels()==1)
        {
            cvtColor(resized, resized, COLOR_GRAY2BGR); 
        }

        // Assign the image
        Mat sub_cell(this->canvas, Rect(cell_x,cell_y,resized.cols, resized.rows));
        resized.copyTo(sub_cell);
        putText(cell, title.c_str(), Point(20,20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(200,0,0), 1, LINE_AA);
        i++;
        ++titles_it;
        if(i==max_images)
            break;
    }

    // show image
    imshow(this->windowTitle, this->canvas);
}

