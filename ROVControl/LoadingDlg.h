#pragma once


// CLoadingDlg 对话框

class CLoadingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoadingDlg)

public:
	CLoadingDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLoadingDlg();

// 对话框数据
	enum { IDD = IDD_LOADING_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CImage m_img;
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
private:
	BOOL a;
	BOOL b;
};
