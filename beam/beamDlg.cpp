
// beamDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "beam.h"
#include "beamDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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
	_d(0.25),
	_lambda(1.0),
	_R(100.0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CbeamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, _d);
	DDX_Text(pDX, IDC_EDIT2, _lambda);
	DDX_Text(pDX, IDC_EDIT3, _R);
	DDX_Control(pDX, IDC_STATIC5, viewer);
	DDX_Check(pDX, IDC_CHECK1, isProjection);
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
Point CbeamDlg::ConvertFromPixelsToMeters(Point pix, CRect w)
{
	Max.x = _N * _d / 2.;
	Min.x = -_N * _d / 2.;
	Max.y = _N * _d / 2.;
	Min.y = -_N * _d / 2.;

	int W = w.Width();
	double xScale = (double)(Max.x - Min.x) / W;  // xScale-масштабный коэффициент по  оси х
	double X = xScale * (pix.x - W / 2.);

	int H = w.Height();
	double yScale = (double)(Max.y - Min.y) / H;  // xScale-масштабный коэффициент по  оси х
	double Y = -yScale * (pix.y - H / 2.);

	Point tmpPoint;
	tmpPoint.x = X;
	tmpPoint.y = Y;
	tmpPoint.z = 0;
	return tmpPoint;
}

/** Обработчик нажатия левой кнопки мыши - задать источники излучения.*/
void CbeamDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	Point coordinate;
	coordinate.x = point.x - _antenna_coords.x;
	coordinate.y = point.y - _antenna_coords.y;
	coordinate.z = 0;

	if (coordinate.x > _rect.Width() || coordinate.y > _rect.Height())
	{

	}
	else
	{
		_pnt.DrawCircle(coordinate.x, coordinate.y, _mdc, _rect);
		_PicDc->BitBlt(0, 0, _rect.Width(), _rect.Height(), _mdc, 0, 0, SRCCOPY);

		vec_sources.push_back(coordinate);
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}

/** Обработчик нажатия кнопки - очистить источники излучения.*/
void CbeamDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);

	vec_sources.clear();
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
	x.resize(radiation_pattern.size());
	y.resize(radiation_pattern.size());
	z.resize(radiation_pattern.size());
	for (int i = 0; i < radiation_pattern.size(); i++)
	{
		x[i] = radiation_pattern[i].elevation;
		y[i] = radiation_pattern[i].аzimuth;
		if (isProjection)
		{
			x[i] = radiation_pattern[i].x;
			y[i] = radiation_pattern[i].y;
		}
		z[i] = radiation_pattern[i].A;
	}

	SurfaceChart *c = new SurfaceChart(605, 275);
	c->setPlotRegion(250, 110, 260, 260, 130);

	// Set the elevation and rotation angles to 45 and -45 degrees
	c->setViewAngle(angle1, angle2);

	// Set the perspective level to 30
	//c->setPerspective(30);

	//------------------------------
	c->zAxis()->setAutoScale(0, 0, 1);
	//-------------------------------

	// Set the data to use to plot the chart
	c->setData(vectorToArray(x), vectorToArray(y), vectorToArray(z));

	ColorAxis *cAxis = c->setColorAxis(550, 20, Chart::TopRight, 200, Chart::Right);

	cAxis->setTitle("Amplitude", "arialbd.ttf", 12);

	// Set surface grid lines to semi-transparent black (cc000000)
	c->setSurfaceAxisGrid(0xcc000000);

	// Set contour lines to semi-transparent white (80ffffff)
	c->setContourColor(0x80ffffff);

	// Set the wall thickness to 0
	c->setWallThickness(0, 0, 0);

	// Show only the xy wall, and hide the yz and zx walls.
	c->setWallVisibility(true, false, false);

	// Set the x, y and z axis titles using 12 points Arial Bold font
	if (isProjection)
	{
		c->xAxis()->setTitle("x", "arialbd.ttf", 12);
		c->yAxis()->setTitle("y", "arialbd.ttf", 12);
	}
	else
	{
		c->xAxis()->setTitle("Elevation angle", "arialbd.ttf", 12);
		c->yAxis()->setTitle("Azimuth", "arialbd.ttf", 12);
	}

	viewer.setChart(c);
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

	vec_antenna.resize(vec_sources.size());
	for (int i = 0; i < vec_sources.size(); i++)
	{
		vec_antenna[i] = ConvertFromPixelsToMeters(vec_sources[i], _rect);
	}

	rp.Amplitude = 1.0;
	rp.Distance = _R;
	rp.Wavelength = _lambda;

	double step_phi = 5;
	double step_theta = 5;
	double phi_max = 360;
	double theta_max = 90;
	int N_phi = phi_max / step_phi;
	int N_theta = theta_max / step_theta;

	vec_theta.resize(N_theta);
	vec_phi.resize(N_phi);
	for (int i = 0; i < N_theta; i++)
	{
		vec_theta[i] = M_PI * (i * step_theta) / 180.;
	}
	for (int i = 0; i < N_phi; i++)
	{
		vec_phi[i] = M_PI * (i * step_phi) / 180.;
	}

	radiation_pattern = rp.FindRadPatt(vec_antenna, vec_phi, vec_theta);

	DrawRadiationPattern(_angle1, _angle2);

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
