#pragma once


// CGetPidDlg �Ի���

class CGetPidDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGetPidDlg)

public:
	CGetPidDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGetPidDlg();

// �Ի�������
	enum { IDD = IDD_GETPID };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
