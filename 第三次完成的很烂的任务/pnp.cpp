#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    // 加载相机矩阵和畸变参数
    Mat camera_matrix = (Mat_<double>(3, 3) << 1900.,0.,960.,0.,1900.,540.,0.,0.,1.);
    Mat distortion_coeffs = (Mat_<double>(1, 5) << 0.,0.,0.,0.,0.);

    // 加载图片并进行预处理
    Mat src = imread("1_whole.png");
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);

    // 定义装甲板四个顶点的坐标
    vector<Point3f> object_points;
    object_points.push_back(Point3f(-12.5f, -5.5f, 0.f)); // 左下角
    object_points.push_back(Point3f(-12.5f, 5.5f, 0.f));  // 左上角
    object_points.push_back(Point3f(12.5f, 5.5f, 0.f));   // 右上角
    object_points.push_back(Point3f(12.5f, -5.5f, 0.f));  // 右下角

    // 定义装甲板四个顶点在图像中的坐标
    vector<Point2f> image_points;
    image_points.push_back(Point2f(994, 899)); // 左下角
    image_points.push_back(Point2f(984, 816));  // 左上角
    image_points.push_back(Point2f(1063, 813));  // 右上角
    image_points.push_back(Point2f(1069, 896)); // 右下角

    // 使用PnP算法计算旋转向量和平移向量
    Mat rvec, tvec;
    solvePnP(object_points, image_points, camera_matrix, distortion_coeffs, rvec, tvec);

    // 将旋转向量转化为旋转矩阵
    Mat rotation_matrix;
    Rodrigues(rvec, rotation_matrix);

    // 输出旋转矩阵和平移矩阵
    cout << "Rotation Matrix: " << endl << rotation_matrix << endl;
    cout << "Translation Vector: " << endl << tvec << endl;

    return 0;
}