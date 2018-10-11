#pragma once

#include <iostream>

class MyPoint
{
public:
	double x, y, z;
	/** ����������� �� ���������.*/
	MyPoint();
	/** ����������� � �����������.*/
	MyPoint(double X, double Y, double Z);
	/** ������������� �������.*/
	operator MyPoint() const;
	/** ������������� �������� ==.*/
	bool operator == (MyPoint point);
	/** ������������� �������� !=.*/
	bool operator != (MyPoint point);
	/** ������������� �������� <.*/
	bool operator < (const MyPoint & right) const;
	/** ������������� �������� >.*/
	bool operator > (const MyPoint & right) const;
};
