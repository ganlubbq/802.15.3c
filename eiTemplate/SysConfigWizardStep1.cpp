// SysConfigWizardStep1.cpp : 实现文件
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "SysConfigWizardStep1.h"
#include "afxdialogex.h"
#include "SysConfigWizard.h"


// CSysConfigWizardStep1 对话框

IMPLEMENT_DYNAMIC(CSysConfigWizardStep1, CPropertyPage)

CSysConfigWizardStep1::CSysConfigWizardStep1()
	: CPropertyPage(CSysConfigWizardStep1::IDD)
{
	m_whiterush.CreateSolidBrush(RGB(255,255,255));
	m_font_title.CreateFont(19,0,0,0,FW_NORMAL,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
		DRAFT_QUALITY,FIXED_PITCH|FF_SWISS|FF_SCRIPT,"微软雅黑");
	m_font_content.CreatePointFont(90,"微软雅黑");
}

CSysConfigWizardStep1::~CSysConfigWizardStep1()
{
}

void CSysConfigWizardStep1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TITLE_TEXT_STEP1, m_text_title);
	DDX_Control(pDX, IDC_CONTENT_TEXT_STEP1, m_text_content);
	DDX_Control(pDX, IDC_WIZ_LIST_STEP1, m_list_function);
}


BEGIN_MESSAGE_MAP(CSysConfigWizardStep1, CPropertyPage)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CSysConfigWizardStep1 消息处理程序


BOOL CSysConfigWizardStep1::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化
	/************************************************************************/
	/* 设置各个控件的显示字体和文本                                         */
	/************************************************************************/
	m_text_title.MoveWindow(25,2,300,50);
	m_text_title.SetFont(&m_font_title);
	m_text_title.SetWindowText("第一步：");

	m_text_content.MoveWindow(45,25,300,40);
	m_text_content.SetFont(&m_font_content);
	m_text_content.SetWindowText("选择配置项：从下面的列表框中选择一项协议配置");

	m_list_function.SetFont(&m_font_content);
	m_list_function.InsertString(0,"IEEE 802.15.3c配置向导");
	//m_list_function.InsertString(1,"IEEE 802.11ac M×2 MIMO");
	//m_list_function.InsertString(2,"IEEE 802.11ac M×3 MIMO");
	//m_list_function.InsertString(3,"IEEE 802.11ac M×4 MIMO");
	//m_list_function.InsertString(4,"IEEE 802.11ac M×5 MIMO");
	//m_list_function.InsertString(5,"IEEE 802.11ac M×6 MIMO");
	//m_list_function.InsertString(6,"IEEE 802.11ac M×7 MIMO");
	//m_list_function.InsertString(7,"IEEE 802.11ac M×8 MIMO");
	//m_list_function.InsertString(8,"IEEE 802.11ac M×N MIMO (with 1 SG switching between different waveforms)");
	m_list_function.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CSysConfigWizardStep1::OnPaint()
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


HBRUSH CSysConfigWizardStep1::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


BOOL CSysConfigWizardStep1::OnSetActive()
{
	// TODO: 在此添加专用代码和/或调用基类
	CPropertySheet* psheet = (CPropertySheet*) GetParent();
	//设置属性表只有“下一步”按钮
	psheet->SetWizardButtons(PSWIZB_NEXT);
	return CPropertyPage::OnSetActive();
}


LRESULT CSysConfigWizardStep1::OnWizardNext()
{
	// TODO: 在此添加专用代码和/或调用基类
	/************************************************************************/
	/* 第一步的配置主要是为了确定使用的仪器数量                             */
	/************************************************************************/
	CSysConfigWizard* p_wiz = (CSysConfigWizard*)GetParent();
	int cur_sel = m_list_function.GetCurSel();
	p_wiz->m_function_choice = cur_sel;
	p_wiz->m_num_instruments = 1;
	CString str = "";
	str.Format("./user/config_list/Instr_Sel_%d.conf",cur_sel);
	p_wiz->m_config_list_dir = str;
	str.Format("./user/Instr_Sel_%d/",cur_sel);
	p_wiz->m_option_dir = str;
	
	//CString str;
	//str.Format("%d",p_wiz->m_num_instruments);
	//MessageBox(str);
	return CPropertyPage::OnWizardNext();
}
