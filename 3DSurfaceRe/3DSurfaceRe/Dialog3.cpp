// Dialog3.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "3DSurfaceRe.h"
#include "Dialog3.h"
#include "afxdialogex.h"

BYTE m_FileType;  //index of file type
DI_RESOLUTION m_Resolution;
DI_RESOLUTION m_CaptureResolution;
int m_Height;
int m_Width;
int m_VOff;
int m_HOff;
const UINT WM_USERDEFMSG = ::RegisterWindowMessageA(_T("UserDefMsg"));
// CDialog3 �Ի���
#pragma comment(lib,"DICAMSDK.lib")
IMPLEMENT_DYNAMIC(CDialog3, CDialogEx)

CDialog3::CDialog3(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialog3::IDD, pParent)
{
	m_HOff = 0;
	m_VOff = 0;
	m_Width = 0;	
	m_Height = 0;
	m_FileType = 0;
}

CDialog3::~CDialog3()
{
}

void CDialog3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MULTICAM_LIST, m_MultiCamList);//�󶨿ؼ��Ϳؼ�����
}

BOOL CDialog3::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_HOff = ROI_HOFFSET;
	m_VOff = ROI_VOFFSET;
	m_Width = ROI_WIDTH;
	m_Height = ROI_HEIGHT;
	m_Image_Count = 0;
	m_FileType = FILE_BMP;
	BYTE CamAllNum = 0;
	BYTE Resolution = 0;
	BYTE CapRes = 0;
	CameraGetMultiCameraNumber(&CamAllNum, &Resolution, &CapRes);//Set combobox

	this->GetDlgItem(IDC_SETUP)->EnableWindow(FALSE);
	this->GetDlgItem(IDC_RESOLUTION)->EnableWindow(TRUE);
	this->GetDlgItem(IDC_SAVEFILE)->EnableWindow(TRUE);
	this->GetDlgItem(IDC_SAVEIMG)->EnableWindow(TRUE);

	for(int i=0; i<CamAllNum; i++)
	{
		CString xtmp;
		xtmp.Format("%s #%d", MODEL_NAME,i+1);
		this->m_MultiCamList.AddString(xtmp);
	}
	this->m_MultiCamList.SetCurSel(0);

	m_SetupDlg = NULL;
	m_SetResolutionDlg = NULL;
	m_Resolution = (DI_RESOLUTION)Resolution;
	m_CaptureResolution = (DI_RESOLUTION)CapRes;
	m_pDlg = (C3DSurfaceReDlg *)GetParent()->GetParent();
	
	return TRUE;
}

BEGIN_MESSAGE_MAP(CDialog3, CDialogEx)
	ON_BN_CLICKED(IDC_PLAY, &CDialog3::OnBnClickedPlay)
	ON_BN_CLICKED(IDC_SAVEFILE, &CDialog3::OnBnClickedSavefile)
	ON_BN_CLICKED(IDC_SAVEIMG, &CDialog3::OnBnClickedSaveimg)
	ON_BN_CLICKED(IDC_SETUP, &CDialog3::OnBnClickedSetup)
	ON_BN_CLICKED(IDC_RESOLUTION, &CDialog3::OnBnClickedResolution)
	ON_BN_CLICKED(IDC_EXIT, &CDialog3::OnBnClickedExit)
END_MESSAGE_MAP()


// CDialog3 ��Ϣ�������
/*==============================================================
����:	SnapThreadCallback
����:   �����ṩ��SDKʹ�õĺ�������.
����:   *pBuffer ��ǰ֡ͼ������ָ��. 
        Type-- DATA_TYPE_RAW ͼ��ԭʼ�����˽����ݴ�СΪImageWidth*ImageHeight*����BYTE����
		    -- DATA_TYPE_RGB24  RGB24, ���ݴ�СΪImageWidth*ImageHeight*3
		LPVOID lpContext ���������Ĺ�ϵ��
	

����ֵ: 
˵��: �û������ڴ˺����б�д�Լ��ĳ�������ͼ����,���Ƶȵ�

	�������������ͼ���л�һ������.
ע�⣺1��һ֡��ȷͼ���ص�Щ�������Σ�һ��Type = DATA_TYPE_RAW,�ڶ�����DATA_TYPE_RGB24���������Ҫѡ����ȷ�����ݡ�
      2���뾡�����ٴ˺�����ռ��ʱ�䣬������ͼ������CAPY�����BUFFER�ٴ����ô˺������緵�ء�
--------------------------------------------------------------*/
int CALLBACK SnapThreadCallback(BYTE *pBuffer,  DI_DATA_TYPE Type, LPVOID lpContext)
{
	//CDialog3 *pCtrl = (CDialog3 *)lpContext;
	//pCtrl->ImageProcess(pBuffer, Type);
	return TRUE;	
	
#if 0
	/* �ɼ�IO3��׳̬�������IO2 */
	BYTE m_led = 0;
	//  io3 input, io2 output
	CameraSetGpio(0x02); 
	
	CameraReadGpio(&m_led);
	if ( m_led & 0x01 )
	{
		CameraWriteGpio(0x02);
	}
	else
	{
		CameraWriteGpio(0x00);
	}
#endif
	return TRUE;
}

