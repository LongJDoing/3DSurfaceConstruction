// Dialog2.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "3DSurfaceRe.h"
#include "Dialog2.h"
#include "afxdialogex.h"
#include <iostream>
#include <fstream>
using namespace std;

// CDialog2 �Ի���

IMPLEMENT_DYNAMIC(CDialog2, CDialogEx)

CDialog2::CDialog2(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialog2::IDD, pParent)
{
	m_inputdlg = NULL;
	m_pDlg = NULL;

	m_myphase = new CMyPhase();
	m_myimageopreate = new CImageOperate();
	m_pConnectComponentLabel = new CConnectComponentLabel;
	m_mygeometry = new CMyGeometry();

}

CDialog2::~CDialog2()
{
}

void CDialog2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHOBJECTLIST, m_ChObjectList);
	DDX_Control(pDX, IDC_CHDRLIST, m_ChDirectionList);
}


BEGIN_MESSAGE_MAP(CDialog2, CDialogEx)
	ON_BN_CLICKED(IDC_CALCULATECORNER, &CDialog2::OnBnClickedCalculatecorner)
	ON_BN_CLICKED(IDC_IMPORTSTRIPES, &CDialog2::OnBnClickedImportstripes)
	ON_BN_CLICKED(IDC_CALCULATERPM, &CDialog2::OnBnClickedCalculaterpm)
	ON_BN_CLICKED(IDC_CALCULATEAPM, &CDialog2::OnBnClickedCalculateapm)
	ON_CBN_SELCHANGE(IDC_CHOBJECTLIST, &CDialog2::OnCbnSelchangeChobjectlist)
	ON_CBN_SELCHANGE(IDC_CHDRLIST, &CDialog2::OnCbnSelchangeChdrlist)
	ON_BN_CLICKED(IDC_BLACKSCREEN, &CDialog2::OnBnClickedBlackscreen)
	ON_BN_CLICKED(IDC_FINDPROJECTIONCORPT, &CDialog2::OnBnClickedFindprojectioncorpt)
	ON_BN_CLICKED(IDC_3DRECONSTRUCTION, &CDialog2::OnBnClicked3dreconstruction)
	ON_BN_CLICKED(IDC_SHOWPHASEMAP, &CDialog2::OnBnClickedShowphasemap)
	ON_BN_CLICKED(IDC_SHOWABSOLUTEMAP, &CDialog2::OnBnClickedShowabsolutemap)
	ON_BN_CLICKED(IDC_SHOWGRAYMAP, &CDialog2::OnBnClickedShowgraymap)
END_MESSAGE_MAP()

BOOL CDialog2::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_pDlg = (C3DSurfaceReDlg *)GetParent()->GetParent();
	return TRUE;
}
// CDialog2 ��Ϣ�������


void CDialog2::OnBnClickedCalculatecorner()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_pDlg->m_CornerImg = this->InputOneImg();
	this->GetDlgItem(IDC_IMPORTSTRIPES)->EnableWindow(TRUE);
	this->GetDlgItem(IDC_CALCULATECORNER)->EnableWindow(FALSE);
	m_pDlg->b_objectcorner = true;
	m_pDlg->b_ifcorner = true;
	m_pDlg->OnShowImg(m_pDlg->m_CornerImg, TRUE);

}

CImage * CDialog2::InputOneImg()
{
	CImage * image;
	image = new CImage();

	CString strFilter;
	CSimpleArray<GUID>aguidFileTypes;
	HRESULT hResult;
	hResult = image->GetExporterFilterString(strFilter,aguidFileTypes,_T("All image Files"));

	strFilter =_T("BMP (*.bmp)|*.bmp|JPEG (*.jpg)|*.jpg|GIF (*.gif)|*.gif|PNG (*.png)|*.png||");
	if(FAILED(hResult))
	{
		MessageBox(_T("Failed��"));
		return NULL;
	}

	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, strFilter);//��ѡģʽ
	if(dlg.DoModal()!=IDOK)     //�ж��Ƿ���ͼƬ
	{ 
		return NULL;
	}
	CString m_path = dlg.GetPathName();
	if(m_path=="")   //�ж�ͼƬ·���Ƿ����
	{
		return NULL;
	}

	hResult = image->Load(m_path);   //���ⲿͼ���ļ�װ�ص�CImage������
	if(FAILED(hResult))
	{
		MessageBox(_T("Failed"));
		return NULL;
	}
	m_pDlg->m_Width = image->GetWidth();
	m_pDlg->m_Height = image->GetHeight();
	return image;
}

void CDialog2::OnBnClickedImportstripes()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_pDlg->m_ImageArray = this->InputMulImg();
	this->GetDlgItem(IDC_IMPORTSTRIPES)->EnableWindow(FALSE);
	this->GetDlgItem(IDC_CALCULATERPM)->EnableWindow(TRUE);
	m_pDlg->OnShowImg(NULL,false);
}

