#include "StdAfx.h"
#include "MyGeometry.h"
#include <fstream>
#include <iostream>

using namespace std;
CMyGeometry::CMyGeometry(void)
{
	m_gausseliminate = new CGaussEliminate();
	m_mynewtonmethod = new CMyNewtonMethod();
	//m_gausseliminate->aa();
}


CMyGeometry::~CMyGeometry(void)
{
	//delete m_gausseliminate;
//	delete m_mynewtonmethod;
}

/*==============================================================
Name:	GetProjectionSamplePoint
Desc:   
Param: 
Return:  һ������������ֵ
Note: ���ƽ��1�Ĳ�����
  --------------------------------------------------------------*/
int ** CMyGeometry::GetProjectionSamplePoint(int * labelmap, CPoint startpoint, int width, int height, int * mynum)
{
	int num = 0;
	for(int cx = startpoint.x - 120; cx <= startpoint.x + 120;)
	{
		for(int cy = startpoint.y - 120 ; cy <= startpoint.y + 120;)
		{
			if((labelmap[startpoint.x + startpoint.y * width] != 0)
				&&((cx >= 0)&&(cx <= width))&&((cy >= 0)&&(cx <= height)))
				num++;
			cy += 20;
		}
		cx += 20;
	}
	int ** plane1samplepoint = new int*[num];
	for(int i = 0; i < num; i++)
		plane1samplepoint[i] = new int[2];
	int i = 0;
	for(int cx = startpoint.x - 120 ; cx <= startpoint.x + 120;)  //�˴�ҲҪ�޸�
	{
		for(int cy = startpoint.y -120; cy <= startpoint.y + 120;)
		{
			if((labelmap[startpoint.x + startpoint.y * width] != 0)
				&&((cx >= 0)&&(cx <= width))&&((cy >= 0)&&(cx <= height)))
			{
				plane1samplepoint[i][0] = cx;
				plane1samplepoint[i][1] = cy;
				cy += 20;
				i++;
			}
		}
		cx += 20;
	}
	mynum[0] = num;
	return plane1samplepoint;

}
/*==============================================================
Name:	GetPrjectionSmaplePointAbsolutePhase
Desc:   
Param: 
Return:  һ�����������Ӧ�ľ�����λ
Note: ���Ӧ��ͶӰУ׼ʱ���Ҿ�����λֵ,��ΪУ׼��Ϊƽ��壬
      ����ȡƽ��ֵ���׼ȷ
  --------------------------------------------------------------*/
double * CMyGeometry::GetPrjectionSmaplePointAbsolutePhase(double * referenceabsolutephasemap, int * labelmap, 
	int ** projectionsamplepoint, int num, int width, int height, bool direction)
{
	double * projectionsamplepointabsolutephase = new double[num];
	if(direction) // ��ֱ�����դ
	{
		double * uabsolutephase = new double[width];
		int * unum = new int[width];
		for(int i = 0; i < width; i++)
		{
			uabsolutephase[i] = 0.0;
			unum[i] = 0;
		}
		for(int cx = 0; cx < width; cx++)
		{
			for(int cy = 0; cy < height; cy++)
				if(labelmap[cx + cy*width] != 0)
				{
					uabsolutephase[cx] += referenceabsolutephasemap[cx + cy*width];
					unum[cx]++;
				}
		}
		for(int i = 0; i < width; i++)
			uabsolutephase[i] /= unum[i];
		for(int i = 0; i < num; i++)
			projectionsamplepointabsolutephase[i] = uabsolutephase[projectionsamplepoint[i][0]];
		delete uabsolutephase;
		delete unum;
	}                                       
	else // ˮƽ�����դ
	{
		double * vabsolutephase = new double[height];
		int * vnum = new int[height];
		for(int i = 0; i < height; i++)
		{
			vabsolutephase[i] = 0.0;
			vnum[i] = 0;
		}
		for(int cy = 0; cy < height; cy++)
		{
			for(int cx = 0; cx < width; cx++)
				if(labelmap[cx + cy*width] != 0)
				{
					vabsolutephase[cy] += referenceabsolutephasemap[cx + cy*width] ;
					vnum[cy]++;
				}
		}
		for(int i = 0; i < height; i++)
			vabsolutephase[i] /= vnum[i];
		for(int i = 0; i < num; i++)
			projectionsamplepointabsolutephase[i] = vabsolutephase[projectionsamplepoint[i][1]];		
		delete vabsolutephase, vnum;
	}
	return projectionsamplepointabsolutephase;
}
/*==============================================================
Name:	GetPrjectionSmaplePointAbsolutePhase
Desc:   
Param: 
Return:  һ�����������Ӧ�ľ�����λ
Note: ���Ӧ��ͶӰУ׼ʱ���Ҿ�����λֵ,��ΪУ׼��Ϊƽ��壬
      ����ȡƽ��ֵ���׼ȷ
  --------------------------------------------------------------*/
double  CMyGeometry::GetPointAbsolutePhase(double * absolutephasemap, int * point, int width, int height)
{
	double  pointabsolutephase  = 0.0 ;
	pointabsolutephase = absolutephasemap[point[0] + point[1] * width]; // ���ͼ��
	return pointabsolutephase;

}
/*==============================================================
Name:	GetAbsolutePhaseCorrespondPoint
Desc:   ���դ������ƽ������ˮƽ�ģ����ߴ�ֱ��
Param: 
Return:  ������λֵ����Ӧƽ��ƽ��2������
Note: ���Ӧ��ͶӰУ׼ʱ��ͨ��ƽ��1�����㣬���㵽�ľ�����λֵ���ҵ�
      ��Ӧ��ƽ��2��ͬ��λֵ�ĵ������
  --------------------------------------------------------------*/
