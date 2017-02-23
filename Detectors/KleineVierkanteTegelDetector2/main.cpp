#include <opencv2/opencv.hpp>

#include <fstream>
#include <vector>

cv::Mat roi;
std::vector<int> horz, vert;
int min_horz, min_vert;

int get_min_dist(const std::vector<int>& values) {

    //thresholds
    const int MIN_LINE_DIST_THRESHOLD = 20;

    //calculate
    if (values.size() < 2) {
        return -1;
    }
    else {
        int min_dist = INT_MAX;
        for (int i = 0; i < values.size(); i++) {
            for (int j = i + 1; j < values.size(); j++) {
                int distance = std::abs(values[j] - values[i]);
                if (distance > MIN_LINE_DIST_THRESHOLD && distance < min_dist) {
                    min_dist = distance;
                }
            }
        }

        if (min_dist == INT_MAX) {
            return -1;
        } else {
            return min_dist;
        }
    }
}

void CannyThreshold(int, void*, bool isHorz) {

    //values
    int ratio = 3;
    int kernel_size = 3;
    int lowThreshold;

    if (isHorz) {
        lowThreshold = 45;
    } else {
        lowThreshold = 35;
    }

    cv::Mat detected_edges;

    //blur
    cv::GaussianBlur(roi, detected_edges, cv::Size(5, 5), 0, 0);

    //canny
    cv::Canny(detected_edges, detected_edges, lowThreshold, lowThreshold * ratio, kernel_size);

    //hough lines
    std::vector<cv::Vec2f> lines;
    cv::HoughLines(detected_edges, lines, 1, CV_PI / 180, 100, 0, 0);

    //check all lines
    for (int i = 0; i < lines.size(); i++) {
        float rho = lines[i][0], theta = lines[i][1];
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;

        // theta == dicht bij 0 ,pi of 2pi -> verticaal
        if (!isHorz && (abs(theta) < 0.3 || abs(theta - 3.14) < 0.3 || abs(theta - 6.28) < 0.3)) {
            vert.push_back(cvRound(x0));
        }
        // theta == dicht bij pi/2 of 3pi/2 -> horizontaal
        else if (isHorz && (abs(theta - 1.57) < 0.01 || abs(theta - 4.71) < 0.01)) {
            horz.push_back(cvRound(y0));
        }
    }

    if (isHorz) {
        min_horz = get_min_dist(horz);
    } else {
        min_vert = get_min_dist(vert);
    }
}

int main(int argc, char** argv) {

    //init
    horz.clear();
    vert.clear();

    //read image
    cv::Mat src = cv::imread(argv[1]);

    //transform image
    cv::Mat transformationMatrix = (cv::Mat_<float>(3, 3) << 1.942573224833244, 1.856642874874286, -660.9095655794609,
            -0.1277720821771055, 3.49452191344536, -74.85814843188734,
            -0.0001991185697340266, 0.003015718375164935, 1);


    cv::warpPerspective(src, src, transformationMatrix, src.size());

    //fix saturation
    cv::Mat saturation = cv::Mat::zeros(src.size(), src.type());
    /// Do the operation new_image(i,j) = alpha*image(i,j) + beta
    for (int y = 0; y < src.rows; y++) {
        for (int x = 0; x < src.cols; x++) {
            for (int c = 0; c < 3; c++) {
                saturation.at<cv::Vec3b>(y, x)[c] = cv::saturate_cast<unsigned char>(3 * (src.at<cv::Vec3b>(y, x)[c]) - 300);
            }
        }
    }

    //region-of-interest
    roi = cv::Mat(saturation, cv::Rect(src.cols / 3, src.rows / 2, src.cols / 2, src.rows / 3));

    //calculate min_hor distance and min_vert distance
    CannyThreshold(0, 0, true); //horz
    CannyThreshold(0, 0, false); //vert

    //feature vector
    std::ostringstream featurevector;
    featurevector << 0 << " ";
    featurevector << 1 << ":" << min_horz << " ";
    featurevector << 2 << ":" << min_vert;

    //write out data to dataFile
    std::ofstream dataFile;
    dataFile.open(argv[2]);

    dataFile << featurevector.str();
    dataFile << std::endl;

    dataFile.close();

    return 0;
}
