// FILE: quadratic.cpp (for CSC 307 Spring 2018 HW 1)
#include "quadratic.h"
#include <iostream>
#include <cmath>

std::ostream& operator <<(std::ostream& outs, const quadratic& q)
{
	outs << q.get_a() << " " << q.get_b() << " " << q.get_c();
	return outs;
}

quadratic operator+ (const quadratic & q1, const quadratic & q2)
{
	quadratic sum;
	double sum_a, sum_b, sum_c;

	sum_a = q1.get_a();
	sum_a += q2.get_a();
	sum_b = q1.get_b();
	sum_b += q2.get_b();
	sum_c = q1.get_c();
	sum_c += q2.get_c();
	sum.change_coefficients(sum_a, sum_b, sum_c);

	return sum;
}
quadratic operator *(double r, const quadratic& q)
{
	quadratic product;
	double prod_a, prod_b, prod_c;

	prod_a = q.get_a();
	prod_a *= r;
	prod_b = q.get_b();
	prod_b *= r;
	prod_c = q.get_c();
	prod_c *= r;
	product.change_coefficients(prod_a, prod_b, prod_c);

	return product;
}

double quadratic::get_a() const
{
	return a;
}
double quadratic::get_b() const
{
	return b;
}
double quadratic::get_c() const
{
	return c;
}

double quadratic::evaluate(double x) const
{
	double evald;

	evald = a*x*x + b*x + c;

	return evald;
}

void quadratic::change_coefficients(double aa, double bb, double cc)
{
	a = aa;
	b = bb;
	c = cc;

	return;
}

int quadratic::num_realroots()
{
	if (a == 0.0 && b == 0.0 && c == 0.0)
		return 3;

	else if (a == 0.0 && b == 0.0)
		return 0;

	else if (a == 0.0)
		return 1;

	else if ((b*b) < (4.0*a*c))
		return 0;

	else if ((b*b) == (4.0*a*c))
		return 1;

	else // ((b*b) > (4.0*a*c)) 
		return 2;
}

double quadratic::oneroot()
{
	double foo = 0.0, bar = 0.0;
	switch (quadratic::num_realroots())
	{
	case 1:

		if (a == 0.0)
		{
			foo = (-(c) / b);

			return (foo + 0.0); // Fix for -0
		}

		else // ((b*b) == (4.0*a*c))
		{
			foo = (-(b) / (2.0*a));

			return (foo + 0.0); // Fix for -0
		}

		break;

	case 2:
		//  ((b*b) > (4.0*a*c))

			foo = ((-(b)-std::sqrt((b*b) - (4.0*a*c))) / (2.0*a));
			bar = ((-(b)+std::sqrt((b*b) - (4.0*a*c))) / (2.0*a));

			if (foo < bar) return foo;
			else return bar;

	case 3:
		return 0;
		break;

	default:
		std::cout << "\n ERROR! oneroot() can NOT be called with zero roots! \n";
		return 0;
		break;
	}
}

double quadratic::theotherroot()
{
	if ((b*b) > (4.0*a*c))
	{
		double foo = 0.0, bar = 0.0;

		foo = ((-(b)-std::sqrt((b*b) - (4.0*a*c))) / (2.0*a));
		bar = ((-(b)+std::sqrt((b*b) - (4.0*a*c))) / (2.0*a));

		if (foo > bar) return foo;
		else return bar;
	}

	else //(quadratic::num_realroots() == 3)
	{
		return 0;
	}
}

quadratic::quadratic(double init_a, double init_b, double init_c)
{
	a = init_a;
	b = init_b;
	c = init_c;
}

