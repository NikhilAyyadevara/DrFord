//#include <bits/stdc++.h>
#include "soldier.h"

soldier::soldier(int a,int b)
{
	x_coordinate=a;
	y_coordinate=b;
}

int soldier::getX()
{
	return x_coordinate;
}

int soldier::getY()
{
	return y_coordinate;
}

void soldier::move(int a, int b)
{
	x_coordinate=a;
	y_coordinate=b;
}

