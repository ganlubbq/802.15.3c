#pragma once
#include "MacConfig_SC.h"


// CMacDiag �Ի���

class CMacDiag : public CDialog
{
	DECLARE_DYNAMIC(CMacDiag)

public:
	CMacDiag(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMacDiag();

// �Ի�������
	enum { IDD = IDD_DIAG_MAC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeComboMacdiag();
	CComboBox m_ComMacdiag;//�����˵�ѡ��ؼ�
	CStatic m_pic_macdiag;
	HBITMAP m_pic_macdiag1;
	HBITMAP m_pic_macdiag2;
	HBITMAP m_pic_macdiag3;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButton_MacConfig();
};
