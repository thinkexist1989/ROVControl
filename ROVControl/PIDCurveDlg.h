#pragma once
#include "atltypes.h"
#include "GetPidDlg.h"
#include "SetPidDlg.h"
#include "afxcmn.h"
#include "iPlotX/iplotx.h"
#include "iPlotX/iplotchannelx.h"


// CPIDCurveDlg 对话框

class CPIDCurveDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPIDCurveDlg)

public:
	CPIDCurveDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPIDCurveDlg();

// 对话框数据
	enum { IDD = IDD_PIDCURVE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CRect m_rectLarge;
	CRect m_rectSmall;
	virtual BOOL OnInitDialog();

	CGetPidDlg m_getPidDlg;
	CSetPidDlg m_setPidDlg;
	CTabCtrl m_tab;
	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);

	CiPlotX m_plot;
	int		count;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnBnClickedBtnClear();
	BOOL m_b1;
	BOOL m_b2;
	BOOL m_b3;
	BOOL m_b4;
	BOOL m_b5;
	BOOL m_b6;
	BOOL m_b7;
	BOOL m_b8;
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck4();
	afx_msg void OnBnClickedCheck5();
	afx_msg void OnBnClickedCheck6();
	afx_msg void OnBnClickedCheck7();
	afx_msg void OnBnClickedCheck8();

	bool m_bStart;

};
