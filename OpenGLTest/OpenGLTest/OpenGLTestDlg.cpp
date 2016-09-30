
// OpenGLTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OpenGLTest.h"
#include "OpenGLTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define M 100
#define N 100
#define radius 0.5

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// COpenGLTestDlg dialog



COpenGLTestDlg::COpenGLTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(COpenGLTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COpenGLTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COpenGLTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


// COpenGLTestDlg message handlers

BOOL COpenGLTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	//在OnInitDialog中设置像素格式，并在DC中选择这种格式
	static PIXELFORMATDESCRIPTOR pfd = { sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		24,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		32,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};
	int pixelformat;
	hDC = ::GetDC(this->GetSafeHwnd());
	if (!(pixelformat = ChoosePixelFormat(hDC, &pfd)))
	{
		MessageBox(L"ChoosePixelFormat failed!");
		return false;
	}
	if (!SetPixelFormat(hDC, pixelformat, &pfd))
	{
		MessageBox(L"SetPixelFormat failed!");
		return false;
	}
	if (!(hRC = wglCreateContext(hDC)))
	{
		MessageBox(L"CreateContext failed!");
		return false;
	}
	if (!wglMakeCurrent(hDC, hRC))
	{
		MessageBox(L"MakeCurrent failed!");
		return false;
	}

	ChangeDrawWinSize();
	SetTimer(1, 50, NULL); //使用一个定时器（最简单的做法）

	// 通过鼠标操作调整openGL视角的设置
	PI = 3.1415926535897;
	tAngInc = PI / 90;                      // 每次触发鼠标事件变换的角度值
	tFovy = 45.0;
	prePt.SetPoint(-1, -1);                 // 初始化prePt & nowPt(在OnMouseMove中使用)
	nowPt.SetPoint(-1, -1);
	tVerticalAng = 0.;
	tHorizonAng = PI / 2;
	tRadius = 1;
	tEyeX = tRadius * cos(tVerticalAng) * cos(tHorizonAng);
	tEyeY = tRadius * sin(tVerticalAng);
	tEyeZ = tRadius * cos(tVerticalAng) * sin(tHorizonAng);
	tCenterX = 0;
	tCenterY = 0;
	tCenterZ = 0;
	tUpX = 0;
	tUpY = 1.0;
	tUpZ = 0;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void COpenGLTestDlg::ChangeDrawWinSize()
{
	CRect rect; //在这个矩形中画图
	GetClientRect(rect);
	//绘制区域占据整个窗口大小
	glViewport(0, 0, rect.Width(), rect.Height());
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, rect.Width() / rect.Height(), 0.1f, 100.0f);// 计算窗口的外观比例*/
	//gluPerspective(45.0f , 640/480 , 0.1f , 100.0f);// 计算窗口的外观比例
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
}
void COpenGLTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void COpenGLTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR COpenGLTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void COpenGLTestDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	ChangeDrawWinSize();
	// TODO: Add your message handler code here
}


void COpenGLTestDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(1);//结束settimer
	CDialogEx::OnClose();
}