void CDialog3::OnBnClickedPlay()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_RunMode == RUNMODE_PLAY)
	{
		CameraStop(); //fp in dll
		CameraUnInit();
		this->SetDlgItemTextA(IDC_PLAY,"&Play");
		this->GetDlgItem(IDC_PLAY)->SetFocus();
		this->GetDlgItem(IDC_SAVEFILE)->EnableWindow(FALSE);
		this->GetDlgItem(IDC_SETUP)->EnableWindow(FALSE);
		this->GetDlgItem(IDC_RESOLUTION)->EnableWindow(FALSE);
		this->GetDlgItem(IDC_SAVEIMG)->EnableWindow(FALSE);
		m_RunMode =RUNMODE_STOP;
		return ;
	}
	else
	{
		BYTE CamNum = this->m_MultiCamList.GetCurSel();//ȡ����Ͽ�ǰѡ������±�
		if(this->m_MultiCamList.GetCount() == 0)
		{
			CamNum = 0;
		}
		if(R_ROI == m_Resolution)
		{
			CameraSetROI(m_HOff, m_VOff, m_Width, m_Height); //fp in dll ,to set the resolution
		}
		if(STATUS_OK != CameraInit(SnapThreadCallback, 
			                       m_Resolution,
								   m_pDlg->GetDlgItem(IDC_PICTURE)->m_hWnd, //NULL
								   CamNum+1,
								   m_pDlg))
		 { 
			 MessageBox("Init Camera failed","Error",MB_OK|MB_ICONSTOP);
			 return ;
		}

#ifdef ENABLE_READ_SN_DEBUG
		char SN[32];
		CameraReadSN(SN, 32);
		CString sSN;
		sSN = SN;
		
		CString sUserSN = "WWW.D-IMAGE.NET 0755-61860636";
		if (sSN == sUserSN)
		{
		//	MessageBox(x, "SN is OK!", MB_OK | MB_ICONSTOP);
		}
		else //��鲻�ԣ���дһ�Σ�д֮ǰ��ȷ��EEPROM���ڿ�д״̬��
		{
			char* pAddr = sUserSN.GetBuffer(32);
			
			CameraWriteSN(pAddr, 32);

			char cNewSn[32];
			CameraReadSN(cNewSn, 32);
			CString sNewSN = cNewSn;

			if (sNewSN == sUserSN )
			{		
				MessageBox("SN Rewrite Ok!", "SN Error", MB_OK | MB_ICONSTOP);
			}
			else
			{
				MessageBox("SN Rewrite Error!", "SN Error", MB_OK | MB_ICONSTOP);
			}
			CameraUnInit();
			return;
		}
#endif
		// Set AWB Window
		{
			INT width = 0;
			INT hight = 0;
			CameraGetImageSize(&width, &hight);
			CameraSetWBWindow(width>>2, hight>>2, width>>1, hight>>1);
		}
		this->SetDlgItemText(IDC_PLAY, "Sto&p");
		this->GetDlgItem(IDC_SAVEFILE)->EnableWindow(TRUE);
		this->GetDlgItem(IDC_SETUP)->EnableWindow(TRUE);
		this->GetDlgItem(IDC_RESOLUTION)->EnableWindow(TRUE);
		this->GetDlgItem(IDC_SAVEIMG)->EnableWindow(TRUE);
		
		/*WM_USERDEFMSG �û��Զ�����Ϣ��ͨ��CameraSetMessage()�����õ����
		Message ID����Message ID����Wparam��Lparam��Ϣ�������Ǵ��ݵ���Ϣ
		��Ӧ����OnVideoMsg()���н����жϺʹ���*/
		CameraSetMessage(this->m_hWnd, WM_USERDEFMSG);
		CameraPlay();
		m_iVideoCnt = 0;
		m_iErrorFrames = 0;
		m_RunMode = RUNMODE_PLAY;
		return;
	}
}

/*==============================================================
Name:	OnSavefile
Desc:   save the file 
Param:	
Return: 
Note: set the save file name and path...
	//the default here is exe file path...   
	�������ѡ��洢ĳһʱ���ͼƬ��ͼƬ��ʽͨ��setupѡ��
  --------------------------------------------------------------*/
void CDialog3::OnBnClickedSavefile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTime time = CTime::GetCurrentTime();
	CString sPath;
	GetModuleFileName(NULL,sPath.GetBuffer(256),256);
	sPath.ReleaseBuffer(256);
	//	MessageBox(sPath);
	int nPos = sPath.ReverseFind('\\');
	sPath = sPath.Left(nPos + 1);
	sPath = ".\\image\\";
	CString sfilename;
	sfilename.Format("%sP%02d%02d%02d%02d%02d", sPath, time.GetMonth(),
		time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());

