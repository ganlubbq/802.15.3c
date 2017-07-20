#pragma once


// CSysConfigWizardStep6 对话框

class CSysConfigWizardStep6 : public CPropertyPage
{
	DECLARE_DYNAMIC(CSysConfigWizardStep6)

public:
	CSysConfigWizardStep6();
	virtual ~CSysConfigWizardStep6();

// 对话框数据
	enum { IDD = IDD_SYSCONFIGWIZARD_STEP_6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CBrush m_whiterush;
	CFont m_font_title;
	CFont m_font_content;
	CStatic m_text_title;
	CStatic m_text_content;
	CEdit m_edit_name;
	CEdit m_edit_summary;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnSetActive();
};