vector<CImage *> CDialog2::InputMulImg()
{
	vector<CImage *> imagearray;
	CString strFilter;
	CSimpleArray<GUID>aguidFileTypes;
	HRESULT hResult;
	CImage * m_pInImage =  new CImage();
	hResult = m_pInImage->GetExporterFilterString(strFilter,aguidFileTypes,_T("All image Files"));

	strFilter =_T("BMP (*.bmp)|*.bmp|JPEG (*.jpg)|*.jpg|GIF (*.gif)|*.gif|PNG (*.png)|*.png||");
	if(FAILED(hResult))
	{
		MessageBox(_T("Failed��"));
		//		return ;
	}
	delete m_pInImage;
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT| OFN_ALLOWMULTISELECT, strFilter);//��ѡģʽ
	if(dlg.DoModal()!=IDOK)     //�ж��Ƿ���ͼƬ
	{ 
		//		return ;
	}
	POSITION pos = dlg.GetStartPosition();

	if(!imagearray.empty())
		imagearray.clear();

	while(pos)
	{
		CString szFileName = dlg.GetNextPathName(pos);
		//int len = szFileName.ReverseFind('\\');//�����ʼ���һ��з����õ����з�ǰ����ַ�����
		CString filename;
		filename = szFileName;
		//filename = szFileName.Mid(len+1); //�ӿ�ʼ�����len+1���ַ��ĺ�����ַ�
		//	m_pInImage->Destroy();

		CImage *img = new CImage();
		hResult = img->Load(filename);   //���ⲿͼ���ļ�װ�ص�CImage������
		if(FAILED(hResult))
		{
			MessageBox(_T("Failed"));
			//			return ;
		}
		imagearray.push_back(img);
		//	delete img; // ����delete
	}
	return imagearray;
}

void CDialog2::OnBnClickedCalculaterpm()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_pDlg->objectphasemap = this->GetphaseMap();
	CImage * image1;
	image1 = this->DrawImage(m_pDlg->objectphasemap, true);
	m_pDlg->OnShowImg(image1, TRUE);
	CString tmp;
	tmp.Format("%d", img_num);
	tmp = ".\\reference-plane\\" + tmp + ".bmp";
	image1->Save(tmp);
	delete image1;image1 = NULL;
	img_num++;
	this->GetDlgItem(IDC_CALCULATEAPM)->EnableWindow(TRUE);
	this->GetDlgItem(IDC_CALCULATERPM)->EnableWindow(FALSE);
	return ;
}

double * CDialog2::GetphaseMap()
{
	double * phasemap ;
	CImage * imagearray[3];
	for(int i = 0; i < 3; i++)
		imagearray[i] = m_pDlg->m_ImageArray[i];
	phasemap = m_myphase->CreatePhaseMap(imagearray, m_pDlg->m_Width, m_pDlg->m_Height);
	return phasemap;
}

CImage * CDialog2::DrawImage(double * values, bool bID)
{
	CImage * image = new CImage();
	image->Create(m_pDlg->m_Width, m_pDlg->m_Height, 8); 
	byte * pData;
	pData = (byte*)image->GetBits();
	int pit = image->GetPitch();
	int bitCount = image->GetBPP()/8;

	if(bID) // ���������λͼ
	{
		for(int cx = 0; cx < m_pDlg->m_Width; cx++)
			for(int cy = 0; cy < m_pDlg->m_Height; cy++)
			{
				int temp = 255*(values[cx + cy*m_pDlg->m_Width] + PI) / (2*PI);
				*(pData + pit*cy + cx*bitCount) = temp;
			}
	}
	else // ���ƾ�����λͼ
	{
		double max , min;
		max = min = values[0];

		for(int i = 0; i < m_pDlg->m_Width * m_pDlg->m_Height; i++)
		{
			if((m_pDlg->objectlabelmap[i] != 0)&&(values[i] != -10000))
			{
				max = (max < values[i]) ? values[i] : max;
				min = (min > values[i]) ? values[i] : min;
			}
		}
		int temp = 0;
		for(int i = 0; i < m_pDlg->m_Width * m_pDlg->m_Height; i++)
		{

			temp = 255*(values[i] - min) / (max - min);
			if((m_pDlg->objectlabelmap[i] != 0)&&(values[i] != -10000))
				*(pData + pit*(i/m_pDlg->m_Width) + bitCount*(i%m_pDlg->m_Width)) = temp;
			else
				*(pData + pit*(i/m_pDlg->m_Width) + bitCount*(i%m_pDlg->m_Width)) = 255;
		}
	}
	image->SetColorTable(0, 256, colorTable);
	return image;
}

