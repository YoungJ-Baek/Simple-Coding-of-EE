#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#define pi 3.141592
#define f0 1
#define f1 2
using namespace std;

float fxy(float x, float y);
float dfxydx(float x, float y, float dx);
float dfxydy(float x, float y, float dy);
float EE(float x0, float y0, float x1, float y1);

int main()
{
	srand(time(NULL));
	float psi = 0.001, eta = 0.0001, dx = 0.01, dy = 0.01;
	float xi1 = rand() % 9 / 10. + 0.1, yi1 = rand() % 9 / 10. + 0.1;
	cout << xi1 << " " << yi1 << endl;
	float xi0 = xi1 - 0.05, yi0 = yi1 - 0.05;
	int iteration = 0;

	while (EE(xi0, yi0, xi1, yi1) > eta&&iteration < 1000 && xi1>0 && xi1 < 1 && yi1>0 && yi1 < 1 && xi0>0 && xi0 < 1 && yi0>0 && yi0 < 1) {
		xi0 = xi1;
		yi0 = yi1;
		xi1 -= psi * dfxydx(xi0, yi0, dx);
		yi1 -= psi * dfxydy(xi0, yi0, dy);
		cout << setw(10) << xi0 << setw(10) << yi0 << " >> " << setw(10) << xi1 << setw(10) << yi1;
		cout << setw(10) << fxy(xi0, yi0) << setw(10) << fxy(xi1, yi1) << endl;
		iteration++;
	}
	cout << iteration << "-th E = " << EE(xi0, yi0, xi1, yi1) << endl;
	return 0;
}

float fxy(float x, float y) { return sin(2 * pi*f0*x)*sin(4 * pi*f1*y); }
float dfxydx(float x, float y, float dx) { return (fxy(x + dx, y) - fxy(x, y)) / dx; }
float dfxydy(float x, float y, float dy) { return (fxy(x, y + dy) - fxy(x, y)) / dy; }
float EE(float x0, float y0, float x1, float y1) { return sqrt((x0 - x1)*(x0 - x1) + (y0 - y1)*(y0 - y1)); }
