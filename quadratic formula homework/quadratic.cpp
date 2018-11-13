// FILE: quadratic.cpp (for CSC 307 Spring 2018 HW 1)
#include "quadratic.h"
#include <iostream>

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

quadratic::quadratic(double init_a, double init_b, double init_c)
{
	a = init_a;
	b = init_b;
	c = init_c;
}

