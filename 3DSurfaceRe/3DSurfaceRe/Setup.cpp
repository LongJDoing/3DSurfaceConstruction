// Setup.cpp : 实现文件
//

#include "stdafx.h"
#include "3DSurfaceRe.h"
#include "Setup.h"
#include "afxdialogex.h"


// CSetup 对话框

IMPLEMENT_DYNAMIC(CSetup, CDialogEx)

CSetup::CSetup(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetup::IDD, pParent)
{
	 m_Gamma = 0; //gamma slider
	 m_ExpTime = 0; //ex time slider
	 m_AeTarget = 0; //ae target slider
	 m_BGain = 0; //b gain slider
	 m_GGain = 0; //g gain slider
	 m_RGain = 0; //r gain slider
	 m_Contrast = 0; //contrast slider
	 m_AnalogGain = 0; //gain slider
	 m_Saturation = 0; //saturation slider
	 
	 m_FrameSpeed = -1;

	 m_bColorCorrect = FALSE;
	 m_Aeen = FALSE;

	 m_bMono = FALSE;
	 m_bHFlip = FALSE;
	 m_bVFlip = FALSE;
	 m_CheckBMP = FALSE;
	 m_CheckJPG = FALSE;
	 m_CheckRAW = FALSE;
	 m_CheckPNG = FALSE;

	 m_FTypeIndex = 0;

}

CSetup::~CSetup()
{
}

BOOL CSetup::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	USHORT uiMaxExpTime = 1000;
	CameraGetMaxExposureTime(&uiMaxExpTime);
	// TODO: Add extra initialization here
	m_GammaCtrl.SetRange(20, 150); //.20~1.5
	m_ContrastCtrl.SetRange(0, 255);
	m_SaturationCtrl.SetRange(0, 255);
	m_AeTargetCtrl.SetRange(40, 200);

	m_ExpTimeCtrl.SetRange(1, uiMaxExpTime); ////设置曝光时间范围

	m_RGainCtrl.SetRange(20, 200);
	m_GGainCtrl.SetRange(20, 200);
	m_BGainCtrl.SetRange(20, 200);
	m_AnalogGainCtrl.SetRange(1, 48);

	UpdateData(TRUE);
	BYTE uiTemp;
	CameraGetCurrentParameterTeam(&uiTemp);
	switch (uiTemp)
	{
	case PARAMETER_TEAM_A:
		CheckDlgButton(IDC_PTA, 1);
		break;
	case PARAMETER_TEAM_B:
		CheckDlgButton(IDC_PTB, 1);
		break;
	case PARAMETER_TEAM_C:
		CheckDlgButton(IDC_PTC, 1);
		break;
	case PARAMETER_TEAM_D:
		CheckDlgButton(IDC_PTD, 1);
		break;
	default:
		uiTemp = PARAMETER_TEAM_A;
		CheckDlgButton(IDC_PTA, 1);
		break;
	}

	m_CheckJPG = m_FTypeIndex&FILE_JPG;
	m_CheckBMP = (m_FTypeIndex&FILE_BMP)>>1;
	m_CheckRAW = (m_FTypeIndex&FILE_RAW)>>2;
	m_CheckPNG = (m_FTypeIndex&FILE_PNG)>>3;


	UpdateData(FALSE);	

	m_ParameterTeam = (DI_PARAMETER_TEAM)uiTemp;
	
	UpdateSetupWindow();
	return TRUE;
}

