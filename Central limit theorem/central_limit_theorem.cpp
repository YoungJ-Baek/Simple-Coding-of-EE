#include <iostream>
#include <cstdlib>
#include <fstream>
#include <random>
#include <time.h>
#define PI 3.141592
using namespace std;

float gaussian(float x, float m, float p);

int main()
{
	ofstream fout("100000.txt");
	int hit[501] = { 0, };
	double Ntry = 100000, ntry = 100;
	for (int i = 0; i < Ntry; i++)
	{
		int sum = 0;
		for (int j = 0; j < ntry; j++)
			sum += rand() % 6;
		hit[sum]++;
	}
	double total = 0;
	for (int i = 0; i < 501; i++) {
		fout << i + 100 << "\t" << hit[i]/Ntry << endl;
		total += i*hit[i]/Ntry;
	}
	double mean = total;
	total = 0;
	for (int i = 0; i < 501; i++) {
		total += (i - mean)*(i - mean)*hit[i] / Ntry;
	}
	double var = total;
	double sig = sqrt(var);

	cout << "mean:" << mean << endl;
	cout << "var:" << var << endl;
	cout << "sigma:" << sig << endl;

	fout.close();

	ofstream g("gaussian.txt");

	for (int i = 0; i < 501; i++)  g << i + 100 << "\t" << gaussian(i, mean, sig) << endl;

	g.close();
	return 0;
}

float gaussian(float x, float m, float p)
{
	float result;

	result = (1 / sqrt(2 * PI * p * p)) * exp(-(x - m) * (x - m) / (2 * p * p));

	return result;
}
