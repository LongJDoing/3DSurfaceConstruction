#include "StdAfx.h"
#include "HQualityMapGuidedUn.h"

CHQualityMapGuidedUn::CHQualityMapGuidedUn(void)
{
}


CHQualityMapGuidedUn::~CHQualityMapGuidedUn(void)
{
}
void CHQualityMapGuidedUn::PushQueue(Queue *queue, int data)
{
	QNode *p = NULL;
	//p = (QNode*)malloc(sizeof(QNode));
	p = new QNode();
	p->data = data;
	if(queue->first == NULL)
	{
		queue->first = p;
		queue->last = p;
		p->next = NULL;
	}
	else
	{
		p->next = NULL;
		queue->first = p;
		queue->first->next = queue->last;
		queue->last = p;
	}
}

int CHQualityMapGuidedUn::PopQueue(Queue *queue)
{
	QNode *p = NULL;
	int data;
	if(queue->first == NULL)
	{
		return -1;
	}
	p = queue->first;
	data = p->data;
	if(queue->first->next == NULL)
	{
		queue->first = NULL;
		queue->last = NULL;
	}
	else
	{
		queue->first = p->next;
	}
	//free(p);
	delete p;
	return data;
}

/*==============================================================
Name:	LineScan
Desc:  执行线扫描算法
Param:	
Return:  
Note: 垂直光栅的线扫描算法，其展开的方向为X轴方向
  --------------------------------------------------------------*/
double CHQualityMapGuidedUn::LineScan(double CurrentValue, double NeighborValue,double UnwrapNeighborValue, CPoint CurrentPoint, CPoint NeighborPoint)
{
	double temp = 0.0;
	temp = CurrentValue - NeighborValue;
	//if(abs(temp) < 1.0e-3)
	//{
	//	if((CurrentPoint.x - NeighborPoint.x) == 0)
	//	{
	//		if((CurrentPoint.y - NeighborPoint.y) == 1)
	//			CurrentValue = UnwrapNeighborValue + 2*PI/ DES; // 40个pixel一个周期，一个周期长为PI
	//		else
	//			CurrentValue = UnwrapNeighborValue - 2*PI/ DES;
	//	}
	//	else
	//		CurrentValue = UnwrapNeighborValue;
	//	
	//}
	if(temp > PI)
		{ CurrentValue = UnwrapNeighborValue + temp - 2 * PI; }
	else if(temp < - PI)
		{ CurrentValue = UnwrapNeighborValue + temp + 2 * PI;}
	//// 当我的相对相位图变化非常大的时候，可能会为PI/2，因此我加入下面两行语句,需要放到这个位置
	/*else if(temp > PI/2 )
		{ CurrentValue = UnwrapNeighborValue + temp - PI; }
	else if(temp < - PI/2)
		{ CurrentValue = UnwrapNeighborValue + temp + PI;}*/

	else
		{ CurrentValue = UnwrapNeighborValue + temp;}

	return CurrentValue;
}
/*==============================================================
Name:	PhaseMapScan
Desc:  执行改进的线扫描算法
Param:	
Return: NULL 
Note: 
  --------------------------------------------------------------*/
void CHQualityMapGuidedUn::ScanPhaseMap(double * bitmap, int * labelmap, int width, int height,CPoint startpoint, 
	CPoint CurrentPoint,Queue *queue, double * absolutephasemap,int index)
{
	CPoint NeighborPoint;
	bool b_nearNeighborUnwrap = FALSE; // 判断面向起点的邻近点相位是否展开
	bool b_Neighbor = FALSE; // 判断周围邻近点是否为作用点，如果都是非，则丢弃该点
	// 至少有一个面向起点的邻点被展开，扫描点将被展开，然后标记为展开
	for(int i = 0; i < 8; i++)
	{
		NeighborPoint.x = CurrentPoint.x + NeighborDirection[i][0];
		NeighborPoint.y = CurrentPoint.y + NeighborDirection[i][1];
		{
			if((abs(NeighborPoint.x - startpoint.x) <= abs(CurrentPoint.x - startpoint.x))&&(abs(NeighborPoint.y - startpoint.y) <= abs(CurrentPoint.y - startpoint.y))
				&&(labelmap[NeighborPoint.x + NeighborPoint.y * width] == UNWRAP))
			{
				labelmap[CurrentPoint.x + CurrentPoint.y * width] = UNWRAP;
				absolutephasemap[CurrentPoint.x + CurrentPoint.y * width] = this->LineScan(bitmap[CurrentPoint.x + CurrentPoint.y * width], 
						bitmap[NeighborPoint.x + NeighborPoint.y * width],absolutephasemap[NeighborPoint.x + NeighborPoint.y * width], CurrentPoint, NeighborPoint) ;
				b_nearNeighborUnwrap = TRUE;
				break;
			}
		//	b_Neighbor = TRUE;
		}
	}
	//该点面向起点的邻点都未展开，但至少有一个有效的邻点面向边界，该点将被放入堆栈
	bool b_farNeighbor = false;
	if((!b_nearNeighborUnwrap))//&&(labelmap[CurrentPoint.x + CurrentPoint.y*width] >= LEVEL3))
	{
		for(int i = 0; i < 8; i++)
		{
			NeighborPoint.x = CurrentPoint.x + NeighborDirection[i][0];
			NeighborPoint.y = CurrentPoint.y + NeighborDirection[i][1];

			if((abs(NeighborPoint.x - startpoint.x) > abs(CurrentPoint.x - startpoint.x))||(abs(NeighborPoint.y - startpoint.y) > abs(CurrentPoint.y - startpoint.y)))
			{
				PushQueue(queue,CurrentPoint.x + CurrentPoint.y*width);
				b_farNeighbor = true;
				break;
			}
		}
	}
	if(b_farNeighbor)
		labelmap[CurrentPoint.x + CurrentPoint.y*width] = index +1;
}

