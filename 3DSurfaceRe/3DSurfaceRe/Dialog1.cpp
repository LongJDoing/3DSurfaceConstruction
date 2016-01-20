// Dialog1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "3DSurfaceRe.h"
#include "Dialog1.h"
#include "afxdialogex.h"
#include <iostream>
#include <fstream>
using namespace std;
RGBQUAD colorTable[256];
int  img_num = 0; // �洢ͼƬ��

// CDialog1 �Ի���

IMPLEMENT_DYNAMIC(CDialog1, CDialogEx)

CDialog1::CDialog1(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialog1::IDD, pParent)
{
	m_inputdlg = NULL;
	m_pDlg = NULL;
	m_showimagedlg = NULL;
	for(int i = 0; i < 256; i++)
	{
		RGBQUAD index;
		index.rgbBlue = index.rgbGreen = index.rgbRed = i;
		colorTable[i] = index;
	}
	m_myphase = new CMyPhase();
	m_mygeometry = new CMyGeometry();
	m_myleastsquare = new CMyLeastSquare();
}

CDialog1::~CDialog1()
{
}

void CDialog1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHPLANELIST, m_ChPlaneList);
	DDX_Control(pDX, IDC_CHDRLIST, m_ChDirectionList);
}


BEGIN_MESSAGE_MAP(CDialog1, CDialogEx)
	ON_BN_CLICKED(IDC_INPUTPA, &CDialog1::OnInputpr)
	ON_BN_CLICKED(IDC_CALCULATECORNER, &CDialog1::OnBnClickedCalculatecorner)
	ON_BN_CLICKED(IDC_IMPORTSTRIPES, &CDialog1::OnBnClickedImportstripes)
	ON_BN_CLICKED(IDC_CALCULATERPM, &CDialog1::OnBnClickedCalculaterpm)
	ON_BN_CLICKED(IDC_CALCULATEAPM, &CDialog1::OnBnClickedCalculateapm)
	ON_CBN_SELCHANGE(IDC_CHPLANELIST, &CDialog1::OnCbnSelchangeChplanelist)
	ON_CBN_SELCHANGE(IDC_CHDRLIST, &CDialog1::OnCbnSelchangeChdrlist)
	ON_BN_CLICKED(IDC_EXTRACTSAMPT, &CDialog1::OnBnClickedExtractsampt)
	ON_BN_CLICKED(IDC_CALCULATECORRESPT, &CDialog1::OnBnClickedCalculatecorrespt)
	ON_BN_CLICKED(IDC_COMPUTEPROJECTORCENTER, &CDialog1::OnBnClickedComputeprojectorcenter)
	ON_BN_CLICKED(IDC_SHOWPHASEMAP, &CDialog1::OnBnClickedShowphasemap)
	ON_BN_CLICKED(IDC_SHOWABSOLUTEMAP, &CDialog1::OnBnClickedShowabsolutemap)
END_MESSAGE_MAP()

BOOL CDialog1::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_pDlg = (C3DSurfaceReDlg *)GetParent()->GetParent();
	return TRUE;
}

// CDialog1 ��Ϣ�������

void CDialog1::OnInputpr()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_inputdlg != NULL)
	{
		delete m_inputdlg;
		m_inputdlg = NULL;
	}
	m_inputdlg = new CInputDialog(this);

	m_inputdlg->Create(IDD_INPUT_DIALOG, this);
	m_inputdlg->ShowWindow(SW_SHOW);
	this->GetDlgItem(IDC_INPUTPA)->EnableWindow(FALSE);

}

/*==============================================================
����:	OnBnClickedCalculatecorner
����:   ���֮�󣬴�һ��ͼƬ
����:   
--------------------------------------------------------------*/
void CDialog1::OnBnClickedCalculatecorner()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_pDlg->m_CornerImg = this->InputOneImg();
	this->GetDlgItem(IDC_IMPORTSTRIPES)->EnableWindow(TRUE);
	this->GetDlgItem(IDC_CALCULATECORNER)->EnableWindow(FALSE);
	m_pDlg->b_objectcorner = false;
	m_pDlg->b_ifcorner = true;
	m_pDlg->OnShowImg(m_pDlg->m_CornerImg, TRUE);
}

CImage * CDialog1::InputOneImg()
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