void CSetup::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_RGAIN, m_RGainCtrl);
	DDX_Control(pDX, IDC_GGAIN, m_GGainCtrl);
	DDX_Control(pDX, IDC_BGAIN, m_BGainCtrl);
	DDX_Control(pDX, IDC_GAMMA, m_GammaCtrl);
	DDX_Control(pDX, IDC_CONTRAST, m_ContrastCtrl);
	DDX_Control(pDX, IDC_SATURATION, m_SaturationCtrl);
	DDX_Control(pDX, IDC_AETARGET, m_AeTargetCtrl);
	DDX_Control(pDX, IDC_GAIN, m_AnalogGainCtrl);
	DDX_Control(pDX, IDC_EXPTIME, m_ExpTimeCtrl);

	DDX_Slider(pDX, IDC_GAMMA, m_Gamma);
	DDX_Slider(pDX, IDC_EXPTIME, m_ExpTime);
	DDX_Slider(pDX, IDC_GAIN, m_AnalogGain);
	DDX_Slider(pDX, IDC_AETARGET, m_AeTarget);
	DDX_Slider(pDX, IDC_BGAIN, m_BGain);
	DDX_Slider(pDX, IDC_GGAIN, m_GGain);
	DDX_Slider(pDX, IDC_RGAIN, m_RGain);
	DDX_Slider(pDX, IDC_CONTRAST, m_Contrast);
	DDX_Slider(pDX, IDC_SATURATION, m_Saturation);

	DDX_Radio(pDX, IDC_LOWSPEED, m_FrameSpeed);
	
	DDX_Check(pDX, IDC_COLORCORRECT, m_bColorCorrect);
	DDX_Check(pDX, IDC_AEEN, m_Aeen);
	DDX_Check(pDX, IDC_HFLIP, m_bHFlip);
	DDX_Check(pDX, IDC_VFLIP, m_bVFlip);
	DDX_Check(pDX, IDC_MONO, m_bMono);
	DDX_Check(pDX, IDC_CHECKBMP, m_CheckBMP);
	DDX_Check(pDX, IDC_CHECKJPG, m_CheckJPG);
	DDX_Check(pDX, IDC_CHECKRAW, m_CheckRAW);
	DDX_Check(pDX, IDC_CHECKPNG, m_CheckPNG);
}


BEGIN_MESSAGE_MAP(CSetup, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_AWBONE, &CSetup::OnAwbone)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_RGAIN, &CSetup::OnCustomdrawRgain)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_GGAIN, &CSetup::OnCustomdrawGgain)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_BGAIN, &CSetup::OnCustomdrawBgain)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_GAMMA, &CSetup::OnCustomdrawGamma)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_CONTRAST, &CSetup::OnCustomdrawContrast)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SATURATION, &CSetup::OnCustomdrawSaturation)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_AETARGET, &CSetup::OnCustomdrawAetarget)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_GAIN, &CSetup::OnCustomdrawGain)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_EXPTIME, &CSetup::OnCustomdrawExptime)
	ON_BN_CLICKED(IDC_COLORCORRECT, &CSetup::OnColorcorrect)
	ON_BN_CLICKED(IDC_AEEN, &CSetup::OnAeen)
	ON_BN_CLICKED(IDC_HFLIP, &CSetup::OnHflip)
	ON_BN_CLICKED(IDC_VFLIP, &CSetup::OnVflip)
	ON_BN_CLICKED(IDC_MONO, &CSetup::OnMono)
	ON_BN_CLICKED(IDC_CHECKJPG, &CSetup::OnCheckjpg)
	ON_BN_CLICKED(IDC_CHECKBMP, &CSetup::OnCheckbmp)
	ON_BN_CLICKED(IDC_CHECKPNG, &CSetup::OnCheckpng)
	ON_BN_CLICKED(IDC_CHECKRAW, &CSetup::OnCheckraw)
	ON_BN_CLICKED(IDC_B2RGB_A, &CSetup::OnB2rgbA)
	ON_BN_CLICKED(IDC_B2RGB_B, &CSetup::OnB2rgbB)
	ON_BN_CLICKED(IDC_B2RGB_C, &CSetup::OnB2rgbC)
	ON_BN_CLICKED(IDC_LOWSPEED, &CSetup::OnLowspeed)
	ON_BN_CLICKED(IDC_HIGHSPEED, &CSetup::OnHighspeed)
	ON_BN_CLICKED(IDC_SUPERSPEED, &CSetup::OnSuperspeed)
	ON_BN_CLICKED(IDC_LF_50HZ, &CSetup::OnLf50hz)
	ON_BN_CLICKED(IDC_LF_60HZ, &CSetup::OnLf60hz)
	ON_BN_CLICKED(IDC_PTA, &CSetup::OnPta)
	ON_BN_CLICKED(IDC_PTB, &CSetup::OnPtb)
	ON_BN_CLICKED(IDC_PTC, &CSetup::OnPtc)
	ON_BN_CLICKED(IDC_PTD, &CSetup::OnPtd)
	ON_BN_CLICKED(IDC_LOAD_PARAMETER, &CSetup::OnLoadParameter)
	ON_BN_CLICKED(IDC_SAVE_PARAMETER, &CSetup::OnSaveParameter)
