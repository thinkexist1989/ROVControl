// PIDCurveDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ROVControl.h"
#include "PIDCurveDlg.h"
#include "afxdialogex.h"

#include "GlobalVar.h"


// CPIDCurveDlg 对话框

IMPLEMENT_DYNAMIC(CPIDCurveDlg, CDialogEx)

CPIDCurveDlg::CPIDCurveDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPIDCurveDlg::IDD, pParent)
	, count(0)
	, m_b1(TRUE)
	, m_bStart(true)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

CPIDCurveDlg::~CPIDCurveDlg()
{
}

void CPIDCurveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB, m_tab);
	DDX_Control(pDX, IDC_IPLOTX1, m_plot);
	DDX_Check(pDX, IDC_CHECK1, m_b1);
	DDX_Check(pDX, IDC_CHECK2, m_b2);
	DDX_Check(pDX, IDC_CHECK3, m_b3);
	DDX_Check(pDX, IDC_CHECK4, m_b4);
	DDX_Check(pDX, IDC_CHECK5, m_b5);
	DDX_Check(pDX, IDC_CHECK6, m_b6);
	DDX_Check(pDX, IDC_CHECK7, m_b7);
	DDX_Check(pDX, IDC_CHECK8, m_b8);
}


BEGIN_MESSAGE_MAP(CPIDCurveDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CPIDCurveDlg::OnBnClickedButton1)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, &CPIDCurveDlg::OnTcnSelchangeTab)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_START, &CPIDCurveDlg::OnBnClickedBtnStart)
	ON_BN_CLICKED(IDC_BTN_CLEAR, &CPIDCurveDlg::OnBnClickedBtnClear)
	ON_BN_CLICKED(IDC_CHECK1, &CPIDCurveDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CPIDCurveDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CPIDCurveDlg::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK4, &CPIDCurveDlg::OnBnClickedCheck4)
	ON_BN_CLICKED(IDC_CHECK5, &CPIDCurveDlg::OnBnClickedCheck5)
	ON_BN_CLICKED(IDC_CHECK6, &CPIDCurveDlg::OnBnClickedCheck6)
	ON_BN_CLICKED(IDC_CHECK7, &CPIDCurveDlg::OnBnClickedCheck7)
	ON_BN_CLICKED(IDC_CHECK8, &CPIDCurveDlg::OnBnClickedCheck8)
END_MESSAGE_MAP()


// CPIDCurveDlg 消息处理程序


void CPIDCurveDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	if(GetDlgItemText(IDC_BUTTON1,str),str == ">>"){
		SetDlgItemText(IDC_BUTTON1,"<<");
		SetWindowPos(NULL,0,0,m_rectLarge.Width(),m_rectLarge.Height(),SWP_NOMOVE|SWP_NOZORDER);

	}
	else{
		SetDlgItemText(IDC_BUTTON1,">>");
		SetWindowPos(NULL,0,0,m_rectSmall.Width(),m_rectSmall.Height(),SWP_NOMOVE|SWP_NOZORDER);
	}

}


