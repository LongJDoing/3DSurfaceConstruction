#pragma once


// CShowImageDialog �Ի���

class CShowImageDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CShowImageDialog)

public:
	CShowImageDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CShowImageDialog();

// �Ի�������
	enum { IDD = IDD_SHOWIMAGEDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	void OnShow(CImage *, int);
	afx_msg void OnPaint();
public:
	CImage * showimage;
};
