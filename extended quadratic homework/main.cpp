
// FILE: main.cpp (for CSC 307 Spring 2018 HW 2)

#include <iostream>    // Provides cout
#include <cstdlib>     // Provides EXIT_SUCCESS
#include "quadratic.h"
using namespace std;   // Allows all standard library items to be used

void testroots(double a, double b, double c)
{
	quadratic q = quadratic(a, b, c);
	int numroots = q.num_realroots();
	cout << "the quadratic expression with coefficients a, b, c " << q << " has " << numroots << " roots." << endl;
	if (numroots >= 1 && numroots <= 3)
	{
		cout << "    The roots are: ";
		if (numroots >= 1)
			cout << q.oneroot();
		if (numroots >= 2)
			cout << " and " << q.theotherroot();
		cout << endl;
	}
}

int main()
{
	quadratic q1 = quadratic();
	quadratic q2 = quadratic(-1.0, 1.1, 10.1);
	cout << q1 << endl;
	cout << q2 << endl;
	q1.change_coefficients(-q2.get_a(), q2.get_a(), 20.18);
	cout << q1.evaluate(1.0) << endl;
	cout << q2.evaluate(1.0) << endl;
	quadratic q3 = q1 + q2;
	quadratic q4 = -1.2*q1;
	cout << q3 << endl;
	cout << q4 << endl;
	cout << q3.evaluate(2.0) << " " << q4.evaluate(3.0) << endl;
	cout << q3.evaluate(1.0) + q4.evaluate(-1.0) << endl;
	cout << q4 + q3 << endl;
	cout << 2.0*q1 << endl;

	//** HW2 test cases **//
	testroots(0.0, 0.0, 0.0);	// test rule 1
	testroots(0.0, 0.0, 2.2);	// test rule 2
	testroots(0.0, 2.2, 0.0);	// test rule 3
	testroots(0.0, 2.2, -2.2);	// test rule 3
	testroots(10.0, 0.1, 1.0);	// test rule 4
	testroots(-4.0, 4.0, -1.0); // test rule 5
	testroots(-9.0, 4.0, 0.25);  // test rule 6

	return EXIT_SUCCESS;
}
