
// beamDlg.h: файл заголовка
//

#pragma once
#include "Paint.h"
#include "AuxBeam.h"
#include "ChartViewer.h"
#include "Point.h"
#include "PaintBeam2D.h"

// Диалоговое окно CbeamDlg
class CbeamDlg : public CDialogEx
{
// Создание
public:
	CbeamDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BEAM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


private:
	/** Параметр решетки.*/
	double _d;
	/** Длина волны.*/
	double _lambda;
	/** Радиус наблюдения.*/
	double _R;
	/** Число точек на решетке.*/
	int _N;

	/** Координаты положения окна рисования антенны.*/
	CPoint _antenna_coords;

	Paint _pnt;
	CChartViewer _viewer;

	/** Максимальный размер решетки (максимальное значение координаты (х,у).*/
	MyPoint _Max;
	/** Минимальный размер решетки (минимальное значение координаты (х,у).*/
	MyPoint _Min;

	RadiationPattern _rp;

	/** Массив значений угла phi - азимут.*/
	std::vector<double> _vec_phi;
	/** Массив значений угла theta - угол места.*/
	std::vector<double> _vec_theta;
	/** Массив значений источников излучения в пользовательских координатах.*/
	std::vector<MyPoint> _vec_antenna;
	std::vector<RadPatt> _radiation_pattern;
	std::vector<MyPoint> _vec_beam_2D;

	/** Угол поворота Ох для ДН.*/
	double _angle1;
	/** Угол поворота Оу для ДН.*/
	double _angle2;
	
	BOOL _isProjection;
	/** Массив источников излучения.*/
	std::vector<MyPoint> _vec_sources;

	PaintBeam2D _pntBeam2D;

	/** Указатель на CWnd.*/
	CWnd* _PicWnd;
	/** Указатель на CDC.*/
	CDC* _PicDc;
	/** Объект CRect.*/
	CRect _rect;
	/** Указатель на CDC.*/
	CDC *_mdc;
	/** Указатель на CBitmap.*/
	CBitmap *_Bmp;
	// Переменные для работы с масштабом 
	double _xp, _yp,			// коэфициенты пересчета
		_xmin, _xmax,			// максисимальное и минимальное значение х 
		_ymin, _ymax;	     // максисимальное и минимальное значение y


public:
	/** Конвертировать вектор в массив для отрисовки ДН.
	* @param v - вектор, подлежащий конвертации.
	* @return - массив (конвертированный вектор).
	*/
	DoubleArray vectorToArray(std::vector<double> &v);

	/** Отрисовать ДН.*/
	void DrawRadiationPattern(double angle1, double angle2);

	/** Конвертировать пиксели в метры.*/
	MyPoint ConvertFromPixelsToMeters(MyPoint pix, CRect w);

	/** Обработчик нажатия левой кнопки мыши - задать источники излучения.*/
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	/** Обработчик нажатия кнопки - очистить источники излучения.*/
	afx_msg void OnBnClickedButton1();

	/** Обработчик нажатия кнопки - построить ДН.*/
	afx_msg void OnBnClickedButton2();

	/** Обработчик нажатия кнопок перемещения курсора.
	* @param pMsg - посылаемое сообщение.
	*/
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
