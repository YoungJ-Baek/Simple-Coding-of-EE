#include <iostream>
#include <cmath>
#include <chrono>
#define PI 3.141592
using namespace std;

using ns = chrono::nanoseconds;
using get_time = chrono::steady_clock;

double pyramid(double x, double y, double height, int n);
double pyramid(double X, double Y, double Z, double dx, double dy, double dz);
double circle(double r, int n);
double circle(double r, double dr, double dpi, double dtheta);
double integralsine(double dt);
double accuracy(double result1, double result2);

int main()
{
	//1
	double x = 100;
	double y = 100;
	double height = 50;
	int n = 1000000;
	double dx = 1.0;
	double dy = dx;
	double dz = dx;

	auto start = get_time::now();
	double result_1 = (100. * 100. * 50.) / 3.;
	auto end = get_time::now();
	auto diff = end - start;

	cout << "#1. 사각뿔(m^3단위)" << endl << endl;
	cout << "계산량" << endl;
	cout << "수식 계산량:\t\t" << chrono::duration_cast<ns>(diff).count() << endl;

	//double integral_1 = pyramid(x, y, height, n);
	double integral_1 = pyramid(x, y, height, dx, dy, dz);
	cout << "계산식 : " << result_1 << "\t구분구적법: " << integral_1 << endl << endl;

	double acc = accuracy(result_1, integral_1);
	cout << "정확도" << endl;
	cout << "Accuracy: " << acc << "\tdB: " << -10 * log10f(acc) << endl << endl;


	//2
	double r = 5;
	double dr = dx;
	double dp = dx;
	double dth = dx;
	start = get_time::now();
	double result_2 = (4 * PI*pow(r, 3) / 3);
	end = get_time::now();
	diff = end - start;

	cout << "#2. 구(cm^3단위)" << endl << endl;
	cout << "계산량" << endl;
	cout << "수식 계산량:\t\t" << chrono::duration_cast<ns>(diff).count() << endl;

	//double integral_2 = circle(r,n);
	double integral_2 = circle(r, dr, dp, dth);
	cout << "계산식 : " << result_2 << "\t구분구적법: " << integral_2 << endl << endl;

	acc = accuracy(result_2, integral_2);
	cout << "정확도" << endl;
	cout << "Accuracy: " << acc << "\tdB: " << -10 * log10f(acc) << endl << endl;

	//3
	double dt = 0.005;
	start = get_time::now();
	double result_3 = -(cos(2 * PI*0.5) - cos(2 * PI * 0)) / (2 * PI);
	end = get_time::now();
	diff = end - start;

	cout << "#3." << endl << endl;
	cout << "계산량" << endl;
	cout << "수식 계산량:\t\t" << chrono::duration_cast<ns>(diff).count() << endl;

	double integral_3 = integralsine(dt);
	cout << "계산식 : " << result_3 << "\t구분구적법: " << integral_3 << endl << endl;

	acc = accuracy(result_3, integral_3);
	cout << "정확도" << endl;
	cout << "Accuracy: " << acc << "\tdB: " << -10 * log10f(acc) << endl << endl;
	return 0;
}

double pyramid(double x, double y, double height, int n)
{
	double dh = height / n;
	double sum = 0;
	auto start = get_time::now();
	for (int i = 1; i <= n; i++)
		sum += (x*y)*pow(double(i) / n, 2)*dh;
	auto end = get_time::now();
	auto diff = end - start;
	cout << "구분구적법 계산량:\t" << chrono::duration_cast<ns>(diff).count() << endl << endl;
	return sum;
}

double pyramid(double X, double Y, double Z, double dx, double dy, double dz)
{
	double sum = 0;
	auto start = get_time::now();

	for (double z = 0; z < Z; z += dz)
		for (double y = -Y / 2 + z; y < Y / 2 - z; y += dy)
			for (double x = -X / 2 + z; x < X / 2 - z; x += dx)
				sum += dx * dy*dz;

	auto end = get_time::now();
	auto diff = end - start;
	cout << "구분구적법 계산량:\t" << chrono::duration_cast<ns>(diff).count() << endl << endl;
	return sum;
}

double circle(double r, int n)
{
	double sum = 0;
	auto start = get_time::now();
	for (int i = 1; i <= n; i++)
		sum += (1 - pow(double(i) / n, 2))*PI*pow(r, 3) / n;
	auto end = get_time::now();
	auto diff = end - start;
	cout << "구분구적법 계산량:\t" << chrono::duration_cast<ns>(diff).count() << endl << endl;
	return sum * 2;
}

double circle(double r, double dr, double dpi, double dtheta)
{
	double sum = 0;
	auto start = get_time::now();
	for (double theta = 0; theta <= 2 * PI; theta += dtheta)
		for (double pi = 0; pi <= PI; pi += dpi)
			for (double row = 0; row <= r; row += dr)
				sum += pow(row, 2)*sin(pi)*dtheta*dpi*dr;
	auto end = get_time::now();
	auto diff = end - start;
	cout << "구분구적법 계산량:\t" << chrono::duration_cast<ns>(diff).count() << endl << endl;
	return sum;
}

double integralsine(double dt)
{
	double sum = 0;
	auto start = get_time::now();
	for (double t = 0; t < 0.5; t += dt)
		sum += sin(2 * PI*t)*dt;
	auto end = get_time::now();
	auto diff = end - start;
	cout << "구분구적법 계산량:\t" << chrono::duration_cast<ns>(diff).count() << endl << endl;
	return sum;
}

double accuracy(double result1, double result2)
{
	return pow(result1 - result2, 2) / pow(result1, 2);
}
