#include "StdAfx.h"
#include "MyPhase.h"
//#include <stdio.h>
//#include <iostream>
//using namespace std;
CMyPhase::CMyPhase(void)
{
	m_pMorphology = new CMorphology();
	m_pConnectComponentLabel = new CConnectComponentLabel();
	m_pMyAlgebra = new CMyAlgebra ();
	m_pVQualityMapGuidedUn = new CVQualityMapGuidedUn();
	m_pHQualityMapGuidedUn = new CHQualityMapGuidedUn();
}


CMyPhase::~CMyPhase(void)
{
	delete m_pConnectComponentLabel;
	delete m_pHQualityMapGuidedUn;
	delete m_pMorphology;
	delete m_pMyAlgebra;
	delete m_pVQualityMapGuidedUn;
}

/*==============================================================
Name:	CreatePhaseMap
Desc:   3步相移算法的代码
Param:	
Return:  获得一幅相对相位图
Note: 
  --------------------------------------------------------------*/
double * CMyPhase::CreatePhaseMap(CImage ** imagearray, int width, int height)
{
	double * phasebitmap =  new double[width*height];

	//CImage *image = new CImage();
	//image->Create(width, height, 24);

	byte * p1Data, *p2Data, *p3Data;
	p1Data = (byte*)imagearray[0]->GetBits();
	p2Data = (byte*)imagearray[1]->GetBits();
	p3Data = (byte*)imagearray[2]->GetBits();
	int pit = imagearray[0]->GetPitch();
	int bitCount = imagearray[0]->GetBPP()/8;
	int r1, r2, r3;
	if (!imagearray[0]->IsNull())
	{
		for(int i = 0; i < width; i++)
			for(int j = 0; j < height; j++)
			{
				r1 = *(p1Data + pit*j + i*bitCount);
				r2 = *(p2Data + pit*j + i*bitCount);
				r3 = *(p3Data + pit*j + i*bitCount);
				//double x = double(sqrt(3.0) * (r1 - r3)) 
				//	/double((2.0 * r2 - r1 - r3));
				phasebitmap[i + j*width] = atan2(double(sqrt(3.0) * (r1 - r3)), double((2.0 * r2 - r1 - r3)));
			//	phasebitmap[i + j*width] = atan(x );
				//printf ("%f\n",phasebitmap[i+j*width]); 
				//int pixel = 255 * (phasebitmap[i + j*width] + PI / 2.0) / PI;
				//image->SetPixelRGB(i, j, pixel, pixel, pixel);	
				
			}
	}
	//image->Save(filename);
	//delete image;
	return phasebitmap;
}

/*==============================================================
Name:	CreateQualityMap1
Desc:   产生质量图1
Param:	
Return:  产生质量图1，用于移除背景图像
Note: 
  --------------------------------------------------------------*/
CImage * CMyPhase::CreateQualityMap1(CImage ** imagearray, int width, int height, bool b_ob)
{
	CImage *image = new CImage();
	image->Create(width, height, 8);
	
	byte *p1Data, *p2Data, *p3Data, * newData;
	p1Data = (byte*)imagearray[0]->GetBits();
	p2Data = (byte*)imagearray[1]->GetBits();
	p3Data = (byte*)imagearray[2]->GetBits();
	newData = (byte*)image->GetBits();
	int pit = imagearray[0]->GetPitch();
	int bitCount = imagearray[0]->GetBPP()/8;
	int newpit = image->GetPitch();
	int newbitCount = image->GetBPP()/8;
    int r1, r2, r3;

	if (!imagearray[0]->IsNull())
	{
		for(int i = 0; i < width; i++)
			for(int j = 0; j < height; j++)
			{
				r1 = *(p1Data + pit*j + i*bitCount);
				r2 = *(p2Data + pit*j + i*bitCount);
				r3 = *(p3Data + pit*j + i*bitCount);
				double temp;
	
				if(r1+r2+r3 == 0)
					temp = 0;
				else
					temp = sqrt(double(3*(r1-r3)*(r1-r3) + (2*r2-r1-r3)*(2*r2-r1-r3))) / (r1+r2+r3);
				//temp = sqrt(double(3*((r1-r3)*(r1-r3)+(r2-r3)*(r2-r3)+(r1-r2)*(r1-r2)))) /(r1+r2+r3);
				
				double biaozhun;
				if (b_ob)
				{
					biaozhun = 0.25;
				}
				else
					biaozhun = 0.25;
				if(temp < biaozhun) // 一般为0.25，我这里取0.20
					*(newData + newpit*j + newbitCount*i) = 0;
				else
					*(newData + newpit*j + newbitCount*i) = 255;
			}
	}
	return image;
}
/*==============================================================
Name:	CreateQualityMap2
Desc:   产生质量图2
Param:	
Return:  产生质量图2，用于移除背景图像
Note: 
  --------------------------------------------------------------*/
