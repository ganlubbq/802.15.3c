#pragma once

//����ҳ��Ӱ�ť
class CMFCPropertyGridPropertyButton : public CMFCPropertyGridProperty
{
public:  
	CMFCPropertyGridPropertyButton(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr = NULL, DWORD_PTR dwData = 0,
		LPCTSTR lpszEditMask = NULL, LPCTSTR lpszEditTemplate = NULL, LPCTSTR lpszValidChars = NULL):  
	CMFCPropertyGridProperty(strName,varValue,lpszDescr)  
	{}  

	virtual ~CMFCPropertyGridPropertyButton()  
	{}  

	virtual BOOL HasButton() const;  

	virtual void OnClickButton(CPoint point);  
protected:  
private:  
};


// CTabProtocolConfig �Ի���

class CTabProtocolConfig : public CDialog
{
	DECLARE_DYNAMIC(CTabProtocolConfig)

public:
	CTabProtocolConfig(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTabProtocolConfig();

// �Ի�������
	enum { IDD = IDD_TAB_PROTOCOL_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnPropertyChanged(__in WPARAM wparam,__in LPARAM lparam);

	BOOL m_finished_ini;
	CComboBox m_mode;
	BlueToothParams* p_bluetoothparams;
	Protocol_param_3C* p_3c_params;//3c����������
	Protocol_param_channel* p_channel_params;//�ŵ�������

	CMFCPropertyGridCtrl m_main_property;
	//����ԭ���Ľ�������
	//CMFCPropertyGridProperty *p_group_signal_config;	//signal configuration
	//CMFCPropertyGridProperty *p_group_payload_config;	//payload setup
	//CMFCPropertyGridProperty *p_group_generation_config;//signal generation setup
	//CMFCPropertyGridProperty *p_group_channel_config;	//channel configuration
	//
	//CMFCPropertyGridProperty *p_trans_type;
	//CMFCPropertyGridProperty *p_pack_type;
	//CMFCPropertyGridProperty *p_lap_addr;
	//CMFCPropertyGridProperty *p_date_rate;
	//CMFCPropertyGridProperty *p_date_max_len;
	//CMFCPropertyGridProperty *p_data_source;
	//CMFCPropertyGridProperty *p_over_samping;
	//CMFCPropertyGridProperty *p_efc_state;
	//CMFCPropertyGridProperty *p_crc_state;
	//CMFCPropertyGridProperty *p_hec_state;
	//CMFCPropertyGridProperty *p_btb;
	//CMFCPropertyGridProperty *p_fc;
	//CMFCPropertyGridProperty *p_noise_power;

	CMFCPropertyGridProperty *pGroup_carrier;//�ز�����
	CMFCPropertyGridProperty *pCarrier_sig_mode;//�ź�ģʽ
	CMFCPropertyGridProperty *pCarrier_data_length; //���ݳ���

	CMFCPropertyGridProperty *pModulation_mcs;//�ź�MCS

	CMFCPropertyGridProperty *pGroup_control;//������Ϣ
	//CMFCPropertyGridPropertyButton *pControl_mac_config;//MAC����

	CMFCPropertyGridProperty *pGroup_modulation;//���Ʊ���
	CMFCPropertyGridProperty *pModulation_mode;//���Ʒ�ʽ
	CMFCPropertyGridProperty *pModulation_fec;//ǰ�����

	CMFCPropertyGridProperty *pGroup_payload;//�غ�����
	CMFCPropertyGridProperty *pPayload_data_source;//����Դ����
	CMFCPropertyGridProperty *pPayload_length;//payload��������
	CMFCPropertyGridProperty* pPayload_trans_rate;//��������ģʽHRP��LRP
	CMFCPropertyGridProperty* pPayload_ssid;	//SSID
	CMFCPropertyGridProperty *pPayload_spreader;//��Ƶ����
	CMFCPropertyGridProperty *pPayload_map_type;//ӳ������
	CMFCPropertyGridProperty *pPayload_uep_eep;//���������
	CMFCPropertyGridProperty *pPayload_interver;//��֯���
	CMFCPropertyGridProperty *pPayload_pces;//�ŵ����Ʋ���
	CMFCPropertyGridProperty *pPayload_tone_inter;//�ز���֯

	CMFCPropertyGridProperty *pGroup_spectrum;//Ƶ�׿���

	CMFCPropertyGridProperty *pGroup_channel;//�ŵ�
	CMFCPropertyGridProperty *pChannel_switch;//�ŵ�����
	CMFCPropertyGridProperty* pChannel_type;//�ŵ�����
	CMFCPropertyGridProperty* pChannel_sys_bw;//ϵͳ����

};
