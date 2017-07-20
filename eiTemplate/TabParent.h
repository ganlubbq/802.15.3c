#pragma once

#include "eiTemplateDoc.h"

#include "TabCarrier.h"
#include "TabProtocolConfig.h"
#include "TabInstrument.h"
// CTabParent ������ͼ

class CTabParent : public CFormView
{
	DECLARE_DYNCREATE(CTabParent)

protected:
	CTabParent();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CTabParent();

public:
	enum { IDD = IDD_TAB_PARENT };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult);
	virtual void OnInitialUpdate();

	CTabCtrl m_mainTab;
	CTabInstrument m_tabInstrument;
	CTabProtocolConfig m_tabProtocolConfig;	
	CTabCarrier m_tabCarrier;
};


