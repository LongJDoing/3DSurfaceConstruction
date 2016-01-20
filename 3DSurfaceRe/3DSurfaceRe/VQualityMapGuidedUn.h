#pragma once
#include "queue.h"
#include "MyDIdefine.h"

class CVQualityMapGuidedUn
{
public:
	CVQualityMapGuidedUn(void);
	~CVQualityMapGuidedUn(void);
public:
	void PushQueue(Queue *, int );
	int PopQueue(Queue *);
	double LineScan(double, double, double, CPoint, CPoint);
	void ScanPhaseMap(double *, int *, int, int, CPoint, CPoint, Queue *, double *,int);
	double * UnwrapPhaseMap(double *, int *, int, int, CPoint, CPoint);
	void BackUnwrap(double *, int *, int, int, CPoint, Queue *, double *);
	CPoint FindStartPosition(double * , int * , CPoint , int , int);
};

