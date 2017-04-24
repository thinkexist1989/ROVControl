
// MainDlg.h : 头文件
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

// CMainDlg 对话框
class CMainDlg : public CDialogEx
{
// 构造
public:
	CMainDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_ROVCONTROL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CLoadingDlg m_LoadingDlg;   //登陆显示对话框

	CTcpServeDlg m_tcpServeDlg;	// TCP通讯对话框
	CJoyStickDlg m_JoyStickDlg; // 手柄通讯对话框
	CLoginDlg	 m_LoginDlg;     //摄像头登陆对话框
	CPIDDlg      m_PidDlg;      //PID控制对话框
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
	// //利用指示灯显示前进指令
	CIledarrow m_moveForward;
	// //显示转动指令
	CIrotationdisplay m_rotation;
	CIledarrow m_moveLeft;
	CIledarrow m_moveRight;
	CIledarrow m_moveBackward;
	afx_msg void OnBnClickedButtonLight();
	afx_msg void OnPidcurve();
};
