#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>


using namespace cv;
using namespace std;

int imProcess(Mat imBig, Mat imSmall);
void matchingMethod(int,void*);

bool useMask;
Mat imBig,imSmall ,imResult;
int matchMethhod;
int maxTrackBar =5;
int main()
{
    string inputSmallPath ="D:\\Workspaces\\Qt Workspace\\TaskProject4DSight\\InputImages\\Small_area.png";
    string inputBigPath = "D:\\Workspaces\\Qt Workspace\\TaskProject4DSight\\InputImages\\StarMap.png";
    imBig = imread(inputBigPath,IMREAD_COLOR);
    imSmall = imread(inputSmallPath,IMREAD_COLOR);

    if (imBig.empty()||imSmall.empty()) {
        cout << "Empty" << endl;
        return EXIT_FAILURE;
    }

    useMask=true;
    namedWindow("Source",WINDOW_AUTOSIZE);

    char* trackBar= "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
    createTrackbar(trackBar,"Source",&matchMethhod,maxTrackBar,matchingMethod);
    matchingMethod(0,0);

    waitKey(0);
    return EXIT_SUCCESS;
}

void matchingMethod(int,void*){
    Mat imDisplay;
    imBig.copyTo(imDisplay);

    int resultCols = imBig.cols +1;
    int resultRows = imBig.rows +1;

    imResult.create(resultRows,resultCols,CV_32FC1);

    matchTemplate(imBig,imSmall,imResult,matchMethhod);
    normalize(imResult,imResult,0,1,NORM_MINMAX,-1,Mat());

    double minVal ,maxVal; Point minLoc, maxLoc, matchLoc;
    minMaxLoc(imResult,&minVal,&maxVal,&minLoc,&maxLoc,Mat());

    if(matchMethhod==TM_SQDIFF || matchMethhod == TM_SQDIFF_NORMED){
        matchLoc = minLoc;
    }else{
        matchLoc = maxLoc;
    }

    rectangle(imDisplay,matchLoc,Point(matchLoc.x+imSmall.cols,matchLoc.y+imSmall.rows),Scalar(0,255,0),2,8,0);

    imshow("Source",imDisplay);
}
