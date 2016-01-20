// ShowImageDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "3DSurfaceRe.h"
#include "ShowImageDialog.h"
#include "afxdialogex.h"


// CShowImageDialog �Ի���

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


// CShowImageDialog ��Ϣ�������
void CShowImageDialog::OnShow(CImage *Image, int nID)
{
	CRect rect;
	//ѡ����Ҫ��ʾ��ͼ��
	if(!Image->IsNull())	
	{
		int cx = Image->GetWidth();
		int cy = Image->GetHeight();
		CRect rectSrc;
		CWnd *pWnd=GetDlgItem(nID);//���pictrue�ؼ����ڵľ��  
			
		pWnd->GetWindowRect(&rect);
		ScreenToClient(&rect);
		int a = rect.Width();
		rectSrc = CRect(CPoint(0, 0), CPoint(cx, cy));
		pWnd->MoveWindow(rect, TRUE);//�������ƶ���Picture�ؼ���ʾ�ľ�������  					
		pWnd->GetClientRect(&rect);//���pictrue�ؼ����ڵľ������� 

		CDC *pDC=pWnd->GetDC();//���pictrue�ؼ���DC  
	
	//	Image->Save("1.jpg");
		
		Image->Draw(pDC->m_hDC, rect, rectSrc); //��ͼƬ����Picture�ؼ���ʾ�ľ������� 
		ReleaseDC(pDC);//�ͷ�picture�ؼ���DC  
	}
	
	return;
}

void CShowImageDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
//	OnShow(showimage, IDC_PICTURE1);
}