END_MESSAGE_MAP()

/*==============================================================
Name: UpdateSetupWindow()
Desc:  update the setupwindow ,get the value from the camera sate

Param:	
Return: 
Note:   
  --------------------------------------------------------------*/
void CSetup::UpdateSetupWindow()
{
	INT RGain =64;
	INT GGain =64;
	INT BGain =64;
	BYTE uiTemp;
	BOOL bTemp;
	CString sTemp;
	BYTE Saturation = 128;
	BYTE Contrast = 0;
	USHORT usAnalogGain = 0;
	BYTE uiNoisePiexlOffset = 50;
	if (1) 
	{
		INT iTemp;
		CameraGetExposureTime(&iTemp);
		m_ExpTime = iTemp;
		CameraGetAeState(&bTemp);
		m_Aeen = bTemp;
		CameraGetAeTarget(&uiTemp);
		m_AeTarget =  uiTemp;
		CameraGetColorEnhancement(&bTemp);
		m_bColorCorrect = bTemp;

		CameraGetGamma(&uiTemp);
		m_Gamma = uiTemp;
		CameraGetAWBState(&bTemp);

		CameraGetMonochrome(&bTemp);
		m_bMono = bTemp;
		CameraGetMirror(MIRROR_DIRECTION_HORIZONTAL, &bTemp);
		m_bHFlip = bTemp;
		CameraGetMirror(MIRROR_DIRECTION_VERTICAL, &bTemp);
		m_bVFlip = bTemp;

		CameraGetAnalogGain( &usAnalogGain );

		CameraGetGain(&RGain, &GGain, &BGain),
		CameraGetSaturation(&Saturation);
		CameraGetContrast(&Contrast);

		UpdateData(FALSE);

		CameraGetFrameSpeed(&uiTemp);
		switch(uiTemp)
		{
			case FRAME_SPEED_NORMAL:
				CheckDlgButton(IDC_LOWSPEED, 1);
				CheckDlgButton(IDC_HIGHSPEED, 0);
				CheckDlgButton(IDC_SUPERSPEED, 0);
				break;
			case FRAME_SPEED_HIGH:
				CheckDlgButton(IDC_LOWSPEED, 0);
				CheckDlgButton(IDC_HIGHSPEED, 1);
				CheckDlgButton(IDC_SUPERSPEED, 0);
				break;
#ifdef HAVE_SPEED_SUPER
 			case FRAME_SPEED_SUPER:
 				CheckDlgButton(IDC_LOWSPEED, 0);
 				CheckDlgButton(IDC_HIGHSPEED, 0);
				CheckDlgButton(IDC_SUPERSPEED, 1);
				break;
#endif
			default:
				CheckDlgButton(IDC_LOWSPEED, 1);
				CheckDlgButton(IDC_HIGHSPEED, 0);
				CheckDlgButton(IDC_SUPERSPEED, 0);
				break;
		}

		CameraGetLightFrquency(&uiTemp);
		if (uiTemp)
		{
			CheckDlgButton(IDC_LF_60HZ, 1);
			CheckDlgButton(IDC_LF_50HZ, 0);
		}
		else
		{
			CheckDlgButton(IDC_LF_60HZ, 0);
			CheckDlgButton(IDC_LF_50HZ, 1);
		}
		CameraGetB2RGBMode(&uiTemp);
		switch (uiTemp)
		{
			case B2RGB_MODE_LAROCHE:
				CheckDlgButton(IDC_B2RGB_A, 1);	
				break;
			case B2RGB_MODE_HAMILTON:
				CheckDlgButton(IDC_B2RGB_B, 1);	
				break;
			case B2RGB_MODE_LINE:
				CheckDlgButton(IDC_B2RGB_C, 1);	
				break;
			default:
				break;
		}
	}
	m_AeTargetCtrl.SetPos(m_AeTarget);
	m_SaturationCtrl.SetPos(Saturation);
	m_ContrastCtrl.SetPos(Contrast);
	
	m_RGainCtrl.SetPos((int)(RGain));
	m_GGainCtrl.SetPos((int)(GGain));
	m_BGainCtrl.SetPos((int)(BGain));
	m_AnalogGainCtrl.SetPos(usAnalogGain);
	
	GetDlgItem(IDC_GAIN)->EnableWindow(!m_Aeen);
	GetDlgItem(IDC_STATIC_GAIN)->EnableWindow(!m_Aeen);

	GetDlgItem(IDC_EXPTIME)->EnableWindow(!m_Aeen);
	GetDlgItem(IDC_STATIC_TIME)->EnableWindow(!m_Aeen);

	GetDlgItem(IDC_AETARGET)->EnableWindow(m_Aeen);
	GetDlgItem(IDC_STATIC_TARGET)->EnableWindow(m_Aeen);

	GetDlgItem(IDC_SATURATION)->EnableWindow(m_bColorCorrect);

#ifndef HAVE_SPEED_SUPER
	GetDlgItem(IDC_SUPERSPEED)->EnableWindow(FALSE);
#endif
	UpdateData(TRUE);

	sTemp.Format("%d", m_AeTarget);
	GetDlgItem(IDC_AETARGETTEXT)->SetWindowText(sTemp);	


	sTemp.Format("%5.2f",GGain/64.0f);
	GetDlgItem(IDC_GTEXT)->SetWindowText(sTemp);

	sTemp.Format("%5.2f",RGain/64.0f);
	GetDlgItem(IDC_RTEXT)->SetWindowText(sTemp);

	sTemp.Format("%5.2f",BGain/64.0f);
	GetDlgItem(IDC_BTEXT)->SetWindowText(sTemp);
	
	sTemp.Format("%d",Saturation);
	GetDlgItem(IDC_SATURATIONTEXT)->SetWindowText(sTemp);
	
	sTemp.Format("%d",Contrast);
	GetDlgItem(IDC_CONTRASTTEXT)->SetWindowText(sTemp);
	
	UpdateExposurteTimeText();

	sTemp.Format("%d",m_AnalogGain);
	GetDlgItem(IDC_GAINTEXT)->SetWindowText(sTemp);

	sTemp.Format("%4.2f",m_Gamma/100.0f);
	GetDlgItem(IDC_GAMMATEXT)->SetWindowText(sTemp);

	UpdateData(FALSE);	
}

