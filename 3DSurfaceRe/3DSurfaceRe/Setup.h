#pragma once
#include "./sdk/DICAMAPI.h"
#include "Dialog3.h"

// CSetup 对话框

class CDialog3;
class CSetup : public CDialogEx
{
	DECLARE_DYNAMIC(CSetup)

public:
	void UpdateSetupWindow();
	CSetup(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetup();

// 对话框数据
	enum { IDD = IDD_SETUP_DIALOG };

protected:
	void UpdateColorGain();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnOK();
	virtual BOOL OnInitDialog();

	afx_msg void OnAwbone();
	afx_msg void OnClose();
	afx_msg void OnCustomdrawRgain(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawGgain(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawBgain(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawGamma(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawContrast(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawSaturation(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawAetarget(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawGain(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawExptime(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnColorcorrect();
	afx_msg void OnAeen();
	afx_msg void OnHflip();
	afx_msg void OnVflip();
	afx_msg void OnMono();
	afx_msg void OnCheckjpg();
	afx_msg void OnCheckbmp();
	afx_msg void OnCheckpng();
	afx_msg void OnCheckraw();
	afx_msg void OnB2rgbA();
	afx_msg void OnB2rgbB();
	afx_msg void OnB2rgbC();
	afx_msg void OnLowspeed();
	afx_msg void OnHighspeed();
	afx_msg void OnSuperspeed();
	afx_msg void OnLf50hz();
	afx_msg void OnLf60hz();
	afx_msg void OnPta();
	afx_msg void OnPtb();
	afx_msg void OnPtc();
	afx_msg void OnPtd();
	afx_msg void OnLoadParameter();
	afx_msg void OnSaveParameter();
	DECLARE_MESSAGE_MAP()
	
public:
	BYTE m_FTypeIndex;
private:
	CSliderCtrl m_RGainCtrl;
	CSliderCtrl m_GGainCtrl;
	CSliderCtrl m_BGainCtrl;
	CSliderCtrl m_ContrastCtrl;
	CSliderCtrl m_GammaCtrl;
	CSliderCtrl m_SaturationCtrl;
	CSliderCtrl m_AeTargetCtrl;
	CSliderCtrl m_AnalogGainCtrl;
	CSliderCtrl m_ExpTimeCtrl;

	int m_Gamma;
	int m_ExpTime;
	int m_AnalogGain;
	int m_AeTarget;
	int m_RGain;
	int m_GGain;
	int m_BGain;
	int m_Contrast;
	int m_Saturation;

	int m_FrameSpeed;

	BOOL m_Aeen;
	BOOL m_bColorCorrect;
	BOOL m_bHFlip;
	BOOL m_bMono;
	BOOL m_bVFlip;
	BOOL m_CheckBMP;
	BOOL m_CheckJPG;
	BOOL m_CheckRAW;
	BOOL m_CheckPNG;
private:
	void UpdateExposurteTimeText();
	DI_PARAMETER_TEAM m_ParameterTeam;

};
