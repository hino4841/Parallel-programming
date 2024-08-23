#include<iostream>
#include<limits>
#include <omp.h>
#include <iomanip> 

using namespace std;

int main() {
	
	int tmp;
	double Mat_A[5][5], Mat_B[5][5], Mat_C[5][5], Mat_D[5][5]; //Declaration of Arrrays
	int num,a;
	int e,p = 0;
	
	/*Fetching the Matrix elements from the user*/

	cout << "Please enter the values of Matrix A of size 5x5" << endl;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cout << "A" << i+1 << "," << j+1<<"  :";  // Dispalys the particualr element to enter the value

			/*Validation of Input values*/
			
			do
			{
				e = 0;
				cin >> Mat_A[i][j];
				tmp = cin.get();
				
				
				if (((tmp <48 || tmp>57 )&& tmp!=10) || (cin.fail()))
					{
					
					e = 1;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Please input only numbers " << endl;
				
				}
			
			}while (e==1);
		
		}
	}
	/*Fetching the Matrix elements from the user*/
	cout << "Please enter the values of Matrix B of size 5x5" << endl;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cout << "B" << i + 1 << "," << j + 1 << "  :";    // Dispalys the particualr element to enter the value

			/*Validation of Input value*/
			

				do
				{
					e = 0;
					cin >> Mat_B[i][j];
					tmp = cin.get();


					if (((tmp < 48 || tmp>57) && tmp != 10) || (cin.fail()))
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

	/*Matrix multiplication on sequencial programming*/
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			Mat_C[i][j] = 0;
			for (int k = 0; k < 5; k++) {
				Mat_C[i][j] =Mat_C[i][j] + (Mat_A[i][k] * Mat_B[k][j]);
			}
		}
	}
	
	
	

	/*Matrix multiplication on parallel programming*/
#pragma omp parallel for shared(Mat_D)   
	for (int i = 0; i < 5; i++) {

		for (int j = 0; j < 5; j++) {
			Mat_D[i][j] = 0;

			for (int k = 0; k < 5; k++) {
				Mat_D[i][j] = Mat_D[i][j] + (Mat_A[i][k] * Mat_B[k][j]);
				num = omp_get_num_threads();
			}
		}
	}
	
	/*Displays A ,B and AB matrices*/
	cout << "Matrix A =" << endl;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {

			cout << setw(10) << right << Mat_A[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
	cout << "Matrix B =" << endl;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {

			cout << setw(10) << right << Mat_B[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
	cout << "Resultant Matrix of AB(sequencial) =" << endl;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			
			cout << setw(10) << right << Mat_C[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
	cout << "Resultant Matrix of AB(Parallel)(Number of threads ="<< num<<") =" << endl;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {

			cout << setw(10) << right << Mat_D[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
	cin >> a;

	
	

	return 0;
}