#include <opencv2/opencv.hpp>

#include <iostream>
#include <fstream>
#include <vector>

std::vector<int> lijnen_horiz, lijnen_vert;

void warpImageHorizontal(cv::Mat& src) {
    cv::Mat transformationMatrix = (cv::Mat_<float>(3, 3) <<
                                3.733014315042774, 2.061886322652256, -1301.047963484205,
                                0.5998443499574854, 5.106979153562959, -1243.185106309681,
                                0.0007714899807180572, 0.003564067611158272, 1);

    cv::warpPerspective(src, src, transformationMatrix, src.size());

    transformationMatrix = (cv::Mat_<float>(3, 3) <<
                                1.046267773340949, 0.1727104311502497, -51.12582022694622,
                                -0.01835162322403518, 1.084371194493872, 5.046643148189599,
                                -3.762685450448503e-05, 0.0002480289139232891, 1);

    cv::warpPerspective(src, src, transformationMatrix, src.size());
}

cv::Mat selectRoi(const cv::Mat& src) {
    int x1 = 0;
    int y1 = 20;
    int width = (3 * src.cols) / 4;
    int height = (3 * src.rows) / 4;

    cv::Rect roi_rect(x1, y1, width, height);

    return cv::Mat(src, roi_rect);
}

void verwerkLijnen(float rho, float theta, bool isHoriz) {
    double a = cos(theta), b = sin(theta);
    double x0 = a*rho, y0 = b*rho;
    if(isHoriz){
        lijnen_horiz.push_back(cvRound(y0));
    }
    else {
        lijnen_vert.push_back(cvRound(x0));
    }
}

//Zoekt de verticale lijnen tussen de tegels naast de sporthal (warpImage ideaal hiervoor ingesteld)
void zoekLijnen(cv::Mat& roi) {

    const float GRAAD = CV_PI / 180;
    const int LOW_THRESH_VERT = 40;
    const int CANNY_RATIO = 3;
    const int KERNEL_SIZE = 3;

    //Canny
    cv::Mat edges;
    cv::GaussianBlur(roi, edges, cv::Size(5, 5), 5, 20);
    cv::cvtColor(edges, edges, CV_BGR2GRAY);
    cv::Canny(edges, edges, LOW_THRESH_VERT, LOW_THRESH_VERT * CANNY_RATIO, KERNEL_SIZE);

    // Hough Line Detection
    std::vector<cv::Vec2f> lines;
    HoughLines(edges, lines, 1, GRAAD, 100, 200, 10);

    //Alle gededecteerde lijnen zitten in lines
    for(unsigned int i = 0; i < lines.size(); i++) {

        //Toepassen van driehoeksmeetkunde om x en y te vinden van de eindpunten van de lijnen
        float rho=lines[i][0];
        float theta=lines[i][1];

        //selectie verticale lijnen
        if(theta > GRAAD * 170 || theta < GRAAD * 10) {
            verwerkLijnen(rho, theta, false);
        }
        //selectie horizontale lijnen
        else if(theta > GRAAD * 80 && theta < GRAAD * 100) {
            verwerkLijnen(rho, theta, true);
        }
    }
}

int get_min_dist(const std::vector<int>& values) {

    const int DIST_THRESHOLD = 100;

    if (values.size() < 2) {
        return -1;
    }
    else {
        int min_dist = 500;
        for (int i = 0; i < values.size(); i++) {
            for (int j = i + 1; j < values.size(); j++) {
                int distance = std::abs(values[j] - values[i]);
                if (distance > DIST_THRESHOLD && distance < min_dist) {
                    min_dist = distance;
                }
            }
        }

        if (min_dist == 500) {
            return -1;
        } else {
            return min_dist;
        }
    }
}

int main(int argc, char** argv) {

    //read image
    cv::Mat src = cv::imread(argv[1]);

    //init
    lijnen_horiz.clear();
    lijnen_vert.clear();

    //transform image
    warpImageHorizontal(src);

    //roi
    cv::Mat roi = selectRoi(src);

    //find lines
    zoekLijnen(roi);

    //get distance
    int min_horiz = get_min_dist(lijnen_horiz);
    int min_vert = get_min_dist(lijnen_vert);

    //feature vector
    std::ostringstream featurevector;
    featurevector << 0 << " ";
    featurevector << 1 << ":" << min_horiz << " ";
    featurevector << 2 << ":" << min_vert;

    //write out data to dataFile
    std::ofstream dataFile;
    dataFile.open(argv[2]);

    dataFile << featurevector.str();
    dataFile << std::endl;

    dataFile.close();

    return 0;
}

