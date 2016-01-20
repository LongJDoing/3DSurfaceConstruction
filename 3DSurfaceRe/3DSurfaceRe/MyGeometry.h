#pragma once
#include "MyDIdefine.h"
#include "MyNewtonMethod.h"
#include "GaussEliminate.h"

class CGaussEliminate;
class CMyGeometry
{
public:
	CMyGeometry(void);
	~CMyGeometry(void);
public:
	// 自定义的空间的几何操作
	double * ConvertCameraImageCoordinateToWordCoordinate(double *);
	double * ConvertCameraImageCoordinateToCameraCoordinate(int * );
	int * ConvertWordCoordinateToCameraImageCoordinate(double *, bool);
	double * ConvertWordCoordinateToCameraCoordinate(double *);
	double * ConvertCameraCoordinateToCameraImageCoordinate(double *, bool);
	int ** GetProjectionSamplePoint(int *, CPoint, int, int, int *); // 得到投影仪的采样点，用于投影仪校准
	double * GetPrjectionSmaplePointAbsolutePhase(double *,int *,  int **, int, int, int, bool);
	double  GetPointAbsolutePhase(double *, int *, int, int);  //得到任一点的绝对相位值
	int * GetAbsolutePhaseCorrespondPoint(double *, int *, double **, int, int, int, bool); 
	int ** GetAbsolutePhaseCorrespondPoint(double *, double *,int *,  double **, int ,int ,int);
	double * FindIntersectionOfLineAndReferenceplane(double *, double *, double); 
	int DeleteBadPoint(int, int **, int **, double **, double **);
	double * GetCameraCenterWordCoordinate();
	double * FindNI(double *, double, int ,int, double * , double *, int, int *); // 使用的


	double * FindNI(double *, double, int , int, double *, double *, double, double, double, double, double, double, int);
	double * FindVerticalLineMid_point(double *, double *, double *, double *);
	double * Calibrate3DDeterminant(double *, double *);
	double * ConvertCameraCoordinateToWordCoordinate(double *);
public:
	// 类变量
	CGaussEliminate *m_gausseliminate;
	CMyNewtonMethod * m_mynewtonmethod;
};

