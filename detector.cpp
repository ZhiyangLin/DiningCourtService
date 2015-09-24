#include "detector.h"

using namespace cv;
#ifdef DEBUG
  using namespace std;
#endif

Detector::Detector(int x, double threshL, double threshH) {
  #ifdef DEBUG
    cout << "Starting detector" << endl;
  #endif
  capture = raspiCamCvCreateCameraCapture(0); // Start the camera

  raspiCamCvSetCaptureProperty(capture, CV_CAP_PROP_EXPOSURE, 2);
  detectorX = x;
  thresholdLow = threshL;
  thresholdHigh = threshH;
  #ifdef DEBUG
    window_name = "RaspiCam Debug Window";
    frame_count = 0;
    time(&start_time);
    detect_count = 0;
  #endif
  raspiCamCvQueryFrame(capture); // Query for the garbage frame
  Detect(); // Begin detection
}

void Detector::Detect() {
  #ifdef DEBUG
    cout << "Detect() running" << endl;
  #endif
  bool canDetect = false;
  bool high = false;
  bool low = false;
  Mat frame; // Current frame
  Mat croppedFrame; // Cropped frame
  const int x = (270+20)/4;
  const int y = 0/2;
  const int width = /*40*/2/2;
  const int height = 480/2;
  Rect ROI(x, y, width, height); // Region of interest
  Mat fgMaskMOG; // fg mask generated by MOG method
  Mat bgMOG;
  Ptr<BackgroundSubtractor> pMOG; // MOG Background subtractor
  #ifdef MOG2
    pMOG = new BackgroundSubtractorMOG2(); // MOG2 approach
  #else
    pMOG = new BackgroundSubtractorMOG(); // MOG approach
  #endif
  IplImage * image = raspiCamCvQueryFrame(capture); // Get the captured frame
  frame = Mat(image, false);
  croppedFrame = frame(ROI);
  pMOG->operator()(croppedFrame, fgMaskMOG, 1); // Learn the first frame
  do {
    image = raspiCamCvQueryFrame(capture); // Get the captured frame
    frame = Mat(image, false); // Convert image captured by raspi camera to Mat for later analysis
    croppedFrame = frame(ROI); // Crop the captured frame (pointer based, does not copy data)
    //resize(croppedFrame, croppedFrame, Size(), 0.5, 0.5, INTER_LINEAR); // Resize the cropped frame (smaller frames will give higher FPS)
    pMOG->operator()(croppedFrame, fgMaskMOG, 0.001); // Update the background model
    double maskSum = sum(fgMaskMOG)[0];
    double average = maskSum / 255 / (width * height);
    low = (average < thresholdLow);
    high = (average > thresholdHigh);
    canDetect = canDetect || low; // Stays true until detect is counted, resets when under thresholdLow
    if (canDetect && high) {
      canDetect = false;
      detect_count += 1;
      // Send the count to the database
      cout << system("./send_count.sh");
      #ifdef DEBUG
        cout << "Detection! Total Detections: " << detect_count << endl;
      #endif
    }
    #ifdef DEBUG
      frame_count += 1; // Keep track of number of frames processed
      double percentage = average * 100;
      char percentage_str[20];
      sprintf(percentage_str, "%.2lf%%", percentage);
      putText(frame, percentage_str, cvPoint(10,20), FONT_HERSHEY_COMPLEX_SMALL, 0.80, cvScalar(255), 1, CV_AA);

      rectangle(frame, ROI, cvScalar(255));

      #ifdef VIDEO
        // Show live video in GUI for debugging
        imshow("frame", frame);
        imshow("fmMaskMog", fgMaskMOG);
        //imshow("croppedFrame", croppedFrame);
      #endif
    #endif
  } while (cvWaitKey(10) < 0); // Wait for any key press to exit
}

Detector::~Detector() {
  #ifdef DEBUG
    cout << "Detector done running" << endl;
    #ifdef VIDEO
      cvDestroyAllWindows(); // Destroy the display windows
    #endif
    printStats();
  #endif
  raspiCamCvReleaseCapture(&capture); // Turn off the camera
}

#ifdef DEBUG
  void Detector::printStats() {
    cout << "Detector Statistics:" << endl;
    time_t curr_time;
    time(&curr_time);
    double seconds = difftime(curr_time, start_time);
    double fps = frame_count / seconds;
    cout << fps << " fps" << endl;
    cout << detect_count << " detections" << endl; 
  }
#endif