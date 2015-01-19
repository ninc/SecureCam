#include <iostream>
#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

class GuiNinc
{
 public:
  GuiNinc(int screen_width, int screen_height, string window_name);
  void display(int h, int w, Mat img[]);



 private:
  int m_screen_height;
  int m_screen_width;
  //Used to define window setup
  int m_setup;
  
  // w - Maximum number of images in a row 
  // h - Maximum number of images in a column 
  int m_width, m_height;

  // scale - How much we have to resize the image
  float m_scale;
  int m_max;
  
  //Image size
  int m_img_width;
  int m_img_height;

  string m_window_name;



};
