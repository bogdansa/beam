#pragma once

#include <vector>

class Paint
{
public:
	/** Нарисовать сетку.*/
	void DrawGrid(int Nx, int Ny, CDC* pMemDC, CRect w);
	void DrawCircle(int x0, int y0, CDC* pMemDC, CRect w);
};