#pragma once

#include "eiTemplateDoc.h"
#include "W.h"


// CGraphWAVE 窗体视图

class CGraphWAVE : public CFormView
{
	DECLARE_DYNCREATE(CGraphWAVE)
	//DECLARE_EASYSIZE;
protected:
	CGraphWAVE();	// 动态创建所使用的受保护的构造函数
	virtual ~CGraphWAVE();

public:
	enum { IDD = IDD_DIALOG_WAVE };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchangeComboWave();
	virtual void OnInitialUpdate();
	
	BOOL m_firstCreate;
	CComboBox	m_comboWAVE;
	CW m_wave;
	//CStatic m_wave;
};
