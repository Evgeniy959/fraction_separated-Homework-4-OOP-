#include"Fraction.h"
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