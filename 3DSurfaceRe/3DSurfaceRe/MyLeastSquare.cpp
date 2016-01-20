#include "StdAfx.h"
#include "MyLeastSquare.h"


CMyLeastSquare::CMyLeastSquare(void)
{
}


CMyLeastSquare::~CMyLeastSquare(void)
{
}

//��a�����ת�ã�
//�����������aΪm��n�ף����������n��m�׾���b�
void CMyLeastSquare::transpose(double  * a, int m, int n, double * b)
{
	int i,j;
	for (i=0; i<n; i++)
		for(j=0; j<m; j++)
		{
//			s = a[j*n+i];
//			b[i*m+j] = s;
			b[i*m+j] = a[j*n+i];
		}
}



//������ˣ�
//m��n�׵ľ���a��n��k�׵ľ���b��ˣ��õ�m��k�׵ľ��󱣴���c�У�
void CMyLeastSquare::trmul(double * a, double  * b, int m, int n, int k, double  * c)
{	
	int i,j,l,u;
	for (i=0; i<=m-1; i++)
		for (j=0; j<=k-1; j++)
		{
			u=i*k+j; 
			c[u]=0;
			for (l=0; l<=n-1; l++)
				c[u]=c[u]+a[i*n+l]*b[l*k+j];
		}
	return;
}


//ƽ��������Cholesky������ʵ�����ԳƷ�����Ľ⣻
//����n��n�������Գ�ϵ������a��n��m�׳�������
//���طֽ���U���������ǲ��ִ���a�����̵�m�����������d��
int CMyLeastSquare::chlk(double * a, int n, int m, double * d)
{
	int i,j,k,u,v;
	if ((a[0]+1.0==1.0)||(a[0]<0.0))
//	if (a<0)
	{ 
		//printf("fail\n"); 
		return(false);
	}
	a[0]=sqrt(a[0]);
	for (j=1; j<=n-1; j++) a[j]=a[j]/a[0];
	for (i=1; i<=n-1; i++)
	{
		u=i*n+i;
		for (j=1; j<=i; j++)
		{ 
			v=(j-1)*n+i;
			a[u]=a[u]-a[v]*a[v];
		}
		if ((a[u]+1.0==1.0)||(a[u]<0.0))
		{ 
			//printf("fail\n"); 
			return(false);
		}
		a[u]=sqrt(a[u]);
		if (i!=(n-1))
		{ 
			for (j=i+1; j<=n-1; j++)
			{ 
				v=i*n+j;
				for (k=1; k<=i; k++)
					a[v]=a[v]-a[(k-1)*n+i]*a[(k-1)*n+j];
					a[v]=a[v]/a[u];
			}
		}
	}
	for (j=0; j<=m-1; j++)
	{ 
		d[j]=d[j]/a[0];
		for (i=1; i<=n-1; i++)
		{ 
			u=i*n+i; 
			v=i*m+j;
			for (k=1; k<=i; k++)
				d[v]=d[v]-a[(k-1)*n+i]*d[(k-1)*m+j];
				d[v]=d[v]/a[u];
		}
	}
	for (j=0; j<=m-1; j++)
	{
		u=(n-1)*m+j;
		d[u]=d[u]/a[n*n-1];
		for (k=n-1; k>=1; k--)
		{ 
			u=(k-1)*m+j;
			for (i=k; i<=n-1; i++)
			{ 
				v=(k-1)*n+i;
				d[u]=d[u]-a[v]*d[i*m+j];
			}
			v=(k-1)*n+k-1;
			d[u]=d[u]/a[v];
		}
	}
	return(true);
}


//�󳬶����̵���С���˽�
//����m��n��ϵ������r��m��1�׳�������p��
//����ֵΪn��1�׽�������
double * CMyLeastSquare::fun(double * r, double * p, int m, int n)
{
    int i,j;
	double *R = new double[m*n];
	double *P = new double[m*1];
	double *RT = new double[n*m];
	double *a = new double[n*n];
	double *b = new double[m*1];
	double *Q = new double[n*1];

	for (i=0; i<m*n; i++)
	{
		R[i] = r[i];
	}
	for (j=0; j<m; j++)	
		P[j] = p[j];
	
    transpose(R, m, n, RT);
	trmul(RT, R, n, m, n, a);
	trmul(RT, P, n, m, 1, b);
    int flag = chlk(a, n, 1, b);

	//if (!flag)
	//	return NULL;
	//else
	for (i=0; i<n; i++)
		Q[i] = (double)b[i];

	delete R;
	delete P;
	delete RT;
	delete a;
	delete b;

	return Q;
}