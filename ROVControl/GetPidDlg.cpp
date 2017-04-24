// GetPidDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ROVControl.h"
#include "GetPidDlg.h"
#include "afxdialogex.h"
#include "TcpServeDlg.h"
#include "GlobalVar.h"


// CGetPidDlg �Ի���

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


// CGetPidDlg ��Ϣ�������


void CGetPidDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTcpServeDlg::GetMotorValue(MOTOR_PID);
}


BOOL CGetPidDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetTimer(1,500,NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CGetPidDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	UpdateData(FALSE);

	CDialogEx::OnTimer(nIDEvent);
}
