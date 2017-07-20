
// eiTemplateView.h : CeiTemplateView 类的接口
//

#pragma once

#include "eiTemplateDoc.h"

class CeiTemplateView : public CView
{
protected: // 仅从序列化创建
	CeiTemplateView();
	DECLARE_DYNCREATE(CeiTemplateView)

// 特性
public:
	CeiTemplateDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CeiTemplateView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
};

#ifndef _DEBUG  // eiTemplateView.cpp 中的调试版本
inline CeiTemplateDoc* CeiTemplateView::GetDocument() const
   { return reinterpret_cast<CeiTemplateDoc*>(m_pDocument); }
#endif