void CDialog2::OnBnClickedCalculateapm()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int m_Width = m_pDlg->m_Width;
	int m_Height = m_pDlg->m_Height;
	m_pDlg->objectlabelmap = new int[m_Width*m_Height];
	for(int i = 0; i < m_Width*m_Height; i++)
		m_pDlg->objectlabelmap[i] = 0;

	CString tmp;
	int m_seldirection = this->m_ChDirectionList.GetCurSel(); // ѡ��ķ���
	int m_selobject = this->m_ChObjectList.GetCurSel(); // ѡ������
	
	if(m_seldirection == 0)
	{
		m_pDlg->objectabsolutephasemap = this->GetAbsolutePhaseMap(m_pDlg->objectphasemap, FALSE);
		tmp.Format(".\\reference-plane\\%d-object-h-absolute-phase.bmp", m_selobject);
	//	this->m_ChDirectionList.SetCurSel(1);
		this->OnCbnSelchangeChobjectlist();
	}
	else
	{
		m_pDlg->objectabsolutephasemap = this->GetAbsolutePhaseMap(m_pDlg->objectphasemap, TRUE);
		tmp.Format(".\\reference-plane\\%d-object-v-absolute-phase.bmp", m_selobject);
		//this->m_ChDirectionList.SetCurSel(0);
		this->OnCbnSelchangeChobjectlist();
	}
	delete m_pDlg->objectphasemap;
	//MessageBox("")
	CImage * image1;
	image1 = this->DrawImage(m_pDlg->objectabsolutephasemap, false);
	m_pDlg->OnShowImg(image1, TRUE);
	delete image1; image1 = NULL;

	this->GetDlgItem(IDC_CALCULATEAPM)->EnableWindow(FALSE);
	this->GetDlgItem(IDC_FINDPROJECTIONCORPT)->EnableWindow(TRUE);
	return;
}


void CDialog2::OnCbnSelchangeChobjectlist()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->GetDlgItem(IDC_CALCULATECORNER)->EnableWindow(TRUE);
}


void CDialog2::OnCbnSelchangeChdrlist()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->GetDlgItem(IDC_IMPORTSTRIPES)->EnableWindow(TRUE);
}

double * CDialog2::GetAbsolutePhaseMap(double * phasemap, bool direction)
{
	CImage * imagearray[3];
	for(int i = 0; i < 3; i++)
		imagearray[i] = m_pDlg->m_ImageArray[i];
	CImage * qualitymap1;
	qualitymap1 = m_myphase->CreateQualityMap1(imagearray, m_pDlg->m_Width, m_pDlg->m_Height,false);
	CButton * b_blackscreen = (CButton *)this->GetDlgItem(IDC_BLACKSCREEN);// �����ж��Ƿ�ѡ��
	if(b_blackscreen->GetCheck())
	{
		this->BlackScreen(m_pDlg->m_CornerImg, qualitymap1);
	}
	// ���������һ���ֲ�����ͨ����Ϊ�޸�����ͼ1�������Ƿ��ܹ���߾���
if (0)
	{
		delete qualitymap1; 
		qualitymap1 = NULL;
		qualitymap1 = new CImage();
		qualitymap1->Load(".\\reference-plane\\objectqualitymap1.bmp");
	}
else
	qualitymap1->SetColorTable(0, 256, colorTable);
	qualitymap1->Save(".\\reference-plane\\qualitymap1.bmp");


	
	double ** dqualitymap2;
	dqualitymap2 = m_myphase->CreateQualityMap2(phasemap, m_pDlg->m_Width, m_pDlg->m_Height );
	int * stratifyqualitylabelmap = m_myphase->StratifyQualityMap(qualitymap1, dqualitymap2, m_pDlg->m_Width, m_pDlg->m_Height);

	for (int i = 0; i < m_pDlg->m_Width*m_pDlg->m_Height; i++)
	{
		int x = i % m_pDlg->m_Width;
		int y = i / m_pDlg->m_Width;
		if(stratifyqualitylabelmap[i] == 0)
		{
			m_pDlg->objectlabelmap[i] = 0;
		}
		else
		{
			m_pDlg->objectlabelmap[i] = 1;
		}
	}
	double * absolutephasemap;

	absolutephasemap = m_myphase->UnwrapPhaseMap(phasemap, stratifyqualitylabelmap, m_pDlg->m_Width, m_pDlg->m_Height, 
		direction, m_pDlg->referencepoint); // ����������е��ú���������startpoint
	ofstream tfout(".\\test-result.txt", ios::out|ios::in|ios::ate);
	tfout << "object data..."<< endl;
	for(int i = 0; i < m_pDlg->m_Height ; i++)
		tfout << absolutephasemap[365 + i*m_pDlg->m_Width] << endl;

	for(int i = 0 ; i < m_pDlg->m_Width*m_pDlg->m_Height; i++)
		if(stratifyqualitylabelmap[i] == 0)
			absolutephasemap[i] = 0;
	delete qualitymap1, stratifyqualitylabelmap;
	for(int i =0; i < m_pDlg->m_Width; i++)
		delete []dqualitymap2[i];
	delete []dqualitymap2; dqualitymap2 = NULL;
	return absolutephasemap;

}

