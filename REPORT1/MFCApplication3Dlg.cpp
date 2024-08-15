
// MFCApplication3Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication3.h"
#include "MFCApplication3Dlg.h"
#include "afxdialogex.h"
//
#include<time.h>
#include<stdlib.h>
#include<ctime>
#include <chrono>
#include<iostream>
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();


	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	// 구현입니다.
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


// CMFCApplication3Dlg 대화 상자



CMFCApplication3Dlg::CMFCApplication3Dlg(CWnd* pParent /*=nullptr*/) // 변수 
	: CDialogEx(IDD_MFCAPPLICATION3_DIALOG, pParent)
	//, m_nDraw_Times(0)

	, xpintX1_(0)
	, ypintY1_(0)
	, xpintX2_(0)
	, ypintY2_(0)
	, nRadius_(0)
	, fm(0)

	, StaticXypos(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Text(pDX, IDC_EDIT1_ENTERTIMES, m_nDraw_Times);
	DDX_Text(pDX, IDC_EDIT_X1, xpintX1_);
	DDX_Text(pDX, IDC_EDIT_Y1, ypintY1_);
	DDX_Text(pDX, IDC_EDIT_X2, xpintX2_);
	DDX_Text(pDX, IDC_EDIT_Y2, ypintY2_);
	DDX_Text(pDX, IDC_STATIC_XYPOS, StaticXypos);
}

BEGIN_MESSAGE_MAP(CMFCApplication3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_MAKECIRCLE, &CMFCApplication3Dlg::OnBnClickedButtonMakecircle)

	//ON_EN_CHANGE(IDC_EDIT1_ENTERTIMES, &CMFCApplication3Dlg::OnEnChangeEdit1Entertimes)
	ON_BN_CLICKED(IDC_BUTTON_DRAW, &CMFCApplication3Dlg::OnBnClickedButtonDraw)
	ON_BN_CLICKED(IDC_BUTTON_Action, &CMFCApplication3Dlg::OnBnClickedButtonAction)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication3Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMFCApplication3Dlg 메시지 처리기

BOOL CMFCApplication3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCApplication3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCApplication3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCApplication3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication3Dlg::OnBnClickedButtonMakecircle() // draw and save button
// 지금은 그냥 배경만 그림 
// 여기에 원그리기 넣어, 세이브도 
{
	int nWidth = 1000;
	int nHeight = 1000;
	//int nWidth = 8;
	//int nHeight = 4;
	int nBpp = 8; //그레이 레벨 비트 퍼 픽셀 
	m_image.Create(nWidth, -nHeight, nBpp);// 영상을 만든다
	if (m_image != NULL) {
		m_image.Destroy();
		m_image.Create(nWidth, -nHeight, nBpp);// 영상을 만든다

	}
	if (nBpp == 8)
	{
		static RGBQUAD rgb[256];//255니까
		for (int i = 0; i < 256; i++)
		{
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
			m_image.SetColorTable(0, 256, rgb);
		}
	}
	int nPitch = m_image.GetPitch(); // 이미지 한줄을 말한다. 메모리 배열의 한칸 
	unsigned char* fm = (unsigned char*)m_image.GetBits();// 이미지의 첫번째 포인터 값을 fm에 담는다. // 이게 단순 대입이 아니라 자체 값을 바꾸는거 인듯 
	// 여기서 이게 색깔 바꿔주는거지? 왜? 어떻게? fm 을 이용해서 그리는게 아니지않나? 맞았다 아닌게 아니였다.

	memset(fm, 0xff, sizeof(unsigned char) * nWidth * nHeight);// 전부다 어떤 값으로 바꿈 ?? 터졌네???? nheight -로 바꾸니니까 된다? 애초에 만들어질때 위아래가 뒤집어지게 만들어져서 그렇다? 
	// 애초에 c이미지가 위아래가 반전되게 만들어졌으니까  nheight에 -를 곱해주면 위에서 아래로 그리는게 아니라 아래에서 위로 그리니까 겱국은 제대로 나옴 



	UpdateDisplay();

}
void CMFCApplication3Dlg::UpdateDisplay() { // 화면에 그려주는 함수 

	CClientDC dc(this); //this는 현재 다이얼로그  dc의 초기화를 
	m_image.Draw(dc, 0, 0); // dc에 0과 0 위치부터 그린다는 말인듯?:


}
void CMFCApplication3Dlg::drawCircle(UCHAR* fm, int x, int y, int nRadius, int nGray) {
	//CClientDC dc(this);
	//dc.Ellipse(10, 10, 100, 100);


	int nCenterX = x + nRadius;// 원 
	int nCenterY = y + nRadius;// 원 
	int nPitch = m_image.GetPitch();

	for (int j = y; j < y + nRadius * 2; j++) {
		for (int i = x; i < x + nRadius * 2; i++) {
			if (inInCircle(i, j, nCenterX, nCenterY, nRadius))
				fm[j * nPitch + i] = nGray;
		}// 메모리 
	}


}

