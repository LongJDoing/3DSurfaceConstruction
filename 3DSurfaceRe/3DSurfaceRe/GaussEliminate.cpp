#include "StdAfx.h"
#include "GaussEliminate.h"


CGaussEliminate::CGaussEliminate(void)
{
}


CGaussEliminate::~CGaussEliminate(void)
{
}

void CGaussEliminate::Eliminate(double **a, double *b, int n)
{
	int i,j,l;
	double p,q,max;
	for(l = 0; l < n-1; l++)
	{
		max = fabs(a[l][l]);                //调用绝对值函数，选出绝对值最大者
		j=l;
		for(i=l;i<n;i++)
			if(max<fabs(a[i][l]))                      
			{
				max = fabs(a[i][l]);
				j = i;
			}
			for(i=l;i<n;i++)                           //交换系数行
			{
				p = a[l][i];
				a[l][i] = a[j][i];
				a[j][i] = p;
			}
		p=b[l];                                     //交换常数行
		b[l]=b[j];
		b[j]=p;
        for(i = l+1; i < n; i++)                           //消元计算
		{
			q = a[i][l] / a[l][l];
			for(j = l; j < n; j++)
				a[i][j] = double(a[i][j] - q * a[l][j]);  //消元后的系数矩阵
			b[i] -= q * b[l];                           //消元后的常数矩阵
		}		
	}
}

void CGaussEliminate::Rewind(double **a, double *b, double *x, int n)
{
	double p;
	int i,j;
	x[n-1]=b[n-1]/a[n-1][n-1];                             
	i=n-2;
	while(i>=0)
	{
		p=0;
		j=i+1;
		while(j<n)
		{
		p+=a[i][j]*x[j];
		x[i]=(b[i]-p)/a[i][i];
		j++;
		}
		i--;
	}
}
void CGaussEliminate::aa()
{
	int a = 1;
}