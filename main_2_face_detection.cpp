#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// Function to apply the sepia effect
void applySepia(Mat &input, Mat &output) {
    Mat sepiaKernel = (Mat_<float>(3,3) <<
                        0.272, 0.534, 0.131,
                        0.349, 0.686, 0.168,
                        0.393, 0.769, 0.189);
    transform(input, output, sepiaKernel);
}

// Function to apply edge detection
void applyEdges(Mat &input, Mat &output) {
    Mat gray;
    cvtColor(input, gray, COLOR_BGR2GRAY);
    Canny(gray, output, 100, 200);
    cvtColor(output, output, COLOR_GRAY2BGR); // Convert back to BGR for consistent output format
}

// Function to apply blur effect
void applyBlur(Mat &input, Mat &output) {

    int kernelSize = 101; 
    GaussianBlur(input, output, Size(kernelSize, kernelSize), 0, 0);
}

int main() {
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cout << "Error: Could not open camera" << endl;
        return -1;
    }

    // Load the Haar Cascade for face detection
    CascadeClassifier faceCascade;
    if (!faceCascade.load("haarcascade_frontalface_default.xml")) {
        cout << "Error loading face cascade. Exiting!" << endl;
        return -1;
    }

    Mat frame;
    char filter = '0'; // Default to no filter

    cout << "Press '1' for Grayscale, '2' for Sepia, '3' for Edge Detection, '4' for Blur, and '0' to remove filters.\n";

    while (true) {
        cap >> frame;
        if (frame.empty())
            break;

        Mat processedFrame = frame.clone();

        switch(filter) {
            case '1': // Grayscale
                cvtColor(frame, processedFrame, COLOR_BGR2GRAY);
                cvtColor(processedFrame, processedFrame, COLOR_GRAY2BGR); // Convert back to BGR for consistent output format
                break;
            case '2': // Sepia
                applySepia(frame, processedFrame);
                break;
            case '3': // Edge Detection
                applyEdges(frame, processedFrame);
                break;
            case '4': // Blur
                applyBlur(frame, processedFrame);
                break;
        }

        // Convert to grayscale for face detection
        Mat grayFrame;
        cvtColor(processedFrame, grayFrame, COLOR_BGR2GRAY);
        equalizeHist(grayFrame, grayFrame);

        // Detect faces
        vector<Rect> faces;
        faceCascade.detectMultiScale(grayFrame, faces);

        // Draw rectangles around detected faces
        for (const Rect &face : faces) {
            rectangle(processedFrame, face, Scalar(0, 255, 0), 2);
        }

        imshow("Video Feed", processedFrame);

        char key = (char) waitKey(30);
        if (key == 27) // ESC key to exit
            break;
        else if (key >= '0' && key <= '4')
            filter = key;
    }

    cap.release();
    destroyAllWindows();

    return 0;
}
