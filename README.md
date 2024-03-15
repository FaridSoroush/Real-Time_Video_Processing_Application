# Real-Time Video Processing Application

This project is a demonstration of real-time video processing using OpenCV in C++. It captures video from the webcam, applies various filters, detects faces, shows live histograms, takes snapshots, and records video.

## Features

- **Real-Time Video Capture**: Captures video stream from the webcam.
- **Filter Application**: Apply different filters to the video stream in real-time:
  - Grayscale
  - Sepia
  - Edge Detection
  - Blur
- **Face Detection**: Detects and highlights faces in the video stream.
- **Live Histogram**: Displays a live histogram of the grayscale video feed.
- **Snapshot Feature**: Allows taking snapshots of the current video frame and saves them to disk.
- **Video Recording**: Start and stop recording the processed video feed at any time, saving creations to a file.

## How to Run

To run this application, you will need to have OpenCV installed on your system. This project is developed and tested with OpenCV 4.9.0, but it should work with other compatible versions.

1. **Clone the Repository**

   ```bash
   git clone <repository-url>
   cd <repository-name>
   ```
   
2. **Compile the Application**

Make sure g++ and pkg-config are installed on your system. Then compile the application using the following command:

   ```bash
   g++ main.cpp -o output `pkg-config --cflags --libs opencv4`
   ```

3. **Run the Application**

After compilation, you can run the application by executing:

   ```bash
   ./output
   ```

## Controls

- Press `1` to apply the Grayscale filter.
- Press `2` for the Sepia effect.
- Press `3` for Edge Detection.
- Press `4` to apply Blur.
- Press `s` to take a snapshot. The snapshot will be saved in the current directory.
- Press `r` to start/stop video recording. The video will be saved in the current directory.
- Press `ESC` to exit the application.

## System Requirements

- **Operating System**: Linux, macOS, or Windows
- **Compiler**: GCC or any compatible C++ compiler that supports C++11.
- **OpenCV Version**: 4.x (Developed and tested with 4.9.0)

## Acknowledgments

This application was developed using OpenCV, an open-source computer vision and machine learning software library.

## License

This project is open source and available under the MIT License.


  
 