int * CMyGeometry::GetAbsolutePhaseCorrespondPoint(double * referenceabsolutephasemap, int * labelmap,
	double ** projectionsamplepointabsolutephase, int num, int width, int height, bool direction)
{
	int * projectionsamplepointcorrespondpoint = new int[num];
	if(direction) // ��ֱ�����դ
	{
		double * uabsolutephase = new double[width];
		int * unum = new int[width];
		for(int i = 0; i < width; i++)
		{
			uabsolutephase[i] = 0.0;
			unum[i] = 0;
		}
		for(int cx = 0; cx < width; cx++)
		{
			for(int cy = 0; cy < height; cy++)
				if(labelmap[cx + cy*width] != 0)
				{
					uabsolutephase[cx] += referenceabsolutephasemap[cx + cy*width];
					unum[cx]++;
				}
		}
		
		for(int i = 0; i < width; i++)
		{
			uabsolutephase[i] /= unum[i];
		}

		for(int i = 0; i < num; i++)
			for(int cx = 0; cx < width; cx++)
				if(fabs(uabsolutephase[cx] - projectionsamplepointabsolutephase[i][0]) < 2.0e-2)
				{
					projectionsamplepointcorrespondpoint[i] = cx;
					break;
				}
				else
				{
					projectionsamplepointcorrespondpoint[i] = 0;
				}
			
		delete uabsolutephase, unum;
	}
	else // ˮƽ�����դ
	{
		double * vabsolutephase = new double[height];
		int * vnum = new int[height];
		for(int i = 0; i < height; i++)
		{
			vabsolutephase[i] = 0.0;
			vnum[i] = 0;
		}
		for(int cy = 0; cy < height; cy++)
		{
			for(int cx = 0; cx < width; cx++)
				if(labelmap[cx + cy*width] != 0)
				{
					vabsolutephase[cy] += referenceabsolutephasemap[cx + cy*width] ;
					vnum[cy]++;
				}
		}
		for(int i = 0; i < height; i++)
			vabsolutephase[i] /= vnum[i];
		for(int i = 0; i < num; i++)
			for(int cy = 0; cy < height; cy++)
				if(fabs(vabsolutephase[cy] - projectionsamplepointabsolutephase[i][1]) < 2.0e-2)
				{
					projectionsamplepointcorrespondpoint[i] = cy;
					break;
				}
				else
				{
					projectionsamplepointcorrespondpoint[i] = 0;
				}
		delete vabsolutephase, vnum;
	}
	return projectionsamplepointcorrespondpoint;

}
/*==============================================================
Name:	GetAbsolutePhaseCorrespondPoint
Desc:   
Param: һ���������ˮƽ���ߴ�ֱ
Return:  ������λֵ����Ӧƽ��ƽ��2������
Note: ���Ӧ��ͶӰУ׼ʱ��ͨ��ƽ��1�����㣬���㵽�ľ�����λֵ���ҵ�
      ��Ӧ��ƽ��2��ͬ��λֵ�ĵ������
  --------------------------------------------------------------*/
int ** CMyGeometry::GetAbsolutePhaseCorrespondPoint(double * referenceVabsolutephasemap, double * referenceHabsolutephasemap,int * labelmap,
	double ** projectionsamplepointabsolutephase, int num, int width, int height)
{
	int ** projectionsamplepointcorrespondpoint = new int*[num];
	for(int i = 0; i < num; i++)
		projectionsamplepointcorrespondpoint[i] = new int[2];

	double ** min = new double*[num];
	for(int i = 0; i < num; i++)
		min[i] = new double[2];
	for(int i = 0; i < num; i++)
	{
		min[i][0] = 0.2;
		min[i][1] = 0;
	}
	for(int i = 0; i < num; i++)
		for(int j = 0 ; j < width*height; j++)
		{
			if(labelmap[j] == 1)
			{
				double vtemp = fabs(referenceVabsolutephasemap[j] - projectionsamplepointabsolutephase[i][0]);
				double htemp = fabs(referenceHabsolutephasemap[j] - projectionsamplepointabsolutephase[i][1]);
		
				if((vtemp <= 2.0e-1)&&(htemp <= 2.0e-1))
				{
					if(min[i][0] > (vtemp + htemp))
					{
						min[i][0] = vtemp + htemp;
						min[i][1] = j;
					}
				}			
			}
		}
	
	for(int i = 0; i < num; i++)
	{
		int a = int(min[i][1] +0.5);
		projectionsamplepointcorrespondpoint[i][0] = a % width;
		projectionsamplepointcorrespondpoint[i][1] = a / width;
	}
	for(int i = 0; i < num; i++)
		delete []min[i];
	delete []min;
	return projectionsamplepointcorrespondpoint;
}
/*==============================================================
Name:	GetAbsolutePhaseCorrespondPoint
Desc:   
Param: 
Return:  ������λֵ����Ӧƽ��ƽ��2������
Note: ���Ӧ��ͶӰУ׼ʱ��ͨ��ƽ��1�����㣬���㵽�ľ�����λֵ���ҵ�
      ��Ӧ��ƽ��2��ͬ��λֵ�ĵ������
  --------------------------------------------------------------*/
