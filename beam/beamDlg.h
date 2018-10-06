
// beamDlg.h: файл заголовка
//

#pragma once
#include "Paint.h"
#include "AuxBeam.h"
#include "ChartViewer.h"

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
	/** Координаты положения окна рисования антенны.*/
	CPoint _antenna_coords;

	Paint _pnt;
	CChartViewer viewer;

	/** Максимальный размер решетки (максимальное значение координаты (х,у).*/
	Point Max;
	/** Минимальный размер решетки (минимальное значение координаты (х,у).*/
	Point Min;

	RadiationPattern rp;

	/** Массив значений угла phi - азимут.*/
	std::vector<double> vec_phi;
	/** Массив значений угла theta - угол места.*/
	std::vector<double> vec_theta;
	/** Массив значений источников излучения в пользовательских координатах.*/
	std::vector<Point> vec_antenna;
	std::vector<RadPatt> radiation_pattern;

	/** Число точек на решетке.*/
	int _N;
	double _angle1;
	double _angle2;
	
	BOOL isProjection;
	/** Массив источников излучения.*/
	std::vector<Point> vec_sources;

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


public:
	/** Конвертировать вектор в массив для отрисовки ДН.
	* @param v - вектор, подлежащий конвертации.
	* @return - массив (конвертированный вектор).
	*/
	DoubleArray vectorToArray(std::vector<double> &v);

	/** Отрисовать ДН.*/
	void DrawRadiationPattern(double angle1, double angle2);

	/** Конвертировать пиксели в метры.*/
	Point ConvertFromPixelsToMeters(Point pix, CRect w);

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
