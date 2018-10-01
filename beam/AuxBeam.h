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

	double x;
	double y;
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
	double Distance;
	double Wavelength;
	double Amplitude;
	RadiationPattern();
	RadPatt FindIForDistance(std::vector<Point> ant, double phi, double theta);
	std::vector<RadPatt> FindRadPatt(std::vector<Point> ant, std::vector<double>phi, std::vector<double>theta);
	void Convert(double phi, double theta, double &elevation, double &аzimuth);

};
