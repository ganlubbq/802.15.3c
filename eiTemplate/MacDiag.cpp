// MacDiag.cpp : 实现文件
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "MacDiag.h"
#include "afxdialogex.h"


// CMacDiag 对话框

IMPLEMENT_DYNAMIC(CMacDiag, CDialog)

CMacDiag::CMacDiag(CWnd* pParent /*=NULL*/)
	: CDialog(CMacDiag::IDD, pParent)
{
	m_pic_macdiag1 =(HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_DIAG_MACHEADER1),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS);
	m_pic_macdiag2 =(HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_DIAG_MACHEADER2),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS);
	m_pic_macdiag3 =(HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_DIAG_MACHEADER3),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS);
}

CMacDiag::~CMacDiag()
{
}

void CMacDiag::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_MACDIAG, m_ComMacdiag);
	DDX_Control(pDX, IDC_STATIC_DIAGMAC, m_pic_macdiag);
}


BEGIN_MESSAGE_MAP(CMacDiag, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_MACDIAG, &CMacDiag::OnCbnSelchangeComboMacdiag)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON1, &CMacDiag::OnBnClickedButton_MacConfig)
END_MESSAGE_MAP()


// CMacDiag 消息处理程序


void CMacDiag::OnCbnSelchangeComboMacdiag()
{
	// TODO: 在此添加控件通知处理程序代码
	switch (m_ComMacdiag.GetCurSel())
	{
	case 0:
		m_pic_macdiag.SetBitmap(m_pic_macdiag1);
		break;
	case 1:
		m_pic_macdiag.SetBitmap(m_pic_macdiag2);
		break;
	case 2:
		m_pic_macdiag.SetBitmap(m_pic_macdiag3);
		break;
	default:
		break;
	}
}


BOOL CMacDiag::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ComMacdiag.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CMacDiag::OnPaint()
{
	CRect   rect;    
	CPaintDC dc(this); // device context for painting
	GetClientRect(rect);  
	dc.FillSolidRect(rect,RGB(255,255,255));   //设置为白色背景
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
}


void CMacDiag::OnBnClickedButton_MacConfig()
{
	// TODO: 在此添加控件通知处理程序代码
	CMacConfig_SC Tab_macconfig_sc;
	Tab_macconfig_sc.DoModal();
}
