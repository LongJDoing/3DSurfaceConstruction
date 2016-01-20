#ifndef MYNEWTONMETHOD_H
#define MYNEWTONMETHOD_H
#include "MyDIdefine.h"
#pragma once
#include <math.h>

class CMyNewtonMethod
{
public:
	CMyNewtonMethod(void);
	~CMyNewtonMethod(void);
	void f_y(double *, double *, double *, double *);    //�����������������������
	void f_Jacobian(double *, double **, double *, double *);  //�����ſ˱Ⱦ���
	void inv_Jacobian(double **, double **); //�����ſ˱Ⱦ���������
	void newtonsolution(double *, double **, double *, double *); //�ɽ��ƽ����� x0 ������ƽ����� x1
};

#endif