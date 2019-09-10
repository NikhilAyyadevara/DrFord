#include <bits/stdc++.h>
#include "soldier.h"



soldier::soldier(int a,int b)
{
	x=a;
	y=b;
}

int soldier::getX()
{
	return x;
}

int soldier::getY()
{
	return y;
}

void soldier::move(int a, int b)
{
	x=a;
	y=b;
}