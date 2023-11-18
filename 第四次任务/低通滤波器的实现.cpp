
#include"Simulator.h"
#include<iostream>
#include<vector>
#include<Eigen/Dense>
#include<Eigen/Core>
constexpr auto M_PI = 3.14159265358979323846;

using namespace std;

class LowPassFilter
{
public:
	LowPassFilter(double sample_rate, double cutoff_frequency)
	{
		double dt = 1.0 / sample_rate;
		double RC = 1.0 / (cutoff_frequency * 2.0 * M_PI);
		alpha_ = dt / (dt + RC);
		prev_output_ = 0.0;
	}

	double update(double input)
	{
		double output = alpha_ * input + (1.0 - alpha_) * prev_output_;
		prev_output_ = output;
		return output;
	}

private:
	double alpha_;
	double prev_output_;
};

int main()
{
	Simulator<double, 2>* simulator;
	simulator = new Simulator<double, 2>(Eigen::Vector2d(0, 0), 5);
	Eigen::Vector2d measurement;
	measurement = simulator->getMeasurement();
	//cout << measurement;
	vector<double>input_signal = { -2.62604,2.64355 };
	double sample_rate = 100.0;
	double cutoff_frequency = 10.0;
	LowPassFilter filter(sample_rate, cutoff_frequency);
	vector<double>output_signal;
	for (double input : input_signal)
	{
		double output = filter.update(input);
		output_signal.push_back(output);
	}
	for (double output : output_signal)
	{
		cout << output << " ";
	}
	cout << endl;
	return 0;
}