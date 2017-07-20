#pragma once


// CTabCarrier �Ի���

class CTabCarrier : public CDialog
{
	DECLARE_DYNAMIC(CTabCarrier)

public:
	CTabCarrier(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTabCarrier();

// �Ի�������
	enum { IDD = IDD_TAB_CARRIER_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	BOOL m_finished_ini;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnPropertyChanged(__in WPARAM wparam,__in LPARAM lparam);//���������������Լ�����ҳ�������
	Protocol_param_3C* p_3c_params;//3c����������

	CMFCPropertyGridCtrl m_MFCPropertyGridTwo;//a/b/gЭ������б�
	CMFCPropertyGridProperty *pGroup11;//��������
	CMFCPropertyGridProperty *pGroup12;//���ο���
	CMFCPropertyGridProperty *pGroup13;//OFDM����

	CMFCPropertyGridProperty *pPropS1;//�ź�ģʽ����SC��HSI��AV

	CMFCPropertyGridProperty* p_IQ_gain_balance;	//IQƽ������
	CMFCPropertyGridProperty* p_quadrature_angle_adjustment;	//�����Ƕȵ���
};
