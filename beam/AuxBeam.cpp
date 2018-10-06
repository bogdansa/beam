#include "stdafx.h"
#include "AuxBeam.h"

/** Конструктор по умолчанию.*/
RadiationPattern::RadiationPattern()
{

}

RadPatt RadiationPattern::FindIForDistance(std::vector<Point> ant, double phi, double theta)
{
	RadPatt radpat;
	Convert(phi, theta, radpat.elevation, radpat.аzimuth);
	double k = 2 * M_PI / Wavelength;

	Point point;
	point.x = Distance * sin(theta) * cos(phi);
	point.y = Distance * sin(theta) * sin(phi);
	point.z = Distance * cos(theta);

	//--------------------
	radpat.x = point.x;
	radpat.y = point.y;
	radpat.z = point.z;
	//--------------------

	Cmplx buf_E;
	buf_E.Real = 0.0;
	buf_E.Image = 0.0;

	double a;
	/** Вычисление интенсивности излучения в точке наблюдения.*/
	for (int i = 0; i < ant.size(); i++)
	{
		a = sqrt((point.x - ant[i].x) * (point.x - ant[i].x) + 
			(point.y - ant[i].y) * (point.y - ant[i].y) + (point.z - ant[i].z) * (point.z - ant[i].z));

		buf_E.Real += Amplitude * cos(a * k) / a;
		buf_E.Image -= Amplitude * sin(a * k) / a;
	}
	radpat.A = sqrt(buf_E.Real * buf_E.Real + buf_E.Image * buf_E.Image);
	return radpat;
}
std::vector<RadPatt> RadiationPattern::FindRadPatt(std::vector<Point> ant, std::vector<double> phi, std::vector<double> theta)
{
	std::vector<RadPatt> radpat;
	radpat.resize(phi.size() * theta.size());
	for (int i = 0; i < theta.size(); i++)
	{
		for (int j = 0; j < phi.size(); j++)
		{
			radpat[i * phi.size() + j] = FindIForDistance(ant, phi[j], theta[i]);
		}
	}
	return radpat;
}
void RadiationPattern::Convert(double phi, double theta, double &elevation, double &аzimuth)
{
	аzimuth = atan(tan(theta) * sin(phi)) * 180.0 / M_PI;
	elevation = asin(sin(theta) * cos(phi) / 
		(sqrt(sin(theta) * sin(theta) * cos(phi) * cos(phi) + cos(theta) * cos(theta)))) * 180. / M_PI;
}
