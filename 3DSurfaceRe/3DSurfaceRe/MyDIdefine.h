#ifndef MYDIDEFINE_H
#define MYDIDEFINE_H

#include <math.h>
#include <errno.h>
const double PI = (2 * asin(1.0));
#define LEVEL1 1
#define LEVEL2 2
#define LEVEL3 3
#define UNWRAP   -1

static int NeighborDirection[8][2] = {{0,1},{1,1},{1,0},{1,-1},
{0,-1},{-1,-1},{-1,0},{-1,1}};      // ���������
static int LabelMapIndex[3] = {1, 2, 3};

//==================���У׼ʱ�򣬻������ڲ�������ƽ��ƽ����ⲿ����================
extern double m_CameraVector[4];
extern double m_RotationVector[9]; 
extern double m_TranslationVector[3]; 
extern double m_Distortion[4];  
extern double m_Distance;
extern double F ;
extern double m_sizex;
extern double m_sizey;
//=====================================================================================

#define Epsilon 0.0001             // ������1����������
#define Max     100               //����������
#define N 2
#define N2 4
#define DES 40


#endif