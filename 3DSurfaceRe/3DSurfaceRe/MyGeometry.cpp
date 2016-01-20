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
Return:  一组采样点的坐标值
Note: 获得平面1的采样点
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
	for(int cx = startpoint.x - 120 ; cx <= startpoint.x + 120;)  //此处也要修改
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
Return:  一组采样点所对应的绝对相位
Note: 其对应于投影校准时候，找绝对相位值,因为校准是为平面板，
      所以取平均值会更准确
  --------------------------------------------------------------*/
double * CMyGeometry::GetPrjectionSmaplePointAbsolutePhase(double * referenceabsolutephasemap, int * labelmap, 
	int ** projectionsamplepoint, int num, int width, int height, bool direction)
{
	double * projectionsamplepointabsolutephase = new double[num];
	if(direction) // 垂直方向光栅
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
	else // 水平方向光栅
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
Return:  一组采样点所对应的绝对相位
Note: 其对应于投影校准时候，找绝对相位值,因为校准是为平面板，
      所以取平均值会更准确
  --------------------------------------------------------------*/
double  CMyGeometry::GetPointAbsolutePhase(double * absolutephasemap, int * point, int width, int height)
{
	double  pointabsolutephase  = 0.0 ;
	pointabsolutephase = absolutephasemap[point[0] + point[1] * width]; // 针对图像
	return pointabsolutephase;

}
/*==============================================================
Name:	GetAbsolutePhaseCorrespondPoint
Desc:   其光栅正好在平面上是水平的，或者垂直的
Param: 
Return:  绝对相位值所对应平行平面2的坐标
Note: 其对应于投影校准时候，通过平面1采样点，计算到的绝对相位值，找到
      对应于平面2相同相位值的点的坐标
  --------------------------------------------------------------*/
int * CMyGeometry::GetAbsolutePhaseCorrespondPoint(double * referenceabsolutephasemap, int * labelmap,
	double ** projectionsamplepointabsolutephase, int num, int width, int height, bool direction)
{
	int * projectionsamplepointcorrespondpoint = new int[num];
	if(direction) // 垂直方向光栅
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
	else // 水平方向光栅
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
Param: 一般情况，非水平或者垂直
Return:  绝对相位值所对应平行平面2的坐标
Note: 其对应于投影校准时候，通过平面1采样点，计算到的绝对相位值，找到
      对应于平面2相同相位值的点的坐标
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
Return:  绝对相位值所对应平行平面2的坐标
Note: 其对应于投影校准时候，通过平面1采样点，计算到的绝对相位值，找到
      对应于平面2相同相位值的点的坐标
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
Return:  空间坐标
Note:  以参考面建立的世界坐标系中，利用相机的内参数和参考面建立的坐标系的外参数，
       将相机像平面上像素点的坐标转换到世界坐标系中的坐标(这里的世界坐标，是位于相机像平面上的点的世界坐标，故其Z坐标很好计算)
  --------------------------------------------------------------*/
double * CMyGeometry::ConvertCameraImageCoordinateToWordCoordinate(double * cameraimagecoordinate)
{
	double * tempcoordinate = new double[2];
	// Step 1...
	tempcoordinate[0] = (cameraimagecoordinate[0] - m_CameraVector[2]) / m_CameraVector[0];
	tempcoordinate[1] = (cameraimagecoordinate[1] - m_CameraVector[3]) / m_CameraVector[1];

	//Step 2... 转换到相机坐标系
	int iter = 0;
	double error = 0.0;
	double * coordinatey = new double[2]; //因变量
	double * coordinateoldx = new double[2];  //自变量X,旧值
	double * coordinatenewx = new double[2];  //自变量X，返回此值
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
	while(iter < Max) //畸变校正
	{
		iter++;
		m_mynewtonmethod->f_y(coordinateoldx, coordinatey,  m_Distortion, tempcoordinate); //计算因变量的值
		m_mynewtonmethod->f_Jacobian(coordinateoldx, jacobian, m_Distortion, tempcoordinate); //计算雅克比矩阵
		m_mynewtonmethod->inv_Jacobian(jacobian, invjacobian); // 计算雅克比矩阵的逆
		m_mynewtonmethod->newtonsolution(coordinateoldx, invjacobian, coordinatey, coordinatenewx); //迭代求出新的x

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

	//Step 3... 相机坐标系转换到世界坐标系
	//计算焦距

	double ** a = new double*[3];
	for(int i = 0; i < 3; i++)
		a[i] = new double[3];
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			a[i][j] = m_RotationVector[i*3 + j];
	double * b = new double[3];
	for(int i = 0; i < 2; i++)
		b[i] = coordinatenewx[i]*(-F) - m_TranslationVector[i]; // 这里原来的程序少了乘以-f
	b[2] = -F - m_TranslationVector[2];
	delete coordinatenewx;
	double * cameraimagewordcoordinate = new double[3]; // 计算相机像平面上的像素点的世界坐标
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
Return:  空间坐标
Note:  以参考面建立的世界坐标系中，利用相机的内参数和参考面建立的坐标系的外参数，
       将相机像平面上像素点的坐标转换到相机坐标系中的坐标
  --------------------------------------------------------------*/
double * CMyGeometry::ConvertCameraImageCoordinateToCameraCoordinate(int * cameraimagecoordinate)
{
	double * tempcoordinate = new double[2];
	// Step 1...
	tempcoordinate[0] = (cameraimagecoordinate[0] - m_CameraVector[2]) / m_CameraVector[0];
	tempcoordinate[1] = (cameraimagecoordinate[1] - m_CameraVector[3]) / m_CameraVector[1];

	//Step 2... 转换到相机坐标系
	int iter = 0;
	double error = 0.0;
	double * coordinatey = new double[2]; //因变量
	double * coordinateoldx = new double[2];  //自变量X,旧值
	double * coordinatenewx = new double[3];  //自变量X，返回此值
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
	while(iter < Max) //畸变校正
	{
		iter++;
		m_mynewtonmethod->f_y(coordinateoldx, coordinatey,  m_Distortion, tempcoordinate); //计算因变量的值
		m_mynewtonmethod->f_Jacobian(coordinateoldx, jacobian, m_Distortion, tempcoordinate); //计算雅克比矩阵
		m_mynewtonmethod->inv_Jacobian(jacobian, invjacobian); // 计算雅克比矩阵的逆
		m_mynewtonmethod->newtonsolution(coordinateoldx, invjacobian, coordinatey, coordinatenewx); //迭代求出新的x

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
Return:  空间坐标
Note:  以参考面建立的世界坐标系中，利用相机的内参数和参考面建立的坐标系的外参数，
       将相机像平面上像素点的坐标转换到世界坐标系中的坐标
  --------------------------------------------------------------*/
double * CMyGeometry::ConvertCameraCoordinateToWordCoordinate(double * cameracoordinate)
{
	//Step 3... 相机坐标系转换到世界坐标系

	double ** a = new double*[3];
	for(int i = 0; i < 3; i++)
		a[i] = new double[3];
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			a[i][j] = m_RotationVector[i*3 + j];
	double * b = new double[3];
	for(int i = 0; i < 3; i++)
		b[i] = cameracoordinate[i] - m_TranslationVector[i];

	double * wordcoordinate = new double[3]; // 计算相机像平面上的像素点的世界坐标
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
Return:  计算从相机中心发出的直线与参考平面的交点，从而获得MR和NR的坐标
Note: 
  --------------------------------------------------------------*/
double * CMyGeometry::FindIntersectionOfLineAndReferenceplane(double * cameracenterwordcoordinate, double * cameraimageplanepointwordcoordinate, double depth)
{
	double temp0, temp1, temp2;
	temp0 = cameraimageplanepointwordcoordinate[0] - cameracenterwordcoordinate[0];
	temp1 = cameraimageplanepointwordcoordinate[1] - cameracenterwordcoordinate[1];
	temp2 = cameraimageplanepointwordcoordinate[2] - cameracenterwordcoordinate[2];

	double * referenceplaneintersectionpointwordcoordinate = new double[3]; //直线与参考平面的交点
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
Return:  计算相机中心的世界坐标
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
Return:  利用相机的内参数和参考面建立的坐标系的外参数，将世界坐标系转换到相机像平面坐标系
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
Return:  利用相机的内参数和参考面建立的坐标系的外参数，将世界坐标系转换到相机坐标系
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
Return:  利用相机的内参数和参考面建立的坐标系的外参数，将相机坐标系转换到相机平面坐标系
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
Desc:   这是我是使用的
Param: 
Return:  找到NI的像素坐标
Note:  这里针对的是特殊情况，也就是参考面的垂直和水平光栅正好是与边界垂直或者平行的
  --------------------------------------------------------------*/
double * CMyGeometry::FindNI(double * referenceabsolutephasemap, double objectabsolutephase, int width, int height, double * PI, double * MI, int direction, int * referencelabelmap)
{
	double k = 0.0;
	// 需要进行一个坐标转换，因为图片Y是从上到下是变大，而坐标系是向上的
	k = double(PI[1] - MI[1]) / (MI[0] - PI[0]); // 这里PI也是需要进行坐标变换
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
	
//参考平面的0相位点(283,238)， 物体的0相位点（214， 266） 故水平光栅是沿着变小的方向，垂直光栅是沿着变大的方向
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
	//			if( ftemp <= 2.0e-1)  // 阈值为0.2，找到其中在此阈值范围内，绝对值之差最小的点，作为目标点
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
	//			if( ftemp <= 2.0e-1)  // 阈值为0.2，找到其中在此阈值范围内，绝对值之差最小的点，作为目标点
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
	
	// 这一段程序不充分，因为它只考虑直线沿着imagecoordinate[0]增大的方向，而没有考虑减小的方向
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
	//			if( ftemp <= 4.0e-1)  // 阈值为0.2，找到其中在此阈值范围内，绝对值之差最小的点，作为目标点
	//			{
	//				if(findmin[0] > ftemp) // 这里又出现了一个阈值限制，故应该将findmin[0] 初始值 < 上面的阈值
	//				{
	//					findmin[0] = ftemp;
	//					findmin[1] = imagecoordinate[0];
	//					findmin[2] = imagecoordinate[1];
	//				}
	//			}
	//		}
	//	}
	//}
	// 考虑双方向的时候

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
					if( ftemp <8.0e-1)  // 阈值为0.2，找到其中在此阈值范围内，绝对值之差最小的点，作为目标点
					{
						if(findmin[0] > ftemp) // 这里又出现了一个阈值限制，故应该将findmin[0] 初始值 < 上面的阈值
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
					if( ftemp <8.0e-1)  // 阈值为0.2，找到其中在此阈值范围内，绝对值之差最小的点，作为目标点
					{
						if(findmin[0] > ftemp) // 这里又出现了一个阈值限制，故应该将findmin[0] 初始值 < 上面的阈值
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
Return:  找到NI的像素坐标
Note:  这里针对的一般情况,在相机坐标系当中进行查找
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
	
	if(direction == 0) //参考平面的0相位点(283,238)， 物体的0相位点（214， 266） 故水平光栅是沿着变小的方向，垂直光栅是沿着变大的方向
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
				if( ftemp <= 2.0e-1)  // 阈值为0.2，找到其中在此阈值范围内，绝对值之差最小的点，作为目标点
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
Return:  计算中垂线与两条直线PNR-CMR的交点，求出交点的中点，将其作为物体空间点M
Note: 有错误，改正。。。
  --------------------------------------------------------------*/
/*
  |x-x0 y-y0 z-z0|
  |a0   a1   a2  | = 0 平面方程
  |b0   b0   b1  |
*/
double * CMyGeometry::FindVerticalLineMid_point(double * projectioncenterwordcoordinate,
	double * cameracenterwordcoordinate, double * NRwordcoordinate, double * MRwordcoordinate)
{
	double * directionvector1 = new double[3];
	double * directionvector2 = new double[3];
	for(int i = 0; i < 3; i++)
	{
		directionvector2[i] = NRwordcoordinate[i] - projectioncenterwordcoordinate[i]; //投影仪线方向矢量
		directionvector1[i] = MRwordcoordinate[i] - cameracenterwordcoordinate[i]; //相机线方向矢量
	}
	double * directionvector = new double[3];
	directionvector = this->Calibrate3DDeterminant(directionvector1, directionvector2);
	double * insectionpoint1 = new double[3];
	double * insectionpoint2 = new double[3];
	//step1.. 求相机线上交点

	insectionpoint1 = this->Calibrate3DDeterminant(directionvector2, directionvector);

	double ** a = new double*[3];
	for(int i = 0; i < 3; i++)
		a[i] = new double[3];
	double *b = new double[3];
	// 点位于相机线上
	a[0][0] = directionvector1[1]; a[0][1] = -directionvector1[0]; a[0][2] = 0; b[0] = directionvector1[1]*cameracenterwordcoordinate[0] - directionvector1[0]*cameracenterwordcoordinate[1];
	a[1][0] = 0;          a[1][1] = directionvector1[2];  a[1][2] = -directionvector1[1]; b[1] = directionvector1[2]*cameracenterwordcoordinate[1] - directionvector1[1]*cameracenterwordcoordinate[2];
	// 在于平面内
	a[2][0] = insectionpoint1[0]; a[2][1] = insectionpoint1[1]; a[2][2] = insectionpoint1[2]; 
	b[2] = insectionpoint1[0]*projectioncenterwordcoordinate[0] + insectionpoint1[1]*projectioncenterwordcoordinate[1] + insectionpoint1[2]*projectioncenterwordcoordinate[2];

	m_gausseliminate->Eliminate(a, b, 3);
	m_gausseliminate->Rewind(a, b, insectionpoint1, 3);
	double in1 = insectionpoint1[0];
	double in2 = insectionpoint1[1];
	double in3 = insectionpoint1[2];
	// step2... 求与投影仪线的交点
	insectionpoint2 = this->Calibrate3DDeterminant(directionvector1, directionvector);
	// 位于投影仪线上
	a[0][0] = directionvector2[1]; a[0][1] = -directionvector2[0]; a[0][2] = 0; b[0] = directionvector2[1]*projectioncenterwordcoordinate[0] - directionvector2[0]*projectioncenterwordcoordinate[1];
	a[1][0] = 0;          a[1][1] = directionvector2[2];  a[1][2] = -directionvector2[1]; b[1] = directionvector2[2]*projectioncenterwordcoordinate[1] - directionvector2[1]*projectioncenterwordcoordinate[2];
	a[2][0] = insectionpoint2[0]; a[2][1] = insectionpoint2[1]; a[2][2] = insectionpoint2[2]; 
	b[2] = insectionpoint2[0]*cameracenterwordcoordinate[0] + insectionpoint2[1]*cameracenterwordcoordinate[1] + insectionpoint2[2]*cameracenterwordcoordinate[2];

	m_gausseliminate->Eliminate(a, b, 3);
	m_gausseliminate->Rewind(a, b, insectionpoint2, 3); //与投影仪先的交点
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
Return:  计算三维行列式
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