#include <iostream>
#include "Integer.h"

using namespace std;

int main()
{
	Integer<int> x("2");
	Integer<int> y("123");
	cout << x.pow(3000) << endl;
	return 0;
}