int CMyGeometry::DeleteBadPoint(int length, int ** plane_1samplepoint, int ** plane_2samplepoint, double ** newplane_1samplepoint, double ** newplane_2samplepoint)
{
	//for(int k =0 ;k < 2; k++)
	//	for(int i = 1; i < length; i++)
	//		for(int j = 0; j < i; j++)
	//			if(plane_2samplepoint[i][k] == plane_2samplepoint[j][k])
	//				plane_2samplepoint[i][k] = 0;
	int mylength;
	mylength = 0;
 	for(int i = 0; i < length; i++ )
	{
		if((plane_2samplepoint[i][0] != 0)&&(plane_2samplepoint[i][1] != 0))
			mylength++;
	}
	int m = 0;
	for(int i = 0; i < length; i++)
	{
		if((plane_2samplepoint[i][0] !=0)&&(plane_2samplepoint[i][1] != 0))
		{
			newplane_1samplepoint[m][0] = plane_1samplepoint[i][0];
			newplane_1samplepoint[m][1] = plane_1samplepoint[i][1];
			newplane_2samplepoint[m][0] = plane_2samplepoint[i][0];
			newplane_2samplepoint[m][1] = plane_2samplepoint[i][1];
			m++;
		}
	}
	return mylength;
}
/*==============================================================
Name:	ConvertCameraImageCoordinateToWordCoordinate
Desc:   
Param: 
Return:  �ռ�����
Note:  �Բο��潨������������ϵ�У�����������ڲ����Ͳο��潨��������ϵ���������
       �������ƽ�������ص������ת������������ϵ�е�����(������������꣬��λ�������ƽ���ϵĵ���������꣬����Z����ܺü���)
  --------------------------------------------------------------*/
double * CMyGeometry::ConvertCameraImageCoordinateToWordCoordinate(double * cameraimagecoordinate)
{
	double * tempcoordinate = new double[2];
	// Step 1...
	tempcoordinate[0] = (cameraimagecoordinate[0] - m_CameraVector[2]) / m_CameraVector[0];
	tempcoordinate[1] = (cameraimagecoordinate[1] - m_CameraVector[3]) / m_CameraVector[1];

	//Step 2... ת�����������ϵ
	int iter = 0;
	double error = 0.0;
	double * coordinatey = new double[2]; //�����
	double * coordinateoldx = new double[2];  //�Ա���X,��ֵ
	double * coordinatenewx = new double[2];  //�Ա���X�����ش�ֵ
	for(int i = 0; i < 2; i++)
	{
		coordinatey[i] = 0.0;
		coordinateoldx[i] = tempcoordinate[i];
	}
	double ** jacobian =  new double*[2];
	double ** invjacobian = new double*[2];
	for(int i = 0; i < 2; i++)
	{
		jacobian[i] = new double[2];
		invjacobian[i] = new double[2];
	}
	bool Isfoud = false;
	while(iter < Max) //����У��
	{
		iter++;
		m_mynewtonmethod->f_y(coordinateoldx, coordinatey,  m_Distortion, tempcoordinate); //�����������ֵ
		m_mynewtonmethod->f_Jacobian(coordinateoldx, jacobian, m_Distortion, tempcoordinate); //�����ſ˱Ⱦ���
		m_mynewtonmethod->inv_Jacobian(jacobian, invjacobian); // �����ſ˱Ⱦ������
		m_mynewtonmethod->newtonsolution(coordinateoldx, invjacobian, coordinatey, coordinatenewx); //��������µ�x

		error = 0.0;
		for(int i = 0; i < 2; i++)
			error += fabs(coordinatenewx[i] - coordinateoldx[i]); 
		if(error < Epsilon) 
		{
			Isfoud = true;
			break;
		}
		for(int i = 0; i < 2; i++)
			coordinateoldx[i] = coordinatenewx[i];
	}
	if(!Isfoud)
		for(int i = 0; i < 2; i++)
		{
			coordinatenewx[i] = tempcoordinate[i];
		}

	for(int i = 0; i < 2; i++)
	{
		delete []jacobian[i];
		delete []invjacobian[i];
	}
	delete []jacobian;
	delete []invjacobian;
	delete tempcoordinate;
	delete coordinateoldx, coordinatey;

	//Step 3... �������ϵת������������ϵ
	//���㽹��

	double ** a = new double*[3];
	for(int i = 0; i < 3; i++)
		a[i] = new double[3];
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			a[i][j] = m_RotationVector[i*3 + j];
	double * b = new double[3];
	for(int i = 0; i < 2; i++)
		b[i] = coordinatenewx[i]*(-F) - m_TranslationVector[i]; // ����ԭ���ĳ������˳���-f
	b[2] = -F - m_TranslationVector[2];
	delete coordinatenewx;
	double * cameraimagewordcoordinate = new double[3]; // ���������ƽ���ϵ����ص����������
	for(int i = 0; i < 3; i++)
		cameraimagewordcoordinate[i] = 0;
	m_gausseliminate->Eliminate(a, b, 3);
	m_gausseliminate->Rewind(a, b, cameraimagewordcoordinate, 3);
	for(int i = 0; i < 2; i++)
		delete []a[i];
	delete []a;
	delete b;
	return cameraimagewordcoordinate;
}
/*==============================================================
Name:	ConvertCameraImageCoordinateToCameraCoordinate
Desc:   
Param: 
Return:  �ռ�����
Note:  �Բο��潨������������ϵ�У�����������ڲ����Ͳο��潨��������ϵ���������
       �������ƽ�������ص������ת�����������ϵ�е�����
  --------------------------------------------------------------*/
