#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	Mat srcimage = imread("D:\\蜡笔小新.jpg");      //读入图片位置
	Mat gray_src; 
	if (!srcimage.data)
	{
		cout << "没有找到图片" << endl;
		return -1;
	}
	namedWindow("input image", WINDOW_AUTOSIZE);     //创建窗口显示图片
	imshow("input image", srcimage);               //显示图片

	//利用库转化为灰度图
	/*
	cvtColor(srcimage, gray_src, COLOR_BGR2GRAY);
	namedWindow("input gray", WINDOW_AUTOSIZE);
	imshow("input gray", gray_src);
	*/

	gray_src.create(srcimage.size(), srcimage.type());   //初始化图像大小和位深度
	int heigth = srcimage.rows;
	int width = srcimage.cols;
	int nc = srcimage.channels();

	for (int row = 0; row < heigth; row++)
	{
		for (int col = 0; col < width; col++)
		{
			int gray = gray_src.at<uchar>(row, col);
			//gray_src.at<uchar>(row, col) = 255 - gray;
			int r = srcimage.at<Vec3b>(row, col)[0];      //获取像素值r
			int g = srcimage.at<Vec3b>(row, col)[1];     //获取像素值g
			int b = srcimage.at<Vec3b>(row, col)[2];    //获取像素值b

			gray = (r * 76 + g * 150 + b * 30) >> 8;     //获取灰度图
			gray_src.at<uchar>(row , col) = gray;
		}
	}

	namedWindow("input gray",WINDOW_AUTOSIZE);
	imshow("input gray", gray_src);
	//namedWindow("取反操作", WINDOW_AUTOSIZE);
	//imshow("取反操作", gray_src);
	waitKey(10000);
	destroyAllWindows();
	return nc;
}