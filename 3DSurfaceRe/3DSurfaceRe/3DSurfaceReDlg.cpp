
// 3DSurfaceReDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "3DSurfaceRe.h"
#include "3DSurfaceReDlg.h"
#include "afxdialogex.h"
#include <fstream>
#include <iostream>

using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

bool b_3DConstruction = false; // �ж��Ƿ����3D�ؽ�

ofstream fout(".\\result.txt", ios::out|ios::in|ios::ate);
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// 3DSurfaceReDlg �Ի���




C3DSurfaceReDlg::C3DSurfaceReDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C3DSurfaceReDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_my1dmorphology = new CMy1DMorphology();
	m_para1 = new CDialog1();
	m_para2 = new CDialog2();
	m_para3 = new CDialog3();
	m_Width = 0;
	m_Height = 0;
	//������������
	m_DrawBuffer = new CImage();
	m_DrawBuffer->Create(640,480,24);
	

	// ��ջ�ͼ��
	CDC *MemDC = CDC::FromHandle(m_DrawBuffer->GetDC());
	MemDC->FillSolidRect(0, 0, 640, 480, RGB(62, 70, 55)); // ������Ϊ������������ɫ

	b_is = false;
	b_do = false;
	b_ifcorner = false;
	b_objectcorner = false;
	b_CalObject = false;
	b_calProject = false;
	labelmap = 0;
	hreferencelabelmap = 0;
	vreferencelabelmap = 0;
	objectlabelmap = 0;
	projectioncenterwordcoordinate = 0;
	cameracenterwordcoordinate = 0;
	referenceplane_1verticalphasemap = 0;
	referenceplane_1horizontalphasemap = 0; 
	referenceplane_2verticalphasemap = 0;
	referenceplane_2horizontalphasemap = 0;
	referenceplane_1verticalabsolutephasemap = 0;
	referenceplane_1horizontalabsolutephasemap = 0;
	referenceplane_2verticalabsolutephasemap = 0;
	referenceplane_2horizontalabsolutephasemap = 0;
	m_times = 0;
	m_CornerImg = 0;
	plane_1correspondpoints = 0;
	plane_2correspondpoints = 0;
	PIcameracoordinate = 0;
	objectwordcoordinate = 0;

}

// �Զ�����������
C3DSurfaceReDlg::~C3DSurfaceReDlg()
{
}
void C3DSurfaceReDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_TABMAIN, m_tabMain);
}

