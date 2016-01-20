#pragma once

#include "3DSurfaceReDlg.h"
#include "InputDialog.h"
#include "MyPhase.h"
#include "MyGeometry.h"
#include "MyLeastSquare.h"
#include "ShowImageDialog.h"
// CDialog1 对话框
extern RGBQUAD colorTable[256];
extern int img_num;
class C3DSurfaceReDlg;
class CInputDialog;
class CShowImageDialog;
class CMyPhase;
class CMyGeometry;
class CMyLeastSquare;
class CDialog1 : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog1)

public:
	CDialog1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialog1();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedCalculateapm();
	afx_msg void OnCbnSelchangeChplanelist();
	afx_msg void OnCbnSelchangeChdrlist();
	afx_msg void OnBnClickedCalculatecorner();
	afx_msg void OnBnClickedImportstripes();
	afx_msg void OnBnClickedCalculaterpm();
	afx_msg void OnBnClickedExtractsampt();
	afx_msg void OnBnClickedCalculatecorrespt();
	afx_msg void OnBnClickedComputeprojectorcenter();
	afx_msg void OnBnClickedShowphasemap();
	afx_msg void OnBnClickedShowabsolutemap();
	DECLARE_MESSAGE_MAP()
protected:
	virtual BOOL OnInitDialog();

public:
	CComboBox m_ChPlaneList;
	CComboBox m_ChDirectionList;
	afx_msg void OnInputpr();
private:
	C3DSurfaceReDlg * m_pDlg;
	CInputDialog * m_inputdlg;
	CMyPhase * m_myphase;
	CMyGeometry * m_mygeometry;
	CMyLeastSquare * m_myleastsquare;
	CShowImageDialog * m_showimagedlg;

public:
	CImage * InputOneImg(); 
	std::vector<CImage *> InputMulImg();
	CImage * DrawImage(double *, bool bID);
	double * GetphaseMap();
	double * GetAbsolutePhaseMap(double *, bool);

};
