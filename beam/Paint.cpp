#include "stdafx.h"
#include "Paint.h"

void Paint::DrawGrid(int width, int height, CDC* pMemDC, CRect w)
{
	pMemDC->FillSolidRect(&w, RGB(175, 175, 175));

	CPen penBlack, *oldpen;
	penBlack.CreatePen(PS_DOT, 1, RGB(0, 0, 0));	//серый
	oldpen = pMemDC->SelectObject(&penBlack);

	double step_x = (double)w.Width() / width;
	double step_y = (double)w.Height() / height;

	double x, y;
	x = 0;
	for (int i = 0; i <= width; i++)
	{
		pMemDC->MoveTo(x, 0);
		pMemDC->LineTo(x, w.Height());
		x += step_x;
	}
	y = 0;
	for (int i = 0; i <= height; i++)
	{
		pMemDC->MoveTo(0, y);
		pMemDC->LineTo(w.Width(), y);
		y += step_y;
	}

	//прорисуем оси
	double x0 = w.Width() / 2.;
	double y0 = w.Height() / 2.;
	CPen penGray;
	penGray.CreatePen(PS_SOLID, 2, RGB(125, 125, 125));
	oldpen = pMemDC->SelectObject(&penGray);
	//ось ОУ
	pMemDC->MoveTo(x0, 0);
	pMemDC->LineTo(x0, w.Height());
	//ось OX
	pMemDC->MoveTo(0, y0);
	pMemDC->LineTo(w.Width(), y0);

}
void Paint::DrawCircle(int x0, int y0, CDC* pMemDC, CRect w)
{
	CPen penBlue;
	penBlue.CreatePen(PS_SOLID, 2, RGB(0, 0, 255));

	CPen *oldpen;
	oldpen = pMemDC->SelectObject(&penBlue);
	CBrush BrushBlue;
	BrushBlue.CreateSolidBrush(RGB(0, 0, 255));
	pMemDC->SelectObject(&BrushBlue);
	pMemDC->SelectObject(&penBlue);
	int rad = 5;
	pMemDC->Ellipse(x0 - rad, y0 - rad, x0 + rad, y0 + rad);
}
