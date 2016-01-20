// ShowImageDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "3DSurfaceRe.h"
#include "ShowImageDialog.h"
#include "afxdialogex.h"


// CShowImageDialog 对话框

IMPLEMENT_DYNAMIC(CShowImageDialog, CDialogEx)

CShowImageDialog::CShowImageDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CShowImageDialog::IDD, pParent)
{

}

CShowImageDialog::~CShowImageDialog()
{
}

void CShowImageDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CShowImageDialog, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CShowImageDialog 消息处理程序
void CShowImageDialog::OnShow(CImage *Image, int nID)
{
	CRect rect;
	//选择需要显示的图像
	if(!Image->IsNull())	
	{
		int cx = Image->GetWidth();
		int cy = Image->GetHeight();
		CRect rectSrc;
		CWnd *pWnd=GetDlgItem(nID);//获得pictrue控件窗口的句柄  
			
		pWnd->GetWindowRect(&rect);
		ScreenToClient(&rect);
		int a = rect.Width();
		rectSrc = CRect(CPoint(0, 0), CPoint(cx, cy));
		pWnd->MoveWindow(rect, TRUE);//将窗口移动到Picture控件表示的矩形区域  					
		pWnd->GetClientRect(&rect);//获得pictrue控件所在的矩形区域 

		CDC *pDC=pWnd->GetDC();//获得pictrue控件的DC  
	
	//	Image->Save("1.jpg");
		
		Image->Draw(pDC->m_hDC, rect, rectSrc); //将图片画到Picture控件表示的矩形区域 
		ReleaseDC(pDC);//释放picture控件的DC  
	}
	
	return;
}

void CShowImageDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
//	OnShow(showimage, IDC_PICTURE1);
}