#if 0
	int Width = 3664;
	int Height= 2748;
	{
		int nImageSize = Width*Height;
		BYTE* BmpBuffer   = (BYTE *) malloc(nImageSize * 3 + 512); //����Ŀռ�����㹻�����������Ҫץͼ��ʵ�ʴ�С���á�

		if (BmpBuffer != NULL)
		{	
			CameraCaptureToBuf(BmpBuffer, DATA_TYPE_RGB24, R3664_2748);//R640_480	

			SaveBmpFile(sfilename+".bmp", BmpBuffer, Width, Height);
		}
		free(BmpBuffer);
		BmpBuffer = NULL;
	}
	//	CameraEnableDeadPixelCorrection();
	//	CameraSetDisplayWindow(160,120,320,240);
#else
	if (R_ROI == m_CaptureResolution)
	{
		CameraSetROI(m_HOff, m_VOff, m_Width, m_Height);
	}//
	CameraCaptureFile(sfilename, m_FileType, 90, m_CaptureResolution);
	MessageBox(sfilename);
#endif
	return ;
}

/*==============================================================
Name:	OnSaveImage
Desc:   save the image 
Param:	
Return: 
Note: save the image for calibration
	//the default here is exe file path...   
	�������ѡ��洢ĳһʱ���ͼƬ��ͼƬ��ʽͨ��setupѡ��
  --------------------------------------------------------------*/
void CDialog3::OnBnClickedSaveimg()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_Image_Count++;
	CString sPath;
	sPath = ".\\image\\";
	CString sTemp;
	sTemp.Format("Q%d", m_Image_Count);
	this->SetDlgItemTextA(IDC_SAVEIMG,sTemp);

	CTime time = CTime::GetCurrentTime();
	//
	CString sfilename;
	sfilename = sPath + sTemp;

#if 0
	int Width = 3664;
	int Height= 2748;
	{
		int nImageSize = Width*Height;
		BYTE* BmpBuffer   = (BYTE *) malloc(nImageSize * 3 + 512); //����Ŀռ�����㹻�����������Ҫץͼ��ʵ�ʴ�С���á�

		if (BmpBuffer != NULL)
		{	
			CameraCaptureToBuf(BmpBuffer, DATA_TYPE_RGB24, R3664_2748);//R640_480	

			SaveBmpFile(sfilename+".bmp", BmpBuffer, Width, Height);
		}
		free(BmpBuffer);
		BmpBuffer = NULL;
	}
	//	CameraEnableDeadPixelCorrection();
	//	CameraSetDisplayWindow(160,120,320,240);
#else
	if (R_ROI == m_CaptureResolution)
	{
		CameraSetROI(m_HOff, m_VOff, m_Width, m_Height);
	}//
	CameraCaptureFile(sfilename, m_FileType, 100, m_CaptureResolution);
	//MessageBox(sfilename);
#endif
	if(m_Image_Count >= 7)
	{
		this->SetDlgItemTextA(IDC_SAVEIMG,"&Save");
		this->GetDlgItem(IDC_CALIBRATECAMERA)->EnableWindow(TRUE);
	}
	return;
}

/*==============================================================
Name:	OnSetup
Desc:   Open the Setup  Panel dialog
Param:	
Return: 
Note: 
  --------------------------------------------------------------*/
void CDialog3::OnBnClickedSetup()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_SetupDlg != NULL)
	{
		delete m_SetupDlg;
		m_SetupDlg = NULL;
		return  ;
	}
	m_SetupDlg = new CSetup(this);

	m_SetupDlg->m_FTypeIndex = m_FileType; // the picture type index
	m_SetupDlg->Create(IDD_SETUP_DIALOG, this);
	m_SetupDlg->ShowWindow(SW_SHOW);
	return;
}


void CDialog3::OnBnClickedResolution()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_SetResolutionDlg != NULL)
	{
		delete m_SetResolutionDlg;
		m_SetResolutionDlg = NULL;
		return  ;
	}

	m_SetResolutionDlg = new CSetResolution(this);
	m_SetResolutionDlg->m_RSLTIndex = m_Resolution;
	m_SetResolutionDlg->m_HOff1 = m_HOff;
	m_SetResolutionDlg->m_VOff1 = m_VOff;
	m_SetResolutionDlg->m_Width1 = m_Width;
	m_SetResolutionDlg->m_Height1 = m_Height;

	m_SetResolutionDlg->m_CaptureIndex = m_CaptureResolution;
	m_SetResolutionDlg->Create(IDD_RESOLUTION_DIALOG, this);
	m_SetResolutionDlg->ShowWindow(SW_SHOW);
	UpdateData(FALSE);
}


void CDialog3::OnBnClickedExit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CameraStop(); //fp in dll
	CameraUnInit();
	this->SetDlgItemTextA(IDC_PLAY,"&Play");
	this->GetDlgItem(IDC_PLAY)->SetFocus();
	this->GetDlgItem(IDC_SAVEFILE)->EnableWindow(FALSE);
	this->GetDlgItem(IDC_SETUP)->EnableWindow(FALSE);
	this->GetDlgItem(IDC_RESOLUTION)->EnableWindow(FALSE);
	this->GetDlgItem(IDC_SAVEIMG)->EnableWindow(FALSE);
	m_RunMode =RUNMODE_STOP;
	return;

}
