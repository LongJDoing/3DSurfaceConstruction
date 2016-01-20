#include "StdAfx.h"
#include "Morphology.h"


CMorphology::CMorphology(void)
{
}


CMorphology::~CMorphology(void)
{
}
static int EDMask[9][2]={{ 0, 0},{-1,0},{ 0,-1},{0,1},{1,0},
                         {-1,-1},{-1,1},{ 1,-1},{1,1}};

static int hMask[8][9][2]={{{1,1},{0,1},{1,0},{0,0},},   //  击中模板
                   {{-1,0},{-1,-1},{0,-1},{0,0},},
                   {{-1,0},{-1,1},{0,1},{0,0},},
                   {{0,-1},{1,-1},{1,0},{0,0},},
                   {{1,1},{0,1},{-1,1},{0,0},},
                   {{-1,-1},{0,-1},{1,-1},{0,0},},
                   {{-1,0},{-1,1},{-1,-1},{0,0},},
                   {{1,-1},{1,0},{1,1},{0,0}} };

static int mMask[8][9][2]={{{-1,0},{-1,-1},{0,-1},},     //  击不中模板
                   {{1,1},{0,1},{1,0},},
                   {{0,-1},{1,-1},{1,0},},
                   {{-1,0},{-1,1},{0,1},},
                   {{-1,-1},{0,-1},{1,-1},},
                   {{1,1},{0,1},{-1,1},},
                   {{1,-1},{1,0},{1,1},},
                   {{-1,0},{-1,1},{-1,-1}} };
int nMask=0;

int  hMaskLen[8]={4,4,4,4,4,4,4,4};                //  击中模板长度
int  mMaskLen[8]={3,3,3,3,3,3,3,3};                //  击不中模板长度


int Nr[150][500][2];
int r =0;
int N = 0;


CImage* CMorphology::Erosion(CImage *pImage,int nMode)
{
    CImage* pDstImage = new CImage();

	int nWidth = pImage->GetWidth();
	int nHeight = pImage->GetHeight();

	int nBitsPerPixel = pImage->GetBPP();
	int nBytesPerPixel = nBitsPerPixel/8;
	pDstImage->Create(nWidth,nHeight,nBitsPerPixel,0);

    int (*p)[2] = EDMask;
	int nLen;
	switch(nMode)
	{
	case 0: nLen = 5;
		break;
	case 1: nLen = 9;
		break;
	case 2: nLen = 4;
		p = hMask[nMask];
		break;
	case 3: nLen = 3;
		p = mMask[nMask];
		break;
	}

	BYTE *Srcpixel,*Dstpixel;

	int i,j,k;
	for(i = 1; i < nWidth-1;i++)
	{
		for(j = 1; j < nHeight-1;j++)
		{
			Srcpixel = (BYTE*)pImage->GetPixelAddress(i,j);
			Dstpixel = (BYTE*)pDstImage->GetPixelAddress(i,j);
			*Dstpixel = *(Dstpixel+1) = *(Dstpixel+2) = 0;
			
			int nMin = 255;

			for(k = 0;k < nLen; k++)
			{
				//Srcpixel = (BYTE*)pImage->GetPixelAddress(i+EDMask[k][0],j+EDMask[k][1]);
				Srcpixel = (BYTE*)pImage->GetPixelAddress(i+*(*(p+k)+0),j+*(*(p+k)+1));
				if(*Srcpixel == 0)
				{
					break;
				}
				if(*Srcpixel < nMin)
				{
					nMin = *Srcpixel;
				}
			}
			if(k == nLen)
			{
				*Dstpixel = *(Dstpixel+1) = *(Dstpixel+2) = nMin;
			}
		}
	}
	return pDstImage;

}
CImage* CMorphology::Dilation(CImage *pImage,int nMode)
{
    CImage* pDstImage = new CImage();

	int nWidth = pImage->GetWidth();
	int nHeight = pImage->GetHeight();

	int nBitsPerPixel = pImage->GetBPP();
	int nBytesPerPixel = nBitsPerPixel/8;
	pDstImage->Create(nWidth,nHeight,nBitsPerPixel,0);

	int nLen;
	switch(nMode)
	{
	case 0: nLen = 5;
		break;
	case 1: nLen = 9;
		break;
	}

	BYTE *Srcpixel,*Dstpixel;

	int i,j,k;

	for(i = 1; i < nWidth-1;i++)
	{
		for(j = 1; j < nHeight-1;j++)
		{
			Srcpixel = (BYTE*)pImage->GetPixelAddress(i,j);
			Dstpixel = (BYTE*)pDstImage->GetPixelAddress(i,j);
			*Dstpixel = *(Dstpixel+1) = *(Dstpixel+2) = 0;
		
			int nMax = 0;

			for(k = 0;k < nLen ; k++)
			{
				Srcpixel = (BYTE*)pImage->GetPixelAddress(i+EDMask[k][0],j+EDMask[k][1]);

				if(*Srcpixel == 255)
				{
					break;
				}
				if(*Srcpixel > nMax)
				{
					nMax = *Srcpixel;
				}
			}
			if(k < nLen)
			{
				*Dstpixel = *(Dstpixel+1) = *(Dstpixel+2) = 255;
			}
			else
			{
				*Dstpixel = *(Dstpixel+1) = *(Dstpixel+2) = nMax;
			}
		}
	}
	return pDstImage;

}
CImage* CMorphology::Open(CImage *pImage,int nMode)
{
	 CImage* pDstImage;

	 pDstImage = Erosion(pImage,nMode);

	 pDstImage = Dilation(pDstImage,nMode);

	 return pDstImage;
}
CImage* CMorphology::Close(CImage *pImage,int nMode)
{
	 CImage* pDstImage;

	 pDstImage = Dilation(pImage,nMode);

	 pDstImage = Erosion(pDstImage,nMode);

	 return pDstImage;	 
}

