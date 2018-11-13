// FILE: main.cpp (for CSC 307 Spring 2018 HW 1)


#include <iostream>    // Provides cout
#include <cstdlib>     // Provides EXIT_SUCCESS
#include "quadratic.h"
using namespace std;   // Allows all standard library items to be used

int main()
{
	quadratic q1 = quadratic();
	quadratic q2 = quadratic(-1.0);
	cout << q1 << endl;
	cout << q2 << endl;
	q1.change_coefficients(1.0, 3.3, -5.2);
	cout << q1.evaluate(1.0) << endl;
	cout << q2.evaluate(1.0) << endl;
	quadratic q3 = q1 + q2;
	quadratic q4 = -1.1*q1;
	cout << q3 << endl;
	cout << q4 << endl;
	cout << q3.evaluate(2.0) << " " << q4.evaluate(3.0) << endl;
	cout << q3.evaluate(1.0) + q4.evaluate(-1.0) << endl;
	cout << q4 + q3 << endl;
	cout << 2.0*q1 << endl;
	//system("pause");
	return EXIT_SUCCESS;
}
