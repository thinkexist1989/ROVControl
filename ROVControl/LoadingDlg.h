#pragma once


// CLoadingDlg �Ի���

class CLoadingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoadingDlg)

public:
	CLoadingDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLoadingDlg();

// �Ի�������
	enum { IDD = IDD_LOADING_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
