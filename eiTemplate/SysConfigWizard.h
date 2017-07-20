#pragma once

#include "SysConfigWizardStep1.h"
#include "SysConfigWizardStep2.h"
#include "SysConfigWizardStep3.h"
#include "SysConfigWizardStep4.h"
#include "SysConfigWizardStep5.h"
#include "SysConfigWizardStep6.h"
// CSysConfigWizard

class CSysConfigWizard : public CPropertySheet
{
	DECLARE_DYNAMIC(CSysConfigWizard)

public:
	CSysConfigWizard(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CSysConfigWizard(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CSysConfigWizard();
private:
	CFont m_font;//为统一页面字体设置风格，在这里设置wizard的按钮字体
	/************************************************************************/
	/* 6个配置步骤的指针声明                                                */
	/************************************************************************/
	CSysConfigWizardStep1 *m_step1;
	CSysConfigWizardStep2 *m_step2;
	CSysConfigWizardStep3 *m_step3;
	CSysConfigWizardStep4 *m_step4;
	CSysConfigWizardStep5 *m_step5;
	CSysConfigWizardStep6 *m_step6;
protected:
	DECLARE_MESSAGE_MAP()
public:
	/************************************************************************/
	/* 仪器连接相关的变量，这些变量也是本向导要配置的主要内容               */
	/************************************************************************/
	ViSession defaultRM;
	ViSession vi[8];
	ViStatus vi_error_info[8];
	CString str_conn[8];//连接仪器的程控命令
	BOOL b_instr_connected;
	int m_function_choice;//当前选择的配置项
	int m_num_instruments;//当前配置的仪器数量

	CString m_option_dir;//当前配置选项所在的文件夹
	CString m_option_name;//当前配置选项的文件名
	CString m_config_list_dir;//当前配置包含的选项的文件路径，该文件用于确定第三步中显示用户已保存的配置选项

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};