BEGIN_MESSAGE_MAP(C3DSurfaceReDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_NOTIFY(TCN_SELCHANGE, IDC_TABMAIN, &C3DSurfaceReDlg::OnTcnSelchangeTabmain)
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()

	// ��Ϣ����
	END_MESSAGE_MAP()


// 3DSurfaceReDlg ��Ϣ�������

BOOL C3DSurfaceReDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	 //���ѡ�
	m_tabMain.InsertItem(0,_T("Camera Controls"));
    m_tabMain.InsertItem(1,_T("Projector Calibration"));//�� ���ɸ��ģ���sheetҳ�����֣�
	m_tabMain.InsertItem(2,_T("3D Reconstruction"));

	 //�����Ի���,���ҽ�IDC_TABMAIN�ؼ���Ϊ������
	m_para3->Create(IDD_DIALOG3, GetDlgItem(IDC_TABMAIN));
	m_para1->Create(IDD_DIALOG1, GetDlgItem(IDC_TABMAIN));
	m_para2->Create(IDD_DIALOG2, GetDlgItem(IDC_TABMAIN));
	
	 //���IDC_tabMain�ͻ�����С
	CRect rs;
	m_tabMain.GetClientRect(&rs);
	 //�����ӶԻ����ڸ������е�λ�ã����ԸĶ���ֵ��ʹ�Ӵ���Ĵ�С���ʣ�
	rs.top += 20;
	rs.bottom -= 5;
	rs.left += 5;
	rs.right -= 5;
	 //�����ӶԻ���ߴ粢�ƶ���ָ��λ��
	m_para1->MoveWindow(&rs);
	m_para2->MoveWindow(&rs);
	m_para3->MoveWindow(&rs);
	 //�ֱ��������غ���ʾ
	m_para3->ShowWindow(true);
	m_para1->ShowWindow(false);
	m_para2->ShowWindow(false);
	//����Ĭ�ϵ�ѡ�
	m_tabMain.SetCurSel(0);

	m_para1->GetDlgItem(IDC_IMPORTSTRIPES)->EnableWindow(FALSE);
	m_para1->GetDlgItem(IDC_CALCULATERPM)->EnableWindow(FALSE);
	m_para1->GetDlgItem(IDC_CALCULATEAPM)->EnableWindow(FALSE);
	m_para1->GetDlgItem(IDC_EXTRACTSAMPT)->EnableWindow(FALSE);
	m_para1->GetDlgItem(IDC_CALCULATECORRESPT)->EnableWindow(FALSE);
	m_para1->GetDlgItem(IDC_COMPUTEPROJECTORCENTER)->EnableWindow(FALSE);
	m_para1->GetDlgItem(IDC_CALCULATECORNER)->EnableWindow(TRUE);
	m_para1->GetDlgItem(IDC_INPUTPA)->EnableWindow(TRUE);
	// ����tab-control ��combobox�ؼ�
	CString tmp1, tmp2;

	tmp1 = _T("Reference Plane 1");
	tmp2 = _T("Reference Plane 2");

	m_para1->m_ChPlaneList.AddString(tmp1);
	m_para1->m_ChPlaneList.AddString(tmp2);
	m_para1->m_ChPlaneList.SetCurSel(0);

	tmp1 = _T("Horizontal Direction");
	tmp2 = _T("Vertical Direction");

	m_para1->m_ChDirectionList.AddString(tmp1);
	m_para1->m_ChDirectionList.AddString(tmp2);
	m_para1->m_ChDirectionList.SetCurSel(0);

	// ���� dialog2
	m_para2->GetDlgItem(IDC_IMPORTSTRIPES)->EnableWindow(FALSE);
	m_para2->GetDlgItem(IDC_CALCULATERPM)->EnableWindow(FALSE);
	m_para2->GetDlgItem(IDC_CALCULATEAPM)->EnableWindow(FALSE);
	m_para2->GetDlgItem(IDC_FINDPROJECTIONCORPT)->EnableWindow(FALSE);
	m_para2->GetDlgItem(IDC_3DRECONSTRUCTION)->EnableWindow(FALSE);
	m_para2->GetDlgItem(IDC_CALCULATECORNER)->EnableWindow(TRUE);
	// ����tab-control ��combobox�ؼ�

	tmp1 = _T("Object 1");
	tmp2 = _T("Object 2");

	m_para2->m_ChObjectList.AddString(tmp1);
	m_para2->m_ChObjectList.AddString(tmp2);
	m_para2->m_ChObjectList.SetCurSel(0);

	tmp1 = _T("Horizontal Direction");
	tmp2 = _T("Vertical Direction");

	m_para2->m_ChDirectionList.AddString(tmp1);
	m_para2->m_ChDirectionList.AddString(tmp2);
	m_para2->m_ChDirectionList.SetCurSel(0);

	// ���ƴ�С�Ĵ���
	m_Resize.SetOwner(this);
	
	m_Resize.SetResize(IDC_PICTURESTATIC,PK_TOP_LEFT,PK_BOTTOM_RIGHT); 
	m_Resize.SetResize(IDC_PICTURE,PK_TOP_LEFT,PK_BOTTOM_RIGHT); 
	m_Resize.SetResize(IDC_PICTURE2,PK_TOP_LEFT,PK_BOTTOM_MOVE); 
	m_Resize.SetResize(IDC_PICTURE3,PK_TOP_MOVE2,PK_BOTTOM_MOVE1); 
	m_Resize.SetResize(IDC_PICTURE4,PK_TOP_MOVE1,PK_BOTTOM_MOVE2); 
	m_Resize.SetResize(IDC_TABMAIN,PK_TOP_RIGHT,PK_BOTTOM_RIGHT); 

//	 m_Resize.SetResize(IDC_TABMAIN,PK_TOP_LEFT,PK_TOP_LEFT); 
  	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void C3DSurfaceReDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void C3DSurfaceReDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		CDC *MemDC = CDC::FromHandle(m_DrawBuffer->GetDC());
		CWnd *pWnd=GetDlgItem(IDC_PICTURE);//���pictrue�ؼ����ڵľ��  
		CRect rect;
		pWnd->GetClientRect(&rect);
		
		CDC *pDC=pWnd->GetDC();//���pictrue�ؼ���DC  
		HDC hDC = pDC->GetSafeHdc();
		CRect srcrect(0,0,640,480);
		m_DrawBuffer->StretchBlt(hDC,  rect,srcrect);
		//pDC->BitBlt(0, 0, rect.Width(), rect.Height(),MemDC, 0, 0, SRCCOPY);

	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR C3DSurfaceReDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//==============================================================
//	              =====�������====
//==============================================================

/*==============================================================
����:	OnTcnSelchangeTabmain
����:   �ı�tab�ؼ���ѡ��ͬ��ҳ
����:   
-------------------------------------------------------------*/
void C3DSurfaceReDlg::OnTcnSelchangeTabmain(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int CurSel = m_tabMain.GetCurSel();
	 switch(CurSel)
	 {
	 case 0:
		 m_para3->ShowWindow(true);
		 m_para1->ShowWindow(false);
		 m_para2->ShowWindow(false);
		 break;
	 case 1:
		 m_para3->ShowWindow(false);
		 m_para1->ShowWindow(true);
		 m_para2->ShowWindow(false);
		 break;
	 case 2:
		 m_para3->ShowWindow(false);
		 m_para1->ShowWindow(false);
		 m_para2->ShowWindow(true);
		 break;
	 default:;
	 } 
	*pResult = 0;
}


/*==============================================================
����:	OnSize
����:   ���ڿռ����Ŵ��ڴ�С�ı���ı�
����: 
--------------------------------------------------------------*/
void C3DSurfaceReDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	m_Resize.OnSize(cx,cy);
	// TODO: �ڴ˴������Ϣ����������
}

