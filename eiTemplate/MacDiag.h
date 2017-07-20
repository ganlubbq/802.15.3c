#pragma once
#include "MacConfig_SC.h"


// CMacDiag 对话框

class CMacDiag : public CDialog
{
	DECLARE_DYNAMIC(CMacDiag)

public:
	CMacDiag(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMacDiag();

// 对话框数据
	enum { IDD = IDD_DIAG_MAC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeComboMacdiag();
	CComboBox m_ComMacdiag;//下拉菜单选项控件
	CStatic m_pic_macdiag;
	HBITMAP m_pic_macdiag1;
	HBITMAP m_pic_macdiag2;
	HBITMAP m_pic_macdiag3;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButton_MacConfig();
};