/*==============================================================
Name:	UnwrapPhaseMap
Desc:   基于质量图的相位展开
Param:	
Return:  NULL
Note: 
  --------------------------------------------------------------*/
double * CHQualityMapGuidedUn::UnwrapPhaseMap(double * phasemap, int * labelmap, int width, int height,CPoint startpoint, CPoint refpoint)
{
	Queue *queue = NULL;
//	queue = (Queue*)malloc(sizeof(Queue));
	queue = new Queue();
	queue->first = NULL;
    queue->last = NULL;
	CPoint CurrentPoint;
	labelmap[startpoint.x + startpoint.y*width] = UNWRAP;
	double *absolutephasemap = new double[width*height];
	for(int i = 0; i < width*height; i++)
		absolutephasemap[i] = phasemap[i];
	//右上角
	int index = 1;
	while(index < 4)
	{
		//int cy = startpoint.y;
	for(int cx = startpoint.x; cx < width-1; cx++)
		for(int cy = startpoint.y; cy > 1; cy--)
			{
				CurrentPoint.x = cx;
				CurrentPoint.y = cy;
				if(labelmap[CurrentPoint.x + CurrentPoint.y*width] == index)//扫描第一层
				{
	                ScanPhaseMap(phasemap, labelmap, width, height, startpoint, CurrentPoint, queue, absolutephasemap,index);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 				
				}
		//		if(labelmap[CurrentPoint.x + CurrentPoint.y*width] == index)
		//			labelmap[CurrentPoint.x + CurrentPoint.y*width] = index +1; //可以放到前面
			}
	//	BackUnwrap(phasemap, labelmap, width, height, startpoint, queue, absolutephasemap);
		//for(int cx = startpoint.x; cx < width-1; cx++)
		//	for(int cy = startpoint.y; cy > 1; cy--)
		//		if(labelmap[cx + cy*width] == index)
		//			labelmap[cx + cy*width] = index +1; //可以放到前面
		index++;
	}
	//左上角
    index = 1;
	while(index < 4)
	{
	//	int cy = startpoint.y;
		for(int cx = startpoint.x; cx > 1; cx--)
			for(int cy = startpoint.y; cy > 1; cy--)
			{
				CurrentPoint.x = cx;
				CurrentPoint.y = cy;
				if(labelmap[CurrentPoint.x + CurrentPoint.y*width] == index)//扫描第一层
				{
					ScanPhaseMap(phasemap, labelmap, width, height, startpoint, CurrentPoint, queue, absolutephasemap, index);
				}
			//	if(labelmap[CurrentPoint.x + CurrentPoint.y*width] == index)
			//		labelmap[CurrentPoint.x + CurrentPoint.y*width] = index +1; //可以放到前面

			}
	//	BackUnwrap(phasemap, labelmap, width, height, startpoint, queue, absolutephasemap);
		//for(int cx = startpoint.x; cx > 1; cx--)
		//	for(int cy = startpoint.y; cy > 1; cy--)
		//		if(labelmap[cx + cy*width] == index)
		//			labelmap[cx + cy*width] = index +1;
		index++;
	}
	//左下角
    index = 1;
	while(index < 4)
	{
	//	int cy = startpoint.y;
		for(int cx = startpoint.x; cx > 1; cx--)
			for(int cy = startpoint.y; cy < height -1; cy++)
			{
				CurrentPoint.x = cx;
				CurrentPoint.y = cy;
				if(labelmap[CurrentPoint.x + CurrentPoint.y*width] == index)//扫描第一层
				{
					ScanPhaseMap(phasemap, labelmap, width, height, startpoint, CurrentPoint, queue, absolutephasemap,index);
				}
		//		if(labelmap[CurrentPoint.x + CurrentPoint.y*width] == index)
		//			labelmap[CurrentPoint.x + CurrentPoint.y*width] = index +1; //可以放到前面
			}
	//	BackUnwrap(phasemap, labelmap, width, height, startpoint, queue, absolutephasemap);
		//for(int cx = startpoint.x; cx > 1; cx--)
		//	for(int cy = startpoint.y; cy < height -1; cy++)
		//		if(labelmap[cx + cy*width] == index)
		//			labelmap[cx + cy*width] = index +1;
		index++;
	}
	//右下角
	index = 1;
	while(index < 4)
	{
	//	int cy = startpoint.y;
		for(int cx = startpoint.x; cx < width-1; cx++)
			for(int cy = startpoint.y; cy < height -1; cy++)
			{
				CurrentPoint.x = cx;
				CurrentPoint.y = cy;
				if(labelmap[CurrentPoint.x + CurrentPoint.y*width] == index)//扫描第一层
				{
					ScanPhaseMap(phasemap, labelmap, width, height, startpoint, CurrentPoint, queue, absolutephasemap, index);
				}
			//	if(labelmap[CurrentPoint.x + CurrentPoint.y*width] == index)
			//		labelmap[CurrentPoint.x + CurrentPoint.y*width] = index +1; //可以放到前面
			}
	//	BackUnwrap(phasemap, labelmap, width, height, startpoint, queue, absolutephasemap);
		/*for(int cx = startpoint.x; cx < width-1; cx++)
			for(int cy = startpoint.y; cy < height -1; cy++)
				if(labelmap[cx + cy*width] == index)
					labelmap[cx + cy*width] = index +1;*/
		index++;
	}
	//CString stmp;
	//stmp.Format('%d', labelmap[464 + 277*width]);
	//AfxMessageBox(stmp,NULL);
	BackUnwrap(phasemap, labelmap, width, height, startpoint, queue, absolutephasemap);
	for(int i = 0; i < width*height; i++)
		if(labelmap[i] == UNWRAP)
			absolutephasemap[i] = absolutephasemap[i];
		else
			absolutephasemap[i] = -10000;

	return absolutephasemap;
}

