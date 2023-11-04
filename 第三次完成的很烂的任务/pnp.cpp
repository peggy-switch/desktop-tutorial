#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    // �����������ͻ������
    Mat camera_matrix = (Mat_<double>(3, 3) << 1900.,0.,960.,0.,1900.,540.,0.,0.,1.);
    Mat distortion_coeffs = (Mat_<double>(1, 5) << 0.,0.,0.,0.,0.);

    // ����ͼƬ������Ԥ����
    Mat src = imread("1_whole.png");
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);

    // ����װ�װ��ĸ����������
    vector<Point3f> object_points;
    object_points.push_back(Point3f(-12.5f, -5.5f, 0.f)); // ���½�
    object_points.push_back(Point3f(-12.5f, 5.5f, 0.f));  // ���Ͻ�
    object_points.push_back(Point3f(12.5f, 5.5f, 0.f));   // ���Ͻ�
    object_points.push_back(Point3f(12.5f, -5.5f, 0.f));  // ���½�

    // ����װ�װ��ĸ�������ͼ���е�����
    vector<Point2f> image_points;
    image_points.push_back(Point2f(994, 899)); // ���½�
    image_points.push_back(Point2f(984, 816));  // ���Ͻ�
    image_points.push_back(Point2f(1063, 813));  // ���Ͻ�
    image_points.push_back(Point2f(1069, 896)); // ���½�

    // ʹ��PnP�㷨������ת������ƽ������
    Mat rvec, tvec;
    solvePnP(object_points, image_points, camera_matrix, distortion_coeffs, rvec, tvec);

    // ����ת����ת��Ϊ��ת����
    Mat rotation_matrix;
    Rodrigues(rvec, rotation_matrix);

    // �����ת�����ƽ�ƾ���
    cout << "Rotation Matrix: " << endl << rotation_matrix << endl;
    cout << "Translation Vector: " << endl << tvec << endl;

    return 0;
}