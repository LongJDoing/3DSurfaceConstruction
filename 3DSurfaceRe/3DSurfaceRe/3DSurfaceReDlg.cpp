
// 3DSurfaceReDlg.cpp : 实现文件
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

bool b_3DConstruction = false; // 判断是否进行3D重建

ofstream fout(".\\result.txt", ios::out|ios::in|ios::ate);
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// 3DSurfaceReDlg 对话框




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
	//设置三缓存区
	m_DrawBuffer = new CImage();
	m_DrawBuffer->Create(640,480,24);
	

	// 清空绘图板
	CDC *MemDC = CDC::FromHandle(m_DrawBuffer->GetDC());
	MemDC->FillSolidRect(0, 0, 640, 480, RGB(62, 70, 55)); // 这里是为这个矩形填充颜色

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

// 自定义析构函数
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

	// 消息传递
	END_MESSAGE_MAP()


// 3DSurfaceReDlg 消息处理程序

BOOL C3DSurfaceReDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	 //添加选项卡
	m_tabMain.InsertItem(0,_T("Camera Controls"));
    m_tabMain.InsertItem(1,_T("Projector Calibration"));//“ ”可更改，是sheet页的名字；
	m_tabMain.InsertItem(2,_T("3D Reconstruction"));

	 //关联对话框,并且将IDC_TABMAIN控件设为父窗口
	m_para3->Create(IDD_DIALOG3, GetDlgItem(IDC_TABMAIN));
	m_para1->Create(IDD_DIALOG1, GetDlgItem(IDC_TABMAIN));
	m_para2->Create(IDD_DIALOG2, GetDlgItem(IDC_TABMAIN));
	
	 //获得IDC_tabMain客户区大小
	CRect rs;
	m_tabMain.GetClientRect(&rs);
	 //调整子对话框在父窗口中的位置，可以改动数值，使子窗体的大小合适；
	rs.top += 20;
	rs.bottom -= 5;
	rs.left += 5;
	rs.right -= 5;
	 //设置子对话框尺寸并移动到指定位置
	m_para1->MoveWindow(&rs);
	m_para2->MoveWindow(&rs);
	m_para3->MoveWindow(&rs);
	 //分别设置隐藏和显示
	m_para3->ShowWindow(true);
	m_para1->ShowWindow(false);
	m_para2->ShowWindow(false);
	//设置默认的选项卡
	m_tabMain.SetCurSel(0);

	m_para1->GetDlgItem(IDC_IMPORTSTRIPES)->EnableWindow(FALSE);
	m_para1->GetDlgItem(IDC_CALCULATERPM)->EnableWindow(FALSE);
	m_para1->GetDlgItem(IDC_CALCULATEAPM)->EnableWindow(FALSE);
	m_para1->GetDlgItem(IDC_EXTRACTSAMPT)->EnableWindow(FALSE);
	m_para1->GetDlgItem(IDC_CALCULATECORRESPT)->EnableWindow(FALSE);
	m_para1->GetDlgItem(IDC_COMPUTEPROJECTORCENTER)->EnableWindow(FALSE);
	m_para1->GetDlgItem(IDC_CALCULATECORNER)->EnableWindow(TRUE);
	m_para1->GetDlgItem(IDC_INPUTPA)->EnableWindow(TRUE);
	// 设置tab-control 的combobox控件
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

	// 设置 dialog2
	m_para2->GetDlgItem(IDC_IMPORTSTRIPES)->EnableWindow(FALSE);
	m_para2->GetDlgItem(IDC_CALCULATERPM)->EnableWindow(FALSE);
	m_para2->GetDlgItem(IDC_CALCULATEAPM)->EnableWindow(FALSE);
	m_para2->GetDlgItem(IDC_FINDPROJECTIONCORPT)->EnableWindow(FALSE);
	m_para2->GetDlgItem(IDC_3DRECONSTRUCTION)->EnableWindow(FALSE);
	m_para2->GetDlgItem(IDC_CALCULATECORNER)->EnableWindow(TRUE);
	// 设置tab-control 的combobox控件

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

	// 控制大小的窗口
	m_Resize.SetOwner(this);
	
	m_Resize.SetResize(IDC_PICTURESTATIC,PK_TOP_LEFT,PK_BOTTOM_RIGHT); 
	m_Resize.SetResize(IDC_PICTURE,PK_TOP_LEFT,PK_BOTTOM_RIGHT); 
	m_Resize.SetResize(IDC_PICTURE2,PK_TOP_LEFT,PK_BOTTOM_MOVE); 
	m_Resize.SetResize(IDC_PICTURE3,PK_TOP_MOVE2,PK_BOTTOM_MOVE1); 
	m_Resize.SetResize(IDC_PICTURE4,PK_TOP_MOVE1,PK_BOTTOM_MOVE2); 
	m_Resize.SetResize(IDC_TABMAIN,PK_TOP_RIGHT,PK_BOTTOM_RIGHT); 