BOOL CPIDCurveDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rectSeparator;

	if(m_rectLarge.IsRectNull()){
		GetWindowRect(&m_rectLarge);
		GetDlgItem(IDC_SEPARATOR)->GetWindowRect(&rectSeparator);
		m_rectSmall.top = m_rectLarge.top;
		m_rectSmall.bottom = m_rectLarge.bottom;
		m_rectSmall.left = m_rectLarge.left;
		m_rectSmall.right = rectSeparator.right;
	}
	SetWindowPos(NULL,0,0,m_rectSmall.Width(),m_rectSmall.Height(),SWP_NOMOVE|SWP_NOZORDER);

	TCITEM tc1,tc2;
	tc1.mask = TCIF_TEXT;
	tc1.pszText = _T("查询");
	tc2.mask = TCIF_TEXT;
	tc2.pszText = _T("设置");

	m_tab.InsertItem(0, &tc1);
	m_tab.InsertItem(1, &tc2); //到这里只是添加了两个tab页


	//m_tab.InsertItem(0,"查询");
	//m_tab.InsertItem(1,"设置");	

	//获得IDC_TABTEST客户区大小
	CRect rs;
	m_tab.GetClientRect(&rs);
	//调整子对话框在父窗口中的位置
	rs.top +=30; 
	rs.bottom -= 30; 
	rs.left+= 1; 
	rs.right-= 2; 

	m_getPidDlg.Create(IDD_GETPID,GetDlgItem(IDC_TAB));
	m_getPidDlg.MoveWindow(&rs);

	m_setPidDlg.Create(IDD_SETPID,GetDlgItem(IDC_TAB));
	m_setPidDlg.MoveWindow(&rs);
	
	m_getPidDlg.ShowWindow(TRUE);

	m_tab.SetCurSel(0);

	m_plot.GetChannel(0).SetVisible(m_b1);
	m_plot.GetChannel(1).SetVisible(m_b2);
	m_plot.GetChannel(2).SetVisible(m_b3);
	m_plot.GetChannel(3).SetVisible(m_b4);
	m_plot.GetChannel(4).SetVisible(m_b5);
	m_plot.GetChannel(5).SetVisible(m_b6);
	m_plot.GetChannel(6).SetVisible(m_b7);
	m_plot.GetChannel(7).SetVisible(m_b8);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CPIDCurveDlg::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	switch(m_tab.GetCurSel()){
		case 0:
			m_getPidDlg.ShowWindow(SW_SHOW);
			m_setPidDlg.ShowWindow(SW_HIDE);
			break;
		case 1:
			m_getPidDlg.ShowWindow(SW_HIDE);
			m_setPidDlg.ShowWindow(SW_SHOW);
			break;
		default:
			break;
	}
	
}


void CPIDCurveDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	UpdateData(TRUE);

	m_plot.GetChannel(0).AddXY(count,GlobalVar::motor_N1);
	m_plot.GetChannel(1).AddXY(count,GlobalVar::motor_N2);
	m_plot.GetChannel(2).AddXY(count,GlobalVar::motor_N3);
	m_plot.GetChannel(3).AddXY(count,GlobalVar::motor_N4);
	m_plot.GetChannel(4).AddXY(count,GlobalVar::motor_N5);
	m_plot.GetChannel(5).AddXY(count,GlobalVar::motor_N6);
	m_plot.GetChannel(6).AddXY(count,GlobalVar::motor_N7);
	m_plot.GetChannel(7).AddXY(count,GlobalVar::motor_N8);

	count++;

	CDialogEx::OnTimer(nIDEvent);
}



void CPIDCurveDlg::OnBnClickedBtnStart()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_bStart == true){
		SetDlgItemText(IDC_BTN_START,"停止记录");
		SetTimer(1,100,NULL);
		m_bStart = false;
	}
	else{
		SetDlgItemText(IDC_BTN_START,"开始记录");
		KillTimer(1);
		//count = 0;
		m_bStart = true;
	}
}


void CPIDCurveDlg::OnBnClickedBtnClear()
{
	// TODO: 在此添加控件通知处理程序代码
	m_plot.GetChannel(0).Clear();
	m_plot.GetChannel(1).Clear();
	m_plot.GetChannel(2).Clear();
	m_plot.GetChannel(3).Clear();
	m_plot.GetChannel(4).Clear();
	m_plot.GetChannel(5).Clear();
	m_plot.GetChannel(6).Clear();
	m_plot.GetChannel(7).Clear();
	count = 0;
}


void CPIDCurveDlg::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_plot.GetChannel(0).SetVisible(m_b1);
}


void CPIDCurveDlg::OnBnClickedCheck2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_plot.GetChannel(1).SetVisible(m_b2);
}


void CPIDCurveDlg::OnBnClickedCheck3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_plot.GetChannel(2).SetVisible(m_b3);
}


void CPIDCurveDlg::OnBnClickedCheck4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_plot.GetChannel(3).SetVisible(m_b4);
}


void CPIDCurveDlg::OnBnClickedCheck5()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_plot.GetChannel(4).SetVisible(m_b5);
}


void CPIDCurveDlg::OnBnClickedCheck6()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	UpdateData(TRUE);
	m_plot.GetChannel(5).SetVisible(m_b6);
}


void CPIDCurveDlg::OnBnClickedCheck7()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_plot.GetChannel(6).SetVisible(m_b7);
}


void CPIDCurveDlg::OnBnClickedCheck8()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_plot.GetChannel(7).SetVisible(m_b8);
}
