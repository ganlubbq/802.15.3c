// TabProtocolConfig.cpp : 实现文件
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "TabProtocolConfig.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "MacDiag.h"

// CTabProtocolConfig 对话框

IMPLEMENT_DYNAMIC(CTabProtocolConfig, CDialog)

BOOL CMFCPropertyGridPropertyButton::HasButton() const
{
	return TRUE;
}

void CMFCPropertyGridPropertyButton::OnClickButton(CPoint point)
{
	CMacDiag Tab_MacDiag;
	Tab_MacDiag.DoModal();
}

CTabProtocolConfig::CTabProtocolConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CTabProtocolConfig::IDD, pParent)
{
	m_finished_ini = FALSE;
	p_bluetoothparams = 0;//构造函数中先将指针赋为0，在OnInitDialog中再具体赋值
	p_3c_params = 0;
	p_channel_params = 0;
}

CTabProtocolConfig::~CTabProtocolConfig()
{
}

void CTabProtocolConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_MODE, m_mode);
}


BEGIN_MESSAGE_MAP(CTabProtocolConfig, CDialog)
	ON_WM_SIZE()
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED,OnPropertyChanged)
END_MESSAGE_MAP()


// CTabProtocolConfig 消息处理程序


void CTabProtocolConfig::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnOK();
}


BOOL CTabProtocolConfig::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_mode.SetCurSel(0);
	//有关协议配置的指针传递到配置协议类
	p_bluetoothparams = ((CMainFrame*)AfxGetMainWnd())->m_pass_to_thread.p_protocol_params;
	p_3c_params = ((CMainFrame*)AfxGetMainWnd())->m_pass_to_thread.p_protocol_params_3c;//给3C参数指针赋值
	p_channel_params = ((CMainFrame*)AfxGetMainWnd())->m_pass_to_thread.p_protocol_params_channel;//给信道参数指针赋值

	CRect rc;//使用客户区大小对属性表单控件进行定位
	GetClientRect(&rc);
	//rc.bottom += 20;
	rc.left += 10;
	//rc.right += 10;
	rc.top += 45;
	m_main_property.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,rc,this,PROPERTYGRID_PROTOCOL_CONFIG);
	m_main_property.EnableHeaderCtrl(FALSE,"参数","值");
	m_main_property.EnableDescriptionArea();
	m_main_property.SetDescriptionRows(5);
	m_main_property.SetVSDotNetLook();
	m_main_property.MarkModifiedProperties(TRUE);
	m_main_property.SetAlphabeticMode(false); 
	m_main_property.SetShowDragContext();

	/************************************************************************/
	/* 注:要设置下拉选择的选项不能编辑，以减少后期判断选择正确与否的工作    */
	/************************************************************************/
	//15.3c添加的界面
	//pGroup_carrier
	pGroup_carrier = new CMFCPropertyGridProperty("载波配置");
	pCarrier_sig_mode = new CMFCPropertyGridProperty("信号模式", "SC", "选择所生成信号的模式:SC-PHY/HSI-PHY/AV-PHY", PROTO_SIG_MODE_3C);
	pCarrier_sig_mode->AddOption(_T("SC"));  
	pCarrier_sig_mode->AddOption(_T("HSI")); 
	pCarrier_sig_mode->AddOption(_T("AV"));
	pCarrier_sig_mode->AllowEdit(FALSE);
	pGroup_carrier->AddSubItem(pCarrier_sig_mode);
	CMFCPropertyGridProperty* pCarrier_frames = new CMFCPropertyGridProperty(_T("信号帧数"),_T("1"),_T("输入所需生成信号的帧数"));
	pGroup_carrier->AddSubItem(pCarrier_frames);
	pGroup_carrier->AllowEdit(FALSE);
