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
	void f_y(double *, double *, double *, double *);    //计算向量函数的因变量向量
	void f_Jacobian(double *, double **, double *, double *);  //计算雅克比矩阵
	void inv_Jacobian(double **, double **); //计算雅克比矩阵的逆矩阵
	void newtonsolution(double *, double **, double *, double *); //由近似解向量 x0 计算近似解向量 x1
};

#endif