CImage* CMorphology::InnerEdge(CImage *pImage,int nMode)
{
	 CImage* pDstImage;

	 pDstImage = Erosion(pImage,nMode);

	for(int i = 0; i < pImage->GetWidth();i++)
	{
		for(int j = 0; j < pImage->GetHeight();j++)
		{
			BYTE *Srcpixel = (BYTE*)pImage->GetPixelAddress(i,j);
			BYTE *Dstpixel = (BYTE*)pDstImage->GetPixelAddress(i,j);
			*Dstpixel = *Srcpixel - *Dstpixel;
			*(Dstpixel+1) = *(Srcpixel+1) - *(Dstpixel+1);
			*(Dstpixel+2) = *(Srcpixel+2) - *(Dstpixel+2);
			if(*Dstpixel<0) *Dstpixel=0;
			if(*(Dstpixel+1)<0) *(Dstpixel+1)=0;
			if(*(Dstpixel+2)<0) *(Dstpixel+2)=0;
		}
	}
	 return pDstImage;
}
CImage* CMorphology::OutterEdge(CImage *pImage,int nMode)
{
	 CImage* pDstImage;

	 pDstImage = Dilation(pImage,nMode);

	 for(int i = 0; i < pImage->GetWidth();i++)
	{
		for(int j = 0; j < pImage->GetHeight();j++)
		{
			BYTE *Srcpixel = (BYTE*)pImage->GetPixelAddress(i,j);
			BYTE *Dstpixel = (BYTE*)pDstImage->GetPixelAddress(i,j);
			*Dstpixel -= *Srcpixel;
			*(Dstpixel+1) -= *(Srcpixel+1);
			*(Dstpixel+2) -= *(Srcpixel+2);
			if(*Dstpixel<0) *Dstpixel=0;
			if(*(Dstpixel+1)<0) *(Dstpixel+1)=0;
			if(*(Dstpixel+2)<0) *(Dstpixel+2)=0;
		}
	}

	 return pDstImage;
}
CImage* CMorphology::MorphologyEdge(CImage *pImage,int nMode)
{
	 CImage* pDstImage1;
	 CImage* pDstImage2;

	 pDstImage1 = Dilation(pImage,nMode);

	 pDstImage2 = Erosion(pImage,nMode);

	 for(int i = 0; i < pDstImage1->GetWidth();i++)
	{
		for(int j = 0; j < pDstImage1->GetHeight();j++)
		{
			BYTE *Srcpixel = (BYTE*)pDstImage1->GetPixelAddress(i,j);
			BYTE *Dstpixel = (BYTE*)pDstImage2->GetPixelAddress(i,j);
			*Dstpixel = *Srcpixel - *Dstpixel;
			*(Dstpixel+1) = *(Srcpixel+1) - *(Dstpixel+1);
			*(Dstpixel+2) = *(Srcpixel+2) - *(Dstpixel+2);
			if(*Dstpixel<0) *Dstpixel=0;
			if(*(Dstpixel+1)<0) *(Dstpixel+1)=0;
			if(*(Dstpixel+2)<0) *(Dstpixel+2)=0;
		}
	}

	 return pDstImage2;
}

void CMorphology::OneDDilation(int * bitmap, int length)
{
	int * tempbitmap = new int[2*length];
	for(int j = 0; j < 2; j++)
		for(int i = 0; i < length; i++)
		{
			tempbitmap[i + j*length] = bitmap[i];
		}

	int num = length / 10;
	int * MySE = new int[num];
	for(int i = 0; i < num; i++)
		MySE[i] = 1;
	for(int i = 0; i < length; i++)
		bitmap[i] = 0;
	for(int x = 0; x < length; x++)  // A的长度
		for(int j = 0; j < num; j++)  // B的长度
		{
			if(tempbitmap[x + j] == 1)
			{
				bitmap[x] = 1;
				break;
			}
		}
	//fout << endl;
	//fout << "Dilation之后" << endl;

	//for(int i = 0; i < length; i++)
	//	fout << bitmap[i] << " ";
	//fout<< endl;
	delete tempbitmap, MySE;
}

void CMorphology::OneDErosion(int * bitmap, int length)
{
	int * tempbitmap = new int[2*length];
	for(int j = 0; j < 2; j++)
		for(int i = 0; i < length; i++)
		{
			tempbitmap[i + j*length] = bitmap[i];
		}
	int num = length / 10;
	int * MySE = new int[num];
	for(int i = 0; i < num; i++)
		MySE[i] = 1;
	for(int i = 0; i < length; i++)
		bitmap[i] = 1;
	for(int i = 0; i < 2*length; i++)
	{
		if(tempbitmap[i] == 1)
			tempbitmap[i] = 0;
		else
			tempbitmap[i] =1;
	}
	for(int x = 0; x < length; x++)  // A的长度
		for(int j = 0; j < num; j++)  // B的长度
		{
			if(tempbitmap[x + j] == 1)
			{
				bitmap[x] = 0;
				break;
			}
		}
	delete tempbitmap, MySE;
	//fout << endl;
	//fout << "Erosion之后" << endl;

	//for(int i = 0; i < length; i++)
	//	fout << bitmap[i] << " ";
	//fout<< endl;
}

void CMorphology::OneDClosing(int * bitmap, int length)
{
	this->OneDDilation(bitmap, length);
	this->OneDErosion(bitmap, length);
}

void CMorphology::OneDOpening(int * bitmap, int length)
{
	this->OneDErosion(bitmap, length);
	this->OneDDilation(bitmap, length);
}