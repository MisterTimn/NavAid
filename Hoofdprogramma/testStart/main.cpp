/* 
 * File:   main.cpp
 * Author: g
 *
 * Created on May 15, 2014, 11:35 AM
 */

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <queue>


using namespace std;
using namespace cv;

struct Location {
    vector<string> trainFiles;
    vector<string> programNames;
    string locationName;
    // evt.. directions
};
vector<Location> locations(5);
int currentLocation;
bool revrse;
int learncount = 0;
int hogentStemmen = 0;
int stationStemmen = 0;
int volgendeStemmen = 0;
int huidigeStemmen = 0;
queue<bool> huidigOfVolgend;


template <typename T>
std::string to_string(T const& value) {
    stringstream sstr;
    sstr << value;
    return sstr.str();
}


double useSVM(const string & trainingFile, const string & testDataFile, const string & resultFile) {
    const string command = "./svm_perf_classify " + testDataFile + " " + trainingFile + " " + resultFile + " > /dev/null";
    system(command.c_str());
    ifstream myfile;
    myfile.open(resultFile.c_str());
    string line;
    if (myfile.is_open()) {
        //while (getline(myfile, line)) {
        getline(myfile, line);
        //cout << line << '\n';
        myfile.close();
        return atof(line.c_str());
        //}
    } else {
        //cout << "Could not open: " + resultFile;
        return 0;
    }
}

void callFeatureDetection(const string & programName, const string & imagePath, const string & outputFile) {
    const string command = "./" + programName + " " + imagePath + " " + outputFile + " > /dev/null";
    system(command.c_str());
}

void mainFunction(Mat & src) {

    const string photoName = "testImage.jpg";
    // save image to file so other programs can open it... 
    imwrite(photoName, src);

    //namedWindow("pic");
    //imshow("pic", src);
    //if (waitKey(1000.0 / video.get(CV_CAP_PROP_FPS)) >= 0) {
    //    break;
    //}
    if (learncount < 5) {
        // learning mode... try to detect if position is Sint Pieters station or Hogent
        callFeatureDetection(locations[0].programNames[0], photoName, locations[0].programNames[0] + ".testdata");
        double sterkteStation = useSVM(locations[0].trainFiles[0], locations[0].programNames[0] + ".testdata", "result" + locations[0].programNames[0]);
        cout << locations[3].programNames[1] << endl;
        callFeatureDetection(locations[3].programNames[1], photoName, locations[3].programNames[1] + ".testdata");
        double sterkteHogent = useSVM(locations[3].trainFiles[1], locations[3].programNames[1] + ".testdata", "result" + locations[3].programNames[1]);

        if (sterkteHogent > sterkteStation) {
            hogentStemmen++;
        } else {
            stationStemmen++;
        }

        // vote huidige
        huidigOfVolgend.push(true);
        huidigeStemmen++;
        
        learncount++;
        if (learncount == 5) {
            if (hogentStemmen > stationStemmen) {
                // we are going from the university to the station
                currentLocation = 4;
                revrse = true;
            } else {
                // we are going from the station to the university
                currentLocation = 0;
                revrse = false;
            }
        }
    } else {
        //double huidigeSterkste = 0;
        //double volgendeSterkste = 0;
        int aantalHuidigeStemmen = 0;
        int totaalHuidig = 0;
        int aantalVolgendeStemmen = 0;
        int totaalVolgend = 0;
        if (revrse) {
            for (int i = currentLocation; i >= currentLocation - 1; i--) {
                for (int j = 0; j < locations[i].programNames.size(); j++) {
                    callFeatureDetection(locations[i].programNames[j], photoName, locations[i].programNames[j] + ".testdata");
                    //cout << "Sterkte van " << locations[i].programNames[j] << endl;
                    double sterkte = useSVM(locations[i].trainFiles[j], locations[i].programNames[j] + ".testdata", "result" + locations[i].programNames[j]);
                    if (sterkte > 0.5) {
                        //    cout << "true!";
                    } else if (sterkte < -0.5) {
                        //    cout << "false! ";
                    } else {
                        //   cout << "unsure...";
                    }
                    if (i == currentLocation) { //&& huidigeSterkste < sterkte) {
                        //huidigeSterkste = sterkte;
                        if (sterkte > 0) {
                            aantalHuidigeStemmen++;
                        }
                        totaalHuidig++;
                    } else if (i != currentLocation) {// && volgendeSterkste < sterkte) {
                        //volgendeSterkste = sterkte;
                        if (sterkte > 0) {
                            aantalVolgendeStemmen++;
                        }
                        totaalVolgend++;
                    }
                }
            }
        } else {
            for (int i = currentLocation; i <= currentLocation + 1; i++) {
                for (int j = 0; j < locations[i].programNames.size(); j++) {
                    callFeatureDetection(locations[i].programNames[j], photoName, locations[i].programNames[j] + ".testdata");
                    //cout << "Sterkte van " << locations[i].programNames[j] << endl;
                    double sterkte = useSVM(locations[i].trainFiles[j], locations[i].programNames[j] + ".testdata", "result" + locations[i].programNames[j]);
                    if (sterkte > 0.5) {
                        //  cout << "true!";
                    } else if (sterkte < -0.5) {
                        //  cout << "false! ";
                    } else {
                        //  cout << "unsure...";
                    }
                    if (i == currentLocation) { //&& huidigeSterkste < sterkte) {
                        //huidigeSterkste = sterkte;
                        if (sterkte > 0) {
                            aantalHuidigeStemmen++;
                        }
                        totaalHuidig++;
                    } else if (i != currentLocation) {// && volgendeSterkste < sterkte) {
                        //volgendeSterkste = sterkte;
                        if (sterkte > 0) {
                            aantalVolgendeStemmen++;
                        }
                        totaalVolgend++;
                    }
                }
            }
        }

        
        /// compare both values
        //if (huidigeSterkste >= volgendeSterkste) {
        double dummy = 1.0;
        
        
        double h = dummy * aantalHuidigeStemmen / totaalHuidig;
        double v= dummy  * aantalVolgendeStemmen / totaalVolgend;
        if(totaalHuidig == 0  ){
            h=0.1;
        } else if(totaalVolgend==0){
            v=0.1;
        }
        if (h > v) {
            // vote huidige
            huidigOfVolgend.push(true);
            huidigeStemmen++;
            //cout<< "Stem voor huidige ";
        } else if(h < v) {
            // vote volgende
            huidigOfVolgend.push(false);
            volgendeStemmen++;
            
            //cout<< "Stem voor volgende ";
        } 
        //cout<< "ratio " << h << " tegen " << v<<endl;
        //cout << "Huidige zoone: " + locations[currentLocation].locationName << endl;
        // check size and vote balance
        //cout<< "Size: " << huidigOfVolgend.size()<<endl;
        //cout<< "Sterkte huidig: " << huidigeSterkste << " , volgende sterkte: " << volgendeSterkste <<endl;
        if (huidigOfVolgend.size() == 10) {
            // remove a value from the queue
            if (huidigOfVolgend.front()) {
                // remove huidige
                huidigeStemmen--;
            } else {
                volgendeStemmen--;
            }
            huidigOfVolgend.pop();

            // COMPARE huidigeStemmen and volgendeStemmen
            if (volgendeStemmen > huidigeStemmen) {
                // move to next sector
                while (!huidigOfVolgend.empty()) {
                    huidigOfVolgend.pop();
                }
                huidigeStemmen = 0;
                volgendeStemmen = 0;
                for(int i=0;i<9;i++){
                    huidigeStemmen++;
                    huidigOfVolgend.push(true);
                }
                if (revrse) {
                    currentLocation--;
                } else {
                    currentLocation++;
                }
                cout << "Location changed to " << locations[currentLocation].locationName;
                cout << endl;
            }
        }



    }
    //    namedWindow("test");
    //    imshow("test", src);
    //    waitKey(0);
    //const string trainingFile = "model";
    //const string testDataFile = "train_goood.dat";
    //const string resultFile = "predictions";
    //    double sterkte = useSVM(trainingFile, testDataFile, resultFile);
    //    if (sterkte > 0.5) {
    //        cout << "true!";
    //    } else if (sterkte < -0.5) {
    //        cout << "false! ";
    //    } else {
    //        cout << "unsure...";
    //    }
}

