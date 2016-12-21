#pragma once

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <opencv2/opencv.hpp>
#include <string>

namespace tkcv {

  typedef struct Face {
    std::pair<unsigned,unsigned> center = std::make_pair(0,0);
    unsigned height = 0;
    unsigned width = 0;
    float confidence;

    Face(std::pair<unsigned,unsigned> _center, int _height, int _width, float _confidence=1.0f)
    : center(_center),
      height(_height),
      width(_width),
      confidence(_confidence) {
    }

  } Face;

  class FaceDetector{
  private:
    std::string cascadeFilePath;
    cv::CascadeClassifier faceCascade;

  public:
    FaceDetector();
    void detectFaces(const cv::Mat& image, std::vector<Face>& faces);
    void drawFaceRectInImage(
      const Face& face, 
      cv::Mat& image, 
      cv::Scalar color=cv::Scalar(255,255,0),
      bool annotate=false, 
      std::string annotateValue="");
  };
}