/*==============================================================
Name:	OnOK
Desc:  set OK

Param:	
Return: 
Note:   
  --------------------------------------------------------------*/
void CSetup::OnOK()
{
	m_FileType = this->m_FTypeIndex;
	CDialogEx::OnOK();
}


// CSetup 消息处理程序

/*==============================================================
Name:	OnAwbbone
Desc:  set one awb

Param:	
Return: 
Note:   
  --------------------------------------------------------------*/
void CSetup::OnAwbone()
{
	// TODO: 在此添加控件通知处理程序代码
	CameraSetAWBState(1); // set automatic white balance mode
	int RGain,GGain,BGain;

	CameraGetGain(&RGain, &GGain, &BGain); //得到每个颜色通道增益
	
	CString sTemp;
	sTemp.Format("%5.2f", GGain/64.0f);
	GetDlgItem(IDC_GTEXT)->SetWindowTextA(sTemp);

    sTemp.Format("%5.2f", RGain/64.0f);
	GetDlgItem(IDC_RTEXT)->SetWindowTextA(sTemp);

	sTemp.Format("%5.2f", BGain/64.0f);
	GetDlgItem(IDC_BTEXT)->SetWindowTextA(sTemp);

	m_RGainCtrl.SetPos((int)(RGain));
	m_GGainCtrl.SetPos((int)(GGain));
	m_BGainCtrl.SetPos((int)(BGain));
}

/*==============================================================
Name:	OnClose
Desc:  close the window

Param:	
Return: 
Note:   ON_WM_CLOSE()
  --------------------------------------------------------------*/
void CSetup::OnClose()
{
	m_FileType = this->m_FTypeIndex;
	CDialogEx::OnClose();
}

/*==============================================================
Name:	OnCustomdrawRgain
Desc:  set R gain

Param:	
Return: 
Note:   NM_CUSTOMDRAW
  --------------------------------------------------------------*/
