#pragma once


// CShowImageDialog 对话框

class CShowImageDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CShowImageDialog)

public:
	CShowImageDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CShowImageDialog();

// 对话框数据
	enum { IDD = IDD_SHOWIMAGEDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void OnShow(CImage *, int);
	afx_msg void OnPaint();
public:
	CImage * showimage;
};