BOOL CMFCApplication3Dlg::inInCircle(int i, int  j, int  nCenterX, int nCenterY, int  nRadius) {
	// 점의 좌표 i,j가 원안에 있는지 확인
	bool bRet = false;
	// 원둘레 
	double dX = i - nCenterX;
	double dY = j - nCenterY;
	double dDist = dX * dX + dY * dY; //피타고라스는 진짜 유명한 수학자임  두 점 사이의 거리 계산 

	if (dDist < nRadius * nRadius) {// 원안에 점이 위치하면 트루  점이 원안에 있으면 색칠하려고 하는 함수 네 
		bRet = true;

	}

	return bRet;
}

CString CMFCApplication3Dlg::GetSaveDataFileName(int x1, int y1, int nRadius)
{
	CString strPath, strTime;
	CTime t = CTime::GetCurrentTime();

	auto time = std::chrono::system_clock::now();
	auto mill = std::chrono::duration_cast<std::chrono::milliseconds>(time.time_since_epoch());

	long long currentTimeMillis = mill.count();
	int msc = currentTimeMillis % 1000;
	//long nowTime = currentTimeMillis / 1000;

	strTime.Format(_T("_%03d_%03d_%02d_%02d%02d_%02d%02d%02d%03d"), x1, y1, nRadius, t.GetMonth(), t.GetDay(), t.GetHour(), t.GetMinute(), t.GetSecond(), msc);
	CFileFind file ;
	CString strFile = _T("*.*"); // 폴더 경로 
	// 경로 폴더가 있다면 1, 없다면 0을 반환
	CString sDirName = _T("C:\\adadasdd/");
	BOOL bResult = file.FindFile(sDirName + strFile);
	if (!bResult) {
		bResult = CreateDirectory(sDirName + "\\", NULL);
	


	}



	return strPath + "C:\\adadasdd/" + strTime + ".jpg";
}

void CMFCApplication3Dlg::MoveRect() { // 첫번째 원 그리기 draw button
	UpdateData(TRUE);

	static int nSttX = xpintX1_;
	static int nSttY = ypintY1_;

	srand(time(NULL));



	CString g_strFileImage = _T("");
	int nGray = 80;
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();
	int nRadius = 10 + rand() % 90; //10 에서 99까지 랜덤 원크기 
	nRadius_ = nRadius;
	unsigned char* fm = (unsigned char*)m_image.GetBits();


	drawCircle(fm, nSttX, nSttY, nRadius, 0xff);// 원그려서 이동시키지 흰색 원그리기 

	nSttX = xpintX1_;
	nSttY = ypintY1_;
	cout << "nSttX: " << nSttX << "nSttY: " << nSttY << "nRadius: " << nRadius << endl;

	drawCircle(fm, nSttX, nSttY, nRadius, nGray);// 회색원  그리기 


	UpdateDisplay();
	//m_image.Save(g_strFileImage);


}



void CMFCApplication3Dlg::OnBnClickedButtonDraw()
{
	MoveRect();
}


void CMFCApplication3Dlg::OnBnClickedButtonAction()// action
{

	UpdateData(TRUE);

	srand(time(NULL));

	CString g_strFileImage = _T("");
	int nGray = 80;
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();

	unsigned char* fm = (unsigned char*)m_image.GetBits();

	int nSttX = xpintX1_; // 첫번째 좌표 
	int nSttY = ypintY1_;

	double dSttX = nSttX;
	double dSttY = nSttY;

	int xresult = xpintX2_ - nSttX;
	int yresult = ypintY2_ - nSttY;

	//점사이 거리 횟수로 나누기
	// 
	double count = rand() % 100;
	double xdistance = xresult / count;
	double ydistandce = yresult / count;
	cout << count << endl;
	int save_dSttX = xpintX2_;
	int save_dSttY = ypintY2_;
	for (int i = 0; i < count; i++)
	{
		//여기서 전역변수로 받아버려
		drawCircle(fm, dSttX, dSttY, nRadius_, 0xff);// 원그려서 이동시키지 흰색 원그리기 

		dSttX += xdistance;
		dSttY += ydistandce;

		//g_strFileImage = GetSaveDataFileName(save_dSttX, save_dSttY);

		//drawCircle(fm, nSttX++, nSttY++, nRadius, nGray);// 원그려서 이동시키지 연산자가 나중에 쓰여지면 흰색으로 지운 부분에 다시 회색으로  그리고 나서 증가해서
		// 의미 없어짐 
		drawCircle(fm, dSttX, dSttY, nRadius_, nGray);// 회색원  그리기 
		g_strFileImage = GetSaveDataFileName(dSttX, dSttY, nRadius_);// 이게 잘못됨 이동중 좌표 


		UpdateDisplay();
		m_image.Save(g_strFileImage);
		//}
	}
}


