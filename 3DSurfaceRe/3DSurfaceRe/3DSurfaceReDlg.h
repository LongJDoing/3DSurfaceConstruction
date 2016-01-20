
// 3DSurfaceReDlg.h : ͷ�ļ�
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
// 3DSurfaceReDlg �Ի���
class C3DSurfaceReDlg : public CDialogEx
{
// ����
public:
	C3DSurfaceReDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_3DSURFACERE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
public:
	~C3DSurfaceReDlg();

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	afx_msg void OnTcnSelchangeTabmain(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//�Զ�����Ϣӳ�亯��

	DECLARE_MESSAGE_MAP()

private:
	// 
	CTabCtrl m_tabMain;
	CDialog1 * m_para1;
	CDialog2 * m_para2;
	CDialog3 * m_para3;

public:
	// �Զ��庯��

	// �Զ������
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
	int ** projectionplane_1samplepoint; // ͶӰ��У׼ʱ�����յõ�ƽ��1�Ĳ�����
	int ** projectionplane_2samplepoint; // ͶӰ��У׼ʱ�����յõ�ƽ��2�Ĳ�����
	double * cameracenterwordcoordinate; // �������
	double * projectioncenterwordcoordinate ; // ͶӰ����
	bool b_do;
	bool b_ifcorner; //�Ƿ���Ѱ�ҽǵ�״̬
	bool b_objectcorner; //�Ƿ���Ѱ������ǵ�״̬
	bool b_CalObject;  // �Ƿ��������д���
	bool b_calProject; // �Ƿ��Ѿ�������ͶӰ����
	double * referenceplane_1verticalphasemap, *referenceplane_1horizontalphasemap, 
		*referenceplane_2verticalphasemap, * referenceplane_2horizontalphasemap;
	double * referenceplane_1verticalabsolutephasemap, * referenceplane_1horizontalabsolutephasemap,
		* referenceplane_2verticalabsolutephasemap, * referenceplane_2horizontalabsolutephasemap;
	double ** plane_1correspondpoints;
	double ** plane_2correspondpoints;
	int  m_times;
	CImage * m_CornerImg;
	int ** plane_1projectionsamplepoints; // ѡȡ��ͶӰ������
	int samplenum; // ѡ��Ĳ�����ĸ���
	int projectionsamplepointsnum; // ���յõ��Ĳ�����ĸ���
	// 3D�ؽ�
	double * objectphasemap ;
	double * objectabsolutephasemap;

	double * PIcameracoordinate;
	double ** objectwordcoordinate;
	CImage * m_DrawBuffer; // ������
private:
	// �Զ��������
	CResizeControl  m_Resize; // �任���ڴ�С
	CMy1DMorphology * m_my1dmorphology;

public:
	void OnShowImg(CImage *, bool);
	void OnDrawImage(CImage *, CImage *);
	void OnFindPlaneCorner(CImage *, int, int); //��ƽ��Ľǵ�
	void OnFindObjectCorner(CImage *, int, int); // �ҵ�����Ľǵ�

};

