
// beamDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "beam.h"
#include "beamDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define KOORD_CU(x,y) int(_xp * ((x)-_xmin)), int(_yp * ((y)-_ymax))

#include <algorithm>

// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно CbeamDlg



CbeamDlg::CbeamDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BEAM_DIALOG, pParent),
	_d(0.2),
	_lambda(1.0),
	_R(100.0),
	_isProjection(TRUE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CbeamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, _d);
	DDX_Text(pDX, IDC_EDIT2, _lambda);
	DDX_Text(pDX, IDC_EDIT3, _R);
	DDX_Control(pDX, IDC_STATIC5, _viewer);
	DDX_Control(pDX, IDC_STATIC6, _pntBeam2D);
}

BEGIN_MESSAGE_MAP(CbeamDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON1, &CbeamDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CbeamDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// Обработчики сообщений CbeamDlg

BOOL CbeamDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	_PicWnd = this->GetDlgItem(IDC_STATIC4);
	_PicDc = _PicWnd->GetDC();
	_PicWnd->GetClientRect(&_rect);

	_mdc = new CDC();
	_mdc->CreateCompatibleDC(_PicDc);

	CBitmap bmpTmp;
	bmpTmp.CreateCompatibleBitmap(_PicDc, _rect.Width(), _rect.Height());
	_Bmp = _mdc->SelectObject(&bmpTmp);

	CRect rectangle;
	CWnd *pWnd = GetDlgItem(IDC_STATIC4);
	pWnd->GetWindowRect(&rectangle);
	ScreenToClient(&rectangle);
	_antenna_coords = rectangle.TopLeft();	//координаты

	_N = 10;
	_angle1 = 15;
	_angle2 = 45;

	_xmin = -2.0; _xmax = 2.0;
	_ymin = -2.0; _ymax = 2.0;

	_pnt.DrawGrid(_N, _N, _mdc, _rect);

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CbeamDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CbeamDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();

		_PicDc->BitBlt(0, 0, _rect.Width(), _rect.Height(), _mdc, 0, 0, SRCCOPY);
		
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CbeamDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/** Конвертировать пиксели в метры.*/
MyPoint CbeamDlg::ConvertFromPixelsToMeters(MyPoint pix, CRect w)
{
	_Max.x = _N * _d / 2.;
	_Min.x = -_N * _d / 2.;
	_Max.y = _N * _d / 2.;
	_Min.y = -_N * _d / 2.;

	int W = w.Width();
	double xScale = (double)(_Max.x - _Min.x) / W;  // xScale-масштабный коэффициент по  оси х
	double X = xScale * (pix.x - W / 2.);

	int H = w.Height();
	double yScale = (double)(_Max.y - _Min.y) / H;  // xScale-масштабный коэффициент по  оси х
	double Y = -yScale * (pix.y - H / 2.);

	MyPoint tmpPoint;
	tmpPoint.x = X;
	tmpPoint.y = Y;
	tmpPoint.z = 0;
	return tmpPoint;
}

/** Обработчик нажатия левой кнопки мыши - задать источники излучения.*/
void CbeamDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	MyPoint coordinate;
	coordinate.x = point.x - _antenna_coords.x;
	coordinate.y = point.y - _antenna_coords.y;
	coordinate.z = 0;

	if (coordinate.x > _rect.Width() || coordinate.y > _rect.Height())
	{

	}
	else
	{
		_pnt.DrawCircle(static_cast<int>(coordinate.x), static_cast<int>(coordinate.y), _mdc, _rect);
		_PicDc->BitBlt(0, 0, _rect.Width(), _rect.Height(), _mdc, 0, 0, SRCCOPY);

		_vec_sources.push_back(coordinate);
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}

/** Обработчик нажатия кнопки - очистить источники излучения.*/
void CbeamDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);

	_vec_beam_2D.clear();
	_vec_sources.clear();
	_pnt.DrawGrid(_N, _N, _mdc, _rect);
	_PicDc->BitBlt(0, 0, _rect.Width(), _rect.Height(), _mdc, 0, 0, SRCCOPY);

	UpdateData(FALSE);
}

