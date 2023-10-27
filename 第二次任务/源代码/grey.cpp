#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	Mat srcimage = imread("D:\\����С��.jpg");      //����ͼƬλ��
	Mat gray_src; 
	if (!srcimage.data)
	{
		cout << "û���ҵ�ͼƬ" << endl;
		return -1;
	}
	namedWindow("input image", WINDOW_AUTOSIZE);     //����������ʾͼƬ
	imshow("input image", srcimage);               //��ʾͼƬ

	//���ÿ�ת��Ϊ�Ҷ�ͼ
	/*
	cvtColor(srcimage, gray_src, COLOR_BGR2GRAY);
	namedWindow("input gray", WINDOW_AUTOSIZE);
	imshow("input gray", gray_src);
	*/

	gray_src.create(srcimage.size(), srcimage.type());   //��ʼ��ͼ���С��λ���
	int heigth = srcimage.rows;
	int width = srcimage.cols;
	int nc = srcimage.channels();

	for (int row = 0; row < heigth; row++)
	{
		for (int col = 0; col < width; col++)
		{
			int gray = gray_src.at<uchar>(row, col);
			//gray_src.at<uchar>(row, col) = 255 - gray;
			int r = srcimage.at<Vec3b>(row, col)[0];      //��ȡ����ֵr
			int g = srcimage.at<Vec3b>(row, col)[1];     //��ȡ����ֵg
			int b = srcimage.at<Vec3b>(row, col)[2];    //��ȡ����ֵb

			gray = (r * 76 + g * 150 + b * 30) >> 8;     //��ȡ�Ҷ�ͼ
			gray_src.at<uchar>(row , col) = gray;
		}
	}

	namedWindow("input gray",WINDOW_AUTOSIZE);
	imshow("input gray", gray_src);
	//namedWindow("ȡ������", WINDOW_AUTOSIZE);
	//imshow("ȡ������", gray_src);
	waitKey(10000);
	destroyAllWindows();
	return nc;
}