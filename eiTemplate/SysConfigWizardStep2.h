#pragma once


// CSysConfigWizardStep2 对话框

class CSysConfigWizardStep2 : public CPropertyPage
{
	DECLARE_DYNAMIC(CSysConfigWizardStep2)

public:
	CSysConfigWizardStep2();
	virtual ~CSysConfigWizardStep2();

// 对话框数据
	enum { IDD = IDD_SYSCONFIGWIZARD_STEP_2 };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CBrush m_whiterush;
	CFont m_font_title;
	CFont m_font_content;
	CStatic m_text_title;
	CStatic m_text_content;
	CStatic m_pic_instr;
	CListBox m_list;
	HBITMAP m_pic_instr1;
	HBITMAP m_pic_instr2;
	HBITMAP m_pic_instr3;
	HBITMAP m_pic_instr4;
	HBITMAP m_pic_instr5;
	HBITMAP m_pic_instr6;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnSetActive();
	afx_msg void OnSelchangeWizListStep2();
};