// 	pCarrier_data_length = new CMFCPropertyGridProperty(_T("数据长度"),_T("123456"),_T("输入所需生成信号数据长度"), PROTO_SIG_GENLENGTH_3C);
// 	pGroup_carrier->AddSubItem(pCarrier_data_length);
	CMFCPropertyGridProperty* pCarrier_freq_offset = new CMFCPropertyGridProperty(_T("频率偏移"),_T("10000.0000Hz"),_T("显示当前频率偏移值"));
	pCarrier_freq_offset->AllowEdit(FALSE);
	pGroup_carrier->AddSubItem(pCarrier_freq_offset);
	CMFCPropertyGridProperty* pCarrier_relative_power = new CMFCPropertyGridProperty(_T("相对功率"),_T("00.000dB"),_T("显示当前模式的相对功率"));
	pCarrier_relative_power->AllowEdit(FALSE);
	pGroup_carrier->AddSubItem(pCarrier_relative_power);
	CMFCPropertyGridProperty* pCarrier_trans_space = new CMFCPropertyGridProperty(_T("连续传输间隔"),_T("0.5μs"),_T("设置连续传输间隔"));
	pCarrier_trans_space->AddOption(_T("0.2μs"));
	pCarrier_trans_space->AddOption(_T("0.5μs"));
	pCarrier_trans_space->AddOption(_T("2.0μs"));
	pCarrier_trans_space->AllowEdit(FALSE);
	pGroup_carrier->AddSubItem(pCarrier_trans_space);
	CMFCPropertyGridProperty* pCarrier_trans_time = new CMFCPropertyGridProperty(_T("收/发转换时间"),_T("2.5μs"),_T("设置收/发转换时间"));
	pCarrier_trans_time->AddOption(_T("0.2μs"));
	pCarrier_trans_time->AddOption(_T("2.0μs"));
	pCarrier_trans_time->AddOption(_T("2.5μs"));
	pCarrier_trans_time->AllowEdit(FALSE);
	pGroup_carrier->AddSubItem(pCarrier_trans_time);
	CMFCPropertyGridProperty* pCarrier_switch_time = new CMFCPropertyGridProperty(_T("信道切换时间"),_T("100μs"),_T("显示当前模式的相对功率"));
	pCarrier_switch_time->AllowEdit(FALSE);
	pGroup_carrier->AddSubItem(pCarrier_switch_time);

	//pGroup_control
	pGroup_control = new CMFCPropertyGridProperty("控制信息");
	CMFCPropertyGridProperty* pControl_preamble = new CMFCPropertyGridProperty(_T("前导类型"),_T("short"),_T("选择生成信号的前导类型：short/long"));
	pControl_preamble->AddOption(_T("short"));
	pControl_preamble->AddOption(_T("long"));
	pControl_preamble->AllowEdit(FALSE);
	pGroup_control->AddSubItem(pControl_preamble);
	CMFCPropertyGridProperty* pControl_aggregation = new CMFCPropertyGridProperty(_T("Aggregation"),_T("ON"),_T("选择生成信号的Aggregation：ON/OFF"));
	pControl_aggregation->AddOption(_T("ON"));
	pControl_aggregation->AddOption(_T("OFF"));
	pControl_aggregation->AllowEdit(FALSE);
	pGroup_control->AddSubItem(pControl_aggregation);
	CMFCPropertyGridPropertyButton *pControl_mac_config = new CMFCPropertyGridPropertyButton("MAC详细配置","","详细配置MAC信息");
	pGroup_control->AddSubItem(pControl_mac_config);

	//pGroup_modulation
	pGroup_modulation = new CMFCPropertyGridProperty("调制编码");
	pModulation_mcs = new CMFCPropertyGridProperty(_T("MCS"),_T("0"),_T("选择生成信号的MCS"), PROTO_SIG_MCS_3C);
	pModulation_mcs->AddOption(_T("0"));
	pModulation_mcs->AddOption(_T("1"));
	pModulation_mcs->AddOption(_T("2"));
	pModulation_mcs->AddOption(_T("3"));
	pModulation_mcs->AddOption(_T("4"));
	pModulation_mcs->AddOption(_T("5"));
	pModulation_mcs->AddOption(_T("6"));
	pModulation_mcs->AddOption(_T("7"));
	pModulation_mcs->AddOption(_T("8"));
	pModulation_mcs->AddOption(_T("9"));
	pModulation_mcs->AddOption(_T("10"));
	pModulation_mcs->AddOption(_T("11"));
	pModulation_mcs->AddOption(_T("12"));
	pModulation_mcs->AddOption(_T("13"));
	pModulation_mcs->AllowEdit(FALSE);
	pGroup_modulation->AddSubItem(pModulation_mcs);
	pModulation_mode = new CMFCPropertyGridProperty(_T("调制方式"),_T("π/2 BPSK"),_T("显示当前模式下的调制方式"));
	pModulation_mode->AddOption(_T("π/2 BPSK"));
	pModulation_mode->AddOption(_T("π/2 QPSK"));
	pModulation_mode->AddOption(_T("π/2 8-PSK"));
	pModulation_mode->AddOption(_T("π/2 16-QAM"));
	pModulation_mode->AllowEdit(FALSE);
	pGroup_modulation->AddSubItem(pModulation_mode);
	pModulation_fec = new CMFCPropertyGridProperty(_T("前向编码"),_T("RS(255,239)"),_T("显示当前模式下的前向编码方式"));
	pModulation_fec->AddOption(_T("RS(255,239)"));
	pModulation_fec->AddOption(_T("LDPC(672,336)"));
	pModulation_fec->AddOption(_T("LDPC(672,504)"));
	pModulation_fec->AddOption(_T("LDPC(672,588)"));
	pModulation_fec->AllowEdit(FALSE);
	pGroup_modulation->AddSubItem(pModulation_fec);

	//pGroup_payload
	pGroup_payload = new CMFCPropertyGridProperty("载荷配置");
	CMFCPropertyGridProperty* pPayload_rate = new CMFCPropertyGridProperty(_T("数据速率"),_T("1234.00Mbps"),_T("显示当前模式的数据速率"));
	pPayload_rate->AllowEdit(FALSE);
	pGroup_payload->AddSubItem(pPayload_rate);
	pPayload_data_source = new CMFCPropertyGridProperty(_T("数据源"),_T("PN9"),_T("选择数据源类型：PN9/PN15/ALL0/从文件读取"), PROTO_SIG_DATA_SOURCE_3C);
	pPayload_data_source->AddOption(_T("PN9"));
	pPayload_data_source->AddOption(_T("PN15"));
	pPayload_data_source->AddOption(_T("ALL0"));
	pPayload_data_source->AddOption(_T("从文件读取"));
	pPayload_data_source->AllowEdit(FALSE);
	pGroup_payload->AddSubItem(pPayload_data_source);
	pPayload_length = new CMFCPropertyGridProperty(_T("负载长度"),_T("30592"),_T("设置负载长度"), PROTO_SIG_PAYLOADLENGTH_3C);
	pGroup_payload->AddSubItem(pPayload_length);
	pPayload_trans_rate = new CMFCPropertyGridProperty(_T("传输速率模式"),_T("HRP"),_T("选择传输速率模式：HRP/LRP"), PROTO_SIG_TRANS_RATE_TYPE);
	pPayload_trans_rate->AddOption(_T("HRP"));
	pPayload_trans_rate->AddOption(_T("LRP"));
	pPayload_trans_rate->AllowEdit(FALSE);
	pPayload_trans_rate->Show(FALSE);
	pGroup_payload->AddSubItem(pPayload_trans_rate);
	pPayload_ssid = new CMFCPropertyGridProperty(_T("SSID"),_T("0000"),_T("设置扰码器初始序列"), PROTO_SIG_SSID_3C);
	pGroup_payload->AddSubItem(pPayload_ssid);
	pPayload_spreader = new CMFCPropertyGridProperty(_T("扩频因子"),_T("64"),_T("选择当前模式的扩频因子"), PROTO_SIG_SPREADER_3C);
	pPayload_spreader->AddOption(_T("1"));
	pPayload_spreader->AddOption(_T("2"));
	pPayload_spreader->AddOption(_T("4"));
	pPayload_spreader->AddOption(_T("64"));
	pPayload_spreader->AllowEdit(FALSE);
	pGroup_payload->AddSubItem(pPayload_spreader);
	CMFCPropertyGridProperty* pPayload_subblock = new CMFCPropertyGridProperty(_T("数据子块模式"),_T("0"),_T("选择当前模式数据子块分割模式"));
	pPayload_subblock->AddOption(_T("0"));
	pPayload_subblock->AddOption(_T("8"));
	pPayload_subblock->AddOption(_T("64"));
	pPayload_subblock->AllowEdit(FALSE);
	pGroup_payload->AddSubItem(pPayload_subblock);
	pPayload_pces = new CMFCPropertyGridProperty(_T("信道估计插入"),_T("ON"),_T("选择是否插入信道估计：ON/OFF"));
	pPayload_pces->AddOption(_T("ON"));
	pPayload_pces->AddOption(_T("OFF"));
	pPayload_pces->AllowEdit(FALSE);
	pGroup_payload->AddSubItem(pPayload_pces);
	pPayload_map_type = new CMFCPropertyGridProperty(_T("映射类型"),_T("0"),_T("选择当前模式映射类型：0-正常模式，1-歪曲模式"));
	pPayload_map_type->AddOption(_T("0"));
	pPayload_map_type->AddOption(_T("1"));
	pPayload_map_type->AllowEdit(FALSE);
	pPayload_map_type->Enable(FALSE);
	pGroup_payload->AddSubItem(pPayload_map_type);
	pPayload_uep_eep = new CMFCPropertyGridProperty(_T("差错保护类型"),_T("EEP"),_T("选择当前模式差错保护类型：EEP/UEP"));
	pPayload_uep_eep->AddOption(_T("EEP"));
	pPayload_uep_eep->AddOption(_T("UEP"));
	pPayload_uep_eep->AllowEdit(FALSE);
	pPayload_uep_eep->Enable(FALSE);
	pGroup_payload->AddSubItem(pPayload_uep_eep);
	pPayload_interver = new CMFCPropertyGridProperty(_T("交织深度"),_T("2"),_T("选择当前模式交织深度：2/4"));
	pPayload_interver->AddOption(_T("2"));
	pPayload_interver->AddOption(_T("4"));
	pPayload_interver->AllowEdit(FALSE);
	pPayload_interver->Enable(FALSE);
	pGroup_payload->AddSubItem(pPayload_interver);
	pPayload_tone_inter = new CMFCPropertyGridProperty(_T("载波交织"),_T("OFF"),_T("选择是否开启载波交织"), PROTO_SIG_TONEINTER_3C);
	pPayload_tone_inter->AddOption(_T("ON"));
	pPayload_tone_inter->AddOption(_T("OFF"));
	pPayload_tone_inter->AllowEdit(FALSE);
	pPayload_tone_inter->Enable(FALSE);
	pGroup_payload->AddSubItem(pPayload_tone_inter);

	//pGroup_spectrum
	pGroup_spectrum = new CMFCPropertyGridProperty("频谱控制");
	CMFCPropertyGridProperty* pSpectrum_filter = new CMFCPropertyGridProperty(_T("是否使用滤波器"),_T("ON"),_T("设置是否使用滤波器：ON/OFF"));
	pSpectrum_filter->AddOption(_T("ON"));
	pSpectrum_filter->AddOption(_T("OFF"));
	pSpectrum_filter->AllowEdit(FALSE);
	pGroup_spectrum->AddSubItem(pSpectrum_filter);
	CMFCPropertyGridProperty* pSpectrum_win_length = new CMFCPropertyGridProperty(_T("窗口长度"),_T("1024"),_T("设置窗函数采样点数，其长度不能超过一个OFDM信号保护间隔的长度"));
	pGroup_spectrum->AddSubItem(pSpectrum_win_length);

	//pGroup_channel
	pGroup_channel = new CMFCPropertyGridProperty("信道");
	pChannel_switch = new CMFCPropertyGridProperty(_T("信道选择"),_T("OFF"),_T("选择信道：ON/OFF"),PROTO_CHAN_SWITCH);
	pChannel_switch->AddOption(_T("ON"));
	pChannel_switch->AddOption(_T("OFF"));
	pChannel_switch->AllowEdit(FALSE);
	pGroup_channel->AddSubItem(pChannel_switch);
	pChannel_type = new CMFCPropertyGridProperty(_T("信道类型"),_T("11"),_T("设置信道类型"),PROTO_CHAN_TYPE);
	pChannel_type->AddOption(_T("11"));
	pChannel_type->AddOption(_T("12"));
	pChannel_type->AddOption(_T("13"));
	pChannel_type->AddOption(_T("14"));
	pChannel_type->AddOption(_T("15"));
	pChannel_type->AddOption(_T("21"));
	pChannel_type->AddOption(_T("22"));
	pChannel_type->AddOption(_T("23"));
	pChannel_type->AddOption(_T("24"));
	pChannel_type->AddOption(_T("31"));
	pChannel_type->AddOption(_T("32"));
	pChannel_type->AddOption(_T("41"));
	pChannel_type->AddOption(_T("42"));
	pChannel_type->AddOption(_T("71"));
	pChannel_type->AddOption(_T("72"));
	pChannel_type->AddOption(_T("73"));
	pChannel_type->AddOption(_T("81"));
	pChannel_type->AddOption(_T("82"));
	pChannel_type->AddOption(_T("91"));
	pChannel_type->AddOption(_T("92"));
	pChannel_type->AllowEdit(FALSE);
	pGroup_channel->AddSubItem(pChannel_type);
	pChannel_sys_bw = new CMFCPropertyGridProperty(_T("系统带宽"),_T("2124.25MHz"),_T("设置系统带宽"),PROTO_CHAN_SYSBW);
	pGroup_channel->AddSubItem(pChannel_sys_bw);
	CMFCPropertyGridProperty* pChannel_noise_bw = new CMFCPropertyGridProperty(_T("噪声带宽"),_T("12456Hz"),_T("设置噪声带宽"));
	pGroup_channel->AddSubItem(pChannel_noise_bw);
	CMFCPropertyGridProperty* pChannel_nsys_ratio = new CMFCPropertyGridProperty(_T("最小噪声/系统带宽"),_T("12456Hz"),_T("计算最小噪声/系统带宽"));
	pGroup_channel->AddSubItem(pChannel_nsys_ratio);
	CMFCPropertyGridProperty* pChannel_snr = new CMFCPropertyGridProperty(_T("Eb/NO"),_T("00dB"),_T("计算信噪比"));
	pGroup_channel->AddSubItem(pChannel_snr);
	

	m_main_property.AddProperty(pGroup_carrier);
	m_main_property.AddProperty(pGroup_control);
	m_main_property.AddProperty(pGroup_modulation);
	m_main_property.AddProperty(pGroup_payload);
	m_main_property.AddProperty(pGroup_spectrum);
	m_main_property.AddProperty(pGroup_channel);


	m_main_property.EnableDescriptionArea(TRUE);
	m_main_property.SetCustomColors(RGB(250,250,250),RGB(0,0,0),RGB(230,230,230),RGB(100,100,100),RGB(230,230,230),RGB(0,0,0),RGB(220,220,220));
	m_main_property.ShowWindow(TRUE);

	m_finished_ini = TRUE;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CTabProtocolConfig::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (IsWindowVisible() || m_finished_ini)
	{
		m_main_property.MoveWindow(10,45,cx-32,cy-65);
		//m_MFCPropertyGridFour.Invalidate();
	}
}

