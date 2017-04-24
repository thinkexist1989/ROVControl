#pragma once
#include "afxcmn.h"


// CLoginDlg �Ի���

class CLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLoginDlg();

// �Ի�������
	enum { IDD = IDD_PREVIEW_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	BOOL DoLogin();
	BOOL DoCameraPreview();
	BOOL DoStopPlaying();
	BOOL DoClose();
	void DoAddInfo(int depth, float pitch, float roll, float yaw);
	void DoAddInfo2(int X, int Y, int Z, int Rx);
	
	BOOL m_bIsLogin;

	BOOL m_bIsRunning;
	BOOL m_bIsRunning2;

	BOOL m_bIsRecording;

	CIPAddressCtrl m_cameraIp;
	CIPAddressCtrl m_cameraIp2;

	int m_cameraPort;
	int m_cameraPort2;

	CString m_userName;
	CString m_userName2;

	CString m_userPSWD;
	CString m_userPSWD2;

	DWORD m_ipValue;
	DWORD m_ipValue2;

	NET_DVR_DEVICEINFO_V30 m_deviceInfo;
	NET_DVR_PREVIEWINFO    m_previewInfo;
	LONG m_userID;
	LONG m_realplayHandle;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCancel();
	
	
	
	// ��������ͷ������
	HANDLE m_hPreview;
	afx_msg void OnBnClickedOk2();
};
