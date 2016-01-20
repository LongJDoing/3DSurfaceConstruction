#include "stdafx.h"
#include "MyDIdefine.h"

double m_CameraVector[4] = { 1399.15690,   1398.09149,   267.55968,   318.66995 };

double m_RotationVector[9]= {
	0.999828, 	 0.007685 ,	 -0.016864,
	0.008079, 	 -0.999693, 	 0.023406,
	-0.016679 ,	 -0.023538 ,	 -0.999584
                                     };
double m_TranslationVector[3] = { -98.205837, 	 -16.949284 ,	 1174.974705 };
double m_Distortion[4] = { -0.36313,   0.71511,   0.00644,   -0.00194 }; // 我自己修改了这里的一些数据
double m_sizex = 3.6;
double m_sizey = 3.6;
double m_Distance = 60; // mm
double F = (m_CameraVector[0]*m_sizex/1000 + m_CameraVector[1]*m_sizey/1000)/2;