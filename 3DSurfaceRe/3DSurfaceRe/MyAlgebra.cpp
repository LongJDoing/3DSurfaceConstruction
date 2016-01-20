#include "StdAfx.h"
#include "MyAlgebra.h"
#include <math.h>

CMyAlgebra::CMyAlgebra(void)
{
}


CMyAlgebra::~CMyAlgebra(void)
{
}

double CMyAlgebra::CalculateMean(double ** values, int *labelmap, int width, int height, int maxarea, int labelIndex)
{
	m_Mean = 0.0;
	for(int i = 0; i < width*height; i++)
	{
		if(labelmap[i] == labelIndex)
			m_Mean += (double)values[i%width][i/width] / maxarea;
	}
	return m_Mean;
}

double CMyAlgebra::CalculateVariance(double **values, int *labelmap, int width, int height, int maxarea, int labelIndex)
{
	m_Variance = 0.0;
	double m_Mean = CalculateMean(values, labelmap, width, height, maxarea, labelIndex);
	for(int i = 0; i < width*height; i++)
	{
		if(labelmap[i] == labelIndex)
			m_Variance += (double)(((values[i%width][i/width]-m_Mean)*(values[i%width][i/width]-m_Mean)) / maxarea);
	}
	return sqrt(m_Variance);
}

int CMyAlgebra::CalculateArea(int *labelmap, int width, int height, int labelIndex)
{
	int Area = 0;
	for(int i = 0; i < width * height; i++)
	{
		if(labelmap[i] == labelIndex)
			Area++;
	}
	return Area;
}

CPoint CMyAlgebra::CalculateCenterPoint(int *labelmap, int width, int height, int labelIndex,  int maxarea)
{
	CPoint  CenterPoint ;
	for(int cx = 0; cx < width; cx++)
		for(int cy = 0; cy < height; cy++)
		{
			if(labelmap[cx + cy*width] == labelIndex)
			{
				CenterPoint.x  += cx;
				CenterPoint.y += cy;
			}
		}
	CenterPoint.x = CenterPoint.x / maxarea;
	CenterPoint.y  = CenterPoint.y / maxarea;

	return CenterPoint; 
}