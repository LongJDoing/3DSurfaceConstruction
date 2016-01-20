#include "StdAfx.h"
#include "MyNewtonMethod.h"


CMyNewtonMethod::CMyNewtonMethod(void)
{
}


CMyNewtonMethod::~CMyNewtonMethod(void)
{
}

/*==============================================================
Name:	f_y
Desc:   
Param: 输入初值 *x
Return:  *y
Note: 
  --------------------------------------------------------------*/
void CMyNewtonMethod::f_y(double *x, double * y, double *distortion, double * imagecoordinate)
{
	double drtemp;
	drtemp = x[0] * x[0] + x[1] * x[1];
	y[0] = x[0]*(1 + distortion[0] * drtemp + distortion[1] * drtemp * drtemp) + 2*distortion[2]*x[0]*x[1] + 
		distortion[3]*(drtemp + 2 * x[0] *x[0]) - imagecoordinate[0];
	y[1] = x[1]*(1 + distortion[0] * drtemp + distortion[1] * drtemp * drtemp) + distortion[2]*(drtemp + 2*x[1]*x[1]) + 
		2*distortion[3]*x[0]*x[1] - imagecoordinate[1];

}

/*==============================================================
Name:	f_Jacobian
Desc:   
Param: 
Return:  返回雅克比矩阵
Note: 
  --------------------------------------------------------------*/
void CMyNewtonMethod::f_Jacobian(double *x, double ** jacobian, double *distortion, double * imagecoordinate)
{
	double xtemp, ytemp;
	xtemp = x[0];
	ytemp = x[1];

	//计算雅克比矩阵的值，即求偏导数
	jacobian[0][0] = 5*distortion[1]*xtemp*xtemp*xtemp*xtemp + 3*distortion[0]*xtemp*xtemp + 6*distortion[1]*xtemp*xtemp*ytemp*ytemp + 
		6*distortion[3]*xtemp + distortion[0]*ytemp*ytemp + distortion[1]*ytemp*ytemp*ytemp*ytemp + 1 + 2*distortion[2]*ytemp;
	jacobian[0][1] = 4*distortion[1]*xtemp*xtemp*xtemp*ytemp + 2*distortion[0]*xtemp*ytemp + 4*distortion[1]*xtemp*ytemp*ytemp*ytemp*ytemp +
		2*distortion[1]*xtemp + 2*distortion[3]*ytemp;
	jacobian[1][0] = 4*distortion[1]*xtemp*ytemp*ytemp*ytemp + 2*distortion[0]*xtemp*ytemp + 4*distortion[1]*xtemp*xtemp*xtemp*ytemp + 2*distortion[3]*ytemp
		+ 2*distortion[2]*xtemp;
	jacobian[1][1] = 5*distortion[1]*ytemp*ytemp*ytemp*ytemp + 3*distortion[0]*ytemp*ytemp + 6*distortion[2]*ytemp + distortion[0]*xtemp*xtemp + 1 + 
		distortion[1]*xtemp*xtemp*xtemp*xtemp + 2*distortion[2]*xtemp;
}

/*==============================================================
Name:	inv_Jacobian
Desc:   
Param: 
Return:  返回雅克比矩阵的逆矩阵
Note: 
  --------------------------------------------------------------*/
void CMyNewtonMethod::inv_Jacobian(double ** jacobian, double ** invjacobin)
{
	double aug[N][N2],L;
	int i,j,k;
	for (i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
			aug[i][j]=jacobian[i][j];
	    for(j=N;j<N2;j++)
			if(j==i+N) aug[i][j]=1;
			else  aug[i][j]=0;
	}
	for (i=0;i<N;i++)
	{
	  for (k=i+1;k<N;k++)
	  {
		  L=-aug[k][i]/aug[i][i];
		  for(j=i;j<N2;j++)
			  aug[k][j]=aug[k][j]+L*aug[i][j];
	  }
	}
	for (i=N-1;i>0;i--)
	{  
		for (k=i-1;k>=0;k--)
		{
			L=-aug[k][i]/aug[i][i];
			for(j=N2-1;j>=0;j--)
				aug[k][j]=aug[k][j]+L*aug[i][j];
		}
	}
	for (i=N-1;i>=0;i--)
	   for(j=N2-1;j>=0;j--)
		   aug[i][j]=aug[i][j]/aug[i][i];
	for (i=0;i<N;i++)
	   for(j=N;j<N2;j++)
		   invjacobin[i][j-N]=aug[i][j];
}

/*==============================================================
Name:	newtonsolution
Desc:   
Param: 
Return:  迭代求解新的值
Note: 
  --------------------------------------------------------------*/
void CMyNewtonMethod::newtonsolution(double *oldx, double **invjacobian, double *oldy, double * newx)
{
	int i,j;
	double sum = 0.0;
	
	for(i=0;i<N;i++)
	{
		sum=0;
		  for(j=0;j<N;j++)
			  sum = sum + invjacobian[i][j] * oldy[j];
		newx[i]=oldx[i]-sum;
	}
}