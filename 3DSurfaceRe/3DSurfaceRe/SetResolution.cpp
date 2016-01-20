// SetResolution.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "3DSurfaceRe.h"
#include "SetResolution.h"
#include "afxdialogex.h"


// CSetResolution �Ի���

IMPLEMENT_DYNAMIC(CSetResolution, CDialogEx)

CSetResolution::CSetResolution(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetResolution::IDD, pParent)
{
	m_RSLTIndex = 1;
	m_CaptureIndex = 1;
	m_HOff1 = 0;
	m_VOff1 = 0;
	m_Height1 = 0;
	m_Width1 = 0;
	m_pParentWnd = pParent;
}

CSetResolution::~CSetResolution()
{
}

void CSetResolution::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_HOFF, m_HOff1);
	DDX_Text(pDX, IDC_VOFF, m_VOff1);
	DDX_Text(pDX, IDC_HEIGHT, m_Height1);
	DDX_Text(pDX, IDC_WIDTH, m_Width1);
}


BEGIN_MESSAGE_MAP(CSetResolution, CDialogEx)
	ON_BN_CLICKED(IDC_RESOLUTION_A, &CSetResolution::OnResolutionA)
	ON_BN_CLICKED(IDC_RESOLUTION_B, &CSetResolution::OnResolutionB)
	ON_BN_CLICKED(IDC_RESOLUTION_C, &CSetResolution::OnResolutionC)
	ON_BN_CLICKED(IDC_RESOLUTION_D, &CSetResolution::OnResolutionD)
	ON_BN_CLICKED(IDC_RESOLUTION_E, &CSetResolution::OnResolutionE)
	ON_BN_CLICKED(IDC_RESOLUTION_F, &CSetResolution::OnResolutionF)
	ON_BN_CLICKED(IDC_CAPTURERESOLUTION_A, &CSetResolution::OnCaptureresolutionA)
	ON_BN_CLICKED(IDC_CAPTURERESOLUTION_B, &CSetResolution::OnCaptureresolutionB)
	ON_BN_CLICKED(IDC_CAPTURERESOLUTION_C, &CSetResolution::OnCaptureresolutionC)
	ON_BN_CLICKED(IDC_CAPTURERESOLUTION_D, &CSetResolution::OnCaptureresolutionD)
	ON_BN_CLICKED(IDC_CAPTURERESOLUTION_E, &CSetResolution::OnCaptureresolutionE)
	ON_BN_CLICKED(IDC_CAPTURERESOLUTION_F, &CSetResolution::OnCaptureresolutionF)
	ON_EN_CHANGE(IDC_HOFF, &CSetResolution::OnChangeHoff)
	ON_EN_CHANGE(IDC_VOFF, &CSetResolution::OnChangeVoff)
	ON_EN_CHANGE(IDC_WIDTH, &CSetResolution::OnChangeWidth)
	ON_EN_CHANGE(IDC_HEIGHT, &CSetResolution::OnChangeHeight)
END_MESSAGE_MAP()


// CSetResolution ��Ϣ�������
/*==============================================================
Name:	OnResolutionA/B/C/D/E/F
Desc:  Choose one resolution 

Param:	
Return: 
Note:   
  --------------------------------------------------------------*/

void CSetResolution::OnResolutionA()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_RSLTIndex = RESOLUTION_A_INDEX;
	GetDlgItem(IDC_HOFF)->EnableWindow(FALSE);
	GetDlgItem(IDC_VOFF)->EnableWindow(FALSE);
	GetDlgItem(IDC_WIDTH)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEIGHT)->EnableWindow(FALSE);
}


void CSetResolution::OnResolutionB()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_RSLTIndex = RESOLUTION_B_INDEX;
	GetDlgItem(IDC_HOFF)->EnableWindow(FALSE);
	GetDlgItem(IDC_VOFF)->EnableWindow(FALSE);
	GetDlgItem(IDC_WIDTH)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEIGHT)->EnableWindow(FALSE);
}


void CSetResolution::OnResolutionC()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_RSLTIndex = RESOLUTION_C_INDEX;
	GetDlgItem(IDC_HOFF)->EnableWindow(FALSE);
	GetDlgItem(IDC_VOFF)->EnableWindow(FALSE);
	GetDlgItem(IDC_WIDTH)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEIGHT)->EnableWindow(FALSE);
}