//	 m_Resize.SetResize(IDC_TABMAIN,PK_TOP_LEFT,PK_TOP_LEFT); 
  	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void C3DSurfaceReDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		CDC *MemDC = CDC::FromHandle(m_DrawBuffer->GetDC());
		CWnd *pWnd=GetDlgItem(IDC_PICTURE);//获得pictrue控件窗口的句柄  
		CRect rect;
		pWnd->GetClientRect(&rect);
		
		CDC *pDC=pWnd->GetDC();//获得pictrue控件的DC  
		HDC hDC = pDC->GetSafeHdc();
		CRect srcrect(0,0,640,480);
		m_DrawBuffer->StretchBlt(hDC,  rect,srcrect);
		//pDC->BitBlt(0, 0, rect.Width(), rect.Height(),MemDC, 0, 0, SRCCOPY);

	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR C3DSurfaceReDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//==============================================================
//	              =====界面操作====
//==============================================================

/*==============================================================
函数:	OnTcnSelchangeTabmain
功能:   改变tab控件，选择不同的页
参数:   
-------------------------------------------------------------*/
void C3DSurfaceReDlg::OnTcnSelchangeTabmain(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
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
函数:	OnSize
功能:   窗口空间随着窗口大小改变而改变
参数: 
--------------------------------------------------------------*/
void C3DSurfaceReDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	m_Resize.OnSize(cx,cy);
	// TODO: 在此处添加消息处理程序代码
}

//==============================================================
//	              =====自定义函数====
//==============================================================

/*==============================================================
函数:	OnShowImg
功能:   在picture中显示图像
参数:   M_S-显示多张图像还是一张图像
--------------------------------------------------------------*/
void C3DSurfaceReDlg::OnShowImg(CImage * Image, bool M_S)
{
	CRect rect;
	if(M_S) // 显示1幅图像
	{
		//选择需要显示的图像
		if(!Image->IsNull())	
		{
			this->OnDrawImage(Image, m_DrawBuffer);
		}
		else return;
	}
	else // 显示3幅图像
	{
		CImage * imagearray[3];
		for(int i = 0; i < 3; i++)
		{
			imagearray[i] = m_ImageArray[i];
			//	CRect rect;
			//选择需要显示的图像
			if(!imagearray[i]->IsNull())	
			{
				//	int cx = imagearray[i]->GetWidth();
				//	int cy = imagearray[i]->GetHeight();
				CRect rectSrc;
				CWnd *pWnd=GetDlgItem(1004+i);//获得pictrue控件窗口的句柄  

				pWnd->GetWindowRect(&rect);
				ScreenToClient(&rect);
				rectSrc = CRect(CPoint(0, 0), CPoint(m_Width, m_Height));
				pWnd->MoveWindow(rect, TRUE);//将窗口移动到Picture控件表示的矩形区域  					
				pWnd->GetClientRect(&rect);//获得pictrue控件所在的矩形区域 

				CDC *pDC=pWnd->GetDC();//获得pictrue控件的DC  
				imagearray[i]->Draw(pDC->m_hDC, rect, rectSrc); //将图片画到Picture控件表示的矩形区域 

				ReleaseDC(pDC);//释放picture控件的DC  
			}
		}
	}

	return;
}

/*==============================================================
函数:	OnDrawImage
功能:   将图片存放到图像缓存
参数:   
--------------------------------------------------------------*/
void C3DSurfaceReDlg::OnDrawImage(CImage *inImage, CImage *image)
{
	byte * inpData = (byte *)inImage->GetBits();
	int inpit = inImage->GetPitch();
	int inbit = inImage->GetBPP()/8;
	byte *pData = (byte *)image->GetBits();
	int pit = image->GetPitch();
	int bit = image->GetBPP()/8;
	int width = inImage->GetWidth(); // 显示图像区域大小固定为640-480
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
函数:	OnLButtonDown
功能:   鼠标左键按下事件
参数:   鼠标左键按下，选择一定的区域，来交互式的寻找交点
        目的是，减少找角点花费的时间
--------------------------------------------------------------*/
void C3DSurfaceReDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// 最好以后这里加一个消息的提示
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
		pWnd->GetClientRect(&srect);//获得pictrue控件所在的矩形区域 

		CPen newpen(PS_DASH, 2, RGB(255, 0, 0));
		pDC->SelectObject(&newpen);
		int newx,newy;
		newy = point.y + srect.top - rect.top;
		newx = point.x + srect.left - rect.left; // 移去windows的坐标和picture的偏差
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
函数:	OnFindPlaneCorner
功能:   半自动找角点算法
参数:   Sun et.al 算法
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
		for(int cx = x0 - 40; cx < x0 + 40; cx++) // 在鼠标点击位置的60*60大小中找点
			for(int cy = y0 - 40; cy < y0 + 40; cy++)
			{
				bool b_is = false;
				for(int label = Nmax; label > 0; label--)
				{
					int * bitmap = new int[label*8];
					int m = 0;

					// 创建一维的数据
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
					// 对1维数据进行开闭操作，以滤除噪声
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
				if(!b_is) // 本来是>0.6作为判断条件，不过我这里的程序发现，100%时候，还有多个点，故取100%
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
			//image->SetColorTable(0, 256, colorTable); // 若其为8位的索引图
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
			// 定义labelmap
			labelmap = new int[m_Width*m_Height];
			for(int i = 0 ; i < m_Width*m_Height; i++)
				labelmap[i] = 1;
//			fout << "plane corner:" << referencepoint.x << "  "<< referencepoint.y << endl;
}

/*==============================================================
函数:	OnFindObjectCorner
功能:   手动找角点算法
参数:   
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
