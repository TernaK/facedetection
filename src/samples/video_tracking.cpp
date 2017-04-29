/* description
  Run the face detector on an input image provided on the command line
*/

#include "Tracker.hpp"
#include "facedetector.hpp"
using namespace cv;
using namespace std;
using namespace tkcv;

void DrawBoxInImage(Point center, Size size, cv::Mat& image, cv::Scalar color=cv::Scalar(255,255,0)) {
  Point tl = Point(center.x-size.width/2, center.y-size.height/2);
  Point br = tl + Point(size.width, size.height);
  rectangle(image, tl - Point(150,80), br + Point(150,80), color, 2);
}

int main(int argc, char *argv[]){

  // std::chrono::time_point<std::chrono::system_clock> start, end;

  Tracker *tracker = nullptr;
  bool startTracking = false;

  std::vector<Face> faces;
  FaceDetector fd;

  VideoCapture vCap(0);
  vCap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
  vCap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
  namedWindow("faces");

  int minTimeout = 6;
  long timeout = 0;
  Size lastFaceSize;
  Point lastFaceCenter;

  ChronoTime lastDetectionTime;// = chrono::system_clock::now();

  for(;;) {
    Mat frame;
    vCap >> frame;
    cv::flip(frame, frame, 1);
    fd.detectFaces(frame, faces);
    bool faceDetected = faces.size() > 0;

    if(!faces.empty()) {
      lastDetectionTime = chrono::system_clock::now();
      // fd.drawFaceRectInImage(faces[0], frame, Scalar(255,255,0), true, "#"+to_string(0));
      Measurement meas = Measurement(faces[0].center.first, faces[0].center.second);

      if(!startTracking) {
        startTracking = true;
        tracker = new Tracker(meas);
        lastFaceSize = Size(faces[0].width, faces[0].height);
        lastFaceCenter = Point(faces[0].center.first, faces[0].center.second);
      }
      else {
        if(timeout >= minTimeout) {
          tracker->update(meas);
          timeout = 0;
          lastFaceSize = Size(faces[0].width, faces[0].height);
          lastFaceCenter = Point(faces[0].center.first, faces[0].center.second);
        }
      }
    }

    if(startTracking) {
      // keep estimating the face location
      Measurement predicted = tracker->estimate();

      chrono::duration<float> sinceDetection = chrono::system_clock::now() - lastDetectionTime;
      if(sinceDetection.count() < 0.5) 
        DrawBoxInImage(Point(predicted.data[0], predicted.data[1]), lastFaceSize, frame, Scalar(0,0,255));
      else {
        delete tracker;
        tracker = nullptr;
        startTracking = false;
      }
    }

    faces.clear();
    imshow("faces", frame);
    if(waitKey(30) == 27) break;

    timeout++;
  }

  if(tracker != nullptr) {
    delete tracker;
  }
}