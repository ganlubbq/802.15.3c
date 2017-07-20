// TabParent.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "TabParent.h"

// CTabParent

IMPLEMENT_DYNCREATE(CTabParent, CFormView)

CTabParent::CTabParent()
	: CFormView(CTabParent::IDD)
{

}

CTabParent::~CTabParent()
{
}

void CTabParent::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_MAIN, m_mainTab);
}

BEGIN_MESSAGE_MAP(CTabParent, CFormView)
	ON_WM_SIZE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &CTabParent::OnSelchangeTabMain)
END_MESSAGE_MAP()


// CTabParent ���

#ifdef _DEBUG
void CTabParent::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CTabParent::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTabParent ��Ϣ�������


void CTabParent::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	CRect rc;

	m_mainTab.InsertItem(0,"�ز���Ϣ");
	m_mainTab.InsertItem(1,"Э�����");
	m_mainTab.InsertItem(2,"��������");

	m_tabInstrument.Create(IDD_TAB_INSTRUMENT,&m_mainTab);
	m_tabProtocolConfig.Create(IDD_TAB_PROTOCOL_CONFIG,&m_mainTab);
	m_tabCarrier.Create(IDD_TAB_CARRIER_INFO,&m_mainTab);

	m_mainTab.GetClientRect(&rc);
	m_tabCarrier.MoveWindow(0,22,rc.Width()+20,rc.Height());
	m_tabCarrier.ShowWindow(SW_SHOW);
	m_tabInstrument.MoveWindow(0,22,rc.Width()+20,rc.Height());
	m_tabInstrument.ShowWindow(SW_HIDE);
	m_tabProtocolConfig.MoveWindow(0,22,rc.Width()+20,rc.Height());
	m_tabProtocolConfig.ShowWindow(SW_HIDE);
}


void CTabParent::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);
	SetScrollSizes(MM_TEXT,CSize(0,0));
	//MessageBox("change");
	// TODO: �ڴ˴������Ϣ����������
	if (IsWindowVisible())
	{
		CRect rc;
		GetClientRect(&rc);
		m_mainTab.MoveWindow(0,0,rc.Width()+1,rc.Height()+1);
		m_mainTab.GetClientRect(&rc);
		m_tabCarrier.MoveWindow(0,22,rc.Width()+20,rc.Height());
		m_tabProtocolConfig.MoveWindow(0,22,rc.Width()+20,rc.Height());
		m_tabInstrument.MoveWindow(0,22,rc.Width()+20,rc.Height());
	}
	CFormView::ShowScrollBar(SB_BOTH, false);
}


void CTabParent::OnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int cursel = m_mainTab.GetCurSel();
	switch(cursel){
	case 0:
		m_tabCarrier.ShowWindow(SW_SHOW);
		m_tabProtocolConfig.ShowWindow(SW_HIDE);
		m_tabInstrument.ShowWindow(SW_HIDE);
		break;
	case 1:
		m_tabCarrier.ShowWindow(SW_HIDE);
		m_tabProtocolConfig.ShowWindow(SW_SHOW);
		m_tabInstrument.ShowWindow(SW_HIDE);
		break;
	case 2:
		m_tabCarrier.ShowWindow(SW_HIDE);
		m_tabProtocolConfig.ShowWindow(SW_HIDE);
		m_tabInstrument.ShowWindow(SW_SHOW);
		break;
	default:
		break;
	}
	*pResult = 0;
}
