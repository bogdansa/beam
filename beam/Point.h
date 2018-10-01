#pragma once

#include <iostream>

class Point
{
public:
	double x, y, z;
	/** ����������� �� ���������.*/
	Point();
	/** ����������� � �����������.*/
	Point(double X, double Y, double Z);
	/** ������������� �������.*/
	operator Point() const;
	/** ������������� �������� ==.*/
	bool operator == (Point point);
	/** ������������� �������� !=.*/
	bool operator != (Point point);
	/** ������������� �������� <.*/
	bool operator < (const Point & right) const;
	/** ������������� �������� >.*/
	bool operator > (const Point & right) const;
};
