#include<iostream>
#include<Eigen/Core>
#include<Eigen/Geometry>
#define pi 3.1415926

using namespace std;

int main()
{
	Eigen::Vector3d eulerAngle(150 * pi / 180, 60 * pi / 180, 90 * pi / 180);
	
	Eigen::Matrix3d rotation_matrix3;
	rotation_matrix3 = Eigen::AngleAxisd(eulerAngle(0), Eigen::Vector3d::UnitZ()) *
		Eigen::AngleAxisd(eulerAngle(1), Eigen::Vector3d::UnitY()) *
		Eigen::AngleAxisd(eulerAngle(2), Eigen::Vector3d::UnitX());
	cout << "rotation matrix3 =\n" << rotation_matrix3 << endl;

	return 0;
}