vector<CImage *> CDialog1::InputMulImg()
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
void CDialog1::OnBnClickedImportstripes()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_pDlg->m_ImageArray = this->InputMulImg();
	this->GetDlgItem(IDC_IMPORTSTRIPES)->EnableWindow(FALSE);
	this->GetDlgItem(IDC_CALCULATERPM)->EnableWindow(TRUE);
	m_pDlg->OnShowImg(NULL,false);
}

/*==============================================================
����:	OnCalculatePhase
����:   ���������λͼ
����:   ��Ҫ3����դͼ�����ؽ�һ�������λͼ  
--------------------------------------------------------------*/
void CDialog1::OnBnClickedCalculaterpm()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//====����Ի���ʱ��ʹ��======================
	int m_selplane;
	int m_seldirection;
	m_selplane = this->m_ChPlaneList.GetCurSel(); // ѡ���ƽ��
	m_seldirection = this->m_ChDirectionList.GetCurSel(); // ѡ��ķ���

	if(m_selplane == 0)
	{
		if(m_seldirection == 0) // ƽ��rea1ˮƽ����
		{
			m_pDlg->referenceplane_1horizontalphasemap = this->GetphaseMap();
			CImage * image1;
			image1 = this->DrawImage(m_pDlg->referenceplane_1horizontalphasemap, true);
			m_pDlg->OnShowImg(image1, TRUE);
			CString tmp;
			tmp.Format("%d", img_num);
			tmp = ".\\reference-plane\\" + tmp + ".bmp";
			image1->Save(tmp);
			delete image1; image1 = NULL;
		}
		else
		{
			m_pDlg->referenceplane_1verticalphasemap = this->GetphaseMap();
			CImage * image1;
			image1 = this->DrawImage(m_pDlg->referenceplane_1verticalphasemap, true);
			m_pDlg->OnShowImg(image1, TRUE);
			CString tmp;
			tmp.Format("%d", img_num);
			tmp = ".\\reference-plane\\" + tmp + ".bmp";
			image1->Save(tmp);
			delete image1;image1 = NULL;
		}

	}
	else
	{
		if(m_seldirection == 0) // ƽ��2ˮƽ����
		{
			m_pDlg->referenceplane_2horizontalphasemap = this->GetphaseMap();
			CImage * image1;
			image1 = this->DrawImage(m_pDlg->referenceplane_2horizontalphasemap, true);
			m_pDlg->OnShowImg(image1, TRUE);
			CString tmp;
			tmp.Format("%d", img_num);
			tmp = ".\\reference-plane\\" + tmp + ".bmp";
			image1->Save(tmp);
			delete image1;image1 = NULL;
		}
		else
		{
			m_pDlg->referenceplane_2verticalphasemap = this->GetphaseMap();
			CImage * image1;
			image1 = this->DrawImage(m_pDlg->referenceplane_2verticalphasemap, true);
			m_pDlg->OnShowImg(image1, TRUE);
			CString tmp;
			tmp.Format("%d", img_num);
			tmp = ".\\reference-plane\\" + tmp + ".bmp";
			image1->Save(tmp);
			delete image1;image1 = NULL;
		}
	}
	img_num++;
	//if(b_ifcorner)
	this->GetDlgItem(IDC_CALCULATEAPM)->EnableWindow(TRUE);
	this->GetDlgItem(IDC_CALCULATERPM)->EnableWindow(FALSE);
	return ;
}

/*==============================================================
����:	DrawImage
����:   ���ݻ���ͼ��
����:   
--------------------------------------------------------------*/
CImage * CDialog1::DrawImage(double * values, bool bID)
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
			if((m_pDlg->labelmap[i] != 0)&&(values[i] != -10000))
			{
				max = (max < values[i]) ? values[i] : max;
				min = (min > values[i]) ? values[i] : min;
			}
		}
		int temp = 0;
		for(int i = 0; i < m_pDlg->m_Width * m_pDlg->m_Height; i++)
		{

			temp = 255*(values[i] - min) / (max - min);
			if((m_pDlg->labelmap[i] != 0)&&(values[i] != -10000))
				*(pData + pit*(i/m_pDlg->m_Width) + bitCount*(i%m_pDlg->m_Width)) = temp;
			else
				*(pData + pit*(i/m_pDlg->m_Width) + bitCount*(i%m_pDlg->m_Width)) = 255;
		}
	}
	image->SetColorTable(0, 256, colorTable);
	return image;
}

