#pragma once


// CMacConfig_HSI �Ի���

class CMacConfig_HSI : public CDialog
{
	DECLARE_DYNAMIC(CMacConfig_HSI)

public:
	CMacConfig_HSI(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMacConfig_HSI();
	CMFCPropertyGridCtrl     m_MFCPropertyGrid_MacConfigHSI;//Э����������б�
	CMFCPropertyGridProperty *pGroup11;//��������
// �Ի�������
	enum { IDD = IDD_MAC_CONFIG_HSI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	BOOL m_finished_ini;
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
