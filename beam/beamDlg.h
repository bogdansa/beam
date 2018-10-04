
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

	Point Max;
	Point Min;

	RadiationPattern rp;

	std::vector<double> phi;
	std::vector<double> theta;
	std::vector<Point> antenna;
	std::vector<RadPatt> radiation_pattern;

	int _N;
	double _angle1;
	double _angle2;
	
	CWnd* _PicWnd;
	CDC* _PicDc;
	CRect _rect;

	CDC *_mdc;
	CBitmap *_tmpBmp;

	BOOL isProjection;
	std::vector<Point> px;
public:
	/** Обработчик нажатия левой кнопки мыши.*/
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	/** Обработчик нажатия кнопки - очистить источники излучения.*/
	afx_msg void OnBnClickedButton1();
	Point ConvertFromPixelsToMeters(Point pix, CRect w);
	afx_msg void OnBnClickedButton2();
	void DrawRadiationPattern(double angle1, double angle2);
	DoubleArray vectorToArray(std::vector<double> &v);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
