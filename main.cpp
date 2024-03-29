#include <opencv2/opencv.hpp>
#include <iostream>
///*real time image processing*/
using namespace cv;
using namespace std;

void applySepia(Mat &input, Mat &output) {
    Mat sepiaKernel = (Mat_<float>(3,3) <<
                        0.272, 0.534, 0.131,
                        0.349, 0.686, 0.168,
                        0.393, 0.769, 0.189);
    transform(input, output, sepiaKernel);
}

void applyEdges(Mat &input, Mat &output) {
    Mat gray;
    cvtColor(input, gray, COLOR_BGR2GRAY);
    Canny(gray, output, 100, 200);
    cvtColor(output, output, COLOR_GRAY2BGR);
}

void applyBlur(Mat &input, Mat &output) {
    int kernelSize = 101;
    if (kernelSize % 2 == 0) kernelSize++;
    if (kernelSize <= 0) kernelSize = 1;
    
    GaussianBlur(input, output, Size(kernelSize, kernelSize), 0, 0);
}

void showHistogram(const Mat& img) {
    int bins = 256;
    int histSize[] = {bins};
    float lranges[] = {0, 256};
    const float* ranges[] = {lranges};
    Mat hist;
    int channels[] = {0};

    calcHist(&img, 1, channels, Mat(), hist, 1, histSize, ranges, true, false);
    double maxVal = 0;
    minMaxLoc(hist, 0, &maxVal);

    int scale = 2;
    Mat histImg = Mat::zeros(bins*scale, bins, CV_8UC3);

    for (int i = 0; i < bins; i++) {
        float binVal = hist.at<float>(i);
        int intensity = cvRound(binVal * bins / maxVal);
        rectangle(histImg, Point(i*scale, bins-1), Point((i+1)*scale - 1, bins - intensity),
                  Scalar(255, 255, 255), FILLED);
    }

    imshow("Histogram", histImg);
}

int main() {
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cout << "Error: Could not open camera" << endl;
        return -1;
    }

    CascadeClassifier faceCascade;
    if (!faceCascade.load("haarcascade_frontalface_default.xml")) {
        cout << "Error loading face cascade. Exiting!" << endl;
        return -1;
    }

    Mat frame;
    char filter = '0'; // Default to no filter
    bool isRecording = false;
    VideoWriter videoWriter;

    cout << "Press '1' for Grayscale, '2' for Sepia, '3' for Edge Detection, '4' for Blur, 'r' to start/stop recording, 's' to save snapshot, and '0' to remove filters.\n";

    while (true) {
        cap >> frame;
        if (frame.empty()) break;

        Mat processedFrame = frame.clone();

        switch(filter) {
            case '1':
                cvtColor(frame, processedFrame, COLOR_BGR2GRAY);
                cvtColor(processedFrame, processedFrame, COLOR_GRAY2BGR);
                break;
            case '2':
                applySepia(frame, processedFrame);
                break;
            case '3':
                applyEdges(frame, processedFrame);
                break;
            case '4':
                applyBlur(frame, processedFrame);
                break;
        }

        vector<Rect> faces;
        Mat grayFrame;
        cvtColor(processedFrame, grayFrame, COLOR_BGR2GRAY);
        equalizeHist(grayFrame, grayFrame);
        faceCascade.detectMultiScale(grayFrame, faces);
        for (const Rect &face : faces) {
            rectangle(processedFrame, face, Scalar(0, 255, 0), 2);
        }

        Mat grayFrameForHist;
        if (filter == '1') {
            grayFrameForHist = processedFrame.clone();
        } else {
            cvtColor(processedFrame, grayFrameForHist, COLOR_BGR2GRAY);
        }
        showHistogram(grayFrameForHist);

        imshow("Video Feed", processedFrame);

        // Recording video
        if (isRecording) {
            videoWriter.write(processedFrame);
        }

        char key = (char)waitKey(30);
        if (key == 27) break; // ESC key to exit
        else if (key >= '0' && key <= '4')
            filter = key;
        else if (key == 'r' || key == 'R') {
            if (isRecording) {
                videoWriter.release();
                cout << "Stopped recording." << endl;
            } else {
                string filename = "recording_" + to_string(time(0)) + ".avi";
                int codec = VideoWriter::fourcc('M', 'J', 'P', 'G');
                videoWriter.open(filename, codec, 10, processedFrame.size(), true);
                if (!videoWriter.isOpened()) {
                    cout << "Could not open the output video file for write\n";
                    return -1;
                }
                cout << "Started recording to " << filename << endl;
            }
            isRecording = !isRecording;
        }
        else if (key == 's' || key == 'S') {
            string filename = "snapshot_" + to_string(time(0)) + ".png";
            imwrite(filename, processedFrame);
            cout << "Saved snapshot: " << filename << endl;
        }
    }

    if (isRecording) {
        videoWriter.release();
    }

    cap.release();
    destroyAllWindows();

    return 0;
}
