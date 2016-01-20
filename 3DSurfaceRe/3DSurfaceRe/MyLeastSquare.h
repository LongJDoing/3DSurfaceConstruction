#pragma once
#include "MyDIdefine.h"
class CMyLeastSquare
{
public:
	CMyLeastSquare(void);
	~CMyLeastSquare(void);
	void transpose(double *, int, int, double *);
	void trmul(double *, double *, int ,int, int k, double * );
	int chlk(double *, int, int, double *);
	double * fun(double *, double *, int, int);
};


