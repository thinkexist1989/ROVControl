// LoadingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ROVControl.h"
#include "LoadingDlg.h"
#include "afxdialogex.h"


// CLoadingDlg �Ի���

IMPLEMENT_DYNAMIC(CLoadingDlg, CDialogEx)

CLoadingDlg::CLoadingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoadingDlg::IDD, pParent)
	, a(FALSE)
	, b(FALSE)
{
	m_img.LoadFromResource(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_LOADING_BITMAP));
}

CLoadingDlg::~CLoadingDlg()
{
}

void CLoadingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLoadingDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_TIMER()
//	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CLoadingDlg ��Ϣ�������


BOOL CLoadingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetWindowPos(NULL, 0, 0, 512, 384, SWP_NOMOVE);
	CenterWindow();

	//m_img.LoadFromResource(AfxGetResourceHandle(), IDB_LOADING_BITMAP);
	if (a == FALSE)
	{ 
		SetTimer(1, 2000, NULL);
		a = TRUE;
	}
	else
	{
		b = TRUE;
	}



	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CLoadingDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	//CWindowDC dc(this);
	//img.Load(_T("SplashScreenLarge2560.png"));

	dc.SetStretchBltMode(COLORONCOLOR);
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(255, 255, 255));


	if (!m_img.IsNull())
		m_img.Draw(dc.m_hDC, 0, 0, 512, 384);
	
	
	
	POINT a;
	a.x = 280;   a.y = 335;
	SIZE b;
	b.cx = 100; b.cy = 100;
	CRect rec = CRect(a, b);
	
	CFont newFont, *oldFont;
	newFont.CreatePointFont(110, "Segoe Script");

	oldFont = dc.SelectObject(&newFont);
	dc.DrawText(VERSION, &rec, DT_SINGLELINE | DT_CENTER);
	dc.SelectObject(oldFont);

	if (this->b == TRUE){
		POINT a;
		a.x = 100;   a.y = 100;
		SIZE b;
		b.cx = 200; b.cy = 100;
		CRect rec = CRect(a, b);
		CFont newFont, *oldFont;
		newFont.CreatePointFont(110, "΢���ź�");

		oldFont = dc.SelectObject(&newFont);

		char* s = new char[300];
		sprintf(s, "�����д��%s\
				  \r\r��д���ڣ�%s\
				  \r\rTEL:%s",PROGRAMMER,PROGDATE,TEL);
		dc.DrawText(s, &rec, DT_LEFT);
		dc.SelectObject(oldFont);
	}
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}


void CLoadingDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	OnCancel();
	CDialogEx::OnTimer(nIDEvent);
}

void CLoadingDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	OnCancel();
	CDialogEx::OnLButtonUp(nFlags, point);
}