void CSetup::OnCustomdrawRgain(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	UpdateColorGain();
	*pResult = 0;
}


void CSetup::OnCustomdrawGgain(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	UpdateColorGain();
	*pResult = 0;
}


void CSetup::OnCustomdrawBgain(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	UpdateColorGain();
	*pResult = 0;
}

/*==============================================================
Name:	UpdateColorCain
Desc:  update color gain

Param:	
Return: 
Note:    
  --------------------------------------------------------------*/
void CSetup::UpdateColorGain()
{
	USHORT RGain = m_RGainCtrl.GetPos();
	USHORT GGain = m_GGainCtrl.GetPos();
	USHORT BGain = m_BGainCtrl.GetPos();

	CString sTemp;
	sTemp.Format("%5.2f", RGain/64.0f);
	GetDlgItem(IDC_RTEXT)->SetWindowTextA(sTemp);

	sTemp.Format("%5.2f", GGain/64.0f);
	GetDlgItem(IDC_GTEXT)->SetWindowTextA(sTemp);

	sTemp.Format("%5.2f", BGain/64.0f);
	GetDlgItem(IDC_BTEXT)->SetWindowTextA(sTemp);

	CameraSetGain(RGain, GGain, BGain);
}

/*==============================================================
Name:	OnCustomdrawGamma
Desc:  set the gamma

Param:	
Return: 
Note:    
  --------------------------------------------------------------*/
void CSetup::OnCustomdrawGamma(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int GammaValue = m_Gamma;
	{
		CameraSetGamma(GammaValue);
		float x = GammaValue / 100.0f;
		CString sTemp;
		sTemp.Format("%4.2f", x);
		GetDlgItem(IDC_GAMMATEXT)->SetWindowTextA(sTemp);
	}
	*pResult = 0;
}

/*==============================================================
Name:	OnCustomdrawContrast
Desc:  set the contrast

Param:	
Return: 
Note:    
  --------------------------------------------------------------*/
void CSetup::OnCustomdrawContrast(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int ContrastValue = m_ContrastCtrl.GetPos();

	CameraSetContrast(ContrastValue);
	CString sTemp;
	sTemp.Format("%d", ContrastValue);
	GetDlgItem(IDC_CONTRASTTEXT)->SetWindowTextA(sTemp);
	
	*pResult = 0;
}

/*==============================================================
Name:	OnCustomdrawSaturation
Desc:  set the saturation
Param:	
Return: 
Note:    
  --------------------------------------------------------------*/
void CSetup::OnCustomdrawSaturation(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int SaturationValue = m_SaturationCtrl.GetPos();
	{
		CameraSetSaturation(SaturationValue);
		CString sTemp;
		sTemp.Format("%d", SaturationValue);
		GetDlgItem(IDC_SATURATIONTEXT)->SetWindowTextA(sTemp);
	}
	*pResult = 0;
}

/*==============================================================
Name:	OnCustomdrawAetarget
Desc:   设置自动曝光的亮度目标

Param:	
Return: 
Note:    
  --------------------------------------------------------------*/
void CSetup::OnCustomdrawAetarget(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int pos;
	pos = m_AeTargetCtrl.GetPos();

	CameraSetAeTarget(pos);

	CString sTemp;
	sTemp.Format("%d", pos);
	GetDlgItem(IDC_AETARGETTEXT)->SetWindowTextA(sTemp);

	UpdateData(TRUE);

	*pResult = 0;
}

/*==============================================================
Name:	OnCustomdrawGain
Desc:   set the gain

Param:	
Return: 
Note:    
  --------------------------------------------------------------*/
void CSetup::OnCustomdrawGain(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int AnalogGain = m_AnalogGainCtrl.GetPos();

	CameraSetAnalogGain(AnalogGain);
	CString sTemp;
	sTemp.Format("%d", AnalogGain);
	GetDlgItem(IDC_GAINTEXT)->SetWindowTextA(sTemp);

	*pResult = 0;
}

/*==============================================================
Name:	OnCustomExptime
Desc:   设置曝光时间

Param:	
Return: 
Note:    AE禁止时有效
  --------------------------------------------------------------*/
