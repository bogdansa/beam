#pragma once

class Paint
{
public:
	/** ���������� ���������.
	* @param x0 - ���������� ��������� �� ��.
	* @param �0 - ���������� ��������� �� ��.
	* @param pMemDC - ��������� �� CDC.
	* @param w - ������ CRect.
	*/
	void DrawGrid(int Nx, int Ny, CDC* pMemDC, CRect w);
	/** ���������� ���������.
	* @param x0 - ���������� ��������� �� ��.
	* @param �0 - ���������� ��������� �� ��.
	* @param pMemDC - ��������� �� CDC.
	* @param w - ������ CRect.
	*/
	void DrawCircle(int x0, int y0, CDC* pMemDC, CRect w);
};