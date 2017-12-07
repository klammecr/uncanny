#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace cv; // imread
using namespace std; // cout + endl

void checkImageInDir(cv::Mat &inputImage, String imageName){
    if(! inputImage.data )
    {
        std::cout <<  "Could not locate " << imageName << " in the current directory." << std::endl;
        return;
    } else {
        std::cout <<  imageName << " found!" << std::endl;
    }
}

bool checkSameSize(cv::Mat &inputImage1, cv::Mat &inputImage2) {
    // First Check Image Sizes
    if (inputImage1.size != inputImage2.size) {
        std::cout << "Images not the same size." << std::endl;
        return true;
    } else {
        std::cout << "Images are the same size." << std::endl;
        return false;
    }
}


int main(int argc, char **argv) {

    String image1 = "snow.jpg";
    String image2 = "snow.jpg";

    // ./programName would be argv[0]
    if (argv[1] && argv[2]) {
        image1 = argv[1];
        image2 = argv[2];
    }

    cv::Mat inputImage1 = imread(image1, CV_LOAD_IMAGE_COLOR);
    cv::Mat inputImage2 = imread(image2, CV_LOAD_IMAGE_COLOR);
    cv::Mat outputImage; // output image to be set by comparison.

    // initial checks
    checkImageInDir(inputImage1, image1);
    checkImageInDir(inputImage2, image2); // check image exists
    checkSameSize(inputImage1, inputImage2); // check images same size

    // compare into output image
    cv::compare(inputImage1, inputImage2, outputImage, CMP_EQ);

    int totalPixels = outputImage.size().height * outputImage.size().width;
    int currentCorrectPixels = totalPixels;

    for (int i = 0; i < outputImage.size().height; i++ ) {
        for (int j = 0; j < outputImage.size().width; j++){
            int currentPixel = outputImage.at<uchar>(i,j);
            if (currentPixel != 255 ) {
                currentCorrectPixels = currentCorrectPixels - 1;
                //return 0;
            }
        }
    }
    std::cout << "Images Are " << (currentCorrectPixels/totalPixels)*100 << "% Identical" << std::endl;


    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Display window", outputImage );                   // Show our image inside it.

    waitKey(0); // do not close window until done viewing image

    return 0;
}