/** Отрисовать ДН.*/
void CbeamDlg::DrawRadiationPattern(double angle1, double angle2)
{
	std::vector<double> x;
	std::vector<double> y;
	std::vector<double> z;
	x.resize(_radiation_pattern.size());
	y.resize(_radiation_pattern.size());
	z.resize(_radiation_pattern.size());
	for (size_t i = 0; i < _radiation_pattern.size(); i++)
	{
		x[i] = _radiation_pattern[i].elevation;
		y[i] = _radiation_pattern[i].аzimuth;
		if (_isProjection)
		{
			x[i] = _radiation_pattern[i].x;
			y[i] = _radiation_pattern[i].y;
		}
		z[i] = _radiation_pattern[i].A;
	}

	SurfaceChart *c = new SurfaceChart(645, 505);
	c->setPlotRegion(270, 240, 310, 330, 230);

	// Set the elevation and rotation angles to 45 and -45 degrees
	c->setViewAngle(angle1, angle2);

	// Set the perspective level to 30
	//c->setPerspective(30);

	//------------------------------
	c->zAxis()->setAutoScale(0, 0, 1);
	//-------------------------------

	// Set the data to use to plot the chart
	c->setData(vectorToArray(x), vectorToArray(y), vectorToArray(z));

	ColorAxis *cAxis = c->setColorAxis(570, 40, Chart::TopRight, 270, Chart::Right);

	cAxis->setTitle("Amplitude", "arialbd.ttf", 12);

	// Set surface grid lines to semi-transparent black (cc000000)
	c->setSurfaceAxisGrid(0xcc000000);

	// Set contour lines to semi-transparent white (80ffffff)
	c->setContourColor(0x80ffffff);

	// Set the wall thickness to 0
	c->setWallThickness(10, 0, 0);

	// Show only the xy wall, and hide the yz and zx walls.
	c->setWallVisibility(true, false, false);

	// Set the x, y and z axis titles using 12 points Arial Bold font
	if (_isProjection)
	{
		c->xAxis()->setTitle("x", "arialbd.ttf", 12);
		c->yAxis()->setTitle("y", "arialbd.ttf", 12);
	}
	else
	{
		c->xAxis()->setTitle("Elevation angle", "arialbd.ttf", 12);
		c->yAxis()->setTitle("Azimuth", "arialbd.ttf", 12);
	}

	_viewer.setChart(c);
	delete c;
}

/** Конвертировать вектор в массив для отрисовки ДН.
* @param v - вектор, подлежащий конвертации.
* @return - массив (конвертированный вектор).
*/
DoubleArray CbeamDlg::vectorToArray(std::vector<double> &v)
{
	return (v.size() == 0) ? DoubleArray() : DoubleArray(v.data(), (int)v.size());
}

/** Обработчик нажатия кнопки - построить ДН.*/
void CbeamDlg::OnBnClickedButton2()
{
	UpdateData(TRUE);

	_vec_antenna.resize(_vec_sources.size());
	for (size_t i = 0; i < _vec_sources.size(); i++)
	{
		_vec_antenna[i] = ConvertFromPixelsToMeters(_vec_sources[i], _rect);
	}

	_rp.Amplitude = 1.0;
	_rp.Distance = _R;
	_rp.Wavelength = _lambda;

	double step_phi = 5;
	double step_theta = 5;
	double phi_max = 360;
	double theta_max = 90;
	int N_phi = static_cast<int>(phi_max / step_phi);
	int N_theta = static_cast<int>(theta_max / step_theta);

	_vec_theta.resize(N_theta);
	_vec_phi.resize(N_phi);
	for (int i = 0; i < N_theta; i++)
	{
		_vec_theta[i] = M_PI * (i * step_theta) / 180.;
	}
	for (int i = 0; i < N_phi; i++)
	{
		_vec_phi[i] = M_PI * (i * step_phi) / 180.;
	}

	_radiation_pattern = _rp.FindRadPatt(_vec_antenna, _vec_phi, _vec_theta);

	_vec_beam_2D.resize(_radiation_pattern.size());
	double maxA = 0.0;
	double maxX = 0.0;
	double maxY = 0.0;
	for (size_t it = 0; it < _radiation_pattern.size(); ++it)
	{
		if (maxX < _radiation_pattern[it].x)
			maxX = _radiation_pattern[it].x;
		if (maxY < _radiation_pattern[it].y)
			maxY = _radiation_pattern[it].y;
		if (maxA < _radiation_pattern[it].A)
			maxA = _radiation_pattern[it].A;

		_vec_beam_2D[it].x = _radiation_pattern[it].x;
		_vec_beam_2D[it].y = _radiation_pattern[it].y;
		_vec_beam_2D[it].z = _radiation_pattern[it].A;
	}
	_xmin = -maxX; _xmax = maxX;
	_ymin = -maxY; _ymax = maxY;

	std::for_each(_vec_beam_2D.begin(), _vec_beam_2D.end(),
		[&maxA](MyPoint & x)
	{
		x.z = x.z / maxA * 255.0;
	});

	DrawRadiationPattern(_angle1, _angle2);	

	_pntBeam2D.set_vector(_vec_beam_2D);
	_pntBeam2D.Exchange(_xmin, _xmax, _ymin, _ymax);

	UpdateData(FALSE);
}


BOOL CbeamDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_UP:
		{
			_angle1 -= 1; break;
		}
		case VK_DOWN:
		{
			_angle1 += 1; break;
		}
		case VK_RIGHT:
		{
			_angle2 -= 1; break;
		}
		case VK_LEFT:
		{
			_angle2 += 1; break;
		}
		default:
			break;
		}
	}
	DrawRadiationPattern(_angle1, _angle2);

	return CDialogEx::PreTranslateMessage(pMsg);
}
