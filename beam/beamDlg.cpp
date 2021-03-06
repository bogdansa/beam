
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
}

BEGIN_MESSAGE_MAP(CbeamDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON1, &CbeamDlg::OnBnClickedButton1)
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

	CBitmap bmp;
	bmp.CreateCompatibleBitmap(_PicDc, _rect.Width(), _rect.Height());
	_tmpBmp = _mdc->SelectObject(&bmp);

	CRect rectangle;
	CWnd *pWnd = GetDlgItem(IDC_STATIC4);
	pWnd->GetWindowRect(&rectangle);
	ScreenToClient(&rectangle);
	_antenna_coords = _rect.TopLeft();	//координаты

	_N = 12;
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


/** Обработчик нажатия левой кнопки мыши.*/
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

		px.push_back(coordinate);
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}

/** Обработчик нажатия кнопки - очистить источники излучения.*/
void CbeamDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);

	px.clear();
	_pnt.DrawGrid(_N, _N, _mdc, _rect);
	_PicDc->BitBlt(0, 0, _rect.Width(), _rect.Height(), _mdc, 0, 0, SRCCOPY);

	UpdateData(FALSE);
}