double ** CMyPhase::CreateQualityMap2(double * phasemap, int width, int height)
{
	double ** temp = new double*[width];
	double **temp_1 = new double*[width];
	double **temp_2 = new double*[width];
	for(int i = 0; i < width; i++)
	{
		temp[i] = new double[height];
		temp_1[i] = new double[height];
		temp_2[i] = new double[height];
	}
	double B_r, A_r, M_r;
	for(int i = 0; i < width; i++)
	{
		temp_1[i][0] = 0;
		temp_1[i][height-1] = 0;
	}

	for(int j = 0; j < height; j++)
	{
		temp_2[0][j] = 0;
		temp_2[width - 1][j] = 0;
	}
	for(int i = 0; i < width; i++)
		for(int j = 1; j < height-1; j++)
		{
			M_r = phasemap[i+j*width]/PI;
			B_r = phasemap[i+(j-1)*width]/PI;
			A_r = phasemap[i+(j+1)*width]/PI;
			double A = abs(myLineScan(M_r,B_r));
			double B = abs(myLineScan(A_r, M_r));
			temp_1[i][j] = (A >= B)?A:B;
		}
	for(int j = 0 ;j < height; j++)
		for(int i = 1; i < width-1; i++)
		{
			M_r = phasemap[i+j*width]/PI;
			B_r = phasemap[i-1+j*width]/PI;
			A_r = phasemap[i+1+j*width]/PI;
			double A = abs(myLineScan(M_r,B_r));
			double B = abs(myLineScan(A_r, M_r));
			temp_2[i][j] = (A >= B)?A:B;
		}
	double Max_r, Min_r;
    Max_r = 0.0;
	Min_r = 1.0;
	for(int i = 0; i < width; i++)
		for(int j = 0; j < height; j++)
		{
			temp[i][j] = (temp_1[i][j] >= temp_2[i][j]) ? temp_1[i][j]:temp_2[i][j];
		}
	for(int i = 0; i < width; i++)
	{
		delete []temp_1[i];
		delete []temp_2[i];
	}
	delete []temp_1;
	delete []temp_2;
	return temp;
}

double CMyPhase::myLineScan(double a, double b)
{
	double temp = a - b;
	if(temp > 0.5)
		temp = temp - 1.0;
	if(temp < -0.5)
		temp = temp + 1.0;
	return temp;
}
/*==============================================================
Name:	StratifyQualityMap
Desc:   利用质量图1和质量图2进行分层，存储为一个新的图片
Param:	
Return:  labelmap，作为分类的标志图
Note: 
  --------------------------------------------------------------*/