double * CDialog1::GetphaseMap()
{
	double * phasemap ;
	CImage * imagearray[3];
	for(int i = 0; i < 3; i++)
		imagearray[i] = m_pDlg->m_ImageArray[i];
	phasemap = m_myphase->CreatePhaseMap(imagearray, m_pDlg->m_Width, m_pDlg->m_Height);
	return phasemap;
}

/*==============================================================
����:	OnCalculateAbsolutephase
����:   ���������λͼ
����:   ��������ͼ����λչ���㷨 + �ǵ�Ѱ���㷨

--------------------------------------------------------------*/
void CDialog1::OnBnClickedCalculateapm()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int m_selplane;
	int m_seldirection;
	m_selplane = this->m_ChPlaneList.GetCurSel(); // ѡ���ƽ��
	m_seldirection = this->m_ChDirectionList.GetCurSel(); // ѡ��ķ���

	if(m_selplane == 0)
	{
		if(m_seldirection == 0) // ƽ��1ˮƽ����
		{
			m_pDlg->referenceplane_1horizontalabsolutephasemap = this->GetAbsolutePhaseMap(m_pDlg->referenceplane_1horizontalphasemap, FALSE);

			CImage * image1;
			image1 = this->DrawImage(m_pDlg->referenceplane_1horizontalabsolutephasemap, false);
			m_pDlg->OnShowImg(image1, TRUE);
			CString tmp;
			tmp.Format("%d", img_num);
			tmp = ".\\reference-plane\\" + tmp + ".bmp";
			image1->Save(tmp);
			delete image1;
			delete m_pDlg->referenceplane_1horizontalphasemap;
			MessageBox("Select Import vertical stripes!");
			this->m_ChDirectionList.SetCurSel(1);
			OnCbnSelchangeChdrlist();
		}
		else // ��ֱ����
		{
			m_pDlg->referenceplane_1verticalabsolutephasemap = this->GetAbsolutePhaseMap(m_pDlg->referenceplane_1verticalphasemap, TRUE);

			CImage * image1;
			image1 = this->DrawImage(m_pDlg->referenceplane_1verticalabsolutephasemap, false);
			m_pDlg->OnShowImg(image1, TRUE);
			CString tmp;
			tmp.Format("%d", img_num);
			tmp = ".\\reference-plane\\" + tmp + ".bmp";
			image1->Save(tmp);
			delete image1;
			delete m_pDlg->referenceplane_1verticalphasemap;
			MessageBox("Select Import the second corner map!");
			this->m_ChDirectionList.SetCurSel(0);
			this->m_ChPlaneList.SetCurSel(1);
			//OnCbnSelchangeChdrlist();
			OnCbnSelchangeChplanelist();
		}

	}
	else
	{
		if(m_seldirection == 0) // ƽ��2ˮƽ����
		{
			m_pDlg->referenceplane_2horizontalabsolutephasemap = this->GetAbsolutePhaseMap(m_pDlg->referenceplane_2horizontalphasemap, FALSE);
			CImage * image1;
			image1 = this->DrawImage(m_pDlg->referenceplane_2horizontalabsolutephasemap, false);
			m_pDlg->OnShowImg(image1, TRUE);
			CString tmp;
			tmp.Format("%d", img_num);
			tmp = ".\\reference-plane\\" + tmp + ".bmp";
			image1->Save(tmp);
			delete image1;
			delete m_pDlg->referenceplane_2horizontalphasemap;
			MessageBox("Select Import vertical stripes!");
			this->m_ChDirectionList.SetCurSel(1);
			OnCbnSelchangeChdrlist();
		}
		else
		{
			m_pDlg->referenceplane_2verticalabsolutephasemap = this->GetAbsolutePhaseMap(m_pDlg->referenceplane_2verticalphasemap, TRUE);

			CImage * image1;
			image1 = this->DrawImage(m_pDlg->referenceplane_2verticalabsolutephasemap, false);
			m_pDlg->OnShowImg(image1, TRUE);
			CString tmp;
			tmp.Format("%d", img_num);
			tmp = ".\\reference-plane\\" + tmp + ".bmp";
			image1->Save(tmp);
			delete image1;
			delete m_pDlg->referenceplane_2verticalphasemap;
			MessageBox("Start extracting sample points!");
			this->GetDlgItem(IDC_EXTRACTSAMPT)->EnableWindow(TRUE);
		}
	}
	img_num++;

	this->GetDlgItem(IDC_CALCULATEAPM)->EnableWindow(FALSE);
	return ;
}



