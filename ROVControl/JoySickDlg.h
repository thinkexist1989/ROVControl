#pragma once
#include "DIJoystick.h"

#define TIMERID   6

// CJoySickDlg �Ի���

class CJoyStickDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CJoyStickDlg)

public:
	CJoyStickDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CJoyStickDlg();

// �Ի�������
	enum { IDD = IDD_JOYSTICK_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	BOOL		 m_Right;
	BOOL		 m_Up;
	BOOL		 m_Left;
	BOOL		 m_Fire;
	CComboBox	 m_JoyStickName;
	BOOL		 m_Down;
	int			 m_Buttons;

	CDIJoystick m_Joystick;
	LPDIJOYSTATE m_joyState;
	
	int m_XAxis;
	int m_YAxis;
	int m_ZAxis;
	int m_RxAxis;
	int m_RyAxis;
	int m_RzAxis;
	
public:	
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeButtonNames();
	virtual void OnCancel();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnCtlpnl();



	int Get_FB() {return m_YAxis;}//�õ�ǰ���ƽ���ָ��Forward Backward
	int Get_LR() {return m_XAxis;}//�õ������˶���ָ��Left Right
	int Get_UD() {return m_ZAxis;}//�õ������˶���ָ��Up Down
	int Get_YAW() {return m_RzAxis;} //�õ���Z��ת��
};
