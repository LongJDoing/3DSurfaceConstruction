// InputDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "3DSurfaceRe.h"
#include "InputDialog.h"


// CInputDialog

IMPLEMENT_DYNAMIC(CInputDialog, CDialogEx)

CInputDialog::CInputDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInputDialog::IDD, pParent)
{
	m_cameravector1 = m_CameraVector[0];
	m_cameravector2 = m_CameraVector[1];
	m_cameravector3 = m_CameraVector[2]    ;
	m_cameravector4 = m_CameraVector[3];
	m_cameradistortion1 = m_Distortion[0];
	m_cameradistortion2 = m_Distortion[1];
	m_cameradistortion3 =   m_Distortion[2];
	m_cameradistortion4 = m_Distortion[3];
	m_pixelsizex = m_sizex;  // pointgrey 相机的像素尺寸4.4
	m_pixelsizey = m_sizey;
	m_rotation1 = m_RotationVector[0];
	m_rotation2 = m_RotationVector[1];
	m_rotation3 = m_RotationVector[2];
	m_rotation4 = m_RotationVector[3];
	m_rotation5 = m_RotationVector[4];
	m_rotation6 = m_RotationVector[5];
	m_rotation7 = m_RotationVector[6];
	m_rotation8 = m_RotationVector[7];
	m_rotation9 = m_RotationVector[8];
	m_translation1 = m_TranslationVector[0];
	m_translation2 = m_TranslationVector[1];
	m_translation3 = m_TranslationVector[2]  ;
	m_distance = m_Distance;
	F = (m_CameraVector[0]*m_sizex/1000 + m_CameraVector[1]*m_sizey/1000)/2;
}

CInputDialog::~CInputDialog()
{
}

void CInputDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CAMERAPA1_EDIT, m_cameravector1);
	DDX_Text(pDX, IDC_CAMERAPA2_EDIT, m_cameravector2);
	DDX_Text(pDX, IDC_CMAERAPA3_EDIT, m_cameravector3);
	DDX_Text(pDX, IDC_CMAERAPA4_EDIT, m_cameravector4);
	DDX_Text(pDX, IDC_DISTORTION1_EDIT, m_cameradistortion1);
	DDX_Text(pDX, IDC_DISTORTION2_EDIT, m_cameradistortion2);
	DDX_Text(pDX, IDC_DISTORTION3_EDIT, m_cameradistortion3);
	DDX_Text(pDX, IDC_DISTORTION4_EDIT, m_cameradistortion4);
	DDX_Text(pDX, IDC_PIXELSZ1_EDIT, m_pixelsizex);
	DDX_Text(pDX, IDC_PIXELSZ2_EDIT, m_pixelsizey);
	DDX_Text(pDX, IDC_ROTATION1_EDIT, m_rotation1);
	DDX_Text(pDX, IDC_ROTATION2_EDIT, m_rotation2);
	DDX_Text(pDX, IDC_ROTATION3_EDIT, m_rotation3);
	DDX_Text(pDX, IDC_ROTATION4_EDIT, m_rotation4);
	DDX_Text(pDX, IDC_ROTATION5_EDIT, m_rotation5);
	DDX_Text(pDX, IDC_ROTATION6_EDIT, m_rotation6);
	DDX_Text(pDX, IDC_ROTATION7_EDIT, m_rotation7);
	DDX_Text(pDX, IDC_ROTATION8_EDIT, m_rotation8);
	DDX_Text(pDX, IDC_ROTATION9_EDIT, m_rotation9);
	DDX_Text(pDX, IDC_TRANSLATION1_EDIT2, m_translation1);
	DDX_Text(pDX, IDC_TRANSLATION2_EDIT3, m_translation2);
	DDX_Text(pDX, IDC_TRANSLATION3_EDIT, m_translation3);
	DDX_Text(pDX, IDC_DISTANCE_EDIT, m_distance);
}

BEGIN_MESSAGE_MAP(CInputDialog, CDialogEx)
	ON_WM_PAINT()
	ON_WM_ACTIVATE()
	ON_BN_CLICKED(IDC_OK_BUTTON, &CInputDialog::OnOkButton)
	ON_EN_CHANGE(IDC_CAMERAPA1_EDIT, &CInputDialog::OnChangeCamerapa1Edit)
	ON_EN_CHANGE(IDC_CAMERAPA2_EDIT, &CInputDialog::OnChangeCamerapa2Edit)
	ON_EN_CHANGE(IDC_CMAERAPA3_EDIT, &CInputDialog::OnChangeCmaerapa3Edit)
	ON_EN_CHANGE(IDC_CMAERAPA4_EDIT, &CInputDialog::OnChangeCmaerapa4Edit)
	ON_EN_CHANGE(IDC_DISTORTION1_EDIT, &CInputDialog::OnChangeDistortion1Edit)
	ON_EN_CHANGE(IDC_DISTORTION2_EDIT, &CInputDialog::OnChangeDistortion2Edit)
	ON_EN_CHANGE(IDC_DISTORTION3_EDIT, &CInputDialog::OnChangeDistortion3Edit)
	ON_EN_CHANGE(IDC_DISTORTION4_EDIT, &CInputDialog::OnChangeDistortion4Edit)
	ON_EN_CHANGE(IDC_PIXELSZ1_EDIT, &CInputDialog::OnChangePixelsz1Edit)
	ON_EN_CHANGE(IDC_PIXELSZ2_EDIT, &CInputDialog::OnChangePixelsz2Edit)
	ON_EN_CHANGE(IDC_ROTATION1_EDIT, &CInputDialog::OnChangeRotation1Edit)
	ON_EN_CHANGE(IDC_ROTATION2_EDIT, &CInputDialog::OnChangeRotation2Edit)
	ON_EN_CHANGE(IDC_ROTATION3_EDIT, &CInputDialog::OnChangeRotation3Edit)
	ON_EN_CHANGE(IDC_ROTATION4_EDIT, &CInputDialog::OnChangeRotation4Edit)
	ON_EN_CHANGE(IDC_ROTATION5_EDIT, &CInputDialog::OnChangeRotation5Edit)
	ON_EN_CHANGE(IDC_ROTATION6_EDIT, &CInputDialog::OnChangeRotation6Edit)
	ON_EN_CHANGE(IDC_ROTATION7_EDIT, &CInputDialog::OnChangeRotation7Edit)
	ON_EN_CHANGE(IDC_ROTATION8_EDIT, &CInputDialog::OnChangeRotation8Edit)
	ON_EN_CHANGE(IDC_ROTATION9_EDIT, &CInputDialog::OnChangeRotation9Edit)
	ON_EN_CHANGE(IDC_TRANSLATION1_EDIT2, &CInputDialog::OnChangeTranslation1Edit2)
	ON_EN_CHANGE(IDC_TRANSLATION2_EDIT3, &CInputDialog::OnChangeTranslation2Edit3)
	ON_EN_CHANGE(IDC_TRANSLATION3_EDIT, &CInputDialog::OnChangeTranslation3Edit)
	ON_EN_CHANGE(IDC_DISTANCE_EDIT, &CInputDialog::OnChangeDistanceEdit)
