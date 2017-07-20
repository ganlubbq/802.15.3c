#pragma once


// CMySplitterWnd

class CMySplitterWnd : public CSplitterWnd
{
	DECLARE_DYNAMIC(CMySplitterWnd)

public:
	double m_splitterScale;

	CMySplitterWnd();
	virtual ~CMySplitterWnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnDrawSplitter(CDC* pDC, ESplitType nType, const CRect& rect);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};


