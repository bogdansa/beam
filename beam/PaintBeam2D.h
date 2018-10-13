#pragma once
#include "afxwin.h"
#include <vector>
#include "Point.h"

class PaintBeam2D : public CStatic
{
private:
	// ������ ��� ������������� GDI+
	ULONG_PTR _token;

	double _xmin, _xmax,   // ����������� � ������������ �������� �� �
		_ymin, _ymax,   // ����������� � ������������ �������� �� �
		_step_x, _step_y;   // ��� �� � � �

	/** ��������������� �����������.*/
	std::vector<std::vector<double>> _vec_beam2D;
	
public:
	/** �����������.*/
	PaintBeam2D();
	/** ����������.*/
	~PaintBeam2D();

	/** ������� ������ ����������� ����� ��������.*/
	void Exchange(double left, double right, double low, double up);

	/** ������� �������������� � � ����������� �������.*/
	Gdiplus::REAL Trans_X(LPDRAWITEMSTRUCT lpDrawItemStruct, Gdiplus::REAL x);
	/** ������� �������������� � � ����������� �������.*/
	Gdiplus::REAL Trans_Y(LPDRAWITEMSTRUCT lpDrawItemStruct, Gdiplus::REAL y);

	/** ���������������� ������.*/
	void set_vector(const std::vector<std::vector<double>> & vec);
	
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
};