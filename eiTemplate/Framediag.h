#pragma once


// CFramediag �Ի���

class CFramediag : public CDialog
{
	DECLARE_DYNAMIC(CFramediag)

public:
	CFramediag(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFramediag();

// �Ի�������
	enum { IDD = IDD_DIAG_FRAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	CComboBox m_ComFramediag;//�����˵�ѡ��ؼ�
	virtual BOOL OnInitDialog();
	CStatic m_pic_framediag;
	HBITMAP m_pic_framediag1;
	HBITMAP m_pic_framediag2;
	HBITMAP m_pic_framediag3;
	afx_msg void OnCbnSelchangeComboFramediag();//�����˵��ؼ�����ʵ��
};