void CDialog1::OnCbnSelchangeChplanelist()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->GetDlgItem(IDC_CALCULATECORNER)->EnableWindow(TRUE);
}


void CDialog1::OnCbnSelchangeChdrlist()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->GetDlgItem(IDC_IMPORTSTRIPES)->EnableWindow(TRUE);
}

double * CDialog1::GetAbsolutePhaseMap(double * phasemap, bool direction)
{
	CImage * imagearray[3];
	for(int i = 0; i < 3; i++)
		imagearray[i] = m_pDlg->m_ImageArray[i];
	CImage * qualitymap1;
	qualitymap1 = m_myphase->CreateQualityMap1(imagearray, m_pDlg->m_Width, m_pDlg->m_Height,false);
	qualitymap1->SetColorTable(0, 256, colorTable);
	qualitymap1->Save(".\\reference-plane\\qualitymap1.bmp");
	
	//===
	//CImage * qualitymap2 = new CImage();
	//qualitymap2->Create(m_pDlg->m_Width, m_pDlg->m_Height, 8);
	/*��ӻ�������ͼ2�Ĵ���*/

	double ** dqualitymap2;
	dqualitymap2 = m_myphase->CreateQualityMap2(phasemap, m_pDlg->m_Width, m_pDlg->m_Height );
	/*qualitymap2->SetColorTable(0, 256, colorTable);
	qualitymap2->Save("reference-plane\\qualitymap2.jpg");*/

	int * stratifyqualitylabelmap = m_myphase->StratifyQualityMap(qualitymap1, dqualitymap2, m_pDlg->m_Width, m_pDlg->m_Height);

	//================== ���ڲο�ƽ�潨��labelmap����=====
	int m_chpllist = this->m_ChPlaneList.GetCurSel();
	int m_chdrlist = this->m_ChDirectionList.GetCurSel();
	if(m_chpllist == 0)
	{
		if(m_chdrlist == 0)
		{
			m_pDlg->hreferencelabelmap = new int[m_pDlg->m_Width*m_pDlg->m_Height];
			for(int i = 0 ; i < m_pDlg->m_Width*m_pDlg->m_Height; i++)
			{
				if(stratifyqualitylabelmap[i] == 0)
					m_pDlg->hreferencelabelmap[i] = 0;
				else
					m_pDlg->hreferencelabelmap[i] = 1;
			}
		}
		else
		{
			m_pDlg->vreferencelabelmap = new int[m_pDlg->m_Width*m_pDlg->m_Height];
			for(int i = 0 ; i < m_pDlg->m_Width*m_pDlg->m_Height; i++)
			{
				if(stratifyqualitylabelmap[i] == 0)
					m_pDlg->vreferencelabelmap[i] = 0;
				else
					m_pDlg->vreferencelabelmap[i] = 1;
			}
		}
	}
	//=========================================================
	double * absolutephasemap;

	absolutephasemap = m_myphase->UnwrapPhaseMap(phasemap, stratifyqualitylabelmap, m_pDlg->m_Width, m_pDlg->m_Height, 
		direction, m_pDlg->referencepoint); // ����������е��ú���������startpoint
	CFile m_File1;
	m_File1.Remove(".\\test-result.txt"); //ɾ����һ�δ洢��ͼƬλ��
	m_File1.Open(".\\test-result.txt",CFile::modeWrite|CFile::modeCreate);//���´������ļ�
	m_File1.Close();
	ofstream tfout(".\\test-result.txt", ios::out|ios::in|ios::ate);
	tfout << "plane data..."<< endl;
	for(int i = 0; i < m_pDlg->m_Height ; i++)
			tfout << absolutephasemap[365 + i*m_pDlg->m_Width] << endl;

	for(int i = 0 ; i < m_pDlg->m_Width*m_pDlg->m_Height; i++)
		if(stratifyqualitylabelmap[i] == 0)
			absolutephasemap[i] = 0;
	// Step9...����labelmap�����ں���ı�ǵȲ���

	for(int cx = 0; cx < m_pDlg->m_Width; cx++)
		for(int cy = 0; cy < m_pDlg->m_Height; cy++)
			if((m_pDlg->labelmap[cx + cy*m_pDlg->m_Width] ==0)||(stratifyqualitylabelmap[cx + cy*m_pDlg->m_Width] == 0))
			{
				m_pDlg->labelmap[cx + cy*m_pDlg->m_Width] = 0;
			}
	delete qualitymap1, stratifyqualitylabelmap;
	for(int i =0; i < m_pDlg->m_Width; i++)
		delete []dqualitymap2[i];
	delete []dqualitymap2; dqualitymap2 = NULL;
	return absolutephasemap;
}

