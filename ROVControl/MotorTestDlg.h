#pragma once


// CMotorTestDlg �Ի���

class CMotorTestDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMotorTestDlg)

public:
	CMotorTestDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMotorTestDlg();

// �Ի�������
	enum { IDD = IDD_MOTORTEST_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CSliderCtrl m_motor1Value;
	CSliderCtrl m_motor2Value;
	CSliderCtrl m_motor3Value;
	CSliderCtrl m_motor4Value;
	CSliderCtrl m_motor5Value;
	CSliderCtrl m_motor6Value;
	CSliderCtrl m_motor7Value;
	CSliderCtrl m_motor8Value;

	void SendMotorSpeed();

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnReset();
	afx_msg void OnBnClickedBtnSend();
};
