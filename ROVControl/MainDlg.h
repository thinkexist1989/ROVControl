
// MainDlg.h : ͷ�ļ�
//

#pragma once

#include "TcpServeDlg.h"
#include "MotorTestDlg.h"
#include "JoySickDlg.h"
#include "LoginDlg.h"
#include "PIDDlg.h"

#include "iangulargaugex1.h"
#include "ilineargaugex1.h"
#include "icompassx1.h"

#include "GlobalVar.h"
#include "LoadingDlg.h"

#include <fstream>

#include "DlgResizeHelper.h"
#include "iledarrow.h"
#include "irotationdisplay.h"

#include "PIDCurveDlg.h"

// CMainDlg �Ի���
class CMainDlg : public CDialogEx
{
// ����
public:
	CMainDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ROVCONTROL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CLoadingDlg m_LoadingDlg;   //��½��ʾ�Ի���

	CTcpServeDlg m_tcpServeDlg;	// TCPͨѶ�Ի���
	CJoyStickDlg m_JoyStickDlg; // �ֱ�ͨѶ�Ի���
	CLoginDlg	 m_LoginDlg;     //����ͷ��½�Ի���
	CPIDDlg      m_PidDlg;      //PID���ƶԻ���
	BOOL		 m_bTcp;
	BOOL		 m_bJoyStick;
	BOOL		 m_bPreview;
	BOOL		 m_bPID;
	BOOL		 m_bMotorTest;
	BOOL		 m_bPIDCurve; 
	std::fstream m_angleCompensationFile;


public:
	afx_msg void OnTcp();
	afx_msg void OnMotortest();
protected:
	afx_msg LRESULT OnTcpconnet(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnTcpdisconnect(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnJoystick();
	afx_msg void OnPreview();
//	afx_msg void OnStnClickedStaticPlay();
	afx_msg void OnStnDblclickStaticPlay();
	afx_msg void OnBnClickedBtnQuickstart();
	afx_msg void OnTimer(UINT_PTR nIDEvent);


public:
	CIangulargaugex1 m_motorX1;
	CIangulargaugex1 m_motorX2;
	CIangulargaugex1 m_motorX3;
	CIangulargaugex1 m_motorX4;
	CIangulargaugex1 m_motorX5;
	CIangulargaugex1 m_motorX6;
	CIangulargaugex1 m_motorX7;
	CIangulargaugex1 m_motorX8;
	CIlineargaugex1 m_deepX;
	CIcompassx1      m_yawX;
	CIlineargaugex1 m_pitchX;
	CIangulargaugex1 m_rollX;
	afx_msg void OnCompensation();
	afx_msg void OnPid();
	afx_msg void OnAppAbout();
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DlgResizeHelper m_Resizehelper;
	// //����ָʾ����ʾǰ��ָ��
	CIledarrow m_moveForward;
	// //��ʾת��ָ��
	CIrotationdisplay m_rotation;
	CIledarrow m_moveLeft;
	CIledarrow m_moveRight;
	CIledarrow m_moveBackward;
	afx_msg void OnBnClickedButtonLight();
	afx_msg void OnPidcurve();
};
