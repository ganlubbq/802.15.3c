#pragma once

//属性页添加按钮
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


// CTabProtocolConfig 对话框

class CTabProtocolConfig : public CDialog
{
	DECLARE_DYNAMIC(CTabProtocolConfig)

public:
	CTabProtocolConfig(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTabProtocolConfig();

// 对话框数据
	enum { IDD = IDD_TAB_PROTOCOL_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnPropertyChanged(__in WPARAM wparam,__in LPARAM lparam);

	BOOL m_finished_ini;
	CComboBox m_mode;
	BlueToothParams* p_bluetoothparams;
	Protocol_param_3C* p_3c_params;//3c参数配置类
	Protocol_param_channel* p_channel_params;//信道配置类

	CMFCPropertyGridCtrl m_main_property;
	//蓝牙原来的界面声明
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

	CMFCPropertyGridProperty *pGroup_carrier;//载波配置
	CMFCPropertyGridProperty *pCarrier_sig_mode;//信号模式
	CMFCPropertyGridProperty *pCarrier_data_length; //数据长度

	CMFCPropertyGridProperty *pModulation_mcs;//信号MCS

	CMFCPropertyGridProperty *pGroup_control;//控制信息
	//CMFCPropertyGridPropertyButton *pControl_mac_config;//MAC设置

	CMFCPropertyGridProperty *pGroup_modulation;//调制编码
	CMFCPropertyGridProperty *pModulation_mode;//调制方式
	CMFCPropertyGridProperty *pModulation_fec;//前向编码

	CMFCPropertyGridProperty *pGroup_payload;//载荷配置
	CMFCPropertyGridProperty *pPayload_data_source;//数据源类型
	CMFCPropertyGridProperty *pPayload_length;//payload长度设置
	CMFCPropertyGridProperty* pPayload_trans_rate;//传输速率模式HRP、LRP
	CMFCPropertyGridProperty* pPayload_ssid;	//SSID
	CMFCPropertyGridProperty *pPayload_spreader;//扩频因子
	CMFCPropertyGridProperty *pPayload_map_type;//映射类型
	CMFCPropertyGridProperty *pPayload_uep_eep;//差错保护类型
	CMFCPropertyGridProperty *pPayload_interver;//交织深度
	CMFCPropertyGridProperty *pPayload_pces;//信道估计插入
	CMFCPropertyGridProperty *pPayload_tone_inter;//载波交织

	CMFCPropertyGridProperty *pGroup_spectrum;//频谱控制

	CMFCPropertyGridProperty *pGroup_channel;//信道
	CMFCPropertyGridProperty *pChannel_switch;//信道开关
	CMFCPropertyGridProperty* pChannel_type;//信道类型
	CMFCPropertyGridProperty* pChannel_sys_bw;//系统带宽

};
