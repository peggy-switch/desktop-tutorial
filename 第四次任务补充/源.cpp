#include <iostream>
#include <opencv2/opencv.hpp>
#include<Eigen/Dense>
#include<Eigen/Core>
#include "KalmanFilter.h"
#include "Simulator.h"

using namespace std;

int main() {
    srand(114514);
    // ��һ����ֹ�˲�Ϊ��չʾʹ�÷���
    // 1. ��ʼ��
    // �˲�����ʼ��
    KalmanFilter<double, 4, 4>* kf;
    kf = new KalmanFilter<double, 4, 4>();
    // ��������ʼ��
    Simulator<double, 4>* simulator;
    simulator = new Simulator<double, 4>(Eigen::Vector4d(0, 0,0,0), 5); // ����Ϊ��ʼ���뷽��

    // 2. ����״̬ת�ƾ���
    kf->transition_matrix << 1, 0, 0.1, 0,
        0, 1, 0, 0.1,
        0, 0, 1, 0,
        0, 0, 0, 1;
    // 3. ���ò�������
    kf->measurement_matrix << 1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1;
    // 4. ���ù�������Э�������
    kf->process_noise_cov << 0.01, 0, 0, 0,
        0, 0.01, 0, 0,
        0, 0, 0.01, 0,
        0, 0, 0, 0.01;
    // 5. ���ò�������Э�������
    kf->measurement_noise_cov << 5, 0, 0, 0,
        0, 5, 0, 0,
        0, 0, 5, 0,
        0, 0, 0, 5;
    // 6. ���ÿ�������
    kf->control_vector << 0,
        0,
        0,
        0;

    // ���������
    Eigen::Vector4d measurement;
    cv::Mat img(500, 500, CV_8UC3, cv::Scalar(0, 0, 0));
    while (1) {
        measurement = simulator->getMeasurement();
        // 7. Ԥ��
        kf->predict(measurement);
        // 8. ����
        kf->update();
        // 9. ��ȡ�������
        Eigen::Vector4d estimate = kf->posteriori_state_estimate;
        // 10. ���Ƴ��۲����˲��㣨ƽ�Ƶ���ͼ���ģ�����ɲ����������ӻ�������matplotlib��VOFA+��Foxglove���ɣ�
        cv::circle(img, cv::Point((int)(measurement[0] * 10 + 250), int(measurement[1] * 10 + 250)), 2, cv::Scalar(0, 0, 255), -1);
        cv::circle(img, cv::Point((int)(estimate[0] * 10 + 250), (int)(estimate[1] * 10 + 250)), 2, cv::Scalar(0, 255, 0), -1);

        cv::imshow("img", img);
        cv::waitKey(10);
    }

    return 0;
}
