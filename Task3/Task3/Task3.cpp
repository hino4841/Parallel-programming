#include<iostream>
#include<limits>
#include <omp.h>
#include<random>
#include<iomanip>
using namespace std;

int main() {
	
	int x, y,e,tmp;
	static double Mat_As[100][100], Mat_Ap[100][100];
	int a,num;
	unsigned int seed;
	cout << "Please enter the number of rows of Matrix A" << endl;

	do
	{
		e = 0;
		cin >> x;
		tmp = cin.get();


		if (((tmp <48 || tmp>57) && tmp != 10) || (cin.fail()))
		{

			e = 1;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Please input only numbers " << endl;

		}
		if (e != 1 && x > 100) {
			cout << "Please enter a number  between 1 and 100" << endl;
			e = 1;
		}

	} while (e == 1);
	
	cout << "Please enter the number of columns of Matrix A" << endl;

	do
	{
		e = 0;
		cin >> y;
		tmp = cin.get();


		if (((tmp <48 || tmp>57) && tmp != 10) || (cin.fail()))
		{

			e = 1;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Please input only numbers " << endl;

		}
		if (e != 1 && y > 100) {
			cout << "Please enter a number  between 1 and 100" << endl;
			e = 1;
		}

	} while (e == 1);

	cout << "Please enter the seed value" << endl;
	cin >> seed;
	
	default_random_engine ran(seed);
	uniform_real_distribution<double> random(0.0, 1.0);
	/*Fetching the Matrix elements from the user*/
	
	
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {

			Mat_As[i][j] = random(ran);
		}
	}

	
#pragma omp parallel for
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			num = omp_get_num_threads();
			Mat_Ap[i][j] = random(ran);
		}
	}
	cout << "Randomly generated  Matrix A of size " << x << "x" << y << "(Sequencial programming)" << endl;
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {

			cout << setw(10) << left << Mat_As[i][j] << " ";
		}
		cout << "\n";
	}


	cout << "\n";
	cout << "Randomly generated Matrix A of size " << x << "x" << y << "(Parallel programming -Number of threads="<<num<<")" << endl;
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {

			cout << setw(10) << left << Mat_As[i][j] << " ";
		}
		cout << "\n";
	}
	cin >> a;
}
