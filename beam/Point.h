#pragma once

#include <iostream>

class MyPoint
{
public:
	double x, y, z;
	/** Конструктор по умолчанию.*/
	MyPoint();
	/** Конструктор с параметрами.*/
	MyPoint(double X, double Y, double Z);
	/** Перегруженный функтор.*/
	operator MyPoint() const;
	/** Перегруженный оператор ==.*/
	bool operator == (MyPoint point);
	/** Перегруженный оператор !=.*/
	bool operator != (MyPoint point);
	/** Перегруженный оператор <.*/
	bool operator < (const MyPoint & right) const;
	/** Перегруженный оператор >.*/
	bool operator > (const MyPoint & right) const;
};
