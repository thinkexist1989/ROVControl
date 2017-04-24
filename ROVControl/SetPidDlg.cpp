// SetPidDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ROVControl.h"
#include "SetPidDlg.h"
#include "afxdialogex.h"
#include "GlobalVar.h"
#include "TcpServeDlg.h"


// CSetPidDlg 对话框

IMPLEMENT_DYNAMIC(CSetPidDlg, CDialogEx)

CSetPidDlg::CSetPidDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetPidDlg::IDD, pParent)
	, m_p1(0.20), m_p2(0.015),  m_p3(0.20),  m_p4(0.15), m_p5(0.20), m_p6(0.15), m_p7(0.20), m_p8(0.60)
	, m_i1(0.10),  m_i2(0.10),  m_i3(0.10),  m_i4(0.08), m_i5(0.10), m_i6(0.15), m_i7(0.05), m_i8(0.20)
	, m_d1(0.10),  m_d2(0.10),  m_d3(0.10),  m_d4(0.10), m_d5(0.10), m_d6(0.10), m_d7(0.10), m_d8(0.10)
{

}

CSetPidDlg::~CSetPidDlg()
{
}

void CSetPidDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_P1, m_p1);
	DDX_Text(pDX, IDC_P2, m_p2);
	DDX_Text(pDX, IDC_P3, m_p3);
	DDX_Text(pDX, IDC_P4, m_p4);
	DDX_Text(pDX, IDC_P5, m_p5);
	DDX_Text(pDX, IDC_P6, m_p6);
	DDX_Text(pDX, IDC_P7, m_p7);
	DDX_Text(pDX, IDC_P8, m_p8);

	DDX_Text(pDX, IDC_I1, m_i1);
	DDX_Text(pDX, IDC_I2, m_i2);
	DDX_Text(pDX, IDC_I3, m_i3);
	DDX_Text(pDX, IDC_I4, m_i4);
	DDX_Text(pDX, IDC_I5, m_i5);
	DDX_Text(pDX, IDC_I6, m_i6);
	DDX_Text(pDX, IDC_I7, m_i7);
	DDX_Text(pDX, IDC_I8, m_i8);

	DDX_Text(pDX, IDC_D1, m_d1);
	DDX_Text(pDX, IDC_D2, m_d2);
	DDX_Text(pDX, IDC_D3, m_d3);
	DDX_Text(pDX, IDC_D4, m_d4);
	DDX_Text(pDX, IDC_D5, m_d5);
	DDX_Text(pDX, IDC_D6, m_d6);
	DDX_Text(pDX, IDC_D7, m_d7);
	DDX_Text(pDX, IDC_D8, m_d8);
}


BEGIN_MESSAGE_MAP(CSetPidDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSetPidDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDOK5, &CSetPidDlg::OnBnClickedOk5)
	ON_BN_CLICKED(IDOK3, &CSetPidDlg::OnBnClickedOk3)
	ON_BN_CLICKED(IDOK4, &CSetPidDlg::OnBnClickedOk4)
END_MESSAGE_MAP()


// CSetPidDlg 消息处理程序


void CSetPidDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CTcpServeDlg::SetMotorPID(MOTOR_GET_P,m_p1,m_p2,m_p3,m_p4,m_p5,m_p6,m_p7,m_p8);
	
}


void CSetPidDlg::OnBnClickedOk5()
{
	// TODO: 在此添加控件通知处理程序代码
	int n1 = GetDlgItemInt(IDC_TEST_N1);
	int n2 = GetDlgItemInt(IDC_TEST_N2);
	int n3 = GetDlgItemInt(IDC_TEST_N3);
	int n4 = GetDlgItemInt(IDC_TEST_N4);
	int n5 = GetDlgItemInt(IDC_TEST_N5);
	int n6 = GetDlgItemInt(IDC_TEST_N6);
	int n7 = GetDlgItemInt(IDC_TEST_N7);
	int n8 = GetDlgItemInt(IDC_TEST_N8);

	CTcpServeDlg::SendMotorN(n1,n2,n3,n4,n5,n6,n7,n8);
}


void CSetPidDlg::OnBnClickedOk3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CTcpServeDlg::SetMotorPID(MOTOR_GET_I,m_i1,m_i2,m_i3,m_i4,m_i5,m_i6,m_i7,m_i8);
}


void CSetPidDlg::OnBnClickedOk4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CTcpServeDlg::SetMotorPID(MOTOR_GET_D,m_d1,m_d2,m_d3,m_d4,m_d5,m_d6,m_d7,m_d8);
}