double * CMyGeometry::ConvertCameraImageCoordinateToCameraCoordinate(int * cameraimagecoordinate)
{
	double * tempcoordinate = new double[2];
	// Step 1...
	tempcoordinate[0] = (cameraimagecoordinate[0] - m_CameraVector[2]) / m_CameraVector[0];
	tempcoordinate[1] = (cameraimagecoordinate[1] - m_CameraVector[3]) / m_CameraVector[1];

	//Step 2... ת�����������ϵ
	int iter = 0;
	double error = 0.0;
	double * coordinatey = new double[2]; //�����
	double * coordinateoldx = new double[2];  //�Ա���X,��ֵ
	double * coordinatenewx = new double[3];  //�Ա���X�����ش�ֵ
	for(int i = 0; i < 2; i++)
	{
		coordinatey[i] = 0.0;
		coordinateoldx[i] = tempcoordinate[i];
	}
	double ** jacobian =  new double*[2];
	double ** invjacobian = new double*[2];
	for(int i = 0; i < 2; i++)
	{
		jacobian[i] = new double[2];
		invjacobian[i] = new double[2];
	}
	bool Isfoud = false;
	while(iter < Max) //����У��
	{
		iter++;
		m_mynewtonmethod->f_y(coordinateoldx, coordinatey,  m_Distortion, tempcoordinate); //�����������ֵ
		m_mynewtonmethod->f_Jacobian(coordinateoldx, jacobian, m_Distortion, tempcoordinate); //�����ſ˱Ⱦ���
		m_mynewtonmethod->inv_Jacobian(jacobian, invjacobian); // �����ſ˱Ⱦ������
		m_mynewtonmethod->newtonsolution(coordinateoldx, invjacobian, coordinatey, coordinatenewx); //��������µ�x

		error = 0.0;
		for(int i = 0; i < 2; i++)
			error += fabs(coordinatenewx[i] - coordinateoldx[i]); 
		if(error < Epsilon) 
		{
			Isfoud = true;
			break;
		}
		for(int i = 0; i < 2; i++)
			coordinateoldx[i] = coordinatenewx[i];
	}
	if(!Isfoud)
		for(int i = 0; i < 2; i++)
		{
			coordinatenewx[i] = tempcoordinate[i];
		}

	for(int i = 0; i < 2; i++)
	{
		delete []jacobian[i];
		delete []invjacobian[i];
	}
	delete []jacobian;
	delete []invjacobian;
	delete tempcoordinate;
	delete coordinateoldx, coordinatey;
	double a = coordinatenewx[0];
	double b = coordinatenewx[1];
	coordinatenewx[0] *= -F;
	coordinatenewx[1] *= -F;
	coordinatenewx[2] = -F;

	return coordinatenewx;
}
/*==============================================================
Name:	ConvertCameraCoordinateToWordCoordinate
Desc:   
Param: 
Return:  �ռ�����
Note:  �Բο��潨������������ϵ�У�����������ڲ����Ͳο��潨��������ϵ���������
       �������ƽ�������ص������ת������������ϵ�е�����
  --------------------------------------------------------------*/
double * CMyGeometry::ConvertCameraCoordinateToWordCoordinate(double * cameracoordinate)
{
	//Step 3... �������ϵת������������ϵ

	double ** a = new double*[3];
	for(int i = 0; i < 3; i++)
		a[i] = new double[3];
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			a[i][j] = m_RotationVector[i*3 + j];
	double * b = new double[3];
	for(int i = 0; i < 3; i++)
		b[i] = cameracoordinate[i] - m_TranslationVector[i];

	double * wordcoordinate = new double[3]; // ���������ƽ���ϵ����ص����������
	for(int i = 0; i < 3; i++)
		wordcoordinate[i] = 0;
	m_gausseliminate->Eliminate(a, b, 3);
	m_gausseliminate->Rewind(a, b, wordcoordinate, 3);
	for(int i = 0; i < 2; i++)
		delete []a[i];
	delete []a;
	delete b;
	return wordcoordinate;
}
/*==============================================================
Name:	FindIntersectionOfLineAndReferenceplane
Desc:   
Param: 
Return:  �����������ķ�����ֱ����ο�ƽ��Ľ��㣬�Ӷ����MR��NR������
Note: 
  --------------------------------------------------------------*/
double * CMyGeometry::FindIntersectionOfLineAndReferenceplane(double * cameracenterwordcoordinate, double * cameraimageplanepointwordcoordinate, double depth)
{
	double temp0, temp1, temp2;
	temp0 = cameraimageplanepointwordcoordinate[0] - cameracenterwordcoordinate[0];
	temp1 = cameraimageplanepointwordcoordinate[1] - cameracenterwordcoordinate[1];
	temp2 = cameraimageplanepointwordcoordinate[2] - cameracenterwordcoordinate[2];

	double * referenceplaneintersectionpointwordcoordinate = new double[3]; //ֱ����ο�ƽ��Ľ���
	double ** a = new double*[3];
	for(int i = 0; i < 3; i++)
		a[i] = new double[3];
	double *b = new double[3];
	a[0][0] = temp1; a[0][1] = - temp0; a[0][2] = 0;      b[0] = cameracenterwordcoordinate[0]*temp1 - cameracenterwordcoordinate[1]*temp0;
	a[1][0] = 0;     a[1][1] = temp2;   a[1][2] = -temp1; b[1] =  cameracenterwordcoordinate[1]*temp2 -  cameracenterwordcoordinate[2]*temp1;
	a[2][0] = 0;     a[2][1] = 0;       a[2][2] = 1;      b[2] = depth;
	m_gausseliminate->Eliminate(a, b, 3);
	m_gausseliminate->Rewind(a, b, referenceplaneintersectionpointwordcoordinate, 3);
	for(int i = 0; i < 3; i++)
		delete []a[i];
	delete a;
	delete b;
	return referenceplaneintersectionpointwordcoordinate;
}

