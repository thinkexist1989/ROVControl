
// ROVControl.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CRovCtrlApp:
// �йش����ʵ�֣������ ROVControl.cpp
//

class CRovCtrlApp : public CWinApp
{
public:
	CRovCtrlApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CRovCtrlApp theApp;