void CSetResolution::OnResolutionD()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_RSLTIndex = RESOLUTION_D_INDEX;
	GetDlgItem(IDC_HOFF)->EnableWindow(FALSE);
	GetDlgItem(IDC_VOFF)->EnableWindow(FALSE);
	GetDlgItem(IDC_WIDTH)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEIGHT)->EnableWindow(FALSE);
}


void CSetResolution::OnResolutionE()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_RSLTIndex = RESOLUTION_E_INDEX;
	GetDlgItem(IDC_HOFF)->EnableWindow(FALSE);
	GetDlgItem(IDC_VOFF)->EnableWindow(FALSE);
	GetDlgItem(IDC_WIDTH)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEIGHT)->EnableWindow(FALSE);
}


void CSetResolution::OnResolutionF()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_RSLTIndex = RESOLUTION_F_INDEX ;
	GetDlgItem(IDC_HOFF)->EnableWindow(TRUE);
	GetDlgItem(IDC_VOFF)->EnableWindow(TRUE);
	GetDlgItem(IDC_HEIGHT)->EnableWindow(TRUE);
	GetDlgItem(IDC_WIDTH)->EnableWindow(TRUE);
}

/*==============================================================
Name:	OnCaptureResolutionA/B/C/D/E/F
Desc:  Choose one capture resolution 

Param:	
Return: 
Note:   
  --------------------------------------------------------------*/
void CSetResolution::OnCaptureresolutionA()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_CaptureIndex = RESOLUTION_A_INDEX;
}


void CSetResolution::OnCaptureresolutionB()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_CaptureIndex = RESOLUTION_B_INDEX;
}


void CSetResolution::OnCaptureresolutionC()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_CaptureIndex = RESOLUTION_C_INDEX;
}


void CSetResolution::OnCaptureresolutionD()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_CaptureIndex = RESOLUTION_D_INDEX;
}


void CSetResolution::OnCaptureresolutionE()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_CaptureIndex = RESOLUTION_E_INDEX ;
}


void CSetResolution::OnCaptureresolutionF()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_CaptureIndex = RESOLUTION_F_INDEX ;
}

/*==============================================================
Name:	OnChange
Desc:  �Զ���ֱ���

Param:	
Return: 
Note:   
  --------------------------------------------------------------*/
void CSetResolution::OnChangeHoff()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
}


void CSetResolution::OnChangeVoff()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
}


void CSetResolution::OnChangeWidth()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
}


void CSetResolution::OnChangeHeight()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
}

void CSetResolution::OnOK()
{
	BYTE TempIndex = m_RSLTIndex;
	BYTE TempCIndex = m_CaptureIndex;

	m_Resolution = (DI_RESOLUTION)TempIndex;
	m_HOff = m_HOff1;
	m_VOff = m_VOff1;
	m_Width = m_Width1;
	m_Height = m_Height1;
	m_CaptureResolution = (DI_RESOLUTION)TempCIndex;

	CDialogEx::OnOK();
}

void CSetResolution::OnCancel()
{
	CDialogEx::OnCancel();
}
/*==============================================================
Name:	OnInitDialog
Desc:   ��ʼ������,���ؼ���ʼ��

Param:	
Return: 
Note:   
  --------------------------------------------------------------*/
