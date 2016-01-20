#pragma once
#include "MyDIdefine.h"
// CInputDialog

class CInputDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CInputDialog)

public:
	CInputDialog(CWnd* pParent = NULL);
	virtual ~CInputDialog();
	// 对话框数据
	enum { IDD = IDD_INPUT_DIALOG };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnOkButton();
	afx_msg void OnChangeCamerapa1Edit();
	afx_msg void OnChangeCamerapa2Edit();
	afx_msg void OnChangeCmaerapa3Edit();
	afx_msg void OnChangeCmaerapa4Edit();
	afx_msg void OnChangeDistortion1Edit();
	afx_msg void OnChangeDistortion2Edit();
	afx_msg void OnChangeDistortion3Edit();
	afx_msg void OnChangeDistortion4Edit();
	afx_msg void OnChangePixelsz1Edit();
	afx_msg void OnChangePixelsz2Edit();
	afx_msg void OnChangeRotation1Edit();
	afx_msg void OnChangeRotation2Edit();
	afx_msg void OnChangeRotation3Edit();
	afx_msg void OnChangeRotation4Edit();
	afx_msg void OnChangeRotation5Edit();
	afx_msg void OnChangeRotation6Edit();
	afx_msg void OnChangeRotation7Edit();
	afx_msg void OnChangeRotation8Edit();
	afx_msg void OnChangeRotation9Edit();
	afx_msg void OnChangeTranslation1Edit2();
	afx_msg void OnChangeTranslation2Edit3();
	afx_msg void OnChangeTranslation3Edit();
	afx_msg void OnChangeDistanceEdit();

public:
	double m_cameravector1;
	double m_cameravector2;
	double m_cameravector3;
	double m_cameravector4;
	double m_cameradistortion1;
	double m_cameradistortion2;
	double m_cameradistortion3;
	double m_cameradistortion4;
	double m_pixelsizex;
	double m_pixelsizey;
	double m_rotation1;
	double m_rotation2;
	double m_rotation3;
	double m_rotation4;
	double m_rotation5;
	double m_rotation6;
	double m_rotation7;
	double m_rotation8;
	double m_rotation9;
	double m_translation1;
	double m_translation2;
	double m_translation3;
	double m_distance;
};


