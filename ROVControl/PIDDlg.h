#pragma once
#include "iswitchled_deep.h"


// CPIDDlg �Ի���

class CPIDDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPIDDlg)

public:
	CPIDDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPIDDlg();

// �Ի�������
	enum { IDD = IDD_PID_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CIswitchled_deep m_pidDeepOK;
	CIswitchled_deep m_pidYawOK;
	CIswitchled_deep m_pidPitchOK;
	CIswitchled_deep m_pidRollOK;
	float m_Kp_Deep;
	float m_Kd_Deep;
	float m_Ki_Deep;
	float m_Kp_Yaw;
	float m_Kd_Yaw;
	float m_Ki_Yaw;
	float m_Kp_Pitch;
	float m_Kd_Pitch;
	float m_Ki_Pitch;
	float m_Kp_Roll;
	float m_Kd_Roll;
	float m_Ki_Roll;
};
