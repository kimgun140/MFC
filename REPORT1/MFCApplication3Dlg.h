
// MFCApplication3Dlg.h: 헤더 파일
//

#pragma once


// CMFCApplication3Dlg 대화 상자
class CMFCApplication3Dlg : public CDialogEx
{
private:
	CImage m_image; // 이미지 

// 생성입니다.
public:
	CMFCApplication3Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION3_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonMakecircle();
	BOOL inInCircle(int i, int  j, int  nCenterX, int nCenterY, int  nRadius);
	void UpdateDisplay();
	void drawCircle(UCHAR* fm, int x, int y, int nRadius, int nGray);
	void MoveRect();
	//int m_nDraw_Times;
	CString GetSaveDataFileName(int x1, int y1, int nRadius);
	//afx_msg void OnEnChangeEdit1Entertimes();
	afx_msg void OnBnClickedButtonDraw();
	int xpintX1_;
	int ypintY1_;
	afx_msg void OnBnClickedButtonAction();
	int xpintX2_;
	int ypintY2_;
	int nRadius_;
	afx_msg void OnBnClickedButton2();
	CString sPath;
	void drawX( int x, int y,int radius);
	//unsigned char* fm = (unsigned char*)m_image.GetBits();//

	int StaticXypos;
};
