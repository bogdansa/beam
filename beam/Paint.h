#pragma once

class Paint
{
public:
	/** Нарисовать источники.
	* @param x0 - координата источника по Ох.
	* @param у0 - координата источника по Оу.
	* @param pMemDC - указатель на CDC.
	* @param w - объект CRect.
	*/
	void DrawGrid(int Nx, int Ny, CDC* pMemDC, CRect w);
	/** Нарисовать источники.
	* @param x0 - координата источника по Ох.
	* @param у0 - координата источника по Оу.
	* @param pMemDC - указатель на CDC.
	* @param w - объект CRect.
	*/
	void DrawCircle(int x0, int y0, CDC* pMemDC, CRect w);
};