#pragma once
class CImageOperate
{
public:
	CImageOperate(void);
	~CImageOperate(void);
public:
	void calhistogram(CImage *, int *);
	CImage * CreateHistogram(int *);
	int calotsuThreshold(int *);
	void calotsuTwoThreshold(int *,int &T1, int &T2); // otsuË«ãÐÖµ
	int calentropyThreshold(int *);
	
	void ToBinary(CImage *, int);
	double *  Gussianfilter();
	double *   Medianfilter();
	double *   SobelKernel();
	double *   PrewittKernel();
	int *   LaplaceKerner();
	void calconvolution(CImage *, int, int *);
	void calconvolution(double **, int, double *, int, int);
};

