// MySplitterWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "MySplitterWnd.h"


// CMySplitterWnd

IMPLEMENT_DYNAMIC(CMySplitterWnd, CSplitterWnd)

CMySplitterWnd::CMySplitterWnd()
{
	m_splitterScale = 0.5;
}

CMySplitterWnd::~CMySplitterWnd()
{
}


BEGIN_MESSAGE_MAP(CMySplitterWnd, CSplitterWnd)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CMySplitterWnd 消息处理程序


void CMySplitterWnd::OnDrawSplitter(CDC* pDC, ESplitType nType, const CRect& rectArg)
{
	// TODO: 在此添加专用代码和/或调用基类

	CSplitterWnd::OnDrawSplitter(pDC, nType, rectArg);
	if(pDC==NULL)
	{
		RedrawWindow(rectArg,NULL,RDW_INVALIDATE|RDW_NOCHILDREN);
		return;
	}
	if (nType == splitBar)
		pDC->FillSolidRect(rectArg,RGB(237,239,252));
	if (GetRowCount()==2)	//判断如果是右边的两个子分割窗口，就实时计算出当前上下两个窗口所占的比例
	{
		CRect rc_top,rc_bottom;
		GetPane(0,0)->GetClientRect(&rc_top);
		GetPane(1,0)->GetClientRect(&rc_bottom);
		m_splitterScale = (double)rc_top.Height() / ((double)rc_top.Height() + (double)rc_bottom.Height());
	}
}



void CMySplitterWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	/************************************************************************/
	/*重载鼠标移动消息处理的目的是限制分隔条的作用范围，因为我们的软件由两个*/
	/*分割类组成，这两个类一个分割为一行一个分割为两行，通过获取分割的行数就*/
	/*很容易判断当前在响应此函数的是左边的分割窗口还是右边的分割窗口，从而进*/
	/*一步根据鼠标的位置进行移动的限制										*/
	/*当前版本规定左侧分隔栏宽度不能小于200，右侧两个分隔块的高度不能小于30 */
	/************************************************************************/
	if (GetRowCount()==1)	//只有一行，代表是主分割窗口
	{
		CRect rect;
		GetClientRect(&rect);
		if (point.x<=200 || point.x>=rect.Width()-35)
		{
			CWnd::OnMouseMove(nFlags,point);
			return;
		}
	}
	if (GetRowCount()==2)	//有两行，代表是右边的子分割窗口
	{
		CRect rect;
		GetClientRect(&rect);
		if (point.y<=30 || point.y>=(rect.Height()-30))
		{
			CWnd::OnMouseMove(nFlags,point);
			return;
		}
	}
	CSplitterWnd::OnMouseMove(nFlags, point);
}
