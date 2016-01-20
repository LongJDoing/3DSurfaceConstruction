#pragma once
#include "3DSurfaceReDlg.h"
#include ".\SDK\DICAMAPI.h"
#include "SetResolution.h"
#include "Setup.h"

extern BYTE m_FileType;  //index of file type
extern DI_RESOLUTION m_Resolution;
extern DI_RESOLUTION m_CaptureResolution;
extern int m_Height;
extern int m_Width;
extern int m_VOff;
extern int m_HOff;
////////////////// RESOLUTION SETTINGS DEFINE ///////////////////////////////////////////
//#define DTCM1400
////////////////// RESOLUTION SETTINGS DEFINE ///////////////////////////////////////////

#ifdef D1400C
#define HAVE_SPEED_SUPER  1
#define MODEL_NAME          "D1400C"
#define PREVIEW_RESOLUTION  R2048_1536

#define RESOLUTION_A_INDEX  R4384_3288
#define RESOLUTION_A_TEXT  "4384*3288"
#define RESOLUTION_A_ENABLE TRUE

#define RESOLUTION_B_INDEX  R2048_1536
#define RESOLUTION_B_TEXT  "2048*1536"
#define RESOLUTION_B_ENABLE TRUE

#define RESOLUTION_C_INDEX  R1280_960
#define RESOLUTION_C_TEXT  "1280*960"
#define RESOLUTION_C_ENABLE TRUE

#define RESOLUTION_D_INDEX  R1024_768
#define RESOLUTION_D_TEXT  "1024*768"
#define RESOLUTION_D_ENABLE TRUE

#define RESOLUTION_E_INDEX  R640_480
#define RESOLUTION_E_TEXT  "640*480"
#define RESOLUTION_E_ENABLE TRUE

#define RESOLUTION_F_INDEX  R_ROI
#define RESOLUTION_F_TEXT  "ROI"
#define RESOLUTION_F_ENABLE TRUE

#define ROI_HOFFSET  320
#define ROI_VOFFSET  240
#define ROI_WIDTH    1280
#define ROI_HEIGHT   1024
#endif

#ifdef D1000C
#define HAVE_SPEED_SUPER    1
#define MODEL_NAME          "D1000C"
#define PREVIEW_RESOLUTION  R3664_2748

#define RESOLUTION_A_INDEX  R3664_2748
#define RESOLUTION_A_TEXT  "3664*2748"
#define RESOLUTION_A_ENABLE TRUE

#define RESOLUTION_B_INDEX  R1600_1200
#define RESOLUTION_B_TEXT  "1600*1200"
#define RESOLUTION_B_ENABLE TRUE

#define RESOLUTION_C_INDEX  R1280_960
#define RESOLUTION_C_TEXT  "1280*960"
#define RESOLUTION_C_ENABLE TRUE

#define RESOLUTION_D_INDEX  R800_600
#define RESOLUTION_D_TEXT  "800*600"
#define RESOLUTION_D_ENABLE TRUE

#define RESOLUTION_E_INDEX  R640_480
#define RESOLUTION_E_TEXT  "640*480"
#define RESOLUTION_E_ENABLE TRUE

#define RESOLUTION_F_INDEX  R_ROI
#define RESOLUTION_F_TEXT  "ROI"
#define RESOLUTION_F_ENABLE TRUE

#define ROI_HOFFSET  320
#define ROI_VOFFSET  240
#define ROI_WIDTH    1280
#define ROI_HEIGHT   1024
#endif

#ifdef D900C
#define HAVE_SPEED_SUPER    1
#define MODEL_NAME "D900C"
#define PREVIEW_RESOLUTION  R1600_1200

#define RESOLUTION_A_INDEX  R3488_2616
#define RESOLUTION_A_TEXT  "3488*2616"
#define RESOLUTION_A_ENABLE TRUE

#define RESOLUTION_B_INDEX  R1600_1200
#define RESOLUTION_B_TEXT  "1600*1200"
#define RESOLUTION_B_ENABLE TRUE

#define RESOLUTION_C_INDEX  R1280_960
#define RESOLUTION_C_TEXT  "1280*960"
#define RESOLUTION_C_ENABLE TRUE

#define RESOLUTION_D_INDEX  R800_600
#define RESOLUTION_D_TEXT  "800*600"
#define RESOLUTION_D_ENABLE TRUE

#define RESOLUTION_E_INDEX  R640_480
#define RESOLUTION_E_TEXT  "640*480"
#define RESOLUTION_E_ENABLE TRUE

#define RESOLUTION_F_INDEX  R_ROI
#define RESOLUTION_F_TEXT  "ROI"
#define RESOLUTION_F_ENABLE TRUE

