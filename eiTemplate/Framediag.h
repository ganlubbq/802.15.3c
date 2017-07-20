#pragma once


// CFramediag 对话框

class CFramediag : public CDialog
{
	DECLARE_DYNAMIC(CFramediag)

public:
	CFramediag(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFramediag();

// 对话框数据
	enum { IDD = IDD_DIAG_FRAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	CComboBox m_ComFramediag;//下拉菜单选项控件
	virtual BOOL OnInitDialog();
	CStatic m_pic_framediag;
	HBITMAP m_pic_framediag1;
	HBITMAP m_pic_framediag2;
	HBITMAP m_pic_framediag3;
	afx_msg void OnCbnSelchangeComboFramediag();//下来菜单控件功能实现
};
