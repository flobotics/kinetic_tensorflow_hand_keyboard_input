#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sstream> // for converting the command line parameter to integer
#include <ros/console.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

int main(int argc, char** argv)
{
  // Check if video source has been passed as a parameter
  if(argv[1] == NULL) return 1;

  ros::init(argc, argv, "image_publisher");
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh);
  image_transport::Publisher pub = it.advertise("camera/imageai", 1);

  // Convert the passed as command line parameter index for the video device to an integer
  std::istringstream video_sourceCmd(argv[1]);
  int video_source;
  // Check if it is indeed a number
  if(!(video_sourceCmd >> video_source)) return 1;

  cv::VideoCapture cap(video_source);
  // Check if video device can be opened with the given index
  if(!cap.isOpened()) return 1;
  cv::Mat frame;
  cv::Mat back_frame(600,640,CV_8UC1, cv::Scalar::all(255));
  cv::Mat cmd_frame(50,50, CV_8UC1, cv::Scalar::all(0));
  cv::Mat force_frame(32,512, CV_8UC1, cv::Scalar::all(255));
  force_frame.at<uchar>(0, 50) = 0;
  force_frame.at<uchar>(2, 250) = 0;
  force_frame.at<uchar>(4, 50) = 0;
  force_frame.at<uchar>(6, 250) = 0;
  force_frame.at<uchar>(8, 50) = 0;
  force_frame.at<uchar>(10, 250) = 0;
  force_frame.at<uchar>(12, 50) = 0;
  force_frame.at<uchar>(14, 250) = 0;

  force_frame.at<uchar>(16, 50) = 0;
  force_frame.at<uchar>(18, 250) = 0;
  force_frame.at<uchar>(20, 50) = 0;
  force_frame.at<uchar>(22, 250) = 0;
  force_frame.at<uchar>(24, 50) = 0;
  force_frame.at<uchar>(26, 250) = 0;
  force_frame.at<uchar>(28, 50) = 0;
  force_frame.at<uchar>(30, 250) = 0;

  putText(cmd_frame, "2",cvPoint(0,45),0, 2, cvScalar(800,800,950), 3, 1);
  sensor_msgs::ImagePtr msg;

  ros::Rate loop_rate(5);
  while (nh.ok()) {
    cap >> frame;
    // Check if grabbed frame is actually full with some content
    if(!frame.empty()) {
      //widht=640  heigth=480
      //printf("mat height >%d< widht >%d<", frame.rows, frame.cols );
      cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);

      frame.copyTo(back_frame(cv::Rect(0,82,frame.cols, frame.rows)));      
      cmd_frame.copyTo(back_frame(cv::Rect(0,0,cmd_frame.cols, cmd_frame.rows)));
      force_frame.copyTo(back_frame(cv::Rect(0,50, force_frame.cols, force_frame.rows)));

      msg = cv_bridge::CvImage(std_msgs::Header(), "mono8", back_frame).toImageMsg();
  //    msg = cv_bridge::CvImage(std_msgs::Header(), "mono8", frame).toImageMsg();
  //  msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();
      pub.publish(msg);
      cv::waitKey(1);
    }

    ros::spinOnce();
    loop_rate.sleep();
  }
}
