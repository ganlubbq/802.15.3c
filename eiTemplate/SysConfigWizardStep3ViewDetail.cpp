// SysConfigWizardStep3ViewDetail.cpp : 实现文件
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "SysConfigWizardStep3ViewDetail.h"
#include "afxdialogex.h"
#include "SysConfigWizard.h"
#include "SysConfigWizardStep3.h"

using namespace std;

// CSysConfigWizardStep3ViewDetail 对话框

IMPLEMENT_DYNAMIC(CSysConfigWizardStep3ViewDetail, CDialog)

CSysConfigWizardStep3ViewDetail::CSysConfigWizardStep3ViewDetail(CWnd* pParent /*=NULL*/)
	: CDialog(CSysConfigWizardStep3ViewDetail::IDD, pParent)
{
	m_font_content.CreatePointFont(90,"微软雅黑");
	m_file_dir = "";
	m_file_name = "";
}

CSysConfigWizardStep3ViewDetail::~CSysConfigWizardStep3ViewDetail()
{
}

void CSysConfigWizardStep3ViewDetail::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSysConfigWizardStep3ViewDetail, CDialog)
END_MESSAGE_MAP()


// CSysConfigWizardStep3ViewDetail 消息处理程序


BOOL CSysConfigWizardStep3ViewDetail::OnInitDialog()
{
	using namespace rapidxml;
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	/************************************************************************/
	/* 设置确定按钮的字体                                                   */
	/************************************************************************/
	CButton* p_btn_ok = ((CButton*)GetDlgItem(IDOK));
	p_btn_ok->SetFont(&m_font_content);
	
	CRect rc;
	GetClientRect(&rc);
	rc.bottom -= 35;
	rc.left += 1;
	rc.right -= 1;
	rc.top += 1;
	m_content_instr_config.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,rc,this,PROPERTYGRID_INSTRUMENT_CONFIG);
	m_content_instr_config.EnableHeaderCtrl(FALSE,"参数","值");
	//m_content_instr_config.EnableDescriptionArea();
	//m_content_instr_config.SetDescriptionRows(5);
	m_content_instr_config.SetVSDotNetLook();
	m_content_instr_config.MarkModifiedProperties();
	m_content_instr_config.SetAlphabeticMode(false); 
	m_content_instr_config.SetShowDragContext();
	m_content_instr_config.SetFont(&m_font_content);

	CMFCPropertyGridProperty *p_group_info = new CMFCPropertyGridProperty("配置信息");

	/************************************************************************/
	/* 确定当前选择的配置文件所在的文件夹和路径                             */
	/************************************************************************/
	m_file_dir.Append(m_file_name);
	m_file_dir.Append(".xml");
	//m_option_dir
	/************************************************************************/
	/* 解析xml文档，按照文档的内容刷新显示页面的内容                        */
	/************************************************************************/
	CMFCPropertyGridProperty* p_instr_group_array[8];
	CMFCPropertyGridProperty* p_prop_name;//名称
	CMFCPropertyGridProperty* p_prop_desc;//描述
	CMFCPropertyGridProperty* p_prop_array_instr[5];//仪器组对应的5个小条目

	file<> fdoc(m_file_dir.GetBuffer());
	//cout<<fdoc.data()<<endl;
	xml_document<> doc;
	doc.parse<0>(fdoc.data());

	// 获取根节点
	xml_node<>* p_root = doc.first_node();
	// 根节点第一个节点是InstrumentsInfo,其中包含了配置文件的名称和配置的描述
	xml_node<>* p_instrinfo_node = p_root->first_node();
	// 配置名称
	xml_node<>* p_config_name = p_instrinfo_node->first_node();
	p_prop_name = new CMFCPropertyGridProperty("名称",p_config_name->value());
	p_prop_name->Enable(FALSE);
	p_group_info->AddSubItem(p_prop_name);
	// 配置描述
	xml_node<>* p_config_desc = p_instrinfo_node->last_node();
	p_prop_desc = new CMFCPropertyGridProperty("描述",p_config_desc->value());
	p_prop_desc->Enable(FALSE);
	p_group_info->AddSubItem(p_prop_desc);

	m_content_instr_config.AddProperty(p_group_info);

	// 因为仪器的数量可变，所以要通过下面的方法自动确定连接仪器的数量
	CString content;
	int i=0;
	for (xml_node<> *node = p_instrinfo_node->next_sibling();node;node = node->next_sibling(),i++)
	{
		// 每执行一个循环，就要设置一个仪器的分组
		content.Format("仪器 NO.%d 配置详情：",i+1);
		p_instr_group_array[i] = new CMFCPropertyGridProperty(content);
		// 解析仪器类型并动态创建表单项
		xml_node<>* p_instr_type = node->first_node();
		p_prop_array_instr[0] = new CMFCPropertyGridProperty("仪器类型",p_instr_type->value());
		p_prop_array_instr[0]->Enable(FALSE);
		p_instr_group_array[i]->AddSubItem(p_prop_array_instr[0]);
		// 解析仪器连接状态并动态创建表单项
		xml_node<>* p_connection = p_instr_type->next_sibling();
		p_prop_array_instr[1] = new CMFCPropertyGridProperty("连接信息",p_connection->value());
		p_prop_array_instr[1]->Enable(FALSE);
		p_instr_group_array[i]->AddSubItem(p_prop_array_instr[1]);
		// 解析仪器Model Number并动态创建表单项
		xml_node<>* p_model_number = p_connection->next_sibling();
		p_prop_array_instr[2] = new CMFCPropertyGridProperty("Model Number",p_model_number->value());
		p_prop_array_instr[2]->Enable(FALSE);
		p_instr_group_array[i]->AddSubItem(p_prop_array_instr[2]);
		// 解析仪器Serial Number并动态创建表单项
		xml_node<>* p_serial_number = p_model_number->next_sibling();
		p_prop_array_instr[3] = new CMFCPropertyGridProperty("Serial Number",p_serial_number->value());
		p_prop_array_instr[3]->Enable(FALSE);
		p_instr_group_array[i]->AddSubItem(p_prop_array_instr[3]);
		// 解析仪器Firmware Revision并动态创建表单项
		xml_node<>* p_firmware_revision = p_serial_number->next_sibling();
		p_prop_array_instr[4] = new CMFCPropertyGridProperty("Firmware Revision",p_firmware_revision->value());
		p_prop_array_instr[4]->Enable(FALSE);
		p_instr_group_array[i]->AddSubItem(p_prop_array_instr[4]);

		m_content_instr_config.AddProperty(p_instr_group_array[i]);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