/*==============================================================
����:	OnBnClickedExtractsampt
����:   �ҵ�������
����:   ͨ������������㷨���ҵ�����ƽ��ƽ��Ĳ�����

--------------------------------------------------------------*/
void CDialog1::OnBnClickedExtractsampt()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int * mynum = 0;
	mynum = new int[1];
	CPoint mypoint;
	mypoint.x = m_pDlg->m_Width / 2;
	mypoint.y = m_pDlg->m_Height / 2;
	m_pDlg->plane_1projectionsamplepoints = m_mygeometry->GetProjectionSamplePoint(m_pDlg->labelmap, mypoint, m_pDlg->m_Width, m_pDlg->m_Height, mynum);
	m_pDlg->samplenum = mynum[0];
	delete mynum;
	CImage *image = new CImage();
	image->Create(m_pDlg->m_Width, m_pDlg->m_Height,24);
	int bitCount = image->GetBPP()/8;
	byte * pData = (byte*)image->GetBits();
	int pit = image->GetPitch();
	for(int cx = 0; cx < m_pDlg->m_Width; cx++)
		for(int cy = 0; cy < m_pDlg->m_Height; cy++)
		{
			*(pData + cy*pit + cx*bitCount) = 62;
			*(pData + cy*pit + cx*bitCount +1) = 70;
			*(pData + cy*pit + cx*bitCount +2)  = 55;
		}
	if(m_pDlg->samplenum!=0)
		for(int i = 0; i < m_pDlg->samplenum; i++)
		{
			int x = m_pDlg->plane_1projectionsamplepoints[i][0];
			for(int dy = m_pDlg->plane_1projectionsamplepoints[i][1]-5; dy <= m_pDlg->plane_1projectionsamplepoints[i][1] +5; dy++)
			{
				*(pData + dy*pit + x*bitCount) = 255;
				*(pData + dy*pit + x*bitCount +1) = 0;
				*(pData + dy*pit + x*bitCount +2)  = 0;
			}
			int y = m_pDlg->plane_1projectionsamplepoints[i][1];
			for(int dx = m_pDlg->plane_1projectionsamplepoints[i][0]-5; dx <= m_pDlg->plane_1projectionsamplepoints[i][0] +5; dx++)
			{
				*(pData + y*pit + dx*bitCount) = 255;
				*(pData + y*pit + dx*bitCount +1) = 0;
				*(pData + y*pit + dx*bitCount +2)  = 0;
			}
		}
	m_pDlg->OnDrawImage(image, m_pDlg->m_DrawBuffer);
	delete image;
	this->GetDlgItem(IDC_CALCULATECORRESPT)->EnableWindow(TRUE);
	this->GetDlgItem(IDC_EXTRACTSAMPT)->EnableWindow(FALSE);
	return;
}

