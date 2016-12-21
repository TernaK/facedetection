#include "facedetector.hpp"
using namespace std;
using namespace cv;
using namespace tkcv;

FaceDetector::FaceDetector(){
  string folder = SUPPORT_PATH;
  cascadeFilePath = folder + "haarcascade_frontalface_alt.xml";
  if(!faceCascade.load(cascadeFilePath)){
    cout << "Could not load classifier file!\n";
    exit(-1);
  }

}


void FaceDetector::detectFaces(const cv::Mat& image, std::vector<Face>& faces){
  //get gray
  assert(image.type() == CV_8UC3 || image.type() == CV_8U);
  Mat gray;
  if(image.type() == CV_8UC3)
    cvtColor(image, gray, CV_BGR2GRAY);
  else
    gray = image.clone();

  //detect
  std::vector<Rect> detections;
  faceCascade.detectMultiScale( gray, detections, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(50, 50));

  //convert detections Rect to Face
  for(auto detection: detections){
    cv::Point centerPoint =  (detection.tl() + detection.br()) / 2;
    pair<unsigned,unsigned> center = make_pair(centerPoint.x, centerPoint.y);
    faces.push_back(Face(center, detection.size().height, detection.size().width));
  }

}


void FaceDetector::drawFaceRectInImage(const Face& face, cv::Mat& image, cv::Scalar color, bool annotate, std::string annotateValue){
  //circle(image, cv::Point(face.center.first, face.center.second), (face.height+face.width)/2, Scalar(255,255,0));
  Point tl = Point(face.center.first-face.width/2, face.center.second-face.height/2);
  Point br = tl + Point(face.width, face.height);
  rectangle(image, tl, br, color);

  if(annotate){
    int baseline=0;
    float fontScale = 1.0;
    int fontFace = FONT_HERSHEY_PLAIN;
    int thickness = 1;
    //Size textSize = getTextSize(annotateValue, fontFace, fontScale, thickness, &baseline);

    putText(image, annotateValue, tl-Point(4,4), fontFace, fontScale, Scalar(0,0,0));
    putText(image, annotateValue, tl-Point(5,5), fontFace, fontScale, color);
  }
}
