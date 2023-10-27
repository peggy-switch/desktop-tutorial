#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat srcimage = imread("D:\\����С��.jpg");
	Mat dstimage1 , dstimage2 , dstimage3;

	if (!srcimage.data)
	{
		cout << "û���ҵ�ͼƬ" << endl;
		return -1;
	}
	namedWindow("input image", WINDOW_AUTOSIZE);     //����������ʾͼƬ
	imshow("input image", srcimage);               //��ʾͼƬ

	double scale_down1 = 0.8;        //��С����
	resize(srcimage, dstimage1, Size(), scale_down1, scale_down1, INTER_LINEAR);    //�ߴ����
	namedWindow("input dst1", WINDOW_AUTOSIZE);
	imshow("input dst1", dstimage1);

	double scale_down2 = 0.6;
	resize(srcimage, dstimage2, Size(), scale_down2, scale_down2, INTER_LINEAR);
	namedWindow("input dst2", WINDOW_AUTOSIZE);
	imshow("input dst2", dstimage2);

	pyrDown(srcimage, dstimage3, Size((srcimage.cols + 1) / 2, (srcimage.rows + 1) / 2), BORDER_DEFAULT);
	namedWindow("input dst3", WINDOW_AUTOSIZE);     //����������ʾͼƬ
	imshow("input dst3", dstimage3);               //��ʾͼƬ

	waitKey(0);
	destroyAllWindows();
	return 0;
}