void COpenGLTestDlg::DrawFunc() //函数具体实现
{
	//glMatrixMode(GL_PROJECTION);                            // 设置modelview 和 projection
	//glLoadIdentity();                                       // 此处尤其不能少glLoadIdentity()
	//gluPerspective(tFovy, 1, 0.1, 1000.0);                  // 注意zNear,zFar的取值
	//glMatrixMode(GL_MODELVIEW);
	
	//gluLookAt(tEyeX, tEyeY, tEyeZ, tCenterX, tCenterY, tCenterZ, tUpX, tUpY, tUpZ);

	//glClear(GL_COLOR_BUFFER_BIT);

	//glColor3f(1.0, 1.0, 1.0);
	//glutWireCube(50.0);

	//SwapBuffers(hDC);                                    // 使用glFlush()没有显示？

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -3.0f);
	gluLookAt(tEyeX, tEyeY, tEyeZ, tCenterX, tCenterY, tCenterZ, tUpX, tUpY, tUpZ);


	//glBegin(GL_QUADS);				//绘制正方形
	//glTexCoord2f(0.0, 1.0);			//纹理左上
	//glVertex3f(-1.0f, 1.0f, 0.0f);	//四边形左上

	//glTexCoord2f(1.0, 1.0);			//纹理右上
	//glVertex3f(1.0f, 1.0f, 0.0f);		//右上

	//glTexCoord2f(1.0, 0.0);			//纹理右下
	//glVertex3f(1.0f, -1.0f, 0.0f);	//右下

	//glTexCoord2f(0.0, 0.0);			//纹理左下
	//glVertex3f(-1.0f, -1.0f, 0.0f);	//左下	

	//glEnd();


	float step_z = PI / M;
	float step_xy = 2 * PI / N;
	float x[4], y[4], z[4];

	float angle_z = 0.0;
	float angle_xy = 0.0;
	int i = 0, j = 0;
	glBegin(GL_POINTS);//GL_QUADS
	for (i = 0; i<M; i++)
	{
		angle_z = i * step_z;

		for (j = 0; j<N; j++)
		{
			angle_xy = j * step_xy;

			x[0] = radius * sin(angle_z) * cos(angle_xy);
			y[0] = radius * sin(angle_z) * sin(angle_xy);
			z[0] = radius * cos(angle_z);

			x[1] = radius * sin(angle_z + step_z) * cos(angle_xy);
			y[1] = radius * sin(angle_z + step_z) * sin(angle_xy);
			z[1] = radius * cos(angle_z + step_z);

			x[2] = radius*sin(angle_z + step_z)*cos(angle_xy + step_xy);
			y[2] = radius*sin(angle_z + step_z)*sin(angle_xy + step_xy);
			z[2] = radius*cos(angle_z + step_z);

			x[3] = radius * sin(angle_z) * cos(angle_xy + step_xy);
			y[3] = radius * sin(angle_z) * sin(angle_xy + step_xy);
			z[3] = radius * cos(angle_z);

			for (int k = 0; k<4; k++)
			{
				glVertex3f(0 + x[k], 0 + y[k], 0 + z[k]);
			}
		}
	}
	glEnd();


	SwapBuffers(hDC); //利用双缓冲
}

void COpenGLTestDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	DrawFunc();   //定时器中调用这个函数
	CDialogEx::OnTimer(nIDEvent);
}


void COpenGLTestDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (nFlags & MK_LBUTTON == TRUE) {

		//MessageBox("mouse move function triggered!", "attentino", MB_OK);

		nowPt.x = point.x;
		nowPt.y = point.y;
		if (prePt.x != -1 && prePt.y != -1 && nowPt.x != -1 && nowPt.y != -1) {
			double tDx = nowPt.x - prePt.x;
			double tDy = nowPt.y - prePt.y;
			double tDis = sqrt(tDx*tDx + tDy*tDy);
			if (tDx > 0.) {
				tHorizonAng += tAngInc * tDx / tDis;
				if (tHorizonAng < 0.) { tHorizonAng += 2 * PI; }
				if (tHorizonAng > 2 * PI) { tHorizonAng -= 2 * PI; }
			}
			else if (tDx < 0.) {
				tHorizonAng += tAngInc * tDx / tDis;
				if (tHorizonAng < 0.) { tHorizonAng += 2 * PI; }
				if (tHorizonAng > 2 * PI) { tHorizonAng -= 2 * PI; }
			}
			if (tDy > 0.) {
				tVerticalAng = tVerticalAng + tAngInc * tDy / tDis;
				if (tVerticalAng > PI / 2) { tVerticalAng = PI / 2; }
			}
			else if (tDy < 0.) {
				tVerticalAng = tVerticalAng + tAngInc * tDy / tDis;
				if (tVerticalAng < -PI / 2) { tVerticalAng = -PI / 2; }
			}

			tEyeX = tRadius * cos(tVerticalAng) * cos(tHorizonAng);
			tEyeY = tRadius * sin(tVerticalAng);
			tEyeZ = tRadius * cos(tVerticalAng) * sin(tHorizonAng);
		}
		prePt.x = nowPt.x;
		prePt.y = nowPt.y;
	}
	CDialogEx::OnMouseMove(nFlags, point);
}


BOOL COpenGLTestDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default
	int tWheelCount = zDelta / 120;
	if (tWheelCount > 0) {
		tFovy += 1.0;
	}
	else if (tWheelCount < 0) {
		tFovy -= 1.0;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();                                            // 此处尤其不可少glLoadIdentity()
	gluPerspective(tFovy, 1, 0.1, 1000.0);                        // 注意zNear,zFar的取值
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}