#define ROI_HOFFSET  320
#define ROI_VOFFSET  240
#define ROI_WIDTH    1280
#define ROI_HEIGHT   1024
#endif

#ifdef D800C
#define HAVE_SPEED_SUPER   1
#define MODEL_NAME         "D800C"
#define PREVIEW_RESOLUTION  R1600_1200

#define RESOLUTION_A_INDEX  R3264_2448
#define RESOLUTION_A_TEXT  "3264*2448"
#define RESOLUTION_A_ENABLE TRUE

#define RESOLUTION_B_INDEX  R1600_1200
#define RESOLUTION_B_TEXT  "1600*1200"
#define RESOLUTION_B_ENABLE TRUE

#define RESOLUTION_C_INDEX  R1280_960
#define RESOLUTION_C_TEXT  "1280*960"
#define RESOLUTION_C_ENABLE TRUE

#define RESOLUTION_D_INDEX  R800_600
#define RESOLUTION_D_TEXT  "800*600"
#define RESOLUTION_D_ENABLE TRUE

#define RESOLUTION_E_INDEX  R640_480
#define RESOLUTION_E_TEXT  "640*480"
#define RESOLUTION_E_ENABLE TRUE

#define RESOLUTION_F_INDEX  R_ROI
#define RESOLUTION_F_TEXT  "ROI"
#define RESOLUTION_F_ENABLE TRUE

#define ROI_HOFFSET  320
#define ROI_VOFFSET  240
#define ROI_WIDTH    1280
#define ROI_HEIGHT   1024
#endif

#ifdef D500C
#define HAVE_SPEED_SUPER  1
#define MODEL_NAME          "D500C"
#define PREVIEW_RESOLUTION  R1280_960

#define RESOLUTION_A_INDEX  R2592_1944
#define RESOLUTION_A_TEXT  "2592*1944"
#define RESOLUTION_A_ENABLE TRUE

#define RESOLUTION_B_INDEX  R1280_960
#define RESOLUTION_B_TEXT  "1280*960"
#define RESOLUTION_B_ENABLE TRUE

#define RESOLUTION_C_INDEX  R1024_768
#define RESOLUTION_C_TEXT  "1024*768"
#define RESOLUTION_C_ENABLE TRUE

#define RESOLUTION_D_INDEX  R640_480
#define RESOLUTION_D_TEXT  "640*480"
#define RESOLUTION_D_ENABLE TRUE

#define RESOLUTION_E_INDEX  R_ROI+1
#define RESOLUTION_E_TEXT  "Not use"
#define RESOLUTION_E_ENABLE FALSE

#define RESOLUTION_F_INDEX  R_ROI
#define RESOLUTION_F_TEXT  "ROI"
#define RESOLUTION_F_ENABLE TRUE

#define ROI_HOFFSET  640
#define ROI_VOFFSET  480
#define ROI_WIDTH    1280
#define ROI_HEIGHT   1024
#endif

#ifdef D300C
#define MODEL_NAME "D300C"
#define PREVIEW_RESOLUTION  R1024_768

#define RESOLUTION_A_INDEX  R2048_1536
#define RESOLUTION_A_TEXT  "2048*1536"	
#define RESOLUTION_A_ENABLE TRUE

#define RESOLUTION_B_INDEX  R1024_768
#define RESOLUTION_B_TEXT  "1024*768"	
#define RESOLUTION_B_ENABLE TRUE

#define RESOLUTION_C_INDEX  R640_480
#define RESOLUTION_C_TEXT  "640*480"	
#define RESOLUTION_C_ENABLE TRUE

#define RESOLUTION_D_INDEX  R_ROI+1
#define RESOLUTION_D_TEXT  "Not Use"	
#define RESOLUTION_D_ENABLE FALSE

#define RESOLUTION_E_INDEX  R_ROI+2
#define RESOLUTION_E_TEXT  "Not use"
#define RESOLUTION_E_ENABLE FALSE

#define RESOLUTION_F_INDEX  R_ROI
#define RESOLUTION_F_TEXT  "ROI"
#define RESOLUTION_F_ENABLE TRUE

#define ROI_HOFFSET  640
#define ROI_VOFFSET  480
#define ROI_WIDTH    1024
#define ROI_HEIGHT   768
#endif

#ifdef DC210C
#define MODEL_NAME "D210C"
#define PREVIEW_RESOLUTION  R1024_768

#define RESOLUTION_A_INDEX  R1600_1200
#define RESOLUTION_A_TEXT  "1600*1200"	
#define RESOLUTION_A_ENABLE TRUE

#define RESOLUTION_B_INDEX  R800_600
#define RESOLUTION_B_TEXT  "800*600"	
#define RESOLUTION_B_ENABLE TRUE

