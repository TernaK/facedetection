#pragma once

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <opencv2/opencv.hpp>
#include <string>

namespace tkcv {

  //hold data related to face detections
  typedef struct Face {
    std::pair<unsigned,unsigned> center = std::make_pair(0,0);  //center coordinates of face
    unsigned height = 0;                                        //height of face
    unsigned width = 0;                                         //width of face
    float confidence;

    Face(std::pair<unsigned,unsigned> _center, int _height, int _width, float _confidence=1.0f)
    : center(_center),
      height(_height),
      width(_width),
      confidence(_confidence) {
    }

  } Face;


  //interface to the face detector
  class FaceDetector {
  private:
    std::string cascadeFilePath;        //path to cascade file
    cv::CascadeClassifier faceCascade;  //face classifier

  public:
    FaceDetector();


    //detect faces in an image
    //image:input the image in which to detect the faces
    //faces:output array of detected faces
    void detectFaces(const cv::Mat& image, std::vector<Face>& faces);


    //draw face region of interest in an image
    //face:input the face to draw
    //image:input the image in which to draw the face
    //color:input/optional the color of the annotation
    //annotate:input/optional set true to annotate face
    //annotateWith:input/optional annotate the face with this text
    void drawFaceRectInImage(
      const Face& face, 
      cv::Mat& image, 
      cv::Scalar color=cv::Scalar(255,255,0),
      bool annotate=false, 
      std::string annotateValue="");
  };
}
