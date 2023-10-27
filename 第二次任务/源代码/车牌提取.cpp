#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat srcimage = imread("C:\\Users\\24462\\Desktop\\车牌3.png");
	//namedWindow("原始图片",WINDOW_NORMAL);
	//imshow("原始图片", srcimage);

	//灰度化
	Mat gray_image;
	cvtColor(srcimage, gray_image, COLOR_RGB2GRAY);//转化为灰度图
	//namedWindow("灰度图",WINDOW_NORMAL);
	//imshow("灰度图", gray_image);

	//中值滤波，去噪
	Mat blur_image;
	medianBlur(gray_image, blur_image, 3);
	//namedWindow("滤过图", WINDOW_NORMAL);
	//imshow("滤过图", blur_image);

	//边缘检测
	Mat candy_image;
	Canny(blur_image, candy_image, 300, 200, 3);
	//namedWindow("test", WINDOW_NORMAL);
	//imshow("test", candy_image);

	//图片膨胀处理
	Mat dilate_image, erode_image;
	Mat element = getStructuringElement(MORPH_RECT, Size(25, 25));
	//Mat elementY = getStructuringElement(MORPH_RECT, Size(1, 25));
	Point point(-1, -1);
	//x方向的膨胀腐蚀，使车牌连成一个矩形区域
	dilate(candy_image, dilate_image, element, point, 2);
	erode(candy_image, dilate_image, element, point, 4);
	dilate(candy_image, dilate_image, element, point, 2);
	
	//y方向的膨胀腐蚀
	//erode(dilate_image, erode_image, elementY, point, 1);
	//dilate(erode_image, dilate_image, elementY, point, 2);
	//namedWindow("test", WINDOW_NORMAL);
	//imshow("test", dilate_image);
	
	Mat blur_image1;
	medianBlur(dilate_image, blur_image1, 15);
	medianBlur(blur_image1, blur_image1, 15);
	//namedWindow("test", WINDOW_NORMAL);
	//imshow("test", dilate_image);

	Mat contour_image;
	contour_image = blur_image1.clone();//拷贝图像信息
	//namedWindow("test", WINDOW_NORMAL);
	//imshow("test", canimage);

	/*vector<vector<Point>> contours;
	findContours(contour_image, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);
	drawContours(contour_image, contours, -1, Scalar(225), 1);
	Mat roi_image;
	vector<Point> rectPoint;
	for (int i = 0; i < contours.size(); i++)
	{
		Rect doundingRect = boundingRect(Mat(contours[i]));
		float aspectRatio = static_cast<float>(doundingRect.width)/ static_cast<float> (doundingRect.height);
		if (aspectRatio >= 2.2 && aspectRatio <= 3.6)
		{
			rectangle(contour_image, doundingRect, Scalar(0, 0, 255), 2);
			roi_image = srcimage(doundingRect);
		}
	}*/
	vector<vector<Point>> contours;
	findContours(contour_image, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//画出轮廓
	drawContours(contour_image, contours, -1, Scalar(255), 1);
	//轮廓表示为一个矩形  车牌提取
	Mat  roi_image;
	vector<Point> rectPoint;
	for (int i = 0; i < contours.size(); i++) 
	{
		Rect r = boundingRect(Mat(contours[i]));
		//RotatedRect r = minAreaRect(Mat(contours[i]));
		//cout << "contours " << i << "  height = " << r.height << "  width = " << r.width << "rate = " << ((float)r.width / r.height) << endl;
		if ((float)r.width / r.height >= 2.5 && (float)r.width / r.height <= 3.5) 
		{
			//cout << "r.x = " << r.x << "  r.y  = " << r.y << endl;
			rectangle(contour_image, r, Scalar(0, 0, 255), 2);
			//for (int j = 0; j < contours[i].size(); j++) {
			//	cout << "point = " << contours[i][j] << endl;
			//}
			//rectangle(image, r, Scalar(0, 0, 255), 3);
			roi_image = srcimage(r);
		}
	}
	//namedWindow("test", WINDOW_NORMAL);
	//imshow("test", roi_image);
	Mat roi_gray_image;
	cvtColor(roi_image, roi_gray_image, COLOR_RGB2GRAY);
	//namedWindow("test", WINDOW_NORMAL);
	//imshow("test", roi_gray_image);

	Mat candy_roi_image;
	Canny(roi_gray_image, candy_roi_image, 300, 200, 3);
	//二值化
	Mat roi_threadhold_image;
	threshold(candy_roi_image, roi_threadhold_image, 100, 255, THRESH_BINARY);
	namedWindow("test", WINDOW_NORMAL);
	imshow("test", roi_threadhold_image);
	waitKey(0);
	destroyAllWindows();
	return 0;
}