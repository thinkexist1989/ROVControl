// JoySickDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ROVControl.h"
#include "JoySickDlg.h"
#include "afxdialogex.h"


// CJoySickDlg 对话框

IMPLEMENT_DYNAMIC(CJoyStickDlg, CDialogEx)

CJoyStickDlg::CJoyStickDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CJoyStickDlg::IDD, pParent)
{
	m_Down = FALSE;
	m_Fire = FALSE;
	m_Left = FALSE;
	m_Right = FALSE;
	m_Up = FALSE;

	m_XAxis = 0;
	m_YAxis = 0;
	m_ZAxis = 0;
	m_RxAxis = 0;
	m_RyAxis = 0;
	m_RzAxis = 0;
}

CJoyStickDlg::~CJoyStickDlg()
{
}

void CJoyStickDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Check(pDX, IDC_UP, m_Left);
	DDX_Check(pDX, IDC_RIGHT, m_Right);
	DDX_Check(pDX, IDC_UP, m_Up);
	DDX_Check(pDX, IDC_LEFT, m_Left);
	DDX_Check(pDX, IDC_FIRE, m_Fire);
	DDX_Control(pDX, IDC_JOYSTICK_NAME, m_JoyStickName);
	DDX_Check(pDX, IDC_DOWN, m_Down);
	DDX_Text(pDX, IDC_XAxis, m_XAxis);
	DDX_Text(pDX, IDC_YAxis, m_YAxis);
	DDX_Text(pDX, IDC_ZAxis, m_ZAxis);
	DDX_Text(pDX, IDC_RxAxis, m_RxAxis);
	DDX_Text(pDX, IDC_RyAxis, m_RyAxis);
	DDX_Text(pDX, IDC_RzAxis, m_RzAxis);
}


BEGIN_MESSAGE_MAP(CJoyStickDlg, CDialogEx)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_CTLPNL, &CJoyStickDlg::OnBnClickedBtnCtlpnl)
END_MESSAGE_MAP()


// CJoySickDlg 消息处理程序


BOOL CJoyStickDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//////////////////////////////////////////////////////////////////////
	//
	// Set the HWND for this Dialog Instance To Enable DInput!
	//
	//////////////////////////////////////////////////////////////////////

	m_Joystick.StartToDo();

	CWnd *jb=this;

	m_Joystick.SetHWND(jb->m_hWnd);

	// Reset Combo Control
	m_JoyStickName.ResetContent();

	LPCDIDEVICEINSTANCE lpddi=NULL;

	// Ensure you have First Joystick ID to start search for additional Devices!
	lpddi=m_Joystick.GetFirstJoystickID();

	if(!lpddi)
	{
		// No joysticks have been found!
		MessageBox("Can't find a joystick on your system.","No Joystick Detected",MB_ICONHAND|MB_OK);
		//return FALSE;
		//DestroyWindow();
		//this->OnCancel();
		OnCancel();
	}
	else
	{

		while(lpddi)
		{
			int x = m_JoyStickName.AddString(lpddi->tszInstanceName);
			m_JoyStickName.SetItemDataPtr(x,(void*)lpddi);
			lpddi=m_Joystick.GetNextJoystickID();
		}

		m_JoyStickName.SetCurSel(0);
		OnSelchangeButtonNames();

		SetTimer(TIMERID,50,NULL);

		return TRUE;  // return TRUE unless you set the focus to a control
		// EXCEPTION: OCX Property Pages should return FALSE
	}
	return TRUE;  // return TRUE  unless you set the focus to a control

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CJoyStickDlg::OnSelchangeButtonNames()
{
	CWnd* jb = this;
	m_Joystick.SetHWND(jb->m_hWnd);

	LPCDIDEVICEINSTANCE lpddi=NULL;

	//m_ctlButtonNames.ResetContent();

	int x=m_JoyStickName.GetCurSel();

	lpddi=(LPCDIDEVICEINSTANCE)m_JoyStickName.GetItemDataPtr(x);

	GUID myguid;

	if(lpddi && ((int)lpddi!=-1))
	{

		memcpy(&myguid,&(lpddi->guidInstance),sizeof(GUID));

		m_Joystick.SetPreferredDevice(&myguid);

		m_Buttons=m_Joystick.HowManyButtons();

		//char* name = NULL;
		//name=m_Joystick.GetFirstButtonName();

		//while(name)
		//{
		//	m_ctlButtonNames.AddString(name);
		//	name=myJoystick1.GetNextButtonName();
		//}
	}

	/*m_ctlButtonNames.SetCurSel(0);	*/
}


void CJoyStickDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	CDialogEx::OnCancel();
}


void CJoyStickDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_Joystick.PollDevice();

	if(m_Joystick.IsJoystickLeft()) m_Left = true; else m_Left=false;
	if(m_Joystick.IsJoystickRight()) m_Right = true; else m_Right=false;
	if(m_Joystick.IsJoystickUp()) m_Up = true; else m_Up=false;
	if(m_Joystick.IsJoystickDown()) m_Down = true; else m_Down=false;
	if(m_Joystick.IsJoystickFire()) m_Fire = true; else m_Fire=false;

	m_joyState = m_Joystick.GetJoystickStateInfo();

	m_XAxis = m_joyState->lX/10000.0*2550;
	m_YAxis = -m_joyState->lY/10000.0*2550;
	//m_ZAxis = (-m_joyState->lZ + 10000)/2;
	m_ZAxis = -m_joyState->lZ/10000.0*2550;

	m_RxAxis = m_joyState->lRx/10000.0*2550;
	m_RyAxis = m_joyState->lRy/10000.0*2550;
	m_RzAxis = -m_joyState->lRz/10000.0*2550;

	//m_FireText.Empty();

	//for(int i=0;i<m_Buttons;i++){
	//	if(myJoystick1.IsJoystickFire(i)){
	//		CString temp;
	//		temp.Format("Fire Button : %d\r\n",i);
	//		m_FireText+=temp;
	//	}
	//}

	UpdateData(FALSE);  //将值赋给控件

	CDialogEx::OnTimer(nIDEvent);
}




void CJoyStickDlg::OnBnClickedBtnCtlpnl()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Joystick.RunControlPanel();
}
