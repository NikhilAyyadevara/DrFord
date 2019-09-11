#include <bits/stdc++.h>

using namespace std;

class soldier
{
	private:
		int x_coordinate;
		int y_coordinate;

	public:
		int getX();
		int getY();
		void move(int, int);
		soldier(int, int);
};