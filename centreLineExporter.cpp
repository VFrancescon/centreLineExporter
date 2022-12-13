#include "cameraGeneric.hpp"
#include <fstream>

int th_low = 50, th_high = 255;

int main(int argc, char* argv[]){
    Mat inputImg, procImg, inputCopy;
    
    std::ofstream outputFile;
    std::cout << "Usage:\n";
    std::cout << "ARG1: DEFAULT: NikitaSampleImg.png, image path otherwise\n";
    std::cout << "Calculates centreline and outputs its points as a csv with teh same name as the input file.";
    
    std::string inputPath;
    if(argc == 2){
        inputPath = argv[1];
    } else inputPath = "../NikitaSampleImg.png";
    inputImg = imread(inputPath);

    if(argc == 2){
        inputImg = imread(argv[1]);
    } else inputImg = imread("../NikitaSampleImg.png");
    inputCopy = inputImg;

    std::string outputPath = inputPath.substr(0, inputPath.size()-4) + ".csv";
    
    outputFile.open(outputPath);

    std::cout << "Input files:\n";
    std::cout << inputPath << "\n";
    std::cout << outputPath << "\n";


    outputFile << "Point Number, X-coordinate, Y-coordinate\n";



    Mat inputMask = imread("../NikitaMask.png");
    cvtColor(inputMask, inputMask, CV_8UC1);
    bitwise_not(inputMask, inputMask);

    cvtColor(inputImg, procImg, COLOR_BGR2GRAY);
    blur(procImg, procImg, Size(5,5));
    threshold(procImg, inputImg, th_low, th_high, THRESH_BINARY_INV);
    dilate(inputImg, inputImg, Mat(), Point(-1,-1), 10);
    cvtColor(inputImg, inputImg, CV_8UC1);
    inputImg.copyTo(procImg, inputMask);


    cvtColor(procImg,procImg, COLOR_BGR2GRAY);
    std::vector<std::vector<Point> > contours;
    std::vector<Vec4i> hierarchy;
    findContours(procImg, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);

    Mat skeleton = Mat::zeros(procImg.rows, procImg.cols, CV_8UC1);
    ximgproc::thinning(procImg, skeleton, 0);

    std::vector<Point> cntLine;
    findNonZero(skeleton, cntLine);
    // std::reverse(cntLine.begin(), cntLine.end());


    int k = 0;
    for(auto i: cntLine){
        outputFile << k << "," << i.x << "," << i.y << "\n";
        k++;
    }
    // imwrite("output.png", inputImg);
    // imshow("Processed", inputCopy);
    // imshow("Skelly", skeleton);
    // char c= (char)waitKey(0);
    
    outputFile.close();

    return 0;
}