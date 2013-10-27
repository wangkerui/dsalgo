#include <iostream>
#define MAX_VALUE 0x7fffffff
#define MIN_VALUE 0x80000000

#define add_a_b add(a, b)

using namespace std;

int add(int, int);

int main()
{
	int a, b;

	a = MAX_VALUE, b = 1;  // the max value plus one.
	add_a_b;

	a = MAX_VALUE, b = 0;  // the max value plus zero.
	add_a_b;

	a = MIN_VALUE, b = -1; // the min value plus negative one.
	add_a_b;

	a = MIN_VALUE, b = 0;  // the min value plus zero.
	add_a_b;

	a = MIN_VALUE;
	b = MAX_VALUE;         // the max and min value
	add_a_b;

	a = 3, b = 5;          // two positive integers
	add_a_b;

	a = -4, b = -9;        // two negative integers
	add_a_b;

	a = 13, b = -26;      // the negative one is greater than the positive.
	add_a_b;

	a = 8, b = -3;        // the negative one is less than the positive.
	add_a_b;

	return 0;
}

int add (int a, int b)
{
	int num1 = a, num2 = b, sum = 0, carry = 0, tmp = 0;
	do
	{
		sum = num1 ^ num2;
		carry = (num1 & num2) << 1;

		num1 = sum;
		num2 = carry;
	}while(num2 != 0);

	// check overflow
	bool overflow = false;
	if (a<0 && b<0 && (sum&0x80000000)!=0x80000000) overflow = true;
	if (a>0 && b>0 && (sum&0x80000000)!=0) overflow = true;
	
	if (overflow)
		cout << a << "+" << b << "=" << "\n\toverflow!" << endl;
	else
		cout << a << "+" << b << "=" << sum << endl;

	return sum;
}