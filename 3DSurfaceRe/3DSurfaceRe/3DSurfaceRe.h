
// 3DSurfaceRe.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// 3DSurfaceReApp:
// �йش����ʵ�֣������ 3DSurfaceRe.cpp
//

class C3DSurfaceReApp : public CWinApp
{
public:
	C3DSurfaceReApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern C3DSurfaceReApp theApp;