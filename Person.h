#pragma once
#include <iostream>

using namespace std;

class Person {
private:
	string FirstName;
	string MiddleName;
	string LastName;
	int BirthDay;
public:
	Person() {
		FirstName = " ";
		MiddleName = " ";
		LastName = " ";
		BirthDay = 0;
	}
	Person(string FN,
		string MN,
		string LN,
		int BD) {
		FirstName = FN;
		MiddleName = MN;
		LastName = LN;
		BirthDay = BD;
	}
	~Person() {

	}

	string GetFirstName() {
		return FirstName;
	}

	string GetMiddleName() {
		return MiddleName;
	}

	string GetLastName() {
		return LastName;
	}

	string GetFullName() {
		string FullName = FirstName + ' ' + MiddleName + ' ' + LastName;
		return FullName;
	}

	string GetFIO() { // Фамилия.И.О.
		string FIO = LastName + ' ' + FirstName[0] + '.' + MiddleName[0] + '.';
		return FIO;
	}

	int GetBirthYear() {
		return BirthDay;
	}

	int GetAge(int year) { // вычислить возраст на заданный момент
		int Age = year - BirthDay;
		return Age;
	}

	bool operator== (Person y);
	bool operator!= (Person y);
};
ostream& operator<<(ostream& os, Person& x) {
	os << "[" << x.GetFirstName() << " " << x.GetMiddleName() << " " << x.GetLastName() << " Birth year:" << x.GetBirthYear() << "]";
	return os;
}

bool  Person::operator== (Person y) {
	if (this->FirstName == y.FirstName && this->MiddleName == y.MiddleName && this->LastName == y.LastName && this->BirthDay == y.BirthDay)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool  Person::operator!= (Person y) {
	return !(*this == y);
}