/*==============================================================
Name:	GetCameraCenterWordCoordinate
Desc:   
Param: 
Return:  ����������ĵ���������
Note: 
  --------------------------------------------------------------*/

double * CMyGeometry::GetCameraCenterWordCoordinate()
{
	double * wordcameracenter = new double[3];
	double ** a = new double*[3];
	for(int i = 0; i < 3; i++)
		a[i] = new double[3];
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			a[i][j] = m_RotationVector[i*3 + j];
	double * b = new double[3];
	for(int i = 0; i < 3; i++)
		b[i] = - m_TranslationVector[i];
	
	m_gausseliminate->Eliminate(a, b, 3);
	m_gausseliminate->Rewind(a, b, wordcameracenter, 3);
	
	for(int i = 0; i < 3; i++)
		delete []a[i];
	delete a;
	delete b;
	return wordcameracenter;

}

/*==============================================================
Name:	ConvertWordCoordinateToCameraImageCoordinate
Desc:   
Param: 
Return:  ����������ڲ����Ͳο��潨��������ϵ�������������������ϵת���������ƽ������ϵ
Note: 
  --------------------------------------------------------------*/
int * CMyGeometry::ConvertWordCoordinateToCameraImageCoordinate(double * wordcoordinate, bool b_if)
{
	double * temp = new double[3];
	for(int i = 0; i < 3; i++)
		temp[i] = 0.0;
	// step 1...
	double ** a = new double*[3];
	for(int i = 0; i < 3; i++)
		a[i] = new double[3];
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			a[i][j] = m_RotationVector[i*3 + j];
	double * b = new double[3];
	for(int i = 0; i < 3; i++)
		b[i] = m_TranslationVector[i];

	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			temp[i] += a[i][j] * wordcoordinate[j];
		}
		temp[i] += b[i];
	}
	for(int i = 0; i < 3; i++)
		delete []a[i];
	delete a;
	delete b;
	//step 2...
	temp[0] = temp[0] / temp[2];
	temp[1] = temp[1] / temp[2];
	//step 3...
	double r , tempx, tempy;
	if(b_if)
	{
	r = temp[0] * temp[0] + temp[1] * temp[1];
	tempx = temp[0]*(1+m_Distortion[0]*r+m_Distortion[1]*r*r) + 2*m_Distortion[2]*temp[0]*temp[1] + m_Distortion[3]*(r + 2*temp[0]*temp[0]);
	tempy = temp[1]*(1+m_Distortion[0]*r+m_Distortion[1]*r*r) + m_Distortion[2]*(r + 2*temp[1]*temp[1]) + 2*m_Distortion[3]*temp[0]*temp[1];
	}
	else
	{
		tempx = temp[0];
		tempy = temp[1];
	}
	delete temp;
	//step 4...
	int * cameraimagecoordinate = new int[2];
	cameraimagecoordinate[0] = m_CameraVector[0]*tempx + m_CameraVector[2];
	cameraimagecoordinate[1] = m_CameraVector[1]*tempy + m_CameraVector[3];

	return cameraimagecoordinate;
}

/*==============================================================
Name:	ConvertWordCoordinateToCameraCoordinate
Desc:   
Param: 
Return:  ����������ڲ����Ͳο��潨��������ϵ�������������������ϵת�����������ϵ
Note: 
  --------------------------------------------------------------*/
double * CMyGeometry::ConvertWordCoordinateToCameraCoordinate(double * wordcoordinate)
{
	double * temp = new double[3];
	for(int i = 0; i < 3; i++)
		temp[i] = 0.0;
	// step 1...
	double ** a = new double*[3];
	for(int i = 0; i < 3; i++)
		a[i] = new double[3];
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			a[i][j] = m_RotationVector[i*3 + j];
	double * b = new double[3];
	for(int i = 0; i < 3; i++)
		b[i] = m_TranslationVector[i];

	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			temp[i] += a[i][j] * wordcoordinate[j];
		}
		temp[i] += b[i];
	}
	for(int i = 0; i < 3; i++)
		delete []a[i];
	delete a;
	delete b;

	return temp;
}
/*==============================================================
Name:	ConvertCameraCoordinateToCameraImageCoordinate
Desc:   
Param: 
Return:  ����������ڲ����Ͳο��潨��������ϵ������������������ϵת�������ƽ������ϵ
Note: 
  --------------------------------------------------------------*/
double * CMyGeometry::ConvertCameraCoordinateToCameraImageCoordinate(double * cameracoordinate, bool b_is)
{
	cameracoordinate[0] = cameracoordinate[0] / cameracoordinate[2];
	cameracoordinate[1] = cameracoordinate[1] / cameracoordinate[2];
	double r , tempx, tempy;
	if(b_is)
	{
		r = cameracoordinate[0] * cameracoordinate[0] + cameracoordinate[1] * cameracoordinate[1];
		tempx = cameracoordinate[0]*(1+m_Distortion[0]*r+m_Distortion[1]*r*r) +
			2*m_Distortion[2]*cameracoordinate[0]*cameracoordinate[1] + m_Distortion[3]*(r + 2*cameracoordinate[0]*cameracoordinate[0]);
		tempy = cameracoordinate[1]*(1+m_Distortion[0]*r+m_Distortion[1]*r*r) +
			m_Distortion[2]*(r + 2*cameracoordinate[1]*cameracoordinate[1]) + 2*m_Distortion[3]*cameracoordinate[0]*cameracoordinate[1];
	}
	else
	{
		tempx = cameracoordinate[0];
		tempy = cameracoordinate[1];
	}
	double * cameraimagecoordinate = new double [2];
	cameraimagecoordinate[0] = m_CameraVector[0]*tempx + m_CameraVector[2];
	cameraimagecoordinate[1] = m_CameraVector[1]*tempy + m_CameraVector[3];

	return cameraimagecoordinate;
}
/*==============================================================
Name:	FindNI
Desc:   ��������ʹ�õ�
Param: 
Return:  �ҵ�NI����������
Note:  ������Ե������������Ҳ���ǲο���Ĵ�ֱ��ˮƽ��դ��������߽紹ֱ����ƽ�е�
  --------------------------------------------------------------*/
