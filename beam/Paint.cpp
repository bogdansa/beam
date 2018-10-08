#include "stdafx.h"
#include "Paint.h"

/** ���������� �����.
* @param width - ������ ������� ���������.
* @param height - ������ ������� ���������.
* @param pMemDC - ��������� �� CDC.
* @param w - ������ CRect.*/
void Paint::DrawGrid(int width, int height, CDC* pMemDC, CRect w)
{
	/** Background.*/
	pMemDC->FillSolidRect(&w, RGB(175, 175, 175));

	CPen penGrid;
	penGrid.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	pMemDC->SelectObject(&penGrid);

	double step_x = (double)w.Width() / width;
	double step_y = (double)w.Height() / height;

	/** ��������� �����.*/
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

	/** ��������� ����.*/
	double x0 = w.Width() / 2.;
	double y0 = w.Height() / 2.;
	CPen penAxes;
	penAxes.CreatePen(PS_SOLID, 2, RGB(95, 95, 95));
	pMemDC->SelectObject(&penAxes);
	// ��� ��
	pMemDC->MoveTo(x0, 0);
	pMemDC->LineTo(x0, w.Height());
	// ��� O�
	pMemDC->MoveTo(0, y0);
	pMemDC->LineTo(w.Width(), y0);

}

/** ���������� ���������.
* @param x0 - ���������� ��������� �� ��.
* @param �0 - ���������� ��������� �� ��.
* @param pMemDC - ��������� �� CDC.
* @param w - ������ CRect.
*/
void Paint::DrawCircle(int x0, int y0, CDC* pMemDC, CRect w)
{
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));

	pMemDC->SelectObject(&pen);
	CBrush Brush;
	Brush.CreateSolidBrush(RGB(255, 0, 0));
	//pMemDC->SelectObject(&Brush);
	pMemDC->SelectObject(&pen);
	int rad = 4;
	pMemDC->Ellipse(x0 - rad, y0 - rad, x0 + rad, y0 + rad);
}
