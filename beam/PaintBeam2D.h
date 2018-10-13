#pragma once
#include "afxwin.h"
#include <vector>
#include "Point.h"

class PaintBeam2D : public CStatic
{
private:
	// Объект для инициализации GDI+
	ULONG_PTR _token;

	double _xmin, _xmax,   // Минимальное и максимальное значение по х
		_ymin, _ymax,   // Минимальное и максимальное значение по у
		_step_x, _step_y;   // Шаг по х и у

	/** Восстановленное изображение.*/
	std::vector<std::vector<double>> _vec_beam2D;
	
public:
	/** Конструктор.*/
	PaintBeam2D();
	/** Деструктор.*/
	~PaintBeam2D();

	/** Функция обмена информацией между классами.*/
	void Exchange(double left, double right, double low, double up);

	/** Функция преобразования х к пиксельному формату.*/
	Gdiplus::REAL Trans_X(LPDRAWITEMSTRUCT lpDrawItemStruct, Gdiplus::REAL x);
	/** Функция преобразования у к пиксельному формату.*/
	Gdiplus::REAL Trans_Y(LPDRAWITEMSTRUCT lpDrawItemStruct, Gdiplus::REAL y);

	/** Инициализировать вектор.*/
	void set_vector(const std::vector<std::vector<double>> & vec);
	
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
};