double * CMyGeometry::FindNI(double * referenceabsolutephasemap, double objectabsolutephase, int width, int height, double * PI, double * MI, int direction, int * referencelabelmap)
{
	double k = 0.0;
	// ��Ҫ����һ������ת������ΪͼƬY�Ǵ��ϵ����Ǳ�󣬶�����ϵ�����ϵ�
	k = double(PI[1] - MI[1]) / (MI[0] - PI[0]); // ����PIҲ����Ҫ��������任
	double * NI = new double[2];
	double * imagecoordinate =  new double[2];
	
	double x0 = MI[0];
	double y0 = height - MI[1];
	imagecoordinate[0] = x0;
	imagecoordinate[1] = y0;
	double  * findmin = new double[3];
	findmin[0] = 1.0;
	findmin[1] = -1;
	findmin[2] = -1;
	
//�ο�ƽ���0��λ��(283,238)�� �����0��λ�㣨214�� 266�� ��ˮƽ��դ�����ű�С�ķ��򣬴�ֱ��դ�����ű��ķ���
	//if(direction == 0)
	//{
	//	while(imagecoordinate[0] > 0)
	//	{
	//		imagecoordinate[0] -= 1;
	//		imagecoordinate[1] = k * (imagecoordinate[0] - x0) + y0;

	//		if((imagecoordinate[1] > 0)&&(imagecoordinate[1] < height))
	//		{
	//			double ftemp = fabs(referenceabsolutephasemap[imagecoordinate[0] + 
	//				(height-imagecoordinate[1]) * width]- objectabsolutephase);
	//			if( ftemp <= 2.0e-1)  // ��ֵΪ0.2���ҵ������ڴ���ֵ��Χ�ڣ�����ֵ֮����С�ĵ㣬��ΪĿ���
	//			{
	//				if(findmin[0] > ftemp)
	//				{
	//					findmin[0] = ftemp;
	//					findmin[1] = imagecoordinate[0];
	//					findmin[2] = imagecoordinate[1];
	//				}
	//			}
	//		}
	//	}
	//}
	//else
	//{
	//	while(imagecoordinate[0] < width)
	//	{
	//		imagecoordinate[0] += 1;
	//		imagecoordinate[1] = k * (imagecoordinate[0] - x0) + y0;

	//		if((imagecoordinate[1] > 0)&&(imagecoordinate[1] < height))
	//		{
	//			double ftemp = fabs(referenceabsolutephasemap[imagecoordinate[0] + 
	//				(height-imagecoordinate[1]) * width]- objectabsolutephase);
	//			if( ftemp <= 2.0e-1)  // ��ֵΪ0.2���ҵ������ڴ���ֵ��Χ�ڣ�����ֵ֮����С�ĵ㣬��ΪĿ���
	//			{
	//				if(findmin[0] > ftemp)
	//				{
	//					findmin[0] = ftemp;
	//					findmin[1] = imagecoordinate[0];
	//					findmin[2] = imagecoordinate[1];
	//				}
	//			}
	//		}
	//	}
	//}
	
	// ��һ�γ��򲻳�֣���Ϊ��ֻ����ֱ������imagecoordinate[0]����ķ��򣬶�û�п��Ǽ�С�ķ���
	//while(imagecoordinate[0] < width)
	//{
	//	imagecoordinate[0] += 1;
	//	imagecoordinate[1] = k * (imagecoordinate[0] - x0) + y0;

	//	if((imagecoordinate[1] > 0)&&(imagecoordinate[1] < height))
	//	{
	//		if(referencelabelmap[imagecoordinate[0] + (height-imagecoordinate[1])* width] == 1)
	//		{
	//			double ftemp = fabs(referenceabsolutephasemap[imagecoordinate[0] + 
	//				(height-imagecoordinate[1]) * width]- objectabsolutephase);
	//			if( ftemp <= 4.0e-1)  // ��ֵΪ0.2���ҵ������ڴ���ֵ��Χ�ڣ�����ֵ֮����С�ĵ㣬��ΪĿ���
	//			{
	//				if(findmin[0] > ftemp) // �����ֳ�����һ����ֵ���ƣ���Ӧ�ý�findmin[0] ��ʼֵ < �������ֵ
	//				{
	//					findmin[0] = ftemp;
	//					findmin[1] = imagecoordinate[0];
	//					findmin[2] = imagecoordinate[1];
	//				}
	//			}
	//		}
	//	}
	//}
	// ����˫�����ʱ��

	if (k*k < 1)
	{
		for(int ind = 0; ind < width; ind++)
		{
			imagecoordinate[1] = k * (ind - x0) + y0;

			if((imagecoordinate[1] > 0)&&(imagecoordinate[1] < height))
			{
				int y = int(height-imagecoordinate[1]+0.5);
				if(referencelabelmap[ind + y* width] == 1)
				{
					double ftemp = fabs(referenceabsolutephasemap[ind + 
						y * width]- objectabsolutephase);
					if( ftemp <8.0e-1)  // ��ֵΪ0.2���ҵ������ڴ���ֵ��Χ�ڣ�����ֵ֮����С�ĵ㣬��ΪĿ���
					{
						if(findmin[0] > ftemp) // �����ֳ�����һ����ֵ���ƣ���Ӧ�ý�findmin[0] ��ʼֵ < �������ֵ
						{
							findmin[0] = ftemp;
							findmin[1] = ind;
							findmin[2] = imagecoordinate[1];
						}
					}
				}
			}
		}
	}
	else
	{
		for(int ind = 0; ind < height; ind++)
		{
			imagecoordinate[0] = (ind - y0)/k + x0;

			if((imagecoordinate[0] > 0)&&(imagecoordinate[0] < width))
			{
				int x = int(imagecoordinate[0]+0.5);
				if(referencelabelmap[x + (height-ind)* width] == 1)
				{
					double ftemp = fabs(referenceabsolutephasemap[x + (height-ind)* width]- objectabsolutephase);
					if( ftemp <8.0e-1)  // ��ֵΪ0.2���ҵ������ڴ���ֵ��Χ�ڣ�����ֵ֮����С�ĵ㣬��ΪĿ���
					{
						if(findmin[0] > ftemp) // �����ֳ�����һ����ֵ���ƣ���Ӧ�ý�findmin[0] ��ʼֵ < �������ֵ
						{
							findmin[0] = ftemp;
							findmin[1] = imagecoordinate[0];
							findmin[2] = ind;
						}
					}
				}
			}
		}

	}
	NI[0] = findmin[1];
	NI[1] = height - findmin[2];
	delete findmin;
	delete imagecoordinate;
	return NI;
}

