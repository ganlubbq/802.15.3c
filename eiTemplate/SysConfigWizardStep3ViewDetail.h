#pragma once


// CSysConfigWizardStep3ViewDetail 对话框

class CSysConfigWizardStep3ViewDetail : public CDialog
{
	DECLARE_DYNAMIC(CSysConfigWizardStep3ViewDetail)

public:
	CSysConfigWizardStep3ViewDetail(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSysConfigWizardStep3ViewDetail();

// 对话框数据
	enum { IDD = IDD_SYSCONFIGWIZARD_STEP_3_VIEW_DETAIL };
private:
	CFont m_font_content;
	CMFCPropertyGridCtrl m_content_instr_config;//显示配置情况的控件
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_file_dir;
	CString m_file_name;
	virtual BOOL OnInitDialog();
};
