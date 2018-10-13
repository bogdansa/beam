#pragma once

#include "Point.h"
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>

struct RadPatt
{
	/** Амплитуда.*/
	double A;
	/** Угол места.*/
	double elevation;
	/** Азимут.*/
	double аzimuth;
	/** Координта по Ох.*/
	double x;
	/** Координта по Оу.*/
	double y;
	/** Координта по Оz.*/
	double z;
};

struct Cmplx
{
	double Real;
	double Image;
};

class RadiationPattern
{
public:
	/** Радиус наблюдения.*/
	double Distance;
	/** Длина волны.*/
	double Wavelength;
	/** Амплитуда.*/
	double Amplitude;
	RadiationPattern();
	RadPatt FindIForDistance(std::vector<MyPoint> ant, double phi, double theta);
	std::vector<RadPatt> FindRadPatt(std::vector<MyPoint> ant, std::vector<double>phi, std::vector<double>theta);
	double FindRadPatt2D(std::vector<MyPoint> vec_antenna, MyPoint z);
	void Convert(double phi, double theta, double &elevation, double &аzimuth);

};
