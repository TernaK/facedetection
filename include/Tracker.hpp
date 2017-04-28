//
//  Tracker.hpp
//  kalman_tracker
//
//  Created by Terna Kpamber on 4/28/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#ifndef Tracker_hpp
#define Tracker_hpp

#include <opencv2/opencv.hpp>
#include <chrono>

// Convenient representation of time
typedef std::chrono::time_point<std::chrono::system_clock> ChronoTime;

// This struct is an interface to let some external process interact with the Tracker class
typedef struct Measurement {
  float data[4]; // hold measurement data: [x y width height]
  
  Measurement(float x, float y, float w = 0, float h = 0) {
    data[0] = x; data[1] = y; data[2] = w; data[3] = h;
  }
  
  // Create a string representation of an instance. Useful for cout.
  std::string toString(bool jusXY = true) {
    if(jusXY)
      return cv::format("[x: %.1f, y: %.1f]", data[0], data[1]);
    
    return cv::format("[x: %.1f, y: %.1f, w: %.1f, h: %.1f]", data[0], data[1], data[2], data[3]);
  }
  
  // Convert an instance to a cv::KalmanFilter style measurement Mat
  // justXY: if true, only use the fist two elements of Measurement.data
  cv::Mat toKalmanMeasurement(bool jusXY = true) {
    return cv::Mat((jusXY ? 2 : 4), 1, CV_32F, data);
  }
} Measurement;


// This class abstracts typical Kalman filter operations like prediction and correction.
// It initializes a filter and sets-up the transition, noise and erorr matrices.
// It also maintains a timer object
class Tracker {
private:
  ChronoTime timer;     // keep track of time
  int kfNumStates = 4;  // x y dx dy [w h dw dh]
  int kfNumMeas = 2;    // x y [w h]
  cv::KalmanFilter kf;  // the filter
  
public:
  // Provide an intial measurement
  Tracker(Measurement initial = Measurement(0,0,0,0), cv::Size frameSize = cv::Size(-1, -1));
  
  // Record the current time with the timer
  ChronoTime restartTimer();
  
  // Get the time difference sine the last time the timer was updated
  float getTimeDelta(ChronoTime atTime = std::chrono::system_clock::now());
  
  // Correct the filter state at the time of calling and update the timer
  void update(Measurement meas);
  
  // Predict the filter state at the time of calling and update the timer
  Measurement estimate();
};

#endif /* Tracker_hpp */
