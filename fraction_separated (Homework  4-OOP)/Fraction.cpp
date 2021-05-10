#include"Fraction.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
//////////////				CLASS DEFINITION - ОПРЕДЕЛЕНИЕ КЛАССА				/////////////////

bool Fraction::get_minus()const
{
	return minus;
}
int Fraction::get_integer()const
{
	return integer;
}
int Fraction::get_numerator()const
{
	return numerator;
}
int Fraction::get_denominator()const
{

	return denominator;
}
void Fraction::set_minus(bool minus)
{
	this->minus = minus;
}
void Fraction::set_integer(int integer)
{
	this->integer = integer;
}
void Fraction::set_numerator(int numerator)
{
	this->numerator = numerator;
}
void Fraction::set_denominator(int denominator)
{
	if (denominator == 0)denominator = 1;
	else this->denominator = denominator;
}
/////////////////////////////////////////////////
Fraction& Fraction::set_minus_to_number()
{
	if (minus)
	{
		if (integer)integer = -integer;
		else numerator = -numerator;
		minus = false;
	}
	return *this;
}
Fraction& Fraction::get_minus_from_number()
{
	if (integer < 0)
	{
		integer = -integer;
		minus = true;
	}
	if (numerator < 0)
	{
		numerator = -numerator;
		minus = true;
	}
	return *this;
}
/////////////////////////////////////////////////

//           Consctructors:
Fraction::Fraction() :minus(false), integer(0), numerator(0), denominator(1)
{

#ifdef DEBUG
	cout << "DefaultConstructor:\t" << this << endl;
#endif // DEBUG

}
Fraction::Fraction(int integer) //:Fraction(integer)
{
	this->minus = false;
	this->integer = integer;
	this->numerator = 0;
	this->denominator = 1;
	if (integer < 0)
	{
		minus = true;
		this->integer = -integer;
	}
#ifdef DEBUG
	cout << "Constructor1:\t" << this << endl;
#endif // DEBUG
}
Fraction::Fraction(int numerator, int denominator) :Fraction(numerator)
{
	if (numerator < 0)
	{
		minus = true;
		this->numerator = -numerator;
	}
#ifdef DEBUG
	cout << "Constructor2:\t" << this << endl;
#endif // DEBUG

}
Fraction::Fraction(int integer, int numerator, int denominator) //:Fraction(numerator), Fraction(integer)
{
	this->minus = false;
	this->integer = integer;
	this->numerator = numerator;
	this->set_denominator(denominator);
	if (integer < 0)
	{
		minus = true;
		this->integer = -integer;
	}
	if (numerator < 0)
	{
		minus = true;
		this->numerator = -numerator;
	}
	cout << "Constructor3:\t" << this << endl;

}
Fraction::~Fraction()
{
	cout << "Destructor:\t" << this << endl;
}
Fraction& Fraction::operator=(const Fraction& other)
{
	this->integer = other.integer;
	this->numerator = other.numerator;
	this->denominator = other.denominator;
#ifdef DEBUG
	cout << "CopyAssignment:\t" << this << endl;
#endif // DEBUG

	return *this;
}
Fraction& Fraction::operator+=(const Fraction& other)
{
	return *this = *this + other;
}
Fraction& Fraction::operator-=(const Fraction& other)
{
	return *this = *this - other;
}
Fraction& Fraction::operator*=(const Fraction& other)
{
	return *this = *this*other;
}
Fraction& Fraction::operator/=(const Fraction& other)
{
	return *this = *this / other;
}

//              Increment/Decrement
Fraction& Fraction::operator++()
{
	this->integer++;
	return *this;
}

Fraction Fraction::operator++(int)
{
	Fraction old = *this;
	this->integer++;
	return old;
}

Fraction& Fraction::operator--()
{
	this->integer--;
	return *this;
}

Fraction Fraction::operator--(int)
{
	Fraction old = *this;
	this->integer--;
	return old;
}

//                    Methods:

void Fraction::to_proper()
{
	get_minus_from_number();
	integer += numerator / denominator;
	numerator %= denominator;
}
void Fraction::to_improper()
{
	get_minus_from_number();
	numerator += integer * denominator;
	integer = 0;
}