void CDialog2::BlackScreen(CImage * image1, CImage *image2) // �ҵ���ɫ������
{
	byte * pData1 = (byte*)image1->GetBits();
	int corpit1 = image1->GetPitch();
	int corbitCount1 = image1->GetBPP()/8;

	byte * pData2 = (byte*)image2->GetBits();
	int pit2 = image2->GetPitch();
	int bitCount2 = image2->GetBPP()/8;

	int m_Width = image1->GetWidth();
	int m_Height = image1->GetHeight();
	//�˵���ɫĻ������,ͨ���ǵ�ͼ����otsu�㷨���˳�������
	int * m_hisArr;
	m_hisArr = new int[256];
	for(int i = 0; i < 256; i++)
	{
		m_hisArr[i] = 0;
	}
	m_myimageopreate->calhistogram(image1, m_hisArr);
	int m_otsu = m_myimageopreate->calotsuThreshold(m_hisArr);
	delete m_hisArr; m_hisArr = 0;
	for(int cy = 0; cy < m_Height; cy++)
		for(int cx = 0; cx < m_Width; cx++)
		{
			byte r = *(pData1 + cy*corpit1+ cx*corbitCount1); 
			if(r > m_otsu)
				*(pData1 + cy*corpit1 + cx*corbitCount1) = 0;
			else
				*(pData1 + cy*corpit1 + cx*corbitCount1) = 255;
		}
		unsigned char * bitmap = new unsigned char[m_Width * m_Height];
		byte r;
		int * tplabelmap = new int[m_Width * m_Height];

		for(int cx = 0; cx < m_Width; cx++)
			for(int cy = 0; cy < m_Height; cy++)
			{
				r = *(pData1 + cy*corpit1 + cx*corbitCount1);
				bitmap[cx + cy*m_Width] = r;
				tplabelmap[cx + cy*m_Width] =0;
			}
			int m_labelIndex = m_pConnectComponentLabel->ConnectedComponentLabeling(bitmap, m_Width, m_Height, tplabelmap);
			int max, temp, maxIndex;
			max  = 0;
			maxIndex = 1;
			for(int j = 1; j <= m_labelIndex; j++)
			{
				temp = 0;
				for(int i = 0; i < m_Width * m_Height; i++)
				{
					if(tplabelmap[i] == j)
						temp++;
				}
				if(max < temp)
				{
					max = temp;
					maxIndex = j;
				}	
			}
			for(int i = 0; i < m_Width*m_Height; i++)
				if((tplabelmap[i] == maxIndex)||(*(pData2 + pit2*(i/m_Width) + bitCount2*(i%m_Width))==0))
					*(pData2 + pit2*(i/m_Width) + bitCount2*(i%m_Width)) = 0;
				else
					*(pData2 + pit2*(i/m_Width) + bitCount2*(i%m_Width)) = 255;
			delete bitmap; bitmap = NULL;
			delete tplabelmap; tplabelmap = NULL;

}
bool flag = true;
void CDialog2::OnBnClickedBlackscreen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CButton * b_blackscreen = (CButton *)this->GetDlgItem(IDC_BLACKSCREEN);// �����ж��Ƿ�ѡ��
	
	if(b_blackscreen->GetCheck())
	{
		b_blackscreen->SetCheck(flag);
		flag = !flag;
	}

}

/*==============================================================
����:	OnFindProjectCorrespondence
����:   ��ͶӰ����P������ת���������ƽ�������PI
����: 
--------------------------------------------------------------*/
void CDialog2::OnBnClickedFindprojectioncorpt()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(!m_pDlg->b_calProject)
	{
		m_pDlg->projectioncenterwordcoordinate = new double[3];
		m_pDlg->projectioncenterwordcoordinate[0] = 160.7;
		m_pDlg->projectioncenterwordcoordinate[1] = -104.735;
		m_pDlg->projectioncenterwordcoordinate[2] =  1069.99 ;
	}

	// Step5.1 ... ���P���������
	double * projectioncentercameracoordinate;
	projectioncentercameracoordinate = m_mygeometry->ConvertWordCoordinateToCameraCoordinate(m_pDlg->projectioncenterwordcoordinate);

	double cameracentercameracoordinate[3] = {0.0, 0.0, 0.0};

	m_pDlg->PIcameracoordinate = m_mygeometry->FindIntersectionOfLineAndReferenceplane(cameracentercameracoordinate,projectioncentercameracoordinate, -F);

	delete projectioncentercameracoordinate;
	this->GetDlgItem(IDC_FINDPROJECTIONCORPT)->EnableWindow(FALSE);
	this->GetDlgItem(IDC_3DRECONSTRUCTION)->EnableWindow(TRUE);

	return ;
}

