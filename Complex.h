#pragma once
#include <iostream>
#include <cmath>

using namespace std;

class Complex
{
private:
	double Re, Im;
public:
	Complex();
	Complex(double x, double y);
	Complex(double x);
	~Complex();

	Complex operator+ (Complex y);
	Complex operator- (Complex y);
	Complex operator* (Complex y);
	Complex operator/ (Complex y);
	Complex& operator= (Complex y);
	bool operator== (Complex y);
	bool operator!= (Complex y);


	void prt();
	double getRe();
	double getIm();

};


ostream& operator<<(ostream& os, Complex& x);

#pragma once
