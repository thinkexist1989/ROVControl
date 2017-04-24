#pragma once


// CGetPidDlg 对话框

class CGetPidDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGetPidDlg)

public:
	CGetPidDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGetPidDlg();

// 对话框数据
	enum { IDD = IDD_GETPID };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
