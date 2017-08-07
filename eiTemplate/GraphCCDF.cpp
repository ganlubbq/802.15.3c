// GraphCCDF.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "GraphCCDF.h"


// CGraphCCDF

IMPLEMENT_DYNCREATE(CGraphCCDF, CFormView)

CGraphCCDF::CGraphCCDF()
	: CFormView(CGraphCCDF::IDD)
{
	m_firstCreate = TRUE;
}

CGraphCCDF::~CGraphCCDF()
{
}

void CGraphCCDF::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_CCDF, m_ccdf);
	DDX_Control(pDX, IDC_COMBO_CCDF, m_comboCCDF);
}

BEGIN_MESSAGE_MAP(CGraphCCDF, CFormView)
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(IDC_COMBO_CCDF, &CGraphCCDF::OnSelchangeComboCcdf)
END_MESSAGE_MAP()

//BEGIN_EASYSIZE_MAP(CGraphCCDF)
//	EASYSIZE(IDC_ICON_CCDF,ES_BORDER,ES_BORDER,ES_KEEPSIZE,ES_KEEPSIZE,0)
//	EASYSIZE(IDC_COMBO_CCDF,IDC_ICON_CCDF,ES_BORDER,ES_KEEPSIZE,ES_KEEPSIZE,0)
//	EASYSIZE(IDC_CHECK_GAUSSIAN,IDC_COMBO_CCDF,ES_BORDER,ES_KEEPSIZE,ES_KEEPSIZE,0)
//	EASYSIZE(IDC_CHECK_REF,IDC_CHECK_GAUSSIAN,ES_BORDER,ES_KEEPSIZE,ES_KEEPSIZE,0)
//	EASYSIZE(IDC_STATIC_CCDF,ES_BORDER,IDC_ICON_CCDF,ES_BORDER,ES_BORDER,0)
//END_EASYSIZE_MAP
// CGraphCCDF ���

#ifdef _DEBUG
void CGraphCCDF::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CGraphCCDF::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CGraphCCDF ��Ϣ�������


void CGraphCCDF::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);
	// TODO: �ڴ˴������Ϣ����������
	/************************************************************************/
	/* CFormView��CDialog�಻ͬ����easysize��ĳ�ʼ������û����initialDialog*/
	/* �����,������Ҫ��onsize������һ�ε��õ�ʱ���ʼ���ú꣬���ڳ�ʼ���ú�*/
	/* ֮���onsize�н��гߴ�仯����Ӧ����									*/
	/* ��:CGraphWAVE�ڴ˴���ʵ�ַ�����ͬ�����Ǳߵĺ����в���׸��			*/
	/************************************************************************/
	//if (m_firstCreate && /*IsWindowVisible()&&*/ GetWindow(GW_CHILD)!=NULL)
	//{
	//	INIT_EASYSIZE;
	//	m_firstCreate = FALSE;
	//	SetScrollSizes(MM_TEXT,CSize(0,0));
	//	UPDATE_EASYSIZE;
	//}else if (!m_firstCreate)
	//{
	//	SetScrollSizes(MM_TEXT,CSize(0,0));
	//	UPDATE_EASYSIZE;
	//}
	if (IsWindowVisible() && GetWindow(GW_CHILD)!=NULL)
	{
		SetScrollSizes(MM_TEXT,CSize(0,0));
		CRect rc;
		GetClientRect(&rc);
		//ʵ�����ŵķ��������ڴ��ڳߴ��С��ʱ��������ʾ
		if (rc.Height()<75 || rc.Width()<40)
		{
			m_ccdf.ShowWindow(SW_HIDE);
		}else{
			m_ccdf.ShowWindow(SW_SHOW);
			m_ccdf.MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
			m_ccdf.Invalidate();
		}
		//ʵ�����ŵķ����������������ſ��ƺ����б�������ͼ�ĸ߶ȹ�С
		//m_ccdf.MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
		//m_ccdf.Invalidate();
	}
	CFormView::ShowScrollBar(SB_BOTH, false);
}


void CGraphCCDF::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	m_comboCCDF.SetCurSel(0);

}


void CGraphCCDF::OnSelchangeComboCcdf()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	switch(m_comboCCDF.GetCurSel())
	{
	case 0:
		m_ccdf.burstflag();
		break;
	case 1:
		m_ccdf.waveflag();
		break;
	}
}