END_MESSAGE_MAP()



// CInputDialog 消息处理程序




void CInputDialog::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);

	// TODO: 在此处添加消息处理程序代码
}


void CInputDialog::OnOkButton()
{
	// TODO: 在此添加控件通知处理程序代码

	// 相机内部向量
	//	extern double m_CameraVector[4];
	m_CameraVector[0] = m_cameravector1;
	m_CameraVector[1] = m_cameravector2;
	m_CameraVector[2] = m_cameravector3;
	m_CameraVector[3] = m_cameravector4;
	// 镜头畸变
	//	extern double m_Distortion[4];
	m_Distortion[0] = m_cameradistortion1;
	m_Distortion[1] = m_cameradistortion2;
	m_Distortion[2] = m_cameradistortion3;
	m_Distortion[3] = m_cameradistortion4;

	// 相机传感器的像素大小
	m_sizex = m_pixelsizex; // mm
	m_sizey = m_pixelsizey;

	//	extern double F;
	F = (m_CameraVector[0]*m_sizex/1000 + m_CameraVector[1]*m_sizey/1000)/2;

	//外部参数，旋转矩阵
	//	extern double m_RotationVector[9];
	m_RotationVector[0] =m_rotation1;
	m_RotationVector[1] = m_rotation2;
	m_RotationVector[2] = m_rotation3;
	m_RotationVector[3] = m_rotation4;
	m_RotationVector[4] = m_rotation5;
	m_RotationVector[5] = m_rotation6;
	m_RotationVector[6] = m_rotation7;
	m_RotationVector[7] = m_rotation8;
	m_RotationVector[8] = m_rotation9;

	//外部参数，平移矩阵
	//	extern double m_TranslationVector[3];
	m_TranslationVector[0] = m_translation1;
	m_TranslationVector[1] = m_translation2;
	m_TranslationVector[2] = m_translation3;
	m_Distance = m_distance;
	CDialogEx::OnOK();

}


void CInputDialog::OnChangeCamerapa1Edit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	this->UpdateData(TRUE);
}


void CInputDialog::OnChangeCamerapa2Edit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	this->UpdateData(TRUE);
}


void CInputDialog::OnChangeCmaerapa3Edit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	this->UpdateData(TRUE);
}


void CInputDialog::OnChangeCmaerapa4Edit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	this->UpdateData(TRUE);
}


void CInputDialog::OnChangeDistortion1Edit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	this->UpdateData(TRUE);
}


void CInputDialog::OnChangeDistortion2Edit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	this->UpdateData(TRUE);
}


void CInputDialog::OnChangeDistortion3Edit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	this->UpdateData(TRUE);
}


void CInputDialog::OnChangeDistortion4Edit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	this->UpdateData(TRUE);
}


void CInputDialog::OnChangePixelsz1Edit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	this->UpdateData(TRUE);
}


void CInputDialog::OnChangePixelsz2Edit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	this->UpdateData(TRUE);
}


void CInputDialog::OnChangeRotation1Edit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	this->UpdateData(TRUE);
}


void CInputDialog::OnChangeRotation2Edit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	this->UpdateData(TRUE);
}


void CInputDialog::OnChangeRotation3Edit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	this->UpdateData(TRUE);
}


void CInputDialog::OnChangeRotation4Edit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	this->UpdateData(TRUE);
}


void CInputDialog::OnChangeRotation5Edit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	this->UpdateData(TRUE);
}


void CInputDialog::OnChangeRotation6Edit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	this->UpdateData(TRUE);
}


void CInputDialog::OnChangeRotation7Edit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	this->UpdateData(TRUE);
}


void CInputDialog::OnChangeRotation8Edit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	this->UpdateData(TRUE);
}


void CInputDialog::OnChangeRotation9Edit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	this->UpdateData(TRUE);
}


void CInputDialog::OnChangeTranslation1Edit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	this->UpdateData(TRUE);
}


void CInputDialog::OnChangeTranslation2Edit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	this->UpdateData(TRUE);
}


void CInputDialog::OnChangeTranslation3Edit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	this->UpdateData(TRUE);
}


void CInputDialog::OnChangeDistanceEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	this->UpdateData(TRUE);
}