LRESULT CTabProtocolConfig::OnPropertyChanged(__in WPARAM wparam,__in LPARAM lparam)
{
	CMFCPropertyGridProperty* pProp = (CMFCPropertyGridProperty*) lparam;
	CString str;
	CW* p_wave = &(((CGraphWAVE*)(((CMainFrame*)AfxGetMainWnd())->m_rightSplitter.GetPane(1,0)))->m_wave);//获取改变变量
	CTabCarrier &T_Carri = ((CTabParent*)(((CMainFrame*)AfxGetMainWnd())->m_mainSplitter.GetPane(0,0)))->m_tabCarrier;//跨页联动
	str = pProp->GetValue();
	int id_changed = pProp->GetData();//获取当前值发生变化的属性的ID

	/*******************153c界面参数传入*************************/
	SetFocus();
	switch (id_changed)
	{
	case PROTO_SIG_MODE_3C:
		if (str.Compare("SC") == 0)
		{
			p_3c_params->set_signal_mode(SC);//设置参数，将所有的参数都初始化
			//p_3c_params->Sig_mode = SC;
			pModulation_mcs->RemoveAllOptions();
			pModulation_mcs->AddOption(_T("0"));
			pModulation_mcs->AddOption(_T("1"));
			pModulation_mcs->AddOption(_T("2"));
			pModulation_mcs->AddOption(_T("3"));
			pModulation_mcs->AddOption(_T("4"));
			pModulation_mcs->AddOption(_T("5"));
			pModulation_mcs->AddOption(_T("6"));
			pModulation_mcs->AddOption(_T("7"));
			pModulation_mcs->AddOption(_T("8"));
			pModulation_mcs->AddOption(_T("9"));
			pModulation_mcs->AddOption(_T("10"));
			pModulation_mcs->AddOption(_T("11"));
			pModulation_mcs->AddOption(_T("12"));
			pModulation_mcs->AddOption(_T("13"));
			pModulation_mcs->AllowEdit(FALSE);
			p_wave->m_Maxspectrum = 1760;
			T_Carri.pPropS1->SetValue("SC");//界面联动
			pPayload_length->SetValue("30592");
			pModulation_mode->SetValue("π/2 BPSK");
			pModulation_mode->RemoveAllOptions();
			pModulation_mode->AddOption(_T("π/2 BPSK"));
			pModulation_mode->AddOption(_T("π/2 QPSK"));
			pModulation_mode->AddOption(_T("π/2 8-PSK"));
			pModulation_mode->AddOption(_T("π/2 16-QAM"));
			pModulation_mode->AllowEdit(FALSE);
			pPayload_map_type->Enable(FALSE);
			pPayload_uep_eep->Enable(FALSE);
			pPayload_interver->Enable(FALSE);
			pPayload_tone_inter->Enable(FALSE);
			pPayload_trans_rate->Show(FALSE);
		}
		else if (str.Compare("HSI") == 0)
		{
			p_3c_params->set_signal_mode(HSI);//设置参数，将所有的参数都初始化
			//p_3c_params->Sig_mode = HSI;
			pModulation_mcs->RemoveAllOptions();
			pModulation_mcs->AddOption(_T("0"));
			pModulation_mcs->AddOption(_T("1"));
			pModulation_mcs->AddOption(_T("2"));
			pModulation_mcs->AddOption(_T("3"));
			pModulation_mcs->AddOption(_T("4"));
			pModulation_mcs->AddOption(_T("5"));
			pModulation_mcs->AddOption(_T("6"));
			pModulation_mcs->AddOption(_T("7"));
			pModulation_mcs->AddOption(_T("8"));
			pModulation_mcs->AddOption(_T("9"));
			pModulation_mcs->AddOption(_T("10"));
			pModulation_mcs->AddOption(_T("11"));
			pModulation_mcs->AllowEdit(FALSE);
			p_wave->m_Maxspectrum = 2640;
			T_Carri.pPropS1->SetValue("HSI");
			pPayload_length->SetValue("5376");
			pModulation_mode->SetValue("QPSK");
			pModulation_mode->RemoveAllOptions();
			pModulation_mode->AddOption(_T("QPSK"));
			pModulation_mode->AddOption(_T("16-QAM"));
			pModulation_mode->AddOption(_T("64-QAM"));
			pModulation_mode->AllowEdit(FALSE);
			pPayload_pces->SetValue("OFF");
			pPayload_pces->Enable(FALSE);
			pPayload_map_type->Enable(TRUE);
			pPayload_uep_eep->Enable(TRUE);
			pModulation_fec->SetValue("LDPC(672,336)");
			pModulation_fec->RemoveAllOptions();
			pModulation_fec->AddOption(_T("LDPC(672,336)"));
			pModulation_fec->AddOption(_T("LDPC(672,420)"));
			pModulation_fec->AddOption(_T("LDPC(672,504)"));
			pModulation_fec->AddOption(_T("LDPC(672,588)"));
			pModulation_fec->AllowEdit(FALSE);
			pPayload_tone_inter->SetValue("OFF");
			pPayload_tone_inter->Enable(TRUE);
			pPayload_trans_rate->Show(FALSE);
		}
		else if (str.Compare("AV") == 0)
		{
			p_3c_params->set_signal_mode(AV);//设置参数，将所有的参数都初始化
			//p_3c_params->Sig_mode = AV;
			pModulation_mcs->RemoveAllOptions();
			pModulation_mcs->AddOption(_T("0"));
			pModulation_mcs->AddOption(_T("1"));
			pModulation_mcs->AddOption(_T("2"));
			pModulation_mcs->AddOption(_T("3"));
			pModulation_mcs->AddOption(_T("4"));
			pModulation_mcs->AddOption(_T("5"));
			pModulation_mcs->AddOption(_T("6"));
			pModulation_mcs->AllowEdit(FALSE);
			p_wave->m_Maxspectrum = 2538;
			T_Carri.pPropS1->SetValue("AV");
			pPayload_length->SetValue("5184");
			pModulation_mode->SetValue("QPSK");
			pModulation_mode->RemoveAllOptions();
			pModulation_mode->AddOption(_T("QPSK"));
			pModulation_mode->AddOption(_T("16-QAM"));
			pModulation_mode->AllowEdit(FALSE);
			pModulation_fec->SetValue("RS(224,216)");
			pPayload_tone_inter->SetValue("OFF"); 
			pPayload_tone_inter->Enable(TRUE);
			pPayload_spreader->SetValue("1");
			pPayload_spreader->Enable(FALSE);
			pPayload_trans_rate->Show(TRUE);
		}
		else
		{
			MessageBox("不支持的信号模式！",NULL,MB_ICONERROR);
		}
		break;

	case PROTO_SIG_TONEINTER_3C:
		if (p_3c_params->Sig_mode == HSI)
		{
			if (str.Compare("ON") == 0)
				p_3c_params->HSI_p.ti = 1;
			else
				p_3c_params->HSI_p.ti = 0;
		}
		else if (p_3c_params->Sig_mode == AV)
		{
			if (str.Compare("ON") == 0)
				p_3c_params->AV_p.ti = 1;
			else
				p_3c_params->AV_p.ti = 0;
		}
		break;

	case PROTO_SIG_MCS_3C://配置MCS
		{
			int mcs_temp = atoi(str.GetBuffer());
			if (p_3c_params->Sig_mode == SC)
			{
				{
					switch (mcs_temp)
					{
					case 0:
						p_3c_params->SC_p.MCS = 0;//更改MCS
						p_3c_params->SC_p.sp = 64;//更改扩频因子
						p_3c_params->SC_p.modtype = 1;//更改调制方式
						p_3c_params->SC_p.FECtype = 0;//更改前向编码方式
						p_3c_params->SC_p.subtype = 0;//MCS0固定为部分子块
						pModulation_mode->SetValue("π/2 BPSK");
						pModulation_fec->SetValue("RS(255,239)");
						pPayload_spreader->SetValue("0");
						break;
					case 1:
						p_3c_params->SC_p.MCS = 1;//更改MCS
						p_3c_params->SC_p.sp = 4;//更改扩频因子
						p_3c_params->SC_p.modtype = 1;//更改调制方式
						p_3c_params->SC_p.FECtype = 0;//更改前向编码方式
						//p_3c_params->SC_p.L_mb = 239 * 16;
						pModulation_mode->SetValue("π/2 BPSK");
						pModulation_fec->SetValue("RS(255,239)");
						pPayload_spreader->SetValue("4");
						break;
					case 2:
						p_3c_params->SC_p.MCS = 2;//更改MCS
						p_3c_params->SC_p.sp = 2;//更改扩频因子
						p_3c_params->SC_p.modtype = 1;//更改调制方式
						p_3c_params->SC_p.FECtype = 0;//更改前向编码方式
						//p_3c_params->SC_p.L_mb = 239 * 32;
						pModulation_mode->SetValue("π/2 BPSK");
						pModulation_fec->SetValue("RS(255,239)");
						pPayload_spreader->SetValue("2");
						break;
					case 3:
						p_3c_params->SC_p.MCS = 3;//更改MCS
						p_3c_params->SC_p.sp = 1;//更改扩频因子
						p_3c_params->SC_p.modtype = 1;//更改调制方式
						p_3c_params->SC_p.FECtype = 0;//更改前向编码方式
						//p_3c_params->SC_p.L_mb = 239 * 64;
						pModulation_mode->SetValue("π/2 BPSK");
						pModulation_fec->SetValue("RS(255,239)");
						pPayload_spreader->SetValue("1");
						break;
					case 4:
						p_3c_params->SC_p.MCS = 4;//更改MCS
						p_3c_params->SC_p.sp = 1;//更改扩频因子
						p_3c_params->SC_p.modtype = 1;//更改调制方式
						p_3c_params->SC_p.FECtype = 1;//更改前向编码方式
						p_3c_params->SC_p.FECrate = 2;//更改前向编码码率
						//p_3c_params->SC_p.L_mb = 504 * 32;
						pModulation_mode->SetValue("π/2 BPSK");
						pModulation_fec->SetValue("LDPC(672,504)");
						pPayload_spreader->SetValue("1");
						break;
					case 5:
						p_3c_params->SC_p.MCS = 5;//更改MCS
						p_3c_params->SC_p.sp = 2;//更改扩频因子
						p_3c_params->SC_p.modtype = 1;//更改调制方式
						p_3c_params->SC_p.FECtype = 1;//更改前向编码方式
						p_3c_params->SC_p.FECrate = 0;//更改前向编码码率
						//p_3c_params->SC_p.L_mb = 336 * 16;
						pModulation_mode->SetValue("π/2 BPSK");
						pModulation_fec->SetValue("LDPC(672,336)");
						pPayload_spreader->SetValue("2");
						break;
					case 6:
						p_3c_params->SC_p.MCS = 6;//更改MCS
						p_3c_params->SC_p.sp = 1;//更改扩频因子
						p_3c_params->SC_p.modtype = 1;//更改调制方式
						p_3c_params->SC_p.FECtype = 1;//更改前向编码方式
						p_3c_params->SC_p.FECrate = 0;//更改前向编码码率
						//p_3c_params->SC_p.L_mb = 336 * 32;
						pModulation_mode->SetValue("π/2 BPSK");
						pModulation_fec->SetValue("LDPC(672,336)");
						pPayload_spreader->SetValue("1");
						break;
					case 7:
						p_3c_params->SC_p.MCS = 7;//更改MCS
						p_3c_params->SC_p.sp = 1;//更改扩频因子
						p_3c_params->SC_p.modtype = 2;//更改调制方式
						p_3c_params->SC_p.FECtype = 1;//更改前向编码方式
						p_3c_params->SC_p.FECrate = 0;//更改前向编码码率
						//p_3c_params->SC_p.L_mb = 336 * 32;
						pModulation_mode->SetValue("π/2 QPSK");
						pModulation_fec->SetValue("LDPC(672,336)");
						pPayload_spreader->SetValue("1");
						break;
					case 8:
						p_3c_params->SC_p.MCS = 8;//更改MCS
						p_3c_params->SC_p.sp = 1;//更改扩频因子
						p_3c_params->SC_p.modtype = 2;//更改调制方式
						p_3c_params->SC_p.FECtype = 1;//更改前向编码方式
						p_3c_params->SC_p.FECrate = 2;//更改前向编码码率
						//p_3c_params->SC_p.L_mb = 504 * 32;
						pModulation_mode->SetValue("π/2 QPSK");
						pModulation_fec->SetValue("LDPC(672,504)");
						pPayload_spreader->SetValue("1");
						break;
					case 9:
						p_3c_params->SC_p.MCS = 9;//更改MCS
						p_3c_params->SC_p.sp = 1;//更改扩频因子
						p_3c_params->SC_p.modtype = 2;//更改调制方式
						p_3c_params->SC_p.FECtype = 1;//更改前向编码方式
						p_3c_params->SC_p.FECrate = 3;//更改前向编码码率
						//p_3c_params->SC_p.L_mb = 588 * 32;
						pModulation_mode->SetValue("π/2 QPSK");
						pModulation_fec->SetValue("LDPC(672,588)");
						pPayload_spreader->SetValue("1");
						break;
					case 10://LDPC编码码率1440/1344,还没做
						p_3c_params->SC_p.MCS = 10;//更改MCS
						p_3c_params->SC_p.sp = 1;//更改扩频因子
						p_3c_params->SC_p.modtype = 2;//更改调制方式
						p_3c_params->SC_p.FECtype = 1;//更改前向编码方式
						p_3c_params->SC_p.FECrate = 3;//更改前向编码码率
						//p_3c_params->SC_p.L_mb = 588 * 32;
						pModulation_mode->SetValue("π/2 QPSK");
						pModulation_fec->SetValue("LDPC(1440,1344)");
						pPayload_spreader->SetValue("1");
						break;
					case 11:
						p_3c_params->SC_p.MCS = 11;//更改MCS
						p_3c_params->SC_p.sp = 1;//更改扩频因子
						p_3c_params->SC_p.modtype = 2;//更改调制方式
						p_3c_params->SC_p.FECtype = 0;//更改前向编码方式
						p_3c_params->SC_p.FECrate = 3;//更改前向编码码率
						//p_3c_params->SC_p.L_mb = 239 * 64;
						pModulation_mode->SetValue("π/2 QPSK");
						pModulation_fec->SetValue("RS(255,239)");
						pPayload_spreader->SetValue("1");
						break;
					case 12:
						p_3c_params->SC_p.MCS = 12;//更改MCS
						p_3c_params->SC_p.sp = 1;//更改扩频因子
						p_3c_params->SC_p.modtype = 3;//更改调制方式
						p_3c_params->SC_p.FECtype = 1;//更改前向编码方式
						p_3c_params->SC_p.FECrate = 2;//更改前向编码码率
						//p_3c_params->SC_p.L_mb = 504 * 24;
						pModulation_mode->SetValue("π/2 8PSK");
						pModulation_fec->SetValue("LDPC(672,504)");
						pPayload_spreader->SetValue("1");
						break;
					case 13:
						p_3c_params->SC_p.MCS = 13;//更改MCS
						p_3c_params->SC_p.sp = 1;//更改扩频因子
						p_3c_params->SC_p.modtype = 4;//更改调制方式
						p_3c_params->SC_p.FECtype = 1;//更改前向编码方式
						p_3c_params->SC_p.FECrate = 2;//更改前向编码码率
						//p_3c_params->SC_p.L_mb = 504 * 32;//macbody长度
						pModulation_mode->SetValue("π/2 16-QAM");
						pModulation_fec->SetValue("LDPC(672,504)");
						pPayload_spreader->SetValue("1");
						break;
					}
				}
			}
			else if (p_3c_params->Sig_mode == HSI)
			{
				{
					switch (mcs_temp)
					{
					case 0:
						p_3c_params->HSI_p.MCS = 0;//更改MCS
						p_3c_params->HSI_p.sp = 48;//更改扩频因子
						p_3c_params->HSI_p.modtype = 2;//更改调制方式
						p_3c_params->HSI_p.UEP = 0;//更改UEP方式
						p_3c_params->HSI_p.FECrate = 0;//更改前向编码码率
						//p_3c_params->HSI_p.L_mb = 336 * 4;//macbody长度
						pModulation_mode->SetValue("QPSK");
						pModulation_fec->SetValue("LDPC(672,336)");
						pPayload_spreader->SetValue("48");
						pPayload_uep_eep->SetValue("EEP");
						break;
					case 1:
						p_3c_params->HSI_p.MCS = 1;//更改MCS
						p_3c_params->HSI_p.sp = 1;//更改扩频因子
						p_3c_params->HSI_p.modtype = 2;//更改调制方式
						p_3c_params->HSI_p.UEP = 0;//更改UEP方式
						p_3c_params->HSI_p.FECrate = 0;//更改前向编码码率
						//p_3c_params->HSI_p.L_mb = 336 * 32;//macbody长度
						pModulation_mode->SetValue("QPSK");
						pModulation_fec->SetValue("LDPC(672,336)");
						pPayload_spreader->SetValue("1");
						pPayload_uep_eep->SetValue("EEP");
						break;
					case 2:
						p_3c_params->HSI_p.MCS = 2;//更改MCS
						p_3c_params->HSI_p.sp = 1;//更改扩频因子
						p_3c_params->HSI_p.modtype = 2;//更改调制方式
						p_3c_params->HSI_p.UEP = 0;//更改UEP方式
						p_3c_params->HSI_p.FECrate = 2;//更改前向编码码率
						//p_3c_params->HSI_p.L_mb = 504 * 32;//macbody长度
						pModulation_mode->SetValue("QPSK");
						pModulation_fec->SetValue("LDPC(672,504)");
						pPayload_spreader->SetValue("1");
						pPayload_uep_eep->SetValue("EEP");
						break;
					case 3:
						p_3c_params->HSI_p.MCS = 3;//更改MCS
						p_3c_params->HSI_p.sp = 1;//更改扩频因子
						p_3c_params->HSI_p.modtype = 2;//更改调制方式
						p_3c_params->HSI_p.UEP = 0;//更改UEP方式
						p_3c_params->HSI_p.FECrate = 3;//更改前向编码码率
						//p_3c_params->HSI_p.L_mb = 588 * 16;//macbody长度
						pModulation_mode->SetValue("QPSK");
						pModulation_fec->SetValue("LDPC(672,588)");
						pPayload_spreader->SetValue("1");
						pPayload_uep_eep->SetValue("EEP");
						break;
					case 4:
						p_3c_params->HSI_p.MCS = 4;//更改MCS
						p_3c_params->HSI_p.sp = 1;//更改扩频因子
						p_3c_params->HSI_p.modtype = 4;//更改调制方式
						p_3c_params->HSI_p.UEP = 0;//更改UEP方式
						p_3c_params->HSI_p.FECrate = 0;//更改前向编码码率
						//p_3c_params->HSI_p.L_mb = 336 * 64;//macbody长度
						pModulation_mode->SetValue("16-QAM");
						pModulation_fec->SetValue("LDPC(672,336)");
						pPayload_spreader->SetValue("1");
						pPayload_uep_eep->SetValue("EEP");
						break;
					case 5:
						p_3c_params->HSI_p.MCS = 5;//更改MCS
						p_3c_params->HSI_p.sp = 1;//更改扩频因子
						p_3c_params->HSI_p.modtype = 4;//更改调制方式
						p_3c_params->HSI_p.UEP = 0;//更改UEP方式
						p_3c_params->HSI_p.FECrate = 2;//更改前向编码码率
						//p_3c_params->HSI_p.L_mb = 504 * 64;//macbody长度
						pModulation_mode->SetValue("16-QAM");
						pModulation_fec->SetValue("LDPC(672,504)");
						pPayload_spreader->SetValue("1");
						pPayload_uep_eep->SetValue("EEP");
						break;
					case 6:
						p_3c_params->HSI_p.MCS = 6;//更改MCS
						p_3c_params->HSI_p.sp = 1;//更改扩频因子
						p_3c_params->HSI_p.modtype = 4;//更改调制方式
						p_3c_params->HSI_p.UEP = 0;//更改UEP方式
						p_3c_params->HSI_p.FECrate = 3;//更改前向编码码率
						//p_3c_params->HSI_p.L_mb = 588 * 64;//macbody长度
						pModulation_mode->SetValue("16-QAM");
						pModulation_fec->SetValue("LDPC(672,588)");
						pPayload_spreader->SetValue("1");
						pPayload_uep_eep->SetValue("EEP");
						break;
					case 7:
						p_3c_params->HSI_p.MCS = 7;//更改MCS
						p_3c_params->HSI_p.sp = 1;//更改扩频因子
						p_3c_params->HSI_p.modtype = 6;//更改调制方式
						p_3c_params->HSI_p.UEP = 0;//更改UEP方式
						p_3c_params->HSI_p.FECrate = 1;//更改前向编码码率
						//p_3c_params->HSI_p.L_mb = 420 * 96;//macbody长度
						pModulation_mode->SetValue("64-QAM");
						pModulation_fec->SetValue("LDPC(672,420)");
						pPayload_spreader->SetValue("1");
						pPayload_uep_eep->SetValue("EEP");
						break;
					case 8:
						p_3c_params->HSI_p.MCS = 8;//更改MCS
						p_3c_params->HSI_p.sp = 1;//更改扩频因子
						p_3c_params->HSI_p.modtype = 2;//更改调制方式
						p_3c_params->HSI_p.UEP = 1;//更改UEP方式
						p_3c_params->HSI_p.FECrate = 0;//更改前向编码码率
						//p_3c_params->HSI_p.L_mb = 168 * 96;//macbody长度
						pModulation_mode->SetValue("QPSK");
						pModulation_fec->SetValue("LDPC(672,336),LDPC(672,504)");
						pPayload_spreader->SetValue("1");
						pPayload_uep_eep->SetValue("UEP");
						break;
					case 9:
						p_3c_params->HSI_p.MCS = 9;//更改MCS
						p_3c_params->HSI_p.sp = 1;//更改扩频因子
						p_3c_params->HSI_p.modtype = 2;//更改调制方式
						p_3c_params->HSI_p.UEP = 1;//更改UEP方式
						p_3c_params->HSI_p.FECrate = 2;//更改前向编码码率
						//p_3c_params->HSI_p.L_mb = 84 * 42 * 8;//macbody长度
						pModulation_mode->SetValue("QPSK");
						pModulation_fec->SetValue("LDPC(672,504),LDPC(672,588)");
						pPayload_spreader->SetValue("1");
						pPayload_uep_eep->SetValue("UEP");
						break;
					case 10:
						p_3c_params->HSI_p.MCS = 9;//更改MCS
						p_3c_params->HSI_p.sp = 1;//更改扩频因子
						p_3c_params->HSI_p.modtype = 4;//更改调制方式
						p_3c_params->HSI_p.UEP = 1;//更改UEP方式
						p_3c_params->HSI_p.FECrate = 0;//更改前向编码码率
						//p_3c_params->HSI_p.L_mb = 168 * 96;//macbody长度
						pModulation_mode->SetValue("16-QAM");
						pModulation_fec->SetValue("LDPC(672,336),LDPC(672,504)");
						pPayload_spreader->SetValue("1");
						pPayload_uep_eep->SetValue("UEP");
						break;
					case 11:
						p_3c_params->HSI_p.MCS = 9;//更改MCS
						p_3c_params->HSI_p.sp = 1;//更改扩频因子
						p_3c_params->HSI_p.modtype = 4;//更改调制方式
						p_3c_params->HSI_p.UEP = 1;//更改UEP方式
						p_3c_params->HSI_p.FECrate = 2;//更改前向编码码率
						//p_3c_params->HSI_p.L_mb = 84 * 42 * 16;//macbody长度
						pModulation_mode->SetValue("16-QAM");
						pModulation_fec->SetValue("LDPC(672,504),LDPC(672,588)");
						pPayload_spreader->SetValue("1");
						pPayload_uep_eep->SetValue("UEP");
						break;
					}
				}
			}
			else if (p_3c_params->Sig_mode == AV)
			{
				{
					if (p_3c_params->AV_p.transRateType == 0)
					{
						switch (mcs_temp)
						{
						case 0:
							p_3c_params->AV_p.MCS = 0;//更改MCS
							p_3c_params->AV_p.modtype = 2;//更改调制方式
							p_3c_params->AV_p.UEP = 0;//更改UEP方式
							p_3c_params->AV_p.rate_up = 0;//更改上支路编码码率
							p_3c_params->AV_p.rate_low = 0;//更改下支路编码码率
							//p_3c_params->AV_p.L_mb = 216 * 32;//macbody长度
							pModulation_mode->SetValue("QPSK");
							pModulation_fec->SetValue("RS(224,216)");
							pPayload_uep_eep->SetValue("EEP");
							break;
						case 1:
							p_3c_params->AV_p.MCS = 1;//更改MCS
							p_3c_params->AV_p.modtype = 2;//更改调制方式
							p_3c_params->AV_p.UEP = 0;//更改UEP方式
							p_3c_params->AV_p.rate_up = 3;//更改上支路编码码率
							p_3c_params->AV_p.rate_low = 3;//更改下支路编码码率
							//p_3c_params->AV_p.L_mb = 216 * 32;//macbody长度
							pModulation_mode->SetValue("QPSK");
							pModulation_fec->SetValue("RS(224,216)");
							pPayload_uep_eep->SetValue("EEP");
							break;
						case 2:
							p_3c_params->AV_p.MCS = 2;//更改MCS
							p_3c_params->AV_p.modtype = 4;//更改调制方式
							p_3c_params->AV_p.UEP = 0;//更改UEP方式
							p_3c_params->AV_p.rate_up = 3;//更改上支路编码码率
							p_3c_params->AV_p.rate_low = 3;//更改下支路编码码率
							//p_3c_params->AV_p.L_mb = 216 * 32;//macbody长度
							pModulation_mode->SetValue("16-QAM");
							pModulation_fec->SetValue("RS(224,216)");
							pPayload_uep_eep->SetValue("EEP");
							break;
						case 3:
							p_3c_params->AV_p.MCS = 3;//更改MCS
							p_3c_params->AV_p.modtype = 2;//更改调制方式
							p_3c_params->AV_p.UEP = 1;//更改UEP方式
							p_3c_params->AV_p.rate_up = 2;//更改上支路编码码率
							p_3c_params->AV_p.rate_low = 4;//更改下支路编码码率
							//p_3c_params->AV_p.L_mb = 216 * 32;//macbody长度
							pModulation_mode->SetValue("QPSK");
							pModulation_fec->SetValue("RS(224,216)");
							pPayload_uep_eep->SetValue("UEP");
							break;
						case 4:
							p_3c_params->AV_p.MCS = 4;//更改MCS
							p_3c_params->AV_p.modtype = 4;//更改调制方式
							p_3c_params->AV_p.UEP = 1;//更改UEP方式
							p_3c_params->AV_p.rate_up = 2;//更改上支路编码码率
							p_3c_params->AV_p.rate_low = 4;//更改下支路编码码率
							//p_3c_params->AV_p.L_mb = 216 * 32;//macbody长度
							pModulation_mode->SetValue("16-QAM");
							pModulation_fec->SetValue("RS(224,216)");
							pPayload_uep_eep->SetValue("UEP");
							break;
						case 5:
							p_3c_params->AV_p.MCS = 5;//更改MCS
							p_3c_params->AV_p.modtype = 2;//更改调制方式
							p_3c_params->AV_p.UEP = 2;//更改UEP方式
							p_3c_params->AV_p.rate_up = 0;//更改上支路编码码率
							p_3c_params->AV_p.rate_low = 0;//更改下支路编码码率
							//p_3c_params->AV_p.L_mb = 216 * 32;//macbody长度
							pModulation_mode->SetValue("QPSK");
							pModulation_fec->SetValue("RS(224,216)");
							pPayload_uep_eep->SetValue("MSB-only");
							break;
						case 6:
							p_3c_params->AV_p.MCS = 0;//更改MCS
							p_3c_params->AV_p.modtype = 2;//更改调制方式
							p_3c_params->AV_p.UEP = 2;//更改UEP方式
							p_3c_params->AV_p.rate_up = 3;//更改上支路编码码率
							p_3c_params->AV_p.rate_low = 3;//更改下支路编码码率
							//p_3c_params->AV_p.L_mb = 216 * 32;//macbody长度
							pModulation_mode->SetValue("QPSK");
							pModulation_fec->SetValue("RS(224,216)");
							pPayload_uep_eep->SetValue("MSB-only");
							break;
						case 7:
							p_3c_params->AV_p.MCS = 7;//更改MCS
							p_3c_params->AV_p.modtype = 1;//更改调制方式
							p_3c_params->AV_p.UEP = 2;//更改UEP方式
							p_3c_params->AV_p.rate_up = 3;//更改上支路编码码率
							p_3c_params->AV_p.rate_low = 3;//更改下支路编码码率
							//p_3c_params->AV_p.L_mb = 216 * 32;//macbody长度
							pModulation_mode->SetValue("BPSK");
							pModulation_fec->Enable(FALSE);
							pPayload_uep_eep->Enable(FALSE);
							break;
						case 8:
							p_3c_params->AV_p.MCS = 8;//更改MCS
							p_3c_params->AV_p.modtype = 1;//更改调制方式
							p_3c_params->AV_p.UEP = 2;//更改UEP方式
							p_3c_params->AV_p.rate_up = 3;//更改上支路编码码率
							p_3c_params->AV_p.rate_low = 3;//更改下支路编码码率
							//p_3c_params->AV_p.L_mb = 216 * 32;//macbody长度
							pModulation_mode->SetValue("BPSK");
							pModulation_fec->Enable(FALSE);
							pPayload_uep_eep->Enable(FALSE);
							break;
						case 9:
							p_3c_params->AV_p.MCS = 9;//更改MCS
							p_3c_params->AV_p.modtype = 1;//更改调制方式
							p_3c_params->AV_p.UEP = 2;//更改UEP方式
							p_3c_params->AV_p.rate_up = 3;//更改上支路编码码率
							p_3c_params->AV_p.rate_low = 3;//更改下支路编码码率
							//p_3c_params->AV_p.L_mb = 216 * 32;//macbody长度
							pModulation_mode->SetValue("BPSK");
							pModulation_fec->Enable(FALSE);
							pPayload_uep_eep->Enable(FALSE);
							break;
						case 10:
							p_3c_params->AV_p.MCS = 10;//更改MCS
							p_3c_params->AV_p.modtype = 1;//更改调制方式
							p_3c_params->AV_p.UEP = 2;//更改UEP方式
							p_3c_params->AV_p.rate_up = 3;//更改上支路编码码率
							p_3c_params->AV_p.rate_low = 3;//更改下支路编码码率
							//p_3c_params->AV_p.L_mb = 216 * 32;//macbody长度
							pModulation_mode->SetValue("BPSK");
							pModulation_fec->Enable(FALSE);
							pPayload_uep_eep->Enable(FALSE);
							break;
						default:
							break;
						}
					}
					else
					{
						switch (mcs_temp)
						{
						case 0:
							p_3c_params->AV_p.MCS = 0;//更改MCS
							p_3c_params->AV_p.rate_up = 0;//更改上支路编码码率
							p_3c_params->AV_p.rep = 9;
							break;
						case 1:
							p_3c_params->AV_p.MCS = 1;//更改MCS
							p_3c_params->AV_p.rate_up = 1;//更改上支路编码码率
							p_3c_params->AV_p.rep = 9;
							break;
						case 2:
							p_3c_params->AV_p.MCS = 2;//更改MCS
							p_3c_params->AV_p.rate_up = 3;//更改上支路编码码率
							p_3c_params->AV_p.rep = 9;
							break;
						case 3:
							p_3c_params->AV_p.MCS = 3;//更改MCS
							p_3c_params->AV_p.rate_up = 3;//更改上支路编码码率
							p_3c_params->AV_p.rep = 5;
							break;
						default:
							break;
						}
					}
				}
			}
			break;
		}
		case PROTO_CHAN_SWITCH:
				if (str.Compare("OFF") == 0)
					p_channel_params->chanel_switch = 0;
				else
					p_channel_params->chanel_switch = 1;
			break;
		
		case PROTO_CHAN_TYPE:
			p_channel_params->cm_num=atoi(str.GetBuffer());
			break;

		case PROTO_SIG_DATA_SOURCE_3C:
			if (str.Compare("PN9") ==0)
				p_3c_params->data_source = 0;
			else if (str.Compare("PN15") ==0)
				p_3c_params->data_source = 1;
			else if (str.Compare("ALL0") ==0)
				p_3c_params->data_source = 2;
			else
				p_3c_params->data_source = 3;
			break;
		case PROTO_SIG_PAYLOADLENGTH_3C:
			switch (p_3c_params->Sig_mode) 
			{
			case SC:
				p_3c_params->SC_p.L_mb = atoi(str.GetBuffer());
				break;
			case HSI:
				p_3c_params->HSI_p.L_mb = atoi(str.GetBuffer());
				break;
			case AV:
				p_3c_params->AV_p.L_mb = atoi(str.GetBuffer());
				break;
			default:
				break;
			}
			break;
		case PROTO_SIG_GENLENGTH_3C:
			switch (p_3c_params->Sig_mode) 
			{
			case SC:
				p_3c_params->SC_p.L_mb = atoi(str.GetBuffer());
				break;
			case HSI:
				p_3c_params->HSI_p.L_mb = atoi(str.GetBuffer());
				break;
			case AV:
				p_3c_params->AV_p.L_mb = atoi(str.GetBuffer());
				break;
			default:
				break;
			}
			break;
		case PROTO_SIG_TRANS_RATE_TYPE:
			if (str.Compare("HRP") == 0)
			{
				p_3c_params->AV_p.transRateType = 0;
				p_3c_params->set_signal_mode(AV);//设置参数，将所有的参数都初始化
				pModulation_mcs->RemoveAllOptions();
				pModulation_mcs->AddOption(_T("0"));
				pModulation_mcs->AddOption(_T("1"));
				pModulation_mcs->AddOption(_T("2"));
				pModulation_mcs->AddOption(_T("3"));
				pModulation_mcs->AddOption(_T("4"));
				pModulation_mcs->AddOption(_T("5"));
				pModulation_mcs->AddOption(_T("6"));
				pModulation_mcs->AllowEdit(FALSE);
				p_wave->m_Maxspectrum = 2538;
				T_Carri.pPropS1->SetValue("AV");
				pPayload_length->SetValue("5184");
				pModulation_mode->SetValue("QPSK");
				pModulation_mode->RemoveAllOptions();
				pModulation_mode->AddOption(_T("QPSK"));
				pModulation_mode->AddOption(_T("16-QAM"));
				pModulation_mode->AllowEdit(FALSE);
				pModulation_fec->SetValue("RS(224,216)");
				pPayload_tone_inter->SetValue("OFF"); 
				pPayload_tone_inter->Enable(TRUE);
				pPayload_spreader->SetValue("1");
				pPayload_spreader->Enable(FALSE);
				pPayload_trans_rate->Show(TRUE);
			}
			else
			{
				p_3c_params->set_signal_mode(AV);//设置参数，将所有的参数都初始化
				p_3c_params->AV_p.transRateType = 1;
				pModulation_mcs->SetValue("0");
				pModulation_mcs->RemoveAllOptions();
				pModulation_mcs->AddOption(_T("0"));
				pModulation_mcs->AddOption(_T("1"));
				pModulation_mcs->AddOption(_T("2"));
				pModulation_mcs->AddOption(_T("3"));;
				pModulation_mcs->AllowEdit(FALSE);
				p_wave->m_Maxspectrum = 2538;
				T_Carri.pPropS1->SetValue("AV");
				pPayload_length->SetValue("24");
				pPayload_length->AllowEdit(FALSE);
				pModulation_mode->SetValue("BPSK");
				pModulation_mode->RemoveAllOptions();
				pModulation_mode->AllowEdit(FALSE);
				pModulation_fec->Enable(FALSE);
				pPayload_tone_inter->SetValue("OFF"); 
				pPayload_tone_inter->Enable(FALSE);
				pPayload_spreader->SetValue("1");
				pPayload_spreader->Enable(FALSE);
				pPayload_trans_rate->Show(TRUE);
				p_3c_params->AV_p.L_mb = 24;
				p_3c_params->AV_p.rate_up = 0;
				p_3c_params->AV_p.rep = 9;
			}
			break;
		case PROTO_SIG_SSID_3C:
			{
				int ssid = 0;
				for (int i = 0; i < 4; ++i)
					ssid += pow(double(2), double(3 - i)) * (str.GetAt(i) - '0');
				p_3c_params->SC_p.ssid = ssid;
				p_3c_params->HSI_p.ssid = ssid;
				p_3c_params->AV_p.ssid = ssid;
				break;
			}
	default:
		break;
	}
	/**********************************************************/

	//先注释掉，应该与界面和程序参数的联动有关
	//SetFocus();
	//switch (id_changed)
	//{
	//case CONFIG_TRANS_TYPE:
	//	if (str.Compare("ACL(Asynchronous)") == 0){
	//		p_bluetoothparams->transtype = BlueTooth_ACL;//MessageBox(str);
	//	}else if (str.Compare(_T("SCO(Synchronous)")) == 0){
	//		p_bluetoothparams->transtype = BlueTooth_SCO;//MessageBox(str);
	//	}else{
	//		MessageBox("不支持的传输模式！",NULL,MB_ICONERROR);
	//	}
	//	break;
	//case CONFIG_PACK_TYPE:
	//	if (0 == str.Compare("ID")){
	//		p_bluetoothparams->packettype = ID;//MessageBox(str);
	//	}else if (0 == str.Compare("NULLPACK")){
	//		p_bluetoothparams->packettype = NuLLpack;//MessageBox(str);
	//	}else if (0 == str.Compare("POLL")){
	//		p_bluetoothparams->packettype = POLL;//MessageBox(str);
	//	}else if (0 == str.Compare("FHS")){
	//		p_bluetoothparams->packettype = FHS;//MessageBox(str);
	//	}else if (0 == str.Compare("HV1")){
	//		p_bluetoothparams->packettype = HV1;//MessageBox(str);
	//	}else if (0 == str.Compare("HV2")){
	//		p_bluetoothparams->packettype = HV2;//MessageBox(str);
	//	}else if (0 == str.Compare("HV3")){
	//		p_bluetoothparams->packettype = HV3;//MessageBox(str);
	//	}else if (0 == str.Compare("DM1")){
	//		p_bluetoothparams->packettype = DM1;//MessageBox(str);
	//	}else if (0 == str.Compare("DH1")){
	//		p_bluetoothparams->packettype = DH1;//MessageBox(str);
	//	}else if (0 == str.Compare("DM3")){
	//		p_bluetoothparams->packettype = DM3;//MessageBox(str);
	//	}else if (0 == str.Compare("DH3")){
	//		p_bluetoothparams->packettype = DH3;//MessageBox(str);
	//	}else if (0 == str.Compare("DM5")){
	//		p_bluetoothparams->packettype = DM5;//MessageBox(str);
	//	}else if (0 == str.Compare("DH5")){
	//		p_bluetoothparams->packettype = DH5;//MessageBox(str);
	//	}else if (0 == str.Compare("AUX1")){
	//		p_bluetoothparams->packettype = AUX1;//MessageBox(str);
	//	}else{
	//		MessageBox("不支持的数据包类型！",NULL,MB_ICONERROR);
	//	}
	//	break;
	//case CONFIG_LAPADDR://有待完成
	//	//p_bluetoothparams->Lapadder = str.GetBuffer(24);
	//	break;
	//case CONFIG_DATA_RATE: 
	//	str.MakeUpper();
	//	str.Remove('M');
	//	str.Remove(' ');
	//	p_bluetoothparams->Rs = atof(str.GetBuffer()) * 1e6;//MessageBox(str);
	//	str.Append("M");
	//	pProp->SetValue((COleVariant)str);
	//	break;
	//case CONFIG_MAX_LENGTH://有待完成
	//	str.Remove(' ');
	//	break;
	//case CONFIG_DATA_SOURCE:
	//	if (0 == str.Compare("随机序列"))
	//	{
	//		//选择随机序列应做的处理
	//		//MessageBox(str);
	//	}else if (0 == str.Compare("选择文件"))
	//	{
	//		//选择读取文件应做的处理
	//		//MessageBox(str);
	//	}
	//	break;
	//case CONFIG_OVERSAMP_FACTOR:
	//	str.Remove(' ');
	//	if(0 == atoi(str.GetBuffer()))
	//	{
	//		MessageBox("过采样值设置有误！",NULL,MB_ICONERROR);
	//		str.Format("%d",p_bluetoothparams->oversample);
	//		pProp->SetValue((COleVariant)str);
	//	}else if (20 < atoi(str.GetBuffer()))
	//	{
	//		str.Format("%d",20);
	//		pProp->SetValue((COleVariant)str);
	//		p_bluetoothparams->oversample = 20;
	//	}/*else if (1 == atoi(str.GetBuffer()))
	//	{
	//		str.Format("%d",2);
	//		pProp->SetValue((COleVariant)str);
	//		p_bluetoothparams->oversample = 2;
	//	}*/else
	//	{
	//		p_bluetoothparams->oversample = atoi(str.GetBuffer());
	//		str.Format("%d",atoi(str.GetBuffer()));
	//		pProp->SetValue((COleVariant)str);
	//	}
	//	str.Format("%d",0);
	//	break;
	//case CONFIG_EFC_STATE://有待完成
	//	break;
	//case CONFIG_CRC_STATE://有待完成
	//	break;
	//case CONFIG_HEC_STATE://有待完成
	//	break;
	//case CONFIG_BTB:
	//	str.Remove(' ');
	//	if ((0.0 == atof(str.GetBuffer())) || (atof(str.GetBuffer())>=1.0))
	//	{
	//		MessageBox("调制指数设置有误！",NULL,MB_ICONERROR);
	//		str.Format("%f",p_bluetoothparams->BTb);
	//		pProp->SetValue((COleVariant)str);
	//	} else
	//	{
	//		p_bluetoothparams->BTb = atof(str.GetBuffer());
	//	}
	//	break;
	//case CONFIG_FC:
	//	str.MakeUpper();
	//	str.Remove(' ');
	//	str.Remove('G');
	//	p_bluetoothparams->fc = atof(str.GetBuffer()) * 1e9;//MessageBox(_T("changed"));
	//	break;
	//case CONFIG_NOISE_POWER://有待完成
	//	break;
	//default:
	//	break;
	//}

	return 0;
}