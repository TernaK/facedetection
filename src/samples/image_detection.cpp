/* description
  Run the face detector on an input image provided on the command line
*/

#include "facedetector.hpp"
using namespace cv;
using namespace std;
using namespace tkcv;

int main(int argc, char *argv[]){
  //command line args
  if(argc != 2){
    cout << "Correct usage: image_detection <path_to_image_file>" << endl;
    exit(-1);
  }

  //read the image
  Mat image = imread(argv[1]);

  std::chrono::time_point<std::chrono::system_clock> start, end;

  std::vector<Face> faces;
  FaceDetector fd;
  start = std::chrono::system_clock::now();
  //detect the faces
  fd.detectFaces(image, faces);
  end = std::chrono::system_clock::now();

  //draw the faces
  for(int i = 0 ; i < faces.size(); i++){
    fd.drawFaceRectInImage(faces[i], image, Scalar(255,255,0), true, "#"+to_string(i));
  }

  //stats
  printf("image size: %dx%d\n", image.size().width, image.size().height);
  printf("faces detected: %d\n", (int)faces.size());
  printf("detection time: %lldms\n", chrono::duration_cast<chrono::milliseconds>(end - start).count());

  //display
  namedWindow("faces");
  imshow("faces", image);
  waitKey();
}