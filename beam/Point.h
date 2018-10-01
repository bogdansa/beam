#pragma once

#include <iostream>

class Point
{
public:
	double x, y, z;
	/** Конструктор по умолчанию.*/
	Point();
	/** Конструктор с параметрами.*/
	Point(double X, double Y, double Z);
	/** Перегруженный функтор.*/
	operator Point() const;
	/** Перегруженный оператор ==.*/
	bool operator == (Point point);
	/** Перегруженный оператор !=.*/
	bool operator != (Point point);
	/** Перегруженный оператор <.*/
	bool operator < (const Point & right) const;
	/** Перегруженный оператор >.*/
	bool operator > (const Point & right) const;
};
