#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <ctime>

using namespace std;

float gaussian(float x, float y, float mux, float muy, float sigx, float sigy, float peak);
float fxy(float x, float y);
float dfxydx(float x, float y, float dx);
float dfxydy(float x, float y, float dy);
float EE(float x, float x1, float y, float y1);

void main() {
	srand(time(NULL));
	ofstream textout("peak1.txt");

	float psi = 0.005;
	float eta = 0.0001;//에러범위
	float dx = 0.001, dy = 0.001;
	float x0 = rand() % 7 - 3, x1 = x0 + 0.1, y0 = rand() % 7 - 3, y1 = y0 + 0.1;
	while (abs(x0) > 3 || abs(x1) > 3 || abs(y0) > 3 || abs(y1) > 3) { x0 = rand() % 7 - 3; x1 = x0 + 0.1; y0 = rand() % 7 - 3; y1 = y0 + 0.1; }
	int iteration = 0;

	float temp_x = x1;
	float temp_y = y1;

	textout << "psi\t" << psi << "\t" << "eta\t" << eta << "\t" << "dx\t" << dx << "\t" << "dy\t" << dy << endl << endl;
	while (EE(x0, x1, y0, y1) > eta && iteration < 1000/* && x0>-3 && x0<3 && y0>-3 && y0<3 && x1>-3 && x1<3 && y1>-3 && y1 < 3*/)
	{
		x0 = x1;
		y0 = y1;
		x1 = x0 + psi * dfxydx(x0, y0, dx);
		y1 = y0 + psi * dfxydy(x0, y0, dy);
		iteration++;
		textout << x0 << "\t" << y0 << "\t" << fxy(x1, y1) << endl;
		cout << setw(10) << x0 << setw(10) << setw(10) << y0 << setw(10) << setw(10) << fxy(x1, y1) << endl;
	}
	cout << setw(10) << iteration << "-th " << setw(10) << x1 << setw(10) << y1 << setw(10) << fxy(x1, y1) << endl;
	//textout << iteration << "-th " << x1 << "\t" << y1 << "\t" << fxy(x1, y1) << endl;
	textout.close();
	cout << setw(10) << fxy(-1, -1) << setw(20) << fxy(1, 1) << setw(20) << fxy(x1, y1) << endl;
	cout << setw(10) << temp_x << setw(10) << temp_y << endl;
}
float gaussian(float x, float y, float mux, float muy, float sigx, float sigy, float peak)
{
	return (peak * exp(-pow((x - mux) / sigx, 2.0) - pow((y - muy) / sigy, 2.0)));
}
float  fxy(float x, float y) {
	return (gaussian(x, y, 1., 1., 1., 2., 4) + gaussian(x, y, -1, -1., 1., 1., 2));
}

float dfxydx(float x, float y, float dx)
{
	return (fxy(x + dx, y) - fxy(x, y)) / dx;
}
float dfxydy(float x, float y, float dy)
{
	return (fxy(x, y + dy) - fxy(x, y)) / dy;
}

float EE(float x, float x1, float y, float y1)
{
	return sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));
}
