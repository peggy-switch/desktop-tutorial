#ifndef KALMANFILTER_KALMANFILTER_H
#define KALMANFILTER_KALMANFILTER_H
#ifndef _EXTENDED_KALMAN_OLD_HPP
#define _EXTENDED_KALMAN_OLD_HPP

//#include "ceres/jet.h"
#include "Eigen/Dense"
#include <Eigen/Core>
#include <vector>
#include <iostream>

// KFģ��
template<typename T, int x, int y>
class KalmanFilter {
public:
    Eigen::Matrix<T, x, y> kalman_gain; //����������

    Eigen::Matrix<T, y, 1> measurement; //����ֵz_k

    Eigen::Matrix<T, x, 1> prior_state_estimate;         //�������
    Eigen::Matrix<T, y, 1> prior_state_estimate_measure; //������Ʋ���

    Eigen::Matrix<T, x, x> transition_matrix;         // A:״̬ת�ƾ���
    Eigen::Matrix<T, x, 1> posteriori_state_estimate; //�������
    Eigen::Matrix<T, x, x> error_cov_post;            //״̬����Э������� P_k
    Eigen::Matrix<T, x, x> process_noise_cov;         //������������Q
    Eigen::Matrix<T, y, y> measurement_noise_cov;     //������������ : R
    Eigen::Matrix<T, x, 1> control_vector;            // u_k����������
    Eigen::Matrix<T, x, x> control_matrix;            // B�� ���ƾ���
    Eigen::Matrix<T, y, x> measurement_matrix;        //�������� �� H

    Eigen::Matrix<T, y, y> measurement_cov_maxtrix;

    Eigen::Matrix<T, y, 1> residual; //�в�����

    Eigen::Matrix<T, y, y> residual_matrix; // �в����S

public:
    KalmanFilter() {
        error_cov_post = Eigen::Matrix<T, x, x>::Identity();
        control_vector = Eigen::Matrix<T, x, 1>::Zero();
        control_matrix = Eigen::Matrix<T, x, x>::Zero();
        measurement_matrix = Eigen::Matrix<T, y, x>::Zero();
        process_noise_cov = Eigen::Matrix<T, x, x>::Identity() * 0.001;
        measurement_noise_cov = Eigen::Matrix<T, y, y>::Identity();
        posteriori_state_estimate = Eigen::Matrix<T, x, 1>::Zero();
        measurement_cov_maxtrix = Eigen::Matrix<T, y, y>::Zero();
    }


    Eigen::Matrix<T, x, 1> predict(Eigen::Matrix<T, y, 1> measure) {
        prior_state_estimate = transition_matrix * posteriori_state_estimate + control_matrix * control_vector;
        prior_state_estimate_measure = measurement_matrix * prior_state_estimate;
        error_cov_post = transition_matrix * error_cov_post * transition_matrix.transpose() + process_noise_cov;
        measurement_cov_maxtrix = (measurement_matrix * error_cov_post * measurement_matrix.transpose() +
            measurement_noise_cov).inverse();
        residual = measure - prior_state_estimate_measure;
        return prior_state_estimate;
    }

    Eigen::Matrix<T, x, 1> update() {
        kalman_gain = error_cov_post * measurement_matrix.transpose() * measurement_cov_maxtrix;
        posteriori_state_estimate = prior_state_estimate + kalman_gain * residual;
        error_cov_post = (Eigen::Matrix<T, x, x>::Identity() - kalman_gain * measurement_matrix) * error_cov_post;
        return posteriori_state_estimate;
    }

};

#endif
#endif //KALMANFILTER_KALMANFILTER_H
#pragma once
