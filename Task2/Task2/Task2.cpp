#include<iostream>
#include<limits>
#include <omp.h>
#include <iomanip> 
using namespace std;

int main() {
	int Mat_A[5][4], Mat_B[4][3], Mat_C[5][3], X_S[5][3], X_P[5][3]; //Declaration of Arrrays
	int num, a;
	int tmp;
	int e = 0;
	/*Fetching the Matrix elements from the user*/

	cout << "Please enter the values of Matrix A of size 5x4" << endl;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++) {
			cout << "A" << i + 1 << "," << j + 1 << "  :";  // Dispalys the particualr element to enter the value

															/*Validation of Input values*/

			do
			{
				e = 0;
				cin >> Mat_A[i][j];
				tmp = cin.get();


				if (((tmp <48 || tmp>57) && tmp != 10) || (cin.fail()))
				{

					e = 1;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Please input only numbers " << endl;

				}

			} while (e == 1);

		}
	}
	
	/*Fetching the Matrix elements from the user*/
	cout << "Please enter the values of Matrix B of size 4x3" << endl;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			cout << "B" << i + 1 << "," << j + 1 << "  :";    // Dispalys the particualr element to enter the value

															  /*Validation of Input value*/
			do
			{
				e = 0;
				cin >> Mat_B[i][j];
				tmp = cin.get();


				if (((tmp <48 || tmp>57) && tmp != 10) || (cin.fail()))
				{

					e = 1;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Please input only numbers " << endl;

				}

			} while (e == 1);
		}
	}
	
	/*Fetching the Matrix elements from the user*/
	cout << "Please enter the values of Matrix C of size 5x3" << endl;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 3; j++) {
			cout << "C" << i + 1 << "," << j + 1 << "  :";    // Dispalys the particualr element to enter the value

															  /*Validation of Input value*/
			do
			{
				e = 0;
				cin >> Mat_C[i][j];
				tmp = cin.get();


				if (((tmp <48 || tmp>57) && tmp != 10) || (cin.fail()))
				{

					e = 1;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Please input only numbers " << endl;

				}

			} while (e == 1);
		}
	}
	
	system("CLS"); //Clears the console

				   /*Matrix multiplication and summation in sequencial programming*/
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 3; j++) {
			X_S[i][j] = 0;
				for (int k = 0; k < 4; k++) {
			
					X_S[i][j] = X_S[i][j] + (Mat_A[i][k] * Mat_B[k][j]);
				}
			
			X_S[i][j] = X_S[i][j] + Mat_C[i][j];

		}
	}


	

	/*Matrix multiplication on parallel programming*/
#pragma omp parallel for shared(X_P)   
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 3; j++) {
			X_P[i][j] = 0;
			for (int k = 0; k < 4; k++) {
				num = omp_get_num_threads();
				X_P[i][j] = X_P[i][j] + (Mat_A[i][k] * Mat_B[k][j]);
			}


			X_P[i][j] = X_P[i][j] + Mat_C[i][j];
		}
	}

	/*Displays A ,B and AB+C matrices*/
	cout << "Matrix A =" << endl;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++) {

			cout << setw(10) << left << Mat_A[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
	cout << "Matrix B =" << endl;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {

			cout << setw(10) << left << Mat_B[i][j] << " ";
		}
		cout << "\n";
	}

	cout << "\n";
	cout << "Matrix C =" << endl;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {

			cout << setw(10) << left << Mat_C[i][j] << " ";
		}
		cout << "\n";
	}

	cout << "\n";
	cout << "Resultant Matrix of AB+C (sequencial) =" << endl;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 3; j++) {

			cout << setw(10) << left << X_S[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";

	cout << "Resultant Matrix of AB+C (Parallel)(Number of threads =" << num << ") =" << endl;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 3; j++) {

			cout << setw(10) << left << X_P[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
	cin >> a;


	return 0;
}