int * CMyPhase::StratifyQualityMap(CImage * qualitymap1, double ** qualitymap2, int width, int height)
{
	// 形态学操作，打掉空心点
	//CImage * newqualitymap1;
	qualitymap1 = m_pMorphology->Close(qualitymap1, 1);
	qualitymap1 = m_pMorphology->Open(qualitymap1, 1);
	// 找到质量图1的一个大的连通区域
	byte r;

	unsigned char * bitmap = new unsigned char[width * height];
    int *labelmap = new int[width * height];
	for(int i = 0; i < width * height; i++)
	{
		bitmap[i] = 0;
		labelmap[i] = 0;
	}
	byte * pData;
	pData = (byte*)qualitymap1->GetBits();
	int pit1 = qualitymap1->GetPitch();
	int bitCount1 = qualitymap1->GetBPP()/8;
	for(int cy = 5; cy < height ; cy++)
		for(int cx = 5; cx < width ; cx++)
		{
			r = *(pData + pit1*cy + bitCount1*cx);
			bitmap[cx + cy * width] = r;
		}

	int m_labelIndex = m_pConnectComponentLabel->ConnectedComponentLabeling(bitmap, width, height, labelmap);
	/*CImage * bimage = new CImage();
	bimage->Create(width, height, 24);
	for(int i = 0 ;i < width*height; i++)
	{
		switch(labelmap[i])
		{
		case 0:
			bimage->SetPixelRGB(i%width, i/width, 0,0,0);
			break;
		case 1:
			bimage->SetPixelRGB(i%width, i/width, 255,0,0);
			break;
		case 2:
			bimage->SetPixelRGB(i%width, i/width, 0,255,0);
			break;
		case 3:
			bimage->SetPixelRGB(i%width, i/width, 0,0,255);
			break;
		case 4:
			bimage->SetPixelRGB(i%width, i/width, 124,124,0);
			break;
		case 5:
			bimage->SetPixelRGB(i%width, i/width, 0,124,0);
			break;
		case 6:
			bimage->SetPixelRGB(i%width, i/width, 0,124,124);
			break;
		case 7:
			bimage->SetPixelRGB(i%width, i/width, 0,34,124);
			break;
		default:
			bimage->SetPixelRGB(i%width, i/width, 0,0,255);
			break;
		}
	}
	bimage->Save("reference-plane\\connectcomponent.jpg");
	delete bimage;*/
    //计算该连通区域质量图2的均值、方差，中心点

	int *m_area = new int[m_labelIndex];
	for(int i = 0; i < m_labelIndex; i++)
		m_area[i] = 0;
	for(int j = 0; j < m_labelIndex; j++)
	{
		m_area[j] = m_pMyAlgebra->CalculateArea(labelmap, width, height, j+1); // 后面计算最大面积
	}
	int m_MaxArea = 0;
	int m_MaxlabelIndex = 0;
	for(int i = 0; i < m_labelIndex; i++)
		if(m_MaxArea < m_area[i])
		{
			m_MaxArea = m_area[i];
			m_MaxlabelIndex = i+1;
		}
	delete m_area;
	
	double m_Mean = m_pMyAlgebra->CalculateMean(qualitymap2, labelmap, width, height, m_MaxArea, m_MaxlabelIndex);
	double m_Variance = m_pMyAlgebra->CalculateVariance(qualitymap2, labelmap, width, height, m_MaxArea, m_MaxlabelIndex);
	centerpoint = m_pMyAlgebra->CalculateCenterPoint(labelmap, width, height, m_MaxlabelIndex, m_MaxArea);
	//分为3层
	double Level_1 = m_Mean;
	double Level_2 = m_Mean + m_Variance;

	for(int cx = 0; cx < width; cx++)
		for(int cy = 0; cy < height; cy++)
		{
			double temp = qualitymap2[cx][cy];
			if(labelmap[cx + cy*width] == m_MaxlabelIndex)
			{
				if(Level_1 > temp)
					labelmap[cx + cy*width] = LEVEL1;
				else if((Level_1 < temp)&&(temp < Level_2))
					labelmap[cx + cy*width] = LEVEL2;
				else
					labelmap[cx + cy*width] = LEVEL3;
			}
			else
				labelmap[cx + cy*width] = 0;
		}
	delete bitmap;
	CImage * stratifiedqualitymap = new CImage();
	stratifiedqualitymap->Create(width, height, 24);
	for(int cx = 0; cx < width; cx++)
		for(int cy = 0; cy < height; cy++)
		{
			switch(labelmap[cx + cy*width])
			{
			case 0:
				stratifiedqualitymap->SetPixelRGB(cx, cy, 0, 0, 0);
				break;
			case 1:
				stratifiedqualitymap->SetPixelRGB(cx, cy, 255, 0, 0);
				break;
			case 2:
				stratifiedqualitymap->SetPixelRGB(cx, cy, 0, 255, 0);
				break;
			case 3:
				stratifiedqualitymap->SetPixelRGB(cx, cy, 0, 0, 255);
				break;
			default:
				stratifiedqualitymap->SetPixelRGB(cx, cy, 100, 50, 0);
				break;
			}
		}
	stratifiedqualitymap->Save(".\\reference-plane\\labelmap.bmp");
	delete stratifiedqualitymap;
	return labelmap;
}
/*==============================================================
Name:	UnwrapPhaseMap
Desc:   进行相位展开
Param:	
Return:  返回绝对相位图
Note: 
  --------------------------------------------------------------*/
