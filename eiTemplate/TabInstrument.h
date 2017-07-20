#pragma once

class InstrumentParams
{
public:
	CString frequency;
	CString amplitude;
	CString RF_output;
	CString IQ_ADJ;
	CString I_offset;
	CString Q_offset;
	CString IQ_gain_balance;
	CString quadrature_angle_adjustment;
	CString ALC;
	CString ALC_band;
	CString ALC_search_ref;
	CString ALC_search_method;
	CString ARB_clock_type;
	CString ARB_clock_freq;
	CString TRIG_mode;
	CString TRIG_mode_cont;
	CString TRIG_mode_gate;
	CString TRIG_source;
	CString TRIG_EXT_slope;
	CString TRIG_EXT_delay_switch;
	CString TRIG_EXT_delay;
	CString AWGN_state;
	CString Noise_band;
	InstrumentParams()
	{
		frequency = "";
		amplitude = "";
		RF_output = "";
		IQ_ADJ = "";
		I_offset = "";
		Q_offset = "";
		IQ_gain_balance = "";
		quadrature_angle_adjustment = "";
		ALC = "";
		ALC_band = "";
		ALC_search_ref = "";
		ALC_search_method = "";
		ARB_clock_type = "";
		ARB_clock_freq = "";
		TRIG_mode = "";
		TRIG_mode_cont = "";
		TRIG_mode_gate = "";
		TRIG_source = "";
		TRIG_EXT_slope = "";
		TRIG_EXT_delay_switch = "";
		TRIG_EXT_delay = "";
		AWGN_state = "";
		Noise_band = "";
	}
};

// CTabInstrument 对话框

class CTabInstrument : public CDialogEx
{
	DECLARE_DYNAMIC(CTabInstrument)
public:
	CTabInstrument(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTabInstrument();

	InstrumentParams instr_params[8];//储存各个仪器配置参数的数组，最多支持到8
	BOOL send_command_enabled;

	CMFCPropertyGridCtrl     m_MFCPropertyGrid_INSTRUMENT;//协议的配置项列表
	/***仪器信息，对应安捷伦 Configuration 项***/
	CMFCPropertyGridProperty* p_group_Configuration;
	CMFCPropertyGridProperty* p_instrument_name;

	/***基本配置，对应安捷伦 Basic 项***/
	CMFCPropertyGridProperty* p_group_Basic;
	CMFCPropertyGridProperty* p_frequency;
	CMFCPropertyGridProperty* p_amplitude;
	CMFCPropertyGridProperty* p_RF_output;

	/***IQ，对应安捷伦 IQ 项***/
	CMFCPropertyGridProperty* p_group_IQ;
	CMFCPropertyGridProperty* p_IQ_adjustments;
	CMFCPropertyGridProperty* p_I_offset;
	CMFCPropertyGridProperty* p_Q_offset;
	CMFCPropertyGridProperty* p_IQ_gain_balance;
	CMFCPropertyGridProperty* p_quadrature_angle_adjustment;

	/***ALC，对应安捷伦 ALC 项***/
	CMFCPropertyGridProperty* p_group_ALC;
	CMFCPropertyGridProperty* p_ALC;
	CMFCPropertyGridProperty* p_ALC_bandwidth;
	CMFCPropertyGridProperty* p_power_search_ref;
	CMFCPropertyGridProperty* p_RF_during_power_search;
	CMFCPropertyGridProperty* p_power_search_method;

	/***任意波组，对应安捷伦 Dual ARB 项***/
	CMFCPropertyGridProperty* p_group_ARB;
	CMFCPropertyGridProperty* p_ARB_clock_type;
	CMFCPropertyGridProperty* p_ARB_samp_clock;
	CMFCPropertyGridProperty* p_ARB_clock_freq;

	/***触发，对应安捷伦 Dual ARB Trigger 项***/
	CMFCPropertyGridProperty* p_group_Trigger;
	CMFCPropertyGridProperty* p_trigger_mod;
	CMFCPropertyGridProperty* p_trigger_source;
	CMFCPropertyGridProperty* p_trigger_slope;
	CMFCPropertyGridProperty* p_trigger_delay_active;
	CMFCPropertyGridProperty* p_trigger_delay;
	CMFCPropertyGridProperty* p_trigger_cont_type;
	CMFCPropertyGridProperty* p_trigger_sing_type;
	CMFCPropertyGridProperty* p_trigger_sadv_type;
	CMFCPropertyGridProperty* p_trigger_gate_type;

	/***标记***/
	CMFCPropertyGridProperty* p_group_Marker;
	CMFCPropertyGridProperty* p_marker_state;
	CMFCPropertyGridProperty* p_marker_xiaoyin;
	CMFCPropertyGridProperty* p_marker_ALC_hold;
	CMFCPropertyGridProperty* p_marker_no_1;
	CMFCPropertyGridProperty* p_marker_no_2;
	CMFCPropertyGridProperty* p_marker_no_3;
	CMFCPropertyGridProperty* p_marker_no_4;
	CMFCPropertyGridProperty* p_marker_polar_no_1;
	CMFCPropertyGridProperty* p_marker_polar_no_2;
	CMFCPropertyGridProperty* p_marker_polar_no_3;
	CMFCPropertyGridProperty* p_marker_polar_no_4;

	/***实时噪声，对应安捷伦 Real Time Noise Setup 项***/
	CMFCPropertyGridProperty* p_group_RT_Noise;
	CMFCPropertyGridProperty* p_rt_noise_state;
	CMFCPropertyGridProperty* p_carrier_to_noise_ratio;
	CMFCPropertyGridProperty* p_carrier_bandwidth;
	CMFCPropertyGridProperty* p_noise_bandwidth;
	// 对话框数据
	enum { IDD = IDD_TAB_INSTRUMENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	BOOL m_finished_ini;
	char ch[256];
public:
	ViSession vi;
	CComboBox m_combo_instrument_index;

	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClickedBtnUpdateToInstrument();
	afx_msg void OnClickedBtnUpdateFromInstrument();
	afx_msg void OnClickedBtnPowerSearch();
	afx_msg void OnClickedBtnDcCal();
	afx_msg void OnClickedBtnReset();
	afx_msg LRESULT OnPropertyChanged(__in WPARAM wparam,__in LPARAM lparam);
	afx_msg void OnSelchangeComboInstrumentIndex();
};