/*==============================================================
����:	OnBnClickedCalculatecorrespt
����:   �ҵ���������ƽ���Ӧ��
����:   ͨ���ռ�����任�������Ӧ�� + �����������
        ���ô��ڣ���������ڲ�����ϵͳ�������
--------------------------------------------------------------*/
void CDialog1::OnBnClickedCalculatecorrespt()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int samplenum = m_pDlg->samplenum;
	double ** projectionsamplepointabsolutephase = new double*[samplenum];
	for(int i = 0; i < samplenum; i++)
		projectionsamplepointabsolutephase[i] = new double[2];
	for(int i = 0; i < samplenum; i++)
	{
		projectionsamplepointabsolutephase[i][0] = m_mygeometry->GetPointAbsolutePhase
			(m_pDlg->referenceplane_1verticalabsolutephasemap, m_pDlg->plane_1projectionsamplepoints[i], m_pDlg->m_Width, m_pDlg->m_Height);
		projectionsamplepointabsolutephase[i][1] = m_mygeometry->GetPointAbsolutePhase
			(m_pDlg->referenceplane_1horizontalabsolutephasemap, m_pDlg->plane_1projectionsamplepoints[i], m_pDlg->m_Width, m_pDlg->m_Height);
	}
	int ** plane_2projectionsamplepoints ;
	// no-problem
	plane_2projectionsamplepoints = m_mygeometry->GetAbsolutePhaseCorrespondPoint(m_pDlg->referenceplane_2verticalabsolutephasemap, m_pDlg->referenceplane_2horizontalabsolutephasemap, 
		m_pDlg->labelmap, projectionsamplepointabsolutephase, samplenum, m_pDlg->m_Width, m_pDlg->m_Height);

	double ** newplane_1projectionsamplepoints, ** newplane_2projectionsamplepoints; // ͶӰ��У׼���еĶ�Ӧ��
	newplane_1projectionsamplepoints = new double*[samplenum];
	newplane_2projectionsamplepoints = new double*[samplenum];
	for(int i = 0; i < samplenum; i++)
	{
		newplane_1projectionsamplepoints[i] = new double[2];
        newplane_2projectionsamplepoints[i] = new double[2];
	}
    m_pDlg->projectionsamplepointsnum = 0;
	m_pDlg->projectionsamplepointsnum = m_mygeometry->DeleteBadPoint(samplenum, m_pDlg->plane_1projectionsamplepoints, plane_2projectionsamplepoints, 
		newplane_1projectionsamplepoints, newplane_2projectionsamplepoints);

	for(int i = 0; i < samplenum; i++)
	{
		delete []m_pDlg->plane_1projectionsamplepoints[i];
		delete []plane_2projectionsamplepoints[i];
		delete []projectionsamplepointabsolutephase[i];
	}
		
	delete []m_pDlg->plane_1projectionsamplepoints;
	delete []plane_2projectionsamplepoints;
	delete []projectionsamplepointabsolutephase;

	delete m_pDlg->referenceplane_2verticalabsolutephasemap, m_pDlg->referenceplane_2horizontalabsolutephasemap;

	// Show image
	CImage * image = new CImage;

	image->Create(m_pDlg->m_Width, m_pDlg->m_Height, 24);
	byte * pData = (byte*)image->GetBits();
	int pit = image->GetPitch();
	int bitCount = image->GetBPP()/8;

	for(int cx = 0; cx < m_pDlg->m_Width; cx++)
		for(int cy = 0; cy < m_pDlg->m_Height; cy++)
		{
			*(pData + cy*pit + cx*bitCount) = 62;
			*(pData + cy*pit + cx*bitCount +1) = 70;
			*(pData + cy*pit + cx*bitCount +2)  = 55;
		}
	for(int i = 0; i < m_pDlg->projectionsamplepointsnum; i++)
	{
		int x0 = newplane_1projectionsamplepoints[i][0]; 
		for(int cy = newplane_1projectionsamplepoints[i][1] - 5; cy <= newplane_1projectionsamplepoints[i][1] + 5; cy++)
			//image1->SetPixelRGB(x0, cy, 255, 0, 0);
			{
				*(pData + cy*pit + x0*bitCount) = 255;
				*(pData + cy*pit + x0*bitCount+1) = 0;
				*(pData + cy*pit + x0*bitCount+2) = 0;
			}
		int y0 = newplane_1projectionsamplepoints[i][1]; 
		for(int cx = newplane_1projectionsamplepoints[i][0] - 5; cx <= newplane_1projectionsamplepoints[i][0] + 5; cx++)
		{
			//image1->SetPixelRGB(cx, y0, 255, 0, 0);
			*(pData + y0*pit + cx*bitCount) = 255;
			*(pData + y0*pit + cx*bitCount+1) = 0;
			*(pData + y0*pit + cx*bitCount+2) = 0;

		}

		x0 = newplane_2projectionsamplepoints[i][0]; 
		for(int cy = newplane_2projectionsamplepoints[i][1] - 5; cy <= newplane_2projectionsamplepoints[i][1] + 5; cy++)
		{
			*(pData + cy*pit + x0*bitCount) = 0;
			*(pData + cy*pit + x0*bitCount+1) = 255;
			*(pData + cy*pit + x0*bitCount+2) = 0;
		}
		y0 = newplane_2projectionsamplepoints[i][1]; 
		for(int cx = newplane_2projectionsamplepoints[i][0] - 5; cx <= newplane_2projectionsamplepoints[i][0] + 5; cx++)
		{
			*(pData + y0*pit + cx*bitCount) = 0;
			*(pData + y0*pit + cx*bitCount+1) = 255;
			*(pData + y0*pit + cx*bitCount+2) = 0;
		}

	}
	m_pDlg->OnDrawImage(image,m_pDlg->m_DrawBuffer);
	delete image;	image = NULL;
	this->GetDlgItem(IDC_CALCULATECORRESPT)->EnableWindow(FALSE);
	this->GetDlgItem(IDC_COMPUTEPROJECTORCENTER)->EnableWindow(TRUE);

	// Step13... �������������Ӧ�Ŀռ�����
	double ** plane1_samplepointswordcoordinate = new double*[m_pDlg->projectionsamplepointsnum];
	double ** plane2_samplepointswordcoordinate = new double*[m_pDlg->projectionsamplepointsnum];

	for(int i = 0; i < m_pDlg->projectionsamplepointsnum; i++)
	{
		plane1_samplepointswordcoordinate[i] = m_mygeometry->ConvertCameraImageCoordinateToWordCoordinate(newplane_1projectionsamplepoints[i]);
		plane2_samplepointswordcoordinate[i] = m_mygeometry->ConvertCameraImageCoordinateToWordCoordinate(newplane_2projectionsamplepoints[i]);
	}
	// Step14... ����������ĵ���������
	m_pDlg->cameracenterwordcoordinate = m_mygeometry->GetCameraCenterWordCoordinate();

	// Step15... �����������ο�ƽ��Ķ�Ӧ��
	m_pDlg->plane_1correspondpoints = new double*[m_pDlg->projectionsamplepointsnum];
	m_pDlg->plane_2correspondpoints = new double*[m_pDlg->projectionsamplepointsnum];
	for(int i = 0; i < m_pDlg->projectionsamplepointsnum; i++)
	{
		m_pDlg->plane_1correspondpoints[i] = m_mygeometry->FindIntersectionOfLineAndReferenceplane(m_pDlg->cameracenterwordcoordinate, plane1_samplepointswordcoordinate[i], 0);
		m_pDlg->plane_2correspondpoints[i] = m_mygeometry->FindIntersectionOfLineAndReferenceplane(m_pDlg->cameracenterwordcoordinate, plane2_samplepointswordcoordinate[i], m_Distance);
	}

	delete plane1_samplepointswordcoordinate, plane2_samplepointswordcoordinate;
	for(int i = 0; i < m_pDlg->projectionsamplepointsnum; i++)
	{
		delete []newplane_1projectionsamplepoints[i];
		delete []newplane_2projectionsamplepoints[i];
	}
	delete []newplane_1projectionsamplepoints;
	delete []newplane_2projectionsamplepoints;
	return;
}

