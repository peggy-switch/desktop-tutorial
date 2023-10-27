#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat srcimage = imread("D:\\蜡笔小新.jpg");
	Mat dstimage1 , dstimage2 , dstimage3;

	if (!srcimage.data)
	{
		cout << "没有找到图片" << endl;
		return -1;
	}
	namedWindow("input image", WINDOW_AUTOSIZE);     //创建窗口显示图片
	imshow("input image", srcimage);               //显示图片

	double scale_down1 = 0.8;        //缩小比例
	resize(srcimage, dstimage1, Size(), scale_down1, scale_down1, INTER_LINEAR);    //尺寸调整
	namedWindow("input dst1", WINDOW_AUTOSIZE);
	imshow("input dst1", dstimage1);

	double scale_down2 = 0.6;
	resize(srcimage, dstimage2, Size(), scale_down2, scale_down2, INTER_LINEAR);
	namedWindow("input dst2", WINDOW_AUTOSIZE);
	imshow("input dst2", dstimage2);

	pyrDown(srcimage, dstimage3, Size((srcimage.cols + 1) / 2, (srcimage.rows + 1) / 2), BORDER_DEFAULT);
	namedWindow("input dst3", WINDOW_AUTOSIZE);     //创建窗口显示图片
	imshow("input dst3", dstimage3);               //显示图片

	waitKey(0);
	destroyAllWindows();
	return 0;
}