void CSetup::OnCustomdrawExptime(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if(m_Aeen)
	{
		return;
	}
	int pos;
	pos = m_ExpTimeCtrl.GetPos();

	CameraSetExposureTime(pos);

	UpdateExposurteTimeText();
	UpdateData();

	*pResult = 0;
}

/*==============================================================
Name:	UpdateExposurteTimeText
Desc:   设置曝光时间

Param:	
Return: 
Note:    AE禁止时有效
  --------------------------------------------------------------*/
void CSetup::UpdateExposurteTimeText()
{
	UINT RawTime;
	CString sTemp;

	CameraGetRowTime(&RawTime);
	sTemp.Format("%.3f ms", (float)m_ExpTime*RawTime/1000);
	//	sTemp.Format("%d",m_ExpTime);//
	GetDlgItem(IDC_EXPTEXT)->SetWindowTextA(sTemp);
}

/*==============================================================
Name:	OnColorcorrect
Desc:   check for saturation 

Param:	
Return: 
Note:    
  --------------------------------------------------------------*/
void CSetup::OnColorcorrect()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CameraSetColorEnhancement(m_bColorCorrect);
	GetDlgItem(IDC_SATURATION)->EnableWindow(m_bColorCorrect);
}

/*==============================================================
Name:	OnAeen
Desc:   check for ae 

Param:	
Return: 
Note:    
  --------------------------------------------------------------*/
void CSetup::OnAeen()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CameraSetAeState(m_Aeen);

	GetDlgItem(IDC_GAIN)->EnableWindow(!m_Aeen);
	GetDlgItem(IDC_STATIC_GAIN)->EnableWindow(!m_Aeen);

	GetDlgItem(IDC_EXPTIME)->EnableWindow(!m_Aeen);
	GetDlgItem(IDC_STATIC_TIME)->EnableWindow(!m_Aeen);
	
	GetDlgItem(IDC_AETARGET)->EnableWindow(m_Aeen);
	GetDlgItem(IDC_STATIC_TARGET)->EnableWindow(m_Aeen);

	if(!m_Aeen)
	{
		CString sTemp;
		INT iTemp;
		CameraGetExposureTime(&iTemp);
		m_ExpTime = iTemp;
		UpdateExposurteTimeText();
		m_ExpTimeCtrl.SetPos((int)(m_ExpTime));

		USHORT uiAnalogGain;
		CameraGetAnalogGain(&uiAnalogGain);
		m_AnalogGain = uiAnalogGain;
		m_AnalogGainCtrl.SetPos(m_AnalogGain);
		sTemp.Format("%d",m_AnalogGain);
		GetDlgItem(IDC_GAINTEXT)->SetWindowTextA(sTemp);
	}
}

/*==============================================================
Name:	OnHflip/OnVflip/OnMono
Desc:   设置图像镜像，横向,纵向，单色

Param:	
Return: 
Note:    
  --------------------------------------------------------------*/
void CSetup::OnHflip()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CameraSetMirror(MIRROR_DIRECTION_HORIZONTAL, m_bHFlip);
}


void CSetup::OnVflip()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CameraSetMirror(MIRROR_DIRECTION_VERTICAL, m_bVFlip);
}


void CSetup::OnMono()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CameraSetMonochrome(m_bMono); //set monochrome
}

/*==============================================================
Name:	OnCheckjpg/OnCheckbmp/OnCheckpng/OnCheckraw
Desc:   设置存储格式
Param:	
Return: 
Note:    
  --------------------------------------------------------------*/
void CSetup::OnCheckjpg()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(m_CheckJPG == TRUE)
	{
		m_FTypeIndex |= FILE_JPG;
	}
	else
	{
		m_FTypeIndex &= ~FILE_JPG;
	}
}


void CSetup::OnCheckbmp()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(m_CheckBMP == TRUE)
	{
		m_FTypeIndex |= FILE_BMP;
	}
	else
	{
		m_FTypeIndex &= ~FILE_BMP;
	}
}


void CSetup::OnCheckpng()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_CheckPNG == TRUE)
	{
		m_FTypeIndex |= FILE_PNG;
	}
	else
	{
		m_FTypeIndex &= ~FILE_PNG;
	}	
}


