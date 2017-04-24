// MotorTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ROVControl.h"
#include "MotorTestDlg.h"
#include "afxdialogex.h"
#include "GlobalVar.h"
#include "TcpServeDlg.h"

#define  TIMER1  1


// CMotorTestDlg 对话框

IMPLEMENT_DYNAMIC(CMotorTestDlg, CDialogEx)

CMotorTestDlg::CMotorTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMotorTestDlg::IDD, pParent)
{
}

CMotorTestDlg::~CMotorTestDlg()
{
}

void CMotorTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_MOTOR1, m_motor1Value);
	DDX_Control(pDX, IDC_SLIDER_MOTOR2, m_motor2Value);
	DDX_Control(pDX, IDC_SLIDER_MOTOR3, m_motor3Value);
	DDX_Control(pDX, IDC_SLIDER_MOTOR4, m_motor4Value);
	DDX_Control(pDX, IDC_SLIDER_MOTOR5, m_motor5Value);
	DDX_Control(pDX, IDC_SLIDER_MOTOR6, m_motor6Value);
	DDX_Control(pDX, IDC_SLIDER_MOTOR7, m_motor7Value);
	DDX_Control(pDX, IDC_SLIDER_MOTOR8, m_motor8Value);


    DDX_Text(pDX, IDC_N1,GlobalVar::motor_N1);
}


BEGIN_MESSAGE_MAP(CMotorTestDlg, CDialogEx)

	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_RESET, &CMotorTestDlg::OnBnClickedBtnReset)
	ON_BN_CLICKED(IDC_BTN_SEND, &CMotorTestDlg::OnBnClickedBtnSend)
END_MESSAGE_MAP()


// CMotorTestDlg 消息处理程序


BOOL CMotorTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_motor1Value.SetRange(-2550,2550,TRUE);
	m_motor1Value.SetPos(0);
	SetDlgItemInt(IDC_MOTOR1,m_motor1Value.GetPos());

	m_motor2Value.SetRange(-2550,2550,TRUE);
	m_motor2Value.SetPos(0);
	SetDlgItemInt(IDC_MOTOR2,m_motor2Value.GetPos());

	m_motor3Value.SetRange(-2550,2550,TRUE);
	m_motor3Value.SetPos(0);
	SetDlgItemInt(IDC_MOTOR3,m_motor3Value.GetPos());

	m_motor4Value.SetRange(-2550,2550,TRUE);
	m_motor4Value.SetPos(0);
	SetDlgItemInt(IDC_MOTOR4,m_motor4Value.GetPos());

	m_motor5Value.SetRange(-2550,2550,TRUE);
	m_motor5Value.SetPos(0);
	SetDlgItemInt(IDC_MOTOR5,m_motor5Value.GetPos());

	m_motor6Value.SetRange(-2550,2550,TRUE);
	m_motor6Value.SetPos(0);
	SetDlgItemInt(IDC_MOTOR6,m_motor6Value.GetPos());

	m_motor7Value.SetRange(-2550,2550,TRUE);
	m_motor7Value.SetPos(0);
	SetDlgItemInt(IDC_MOTOR7,m_motor7Value.GetPos());

	m_motor8Value.SetRange(-2550,2550,TRUE);
	m_motor8Value.SetPos(0);
	SetDlgItemInt(IDC_MOTOR8,m_motor8Value.GetPos());

	SetTimer(TIMER1,200,NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CMotorTestDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	GlobalVar::motor_send[0] = m_motor1Value.GetPos();
	SetDlgItemInt(IDC_MOTOR1,GlobalVar::motor_send[0]);
	SetDlgItemInt(IDC_N1,GlobalVar::motor_N1);

	GlobalVar::motor_send[1] = m_motor2Value.GetPos();
	SetDlgItemInt(IDC_MOTOR2,GlobalVar::motor_send[1]);
	SetDlgItemInt(IDC_N2,GlobalVar::motor_N2);

	GlobalVar::motor_send[2] = m_motor3Value.GetPos();
	SetDlgItemInt(IDC_MOTOR3,GlobalVar::motor_send[2]);
	SetDlgItemInt(IDC_N3,GlobalVar::motor_N3);

	GlobalVar::motor_send[3] = m_motor4Value.GetPos();
	SetDlgItemInt(IDC_MOTOR4,GlobalVar::motor_send[3]);
	SetDlgItemInt(IDC_N4,GlobalVar::motor_N4);

	GlobalVar::motor_send[4] = m_motor5Value.GetPos();
	SetDlgItemInt(IDC_MOTOR5,GlobalVar::motor_send[4]);
	SetDlgItemInt(IDC_N5,GlobalVar::motor_N5);

	GlobalVar::motor_send[5] = m_motor6Value.GetPos();
	SetDlgItemInt(IDC_MOTOR6,GlobalVar::motor_send[5]);
	SetDlgItemInt(IDC_N6,GlobalVar::motor_N6);

	GlobalVar::motor_send[6] = m_motor7Value.GetPos();
	SetDlgItemInt(IDC_MOTOR7,GlobalVar::motor_send[6]);
	SetDlgItemInt(IDC_N7,GlobalVar::motor_N7);

	GlobalVar::motor_send[7] = m_motor8Value.GetPos();
	SetDlgItemInt(IDC_MOTOR8,GlobalVar::motor_send[7]);
	SetDlgItemInt(IDC_N8,GlobalVar::motor_N8);

	//UpdateData(FALSE);
	//SendMotorSpeed();

	CDialogEx::OnTimer(nIDEvent);
}


void CMotorTestDlg::OnBnClickedBtnReset()
{
	// TODO: 在此添加控件通知处理程序代码
	m_motor1Value.SetPos(0);
	m_motor2Value.SetPos(0);
	m_motor3Value.SetPos(0);
	m_motor4Value.SetPos(0);
	m_motor5Value.SetPos(0);
	m_motor6Value.SetPos(0);
	m_motor7Value.SetPos(0);
	m_motor8Value.SetPos(0);
}

void CMotorTestDlg::SendMotorSpeed()
{
	CTcpServeDlg::SendMotorSpeed();
}

void CMotorTestDlg::OnBnClickedBtnSend()
{
	// TODO: 在此添加控件通知处理程序代码
	SendMotorSpeed();
}
