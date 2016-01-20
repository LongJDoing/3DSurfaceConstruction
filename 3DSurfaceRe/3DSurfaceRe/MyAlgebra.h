#pragma once
//����һ������������
class CMyAlgebra
{
public:
	CMyAlgebra(void);
	~CMyAlgebra(void);
	double CalculateMean(double **, int *, int, int, int, int);
	double CalculateVariance(double **, int *, int, int, int, int);
//	int  FindCentralPosition(unsigned char *, int *, int, int, int, int);
	int CalculateArea(int *, int, int, int);
	CPoint CalculateCenterPoint(int *, int, int, int, int);

public:
	double m_Mean;
	double m_Variance;
	int m_CentralPosition;
	int m_MaxArea;

};