//==============================================================
//	              =====�Զ��庯��====
//==============================================================

/*==============================================================
����:	OnShowImg
����:   ��picture����ʾͼ��
����:   M_S-��ʾ����ͼ����һ��ͼ��
--------------------------------------------------------------*/
void C3DSurfaceReDlg::OnShowImg(CImage * Image, bool M_S)
{
	CRect rect;
	if(M_S) // ��ʾ1��ͼ��
	{
		//ѡ����Ҫ��ʾ��ͼ��
		if(!Image->IsNull())	
		{
			this->OnDrawImage(Image, m_DrawBuffer);
		}
		else return;
	}
	else // ��ʾ3��ͼ��
	{
		CImage * imagearray[3];
		for(int i = 0; i < 3; i++)
		{
			imagearray[i] = m_ImageArray[i];
			//	CRect rect;
			//ѡ����Ҫ��ʾ��ͼ��
			if(!imagearray[i]->IsNull())	
			{
				//	int cx = imagearray[i]->GetWidth();
				//	int cy = imagearray[i]->GetHeight();
				CRect rectSrc;
				CWnd *pWnd=GetDlgItem(1004+i);//���pictrue�ؼ����ڵľ��  

				pWnd->GetWindowRect(&rect);
				ScreenToClient(&rect);
				rectSrc = CRect(CPoint(0, 0), CPoint(m_Width, m_Height));
				pWnd->MoveWindow(rect, TRUE);//�������ƶ���Picture�ؼ���ʾ�ľ�������  					
				pWnd->GetClientRect(&rect);//���pictrue�ؼ����ڵľ������� 

				CDC *pDC=pWnd->GetDC();//���pictrue�ؼ���DC  
				imagearray[i]->Draw(pDC->m_hDC, rect, rectSrc); //��ͼƬ����Picture�ؼ���ʾ�ľ������� 

				ReleaseDC(pDC);//�ͷ�picture�ؼ���DC  
			}
		}
	}

	return;
}