/*==============================================================
����:	OnBnClicked3dreconstruction
����:   3D�ؽ�����Ľṹ����������һ����άָ�뵱��
����: 
--------------------------------------------------------------*/
void CDialog2::OnBnClicked3dreconstruction()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��������ռ䵱�д�������ռ��д�������֣�����ֻд��ռ䣬
	//�����Ҫ�ο������ģ��뿴֮ǰ��MY-Project1.3

    double * PI;
	int m_Width = m_pDlg->m_Width;
	int m_Height  = m_pDlg->m_Height;
	PI = m_mygeometry->ConvertCameraCoordinateToCameraImageCoordinate(m_pDlg->PIcameracoordinate, FALSE);
    double * NI;
	double * MI = new double[2];
	double  objectabsolutephase;
	double * MIwordcoordinate;
	double * NIwordcoordinate;
	double * MR, * NR;
	m_pDlg->objectwordcoordinate = new double*[m_Width*m_Height];
	for(int i = 0; i < m_Width*m_Height; i++)
		m_pDlg->objectwordcoordinate[i] = new double[3];
	for(int i = 0; i < m_Width*m_Height; i++)
		for(int j = 0; j < 3; j++)
			m_pDlg->objectwordcoordinate[i][j] = -10000.0;

	if(m_pDlg->cameracenterwordcoordinate == NULL)
		m_pDlg->cameracenterwordcoordinate = m_mygeometry->GetCameraCenterWordCoordinate();
	int m_ChDrList = this->m_ChDirectionList.GetCurSel(); // ѡ��ķ���
	for (int i = 0; i < m_Width*m_Height; i++)
	{
		if ((m_pDlg->objectlabelmap[i] == 1)&&(m_pDlg->objectabsolutephasemap[i]!=-10000))
		{
			m_pDlg->objectlabelmap[i] = 1;
		}
		else
		{
			m_pDlg->objectlabelmap[i] = 0;
		}
	}
	for(int i = 0; i < m_Width*m_Height; i++)
		if((m_pDlg->objectlabelmap[i] == 1))
		{
			MI[0] = i % m_Width;
			MI[1] = i / m_Width;
			objectabsolutephase = m_pDlg->objectabsolutephasemap[i];
			if(m_ChDrList == 0)
				NI = m_mygeometry->FindNI(m_pDlg->referenceplane_1horizontalabsolutephasemap, objectabsolutephase, 
				m_Width, m_Height, PI, MI, m_ChDrList, m_pDlg->hreferencelabelmap);
			else
				NI = m_mygeometry->FindNI(m_pDlg->referenceplane_1verticalabsolutephasemap, objectabsolutephase, 
				m_Width, m_Height, PI, MI, m_ChDrList, m_pDlg->vreferencelabelmap);
			if(NI[0] == -1)
			{
				continue;
			}
			
			// Step7...��MI��NI�任���ο�ƽ���ϵĵ㣬��MR��NR
			MIwordcoordinate = m_mygeometry->ConvertCameraImageCoordinateToWordCoordinate(MI);
			NIwordcoordinate = m_mygeometry->ConvertCameraImageCoordinateToWordCoordinate(NI);
			delete NI;
			MR = m_mygeometry->FindIntersectionOfLineAndReferenceplane(m_pDlg->cameracenterwordcoordinate, MIwordcoordinate, 0.0);
			NR = m_mygeometry->FindIntersectionOfLineAndReferenceplane(m_pDlg->cameracenterwordcoordinate, NIwordcoordinate, 0.0);
			delete MIwordcoordinate, NIwordcoordinate;
			// Step8... �ҵ�PNR��CMR�Ľ��㣬�����������Ϊ�ռ��
			//temp0 = NR[0] - projectioncenterwordcoordinate[0];
			////temp1 = NR[1] - projectioncenterwordcoordinate[1];
			////temp2 = NR[2] - projectioncenterwordcoordinate[2];
			////
			////a[0][0] = temp1;
			////a[0][1] = -temp0;
			////a[0][2] = 0;
			////b[0] = temp1 * projectioncenterwordcoordinate[0] - temp0*projectioncenterwordcoordinate[1];

			////a[1][0] = 0;
			////a[1][1] = temp2;
			////a[1][2] = -temp1;
			////b[1] = temp2*projectioncenterwordcoordinate[1] - temp1*projectioncenterwordcoordinate[2];

			////temp0 = MR[0] - cameracenterwordcoordinate[0];
			////temp1 = MR[1] - cameracenterwordcoordinate[1];
			////temp2 = MR[2] - cameracenterwordcoordinate[2];
			////delete MR, NR;
			////a[2][0] = temp1;
			////a[2][1] = -temp0;
			////a[2][2] = 0;
			////b[2] = temp1 * cameracenterwordcoordinate[0] - temp0*cameracenterwordcoordinate[1];

			////a[3][0] = 0;
			////a[3][1] = temp2;
			////a[3][2] = -temp1;
			////b[3] = temp2*cameracenterwordcoordinate[1] - temp1*cameracenterwordcoordinate[2];
			////for(int i = 0; i < 2*2*3; i++)
			////	aa[i] = a[i/(3)][i%(3)];
			////objectwordcoordinate[i] = m_myleastsquare->fun(aa, b, 2*2, 3); // ������������ڴ治���Ĵ���
			//// �������д����е�ķ������
			m_pDlg->objectwordcoordinate[i] = m_mygeometry->FindVerticalLineMid_point(m_pDlg->projectioncenterwordcoordinate, m_pDlg->cameracenterwordcoordinate, NR, MR);
			delete MR, NR;
			//double temp = objectwordcoordinate[i][2];
		}
    delete PI;

	//fout1 << "���λ����Ϣ" << endl;
	//for(int cx = 0; cx < m_Width; cx++)
	//{
	//	for(int cy = 0; cy < m_Height; cy++)
	//		if(labelmap[cx + cy*m_Width] == 1)
	//		fout1 << objectwordcoordinate[cx + cy*m_Width][2] << "  ";
	//	fout1 << endl;
	//}
	this->GetDlgItem(IDC_3DRECONSTRUCTION)->EnableWindow(FALSE);
	return;
}

