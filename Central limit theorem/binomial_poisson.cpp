#include <iostream>
#include <cstdlib>
#include <fstream>
#include <random>
#include <time.h>
#define PI 3.141592
using namespace std;

float factorial(float n);
double binomial(float n, float k, float p);
double Binomial(int n, int k, float p);
double poisson(float alpha, float x);

int main()
{
	srand((unsigned int)time(NULL));

	ofstream out("bnp.txt");

	float p = 0.1;
	const int n = 10000;
	const int simul = 100000;
	float alpha = n * p;

	double bino[n + 1] = { 0, };
	double poi[n + 1] = { 0, };
	double cal[n + 1] = { 0, };

	for (int i = 0; i < simul; i++) {
		int count = 0;
		for (int j = 0; j < n + 1; j++) {
			int x = rand() % 10;
			if (x == 1)count++;
		}
		cal[count]++;
	}

	for (int i = 0; i < n + 1; i++) {
		//bino[i] = binomial(n, i, p);
		//binomial calculation using recursion function
		bino[i] = Binomial(n, i, p);
		poi[i] = poisson(alpha, i);
	}

	double Eb = 0, Ep = 0, Ec = 0;

	for (int i = 0; i < n + 1; i++) {
		Eb += i * bino[i];
		Ep += i * poi[i];
		Ec += i * (float)cal[i] / simul;
		out << i << "\t" << bino[i] << "\t" << poi[i] << "\t" << cal[i] / simul << endl;
	}

	cout << "calculation:" << Ec << endl;
	cout << "Binomial:" << Eb << endl;
	cout << "Poisson:" << Ep << endl;

	out.close();

	return 0;
}

float factorial(float n)
{
	if (n == 1 || n == 0)return 1.0;
	else return n * factorial(n - 1);
}

double binomial(float n, float k, float p)
{
	return (factorial(n) / factorial(k) / factorial(n - k))*pow(p, k)*pow((1 - p), n - k);
}

double Binomial(int n, int k, float p)
{
	if (k == 0)return pow(1 - p, n);

	long double mul = 1;

	if (k > n - k)
		for (int i = 1; i <= n; i++) {
			if (i <= n - k) mul *= (long double)1 / i;
			else if (i <= k)mul *= (long double)1;
			else mul *= (long double)i;
		}
	else if (k == n - k)
		for (int i = 1; i <= n; i++) {
			if (i <= n - k) mul *= (long double)1 / i;
			else mul *= (long double)i;
		}
	else
		for (int i = 1; i <= n; i++) {
			if (i <= k) mul *= (long double)1 / i;
			else if (i <= n - k)mul *= (long double)1;
			else mul *= (long double)i;
		}

	return (double)mul* (long double)pow(p, k*0.5)*(long double)pow(p, k*0.5)*(long double)pow(1 - p, n - k);
}

double poisson(float alpha, float x)
{
	if (x == 0)return (double)exp(-alpha);
	float px = 1.0;
	for (int i = 1; i <= x; i++)
		px *= (long double)(alpha / (float)i)*(long double)pow((long double)exp(-alpha), (long double)1.0 / x);
	return px;
}
