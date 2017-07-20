// SysConfigWizard.cpp : 实现文件
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "SysConfigWizard.h"


// CSysConfigWizard

IMPLEMENT_DYNAMIC(CSysConfigWizard, CPropertySheet)

CSysConfigWizard::CSysConfigWizard(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{

}

CSysConfigWizard::CSysConfigWizard(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	//此处的声明顺序即为页面的序号
	m_step1 = new CSysConfigWizardStep1();
	m_step1->m_psp.dwFlags &= ~PSH_HASHELP;//去掉Help按钮
	AddPage(m_step1);
	m_step2 = new CSysConfigWizardStep2();
	m_step2->m_psp.dwFlags &= ~PSH_HASHELP;//去掉Help按钮
	AddPage(m_step2);
	m_step3 = new CSysConfigWizardStep3();
	m_step3->m_psp.dwFlags &= ~PSH_HASHELP;//去掉Help按钮
	AddPage(m_step3);
	m_step4 = new CSysConfigWizardStep4();
	m_step4->m_psp.dwFlags &= ~PSH_HASHELP;//去掉Help按钮
	AddPage(m_step4);
	m_step5 = new CSysConfigWizardStep5();
	m_step5->m_psp.dwFlags &= ~PSH_HASHELP;//去掉Help按钮
	AddPage(m_step5);
	m_step6 = new CSysConfigWizardStep6();
	m_step6->m_psp.dwFlags &= ~PSH_HASHELP;//去掉Help按钮
	AddPage(m_step6);

	SetActivePage(iSelectPage); //打开向导时默认显示的页面.
	SetWizardMode(); //指定为向导模式

	m_font.CreatePointFont(90,"微软雅黑");

	m_num_instruments = 0;
	m_function_choice = 0;

	m_option_dir = "";
	m_option_name = "";

	for (int i = 0;i<8;i++)
	{
		str_conn[i] = "";
		vi_error_info[i] = 0;
	}
	
	b_instr_connected = FALSE;
}

CSysConfigWizard::~CSysConfigWizard()
{
	delete m_step1;
	delete m_step2;
	delete m_step3;
	delete m_step4;
	delete m_step5;
	delete m_step6;
	m_step1 = 0;
	m_step2 = 0;
	m_step3 = 0;
	m_step4 = 0;
	m_step5 = 0;
	m_step6 = 0;
}


BEGIN_MESSAGE_MAP(CSysConfigWizard, CPropertySheet)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CSysConfigWizard 消息处理程序



BOOL CSysConfigWizard::OnInitDialog()
{
	BOOL bResult = CPropertySheet::OnInitDialog();

	// TODO:  在此添加您的专用代码
	CRect rc;
	/************************************************************************/
	/* 对底部按钮的字体和内容做一些自己的定制                               */
	/************************************************************************/
	CButton* p_btn_back = ((CButton*)GetDlgItem(ID_WIZBACK));
	CButton* p_btn_next = ((CButton*)GetDlgItem(ID_WIZNEXT));
	CButton* p_btn_cancel = ((CButton*)GetDlgItem(IDCANCEL));
	CButton* p_btn_finish = ((CButton*)GetDlgItem(ID_WIZFINISH));
	p_btn_back->SetFont(&m_font);
	p_btn_back->SetWindowText("< 上一步");
	p_btn_next->SetFont(&m_font);
	p_btn_next->SetWindowText("下一步 >");
	p_btn_cancel->SetFont(&m_font);
	p_btn_finish->SetFont(&m_font);

	return bResult;
}


void CSysConfigWizard::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	/************************************************************************/
	/* 绘制上方的白色背景                                                   */
	/************************************************************************/
	CBrush brush(RGB(255,255,255));
	dc.FillRect(CRect(0,0,620,80),&brush);
	/************************************************************************/
	/* 绘制上下分割线                                                       */
	/************************************************************************/
	CPen pen_top,pen_bottom;
	pen_top.CreatePen(PS_SOLID,1,RGB(160,160,160));
	dc.SelectObject(pen_top);
	dc.MoveTo(0,78);
	dc.LineTo(620,78);
	pen_bottom.CreatePen(PS_SOLID,1,RGB(255,255,255));
	dc.SelectObject(pen_bottom);
	dc.MoveTo(0,79);
	dc.LineTo(620,79);
	//dc.MoveTo(0,394);
	//dc.LineTo(485,394);

	// 不为绘图消息调用 CPropertySheet::OnPaint()
}
