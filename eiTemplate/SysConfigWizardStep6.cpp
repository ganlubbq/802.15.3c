// SysConfigWizardStep1.cpp : 实现文件
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "SysConfigWizardStep6.h"
#include "afxdialogex.h"


// CSysConfigWizardStep6 对话框

IMPLEMENT_DYNAMIC(CSysConfigWizardStep6, CPropertyPage)

CSysConfigWizardStep6::CSysConfigWizardStep6()
	: CPropertyPage(CSysConfigWizardStep6::IDD)
{
	m_whiterush.CreateSolidBrush(RGB(255,255,255));
	m_font_title.CreateFont(19,0,0,0,FW_NORMAL,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
		DRAFT_QUALITY,FIXED_PITCH|FF_SWISS|FF_SCRIPT,"微软雅黑");
	m_font_content.CreatePointFont(90,"微软雅黑");
}

CSysConfigWizardStep6::~CSysConfigWizardStep6()
{
}

void CSysConfigWizardStep6::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TITLE_TEXT_STEP6, m_text_title);
	DDX_Control(pDX, IDC_CONTENT_TEXT_STEP6, m_text_content);
	DDX_Control(pDX, IDC_WIZ_NAME, m_edit_name);
	DDX_Control(pDX, IDC_WIZ_SUMMARY, m_edit_summary);
}


BEGIN_MESSAGE_MAP(CSysConfigWizardStep6, CPropertyPage)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CSysConfigWizardStep6 消息处理程序


BOOL CSysConfigWizardStep6::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_text_title.MoveWindow(25,2,300,50);
	m_text_title.SetFont(&m_font_title);
	m_text_title.SetWindowText("第六步：");
	m_text_content.MoveWindow(45,25,300,40);
	m_text_content.SetFont(&m_font_content);
	m_text_content.SetWindowText("输入您配置的连接名称并开始使用硬件系统");
	((CStatic*)GetDlgItem(IDC_SUMMARY_SYS_STEP6))->SetFont(&m_font_content);
	((CStatic*)GetDlgItem(IDC_NAME_SYS_STEP6))->SetFont(&m_font_content);

	m_edit_name.SetFont(&m_font_content);
	m_edit_name.SetWindowText("Untitled");

	m_edit_summary.SetFont(&m_font_content);
	m_edit_summary.SetWindowText("显示详细信息");


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CSysConfigWizardStep6::OnPaint()
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


HBRUSH CSysConfigWizardStep6::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


BOOL CSysConfigWizardStep6::OnSetActive()
{
	// TODO: 在此添加专用代码和/或调用基类
	CPropertySheet* psheet = (CPropertySheet*) GetParent();
	psheet->SetWizardButtons(PSWIZB_BACK|PSWIZB_FINISH);
	return CPropertyPage::OnSetActive();
}