void initialiseParameters() {

    Location loc1;
    loc1.locationName = "Betonpad aan station.";
    loc1.programNames.push_back("BetonDetector");
    for (int i = 0; i < loc1.programNames.size(); i++) {
        loc1.trainFiles.push_back("model" + loc1.programNames[i]);
    }
    Location loc2;
    loc2.locationName = "Tegelstructuren tussen station en oprit.";
    loc2.programNames.push_back("SmalleTegelDetector");
    loc2.programNames.push_back("VoetpadTegelDetector1");
    for (int i = 0; i < loc2.programNames.size(); i++) {
        loc2.trainFiles.push_back("model" + loc2.programNames[i]);
    }
    Location loc3;
    loc3.programNames.push_back("KleineVierkanteTegelDetector1");
    loc3.programNames.push_back("KleineVierkanteTegelDetector1");
    loc3.locationName = "Tegelstructuur tussen oprit en sportgebouw.";
    loc3.programNames.push_back("GrasDetector");
    loc3.programNames.push_back("VoetpadTegelDetector1");
    for (int i = 0; i < loc3.programNames.size(); i++) {
        loc3.trainFiles.push_back("model" + loc3.programNames[i]);
    }
    Location loc4;
    loc4.locationName = "Tegelstructuur en gras naast het sportgebouw.";
    loc4.programNames.push_back("GroteVierkanteTegelDetector");
    loc4.programNames.push_back("GrasDetector");
    for (int i = 0; i < loc4.programNames.size(); i++) {
        loc4.trainFiles.push_back("model" + loc4.programNames[i]);
    }
    Location loc5;
    loc5.locationName = "asfalt tussen sporthal en p-gebouw.";
    for (int i = 0; i < loc5.programNames.size(); i++) {
        loc5.trainFiles.push_back("model" + loc5.programNames[i]);
    }
    // add programnames and trainingFileNames
    locations[0] = loc1;
    locations[1] = loc2;
    locations[2] = loc3;
    locations[3] = loc4;
    locations[4] = loc5;
}

/*
 * 
 */
int main(int argc, char** argv) {
    //system("./svm_perf_learn -c 20 -l 2 /home/g/Downloads/predictions.dat model");

    
    string videoPath = "/home/g/Downloads/20140305_h_10fps.avi";//argv[1];//"/home/g/Downloads/20140305_h_10fps.avi"; //20140226_h_10fps.avi"
    int frameskip = 23;//atoi(argv[2]);
    initialiseParameters();

    int count = 0;
    VideoCapture video(videoPath);
    Mat src;
    if (video.isOpened()) {
        while (video.read(src)) {
            if (count % frameskip == 0) {
                namedWindow("image");
                imshow("image", src);

                mainFunction(src);
                waitKey(0);

            }
            count++;
        }
    }
    return 0;
}

