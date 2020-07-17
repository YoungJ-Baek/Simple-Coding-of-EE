#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

#define PI 3.141592

int main()
{
	float t = 0;
	float f = 40;
	float fs = 30;
	float dt = 1 / fs;
	float T = 5. / 40.;

	ofstream out("test30.txt");

	if (!out) {
		cout << "Cannot open test.txt file.\n";
		return 1;
	}

	for (t; t < T; t += dt)
		out << t << " " << sin(f * 2 * PI * t) << endl;

	out.close();

	return 0;
}
