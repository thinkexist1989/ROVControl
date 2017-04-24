// PIDDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ROVControl.h"
#include "PIDDlg.h"
#include "afxdialogex.h"
#include "GlobalVar.h"


// CPIDDlg 对话框

IMPLEMENT_DYNAMIC(CPIDDlg, CDialogEx)

CPIDDlg::CPIDDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPIDDlg::IDD, pParent)
	, m_Kp_Deep(0)
	, m_Kd_Deep(0)
	, m_Ki_Deep(0)
	, m_Kp_Yaw(0)
	, m_Kd_Yaw(0)
	, m_Ki_Yaw(0)
	, m_Kp_Pitch(0)
	, m_Kd_Pitch(0)
	, m_Ki_Pitch(0)
	, m_Kp_Roll(0)
	, m_Kd_Roll(0)
	, m_Ki_Roll(0)
{

}

CPIDDlg::~CPIDDlg()
{
}

void CPIDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ISWITCHLED_DEEP, m_pidDeepOK);
	DDX_Control(pDX, IDC_ISWITCHLED_YAW, m_pidYawOK);
	DDX_Control(pDX, IDC_ISWITCHLED_PITCH, m_pidPitchOK);
	DDX_Control(pDX, IDC_ISWITCHLED_ROLL, m_pidRollOK);
	DDX_Text(pDX, IDC_KP_DEEP, m_Kp_Deep);
	DDX_Text(pDX, IDC_KD_DEEP, m_Kd_Deep);
	DDX_Text(pDX, IDC_KI_DEEP, m_Ki_Deep);
	DDX_Text(pDX, IDC_KP_YAW, m_Kp_Yaw);
	DDX_Text(pDX, IDC_KD_YAW, m_Kd_Yaw);
	DDX_Text(pDX, IDC_KI_YAW, m_Ki_Yaw);
	DDX_Text(pDX, IDC_KP_PITCH, m_Kp_Pitch);
	DDX_Text(pDX, IDC_KD_PITCH, m_Kd_Pitch);
	DDX_Text(pDX, IDC_KI_PITCH, m_Ki_Pitch);
	DDX_Text(pDX, IDC_KP_ROLL, m_Kp_Roll);
	DDX_Text(pDX, IDC_KD_ROLL, m_Kd_Roll);
	DDX_Text(pDX, IDC_KI_ROLL, m_Ki_Roll);
}


BEGIN_MESSAGE_MAP(CPIDDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CPIDDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CPIDDlg 消息处理程序


void CPIDDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if (m_pidDeepOK.get_Active() == TRUE){
		GlobalVar::pidDeep->m_bEnalbed = TRUE;
		GlobalVar::pidDeep->Kp = m_Kp_Deep;
		GlobalVar::pidDeep->Kd = m_Kd_Deep;
		GlobalVar::pidDeep->Ki = m_Ki_Deep;
	}
	else
	{
		GlobalVar::pidDeep->m_bEnalbed = FALSE;
		GlobalVar::pidDeep->Kp = 0;
		GlobalVar::pidDeep->Kd = 0;
		GlobalVar::pidDeep->Ki = 0;
	}

	if (m_pidYawOK.get_Active() == TRUE){
		GlobalVar::pidYaw->m_bEnalbed = TRUE;
		GlobalVar::pidYaw->Kp = m_Kp_Yaw;
		GlobalVar::pidYaw->Kd = m_Kd_Yaw;
		GlobalVar::pidYaw->Ki = m_Ki_Yaw;
	}
	else
	{
		GlobalVar::pidYaw->m_bEnalbed = FALSE;
		GlobalVar::pidYaw->Kp = 0;
		GlobalVar::pidYaw->Kd = 0;
		GlobalVar::pidYaw->Ki = 0;
	}

	if (m_pidPitchOK.get_Active() == TRUE){
		GlobalVar::pidPitch->m_bEnalbed = TRUE;
		GlobalVar::pidPitch->Kp = m_Kp_Pitch;
		GlobalVar::pidPitch->Kd = m_Kd_Pitch;
		GlobalVar::pidPitch->Ki = m_Ki_Pitch;
	}
	else
	{
		GlobalVar::pidPitch->m_bEnalbed = FALSE;
		GlobalVar::pidPitch->Kp = 0;
		GlobalVar::pidPitch->Kd = 0;
		GlobalVar::pidPitch->Ki = 0;
	}

	if (m_pidRollOK.get_Active() == TRUE){
		GlobalVar::pidRoll->m_bEnalbed = TRUE;
		GlobalVar::pidRoll->Kp = m_Kp_Roll;
		GlobalVar::pidRoll->Kd = m_Kd_Roll;
		GlobalVar::pidRoll->Ki = m_Ki_Roll;
	}
	else
	{
		GlobalVar::pidRoll->m_bEnalbed = FALSE;
		GlobalVar::pidRoll->Kp = 0;
		GlobalVar::pidRoll->Kd = 0;
		GlobalVar::pidRoll->Ki = 0;
	}
	
	//CDialogEx::OnOK();

}
