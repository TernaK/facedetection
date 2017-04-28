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
  rectangle(image, tl - Point(50,50), br + Point(50,50), color, 2);
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

  int freq = 5;
  long timeout = 0;
  Size lastFaceSize;
  Point lastFaceCenter;

  for(;;) {
    Mat frame;
    vCap >> frame;
    fd.detectFaces(frame, faces);
    bool faceDetected = faces.size() > 0;

    if(!faces.empty()) {
      // fd.drawFaceRectInImage(faces[0], frame, Scalar(255,255,0), true, "#"+to_string(0));
      Measurement meas = Measurement(faces[0].center.first, faces[0].center.second);

      if(!startTracking) {
        startTracking = true;
        tracker = new Tracker(meas);
        lastFaceSize = Size(faces[0].width, faces[0].height);
        lastFaceCenter = Point(faces[0].center.first, faces[0].center.second);
      }
      else {
        if(timeout >= freq) {
          tracker->update(meas);
          timeout = 0;
          lastFaceSize = Size(faces[0].width, faces[0].height);
          lastFaceCenter = Point(faces[0].center.first, faces[0].center.second);
        }
      }
    }

    if(startTracking) {
      Measurement predicted = tracker->estimate();
      if(faceDetected)
        DrawBoxInImage(lastFaceCenter, lastFaceSize, frame, Scalar(0,255,0));
      else
        DrawBoxInImage(Point(predicted.data[0], predicted.data[1]), lastFaceSize, frame, Scalar(0,0,255));
    }
    faces.clear();
    imshow("faces", frame);
    if(waitKey(10) == 27) break;

    timeout++;
  }

  if(tracker != nullptr) {
    delete tracker;
  }
}