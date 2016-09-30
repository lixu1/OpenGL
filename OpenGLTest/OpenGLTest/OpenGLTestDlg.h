
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
	double tFovy;                   // ��gluPerspective��ʹ��(��OnMouseWheel��ʹ��)
	CPoint prePt, nowPt;                                        // ��OnMouseMove��ʹ��
	double tEyeX, tEyeY, tEyeZ;                                    // ��gluLookAt��ʹ�õ�3������
	double tCenterX, tCenterY, tCenterZ;
	double tUpX, tUpY, tUpZ;
	double tVerticalAng, tHorizonAng, tRadius, tAngInc; // ˮƽ���򡢴�ֱ����Ľǡ��뾶

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