BOOL CSetResolution::OnInitDialog()
{
	CDialogEx::OnInitDialog();

		GetDlgItem(IDC_HOFF)->EnableWindow(FALSE);
	GetDlgItem(IDC_VOFF)->EnableWindow(FALSE);
	GetDlgItem(IDC_WIDTH)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEIGHT)->EnableWindow(FALSE);

	SetDlgItemText(IDC_RESOLUTION_A, RESOLUTION_A_TEXT);
	SetDlgItemText(IDC_RESOLUTION_B, RESOLUTION_B_TEXT);
	SetDlgItemText(IDC_RESOLUTION_C, RESOLUTION_C_TEXT);
	SetDlgItemText(IDC_RESOLUTION_D, RESOLUTION_D_TEXT);
	SetDlgItemText(IDC_RESOLUTION_E, RESOLUTION_E_TEXT);
	SetDlgItemText(IDC_RESOLUTION_F, RESOLUTION_F_TEXT);

	GetDlgItem(IDC_RESOLUTION_A)->EnableWindow(RESOLUTION_A_ENABLE);
	GetDlgItem(IDC_RESOLUTION_B)->EnableWindow(RESOLUTION_B_ENABLE);
	GetDlgItem(IDC_RESOLUTION_C)->EnableWindow(RESOLUTION_C_ENABLE);
	GetDlgItem(IDC_RESOLUTION_D)->EnableWindow(RESOLUTION_D_ENABLE);
	GetDlgItem(IDC_RESOLUTION_E)->EnableWindow(RESOLUTION_E_ENABLE);
	GetDlgItem(IDC_RESOLUTION_F)->EnableWindow(RESOLUTION_F_ENABLE);	
	switch(m_RSLTIndex)
	{
		case RESOLUTION_A_INDEX:
			CheckDlgButton(IDC_RESOLUTION_A, 1);
			break;
		case RESOLUTION_B_INDEX:
			CheckDlgButton(IDC_RESOLUTION_B, 1);
			break;
		case RESOLUTION_C_INDEX:
			CheckDlgButton(IDC_RESOLUTION_C, 1);
			break;
		case RESOLUTION_D_INDEX:
			CheckDlgButton(IDC_RESOLUTION_D, 1);
			break;	
		case RESOLUTION_E_INDEX:
			CheckDlgButton(IDC_RESOLUTION_E, 1);
			break;	
		case RESOLUTION_F_INDEX:
			CheckDlgButton(IDC_RESOLUTION_F, 1);
			GetDlgItem(IDC_HOFF)->EnableWindow(TRUE);
			GetDlgItem(IDC_VOFF)->EnableWindow(TRUE);
			GetDlgItem(IDC_WIDTH)->EnableWindow(TRUE);
			GetDlgItem(IDC_HEIGHT)->EnableWindow(TRUE);
			break;		
		default:
			break;
	}

	//Capture

	SetDlgItemText(IDC_CAPTURERESOLUTION_A, RESOLUTION_A_TEXT);
	SetDlgItemText(IDC_CAPTURERESOLUTION_B, RESOLUTION_B_TEXT);
	SetDlgItemText(IDC_CAPTURERESOLUTION_C, RESOLUTION_C_TEXT);
	SetDlgItemText(IDC_CAPTURERESOLUTION_D, RESOLUTION_D_TEXT);
	SetDlgItemText(IDC_CAPTURERESOLUTION_E, RESOLUTION_E_TEXT);
	SetDlgItemText(IDC_CAPTURERESOLUTION_F, RESOLUTION_F_TEXT);

	GetDlgItem(IDC_CAPTURERESOLUTION_A)->EnableWindow(RESOLUTION_A_ENABLE);
	GetDlgItem(IDC_CAPTURERESOLUTION_B)->EnableWindow(RESOLUTION_B_ENABLE);
	GetDlgItem(IDC_CAPTURERESOLUTION_C)->EnableWindow(RESOLUTION_C_ENABLE);
	GetDlgItem(IDC_CAPTURERESOLUTION_D)->EnableWindow(RESOLUTION_D_ENABLE);
	GetDlgItem(IDC_CAPTURERESOLUTION_E)->EnableWindow(RESOLUTION_E_ENABLE);
	GetDlgItem(IDC_CAPTURERESOLUTION_F)->EnableWindow(RESOLUTION_F_ENABLE);	
	
	switch(m_CaptureIndex)
	{
	case RESOLUTION_A_INDEX:
		CheckDlgButton(IDC_CAPTURERESOLUTION_A, 1);
		break;
	case RESOLUTION_B_INDEX:
		CheckDlgButton(IDC_CAPTURERESOLUTION_B, 1);
		break;
	case RESOLUTION_C_INDEX:
		CheckDlgButton(IDC_CAPTURERESOLUTION_C, 1);
		break;
	case RESOLUTION_D_INDEX:
		CheckDlgButton(IDC_CAPTURERESOLUTION_D, 1);
		break;	
	case RESOLUTION_E_INDEX:
		CheckDlgButton(IDC_CAPTURERESOLUTION_E, 1);
		break;	
	case RESOLUTION_F_INDEX:
		CheckDlgButton(IDC_CAPTURERESOLUTION_F, 1);
		break;
	default:
		break;
	}
	return TRUE;
}
