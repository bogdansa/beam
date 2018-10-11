#include "stdafx.h"
#include "Point.h"

/** Конструктор по умолчанию.*/
MyPoint::MyPoint()
{
	x = 0;
	y = 0;
	z = 0;
}

/** Конструктор с параметрами.*/
MyPoint::MyPoint(double X, double Y, double Z)
{
	x = X;
	y = Y;
	z = Z;
};

/** Перегруженный функтор.*/
MyPoint::operator MyPoint() const
{ 
	return MyPoint(x, y, z);
};

/** Перегруженный оператор ==.*/
bool MyPoint::operator == (MyPoint point)
{
	double diffX = abs(x - point.x);
	double diffY = abs(y - point.y);
	
	return ((diffX < 1.e-15) && (diffY < 1.e-15)) ? true : false;
};

/** Перегруженный оператор !=.*/
bool MyPoint::operator != (MyPoint point)
{
	return (*this == point) ? false : true;
};

/** Перегруженный оператор <.*/
bool MyPoint::operator < (const MyPoint & right) const
{
	double r1 = x * x + y * y;
	double r2 = right.x * right.x + right.y * right.y;
	double alpha1 = atan2(y, x);

	double alpha2 = atan2(right.y, right.x);
	if (r1 < r2)
	{
		return true;
	}
	else
	{
		//if ((abs(r1 - r2) < 1.e-15))
		if ((abs(r1 - r2) == 0))
		{
			return (alpha1 < alpha2) ? true : false;
		}
		else
		{
			return false;
		}
	}
};

/** Перегруженный оператор >.*/
bool MyPoint::operator > (const MyPoint & right) const
{
	double r1 = x * x + y * y;
	double r2 = right.x * right.x + right.y * right.y;
	double alpha1 = atan2(y, x);

	double alpha2 = atan2(right.y, right.x);
	if (r1 > r2)
	{
		return true;
	}
	else
	{
		//if ((abs(r1 - r2) < 1.e-15))
		if ((abs(r1 - r2) == 0))
		{
			return (alpha1 > alpha2) ? true : false;
		}
		else
		{
			return false;
		}
	}
};