Fraction& Fraction::reduce()
{
	if (numerator == 0) return *this;
	int more, less, rest;
	//Выясняем кто больше числитель или знаменатель:
	if (numerator > denominator) more = numerator, less = denominator;
	else less = numerator, more = denominator;
	//Находим наибольший общий делитель;
	do
	{
		rest = more % less;
		more = less;
		less = rest;
	} while (rest);
	int GCD = more; //Наибольший общий делитель
	//Сокращаем дробь:
	numerator /= GCD;
	denominator /= GCD;
	return *this;
}

Fraction operator+(Fraction left, Fraction right)
{
	left.to_proper();
	right.to_proper();
	left.set_minus_to_number();
	right.set_minus_to_number();
	Fraction result;
	result.set_integer(left.get_integer() + right.get_integer());
	result.set_numerator(left.get_numerator()*right.get_denominator() + right.get_numerator()*left.get_denominator());
	result.set_denominator(left.get_denominator()*right.get_denominator());
	result.to_proper();
	result.get_minus_from_number();
	result.reduce();
	return result;
}
Fraction operator-(Fraction left, Fraction right)
{
	left.to_proper();
	right.to_proper();
	left.set_minus_to_number();
	right.set_minus_to_number();
	return Fraction
	(
		left.get_integer() - right.get_integer(),
		left.get_numerator()*right.get_denominator() - right.get_numerator()*left.get_denominator(),
		left.get_denominator()*right.get_denominator()
	).get_minus_from_number().reduce();
}

Fraction operator*(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	left.set_minus_to_number();
	right.set_minus_to_number();
	return Fraction
	(
		left.get_numerator()*right.get_numerator(),
		left.get_denominator()*right.get_denominator()
	).get_minus_from_number().reduce();

}
Fraction operator/(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	Fraction result
	(
		left.get_numerator()*right.get_denominator(),
		right.get_numerator()*left.get_denominator()
	); result.reduce();
	if (left.get_minus() || right.get_minus())result.set_minus(true);
	if (left.get_minus() && right.get_minus())result.set_minus(false);
	return result;
}

/*------------------------------------------------------------*/
bool operator==(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	left.set_numerator(left.get_numerator() * right.get_denominator());
	right.set_numerator(right.get_numerator() * left.get_denominator());
	return left.get_numerator() == right.get_numerator();
}
bool operator!=(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	left.set_numerator(left.get_numerator() * right.get_denominator());
	right.set_numerator(right.get_numerator() * left.get_denominator());
	return left.get_numerator() != right.get_numerator();
}
bool operator<=(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	left.set_numerator(left.get_numerator() * right.get_denominator());
	right.set_numerator(right.get_numerator() * left.get_denominator());
	return left.get_numerator() <= right.get_numerator();
}
bool operator>=(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	left.set_numerator(left.get_numerator() * right.get_denominator());
	right.set_numerator(right.get_numerator() * left.get_denominator());
	return left.get_numerator() >= right.get_numerator();
}
bool operator>(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	left.set_numerator(left.get_numerator() * right.get_denominator());
	right.set_numerator(right.get_numerator() * left.get_denominator());
	return left.get_numerator() > right.get_numerator();
}
bool operator<(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	left.set_numerator(left.get_numerator() * right.get_denominator());
	right.set_numerator(right.get_numerator() * left.get_denominator());
	return left.get_numerator() < right.get_numerator();
}
/*-------------------------------------------------------------*/

ostream& operator<<(ostream& os, const Fraction& obj)
{
	if (obj.get_minus()) os << " (-";
	if (obj.get_integer()) os << obj.get_integer();
	if (obj.get_integer() && obj.get_numerator())os << "(";
	if (obj.get_numerator())os << obj.get_numerator() << "/" << obj.get_denominator();
	if (obj.get_integer() && obj.get_numerator())os << ")";
	if (obj.get_integer() == 0 && obj.get_numerator() == 0)os << 0;
	if (obj.get_minus()) os << ")";
	return os;
}
istream& operator>>(istream& is, Fraction& obj)
{
	int x, y;
	char c;
	is >> x >> c >> y;
	obj.set_integer(0);
	obj.set_numerator(x);
	obj.set_denominator(y);
	return is;
}
//////////////						CLASS DEFINITION END						/////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
