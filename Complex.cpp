#include <iostream>
#include <cmath>
#include "Complex.h"

using namespace std;

Complex::Complex() {
	Complex::Re = 0;
	Complex::Im = 0;
}

Complex::Complex(double x, double y) {
	Complex::Re = x;
	Complex::Im = y;
}

Complex::Complex(double x) {
	Complex::Re = x;
	Complex::Im = 0;
}

Complex::~Complex() {}

Complex Complex::operator+ (Complex y) {
	return  Complex::Complex(this->Re + y.Re, this->Im + y.Im);
}
Complex Complex::operator- (Complex y) {
	return  Complex::Complex(this->Re - y.Re, this->Im - y.Im);
}
Complex Complex::operator* (Complex y) {
	return  Complex::Complex(this->Re * y.Re - this->Im * y.Im, this->Re * y.Im + this->Im * y.Re);;
}
Complex Complex::operator/ (Complex y) {
	return Complex::Complex((this->Re * y.Re + this->Im * y.Im) / (y.Re * y.Re + y.Im * y.Im), (y.Re * this->Im - this->Re * y.Im) / (y.Re * y.Re + y.Im * y.Im));
}
Complex& Complex::operator= (Complex y) {
	Complex::Re = y.Re;
	Complex::Im = y.Im;
	return *this;
}


bool Complex::operator== (Complex y) {
	if (this->Re == y.Re && this->Im == y.Im)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Complex::operator!= (Complex y) {
	if (this->Re == y.Re && this->Im == y.Im)
	{
		return false;
	}
	else
	{
		return true;
	}
}

double Complex::getRe() {
	return Complex::Re;
}

double Complex::getIm() {
	return Complex::Im;
}

void Complex::prt() {
	cout << Complex::Re << " + i*" << Complex::Im;
}

ostream& operator<<(ostream& os, Complex& x) {
	os << x.getRe() << " + i*" << x.getIm();
	return os;
}