/*==============================================================
����:	OnDrawImage
����:   ��ͼƬ��ŵ�ͼ�񻺴�
����:   
--------------------------------------------------------------*/
void C3DSurfaceReDlg::OnDrawImage(CImage *inImage, CImage *image)
{
	byte * inpData = (byte *)inImage->GetBits();
	int inpit = inImage->GetPitch();
	int inbit = inImage->GetBPP()/8;
	byte *pData = (byte *)image->GetBits();
	int pit = image->GetPitch();
	int bit = image->GetBPP()/8;
	int width = inImage->GetWidth(); // ��ʾͼ�������С�̶�Ϊ640-480
	int height = inImage->GetHeight();

	if(inbit == 1)
	{
		for(int cx = 0; cx < width; cx++)
			for(int cy = 0; cy < height; cy++)
			{
				*(pData + cy*pit + cx*bit) = *(inpData + cy*inpit + cx*inbit);
				*(pData + cy*pit + cx*bit+1) = *(inpData + cy*inpit + cx*inbit);
				*(pData + cy*pit + cx*bit+2) = *(inpData + cy*inpit + cx*inbit);
			}
	}
	else
	{
		for(int cx = 0; cx < width; cx++)
			for(int cy = 0; cy < height; cy++)
			{
				*(pData + cy*pit + cx*bit) = *(inpData + cy*inpit + cx*inbit);
				*(pData + cy*pit + cx*bit+1) = *(inpData + cy*inpit + cx*inbit+ 1);
				if(inbit == 2)
					*(pData + cy*pit + cx*bit+2) = *(inpData + cy*inpit + cx*inbit+ 1);
				else
					*(pData + cy*pit + cx*bit+2) = *(inpData + cy*inpit + cx*inbit+ 2);
			}
	}
	this->Invalidate(TRUE);
	pData = NULL;
	inpData = NULL;
}
/*==============================================================
����:	OnLButtonDown
����:   �����������¼�
����:   ���������£�ѡ��һ��������������ʽ��Ѱ�ҽ���
        Ŀ���ǣ������ҽǵ㻨�ѵ�ʱ��
--------------------------------------------------------------*/
void C3DSurfaceReDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	// ����Ժ������һ����Ϣ����ʾ
	if(b_ifcorner)
	{
		startpoint = point;
		CWnd * pWnd = GetDlgItem(IDC_PICTURE);
		CDC * pDC = pWnd->GetDC();
		int cx = 0;
		int cy = 0;
		CRect rect;
		pWnd->GetWindowRect(&rect);
		ScreenToClient(&rect);
		CRect srect;
		pWnd->GetClientRect(&srect);//���pictrue�ؼ����ڵľ������� 

		CPen newpen(PS_DASH, 2, RGB(255, 0, 0));
		pDC->SelectObject(&newpen);
		int newx,newy;
		newy = point.y + srect.top - rect.top;
		newx = point.x + srect.left - rect.left; // ��ȥwindows�������picture��ƫ��
		pDC->MoveTo(newx , newy - 10);
		pDC->LineTo(newx, newy + 10);
		pDC->MoveTo(newx + 10, newy );
		pDC->LineTo(newx - 10, newy );
		cx = startpoint.x * m_Width / rect.Width();
		cy = startpoint.y * m_Height / rect.Height();
	//	m_CornerImg->Save("1.bmp");

		if (b_objectcorner)
		{
			//this->OnFindObjectCorner(m_CornerImg, newx* m_Width / rect.Width(), newy* m_Height / rect.Height());
			this->OnFindPlaneCorner(m_CornerImg, newx* m_Width / rect.Width(), newy* m_Height / rect.Height());
		} 
		else
		{
			this->OnFindPlaneCorner(m_CornerImg, newx* m_Width / rect.Width(), newy* m_Height / rect.Height());
		}
		
		b_ifcorner = false;
		ReleaseDC(pDC);
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}