void CSetup::OnCheckraw()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_CheckRAW == TRUE)
	{
		m_FTypeIndex |= FILE_RAW;
	}
	else
	{
		m_FTypeIndex &= ~FILE_RAW;
	}
}

/*==============================================================
Name:	OnB2rgbA/OnB2rgbB/OnB2rgbC
Desc:    Set the transfer mode from BAYER to RGB24.
Param:	
Return: 
Note:    
  --------------------------------------------------------------*/
void CSetup::OnB2rgbA()
{
	// TODO: 在此添加控件通知处理程序代码
	CameraSetB2RGBMode(B2RGB_MODE_LAROCHE);
}


void CSetup::OnB2rgbB()
{
	// TODO: 在此添加控件通知处理程序代码
		CameraSetB2RGBMode(B2RGB_MODE_HAMILTON);
}


void CSetup::OnB2rgbC()
{
	// TODO: 在此添加控件通知处理程序代码
	CameraSetB2RGBMode(B2RGB_MODE_LINE);
}

/*==============================================================
Name:	OnLowspeed/OnHighspeed/OnSuperspeed
Desc:    Set the frame speed
Param:	
Return: 
Note:    
  --------------------------------------------------------------*/
void CSetup::OnLowspeed()
{
	// TODO: 在此添加控件通知处理程序代码
	CameraSetFrameSpeed(FRAME_SPEED_NORMAL);
	UpdateSetupWindow();
}


void CSetup::OnHighspeed()
{
	// TODO: 在此添加控件通知处理程序代码
	CameraSetFrameSpeed(FRAME_SPEED_HIGH);
	UpdateSetupWindow();
}


void CSetup::OnSuperspeed()
{
	// TODO: 在此添加控件通知处理程序代码
#ifdef HAVE_SPEED_SUPER
	CameraSetFrameSpeed(FRAME_SPEED_SUPER);
#endif
	UpdateSetupWindow();
}
/*==============================================================
Name:	OnLf50hz/OnLf60hz
Desc:    Set the frame speedSet light frequency
Param:	
Return: 
Note:    
  --------------------------------------------------------------*/
void CSetup::OnLf50hz()
{
	// TODO: 在此添加控件通知处理程序代码
	CameraSetLightFrquency(LIGHT_FREQUENCY_50HZ);
}


void CSetup::OnLf60hz()
{
	// TODO: 在此添加控件通知处理程序代码
		CameraSetLightFrquency(LIGHT_FREQUENCY_60HZ);	
}

/*==============================================================
Name:	OnPta/OnPtb/OnPtc/OnPtd
Desc:    Read the camera parameter
Param:	
Return: 
Note:    
  --------------------------------------------------------------*/
void CSetup::OnPta()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ParameterTeam = PARAMETER_TEAM_A;
	CameraReadParameter(m_ParameterTeam);
	UpdateSetupWindow();
}


void CSetup::OnPtb()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ParameterTeam = PARAMETER_TEAM_B;
	CameraReadParameter(m_ParameterTeam);
	UpdateSetupWindow();
}


void CSetup::OnPtc()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ParameterTeam = PARAMETER_TEAM_C;
	CameraReadParameter(m_ParameterTeam);
	UpdateSetupWindow();
}


void CSetup::OnPtd()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ParameterTeam = PARAMETER_TEAM_D;
	CameraReadParameter(m_ParameterTeam);
	UpdateSetupWindow();
}

/*==============================================================
Name:	OnLoadParameter
Desc:   load default camera setting
Param:	
Return: 
Note:    
  --------------------------------------------------------------*/
void CSetup::OnLoadParameter()
{
	// TODO: 在此添加控件通知处理程序代码
	CameraLoadDefault();
	UpdateSetupWindow();
	CDialogEx::OnOK();
}

/*==============================================================
Name:	OnSaveParameter
Desc:   save a/b/c/d camera parameter to team
Param:	
Return: 
Note:    
  --------------------------------------------------------------*/
void CSetup::OnSaveParameter()
{
	// TODO: 在此添加控件通知处理程序代码
	m_FileType = this->m_FTypeIndex;
	CameraSaveParameter(m_ParameterTeam);
	UpdateSetupWindow();
	CDialogEx::OnOK();
}


