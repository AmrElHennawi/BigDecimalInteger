#include "BigDecimalInt.h"

using namespace std;

int main()
{
	// Test constructor with string parameter
	BigDecimalInt num1("123456789012345678901234567890");
	cout << "num1 = " << num1 << endl;

	// Test constructor with int parameter
	BigDecimalInt num2("113456789011345678901134567890");
	cout << "num2 = " << num2 << endl;

	// Test addition
	BigDecimalInt num3 = num1 + num2;
	cout << "num1 + num2 = " << num3 << endl;

	// Test subtraction
	BigDecimalInt num4 = num2 - num1;
	cout << "num2 - num1 = " << num4 << endl;

	// Test less than
	if (num1 < num2)
		cout << "num1 is less than num2" << endl;
	else
		cout << "num2 is less than num1" << endl;

	// Test greater than
	if (num2 > num1)
		cout << "num2 is greater than num1" << endl;
	else
		cout << "num1 is greater than num2" << endl;

	// Test equality
	if (num1 == num2)
		cout << "num1 is equal to num2" << endl;
	else
		cout << "num1 is not equal to num2" << endl;

	// Test assignment
	BigDecimalInt num5 = num2;
	cout << "num5 (assigned from num2) = " << num5 << endl;

	// Test size and sign functions
	cout << "Size of num1: " << num1.size() << endl;
	cout << "Sign of num1: " << num1.sign() << endl;

	return 0;
}