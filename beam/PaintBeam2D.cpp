#include "stdafx.h"
#include "PaintBeam2D.h"
#include "Gdiplus.h"

using namespace Gdiplus;

/** ������������� GDI+.*/
PaintBeam2D::PaintBeam2D()
{
	GdiplusStartupInput input;
	Status s;
	s = GdiplusStartup(&_token, &input, NULL);
	if (s != Ok)
		MessageBox(L"Don't Open", L"Warning", MB_ICONERROR);
}

/** ��������������� GDI+.*/
PaintBeam2D::~PaintBeam2D()
{
	GdiplusShutdown(_token);
}

/** ������� ������ ����������� ����� ��������.*/
void PaintBeam2D::Exchange(double left, double right, double low, double up)
{
	_xmin = left;
	_xmax = right;
	_ymin = low;
	_ymax = up;
	RedrawWindow();
}

/** �������������� � � ����������� �������.*/
Gdiplus::REAL PaintBeam2D::Trans_X(LPDRAWITEMSTRUCT lpDrawItemStruct, Gdiplus::REAL x)
{
	return (Gdiplus::REAL)(lpDrawItemStruct->rcItem.right) / (Gdiplus::REAL)(_xmax - _xmin) * ((x)-_xmin);
}

/** �������������� � � ����������� �������.*/
Gdiplus::REAL PaintBeam2D::Trans_Y(LPDRAWITEMSTRUCT lpDrawItemStruct, Gdiplus::REAL y)
{
	return -(Gdiplus::REAL)(lpDrawItemStruct->rcItem.bottom) / (Gdiplus::REAL)(_ymax - _ymin) * ((y)-_ymax);
}

/** ���������������� ��������������� �����������(������).*/
void PaintBeam2D::set_vector(const std::vector<MyPoint>& vec)
{
	_vec_beam2D.clear();
	_vec_beam2D = vec;
}


void PaintBeam2D::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	Graphics paint(lpDrawItemStruct->hDC);
	Bitmap bmp(lpDrawItemStruct->rcItem.right, lpDrawItemStruct->rcItem.bottom, &paint);
	Graphics paint_virtual(&bmp);

	Pen penEllipse(Color::Red, 1);
	SolidBrush brushPoints(Color::Yellow);

	paint_virtual.Clear(Color::White);

	if (!_vec_beam2D.empty())
	{
		size_t size = _vec_beam2D.size();
		//Bitmap bmpTmp(size, size);
		for (size_t i = 0; i < size; ++i)
		{
			double val = _vec_beam2D[i].z;
			Color color;
			color = Color::MakeARGB(255, val, val, val);
			SolidBrush brush(color);
			//grBmp.FillRectangle(&brush, 
			//	Trans_X(lpDrawItemStruct, j), 
			//	Trans_Y(lpDrawItemStruct, i), 
			//	Width(lpDrawItemStruct, 1), 
			//	Height(lpDrawItemStruct, 1));
			bmp.SetPixel(Trans_X(lpDrawItemStruct, _vec_beam2D[i].x), Trans_Y(lpDrawItemStruct, _vec_beam2D[i].y), color);
		}
		//gr.DrawImage(&bmpTmp, 0, lpDrawItemStruct->rcItem.bottom, lpDrawItemStruct->rcItem.right, -lpDrawItemStruct->rcItem.bottom);
	}
	paint.DrawImage(&bmp, 0, 0);
}
