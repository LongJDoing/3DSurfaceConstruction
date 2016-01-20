#pragma once

#include "Morphology.h"
class CMorphology 
{
public:
	CMorphology(void);
	~CMorphology(void);

	CImage* Erosion(CImage *pImage,int nMode);
	CImage* Dilation(CImage *pImage,int nMode);
	CImage* Open(CImage *pImage,int nMode);
	CImage* Close(CImage *pImage,int nMode);

	CImage* InnerEdge(CImage *pImage,int nMode);
	CImage* OutterEdge(CImage *pImage,int nMode);
	CImage* MorphologyEdge(CImage *pImage,int nMode);
	
	void OneDDilation(int *, int);
	void OneDErosion(int *, int);
	void OneDOpening(int *, int);
	void OneDClosing(int *, int);

};