/*==============================================================
����:	OnBnClickedShowphasemap
����:   ��ʾ�������λͼ
����: 
--------------------------------------------------------------*/
void CDialog2::OnBnClickedShowphasemap()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CImage * image = new CImage();
	//	int m_selplane = m_para2.m_ChObjectList.GetCurSel(); // ѡ���ƽ��
	int m_seldirection = this->m_ChDirectionList.GetCurSel(); // ѡ��ķ���
	int m_selobject = this->m_ChObjectList.GetCurSel();
	if(m_seldirection == 0)
	{
		CString stmp;
		stmp.Format(".\\reference-plane\\%d-object-h-phase.bmp", m_selobject);
		image->Load(stmp);
	}
	else
	{
		CString stmp;
		stmp.Format(".\\reference-plane\\%d-object-v-phase.bmp", m_selobject);
		image->Load(stmp);
	}
	m_pDlg->OnDrawImage(image, m_pDlg->m_DrawBuffer);
	delete image;
	return ;
}

/*==============================================================
����:	OnBnClickedShowabsolutemap
����:   ��ʾ����ľ�����λͼ
����: 
--------------------------------------------------------------*/
void CDialog2::OnBnClickedShowabsolutemap()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CImage * image = new CImage();
	//	int m_selplane = m_para2.m_ChObjectList.GetCurSel(); // ѡ���ƽ��
	int m_seldirection = this->m_ChDirectionList.GetCurSel(); // ѡ��ķ���
	int m_selobject = this->m_ChObjectList.GetCurSel();
	if(m_seldirection == 0)
	{
		CString stmp;
		stmp.Format(".\\reference-plane\\%d-object-h-absolute-phase.bmp", m_selobject);
		image->Load(stmp);
	}
	else
	{
		CString stmp;
		stmp.Format(".\\reference-plane\\%d-object-v-absolute-phase.bmp", m_selobject);
		image->Load(stmp);
	}
	m_pDlg->OnDrawImage(image, m_pDlg->m_DrawBuffer);
	delete image;
	return;
}

