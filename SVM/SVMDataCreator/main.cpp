#include <opencv2/opencv.hpp>

#include <iostream>
#include <fstream>

int main(int argc, char** argv)
{
    if(argc < 4)
    {
        std::cerr << "Usage: " << argv[0] << std::endl;
        std::cerr << "[1] - video file location" << std::endl;
        std::cerr << "[2] - detector executable" << std::endl;
        std::cerr << "[3] - train/test file location" << std::endl;
        std::cerr << "[4] - number of frames to skip (optional)" << std::endl;
        return -1;
    }

    //open video file
    cv::VideoCapture videoCapture;
    videoCapture.open(argv[1]);

    //check video file
    if(!videoCapture.isOpened())
    {
        std::cerr << "Can't open video file." << std::endl;
        return -1;
    }

    //consts
    const std::string detectorProgram = argv[2];
    const std::string frameName = "frame.jpg";
    const std::string detectorOutput = detectorProgram + "_data";

    bool SKIP_FRAMES = false;
    int FRAMES_TO_SKIP = 0;
    if(argc == 5) {
        SKIP_FRAMES = true;
        FRAMES_TO_SKIP = atoi(argv[4]);
    }

    //open train or test file
    std::ofstream dataFile;
    dataFile.open(argv[3]);

    //read frames from the video file
    int count = 0;
    cv::Mat src;
    while(videoCapture.read(src))
    {
        if(!SKIP_FRAMES || (SKIP_FRAMES && count % FRAMES_TO_SKIP == 0))
        {
            //show the frame
            cv::imshow("frame", src);
            if(cv::waitKey(1000.f / videoCapture.get(CV_CAP_PROP_FPS)) >= 0)
                break;

            //save the frame
            cv::imwrite(frameName, src);

            //execute given detector: detector frame_location datafile_location
            const std::string detectorCommand = "./" + detectorProgram + " " + frameName + " " + detectorOutput;
            system(detectorCommand.c_str());

            //read detector output
            std::ifstream detectorOutputFile;
            detectorOutputFile.open(detectorOutput);

            std::string featurevector;
            if (detectorOutputFile.is_open())
            {
                getline(detectorOutputFile, featurevector);
                detectorOutputFile.close();
            }
            else
            {
                std::cerr << "Problem while reading detector output." << std::endl;
                return -1;
            }

            //positive or negative?
            std::cout << "computed feature vector: " << featurevector << std::endl;
            std::cout << "positive/negative? (enter 1 or -1)" << std::endl;
            std::cout << "input: ";
            int v;
            std::cin >> v;

            //feature vector with 1 or -1 instead of 0
            std::ostringstream newFeaturevector;
            newFeaturevector << v << " ";
            newFeaturevector << featurevector.substr(2);

            std::cout << "new feature vector: " << newFeaturevector.str() << std::endl;
            std::cout << std::endl;

            //write to data file
            dataFile << newFeaturevector.str() << std::endl;

            //cleanup for next frame
            remove(frameName.c_str());
            remove(detectorOutput.c_str());
        }

        ++count;
    }

    videoCapture.release();

    return 0;
}

