// SysConfigWizardStep1.cpp : 实现文件
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "SysConfigWizardStep3.h"
#include "SysConfigWizardStep3ViewDetail.h"
#include "afxdialogex.h"
#include "SysConfigWizard.h"

using namespace rapidxml;

// CSysConfigWizardStep3 对话框

IMPLEMENT_DYNAMIC(CSysConfigWizardStep3, CPropertyPage)

CSysConfigWizardStep3::CSysConfigWizardStep3()
	: CPropertyPage(CSysConfigWizardStep3::IDD)
{
	m_whiterush.CreateSolidBrush(RGB(255,255,255));
	m_font_title.CreateFont(19,0,0,0,FW_NORMAL,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
		DRAFT_QUALITY,FIXED_PITCH|FF_SWISS|FF_SCRIPT,"微软雅黑");
	m_font_content.CreatePointFont(90,"微软雅黑");
}

CSysConfigWizardStep3::~CSysConfigWizardStep3()
{
}

void CSysConfigWizardStep3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TITLE_TEXT_STEP3, m_text_title);
	DDX_Control(pDX, IDC_CONTENT_TEXT_STEP3, m_text_content);
	DDX_Control(pDX, IDC_WIZ_LIST_STEP3, m_list);
	DDX_Control(pDX, IDC_BUTTON_VIEWDETAIL, m_btn_viewdetial);
	DDX_Control(pDX, IDC_BUTTON_DELETEITEM, m_btn_deleteitem);
}


BEGIN_MESSAGE_MAP(CSysConfigWizardStep3, CPropertyPage)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_LBN_SELCHANGE(IDC_WIZ_LIST_STEP3, &CSysConfigWizardStep3::OnSelchangeWizListStep3)
	ON_BN_CLICKED(IDC_BUTTON_VIEWDETAIL, &CSysConfigWizardStep3::OnBnClickedButtonViewdetail)
	ON_BN_CLICKED(IDC_BUTTON_DELETEITEM, &CSysConfigWizardStep3::OnBnClickedButtonDeleteitem)
END_MESSAGE_MAP()


// CSysConfigWizardStep3 消息处理程序


BOOL CSysConfigWizardStep3::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_text_title.MoveWindow(25,2,300,50);
	m_text_title.SetFont(&m_font_title);
	m_text_title.SetWindowText("第三步：");
	m_text_content.MoveWindow(45,25,400,40);
	m_text_content.SetFont(&m_font_content);
	m_text_content.SetWindowText("如果下边列表里已经存在连接信息，可以直接选择其中之一\r\n您也可以通过<新建>去创建新的连接信息");

	m_btn_deleteitem.SetFont(&m_font_content);
	m_btn_viewdetial.SetFont(&m_font_content);

	m_list.SetFont(&m_font_content);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CSysConfigWizardStep3::OnPaint()
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
	/* 根据第一步中选择的配置选项读取相应的文件进行列表的初始化             */
	/************************************************************************/
	CSysConfigWizard* p_wiz = (CSysConfigWizard*)GetParent();
	/************************************************************************/
	/* 解析对应的xml文件，根据文件的内容填写此处的list应该显示的配置项      */
	/************************************************************************/
	file<> fdoc(p_wiz->m_config_list_dir.GetBuffer());
	xml_document<> doc;
	doc.parse<0>(fdoc.data());
	// 获取根节点  
	xml_node<>* p_WizardList = doc.first_node();
	
	while(m_list.GetCount())
	{
		m_list.DeleteString(0);
	}
	int i = 0;
	for (xml_node<>* p_ConfigOption = p_WizardList->first_node();p_ConfigOption;p_ConfigOption=p_ConfigOption->next_sibling(),i++)
	{
		m_list.InsertString(i,p_ConfigOption->value());
	}
	m_list.SetCurSel(0);
	m_btn_deleteitem.EnableWindow(FALSE);
	m_btn_viewdetial.EnableWindow(FALSE);

	// 不为绘图消息调用 CPropertyPage::OnPaint()
}


HBRUSH CSysConfigWizardStep3::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


BOOL CSysConfigWizardStep3::OnSetActive()
{
	// TODO: 在此添加专用代码和/或调用基类
	CPropertySheet* psheet = (CPropertySheet*) GetParent();
	psheet->SetWizardButtons(PSWIZB_NEXT|PSWIZB_BACK);
	return CPropertyPage::OnSetActive();
}


void CSysConfigWizardStep3::OnSelchangeWizListStep3()
{
	// TODO: 在此添加控件通知处理程序代码
	switch(m_list.GetCurSel())
	{
	case 0:
		m_btn_viewdetial.EnableWindow(FALSE);
		m_btn_deleteitem.EnableWindow(FALSE);
		break;
	default:
		m_btn_viewdetial.EnableWindow(TRUE);
		m_btn_deleteitem.EnableWindow(TRUE);
		break;
	}
}


void CSysConfigWizardStep3::OnBnClickedButtonViewdetail()
{
	// TODO: 在此添加控件通知处理程序代码
	CSysConfigWizardStep3ViewDetail d_view_detail;
	CSysConfigWizard* p_wiz = (CSysConfigWizard*)GetParent();
	CString str_temp = "";
	m_list.GetText(m_list.GetCurSel(),str_temp);
	d_view_detail.m_file_name = str_temp;
	d_view_detail.m_file_dir = p_wiz->m_option_dir;
	d_view_detail.DoModal();
}


void CSysConfigWizardStep3::OnBnClickedButtonDeleteitem()
{
	// TODO: 在此添加控件通知处理程序代码

	if (IDOK == MessageBox("确定删除此配置选项？","确定删除",MB_ICONWARNING|MB_OKCANCEL) && m_list.GetCurSel()!=0)
	{
		
		CString current_name = "";//保存要删除选项的名字
		m_list.GetText(m_list.GetCurSel(),current_name);
		m_list.DeleteString(m_list.GetCurSel());
		m_list.SetCurSel(0);
		m_btn_viewdetial.EnableWindow(FALSE);
		m_btn_deleteitem.EnableWindow(FALSE);
	}
}


LRESULT CSysConfigWizardStep3::OnWizardNext()
{
	// TODO: 在此添加专用代码和/或调用基类
	CSysConfigWizard* p_wiz = (CSysConfigWizard*)GetParent();
	CString option_name = "";

	if (m_list.GetCurSel()==0)
	{
		p_wiz->m_option_name = "";
	}else{
		m_list.GetText(m_list.GetCurSel(),option_name);
		p_wiz->m_option_name = option_name;
	}
	
	return CPropertyPage::OnWizardNext();
}
