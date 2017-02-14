// The contents of this file are in the public domain. See LICENSE_FOR_EXAMPLE_PROGRAMS.txt
/*

    This example program shows how to find frontal human faces in an image and
    estimate their pose.  The pose takes the form of 68 landmarks.  These are
    points on the face such as the corners of the mouth, along the eyebrows, on
    the eyes, and so forth.  
    

    This example is essentially just a version of the face_landmark_detection_ex.cpp
    example modified to use OpenCV's VideoCapture object to read from a camera instead 
    of files.


    Finally, note that the face detector is fastest when compiled with at least
    SSE2 instructions enabled.  So if you are using a PC with an Intel or AMD
    chip then you should enable at least SSE2 instructions.  If you are using
    cmake to compile this program you can enable them by using one of the
    following commands when you create the build project:
        cmake path_to_dlib_root/examples -DUSE_SSE2_INSTRUCTIONS=ON
        cmake path_to_dlib_root/examples -DUSE_SSE4_INSTRUCTIONS=ON
        cmake path_to_dlib_root/examples -DUSE_AVX_INSTRUCTIONS=ON
    This will set the appropriate compiler options for GCC, clang, Visual
    Studio, or the Intel compiler.  If you are using another compiler then you
    need to consult your compiler's manual to determine how to enable these
    instructions.  Note that AVX is the fastest but requires a CPU from at least
    2011.  SSE4 is the next fastest and is supported by most current machines.  
*/

#include <dlib/opencv.h>
#include <opencv2/opencv.hpp>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>

using namespace dlib;
using namespace std;

int main() {
  try {
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
      cerr << "Unable to connect to camera" << endl;
      return 1;
    }
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
    cv::namedWindow("stream");

    // Load face detection and pose estimation models.
    frontal_face_detector detector = get_frontal_face_detector();
    shape_predictor pose_model;
    string modelPath = SUPPORT_PATH;
    modelPath += "shape_predictor_68_face_landmarks.dat";
    deserialize(modelPath) >> pose_model;

    // Grab and process frames until the main window is closed by the user.
    // 
    std::vector<int> POIs = {0,8,16,17,19,21,22,24,26,36,39,42,45,27,31,33,35,48,51,54,57};
    
    for(;;) {
      // Grab a frame
      cv::Mat frame;
      cap >> frame;

      cv_image<bgr_pixel> cimg(frame);

      // Detect faces 
      std::vector<rectangle> faces = detector(cimg);
      cout << faces.size() << " face(s) found!" << endl;

      for (auto face: faces) {
        // Find the pose of each face.
        full_object_detection shape = pose_model(cimg, face);

        for(int j = 0; j < POIs.size(); j++) {
          cv::Point org(shape.part(POIs[j]).x(), shape.part(POIs[j]).y());
          cv::circle(frame, org, 2, cv::Scalar(0,255,0));
          // cv::putText(frame, to_string(j), org, cv::FONT_HERSHEY_SCRIPT_SIMPLEX, 0.5, cv::Scalar(255,0,0));
        }  
      }

      // Display it all on the screen
      cv::imshow("stream", frame);
      cout << "press enter to continue\n" ;
      if(cv::waitKey() >= 27) break;
    }
  }

  catch(serialization_error& e) {
    cout << "You need dlib's default face landmarking model file to run this example." << endl;
    cout << "You can get it from the following URL: " << endl;
    cout << "   http://dlib.net/files/shape_predictor_68_face_landmarks.dat.bz2" << endl;
    cout << endl << e.what() << endl;
  }
  catch(exception& e) {
    cout << e.what() << endl;
  }
}
