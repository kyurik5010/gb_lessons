#include <iostream>

using namespace std;

int main()
{
	int x, y;
	cin >> x;
	y = x;
	for(int i = 0; i < x; i++)
		x += x;
	cout << x << ", " << y*y;
	return 0;
}
