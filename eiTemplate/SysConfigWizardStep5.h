#pragma once


// CSysConfigWizardStep5 对话框

class CSysConfigWizardStep5 : public CPropertyPage
{
	DECLARE_DYNAMIC(CSysConfigWizardStep5)

public:
	CSysConfigWizardStep5();
	virtual ~CSysConfigWizardStep5();

// 对话框数据
	enum { IDD = IDD_SYSCONFIGWIZARD_STEP_5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CBrush m_whiterush;
	CFont m_font_title;
	CFont m_font_content;
	CStatic m_text_title;
	CStatic m_text_content;
	CStatic m_connection_info;
	BOOL b_send_conn;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardBack();
};
