#pragma once

#include "3DSurfaceReDlg.h"
#include "InputDialog.h"
#include "MyPhase.h"
#include "MyGeometry.h"
#include "ImageOperate.h"
#include "ConnectComponentLabel.h"

// CDialog2 对话框
class C3DSurfaceReDlg;
class CInputDialog;
class CMyPhase;
class CMyGeometry;
class CConnectComponentLabel;
class CImageOperate;

class CDialog2 : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog2)

public:
	CDialog2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialog2();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedCalculatecorner();
	afx_msg void OnBnClickedImportstripes();
	afx_msg void OnBnClickedCalculaterpm();
	afx_msg void OnBnClickedCalculateapm();
	afx_msg void OnCbnSelchangeChobjectlist();
	afx_msg void OnCbnSelchangeChdrlist();
	afx_msg void OnBnClickedBlackscreen();

	DECLARE_MESSAGE_MAP()
protected:
	virtual BOOL OnInitDialog();
public:
	CComboBox m_ChObjectList;
	CComboBox m_ChDirectionList;
private:
	C3DSurfaceReDlg * m_pDlg;
	CInputDialog * m_inputdlg;
	CMyPhase * m_myphase;
	CMyGeometry * m_mygeometry;
	CImageOperate * m_myimageopreate;
	CConnectComponentLabel *m_pConnectComponentLabel;

public:
	CImage * InputOneImg(); 
	std::vector<CImage *> InputMulImg();
	CImage * DrawImage(double *, bool bID);
	double * GetphaseMap();
	double * GetAbsolutePhaseMap(double *, bool);
	void BlackScreen(CImage * , CImage *);

	afx_msg void OnBnClickedFindprojectioncorpt();
	afx_msg void OnBnClicked3dreconstruction();
	afx_msg void OnBnClickedShowphasemap();
	afx_msg void OnBnClickedShowabsolutemap();
	afx_msg void OnBnClickedShowgraymap();
};
