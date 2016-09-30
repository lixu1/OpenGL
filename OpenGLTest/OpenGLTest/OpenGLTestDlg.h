
// OpenGLTestDlg.h : header file
//

#pragma once


// COpenGLTestDlg dialog
class COpenGLTestDlg : public CDialogEx
{
// Construction
public:
	COpenGLTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_OPENGLTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	void DrawFunc();
	void ChangeDrawWinSize();

	double PI;
	double tFovy;                   // 在gluPerspective中使用(在OnMouseWheel中使用)
	CPoint prePt, nowPt;                                        // 在OnMouseMove中使用
	double tEyeX, tEyeY, tEyeZ;                                    // 在gluLookAt中使用的3个向量
	double tCenterX, tCenterY, tCenterZ;
	double tUpX, tUpY, tUpZ;
	double tVerticalAng, tHorizonAng, tRadius, tAngInc; // 水平方向、垂直方向的角、半径

// Implementation
protected:
	HICON m_hIcon;
	HGLRC hRC;
	HDC hDC;


	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};
