#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/opencv.hpp"
#include <iostream>
#include "GuiNinc.h"

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

  bool test = true;

  int display_width = 1280;
  int display_height = 720;

  Mat images[2];

  VideoCapture cap(0); // open the default camera
  if(!cap.isOpened())  // check if we succeeded
    return -1;

  //Change capturing resolution
  cap.set(CAP_PROP_FRAME_WIDTH, CAM_WIDTH);
  cap.set(CAP_PROP_FRAME_HEIGHT, CAM_HEIGHT);
    

  cap >> images[0];

  // Open the output
  Size frame_size = Size(images[0].cols, images[0].rows);
  //initialize the VideoWriter object 
  VideoWriter out_video("out.avi", CV_FOURCC('X','2','6','4'), 30.0, frame_size, false);

  //if not initialize the VideoWriter successfully, exit the program
  if (!out_video.isOpened())
    {
      cout << "ERROR: Failed to write the video" << endl;
      return -1;
    }

  /*
  Mat edges;
  namedWindow("edges",0);
  namedWindow("frame",0);
  resizeWindow("edges", display_width, display_height);
  resizeWindow("frame", display_width, display_height);
  */


  GuiNinc gui(display_width, display_height, "Camera setup");


  for(;;)
    {
      cap >> images[0]; // get a new frame from camera
      cvtColor(images[0], images[1], CV_BGR2GRAY);
      GaussianBlur(images[1], images[1], Size(7,7), 1.5, 1.5);
      Canny(images[1], images[1], 0, 30, 3);
      
      gui.display(1, 2, images);

      if(test)
	{
	  cout << "EDGES" << endl;
	  print_mat_info(images[1]);


	  cout << "FRAME" << endl;
	  print_mat_info(images[0]);
	  test = false;
	}

      out_video.write(images[1]);

      if(waitKey(30) >= 0) break;
    }
  // the camera will be deinitialized automatically in VideoCapture destructor
  return 0;
}