/*==============================================================
����:	OnBnClickedShowgraymap
����:   ���ݴ洢����ʾ�Ҷ�ͼ
����: 
--------------------------------------------------------------*/
void CDialog2::OnBnClickedShowgraymap()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// �洢���ݵ�λ��
	CFile m_File1, m_File2;
	m_File1.Remove("WordC-result.txt"); //ɾ����һ�δ洢��ͼƬλ��
	m_File1.Open("WordC-result.txt",CFile::modeWrite|CFile::modeCreate);//���´������ļ�
	m_File2.Remove("ImageC-result.txt"); //ɾ����һ�δ洢��ͼƬλ��
	m_File2.Open("ImageC-result.txt",CFile::modeWrite|CFile::modeCreate);//���´������ļ�
	m_File1.Close();
	m_File2.Close();

	int m_Width = m_pDlg->m_Width;
	int m_Height = m_pDlg->m_Height;
	CImage * image = new CImage();
	image->Create(m_Width, m_Height, 24);
	byte *pData = (byte *)image->GetBits();
	int pit = image->GetPitch();
	int bitcount = image->GetBPP()/8;

	for(int cx = 1; cx < m_Width-1; cx++)
		for(int cy = 1; cy < m_Height-1; cy++)
		{
			if(::_isnan(m_pDlg->objectwordcoordinate[cx + cy*m_Width][2])) // �ж�NAN����Χ��NAN����ƽ��
				m_pDlg->objectwordcoordinate[cx + cy*m_Width][2] = -10000.0;
				//((::_isnan(m_pDlg->objectwordcoordinate[cx+1 + (cy)*m_Width][2]) ? 0 : (m_pDlg->objectwordcoordinate[cx+1 + (cy)*m_Width][2])) + 
				//(::_isnan(m_pDlg->objectwordcoordinate[cx-1 + (cy)*m_Width][2]) ? 0 : (m_pDlg->objectwordcoordinate[cx-1 + (cy)*m_Width][2])) +
				//(::_isnan(m_pDlg->objectwordcoordinate[cx + (cy+1)*m_Width][2]) ? 0 : (m_pDlg->objectwordcoordinate[cx + (cy+1)*m_Width][2])) +
				//(::_isnan(m_pDlg->objectwordcoordinate[cx + (cy-1)*m_Width][2]) ? 0 : (m_pDlg->objectwordcoordinate[cx + (cy-1)*m_Width][2])) +
				//(::_isnan(m_pDlg->objectwordcoordinate[cx+1 + (cy-1)*m_Width][2]) ? 0 : (m_pDlg->objectwordcoordinate[cx+1 + (cy-1)*m_Width][2]))+ 
				//(::_isnan(m_pDlg->objectwordcoordinate[cx-1 + (cy-1)*m_Width][2]) ? 0 : (m_pDlg->objectwordcoordinate[cx-1 + (cy-1)*m_Width][2]))+ 
				//(::_isnan(m_pDlg->objectwordcoordinate[cx+1 + (cy+1)*m_Width][2]) ? 0 : (m_pDlg->objectwordcoordinate[cx+1 + (cy+1)*m_Width][2])) +
				//(::_isnan(m_pDlg->objectwordcoordinate[cx-1 + (cy+1)*m_Width][2]) ? 0 : (m_pDlg->objectwordcoordinate[cx-1 + (cy+1)*m_Width][2]))) /8; // ȡ8�����ƽ��

			if(::_isnan(m_pDlg->objectwordcoordinate[cx + cy*m_Width][0])) // �ж�NAN����Χ��NAN����ƽ��
				m_pDlg->objectwordcoordinate[cx + cy*m_Width][0] = 
				((::_isnan(m_pDlg->objectwordcoordinate[cx+1 + (cy)*m_Width][0]) ? 0 : (m_pDlg->objectwordcoordinate[cx+1 + (cy)*m_Width][0])) + 
				(::_isnan(m_pDlg->objectwordcoordinate[cx-1 + (cy)*m_Width][0]) ? 0 : (m_pDlg->objectwordcoordinate[cx-1 + (cy)*m_Width][0])) +
				(::_isnan(m_pDlg->objectwordcoordinate[cx + (cy+1)*m_Width][0]) ? 0 : (m_pDlg->objectwordcoordinate[cx + (cy+1)*m_Width][0])) +
				(::_isnan(m_pDlg->objectwordcoordinate[cx + (cy-1)*m_Width][0]) ? 0 : (m_pDlg->objectwordcoordinate[cx + (cy-1)*m_Width][0])) +
				(::_isnan(m_pDlg->objectwordcoordinate[cx+1 + (cy-1)*m_Width][0]) ? 0 : (m_pDlg->objectwordcoordinate[cx+1 + (cy-1)*m_Width][0]))+ 
				(::_isnan(m_pDlg->objectwordcoordinate[cx-1 + (cy-1)*m_Width][0]) ? 0 : (m_pDlg->objectwordcoordinate[cx-1 + (cy-1)*m_Width][0]))+ 
				(::_isnan(m_pDlg->objectwordcoordinate[cx+1 + (cy+1)*m_Width][0]) ? 0 : (m_pDlg->objectwordcoordinate[cx+1 + (cy+1)*m_Width][0])) +
				(::_isnan(m_pDlg->objectwordcoordinate[cx-1 + (cy+1)*m_Width][0]) ? 0 : (m_pDlg->objectwordcoordinate[cx-1 + (cy+1)*m_Width][0]))) /8; // ȡ8�����ƽ��

			if(::_isnan(m_pDlg->objectwordcoordinate[cx + cy*m_Width][1])) // �ж�NAN����Χ��NAN����ƽ��
				m_pDlg->objectwordcoordinate[cx + cy*m_Width][1] = 
				((::_isnan(m_pDlg->objectwordcoordinate[cx+1 + (cy)*m_Width][1]) ? 0 : (m_pDlg->objectwordcoordinate[cx+1 + (cy)*m_Width][1])) + 
				(::_isnan(m_pDlg->objectwordcoordinate[cx-1 + (cy)*m_Width][1]) ? 0 : (m_pDlg->objectwordcoordinate[cx-1 + (cy)*m_Width][1])) +
				(::_isnan(m_pDlg->objectwordcoordinate[cx + (cy+1)*m_Width][1]) ? 0 : (m_pDlg->objectwordcoordinate[cx + (cy+1)*m_Width][1])) +
				(::_isnan(m_pDlg->objectwordcoordinate[cx + (cy-1)*m_Width][1]) ? 0 : (m_pDlg->objectwordcoordinate[cx + (cy-1)*m_Width][1])) +
				(::_isnan(m_pDlg->objectwordcoordinate[cx+1 + (cy-1)*m_Width][1]) ? 0 : (m_pDlg->objectwordcoordinate[cx+1 + (cy-1)*m_Width][1]))+ 
				(::_isnan(m_pDlg->objectwordcoordinate[cx-1 + (cy-1)*m_Width][1]) ? 0 : (m_pDlg->objectwordcoordinate[cx-1 + (cy-1)*m_Width][1]))+ 
				(::_isnan(m_pDlg->objectwordcoordinate[cx+1 + (cy+1)*m_Width][1]) ? 0 : (m_pDlg->objectwordcoordinate[cx+1 + (cy+1)*m_Width][1])) +
				(::_isnan(m_pDlg->objectwordcoordinate[cx-1 + (cy+1)*m_Width][1]) ? 0 : (m_pDlg->objectwordcoordinate[cx-1 + (cy+1)*m_Width][1]))) /8; // ȡ8�����ƽ��
		}

	// ��������û������˹ƽ�����Ұ�ƽ���������ŵ�MATLAB�н���

	ofstream WCFout(".\\WordC-result.txt", ios::out|ios::in|ios::ate); // ������ʵ����������
	double covcofx = 0.0;
	int Maximagex = 0; int Minimagex = 1000;
	double Maxwordx = 0, Minwordx = 1000;
	for(int i = 0; i < m_Width*m_Height; i++)
	{
		if((m_pDlg->objectlabelmap[i] != 0)&&(abs(m_pDlg->objectwordcoordinate[i][2]+10000.0) > 1000))		/*	for(int cx = 220; cx < 420; cx++)
				for(int cy = 140; cy < 340; cy++)*/
		{
			int * cameraindex = new int[2];
			cameraindex[0] = i % m_Width;
			cameraindex[1]= i / m_Width;
			if(Maximagex < cameraindex[0])
			{
				Maximagex = cameraindex[0];
			}
			if(Minimagex > cameraindex[0])
			{
				Minimagex = cameraindex[0];
			}
			Maxwordx = (Maxwordx < m_pDlg->objectwordcoordinate[i][0]) ? m_pDlg->objectwordcoordinate[i][0] : Maxwordx;
			Minwordx = (Minwordx > m_pDlg->objectwordcoordinate[i][0]) ? m_pDlg->objectwordcoordinate[i][0] : Minwordx;

			WCFout << m_pDlg->objectwordcoordinate[i][0] << " " << m_pDlg->objectwordcoordinate[i][2] << " " << m_pDlg->objectwordcoordinate[i][1] << endl;
			delete cameraindex; cameraindex = 0;
   		}
	}
	covcofx = (Maximagex - Minimagex)/(Maxwordx - Minwordx);
	CString  stmp;
	stmp.Format("%f", 1/covcofx);
	MessageBox(stmp);