void CMFCApplication3Dlg::OnBnClickedButton2() // LOAD
{
	UpdateData();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString str = _T("All files(*.*)|*.*|"); // 모든 파일 표시
	// _T("Excel 파일 (*.xls, *.xlsx) |*.xls; *.xlsx|"); 와 같이 확장자를 제한하여 표시할 수 있음
	CFileDialog dlg(TRUE, _T("*.dat"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, str, this);
	//sPath는 초기에 오픈하고 싶은 폴더 경로
	CString sPath = _T("C:\\adadasdd/");
	dlg.m_ofn.lpstrInitialDir = sPath;
	CString strPathName;
	if (dlg.DoModal() == IDOK)
	{
		strPathName = dlg.GetPathName();
		if (m_image != NULL) {
			m_image.Destroy();

		}

		m_image.Load(strPathName);
		fm = (unsigned char*)m_image.GetBits();
		//cout << "nPitch1111111" << m_image.GetPitch() << endl;
		UpdateDisplay();


	}


	int nGray = 0;
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();
	int nRadius = 5;
	//unsigned char* fm = (unsigned char*)m_image.GetBits();
	cout << "strpath" << string(CT2CA(strPathName)) << endl;

	CString xypos = _T("");// y
	CString xypos1 = _T("");//x
	CString tRadius = _T("");
	int xpos = 0;
	int ypos = 0;
	int radiuspos = 0;
	int retval;
	int retval1;
	int retval2;// radius;

	AfxExtractSubString(xypos, strPathName, 1, *"_");
	AfxExtractSubString(xypos1, strPathName, 2, *"_");
	AfxExtractSubString(tRadius, strPathName, 3, *"_");
	cout << "xypos: " << string(CT2CA(xypos)) << endl;
	cout << "xypos1: " << string(CT2CA(xypos1)) << endl;
	cout << "tRadius: " << string(CT2CA(tRadius)) << endl;
	cout << "strPathName: " << string(CT2CA(strPathName)) << endl;

	retval = xypos.Find(*"_");
	retval1 = xypos1.Find(*"_");
	retval2 = tRadius.Find(*"_");
	cout << "retval" << retval << "retval1" << retval1 << "retval2" << retval2;
	cout << retval << endl;
	xpos = _ttoi(xypos.Mid(retval));
	ypos = _ttoi(xypos1.Mid(retval1));
	radiuspos = _ttoi(tRadius.Mid(retval2));

	// 반지름 
	cout << "xpos: " << xpos << "ypos: " << ypos << "radiuspos: " << radiuspos << endl;
	//drawCircle(fm, xpos, ypos, nRadius, nGray);
	drawX(fm, xpos + radiuspos, ypos + radiuspos, radiuspos);

	CString StaticXypos1;
	StaticXypos1.Format(_T("(%d,%d)"), xpos, ypos);
	SetDlgItemText(IDC_STATIC_XYPOS, StaticXypos1);

	//UpdateDisplay();



}

void CMFCApplication3Dlg::drawX(UCHAR* fm1, int x, int y, int radius) {
	int nPitch = m_image.GetPitch();
	cout << "nPitch" << nPitch << endl;
	cout << "X:" << x << "Y:" << y << endl;
	UpdateData();

	CClientDC dc(this);

	CPen pen;
	pen.CreatePen(PS_SOLID, 5, RGB(255, 0, 0));    // 빨간색 펜 생성

	CPen* oldPen = dc.SelectObject(&pen);

	//dc.MoveTo(x-200, y-200); // 시작 점  
	//dc.LineTo(x+200,y+200 );
	//dc.SelectObject(oldPen);

	cout << "x: " << x << "y: " << y << endl;
	dc.MoveTo(x - 10, y - 10); // 시작 점  
	dc.LineTo(x + 10, y + 10);
	dc.MoveTo(x + 10, y - 10); // 시작 점  
	dc.LineTo(x - 10, y + 10);
	dc.SelectObject(oldPen);


	cout << "aaaa" << x << y;







}