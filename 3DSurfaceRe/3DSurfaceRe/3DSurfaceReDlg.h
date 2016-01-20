
// 3DSurfaceReDlg.h : 头文件
//
#pragma once
#include <vector>
#include <iostream>

#include "Dialog1.h"
#include "Dialog2.h"
#include "Dialog3.h"
#include "MyDIdefine.h"
#include "ResizeControl.h"
#include "My1DMorphology.h"

using namespace std;
//extern ofstream fout;
class CDialog1;
class CDialog2;
class CDialog3;
class CMy1DMorphology;
// 3DSurfaceReDlg 对话框
class C3DSurfaceReDlg : public CDialogEx
{
// 构造
public:
	C3DSurfaceReDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_3DSURFACERE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
public:
	~C3DSurfaceReDlg();

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	afx_msg void OnTcnSelchangeTabmain(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//自定义消息映射函数

	DECLARE_MESSAGE_MAP()

private:
	// 
	CTabCtrl m_tabMain;
	CDialog1 * m_para1;
	CDialog2 * m_para2;
	CDialog3 * m_para3;

public:
	// 自定义函数

	// 自定义变量
	int m_Width;
	int m_Height;
	vector <CImage *> m_ImageArray; 
	int * labelmap;
	int * hreferencelabelmap;
	int * vreferencelabelmap;
	int * objectlabelmap;
	bool b_is;
	CPoint startpoint;
	CPoint referencepoint;
	int ** projectionplane_1samplepoint; // 投影仪校准时，最终得到平面1的采样点
	int ** projectionplane_2samplepoint; // 投影仪校准时，最终得到平面2的采样点
	double * cameracenterwordcoordinate; // 相机中心
	double * projectioncenterwordcoordinate ; // 投影中心
	bool b_do;
	bool b_ifcorner; //是否处于寻找角点状态
	bool b_objectcorner; //是否处于寻找物体角点状态
	bool b_CalObject;  // 是否对物体进行处理
	bool b_calProject; // 是否已经计算了投影中心
	double * referenceplane_1verticalphasemap, *referenceplane_1horizontalphasemap, 
		*referenceplane_2verticalphasemap, * referenceplane_2horizontalphasemap;
	double * referenceplane_1verticalabsolutephasemap, * referenceplane_1horizontalabsolutephasemap,
		* referenceplane_2verticalabsolutephasemap, * referenceplane_2horizontalabsolutephasemap;
	double ** plane_1correspondpoints;
	double ** plane_2correspondpoints;
	int  m_times;
	CImage * m_CornerImg;
	int ** plane_1projectionsamplepoints; // 选取的投影采样点
	int samplenum; // 选择的采样点的个数
	int projectionsamplepointsnum; // 最终得到的采样点的个数
	// 3D重建
	double * objectphasemap ;
	double * objectabsolutephasemap;

	double * PIcameracoordinate;
	double ** objectwordcoordinate;
	CImage * m_DrawBuffer; // 缓存区
private:
	// 自定义类变量
	CResizeControl  m_Resize; // 变换窗口大小
	CMy1DMorphology * m_my1dmorphology;

public:
	void OnShowImg(CImage *, bool);
	void OnDrawImage(CImage *, CImage *);
	void OnFindPlaneCorner(CImage *, int, int); //找平面的角点
	void OnFindObjectCorner(CImage *, int, int); // 找到物体的角点

};

