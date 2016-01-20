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
	// �Զ���Ŀռ�ļ��β���
	double * ConvertCameraImageCoordinateToWordCoordinate(double *);
	double * ConvertCameraImageCoordinateToCameraCoordinate(int * );
	int * ConvertWordCoordinateToCameraImageCoordinate(double *, bool);
	double * ConvertWordCoordinateToCameraCoordinate(double *);
	double * ConvertCameraCoordinateToCameraImageCoordinate(double *, bool);
	int ** GetProjectionSamplePoint(int *, CPoint, int, int, int *); // �õ�ͶӰ�ǵĲ����㣬����ͶӰ��У׼
	double * GetPrjectionSmaplePointAbsolutePhase(double *,int *,  int **, int, int, int, bool);
	double  GetPointAbsolutePhase(double *, int *, int, int);  //�õ���һ��ľ�����λֵ
	int * GetAbsolutePhaseCorrespondPoint(double *, int *, double **, int, int, int, bool); 
	int ** GetAbsolutePhaseCorrespondPoint(double *, double *,int *,  double **, int ,int ,int);
	double * FindIntersectionOfLineAndReferenceplane(double *, double *, double); 
	int DeleteBadPoint(int, int **, int **, double **, double **);
	double * GetCameraCenterWordCoordinate();
	double * FindNI(double *, double, int ,int, double * , double *, int, int *); // ʹ�õ�


	double * FindNI(double *, double, int , int, double *, double *, double, double, double, double, double, double, int);
	double * FindVerticalLineMid_point(double *, double *, double *, double *);
	double * Calibrate3DDeterminant(double *, double *);
	double * ConvertCameraCoordinateToWordCoordinate(double *);
public:
	// �����
	CGaussEliminate *m_gausseliminate;
	CMyNewtonMethod * m_mynewtonmethod;
};

