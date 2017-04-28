//
//  Tracker.cpp
//  kalman_tracker
//
//  Created by Terna Kpamber on 4/28/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#include "Tracker.hpp"

using namespace std;

Tracker::Tracker(Measurement initial, cv::Size frameSize) {
  restartTimer();
  
  // create filter
  kf = cv::KalmanFilter(kfNumStates, kfNumMeas);
  
  cv::setIdentity(kf.transitionMatrix);
  cv::setIdentity(kf.measurementMatrix);
  cv::setIdentity(kf.processNoiseCov, 1E-2);
  cv::setIdentity(kf.measurementNoiseCov, 2.5);
  cv::setIdentity(kf.errorCovPre, 2.5);

  kf.statePost.at<float>(0) = initial.data[0];
  kf.statePost.at<float>(1) = initial.data[1];
}

ChronoTime Tracker::restartTimer() {
  timer = chrono::system_clock::now();
  return timer;
}

float Tracker::getTimeDelta(ChronoTime atTime) {
  chrono::duration<float> deltaSeconds = atTime - timer;
  return deltaSeconds.count();
}

void Tracker::update(Measurement meas) {
  
  ChronoTime now = chrono::system_clock::now();
  float dt = getTimeDelta(now);
  timer = now;
  
  // update transition matrix
  kf.transitionMatrix.at<float>(0, 2) = dt; //dx
  kf.transitionMatrix.at<float>(1, 3) = dt; //dx
  
  // update state
  kf.correct(meas.toKalmanMeasurement());
}

Measurement Tracker::estimate() {
  ChronoTime now = chrono::system_clock::now();
  float dt = getTimeDelta(now);
  timer = now;
  
  // update transition matrix
  kf.transitionMatrix.at<float>(0, 2) = dt; //dx
  kf.transitionMatrix.at<float>(1, 3) = dt; //dx
  
  cv::Mat state = kf.predict();
  
  return Measurement(state.at<float>(0), state.at<float>(1));
}
