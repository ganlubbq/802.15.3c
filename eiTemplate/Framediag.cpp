// Framediag.cpp : 实现文件
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "Framediag.h"
#include "afxdialogex.h"


// CFramediag 对话框

IMPLEMENT_DYNAMIC(CFramediag, CDialog)

CFramediag::CFramediag(CWnd* pParent /*=NULL*/)
	: CDialog(CFramediag::IDD, pParent)
{
	m_pic_framediag1 =(HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_DIAG_FRAME1),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS);
	m_pic_framediag2 =(HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_DIAG_FRAME2),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS);
	m_pic_framediag3 =(HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_DIAG_FRAME3),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS);
}

CFramediag::~CFramediag()
{
}

void CFramediag::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_FRAMEDIAG, m_ComFramediag);
	DDX_Control(pDX, IDC_STATIC_FRAMEDIAG, m_pic_framediag);
}


BEGIN_MESSAGE_MAP(CFramediag, CDialog)
	ON_WM_PAINT()
ON_CBN_SELCHANGE(IDC_COMBO_FRAMEDIAG, &CFramediag::OnCbnSelchangeComboFramediag)
END_MESSAGE_MAP()


// CFramediag 消息处理程序


void CFramediag::OnPaint()
{
	CRect   rect;    
	CPaintDC dc(this); // device context for painting
	GetClientRect(rect);  
	dc.FillSolidRect(rect,RGB(255,255,255));   //设置为白色背景
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
}


BOOL CFramediag::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ComFramediag.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CFramediag::OnCbnSelchangeComboFramediag()
{
	// TODO: 在此添加控件通知处理程序代码
	switch (m_ComFramediag.GetCurSel())
	{
	case 0:
		m_pic_framediag.SetBitmap(m_pic_framediag1);
		break;
	case 1:
		m_pic_framediag.SetBitmap(m_pic_framediag2);
		break;
	case 2:
		m_pic_framediag.SetBitmap(m_pic_framediag3);
		break;
	default:
		break;
	}
}
