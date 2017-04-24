#pragma once


// CSetPidDlg 对话框

class CSetPidDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetPidDlg)

public:
	CSetPidDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetPidDlg();

// 对话框数据
	enum { IDD = IDD_SETPID };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedOk5();
	float m_p1;
	float m_p2;
	float m_p3;
	float m_p4;
	float m_p5;
	float m_p6;
	float m_p7;
	float m_p8;

	float m_i1;
	float m_i2;
	float m_i3;
	float m_i4;
	float m_i5;
	float m_i6;
	float m_i7;
	float m_i8;

	float m_d1;
	float m_d2;
	float m_d3;
	float m_d4;
	float m_d5;
	float m_d6;
	float m_d7;
	float m_d8;
	afx_msg void OnBnClickedOk3();
	afx_msg void OnBnClickedOk4();
};
