#include "facedetector.hpp"
using namespace cv;
using namespace std;
using namespace tkcv;

int main(int argc, char *argv[]){
  if(argc != 2){
    cout << "Correct usage: image_detection <path_to_image_file>" << endl;
    exit(-1);
  }

  Mat image = imread(argv[1]);

  std::chrono::time_point<std::chrono::system_clock> start, end;

  std::vector<Face> faces;
  FaceDetector fd;
  start = std::chrono::system_clock::now();
  fd.detectFaces(image, faces);
  end = std::chrono::system_clock::now();

  for(int i = 0 ; i < faces.size(); i++){
    fd.drawFaceRectInImage(faces[i], image, Scalar(255,255,0), true, "#"+to_string(i));
  }

  printf("image size: %dx%d\n", image.size().width, image.size().height);
  printf("faces detected: %d\n", (int)faces.size());
  printf("detection time: %lldms\n", chrono::duration_cast<chrono::milliseconds>(end - start).count());

  namedWindow("faces");
  imshow("faces", image);
  waitKey();
}