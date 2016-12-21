#include "facedetector.hpp"
using namespace cv;
using namespace std;
using namespace tkcv;

void test_faceDetection(){

  string folder = TEST_IMAGES_PATH;
  Mat image = imread(folder + "faces1.jpg");

  std::chrono::time_point<std::chrono::system_clock> start, end;

  std::vector<Face> faces;
  FaceDetector fd;
  start = std::chrono::system_clock::now();
  fd.detectFaces(image, faces);
  end = std::chrono::system_clock::now();

  for(auto face: faces){
    fd.drawFaceRectInImage(face, image, Scalar(255,255,0), true, "face");
  }

  printf("image size: %dx%d\n", image.size().width, image.size().height);
  printf("faces detected: %d\n", (int)faces.size());
  printf("detection time: %lldms\n", chrono::duration_cast<chrono::milliseconds>(end - start).count());
}

int main(){
  test_faceDetection();
}