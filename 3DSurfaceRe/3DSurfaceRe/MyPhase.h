#pragma once

#include "MyDIdefine.h"
#include "Morphology.h"
#include "ConnectComponentLabel.h"
#include "MyAlgebra.h"
#include "VQualityMapGuidedUn.h"
#include "HQualityMapGuidedUn.h"

class CMyPhase
{
public:
	CMyPhase(void);
	~CMyPhase(void);
	double * CreatePhaseMap(CImage **, int, int);
	CImage * CreateQualityMap1(CImage **, int, int, bool);
	double ** CreateQualityMap2(double *, int, int);
	int * StratifyQualityMap(CImage *, double **, int, int);
	double * UnwrapPhaseMap(double *, int *, int, int, bool, CPoint);
	double  myLineScan(double, double);
public:
	CMorphology *m_pMorphology;
	CConnectComponentLabel *m_pConnectComponentLabel;
	CMyAlgebra * m_pMyAlgebra;
	CVQualityMapGuidedUn  * m_pVQualityMapGuidedUn;
	CHQualityMapGuidedUn  * m_pHQualityMapGuidedUn;
public:
	CPoint centerpoint;
	CPoint startpoint;
};