/*==============================================================
Name:	FindNI
Desc:   
Param: 
Return:  �ҵ�NI����������
Note:  ������Ե�һ�����,���������ϵ���н��в���
  --------------------------------------------------------------*/
double * CMyGeometry::FindNI(double * referenceabsolutephasemap, double objectabsolutephase, 
	int width, int height, double * PI, double * MI, double startx, double endx, double starty, double endy, double dx, double dy, int direction)
{
	double k = 0.0;

	k = double(MI[1] - PI[1]) / (MI[0] - PI[0]);
	double * NI = new double[2];
	double * cameracoordinate =  new double[3];
	
	double x0 = MI[0];
	double y0 = MI[1];
	cameracoordinate[0] = x0;
	cameracoordinate[1] = y0;
	cameracoordinate[2] = MI[2];
	double temp1, temp2;
	temp1 = x0;
	temp2 = y0;
	double  * findmin = new double[3];
	findmin[0] = 0.2;
	findmin[1] = -1;
	findmin[2] = -1;
	
	if(direction == 0) //�ο�ƽ���0��λ��(283,238)�� �����0��λ�㣨214�� 266�� ��ˮƽ��դ�����ű�С�ķ��򣬴�ֱ��դ�����ű��ķ���
	{
		while(cameracoordinate[1] < endy)
		{
			temp2 += dy;
			cameracoordinate[1] = temp2;
			cameracoordinate[0] = (cameracoordinate[1] - y0) / k + x0;
			cameracoordinate[2] = -F;
			if((cameracoordinate[0] > startx)&&(cameracoordinate[0] < endx))
			{
				double * imagecoordinate = this->ConvertCameraCoordinateToCameraImageCoordinate(cameracoordinate, true);
				if((imagecoordinate[0] < 0) || (imagecoordinate[1] < 0))
				{
					imagecoordinate[0] = 0;
					imagecoordinate[1] = 0;
				}
				int x = int(imagecoordinate[0]+0.5);
				int y = int(imagecoordinate[1]+0.5);
				double ftemp = fabs(referenceabsolutephasemap[x + 
					y * width]- objectabsolutephase);
				if( ftemp <= 2.0e-1)  // ��ֵΪ0.2���ҵ������ڴ���ֵ��Χ�ڣ�����ֵ֮����С�ĵ㣬��ΪĿ���
				{
					if(findmin[0] > ftemp)
					{
						findmin[0] = ftemp;
						findmin[1] = imagecoordinate[0];
						findmin[2] = imagecoordinate[1];
					}
				}
				delete imagecoordinate;
			}
		}
	}
	else
	{
		while(cameracoordinate[0] > startx)
		{
			temp1 -= dx; 
			cameracoordinate[0] = temp1;
			cameracoordinate[1] = k * (cameracoordinate[0] - x0) + y0;
			cameracoordinate[2] = -F;
		/*	if((labelmap[i + v*width] != 0 )&&
				(fabs(uabsolutephase[i]- objectabsolutephase) <= 1.0e-1))*/
			if((cameracoordinate[1] > starty)&&(cameracoordinate[1] < endy))
			{
				double * imagecoordinate = this->ConvertCameraCoordinateToCameraImageCoordinate(cameracoordinate, true);
				if((imagecoordinate[0] < 0) || (imagecoordinate[1] < 0))
				{
					imagecoordinate[0] = 0;
					imagecoordinate[1] = 0;
				}
				int x = int(imagecoordinate[0]+0.5);
				int y = int(imagecoordinate[1]+0.5);
				double ftemp = fabs(referenceabsolutephasemap[x + 
					y * width]- objectabsolutephase);
				if( ftemp <= 2.0e-1)
				{
					if(findmin[0] > ftemp)
					{
						findmin[0] = ftemp;
						findmin[1] = imagecoordinate[0];
						findmin[2] = imagecoordinate[1];
					}
				}
				delete imagecoordinate;
			}
		}
	}
	NI[0] = findmin[1];
	NI[1] = findmin[2];
	delete findmin;
	delete cameracoordinate;
	return NI;
}
/*==============================================================
Name:	FindVerticalLineMid_point
Desc:   
Param: 
Return:  �����д���������ֱ��PNR-CMR�Ľ��㣬���������е㣬������Ϊ����ռ��M
Note: �д��󣬸���������
  --------------------------------------------------------------*/
