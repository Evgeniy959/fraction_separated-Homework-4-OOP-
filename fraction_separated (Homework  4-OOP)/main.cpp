// Разделить класс Fraction на файлы.Сделать это в ветке fraction_separated.

#include<iostream>
using namespace std;

#define tab "\t"

class Fraction; // Объявление класса
Fraction operator+(Fraction left, Fraction right); // Прототип оператора +
Fraction operator-(Fraction left, Fraction right);
Fraction operator*(Fraction left, Fraction right);
Fraction operator/(Fraction left, Fraction right);

class Fraction
{
	bool minus; // учитывает знак
	int integer; // целая часть дроби 
	int numerator; // числитель дроби 
	int denominator; // знаменатель дроби

public:
	bool get_minus()const
	{
		return minus;
	}
	int get_integer()const
	{
		return integer;
	}
	int get_numerator()const
	{
		return numerator;
	}
	int get_denominator()const
	{

		return denominator;
	}
	void set_minus(bool minus)
	{
		this->minus = minus;
	}
	void set_integer(int integer)
	{
		this->integer = integer;
	}
	void set_numerator(int numerator)
	{
		this->numerator = numerator;
	}
	void set_denominator(int denominator)
	{
		if (denominator == 0)denominator = 1;
		else this->denominator = denominator;
	}
	/////////////////////////////////////////////////
	Fraction& set_minus_to_number()
	{
		if (minus)
		{
			if (integer)integer = -integer;
			else numerator = -numerator;
			minus = false;
		}
		return *this;
	}
	Fraction& get_minus_from_number()
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
	Fraction()
	{
		this->minus = false;
		this->integer = 0;
		this->numerator = 0;
		this->denominator = 1;
#ifdef DEBUG
		cout << "DefaultConstructor:\t" << this << endl;
#endif // DEBUG

	}
	Fraction(int integer)
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
	Fraction(int numerator, int denominator)
	{
		this->minus = false;
		this->integer = 0;
		this->numerator = numerator;
		this->set_denominator(denominator);
		if (numerator < 0)
		{
			minus = true;
			this->numerator = -numerator;
		}
#ifdef DEBUG
		cout << "Constructor2:\t" << this << endl;
#endif // DEBUG

	}
	Fraction(int integer, int numerator, int denominator)
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
#ifdef DEBUG
		cout << "Constructor3:\t" << this << endl;
#endif // DEBUG

	}
	~Fraction()
	{
#ifdef DEBUG
		cout << "Destructor:\t" << this << endl;
#endif // DEBUG
	}
	Fraction& operator=(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
#ifdef DEBUG
		cout << "CopyAssignment:\t" << this << endl;
#endif // DEBUG

		return *this;
	}
	Fraction& operator+=(const Fraction& other)
	{
		return *this = *this + other;
	}
	Fraction& operator-=(const Fraction& other)
	{
		return *this = *this - other;
	}
	Fraction& operator*=(const Fraction& other)
	{
		return *this = *this*other;
	}
	Fraction& operator/=(const Fraction& other)
	{
		return *this = *this / other;
	}

	//              Increment/Decrement
	Fraction& operator++()
	{
		this->integer++;
		return *this;
	}

	Fraction operator++(int)
	{
		Fraction old = *this;
		this->integer++;
		return old;
	}

	Fraction& operator--()
	{
		this->integer--;
		return *this;
	}

	Fraction operator--(int)
	{
		Fraction old = *this;
		this->integer--;
		return old;
	}

	//                    Methods:

	void to_proper()
	{
		get_minus_from_number();
		integer += numerator / denominator;
		numerator %= denominator;
	}
	void to_improper()
	{
		get_minus_from_number();
		numerator += integer * denominator;
		integer = 0;
	}

	Fraction& reduce()
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
};

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

//#define CONSTRUCTOR_CHECK
void main()
{
	setlocale(LC_ALL, "");
#ifdef CONSTRUCTOR_CHECK
	Fraction A; // Default constructor
	cout << A << endl;
	Fraction B = 5; // Single-argument constructor
	cout << B << endl;
	Fraction C(1, 2);
	cout << C << endl;
	Fraction D(2, 3, 4);
	cout << D << endl;
#endif // CONSTRUCTOR_CHECK
	Fraction C;
	cout << "Введите дробь 'C' в формате x/y: "; cin >> C;
	cout << "C = "; cout << C;
	//Fraction C(7, 2); 
	cout << " Переводим неправильную дробь в правильную: " << C << " - ";
	C.to_proper();
	cout << C << endl;
	cout << "Переводим правильную дробь в неправильную: " << C << " - ";
	C.to_improper();
	cout << C << endl;
	Fraction A(2, 3, 4);
	Fraction B(5, 6, 7);
	cout << "A = " << A << tab << "B = " << B << endl;
	cout << "Значение выражения (A+B) равно : " << A << " + " << B << " = " << A + B << endl;
	cout << "Значение выражения (B-A) равно : " << B << " - " << A << " = " << B - A << endl;
	cout << "Значение выражения (A-A) равно : " << A << " - " << A << " = " << A - A << endl;
	cout << "Значение выражения (A-B) равно : " << A << " - " << B << " = " << A - B << endl;
	cout << "Значение выражения (A*B) равно : " << A << " * " << B << " = " << A * B << endl;
	cout << "Значение выражения (A/B) равно : " << A << " / " << B << " = " << A / B << endl;
	Fraction S(2, 3, 4);
	Fraction K(5, 6, 7);
	cout << "S = " << S << tab << "K = " << K << endl;
	S += K;
	cout << "Значение выражения (S += K) равно " << S << endl;
	S -= K;
	cout << "Значение выражения (S -= K) равно " << S << endl;
	S *= K;
	cout << "Значение выражения (S *= K) равно " << S << endl;
	S /= K;
	cout << "Значение выражения (S /= K) равно " << S << endl;
	Fraction reduce(5, 10);
	cout << "Сокращение дроби (5/10) равно " << reduce.reduce() << endl;
	cout << "Сокращение дроби (3/5) равно " << Fraction(3, 5).reduce() << endl;
	Fraction i(2, 3, 4);
	cout << "i = " << i << endl;
	cout << "Значение выражения (++i) равно : " << ++i << endl;
	cout << "Значение выражения (i++) равно : " << i++ << endl;
	cout << "Значение выражения (--i) равно : " << --i << endl;
	cout << "Значение выражения (i--) равно : " << i-- << endl;
	Fraction a(2, 3, 4);
	Fraction b(5, 6, 7);
	cout << "a = " << a << tab << "b = " << b << endl;
	cout << "Значение выражения (a == b) равно : " << (a == b) << endl;
	cout << "Значение выражения (a != b) равно : " << (a != b) << endl;
	cout << "Значение выражения (a <= b) равно : " << (a <= b) << endl;
	cout << "Значение выражения (a >= b) равно : " << (a >= b) << endl;
	cout << "Значение выражения (a > b) равно : " << (a > b) << endl;
	cout << "Значение выражения (a < b) равно : " << (a < b) << endl;
}