//	fout << "Scale factor: "<<covcofx << endl;

	// ���浽��ռ������
	ofstream ICfout(".\\ImageC-result.txt", ios::out|ios::in|ios::ate); // ֱ�ӽ�Z�������һ���任������
	for(int i = 0; i < m_Width*m_Height; i++)
	{
		if((m_pDlg->objectlabelmap[i] != 0)&&(abs(m_pDlg->objectwordcoordinate[i][2]+10000.0) > 1000))		
		{
			double temp = m_pDlg->objectwordcoordinate[i][2] * covcofx;
			int itemp;
			itemp = int(temp+0.5);
	
			ICfout << i%m_Width << " " << itemp << " " << i/m_Width << endl;
   		}
	}

	// ��ʾ����ĻҶ�ͼ
	double max = 0;
	double min = 1000;
	for(int i = 0; i < m_Width*m_Height; i++)
		if((m_pDlg->objectlabelmap[i] != 0)&&(abs(m_pDlg->objectwordcoordinate[i][2]+10000.0) > 1000))
		{
			max = (max < m_pDlg->objectwordcoordinate[i][2]) ? m_pDlg->objectwordcoordinate[i][2] : max;
			min = (min > m_pDlg->objectwordcoordinate[i][2]) ? m_pDlg->objectwordcoordinate[i][2] : min;

		}
	for(int i = 0; i < m_Width * m_Height; i++)
	{
		if((m_pDlg->objectlabelmap[i] != 0)&&(abs(m_pDlg->objectwordcoordinate[i][2]+10000.0) > 1000))		
		{
			double temp = 255*(m_pDlg->objectwordcoordinate[i][2] - min) / (max - min);
			
			if(temp < 0) // Ϊ0�ĵ�
			{
				*(pData + pit*(i/m_Width) + bitcount*(i%m_Width)) = 0;
				*(pData + pit*(i/m_Width) + bitcount*(i%m_Width)+1) = 0;
				*(pData + pit*(i/m_Width) + bitcount*(i%m_Width)+2) = 255;
			}
			else
			{
				int g = int(temp+0.5);
				*(pData + pit*(i/m_Width) + bitcount*(i%m_Width)) = g;
				*(pData + pit*(i/m_Width) + bitcount*(i%m_Width)+1) = g;
				*(pData + pit*(i/m_Width) + bitcount*(i%m_Width)+2) = g;
			}
		}
		else
		{
			*(pData + pit*(i/m_Width) + bitcount*(i%m_Width)) = 0;
			*(pData + pit*(i/m_Width) + bitcount*(i%m_Width)+1) = 0;
			*(pData + pit*(i/m_Width) + bitcount*(i%m_Width)+2) = 0;
		}	
	}
	int m_seldirection = this->m_ChDirectionList.GetCurSel(); // ѡ��ķ���
	int m_selobject = this->m_ChObjectList.GetCurSel(); // ѡ������
	CString tmp;
	if(m_seldirection == 0)
		tmp.Format(".\\reference-plane\\%d-object-h.bmp", m_selobject);
	else
		tmp.Format(".\\reference-plane\\%d-object-v.bmp", m_selobject);
	image->Save(tmp);
	m_pDlg->OnDrawImage(image, m_pDlg->m_DrawBuffer);
	delete image; image = NULL;
	pData = NULL;
	delete m_pDlg->m_CornerImg; m_pDlg->m_CornerImg = 0;
	delete m_pDlg->objectlabelmap; m_pDlg->objectlabelmap = 0;
	return ;
}
