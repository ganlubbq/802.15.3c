// SysConfigWizardStep1.cpp : 实现文件
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "SysConfigWizardStep5.h"
#include "afxdialogex.h"
#include "SysConfigWizard.h"

// CSysConfigWizardStep5 对话框

IMPLEMENT_DYNAMIC(CSysConfigWizardStep5, CPropertyPage)

CSysConfigWizardStep5::CSysConfigWizardStep5()
	: CPropertyPage(CSysConfigWizardStep5::IDD)
{
	m_whiterush.CreateSolidBrush(RGB(255,255,255));
	m_font_title.CreateFont(19,0,0,0,FW_NORMAL,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
		DRAFT_QUALITY,FIXED_PITCH|FF_SWISS|FF_SCRIPT,"微软雅黑");
	m_font_content.CreatePointFont(90,"微软雅黑");
	b_send_conn = TRUE;
}

CSysConfigWizardStep5::~CSysConfigWizardStep5()
{
}

void CSysConfigWizardStep5::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TITLE_TEXT_STEP5, m_text_title);
	DDX_Control(pDX, IDC_CONTENT_TEXT_STEP5, m_text_content);
	DDX_Control(pDX, IDC_WZD_CONNECTION_INFO, m_connection_info);
}


BEGIN_MESSAGE_MAP(CSysConfigWizardStep5, CPropertyPage)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CSysConfigWizardStep5 消息处理程序


BOOL CSysConfigWizardStep5::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_text_title.MoveWindow(25,2,300,50);
	m_text_title.SetFont(&m_font_title);
	m_text_title.SetWindowText("第五步：");
	m_text_content.MoveWindow(45,25,300,40);
	m_text_content.SetFont(&m_font_content);
	m_text_content.SetWindowText("测试信号发生器的 I/O 接口连接状态");

	m_connection_info.SetFont(&m_font_content);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CSysConfigWizardStep5::OnPaint()
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
	/* 这里用来响应对应上一步配置的连接情况                                 */
	/************************************************************************/
	if (b_send_conn)
	{
		b_send_conn = FALSE;
		CSysConfigWizard* p_wiz = (CSysConfigWizard*)GetParent();
		int num_instr = p_wiz->m_num_instruments;
		ViStatus stat = 0;
		stat = viOpenDefaultRM(&(p_wiz->defaultRM));
		Sleep(10);
		//根据仪器的数量发送程控连接命令并保存状态码
		for (int i = 0;i<num_instr;i++)
		{
			p_wiz->vi_error_info[i] = viOpen(p_wiz->defaultRM,p_wiz->str_conn[i].GetBuffer(),VI_NULL,VI_NULL,&(p_wiz->vi[i]));
			Sleep(10);
			if (p_wiz->vi_error_info[i]>=0)
			{
				viSetAttribute(p_wiz->vi[i],VI_ATTR_TMO_VALUE,2000);
				Sleep(10);
				viSetAttribute(p_wiz->vi[i],VI_ATTR_TERMCHAR_EN,VI_TRUE);
				Sleep(10);
				viSetAttribute(p_wiz->vi[i],VI_ATTR_TERMCHAR,'\n');
				Sleep(10);
			}
		}
		//判断仪器连接是否成功(所有仪器连接成功返回TRUE,否则返回FALSE)
		BOOL temp_connected = TRUE;
		for (int i = 0;i<num_instr;i++)
		{
			temp_connected &= (p_wiz->vi_error_info[i] >= 0);
		}
		p_wiz->b_instr_connected = temp_connected;
		/****************如果连接错误则返回IP设置界面*****************/
		if (temp_connected == FALSE) {
			MessageBox( "设备连接错误", "Init Error!", MB_OK | MB_ICONERROR );
			OnWizardBack();
			CSysConfigWizard* p_wiz = (CSysConfigWizard*)GetParent();
			p_wiz->SetActivePage(3);
		}
	}
	// 不为绘图消息调用 CPropertyPage::OnPaint()
}


HBRUSH CSysConfigWizardStep5::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


BOOL CSysConfigWizardStep5::OnSetActive()
{
	// TODO: 在此添加专用代码和/或调用基类
	CPropertySheet* psheet = (CPropertySheet*) GetParent();
	psheet->SetWizardButtons(PSWIZB_NEXT|PSWIZB_BACK);
	return CPropertyPage::OnSetActive();
}


LRESULT CSysConfigWizardStep5::OnWizardBack()
{
	// TODO: 在此添加专用代码和/或调用基类
	/************************************************************************/
	/* 如果在这一页按下了返回按钮，说明用户要重新定义连接信息，所以需要断开 */
	/* 现有成功的连接，准备下一次程控命令的发送                             */
	/************************************************************************/
	b_send_conn = TRUE;
	CSysConfigWizard* p_wiz = (CSysConfigWizard*)GetParent();
	int num_instr = p_wiz->m_num_instruments;
	ViStatus stat = 0;
	for (int i = 0;i<num_instr;i++)
	{
		if (p_wiz->vi_error_info >= 0)
		{
			//断开连接成功的仪器
			stat = viClear(p_wiz->vi[i]);
			stat = viClose(p_wiz->vi[i]);
		}
	}
	stat = viClose(p_wiz->defaultRM);
	return CPropertyPage::OnWizardBack();
}
