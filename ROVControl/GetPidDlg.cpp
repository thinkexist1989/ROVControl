// GetPidDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ROVControl.h"
#include "GetPidDlg.h"
#include "afxdialogex.h"
#include "TcpServeDlg.h"
#include "GlobalVar.h"


// CGetPidDlg 对话框

IMPLEMENT_DYNAMIC(CGetPidDlg, CDialogEx)

CGetPidDlg::CGetPidDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGetPidDlg::IDD, pParent)
{

}

CGetPidDlg::~CGetPidDlg()
{
}

void CGetPidDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_P1, GlobalVar::motor_p[0]);
	DDX_Text(pDX, IDC_P2, GlobalVar::motor_p[1]);
	DDX_Text(pDX, IDC_P3, GlobalVar::motor_p[2]);
	DDX_Text(pDX, IDC_P4, GlobalVar::motor_p[3]);
	DDX_Text(pDX, IDC_P5, GlobalVar::motor_p[4]);
	DDX_Text(pDX, IDC_P6, GlobalVar::motor_p[5]);
	DDX_Text(pDX, IDC_P7, GlobalVar::motor_p[6]);
	DDX_Text(pDX, IDC_P8, GlobalVar::motor_p[7]);

	DDX_Text(pDX, IDC_I1, GlobalVar::motor_i[0]);
	DDX_Text(pDX, IDC_I2, GlobalVar::motor_i[1]);
	DDX_Text(pDX, IDC_I3, GlobalVar::motor_i[2]);
	DDX_Text(pDX, IDC_I4, GlobalVar::motor_i[3]);
	DDX_Text(pDX, IDC_I5, GlobalVar::motor_i[4]);
	DDX_Text(pDX, IDC_I6, GlobalVar::motor_i[5]);
	DDX_Text(pDX, IDC_I7, GlobalVar::motor_i[6]);
	DDX_Text(pDX, IDC_I8, GlobalVar::motor_i[7]);

	DDX_Text(pDX, IDC_D1, GlobalVar::motor_d[0]);
	DDX_Text(pDX, IDC_D2, GlobalVar::motor_d[1]);
	DDX_Text(pDX, IDC_D3, GlobalVar::motor_d[2]);
	DDX_Text(pDX, IDC_D4, GlobalVar::motor_d[3]);
	DDX_Text(pDX, IDC_D5, GlobalVar::motor_d[4]);
	DDX_Text(pDX, IDC_D6, GlobalVar::motor_d[5]);
	DDX_Text(pDX, IDC_D7, GlobalVar::motor_d[6]);
	DDX_Text(pDX, IDC_D8, GlobalVar::motor_d[7]);
}


BEGIN_MESSAGE_MAP(CGetPidDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CGetPidDlg::OnBnClickedOk)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CGetPidDlg 消息处理程序


void CGetPidDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CTcpServeDlg::GetMotorValue(MOTOR_PID);
}


BOOL CGetPidDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetTimer(1,500,NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CGetPidDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	UpdateData(FALSE);

	CDialogEx::OnTimer(nIDEvent);
}
