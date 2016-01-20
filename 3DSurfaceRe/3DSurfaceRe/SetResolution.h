#pragma once
#include "Dialog3.h"

// CSetResolution 对话框

class CSetResolution : public CDialogEx
{
	DECLARE_DYNAMIC(CSetResolution)

public:
	CSetResolution(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetResolution();

// 对话框数据
	enum { IDD = IDD_RESOLUTION_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnResolutionA();
	afx_msg void OnResolutionB();
	afx_msg void OnResolutionC();
	afx_msg void OnResolutionD();
	afx_msg void OnResolutionE();
	afx_msg void OnResolutionF();
	afx_msg void OnCaptureresolutionA();
	afx_msg void OnCaptureresolutionB();
	afx_msg void OnCaptureresolutionC();
	afx_msg void OnCaptureresolutionD();
	afx_msg void OnCaptureresolutionE();
	afx_msg void OnCaptureresolutionF();
	afx_msg void OnChangeHoff();
	afx_msg void OnChangeVoff();
	afx_msg void OnChangeWidth();
	afx_msg void OnChangeHeight();
	DECLARE_MESSAGE_MAP()
public:
	BYTE m_RSLTIndex; //index of Resolution
	BYTE m_CaptureIndex;
	int m_HOff1;
	int m_VOff1;
	int m_Height1;
	int m_Width1;
	CWnd *m_pParentWnd;

};