/*==============================================================
����:	OnFindPlaneCorner
����:   ���Զ��ҽǵ��㷨
����:   Sun et.al �㷨
--------------------------------------------------------------*/
void C3DSurfaceReDlg::OnFindPlaneCorner(CImage * image, int x0, int y0)
{
	int Nmax = 12; // 11-21
	byte * pData,* corpData;
	corpData = (byte*)image->GetBits();
	int corpit = image->GetPitch();
	int corbitCount = image->GetBPP()/8;
	CImage * newImg = new CImage();
	newImg->Create(m_Width, m_Height, 8);
	pData = (byte*)newImg->GetBits();
	int pit = newImg->GetPitch();
	int bitCount = newImg->GetBPP()/8;
	for(int i = 0; i < m_Width; i++)
		for(int j = 0; j < m_Height; j++)
		{
			*(pData + pit*j + bitCount*i) = *(corpData + corpit*j + corbitCount*i);
		}
		byte r;
		referencepoint.x = 0;
		referencepoint.y = 0;
		int num = 0;
		for(int cx = x0 - 40; cx < x0 + 40; cx++) // �������λ�õ�60*60��С���ҵ�
			for(int cy = y0 - 40; cy < y0 + 40; cy++)
			{
				bool b_is = false;
				for(int label = Nmax; label > 0; label--)
				{
					int * bitmap = new int[label*8];
					int m = 0;

					// ����һά������
					for(int i = -label; i <=  label; i++)
					{
						r = *(pData + (cy - label)*pit + (cx + i)*bitCount);
						bitmap[m] = r;
						m++;
					}
					for(int i = - label + 1; i < label; i++)
					{
						r = *(pData + (cy + i)*pit + (cx + label)*bitCount);
						bitmap[m] = r;
						m++;
					}
					for(int i = label; i >= -label; i--)
					{
						r = *(pData + ( cy + label)*pit + (cx + i)*bitCount);
						bitmap[m] = r;
						m++;
					}
					for(int i = label - 1; i > -label; i--)
					{
						r = *(pData + (cy + i)*pit + (cx - label)*bitCount);
						bitmap[m] = r;
						m++;
					}
					int sum = 0;
					for(int i = 0; i < 8*label; i++)
						sum += bitmap[i];
					sum /= 8*label;
					for(int i = 0; i < 8*label; i++)
						if(bitmap[i] >= sum)
							bitmap[i] = 1;
						else
							bitmap[i] = 0;
					// ��1ά���ݽ��п��ղ��������˳�����
					if(label > 2)
					{
						//	m_my1dmorphology->OneDErosion(bitmap, 8*label);
						m_my1dmorphology->OneDOpening(bitmap, 8*label);
						m_my1dmorphology->OneDClosing(bitmap, 8*label);
					}
					int dif = 0;
					for(int i = 0; i < 8*label - 1; i++)
						dif += abs(bitmap[i+1] - bitmap[i]);
					dif += abs(bitmap[0] - bitmap[8*label - 1]);
					if(dif !=4)
					{
						b_is = true;
						delete bitmap;
						break;
					}
					delete bitmap;
				}
				if(!b_is) // ������>0.6��Ϊ�ж�����������������ĳ����֣�100%ʱ�򣬻��ж���㣬��ȡ100%
				{
					//newimage->SetPixelRGB(cx, cy ,255, 255, 255);
					referencepoint.x += cx;
					referencepoint.y += cy;
					num++;
				}
			}

			referencepoint.x /= num;
			referencepoint.y /= num;
			delete newImg; newImg = NULL;
			//image->SetColorTable(0, 256, colorTable); // ����Ϊ8λ������ͼ
			if(corbitCount == 1)
			{
				for(int cx = 0; cx < m_Width; cx++)
					for(int cy = 0; cy < m_Height; cy++)
						if(((cx-referencepoint.x)*(cx-referencepoint.x) + (cy-referencepoint.y)*(cy-referencepoint.y)) <= 12)
							*(corpData + cy*corpit + cx*corbitCount)  = 255;
				*(corpData + referencepoint.y*corpit + referencepoint.x*corbitCount) = 0;
			}
			if(corbitCount == 3)
			{
				for(int i = referencepoint.x-6; i < referencepoint.x+6; i++)
				{
					*(corpData + referencepoint.y*corpit + i*corbitCount)  = 0;
					*(corpData + referencepoint.y*corpit + i*corbitCount+1)  = 0;
					*(corpData + referencepoint.y*corpit + i*corbitCount+2)  = 255;
				}
				for(int j = referencepoint.y-6; j < referencepoint.y+6; j++)
				{
					*(corpData + j*corpit + referencepoint.x*corbitCount)  = 0;
					*(corpData + j*corpit + referencepoint.x*corbitCount+1)  = 0;
					*(corpData + j*corpit + referencepoint.x*corbitCount+2)  = 255;
				}
			}

			OnShowImg(image, TRUE);
			// ����labelmap
			labelmap = new int[m_Width*m_Height];
			for(int i = 0 ; i < m_Width*m_Height; i++)
				labelmap[i] = 1;
//			fout << "plane corner:" << referencepoint.x << "  "<< referencepoint.y << endl;
}

/*==============================================================
����:	OnFindObjectCorner
����:   �ֶ��ҽǵ��㷨
����:   
--------------------------------------------------------------*/
void C3DSurfaceReDlg::OnFindObjectCorner(CImage * image, int x0, int y0)
{
	int corbitCount = image->GetBPP()/8;
	byte * corpData = (byte*)image->GetBits();
	int corpit = image->GetPitch();
	referencepoint.x = x0;
	referencepoint.y = y0;
	if(corbitCount == 1)
	{
		for(int cx = 0; cx < m_Width; cx++)
			for(int cy = 0; cy < m_Height; cy++)
				if(((cx-referencepoint.x)*(cx-referencepoint.x) + (cy-referencepoint.y)*(cy-referencepoint.y)) <= 12)
					*(corpData + cy*corpit + cx*corbitCount)  = 255;
		*(corpData + referencepoint.y*corpit + referencepoint.x*corbitCount) = 0;
	}
	if(corbitCount == 3)
	{
		for(int i = referencepoint.x-6; i < referencepoint.x+6; i++)
		{
			*(corpData + referencepoint.y*corpit + i*corbitCount)  = 0;
			*(corpData + referencepoint.y*corpit + i*corbitCount+1)  = 0;
			*(corpData + referencepoint.y*corpit + i*corbitCount+2)  = 255;
		}
		for(int j = referencepoint.y-6; j < referencepoint.y+6; j++)
		{
			*(corpData + j*corpit + referencepoint.x*corbitCount)  = 0;
			*(corpData + j*corpit + referencepoint.x*corbitCount+1)  = 0;
			*(corpData + j*corpit + referencepoint.x*corbitCount+2)  = 255;
		}
	}
//	fout << "object corner:" << referencepoint.x << "  "<< referencepoint.y << endl;
}
