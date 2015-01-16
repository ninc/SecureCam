#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;


//Print Matrix information for debugging purposes
void print_mat_info(const Mat& frame)
{

  cout << frame.cols << " x " << frame.rows << endl;

}


int main( int argc, char** argv )
{

  //This will yield 1920x1080 resolution on my logitech c920 camera.
  const int CAM_HEIGHT = 2000;
  const int CAM_WIDTH = 2000;

  int display_width = 1280;
  int display_height = 720;


  Mat frame;
  Mat prev_frame;


  VideoCapture cap(0); // open the default camera
  if(!cap.isOpened())  // check if we succeeded
    return -1;

  //Change capturing resolution
  cap.set(CAP_PROP_FRAME_WIDTH, CAM_WIDTH);
  cap.set(CAP_PROP_FRAME_HEIGHT, CAM_HEIGHT);
    

  cap >> frame;

  // Open the output
  Size frame_size = Size(frame.cols, frame.rows);
  //initialize the VideoWriter object 
  VideoWriter out_video("out.avi", CV_FOURCC('X','2','6','4'), 30.0, frame_size, false);

  //if not initialize the VideoWriter successfully, exit the program
  if (!out_video.isOpened())
    {
      cout << "ERROR: Failed to write the video" << endl;
      return -1;
    }

  bool test = true;
  Mat edges;
  namedWindow("edges",0);
  namedWindow("frame",0);
  resizeWindow("edges", display_width, display_height);
  resizeWindow("frame", display_width, display_height);
  

  for(;;)
    {
      cap >> frame; // get a new frame from camera
      cvtColor(frame, edges, CV_BGR2GRAY);
      GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
      Canny(edges, edges, 0, 30, 3);
      imshow("edges", edges);
      imshow("frame", frame);

      if(test)
	{
	  cout << "EDGES" << endl;
	  print_mat_info(edges);


	  cout << "FRAME" << endl;
	  print_mat_info(frame);
	  test = false;
	}

      out_video.write(edges);

      if(waitKey(30) >= 0) break;
    }
  // the camera will be deinitialized automatically in VideoCapture destructor
  return 0;
}
