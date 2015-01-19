#include "GuiNinc.h"

using namespace cv;
using namespace std;


GuiNinc::GuiNinc(int screen_width, int screen_height, string window_name) :
  m_screen_width{screen_width}, m_screen_height{screen_height}, m_window_name{window_name}
{

  namedWindow(m_window_name, 0);
  resizeWindow(m_window_name, m_screen_width, m_screen_height);
}


void GuiNinc::display(int h, int w, Mat img[])
{

  m_width = w;
  m_height = h;
  
  //Determine how large each image segment is
  m_img_width = m_screen_width / m_width;
  m_img_height = m_screen_height / m_height;

  // Large image to display the smaller image in
  Mat display_img(m_screen_height, m_screen_width, CV_8UC3, Scalar(0, 0, 0));
  Mat roi;

  int x, y;
  int k = 0;
  Rect roi_rect;

  //Copy images to the display image
  for(int i = 0; i<m_height; ++i)
    for(int j = 0; j<m_width; ++j)
      {

	x = j*m_img_width;
	y = i*m_img_height;

	roi_rect = cvRect(x, y, m_img_width, m_img_height);

	// Set the image ROI to display the current image
	roi = display_img(roi_rect);

	cout << "(x, y): " << x << ", " << y << endl;
	cout << "ROI: " << roi.cols << " x " << roi.rows << endl << endl;

	// Resize the input image and copy the it to the Single Big Image
	resize(img[k], roi, roi.size());

	k++;
      }

  imshow(m_window_name, display_img);
}