/*==============================================================
����:	OnBnClickedComputeprojectorcenter
����:   ����ͶӰ����
����:   ͨ����С���˹��ƣ�����������ֱ�ߵĽ���

--------------------------------------------------------------*/

void CDialog1::OnBnClickedComputeprojectorcenter()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// Step16... ������������С���˽����ͶӰ����
	/*   projectionsamplepointsnum ���ߣ���ô��һ���� 2*projectionsamplepointsnum�����̣������3��δ֪���ĳ���������
	     a[0][0] a[0][1] a[0][2]    =     b[0]
	     a[1][0] a[1][1] a[1][2]    =     b[1]
		 a[2][0] a[2][1] a[2][2]    =     b[2]
		 a[3][0] a[3][1] a[3][2]    =     b[3]
	*/
	int projectionsamplepointsnum = m_pDlg->projectionsamplepointsnum;
	double ** a = new double*[2*projectionsamplepointsnum];
	double * b = new double[2*projectionsamplepointsnum];
	for(int i = 0; i < 2*projectionsamplepointsnum; i++)
		a[i] = new double[3];
	int i = 0;
	for(int j = 0; j < projectionsamplepointsnum; j++)
	{
		double temp1, temp2, temp0;
		temp0 = m_pDlg->plane_2correspondpoints[j][0] - m_pDlg->plane_1correspondpoints[j][0];
		temp1 = m_pDlg->plane_2correspondpoints[j][1] - m_pDlg->plane_1correspondpoints[j][1];
		temp2 = m_pDlg->plane_2correspondpoints[j][2] - m_pDlg->plane_1correspondpoints[j][2];

		a[i][0] = temp1;
		a[i][1] = -temp0;
		a[i][2] = 0;
		b[i] = temp1 * m_pDlg->plane_1correspondpoints[j][0] - temp0*m_pDlg->plane_1correspondpoints[j][1];

		a[i+1][0] = 0;
		a[i+1][1] = temp2;
		a[i+1][2] = -temp1;
		b[i+1] = temp2*m_pDlg->plane_1correspondpoints[j][1] - temp1*m_pDlg->plane_1correspondpoints[j][2];
		i += 2;
	}
	double * aa = new double [2*projectionsamplepointsnum*3];
	for(int i = 0; i < 2*projectionsamplepointsnum*3; i++)
		aa[i] = a[i/(3)][i%(3)];
	m_pDlg->projectioncenterwordcoordinate = m_myleastsquare->fun(aa, b, 2*projectionsamplepointsnum, 3);
	for(int i = 0; i < 2*projectionsamplepointsnum; i++)
		delete []a[i];
	delete []a;
	delete b, aa;
	
	for(int i = 0; i < projectionsamplepointsnum; i++)
	{
		delete []m_pDlg->plane_1correspondpoints[i];
		delete []m_pDlg->plane_2correspondpoints[i];
	}
	delete []m_pDlg->plane_1correspondpoints;
	delete []m_pDlg->plane_2correspondpoints;
	CString mtmp;
	mtmp.Format("Projector Center: %f,  %f,  %f", m_pDlg->projectioncenterwordcoordinate[0], m_pDlg->projectioncenterwordcoordinate[1], m_pDlg->projectioncenterwordcoordinate[2]);
	MessageBox(mtmp);
	ofstream fout(".\\result.txt", ios::out|ios::in|ios::ate);
	fout << "Projector Center:" << m_pDlg->projectioncenterwordcoordinate[0] << "  "<< m_pDlg->projectioncenterwordcoordinate[1]<< "  "<< m_pDlg->projectioncenterwordcoordinate[2] << endl;

	this->GetDlgItem(IDC_COMPUTEPROJECTORCENTER)->EnableWindow(FALSE);
	m_pDlg->b_calProject = true;
	delete m_pDlg->m_CornerImg; m_pDlg->m_CornerImg = 0;
	return;
}

