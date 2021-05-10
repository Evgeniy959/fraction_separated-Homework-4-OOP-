// Разделить класс Fraction на файлы.Сделать это в ветке fraction_separated.
#pragma once
#include<iostream>
using namespace std;

#define tab "\t"

/////////////////////////////////////////////////////////////////////////////////////////////////
//////////////				CLASS DECLARATION - ОБЪЯВЛЕНИЕ КЛАССА				/////////////////

class Fraction; // Объявление класса
Fraction operator+(Fraction left, Fraction right); // Прототип оператора +
Fraction operator-(Fraction left, Fraction right);
Fraction operator*(Fraction left, Fraction right);
Fraction operator/(Fraction left, Fraction right);
bool operator==(Fraction left, Fraction right);
bool operator!=(Fraction left, Fraction right);
bool operator<=(Fraction left, Fraction right);
bool operator>=(Fraction left, Fraction right);
bool operator>(Fraction left, Fraction right);
bool operator<(Fraction left, Fraction right);
ostream& operator<<(ostream& os, const Fraction& obj);
istream& operator>>(istream& is, Fraction& obj);

class Fraction
{
	bool minus; // учитывает знак
	int integer; // целая часть дроби 
	int numerator; // числитель дроби 
	int denominator; // знаменатель дроби

public:
	bool get_minus()const;
	int get_integer()const;
	int get_numerator()const;
	int get_denominator()const;
	void set_minus(bool minus);
	void set_integer(int integer);
	void set_numerator(int numerator);
	void set_denominator(int denominator);
	Fraction& set_minus_to_number();
	Fraction& get_minus_from_number();

	//           Consctructors:
	Fraction();
	Fraction(int integer);
	Fraction(int numerator, int denominator);
	Fraction(int integer, int numerator, int denominator);
	~Fraction();
	Fraction& operator=(const Fraction& other);
	Fraction& operator+=(const Fraction& other);
	Fraction& operator-=(const Fraction& other);
	Fraction& operator*=(const Fraction& other);
	Fraction& operator/=(const Fraction& other);

	//              Increment/Decrement
	Fraction& operator++();
	Fraction operator++(int);
	Fraction& operator--();
	Fraction operator--(int);

	//                    Methods:

	void to_proper();
	void to_improper();
	Fraction& reduce();
};
//////////////						CLASS DECLARATION END						/////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////