#define RESOLUTION_C_INDEX  R640_480
#define RESOLUTION_C_TEXT  "640*480"	
#define RESOLUTION_C_ENABLE TRUE

#define RESOLUTION_D_INDEX  R_ROI+1
#define RESOLUTION_D_TEXT  "Not Use"	
#define RESOLUTION_D_ENABLE FALSE

#define RESOLUTION_E_INDEX  R_ROI+2
#define RESOLUTION_E_TEXT  "Not use"
#define RESOLUTION_E_ENABLE FALSE

#define RESOLUTION_F_INDEX  R_ROI
#define RESOLUTION_F_TEXT  "ROI"
#define RESOLUTION_F_ENABLE TRUE

#define ROI_HOFFSET  320
#define ROI_VOFFSET  240
#define ROI_WIDTH    1024
#define ROI_HEIGHT   768
#endif

#ifdef D130C
#define MODEL_NAME "SunTime 130E"

#define PREVIEW_RESOLUTION  R1280_1024

#define RESOLUTION_A_INDEX  R_ROI+1
#define RESOLUTION_A_TEXT  "Not use"
#define RESOLUTION_A_ENABLE FALSE

#define RESOLUTION_B_INDEX  R1280_1024
#define RESOLUTION_B_TEXT  "1280*1024"
#define RESOLUTION_B_ENABLE TRUE

#define RESOLUTION_C_INDEX  R640_480
#define RESOLUTION_C_TEXT  "640*480"
#define RESOLUTION_C_ENABLE TRUE

#define RESOLUTION_D_INDEX  R320_240
#define RESOLUTION_D_TEXT  "320*240"
#define RESOLUTION_D_ENABLE TRUE

#define RESOLUTION_E_INDEX  R_ROI+2
#define RESOLUTION_E_TEXT  "Not use"
#define RESOLUTION_E_ENABLE FALSE

#define RESOLUTION_F_INDEX  R_ROI
#define RESOLUTION_F_TEXT  "ROI"
#define RESOLUTION_F_ENABLE TRUE

#define ROI_HOFFSET  320
#define ROI_VOFFSET  240
#define ROI_WIDTH    640
#define ROI_HEIGHT   480
#endif
#ifdef D036C
#define MODEL_NAME "D036C"

#define PREVIEW_RESOLUTION  R752_480

#define RESOLUTION_A_INDEX  R_ROI+1
#define RESOLUTION_A_TEXT  "Not use"
#define RESOLUTION_A_ENABLE FALSE

#define RESOLUTION_B_INDEX  R752_480
#define RESOLUTION_B_TEXT  "752*480"
#define RESOLUTION_B_ENABLE TRUE

#define RESOLUTION_C_INDEX  R640_480
#define RESOLUTION_C_TEXT  "640*480"
#define RESOLUTION_C_ENABLE TRUE

#define RESOLUTION_D_INDEX  R320_240
#define RESOLUTION_D_TEXT  "320*240"
#define RESOLUTION_D_ENABLE TRUE

#define RESOLUTION_E_INDEX  R_ROI+2
#define RESOLUTION_E_TEXT  "Not use"
#define RESOLUTION_E_ENABLE FALSE

#define RESOLUTION_F_INDEX  R_ROI
#define RESOLUTION_F_TEXT  "ROI"
#define RESOLUTION_F_ENABLE FALSE

#define ROI_HOFFSET  320
#define ROI_VOFFSET  240
#define ROI_WIDTH    640
#define ROI_HEIGHT   480

#endif
// CDialog3 对话框
class C3DSurfaceReDlg;
class CSetResolution;
class CSetup;

class CDialog3 : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog3)

public:
	CDialog3(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialog3();

// 对话框数据
	enum { IDD = IDD_DIALOG3 };
protected:
	virtual BOOL OnInitDialog();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	afx_msg void OnBnClickedPlay();
	DECLARE_MESSAGE_MAP()
private:
	C3DSurfaceReDlg * m_pDlg;
	CComboBox m_MultiCamList;
	BYTE m_RunMode; // the flag of app

	UINT m_iErrorFrames;
	UINT m_iVideoCnt;

	int m_Image_Count;
	
	CSetup *m_SetupDlg; //Setup dialog. AE/AWB/Saturation/Contrast/Gamma
	CSetResolution *m_SetResolutionDlg; //Resolution dialog


public:

	afx_msg void OnBnClickedSavefile();
	afx_msg void OnBnClickedSaveimg();
	afx_msg void OnBnClickedSetup();
	afx_msg void OnBnClickedResolution();
	afx_msg void OnBnClickedExit();
};
