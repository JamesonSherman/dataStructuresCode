#ifndef QUADRATIC_FUNCS
#define QUADRATIC_FUNCS

#include <iostream>
#include <fstream>

class quadratic 
{
	friend quadratic operator+ (const quadratic& q1, const quadratic& q2);
	friend quadratic operator *(double r, const quadratic& q);

public:
	quadratic(double init_a = 0.0, double init_b = 0.0, double init_c = 0.0);
	double get_a() const;
	double get_b() const;
	double get_c() const;
	double evaluate(double x) const;
	void change_coefficients(double aa, double bb, double cc);
	int num_realroots();
	double oneroot();
	double theotherroot();
	
private:
	double a;
	double b;
	double c;

};

std::ostream& operator <<(std::ostream& outs, const quadratic& q);



#endif 
 