#include<iostream>
#include<opencv2/viz.hpp>
#include<opencv2/opencv.hpp>
#include<Eigen/Core>
#include<Eigen/Geometry>
#define pi 3.1415926

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	/*Eigen::Vector3d eulerAngle(150 * pi / 180, 60 * pi / 180, 90 * pi / 180);

	Eigen::Matrix3d rotation_matrix3;
	rotation_matrix3 = Eigen::AngleAxisd(eulerAngle(0), Eigen::Vector3d::UnitZ()) *
		Eigen::AngleAxisd(eulerAngle(1), Eigen::Vector3d::UnitY()) *
		Eigen::AngleAxisd(eulerAngle(2), Eigen::Vector3d::UnitX());*/
	viz::Viz3d myWindow("Coordinate Frame");
	Vec3d cam1_pose(0, 0, 0), cam1_focalPoint(0, 0, 1), cam1_y_dir(0, -1, 0);
	Affine3d cam_3_pose = viz::makeCameraPose(cam1_pose, cam1_focalPoint, cam1_y_dir);
	myWindow.showWidget("World_coordinate", viz::WCoordinateSystem(), cam_3_pose);
	Matx33d PoseR;
	Vec3d PoseT;
	PoseR = Matx33d(-0.433013, -0.75, 0.5, 0.25, 0.433013, 0.866025, -0.866025, 0.5, 1.33974e-08);
	PoseT = Vec3d(-0.128633, 0.000609044, 0.122929) * 10;
	Affine3d Transpose03(PoseR,PoseT);
	myWindow.showWidget("Cam", viz::WCoordinateSystem(), Transpose03);
	myWindow.spin();
	cout << "Hello World" << endl;
	return 0;
}