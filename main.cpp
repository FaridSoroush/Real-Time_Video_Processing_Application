#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // Open the default video camera
    VideoCapture cap(0);

    // Check if the camera opened successfully
    if (!cap.isOpened()) {
        cout << "Error: Could not open camera" << endl;
        return -1;
    }

    Mat frame, grayFrame;

    while (true) {
        // Capture frame-by-frame
        cap >> frame;

        // If the frame is empty, break immediately
        if (frame.empty())
            break;

        // Convert captured frame to grayscale
        cvtColor(frame, grayFrame, COLOR_BGR2GRAY);

        // Display the resulting frame
        imshow("Grayscale Video", grayFrame);

        // Press 27 (ESC) to exit
        char c = (char)waitKey(25);
        if (c == 27)
            break;
    }

    // When everything done, release the video capture object
    cap.release();

    // Closes all the frames
    destroyAllWindows();

    return 0;
}
