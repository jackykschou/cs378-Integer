#include <iostream>
#include "Integer.h"

using namespace std;

int main()
{
	Integer<int, deque<int>> x(0);
	Integer<int, deque<int>> y(99);
	Integer<int, deque<int>> z;
	z = x/y;
	cout << x << " " << y << " " << z << endl;
	return 0;
}