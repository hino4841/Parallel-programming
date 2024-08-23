#include<iostream>
#include<limits>
#include <omp.h>
#include <iomanip> 
#include<time.h>
using namespace std;

int main() {
	static int Mat_A[1000][1000], Mat_B[1000][1000], Mat_C[1000][1000], X_S[1000][1000], X_P[1000][1000]; //Declaration of Arrrays

	int num, a;
	int seed;
	int e = 0;
	clock_t seq_start,seq_dur;
	double Par_start,Par_dur;

	cout << "Please enter the seed value" << endl;
	cin >> seed;
	srand(seed);

	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < 1000; j++) {
			Mat_A[i][j] = rand();
		}

	}

	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < 1000; j++) {
			Mat_B[i][j] = rand();
		}

	}

	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < 1000; j++) {
			Mat_C[i][j] = rand();
		}

	}

	/*Matrix multiplication on parallel programming*/
	Par_start = omp_get_wtime();

#pragma omp parallel  for
	for (int i = 0; i < 1000; i++) {

		for (int j = 0; j < 1000; j++) {
			X_P[i][j] = 0;

			for (int k = 0; k < 1000; k++) {

				X_P[i][j] += (Mat_A[i][k] * Mat_B[k][j]);
			}


			X_P[i][j] += Mat_C[i][j];
		}
	}


	
	
	Par_dur = omp_get_wtime()-Par_start;
	cout << "parallel done" << endl;

	seq_start = clock();
	/*Matrix multiplication and summation in sequencial programming*/
	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < 1000; j++) {
			X_S[i][j] = 0;
			for (int k = 0; k < 1000; k++) {

				X_S[i][j] +=  (Mat_A[i][k] * Mat_B[k][j]);
			}

			X_S[i][j] +=  Mat_C[i][j];

		}
	}
	seq_dur = (double)(clock()-seq_start)/CLOCKS_PER_SEC;

	

	cout << "seq done" << endl;

	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < 1000; j++) {
			if (X_S[i][j] != X_P[i][j]) {
				cout << "Error" << endl;
			}
		}

	}
	cout<<"Time elapsed by parallel programming   = " << Par_dur << endl;
	cout<<"Time elapsed by sequencial programming = " << seq_dur << endl<<endl<<endl;
	cout << "Parallel programming is " << seq_dur / Par_dur << "  times faster than sequencial programming" << endl;
	cin >> a;

	return 0;

}

/*

//Displays A ,B and AB+C matrices
cout << "Matrix A =" << endl;
for (int i = 0; i < 1000; i++) {
	for (int j = 0; j < 1000; j++) {

		cout << setw(10) << left << Mat_A[i][j] << " ";
	}
	cout << "\n";
}
cout << "\n";
cout << "Matrix B =" << endl;
for (int i = 0; i < 1000; i++) {
	for (int j = 0; j < 1000; j++) {

		cout << setw(10) << left << Mat_B[i][j] << " ";
	}
	cout << "\n";
}

cout << "\n";
cout << "Matrix C =" << endl;
for (int i = 0; i < 1000; i++) {
	for (int j = 0; j < 1000; j++) {

		cout << setw(10) << left << Mat_C[i][j] << " ";
	}
	cout << "\n";
}

cout << "\n";
cout << "Resultant Matrix of AB+C (sequencial) =" << endl;
for (int i = 0; i < 1000; i++) {
	for (int j = 0; j < 1000; j++) {

		cout << setw(10) << left << X_S[i][j] << " ";
	}
	cout << "\n";
}
cout << "\n";

cout << "Resultant Matrix of AB+C (Parallel)(Number of threads =" << num << ") =" << endl;
for (int i = 0; i < 1000; i++) {
	for (int j = 0; j < 1000; j++) {

		cout << setw(10) << left << X_P[i][j] << " ";
	}
	cout << "\n";
}
cout << "\n";
cin >> a;

*/