// GraphCCDF.cpp : 实现文件
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
// CGraphCCDF 诊断

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


// CGraphCCDF 消息处理程序


void CGraphCCDF::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);
	// TODO: 在此处添加消息处理程序代码
	/************************************************************************/
	/* CFormView与CDialog类不同，对easysize宏的初始化操作没法在initialDialog*/
	/* 中完成,所以需要在onsize函数第一次调用的时候初始化该宏，并在初始化该宏*/
	/* 之后的onsize中进行尺寸变化的响应调整									*/
	/* 另:CGraphWAVE在此处的实现方法相同，在那边的函数中不予赘述			*/
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
		//实现缩放的方法二：在窗口尺寸过小的时候隐藏显示
		if (rc.Height()<75 || rc.Width()<40)
		{
			m_ccdf.ShowWindow(SW_HIDE);
		}else{
			m_ccdf.ShowWindow(SW_SHOW);
			m_ccdf.MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
			m_ccdf.Invalidate();
		}
		//实现缩放的方法三：在外层的缩放控制函数中避免子视图的高度过小
		//m_ccdf.MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
		//m_ccdf.Invalidate();
	}
	CFormView::ShowScrollBar(SB_BOTH, false);
}


void CGraphCCDF::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	m_comboCCDF.SetCurSel(0);

}


void CGraphCCDF::OnSelchangeComboCcdf()
{
	// TODO: 在此添加控件通知处理程序代码
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
