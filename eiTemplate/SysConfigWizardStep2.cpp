// SysConfigWizardStep2.cpp : 实现文件
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "SysConfigWizardStep2.h"
#include "afxdialogex.h"
#include "SysConfigWizard.h"

// CSysConfigWizardStep2 对话框

IMPLEMENT_DYNAMIC(CSysConfigWizardStep2, CPropertyPage)

CSysConfigWizardStep2::CSysConfigWizardStep2()
	: CPropertyPage(CSysConfigWizardStep2::IDD)
{
	m_whiterush.CreateSolidBrush(RGB(255,255,255));
	m_font_title.CreateFont(19,0,0,0,FW_NORMAL,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
		DRAFT_QUALITY,FIXED_PITCH|FF_SWISS|FF_SCRIPT,"微软雅黑");
	m_font_content.CreatePointFont(90,"微软雅黑");
	m_pic_instr1 =(HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_WIZ_INSTR1),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS);
	m_pic_instr2 =(HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_WIZ_INSTR2),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS);
	m_pic_instr3 =(HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_WIZ_INSTR3),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS);
	m_pic_instr4 =(HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_WIZ_INSTR4),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS);
	m_pic_instr5 =(HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_WIZ_INSTR5),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS);
	m_pic_instr6 =(HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_WIZ_INSTR6),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS);
}

CSysConfigWizardStep2::~CSysConfigWizardStep2()
{
}

void CSysConfigWizardStep2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TITLE_TEXT_STEP2, m_text_title);
	DDX_Control(pDX, IDC_CONTENT_TEXT_STEP2, m_text_content);
	DDX_Control(pDX, IDC_WIZ_INSTR_PREVIEW, m_pic_instr);
	DDX_Control(pDX, IDC_WIZ_LIST_STEP2, m_list);
}


BEGIN_MESSAGE_MAP(CSysConfigWizardStep2, CPropertyPage)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_LBN_SELCHANGE(IDC_WIZ_LIST_STEP2, &CSysConfigWizardStep2::OnSelchangeWizListStep2)
END_MESSAGE_MAP()


// CSysConfigWizardStep2 消息处理程序

BOOL CSysConfigWizardStep2::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_text_title.MoveWindow(25,2,300,50);
	m_text_title.SetFont(&m_font_title);
	m_text_title.SetWindowText("第二步：");
	m_text_content.MoveWindow(45,25,300,40);
	m_text_content.SetFont(&m_font_content);
	m_text_content.SetWindowText("选择仪器：从下面的列表框中选择一种仪器进行配置");

	m_list.SetFont(&m_font_content);
	m_list.MoveWindow(24,100,395,140);
	m_list.InsertString(0,"MXG/ESG/PSG Signal Generator");
	m_list.InsertString(1,"EXT");
	m_list.InsertString(2,"M9281A PXIe Vector Signal Generator");
	m_list.InsertString(3,"M8190A Arbitrary Waveform Geneerator");
	m_list.InsertString(4,"E6630 Wireless Connectivity Test Set");
	m_list.InsertString(5,"PXB");
	m_list.SetCurSel(0);

	m_pic_instr.MoveWindow(24,255,395,106);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CSysConfigWizardStep2::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	/************************************************************************/
	/* 绘制上方的白色背景                                                   */
	/************************************************************************/
	CBrush brush(RGB(255,255,255));
	dc.FillRect(CRect(0,0,620,66),&brush);
	/************************************************************************/
	/* 绘制上方的分割线                                                     */
	/************************************************************************/
	CPen pen_top,pen_bottom;
	pen_top.CreatePen(PS_SOLID,1,RGB(160,160,160));
	dc.SelectObject(pen_top);//选择画笔
	dc.MoveTo(0,67);
	dc.LineTo(620,67);
	pen_bottom.CreatePen(PS_SOLID,1,RGB(255,255,255));
	dc.SelectObject(pen_bottom);
	dc.MoveTo(0,68);
	dc.LineTo(620,68);
	//pen_bottom.CreatePen(PS_SOLID,1,RGB(255,255,255));
	//dc.SelectObject(pen_bottom);
	//dc.MoveTo(0,70);
	//dc.LineTo(485,70);
	/************************************************************************/
	/* 通过下面的代码，结合CSysConfigWizard中的全局变量，可以实现界面在不同 */
	/* 的配置下实现特定的显示效果											*/
	/************************************************************************/


	// 不为绘图消息调用 CPropertyPage::OnPaint()
}


HBRUSH CSysConfigWizardStep2::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (m_text_title.m_hWnd == pWnd->m_hWnd || m_text_content.m_hWnd == pWnd->m_hWnd)
	{
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SetBkColor(RGB(255, 255, 255));
		return m_whiterush;
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


BOOL CSysConfigWizardStep2::OnSetActive()
{
	// TODO: 在此添加专用代码和/或调用基类
	CPropertySheet* psheet = (CPropertySheet*) GetParent();
	psheet->SetWizardButtons(PSWIZB_NEXT|PSWIZB_BACK);
	return CPropertyPage::OnSetActive();
}


void CSysConfigWizardStep2::OnSelchangeWizListStep2()
{
	// TODO: 在此添加控件通知处理程序代码
	/************************************************************************/
	/* 选择不同仪器时预览图的切换                                           */
	/************************************************************************/
	switch (m_list.GetCurSel())
	{
	case 0:
		m_pic_instr.SetBitmap(m_pic_instr1);
		break;
	case 1:
		m_pic_instr.SetBitmap(m_pic_instr2);
		break;
	case 2:
		m_pic_instr.SetBitmap(m_pic_instr3);
		break;
	case 3:
		m_pic_instr.SetBitmap(m_pic_instr4);
		break;
	case 4:
		m_pic_instr.SetBitmap(m_pic_instr5);
		break;
	case 5:
		m_pic_instr.SetBitmap(m_pic_instr6);
		break;
	default:
		break;
	}
}
