#include <opencv2/opencv.hpp>

#include <fstream>
#include <vector>

int main(int argc, char** argv) {

    //threshold values
    const int DX = 300, DY = 100;
    const int HOUGHLINESTHRESHOLD = 375;
    const int POSITIONTHRESHOLD = 5;
    const int TILEDIST = 75;
    const int TILEDISTTHRESHOLD = 15;

    //read image
    cv::Mat src = cv::imread(argv[1]);

    //transform image
    cv::Mat transformationMatrix = (cv::Mat_<float>(3, 3) << 1.942573224833244, 1.856642874874286, -660.9095655794609,
                                    -0.1277720821771055, 3.49452191344536, -74.85814843188734,
                                    -0.0001991185697340266, 0.003015718375164935, 1);

    cv::warpPerspective(src, src, transformationMatrix, src.size());

    //take region-of-interest
    cv::Mat roi(src, cv::Rect(DX, DY, src.cols - DX * 2, src.rows - DY * 2));

    //convert bgr to gray
    cv::Mat roiGray;
    cv::cvtColor(roi, roiGray, CV_BGR2GRAY);

    //blur, smooth, ...
    cv::GaussianBlur(roiGray, roiGray, cv::Size(3, 3), 0);
    cv::adaptiveThreshold(roiGray, roiGray, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 75, 2);

    //black becomes white, white becomes black
    cv::bitwise_not(roiGray, roiGray);

    //detect hough lines
    std::vector<cv::Vec2f> lines;
    cv::HoughLines(roiGray, lines, 1, CV_PI / 180, HOUGHLINESTHRESHOLD, 0, 0);

    //get the y-coordinate
    std::vector<int> positions;
    for(unsigned int i = 0; i < lines.size(); ++i) {
        float rho = lines[i][0], theta = lines[i][1];

        //detect almost horizontal lines only
        if((theta > 1.44f && theta < 1.69f)) {
            double b = std::sin(theta);
            double y = b * rho;

            positions.push_back(y);
        }
    }

    //calculate distance
    std::sort(positions.begin(), positions.end());

    std::vector<int> hDist;
    for(int i = 1; i < positions.size(); ++i) {
        for(int j = 0; j < i; ++j) {
            int d = positions[i] - positions[j];
            if(d > POSITIONTHRESHOLD && std::abs(TILEDIST - d) < TILEDISTTHRESHOLD) {
                hDist.push_back(d);
            }
        }
    }

    int dist = -1;
    if(!hDist.empty()) {
        int avgDist = 0;
        for(int i = 0; i < hDist.size(); ++i) {
            avgDist += hDist[i];
        }

        dist = avgDist / hDist.size();
    }

    //write out data to dataFile
    std::ofstream dataFile;
    dataFile.open(argv[2]);

    std::ostringstream featurevector;
    featurevector << 0 << " ";
    featurevector << 1 << ":" << dist;

    dataFile << featurevector.str();
    dataFile << std::endl;

    dataFile.close();

    return 0;
}
