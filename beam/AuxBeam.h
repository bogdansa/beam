#pragma once

#include "Point.h"
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>

struct RadPatt
{
	/** ���������.*/
	double A;
	/** ���� �����.*/
	double elevation;
	/** ������.*/
	double �zimuth;
	/** ��������� �� ��.*/
	double x;
	/** ��������� �� ��.*/
	double y;
	/** ��������� �� �z.*/
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
	/** ������ ����������.*/
	double Distance;
	/** ����� �����.*/
	double Wavelength;
	/** ���������.*/
	double Amplitude;
	RadiationPattern();
	RadPatt FindIForDistance(std::vector<MyPoint> ant, double phi, double theta);
	std::vector<RadPatt> FindRadPatt(std::vector<MyPoint> ant, std::vector<double>phi, std::vector<double>theta);
	double FindRadPatt2D(std::vector<MyPoint> vec_antenna, MyPoint z);
	void Convert(double phi, double theta, double &elevation, double &�zimuth);

};