double * CMyPhase::UnwrapPhaseMap(double * phasemap, int * labelmap, int width, int height, bool bdirection, CPoint refpoint)
{
	double *absolutephasemap;
	double tempp = phasemap[refpoint.x + refpoint.y*width];
	for(int i = 0; i < width*height; i++)
		phasemap[i] -= tempp; // 将这里作为参考值为0
	if(bdirection)
	{
	//	startpoint = m_pVQualityMapGuidedUn->FindStartPosition(phasemap, labelmap, centerpoint, width, height);
		absolutephasemap = m_pVQualityMapGuidedUn->UnwrapPhaseMap(phasemap, labelmap, width, height, refpoint, refpoint);
	}
	else
	{
	//	startpoint = m_pHQualityMapGuidedUn->FindStartPosition(phasemap, labelmap, centerpoint, width, height);
		absolutephasemap = m_pHQualityMapGuidedUn->UnwrapPhaseMap(phasemap, labelmap, width, height, refpoint, refpoint);
	}
	//absolutephasemap=new double[width*height];
	//int scale = 3;
	//for(int i=0;i<height;i++)
	//{
	//	for(int j=0;j<width;j++)
	//	{
	//		absolutephasemap[i*width +j]=0;
	//	}
	//}

	//for(int x = scale; x < width-scale; x++)
	//{
	//	for(int y = scale; y < height-scale; y++)
	//	{
	//		if(!bdirection) // 水平方向 false
	//		{
	//			for(int m=0;m<scale;m++)
	//			{
	//				int n=(scale-1)/2;
	//				absolutephasemap[x + y*width]+=absolutephasemap1[x + (y+m-n)*width];
	//			}
	//			absolutephasemap[x + y*width]=(double)(absolutephasemap[x + y*width]/scale);
	//		}
	//		else // 对于垂直的情况下，不好
	//		{
	//			for(int m=0;m<scale;m++)
	//			{
	//				int n=(scale-1)/2;
	//				absolutephasemap[x + y*width]+=absolutephasemap1[x+m-n + y*width];
	//			}
	//			absolutephasemap[x + y*width]=(double)(absolutephasemap[x + y*width]/scale);
	//		}
	//	}
	//}
	//delete absolutephasemap1;
	//absolutephasemap1 = NULL;
	/*double max , min;
	max = min = absolutephasemap[0];
	for(int i = 0; i < width * height; i++)
	{
		if(labelmap[i] != 0)
		{
			max = (max < absolutephasemap[i]) ? absolutephasemap[i] : max;
			min = (min > absolutephasemap[i]) ? absolutephasemap[i] : min;
		}
	}*/
	/*CImage * image = new CImage();
	image->Create(width, height, 24);
	int temp = 0;
	for(int i = 0; i < width * height; i++)
	{
		
		temp = 255*(absolutephasemap[i] - min) / (max - min);
		if(labelmap[i] != 0)
			image->SetPixelRGB(i%width, i/width, temp, temp, temp);
		else
			image->SetPixelRGB(i%width, i/width, 255, 255, 255);
	}
	image->Save(filename);*/
	return absolutephasemap;
}