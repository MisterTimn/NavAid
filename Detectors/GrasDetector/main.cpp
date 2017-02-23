#include <opencv2/opencv.hpp>

#include <fstream>
#include <vector>

int main(int argc, char** argv) {

    //thresholds
    const int WHITEPIXELSNEEDED = 20000;

    //read image
    cv::Mat image = cv::imread(argv[1]);

    //equalize image
    cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();

    cv::Mat imageEqualized;
    std::vector<cv::Mat> imageChannels;
    cv::cvtColor(image, imageEqualized, CV_BGR2YCrCb);
    cv::split(imageEqualized, imageChannels);
    clahe->apply(imageChannels[0], imageChannels[0]);
    cv::merge(imageChannels, imageEqualized);
    cv::cvtColor(imageEqualized, imageEqualized, CV_YCrCb2BGR);

    //convert bgr to hsv
    cv::Mat imageHsv;
    cvtColor(imageEqualized, imageHsv, CV_BGR2HSV);

    //find green-like pixels
    cv::Mat imageGreenMask;
    cv::inRange(imageHsv, cv::Scalar(40, 20, 20), cv::Scalar(90, 255, 255), imageGreenMask);

    //two region-of-interest: left, right
    cv::Rect roiLeft(0, 0, image.cols / 3, image.rows);
    cv::Rect roiRight(2 * image.cols / 3, 0, image.cols / 3, image.rows);

    //count white (green) pixels
    int countLeft = cv::countNonZero(imageGreenMask(roiLeft));
    int countRight = cv::countNonZero(imageGreenMask(roiRight));

    //values for feature vector
    int value1 = -1, value2 = -1;
    if(countLeft > WHITEPIXELSNEEDED) {
        value1 = countLeft;
    }

    if(countRight > WHITEPIXELSNEEDED) {
        value2 = countRight;
    }

    //write data to dataFile
    std::ofstream dataFile;
    dataFile.open(argv[2]);

    std::ostringstream featurevector;
    featurevector << 0 << " ";
    featurevector << 1 << ":" << value1 << " ";
    featurevector << 2 << ":" << value2;

    dataFile << featurevector.str();
    dataFile << std::endl;

    dataFile.close();

    return 0;
}
