#include <iostream>
#include "Integer.h"

using namespace std;

int main()
{
	Integer<int> x("10");
	Integer<int> y = 100;
	Integer<int> z = 0;
	z = (x * y);
	x = x.pow(10);
	cout << x << " " << y << " " << z << endl;
	return 0;
}