void CHQualityMapGuidedUn::BackUnwrap(double *phasemap, int *labelmap, int width, int height, 
	CPoint startpoint, Queue *queue, double *absolutephasemap)
{
	int PopIndex = 0;
	CPoint NeighborPoint, CurrentPoint;
	PopIndex = PopQueue(queue);
	while(PopIndex > -1)
	{
		CurrentPoint.x = PopIndex%width;
		CurrentPoint.y = PopIndex/width;
		for(int i = 0; i < 8; i++)
		{
			NeighborPoint.x = CurrentPoint.x + NeighborDirection[i][0];
			NeighborPoint.y = CurrentPoint.y + NeighborDirection[i][1];
			if(((abs(NeighborPoint.x - startpoint.x) > abs(CurrentPoint.x - startpoint.x))||(abs(NeighborPoint.y - startpoint.y) > abs(CurrentPoint.y - startpoint.y)))
							&&(labelmap[NeighborPoint.x + NeighborPoint.y * width] == UNWRAP))
			{
				labelmap[PopIndex] = UNWRAP;
				absolutephasemap[CurrentPoint.x + CurrentPoint.y * width] = this->LineScan(phasemap[CurrentPoint.x + CurrentPoint.y * width], 
									phasemap[NeighborPoint.x + NeighborPoint.y * width], absolutephasemap[NeighborPoint.x + NeighborPoint.y * width], CurrentPoint, NeighborPoint) ;
				break;
			}
		}
		PopIndex = PopQueue(queue);
	}
}

/*==============================================================
Name:	FindStartPosition
Desc:  返回中心点位置
Param:	
Return:  null
Note: 计算质量图2掩模区域的满足条件的初始点作为相位展开的初始点
  --------------------------------------------------------------*/
CPoint CHQualityMapGuidedUn::FindStartPosition(double * phasemap, int *labelmap, CPoint centerpoint, int width, int height)
{
	CPoint StartPoint ;
	int VaryNeighborDirection[8][2];
	bool b_research = FALSE;
	int j = 0; 
	while(!b_research)
	{
		VaryNeighborDirection[0][0] = 0;VaryNeighborDirection[0][1] = j;
		VaryNeighborDirection[1][0] = j;VaryNeighborDirection[1][1] = j;
		VaryNeighborDirection[2][0] = j;VaryNeighborDirection[2][1] = 0;
		VaryNeighborDirection[3][0] = j;VaryNeighborDirection[3][1] = -j;
		VaryNeighborDirection[4][0] = 0;VaryNeighborDirection[4][1] = -j;
		VaryNeighborDirection[5][0] = -j;VaryNeighborDirection[5][1] = -j;
		VaryNeighborDirection[6][0] = -j;VaryNeighborDirection[6][1] = 0;
		VaryNeighborDirection[7][0] = -j;VaryNeighborDirection[7][1] = j;

		for(int i = 0;i < 8;i++)
		{
			StartPoint.x = centerpoint.x + VaryNeighborDirection[i][0];
			StartPoint.y = centerpoint.y + VaryNeighborDirection[i][1];
			
			if((phasemap[StartPoint.x + StartPoint.y * width] > 0.7 * PI)&&(labelmap[StartPoint.x + StartPoint.y * width] == LEVEL1))
			{
				b_research = TRUE;
				break;
			}	
		}
		j++;
	}
	return StartPoint;
}