/*==============================================================
����:	OnBnClickedShowphasemap
����:   ��ʾ����ƽ���4����λͼ
����: 
--------------------------------------------------------------*/
void CDialog1::OnBnClickedShowphasemap()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_showimagedlg != NULL)
	{
		delete m_showimagedlg;
		m_showimagedlg = NULL;
		return  ;
	}
	m_showimagedlg = new CShowImageDialog(this);

	m_showimagedlg->Create(IDD_SHOWIMAGEDIALOG, this);

	CImage *image1 = new CImage();
	CImage *image2 = new CImage();
	CImage *image3 = new CImage();
	CImage *image4 = new CImage();
	image1->Load(".\\reference-plane\\0.bmp");
	image2->Load(".\\reference-plane\\2.bmp");
	image3->Load(".\\reference-plane\\4.bmp");
	image4->Load(".\\reference-plane\\6.bmp");
	m_showimagedlg->ShowWindow(SW_SHOW);
	m_showimagedlg->OnShow(image1, IDC_PICTURE1);
	m_showimagedlg->OnShow(image2, IDC_PICTURE2);
	m_showimagedlg->OnShow(image3, IDC_PICTURE5);
	m_showimagedlg->OnShow(image4, IDC_PICTURE4);
	delete image1, image2, image3, image4;
	return ;
}

/*==============================================================
����:	OnBnClickedShowabsolutemap
����:   ��ʾ����ƽ���4����λͼ
����: 
--------------------------------------------------------------*/
void CDialog1::OnBnClickedShowabsolutemap()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_showimagedlg != NULL)
	{
		delete m_showimagedlg;
		m_showimagedlg = NULL;
		return ;
	}
	m_showimagedlg = new CShowImageDialog(this);

	m_showimagedlg->Create(IDD_SHOWIMAGEDIALOG, this);

	CImage *image1 = new CImage();
	CImage *image2 = new CImage();
	CImage *image3 = new CImage();
	CImage *image4 = new CImage();
	image1->Load(".\\reference-plane\\1.bmp");
	image2->Load(".\\reference-plane\\3.bmp");
	image3->Load(".\\reference-plane\\5.bmp");
	image4->Load(".\\reference-plane\\7.bmp");
	m_showimagedlg->ShowWindow(SW_SHOW);
	m_showimagedlg->OnShow(image1, IDC_PICTURE1);
	m_showimagedlg->OnShow(image2, IDC_PICTURE2);
	m_showimagedlg->OnShow(image3, IDC_PICTURE5);
	m_showimagedlg->OnShow(image4, IDC_PICTURE4);
	delete image1, image2, image3, image4;
	return;
}