/*
  |x-x0 y-y0 z-z0|
  |a0   a1   a2  | = 0 ƽ�淽��
  |b0   b0   b1  |
*/
double * CMyGeometry::FindVerticalLineMid_point(double * projectioncenterwordcoordinate,
	double * cameracenterwordcoordinate, double * NRwordcoordinate, double * MRwordcoordinate)
{
	double * directionvector1 = new double[3];
	double * directionvector2 = new double[3];
	for(int i = 0; i < 3; i++)
	{
		directionvector2[i] = NRwordcoordinate[i] - projectioncenterwordcoordinate[i]; //ͶӰ���߷���ʸ��
		directionvector1[i] = MRwordcoordinate[i] - cameracenterwordcoordinate[i]; //����߷���ʸ��
	}
	double * directionvector = new double[3];
	directionvector = this->Calibrate3DDeterminant(directionvector1, directionvector2);
	double * insectionpoint1 = new double[3];
	double * insectionpoint2 = new double[3];
	//step1.. ��������Ͻ���

	insectionpoint1 = this->Calibrate3DDeterminant(directionvector2, directionvector);

	double ** a = new double*[3];
	for(int i = 0; i < 3; i++)
		a[i] = new double[3];
	double *b = new double[3];
	// ��λ���������
	a[0][0] = directionvector1[1]; a[0][1] = -directionvector1[0]; a[0][2] = 0; b[0] = directionvector1[1]*cameracenterwordcoordinate[0] - directionvector1[0]*cameracenterwordcoordinate[1];
	a[1][0] = 0;          a[1][1] = directionvector1[2];  a[1][2] = -directionvector1[1]; b[1] = directionvector1[2]*cameracenterwordcoordinate[1] - directionvector1[1]*cameracenterwordcoordinate[2];
	// ����ƽ����
	a[2][0] = insectionpoint1[0]; a[2][1] = insectionpoint1[1]; a[2][2] = insectionpoint1[2]; 
	b[2] = insectionpoint1[0]*projectioncenterwordcoordinate[0] + insectionpoint1[1]*projectioncenterwordcoordinate[1] + insectionpoint1[2]*projectioncenterwordcoordinate[2];

	m_gausseliminate->Eliminate(a, b, 3);
	m_gausseliminate->Rewind(a, b, insectionpoint1, 3);
	double in1 = insectionpoint1[0];
	double in2 = insectionpoint1[1];
	double in3 = insectionpoint1[2];
	// step2... ����ͶӰ���ߵĽ���
	insectionpoint2 = this->Calibrate3DDeterminant(directionvector1, directionvector);
	// λ��ͶӰ������
	a[0][0] = directionvector2[1]; a[0][1] = -directionvector2[0]; a[0][2] = 0; b[0] = directionvector2[1]*projectioncenterwordcoordinate[0] - directionvector2[0]*projectioncenterwordcoordinate[1];
	a[1][0] = 0;          a[1][1] = directionvector2[2];  a[1][2] = -directionvector2[1]; b[1] = directionvector2[2]*projectioncenterwordcoordinate[1] - directionvector2[1]*projectioncenterwordcoordinate[2];
	a[2][0] = insectionpoint2[0]; a[2][1] = insectionpoint2[1]; a[2][2] = insectionpoint2[2]; 
	b[2] = insectionpoint2[0]*cameracenterwordcoordinate[0] + insectionpoint2[1]*cameracenterwordcoordinate[1] + insectionpoint2[2]*cameracenterwordcoordinate[2];

	m_gausseliminate->Eliminate(a, b, 3);
	m_gausseliminate->Rewind(a, b, insectionpoint2, 3); //��ͶӰ���ȵĽ���
	double im1 = insectionpoint2[0];
	double im2 = insectionpoint2[1];
	double im3 = insectionpoint2[2];
	double  * mid_pointcoordinate = new double[3];
	for(int i = 0; i < 3; i++)
		mid_pointcoordinate[i] = (insectionpoint2[i] + insectionpoint1[i]) / 2;
	for(int i = 0; i < 3; i++)
		delete []a[i];
	delete []a;
	delete b;
	delete insectionpoint1, insectionpoint2, directionvector1, directionvector2, directionvector; 
	return mid_pointcoordinate;
}
/*==============================================================
Name:	Calibrate3DDeterminant
Desc:   
Param: 
Return:  ������ά����ʽ
Note: 
  --------------------------------------------------------------*/
double * CMyGeometry::Calibrate3DDeterminant(double * a, double * b)
{
	double * c = new double[3];
	c[0] = a[1]*b[2] - a[2]*b[1];
	c[1] = -(a[0]*b[2] - b[0]*a[2]);
	c[2] = a[0]*b[1] - b[0]*a[1];

	return c;
}