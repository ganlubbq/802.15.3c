// TabProtocolConfig.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "TabProtocolConfig.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "MacDiag.h"

// CTabProtocolConfig �Ի���

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
	p_bluetoothparams = 0;//���캯�����Ƚ�ָ�븳Ϊ0����OnInitDialog���پ��帳ֵ
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


// CTabProtocolConfig ��Ϣ�������


void CTabProtocolConfig::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialog::OnOK();
}


BOOL CTabProtocolConfig::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_mode.SetCurSel(0);
	//�й�Э�����õ�ָ�봫�ݵ�����Э����
	p_bluetoothparams = ((CMainFrame*)AfxGetMainWnd())->m_pass_to_thread.p_protocol_params;
	p_3c_params = ((CMainFrame*)AfxGetMainWnd())->m_pass_to_thread.p_protocol_params_3c;//��3C����ָ�븳ֵ
	p_channel_params = ((CMainFrame*)AfxGetMainWnd())->m_pass_to_thread.p_protocol_params_channel;//���ŵ�����ָ�븳ֵ

	CRect rc;//ʹ�ÿͻ�����С�����Ա��ؼ����ж�λ
	GetClientRect(&rc);
	//rc.bottom += 20;
	rc.left += 10;
	//rc.right += 10;
	rc.top += 45;
	m_main_property.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,rc,this,PROPERTYGRID_PROTOCOL_CONFIG);
	m_main_property.EnableHeaderCtrl(FALSE,"����","ֵ");
	m_main_property.EnableDescriptionArea();
	m_main_property.SetDescriptionRows(5);
	m_main_property.SetVSDotNetLook();
	m_main_property.MarkModifiedProperties(TRUE);
	m_main_property.SetAlphabeticMode(false); 
	m_main_property.SetShowDragContext();

	/************************************************************************/
	/* ע:Ҫ��������ѡ���ѡ��ܱ༭���Լ��ٺ����ж�ѡ����ȷ���Ĺ���    */
	/************************************************************************/
	//15.3c��ӵĽ���
	//pGroup_carrier
	pGroup_carrier = new CMFCPropertyGridProperty("�ز�����");
	pCarrier_sig_mode = new CMFCPropertyGridProperty("�ź�ģʽ", "SC", "ѡ���������źŵ�ģʽ:SC-PHY/HSI-PHY/AV-PHY", PROTO_SIG_MODE_3C);
	pCarrier_sig_mode->AddOption(_T("SC"));  
	pCarrier_sig_mode->AddOption(_T("HSI")); 
	pCarrier_sig_mode->AddOption(_T("AV"));
	pCarrier_sig_mode->AllowEdit(FALSE);
	pGroup_carrier->AddSubItem(pCarrier_sig_mode);
	CMFCPropertyGridProperty* pCarrier_frames = new CMFCPropertyGridProperty(_T("�ź�֡��"),_T("1"),_T("�������������źŵ�֡��"));
	pGroup_carrier->AddSubItem(pCarrier_frames);
	pGroup_carrier->AllowEdit(FALSE);
// 	pCarrier_data_length = new CMFCPropertyGridProperty(_T("���ݳ���"),_T("123456"),_T("�������������ź����ݳ���"), PROTO_SIG_GENLENGTH_3C);
// 	pGroup_carrier->AddSubItem(pCarrier_data_length);
	CMFCPropertyGridProperty* pCarrier_freq_offset = new CMFCPropertyGridProperty(_T("Ƶ��ƫ��"),_T("10000.0000Hz"),_T("��ʾ��ǰƵ��ƫ��ֵ"));
	pCarrier_freq_offset->AllowEdit(FALSE);
	pGroup_carrier->AddSubItem(pCarrier_freq_offset);
	CMFCPropertyGridProperty* pCarrier_relative_power = new CMFCPropertyGridProperty(_T("��Թ���"),_T("00.000dB"),_T("��ʾ��ǰģʽ����Թ���"));
	pCarrier_relative_power->AllowEdit(FALSE);
	pGroup_carrier->AddSubItem(pCarrier_relative_power);
	CMFCPropertyGridProperty* pCarrier_trans_space = new CMFCPropertyGridProperty(_T("����������"),_T("0.5��s"),_T("��������������"));
	pCarrier_trans_space->AddOption(_T("0.2��s"));
	pCarrier_trans_space->AddOption(_T("0.5��s"));
	pCarrier_trans_space->AddOption(_T("2.0��s"));
	pCarrier_trans_space->AllowEdit(FALSE);
	pGroup_carrier->AddSubItem(pCarrier_trans_space);
	CMFCPropertyGridProperty* pCarrier_trans_time = new CMFCPropertyGridProperty(_T("��/��ת��ʱ��"),_T("2.5��s"),_T("������/��ת��ʱ��"));
	pCarrier_trans_time->AddOption(_T("0.2��s"));
	pCarrier_trans_time->AddOption(_T("2.0��s"));
	pCarrier_trans_time->AddOption(_T("2.5��s"));
	pCarrier_trans_time->AllowEdit(FALSE);
	pGroup_carrier->AddSubItem(pCarrier_trans_time);
	CMFCPropertyGridProperty* pCarrier_switch_time = new CMFCPropertyGridProperty(_T("�ŵ��л�ʱ��"),_T("100��s"),_T("��ʾ��ǰģʽ����Թ���"));
	pCarrier_switch_time->AllowEdit(FALSE);
	pGroup_carrier->AddSubItem(pCarrier_switch_time);

	//pGroup_control
	pGroup_control = new CMFCPropertyGridProperty("������Ϣ");
	CMFCPropertyGridProperty* pControl_preamble = new CMFCPropertyGridProperty(_T("ǰ������"),_T("short"),_T("ѡ�������źŵ�ǰ�����ͣ�short/long"));
	pControl_preamble->AddOption(_T("short"));
	pControl_preamble->AddOption(_T("long"));
	pControl_preamble->AllowEdit(FALSE);
	pGroup_control->AddSubItem(pControl_preamble);
	CMFCPropertyGridProperty* pControl_aggregation = new CMFCPropertyGridProperty(_T("Aggregation"),_T("ON"),_T("ѡ�������źŵ�Aggregation��ON/OFF"));
	pControl_aggregation->AddOption(_T("ON"));
	pControl_aggregation->AddOption(_T("OFF"));
	pControl_aggregation->AllowEdit(FALSE);
	pGroup_control->AddSubItem(pControl_aggregation);
	CMFCPropertyGridPropertyButton *pControl_mac_config = new CMFCPropertyGridPropertyButton("MAC��ϸ����","","��ϸ����MAC��Ϣ");
	pGroup_control->AddSubItem(pControl_mac_config);

	//pGroup_modulation
	pGroup_modulation = new CMFCPropertyGridProperty("���Ʊ���");
	pModulation_mcs = new CMFCPropertyGridProperty(_T("MCS"),_T("0"),_T("ѡ�������źŵ�MCS"), PROTO_SIG_MCS_3C);
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
	pModulation_mode = new CMFCPropertyGridProperty(_T("���Ʒ�ʽ"),_T("��/2 BPSK"),_T("��ʾ��ǰģʽ�µĵ��Ʒ�ʽ"));
	pModulation_mode->AddOption(_T("��/2 BPSK"));
	pModulation_mode->AddOption(_T("��/2 QPSK"));
	pModulation_mode->AddOption(_T("��/2 8-PSK"));
	pModulation_mode->AddOption(_T("��/2 16-QAM"));
	pModulation_mode->AllowEdit(FALSE);
	pGroup_modulation->AddSubItem(pModulation_mode);
	pModulation_fec = new CMFCPropertyGridProperty(_T("ǰ�����"),_T("RS(255,239)"),_T("��ʾ��ǰģʽ�µ�ǰ����뷽ʽ"));
	pModulation_fec->AddOption(_T("RS(255,239)"));
	pModulation_fec->AddOption(_T("LDPC(672,336)"));
	pModulation_fec->AddOption(_T("LDPC(672,504)"));
	pModulation_fec->AddOption(_T("LDPC(672,588)"));
	pModulation_fec->AllowEdit(FALSE);
	pGroup_modulation->AddSubItem(pModulation_fec);

	//pGroup_payload
	pGroup_payload = new CMFCPropertyGridProperty("�غ�����");
	CMFCPropertyGridProperty* pPayload_rate = new CMFCPropertyGridProperty(_T("��������"),_T("1234.00Mbps"),_T("��ʾ��ǰģʽ����������"));
	pPayload_rate->AllowEdit(FALSE);
	pGroup_payload->AddSubItem(pPayload_rate);
	pPayload_data_source = new CMFCPropertyGridProperty(_T("����Դ"),_T("PN9"),_T("ѡ������Դ���ͣ�PN9/PN15/ALL0/���ļ���ȡ"), PROTO_SIG_DATA_SOURCE_3C);
	pPayload_data_source->AddOption(_T("PN9"));
	pPayload_data_source->AddOption(_T("PN15"));
	pPayload_data_source->AddOption(_T("ALL0"));
	pPayload_data_source->AddOption(_T("���ļ���ȡ"));
	pPayload_data_source->AllowEdit(FALSE);
	pGroup_payload->AddSubItem(pPayload_data_source);
	pPayload_length = new CMFCPropertyGridProperty(_T("���س���"),_T("30592"),_T("���ø��س���"), PROTO_SIG_PAYLOADLENGTH_3C);
	pGroup_payload->AddSubItem(pPayload_length);
	pPayload_trans_rate = new CMFCPropertyGridProperty(_T("��������ģʽ"),_T("HRP"),_T("ѡ��������ģʽ��HRP/LRP"), PROTO_SIG_TRANS_RATE_TYPE);
	pPayload_trans_rate->AddOption(_T("HRP"));
	pPayload_trans_rate->AddOption(_T("LRP"));
	pPayload_trans_rate->AllowEdit(FALSE);
	pPayload_trans_rate->Show(FALSE);
	pGroup_payload->AddSubItem(pPayload_trans_rate);
	pPayload_ssid = new CMFCPropertyGridProperty(_T("SSID"),_T("0000"),_T("������������ʼ����"), PROTO_SIG_SSID_3C);
	pGroup_payload->AddSubItem(pPayload_ssid);
	pPayload_spreader = new CMFCPropertyGridProperty(_T("��Ƶ����"),_T("64"),_T("ѡ��ǰģʽ����Ƶ����"), PROTO_SIG_SPREADER_3C);
	pPayload_spreader->AddOption(_T("1"));
	pPayload_spreader->AddOption(_T("2"));
	pPayload_spreader->AddOption(_T("4"));
	pPayload_spreader->AddOption(_T("64"));
	pPayload_spreader->AllowEdit(FALSE);
	pGroup_payload->AddSubItem(pPayload_spreader);
	CMFCPropertyGridProperty* pPayload_subblock = new CMFCPropertyGridProperty(_T("�����ӿ�ģʽ"),_T("0"),_T("ѡ��ǰģʽ�����ӿ�ָ�ģʽ"));
	pPayload_subblock->AddOption(_T("0"));
	pPayload_subblock->AddOption(_T("8"));
	pPayload_subblock->AddOption(_T("64"));
	pPayload_subblock->AllowEdit(FALSE);
	pGroup_payload->AddSubItem(pPayload_subblock);
	pPayload_pces = new CMFCPropertyGridProperty(_T("�ŵ����Ʋ���"),_T("ON"),_T("ѡ���Ƿ�����ŵ����ƣ�ON/OFF"));
	pPayload_pces->AddOption(_T("ON"));
	pPayload_pces->AddOption(_T("OFF"));
	pPayload_pces->AllowEdit(FALSE);
	pGroup_payload->AddSubItem(pPayload_pces);
	pPayload_map_type = new CMFCPropertyGridProperty(_T("ӳ������"),_T("0"),_T("ѡ��ǰģʽӳ�����ͣ�0-����ģʽ��1-����ģʽ"));
	pPayload_map_type->AddOption(_T("0"));
	pPayload_map_type->AddOption(_T("1"));
	pPayload_map_type->AllowEdit(FALSE);
	pPayload_map_type->Enable(FALSE);
	pGroup_payload->AddSubItem(pPayload_map_type);
	pPayload_uep_eep = new CMFCPropertyGridProperty(_T("���������"),_T("EEP"),_T("ѡ��ǰģʽ��������ͣ�EEP/UEP"));
	pPayload_uep_eep->AddOption(_T("EEP"));
	pPayload_uep_eep->AddOption(_T("UEP"));
	pPayload_uep_eep->AllowEdit(FALSE);
	pPayload_uep_eep->Enable(FALSE);
	pGroup_payload->AddSubItem(pPayload_uep_eep);
	pPayload_interver = new CMFCPropertyGridProperty(_T("��֯���"),_T("2"),_T("ѡ��ǰģʽ��֯��ȣ�2/4"));
	pPayload_interver->AddOption(_T("2"));
	pPayload_interver->AddOption(_T("4"));
	pPayload_interver->AllowEdit(FALSE);
	pPayload_interver->Enable(FALSE);
	pGroup_payload->AddSubItem(pPayload_interver);
	pPayload_tone_inter = new CMFCPropertyGridProperty(_T("�ز���֯"),_T("OFF"),_T("ѡ���Ƿ����ز���֯"), PROTO_SIG_TONEINTER_3C);
	pPayload_tone_inter->AddOption(_T("ON"));
	pPayload_tone_inter->AddOption(_T("OFF"));
	pPayload_tone_inter->AllowEdit(FALSE);
	pPayload_tone_inter->Enable(FALSE);
	pGroup_payload->AddSubItem(pPayload_tone_inter);

	//pGroup_spectrum
	pGroup_spectrum = new CMFCPropertyGridProperty("Ƶ�׿���");
	CMFCPropertyGridProperty* pSpectrum_filter = new CMFCPropertyGridProperty(_T("�Ƿ�ʹ���˲���"),_T("ON"),_T("�����Ƿ�ʹ���˲�����ON/OFF"));
	pSpectrum_filter->AddOption(_T("ON"));
	pSpectrum_filter->AddOption(_T("OFF"));
	pSpectrum_filter->AllowEdit(FALSE);
	pGroup_spectrum->AddSubItem(pSpectrum_filter);
	CMFCPropertyGridProperty* pSpectrum_win_length = new CMFCPropertyGridProperty(_T("���ڳ���"),_T("1024"),_T("���ô����������������䳤�Ȳ��ܳ���һ��OFDM�źű�������ĳ���"));
	pGroup_spectrum->AddSubItem(pSpectrum_win_length);

	//pGroup_channel
	pGroup_channel = new CMFCPropertyGridProperty("�ŵ�");
	pChannel_switch = new CMFCPropertyGridProperty(_T("�ŵ�ѡ��"),_T("OFF"),_T("ѡ���ŵ���ON/OFF"),PROTO_CHAN_SWITCH);
	pChannel_switch->AddOption(_T("ON"));
	pChannel_switch->AddOption(_T("OFF"));
	pChannel_switch->AllowEdit(FALSE);
	pGroup_channel->AddSubItem(pChannel_switch);
	pChannel_type = new CMFCPropertyGridProperty(_T("�ŵ�����"),_T("11"),_T("�����ŵ�����"),PROTO_CHAN_TYPE);
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
	pChannel_sys_bw = new CMFCPropertyGridProperty(_T("ϵͳ����"),_T("2124.25MHz"),_T("����ϵͳ����"),PROTO_CHAN_SYSBW);
	pGroup_channel->AddSubItem(pChannel_sys_bw);
	CMFCPropertyGridProperty* pChannel_noise_bw = new CMFCPropertyGridProperty(_T("��������"),_T("12456Hz"),_T("������������"));
	pGroup_channel->AddSubItem(pChannel_noise_bw);
	CMFCPropertyGridProperty* pChannel_nsys_ratio = new CMFCPropertyGridProperty(_T("��С����/ϵͳ����"),_T("12456Hz"),_T("������С����/ϵͳ����"));
	pGroup_channel->AddSubItem(pChannel_nsys_ratio);
	CMFCPropertyGridProperty* pChannel_snr = new CMFCPropertyGridProperty(_T("Eb/NO"),_T("00dB"),_T("���������"));
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
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CTabProtocolConfig::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
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
	CW* p_wave = &(((CGraphWAVE*)(((CMainFrame*)AfxGetMainWnd())->m_rightSplitter.GetPane(1,0)))->m_wave);//��ȡ�ı����
	CTabCarrier &T_Carri = ((CTabParent*)(((CMainFrame*)AfxGetMainWnd())->m_mainSplitter.GetPane(0,0)))->m_tabCarrier;//��ҳ����
	str = pProp->GetValue();
	int id_changed = pProp->GetData();//��ȡ��ǰֵ�����仯�����Ե�ID

	/*******************153c�����������*************************/
	SetFocus();
	switch (id_changed)
	{
	case PROTO_SIG_MODE_3C:
		if (str.Compare("SC") == 0)
		{
			p_3c_params->set_signal_mode(SC);//���ò����������еĲ�������ʼ��
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
			T_Carri.pPropS1->SetValue("SC");//��������
			pPayload_length->SetValue("30592");
			pModulation_mode->SetValue("��/2 BPSK");
			pModulation_mode->RemoveAllOptions();
			pModulation_mode->AddOption(_T("��/2 BPSK"));
			pModulation_mode->AddOption(_T("��/2 QPSK"));
			pModulation_mode->AddOption(_T("��/2 8-PSK"));
			pModulation_mode->AddOption(_T("��/2 16-QAM"));
			pModulation_mode->AllowEdit(FALSE);
			pPayload_map_type->Enable(FALSE);
			pPayload_uep_eep->Enable(FALSE);
			pPayload_interver->Enable(FALSE);
			pPayload_tone_inter->Enable(FALSE);
			pPayload_trans_rate->Show(FALSE);
		}
		else if (str.Compare("HSI") == 0)
		{
			p_3c_params->set_signal_mode(HSI);//���ò����������еĲ�������ʼ��
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
			p_3c_params->set_signal_mode(AV);//���ò����������еĲ�������ʼ��
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
			MessageBox("��֧�ֵ��ź�ģʽ��",NULL,MB_ICONERROR);
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

	case PROTO_SIG_MCS_3C://����MCS
		{
			int mcs_temp = atoi(str.GetBuffer());
			if (p_3c_params->Sig_mode == SC)
			{
				{
					switch (mcs_temp)
					{
					case 0:
						p_3c_params->SC_p.MCS = 0;//����MCS
						p_3c_params->SC_p.sp = 64;//������Ƶ����
						p_3c_params->SC_p.modtype = 1;//���ĵ��Ʒ�ʽ
						p_3c_params->SC_p.FECtype = 0;//����ǰ����뷽ʽ
						p_3c_params->SC_p.subtype = 0;//MCS0�̶�Ϊ�����ӿ�
						pModulation_mode->SetValue("��/2 BPSK");
						pModulation_fec->SetValue("RS(255,239)");
						pPayload_spreader->SetValue("0");
						break;
					case 1:
						p_3c_params->SC_p.MCS = 1;//����MCS
						p_3c_params->SC_p.sp = 4;//������Ƶ����
						p_3c_params->SC_p.modtype = 1;//���ĵ��Ʒ�ʽ
						p_3c_params->SC_p.FECtype = 0;//����ǰ����뷽ʽ
						//p_3c_params->SC_p.L_mb = 239 * 16;
						pModulation_mode->SetValue("��/2 BPSK");
						pModulation_fec->SetValue("RS(255,239)");
						pPayload_spreader->SetValue("4");
						break;
					case 2:
						p_3c_params->SC_p.MCS = 2;//����MCS
						p_3c_params->SC_p.sp = 2;//������Ƶ����
						p_3c_params->SC_p.modtype = 1;//���ĵ��Ʒ�ʽ
						p_3c_params->SC_p.FECtype = 0;//����ǰ����뷽ʽ
						//p_3c_params->SC_p.L_mb = 239 * 32;
						pModulation_mode->SetValue("��/2 BPSK");
						pModulation_fec->SetValue("RS(255,239)");
						pPayload_spreader->SetValue("2");
						break;
					case 3:
						p_3c_params->SC_p.MCS = 3;//����MCS
						p_3c_params->SC_p.sp = 1;//������Ƶ����
						p_3c_params->SC_p.modtype = 1;//���ĵ��Ʒ�ʽ
						p_3c_params->SC_p.FECtype = 0;//����ǰ����뷽ʽ
						//p_3c_params->SC_p.L_mb = 239 * 64;
						pModulation_mode->SetValue("��/2 BPSK");
						pModulation_fec->SetValue("RS(255,239)");
						pPayload_spreader->SetValue("1");
						break;
					case 4:
						p_3c_params->SC_p.MCS = 4;//����MCS
						p_3c_params->SC_p.sp = 1;//������Ƶ����
						p_3c_params->SC_p.modtype = 1;//���ĵ��Ʒ�ʽ
						p_3c_params->SC_p.FECtype = 1;//����ǰ����뷽ʽ
						p_3c_params->SC_p.FECrate = 2;//����ǰ���������
						//p_3c_params->SC_p.L_mb = 504 * 32;
						pModulation_mode->SetValue("��/2 BPSK");
						pModulation_fec->SetValue("LDPC(672,504)");
						pPayload_spreader->SetValue("1");
						break;
					case 5:
						p_3c_params->SC_p.MCS = 5;//����MCS
						p_3c_params->SC_p.sp = 2;//������Ƶ����
						p_3c_params->SC_p.modtype = 1;//���ĵ��Ʒ�ʽ
						p_3c_params->SC_p.FECtype = 1;//����ǰ����뷽ʽ
						p_3c_params->SC_p.FECrate = 0;//����ǰ���������
						//p_3c_params->SC_p.L_mb = 336 * 16;
						pModulation_mode->SetValue("��/2 BPSK");
						pModulation_fec->SetValue("LDPC(672,336)");
						pPayload_spreader->SetValue("2");
						break;
					case 6:
						p_3c_params->SC_p.MCS = 6;//����MCS
						p_3c_params->SC_p.sp = 1;//������Ƶ����
						p_3c_params->SC_p.modtype = 1;//���ĵ��Ʒ�ʽ
						p_3c_params->SC_p.FECtype = 1;//����ǰ����뷽ʽ
						p_3c_params->SC_p.FECrate = 0;//����ǰ���������
						//p_3c_params->SC_p.L_mb = 336 * 32;
						pModulation_mode->SetValue("��/2 BPSK");
						pModulation_fec->SetValue("LDPC(672,336)");
						pPayload_spreader->SetValue("1");
						break;
					case 7:
						p_3c_params->SC_p.MCS = 7;//����MCS
						p_3c_params->SC_p.sp = 1;//������Ƶ����
						p_3c_params->SC_p.modtype = 2;//���ĵ��Ʒ�ʽ
						p_3c_params->SC_p.FECtype = 1;//����ǰ����뷽ʽ
						p_3c_params->SC_p.FECrate = 0;//����ǰ���������
						//p_3c_params->SC_p.L_mb = 336 * 32;
						pModulation_mode->SetValue("��/2 QPSK");
						pModulation_fec->SetValue("LDPC(672,336)");
						pPayload_spreader->SetValue("1");
						break;
					case 8:
						p_3c_params->SC_p.MCS = 8;//����MCS
						p_3c_params->SC_p.sp = 1;//������Ƶ����
						p_3c_params->SC_p.modtype = 2;//���ĵ��Ʒ�ʽ
						p_3c_params->SC_p.FECtype = 1;//����ǰ����뷽ʽ
						p_3c_params->SC_p.FECrate = 2;//����ǰ���������
						//p_3c_params->SC_p.L_mb = 504 * 32;
						pModulation_mode->SetValue("��/2 QPSK");
						pModulation_fec->SetValue("LDPC(672,504)");
						pPayload_spreader->SetValue("1");
						break;
					case 9:
						p_3c_params->SC_p.MCS = 9;//����MCS
						p_3c_params->SC_p.sp = 1;//������Ƶ����
						p_3c_params->SC_p.modtype = 2;//���ĵ��Ʒ�ʽ
						p_3c_params->SC_p.FECtype = 1;//����ǰ����뷽ʽ
						p_3c_params->SC_p.FECrate = 3;//����ǰ���������
						//p_3c_params->SC_p.L_mb = 588 * 32;
						pModulation_mode->SetValue("��/2 QPSK");
						pModulation_fec->SetValue("LDPC(672,588)");
						pPayload_spreader->SetValue("1");
						break;
					case 10://LDPC��������1440/1344,��û��
						p_3c_params->SC_p.MCS = 10;//����MCS
						p_3c_params->SC_p.sp = 1;//������Ƶ����
						p_3c_params->SC_p.modtype = 2;//���ĵ��Ʒ�ʽ
						p_3c_params->SC_p.FECtype = 1;//����ǰ����뷽ʽ
						p_3c_params->SC_p.FECrate = 3;//����ǰ���������
						//p_3c_params->SC_p.L_mb = 588 * 32;
						pModulation_mode->SetValue("��/2 QPSK");
						pModulation_fec->SetValue("LDPC(1440,1344)");
						pPayload_spreader->SetValue("1");
						break;
					case 11:
						p_3c_params->SC_p.MCS = 11;//����MCS
						p_3c_params->SC_p.sp = 1;//������Ƶ����
						p_3c_params->SC_p.modtype = 2;//���ĵ��Ʒ�ʽ
						p_3c_params->SC_p.FECtype = 0;//����ǰ����뷽ʽ
						p_3c_params->SC_p.FECrate = 3;//����ǰ���������
						//p_3c_params->SC_p.L_mb = 239 * 64;
						pModulation_mode->SetValue("��/2 QPSK");
						pModulation_fec->SetValue("RS(255,239)");
						pPayload_spreader->SetValue("1");
						break;
					case 12:
						p_3c_params->SC_p.MCS = 12;//����MCS
						p_3c_params->SC_p.sp = 1;//������Ƶ����
						p_3c_params->SC_p.modtype = 3;//���ĵ��Ʒ�ʽ
						p_3c_params->SC_p.FECtype = 1;//����ǰ����뷽ʽ
						p_3c_params->SC_p.FECrate = 2;//����ǰ���������
						//p_3c_params->SC_p.L_mb = 504 * 24;
						pModulation_mode->SetValue("��/2 8PSK");
						pModulation_fec->SetValue("LDPC(672,504)");
						pPayload_spreader->SetValue("1");
						break;
					case 13:
						p_3c_params->SC_p.MCS = 13;//����MCS
						p_3c_params->SC_p.sp = 1;//������Ƶ����
						p_3c_params->SC_p.modtype = 4;//���ĵ��Ʒ�ʽ
						p_3c_params->SC_p.FECtype = 1;//����ǰ����뷽ʽ
						p_3c_params->SC_p.FECrate = 2;//����ǰ���������
						//p_3c_params->SC_p.L_mb = 504 * 32;//macbody����
						pModulation_mode->SetValue("��/2 16-QAM");
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
						p_3c_params->HSI_p.MCS = 0;//����MCS
						p_3c_params->HSI_p.sp = 48;//������Ƶ����
						p_3c_params->HSI_p.modtype = 2;//���ĵ��Ʒ�ʽ
						p_3c_params->HSI_p.UEP = 0;//����UEP��ʽ
						p_3c_params->HSI_p.FECrate = 0;//����ǰ���������
						//p_3c_params->HSI_p.L_mb = 336 * 4;//macbody����
						pModulation_mode->SetValue("QPSK");
						pModulation_fec->SetValue("LDPC(672,336)");
						pPayload_spreader->SetValue("48");
						pPayload_uep_eep->SetValue("EEP");
						break;
					case 1:
						p_3c_params->HSI_p.MCS = 1;//����MCS
						p_3c_params->HSI_p.sp = 1;//������Ƶ����
						p_3c_params->HSI_p.modtype = 2;//���ĵ��Ʒ�ʽ
						p_3c_params->HSI_p.UEP = 0;//����UEP��ʽ
						p_3c_params->HSI_p.FECrate = 0;//����ǰ���������
						//p_3c_params->HSI_p.L_mb = 336 * 32;//macbody����
						pModulation_mode->SetValue("QPSK");
						pModulation_fec->SetValue("LDPC(672,336)");
						pPayload_spreader->SetValue("1");
						pPayload_uep_eep->SetValue("EEP");
						break;
					case 2:
						p_3c_params->HSI_p.MCS = 2;//����MCS
						p_3c_params->HSI_p.sp = 1;//������Ƶ����
						p_3c_params->HSI_p.modtype = 2;//���ĵ��Ʒ�ʽ
						p_3c_params->HSI_p.UEP = 0;//����UEP��ʽ
						p_3c_params->HSI_p.FECrate = 2;//����ǰ���������
						//p_3c_params->HSI_p.L_mb = 504 * 32;//macbody����
						pModulation_mode->SetValue("QPSK");
						pModulation_fec->SetValue("LDPC(672,504)");
						pPayload_spreader->SetValue("1");
						pPayload_uep_eep->SetValue("EEP");
						break;
					case 3:
						p_3c_params->HSI_p.MCS = 3;//����MCS
						p_3c_params->HSI_p.sp = 1;//������Ƶ����
						p_3c_params->HSI_p.modtype = 2;//���ĵ��Ʒ�ʽ
						p_3c_params->HSI_p.UEP = 0;//����UEP��ʽ
						p_3c_params->HSI_p.FECrate = 3;//����ǰ���������
						//p_3c_params->HSI_p.L_mb = 588 * 16;//macbody����
						pModulation_mode->SetValue("QPSK");
						pModulation_fec->SetValue("LDPC(672,588)");
						pPayload_spreader->SetValue("1");
						pPayload_uep_eep->SetValue("EEP");
						break;
					case 4:
						p_3c_params->HSI_p.MCS = 4;//����MCS
						p_3c_params->HSI_p.sp = 1;//������Ƶ����
						p_3c_params->HSI_p.modtype = 4;//���ĵ��Ʒ�ʽ
						p_3c_params->HSI_p.UEP = 0;//����UEP��ʽ
						p_3c_params->HSI_p.FECrate = 0;//����ǰ���������
						//p_3c_params->HSI_p.L_mb = 336 * 64;//macbody����
						pModulation_mode->SetValue("16-QAM");
						pModulation_fec->SetValue("LDPC(672,336)");
						pPayload_spreader->SetValue("1");
						pPayload_uep_eep->SetValue("EEP");
						break;
					case 5:
						p_3c_params->HSI_p.MCS = 5;//����MCS
						p_3c_params->HSI_p.sp = 1;//������Ƶ����
						p_3c_params->HSI_p.modtype = 4;//���ĵ��Ʒ�ʽ
						p_3c_params->HSI_p.UEP = 0;//����UEP��ʽ
						p_3c_params->HSI_p.FECrate = 2;//����ǰ���������
						//p_3c_params->HSI_p.L_mb = 504 * 64;//macbody����
						pModulation_mode->SetValue("16-QAM");
						pModulation_fec->SetValue("LDPC(672,504)");
						pPayload_spreader->SetValue("1");
						pPayload_uep_eep->SetValue("EEP");
						break;
					case 6:
						p_3c_params->HSI_p.MCS = 6;//����MCS
						p_3c_params->HSI_p.sp = 1;//������Ƶ����
						p_3c_params->HSI_p.modtype = 4;//���ĵ��Ʒ�ʽ
						p_3c_params->HSI_p.UEP = 0;//����UEP��ʽ
						p_3c_params->HSI_p.FECrate = 3;//����ǰ���������
						//p_3c_params->HSI_p.L_mb = 588 * 64;//macbody����
						pModulation_mode->SetValue("16-QAM");
						pModulation_fec->SetValue("LDPC(672,588)");
						pPayload_spreader->SetValue("1");
						pPayload_uep_eep->SetValue("EEP");
						break;
					case 7:
						p_3c_params->HSI_p.MCS = 7;//����MCS
						p_3c_params->HSI_p.sp = 1;//������Ƶ����
						p_3c_params->HSI_p.modtype = 6;//���ĵ��Ʒ�ʽ
						p_3c_params->HSI_p.UEP = 0;//����UEP��ʽ
						p_3c_params->HSI_p.FECrate = 1;//����ǰ���������
						//p_3c_params->HSI_p.L_mb = 420 * 96;//macbody����
						pModulation_mode->SetValue("64-QAM");
						pModulation_fec->SetValue("LDPC(672,420)");
						pPayload_spreader->SetValue("1");
						pPayload_uep_eep->SetValue("EEP");
						break;
					case 8:
						p_3c_params->HSI_p.MCS = 8;//����MCS
						p_3c_params->HSI_p.sp = 1;//������Ƶ����
						p_3c_params->HSI_p.modtype = 2;//���ĵ��Ʒ�ʽ
						p_3c_params->HSI_p.UEP = 1;//����UEP��ʽ
						p_3c_params->HSI_p.FECrate = 0;//����ǰ���������
						//p_3c_params->HSI_p.L_mb = 168 * 96;//macbody����
						pModulation_mode->SetValue("QPSK");
						pModulation_fec->SetValue("LDPC(672,336),LDPC(672,504)");
						pPayload_spreader->SetValue("1");
						pPayload_uep_eep->SetValue("UEP");
						break;
					case 9:
						p_3c_params->HSI_p.MCS = 9;//����MCS
						p_3c_params->HSI_p.sp = 1;//������Ƶ����
						p_3c_params->HSI_p.modtype = 2;//���ĵ��Ʒ�ʽ
						p_3c_params->HSI_p.UEP = 1;//����UEP��ʽ
						p_3c_params->HSI_p.FECrate = 2;//����ǰ���������
						//p_3c_params->HSI_p.L_mb = 84 * 42 * 8;//macbody����
						pModulation_mode->SetValue("QPSK");
						pModulation_fec->SetValue("LDPC(672,504),LDPC(672,588)");
						pPayload_spreader->SetValue("1");
						pPayload_uep_eep->SetValue("UEP");
						break;
					case 10:
						p_3c_params->HSI_p.MCS = 9;//����MCS
						p_3c_params->HSI_p.sp = 1;//������Ƶ����
						p_3c_params->HSI_p.modtype = 4;//���ĵ��Ʒ�ʽ
						p_3c_params->HSI_p.UEP = 1;//����UEP��ʽ
						p_3c_params->HSI_p.FECrate = 0;//����ǰ���������
						//p_3c_params->HSI_p.L_mb = 168 * 96;//macbody����
						pModulation_mode->SetValue("16-QAM");
						pModulation_fec->SetValue("LDPC(672,336),LDPC(672,504)");
						pPayload_spreader->SetValue("1");
						pPayload_uep_eep->SetValue("UEP");
						break;
					case 11:
						p_3c_params->HSI_p.MCS = 9;//����MCS
						p_3c_params->HSI_p.sp = 1;//������Ƶ����
						p_3c_params->HSI_p.modtype = 4;//���ĵ��Ʒ�ʽ
						p_3c_params->HSI_p.UEP = 1;//����UEP��ʽ
						p_3c_params->HSI_p.FECrate = 2;//����ǰ���������
						//p_3c_params->HSI_p.L_mb = 84 * 42 * 16;//macbody����
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
							p_3c_params->AV_p.MCS = 0;//����MCS
							p_3c_params->AV_p.modtype = 2;//���ĵ��Ʒ�ʽ
							p_3c_params->AV_p.UEP = 0;//����UEP��ʽ
							p_3c_params->AV_p.rate_up = 0;//������֧·��������
							p_3c_params->AV_p.rate_low = 0;//������֧·��������
							//p_3c_params->AV_p.L_mb = 216 * 32;//macbody����
							pModulation_mode->SetValue("QPSK");
							pModulation_fec->SetValue("RS(224,216)");
							pPayload_uep_eep->SetValue("EEP");
							break;
						case 1:
							p_3c_params->AV_p.MCS = 1;//����MCS
							p_3c_params->AV_p.modtype = 2;//���ĵ��Ʒ�ʽ
							p_3c_params->AV_p.UEP = 0;//����UEP��ʽ
							p_3c_params->AV_p.rate_up = 3;//������֧·��������
							p_3c_params->AV_p.rate_low = 3;//������֧·��������
							//p_3c_params->AV_p.L_mb = 216 * 32;//macbody����
							pModulation_mode->SetValue("QPSK");
							pModulation_fec->SetValue("RS(224,216)");
							pPayload_uep_eep->SetValue("EEP");
							break;
						case 2:
							p_3c_params->AV_p.MCS = 2;//����MCS
							p_3c_params->AV_p.modtype = 4;//���ĵ��Ʒ�ʽ
							p_3c_params->AV_p.UEP = 0;//����UEP��ʽ
							p_3c_params->AV_p.rate_up = 3;//������֧·��������
							p_3c_params->AV_p.rate_low = 3;//������֧·��������
							//p_3c_params->AV_p.L_mb = 216 * 32;//macbody����
							pModulation_mode->SetValue("16-QAM");
							pModulation_fec->SetValue("RS(224,216)");
							pPayload_uep_eep->SetValue("EEP");
							break;
						case 3:
							p_3c_params->AV_p.MCS = 3;//����MCS
							p_3c_params->AV_p.modtype = 2;//���ĵ��Ʒ�ʽ
							p_3c_params->AV_p.UEP = 1;//����UEP��ʽ
							p_3c_params->AV_p.rate_up = 2;//������֧·��������
							p_3c_params->AV_p.rate_low = 4;//������֧·��������
							//p_3c_params->AV_p.L_mb = 216 * 32;//macbody����
							pModulation_mode->SetValue("QPSK");
							pModulation_fec->SetValue("RS(224,216)");
							pPayload_uep_eep->SetValue("UEP");
							break;
						case 4:
							p_3c_params->AV_p.MCS = 4;//����MCS
							p_3c_params->AV_p.modtype = 4;//���ĵ��Ʒ�ʽ
							p_3c_params->AV_p.UEP = 1;//����UEP��ʽ
							p_3c_params->AV_p.rate_up = 2;//������֧·��������
							p_3c_params->AV_p.rate_low = 4;//������֧·��������
							//p_3c_params->AV_p.L_mb = 216 * 32;//macbody����
							pModulation_mode->SetValue("16-QAM");
							pModulation_fec->SetValue("RS(224,216)");
							pPayload_uep_eep->SetValue("UEP");
							break;
						case 5:
							p_3c_params->AV_p.MCS = 5;//����MCS
							p_3c_params->AV_p.modtype = 2;//���ĵ��Ʒ�ʽ
							p_3c_params->AV_p.UEP = 2;//����UEP��ʽ
							p_3c_params->AV_p.rate_up = 0;//������֧·��������
							p_3c_params->AV_p.rate_low = 0;//������֧·��������
							//p_3c_params->AV_p.L_mb = 216 * 32;//macbody����
							pModulation_mode->SetValue("QPSK");
							pModulation_fec->SetValue("RS(224,216)");
							pPayload_uep_eep->SetValue("MSB-only");
							break;
						case 6:
							p_3c_params->AV_p.MCS = 0;//����MCS
							p_3c_params->AV_p.modtype = 2;//���ĵ��Ʒ�ʽ
							p_3c_params->AV_p.UEP = 2;//����UEP��ʽ
							p_3c_params->AV_p.rate_up = 3;//������֧·��������
							p_3c_params->AV_p.rate_low = 3;//������֧·��������
							//p_3c_params->AV_p.L_mb = 216 * 32;//macbody����
							pModulation_mode->SetValue("QPSK");
							pModulation_fec->SetValue("RS(224,216)");
							pPayload_uep_eep->SetValue("MSB-only");
							break;
						case 7:
							p_3c_params->AV_p.MCS = 7;//����MCS
							p_3c_params->AV_p.modtype = 1;//���ĵ��Ʒ�ʽ
							p_3c_params->AV_p.UEP = 2;//����UEP��ʽ
							p_3c_params->AV_p.rate_up = 3;//������֧·��������
							p_3c_params->AV_p.rate_low = 3;//������֧·��������
							//p_3c_params->AV_p.L_mb = 216 * 32;//macbody����
							pModulation_mode->SetValue("BPSK");
							pModulation_fec->Enable(FALSE);
							pPayload_uep_eep->Enable(FALSE);
							break;
						case 8:
							p_3c_params->AV_p.MCS = 8;//����MCS
							p_3c_params->AV_p.modtype = 1;//���ĵ��Ʒ�ʽ
							p_3c_params->AV_p.UEP = 2;//����UEP��ʽ
							p_3c_params->AV_p.rate_up = 3;//������֧·��������
							p_3c_params->AV_p.rate_low = 3;//������֧·��������
							//p_3c_params->AV_p.L_mb = 216 * 32;//macbody����
							pModulation_mode->SetValue("BPSK");
							pModulation_fec->Enable(FALSE);
							pPayload_uep_eep->Enable(FALSE);
							break;
						case 9:
							p_3c_params->AV_p.MCS = 9;//����MCS
							p_3c_params->AV_p.modtype = 1;//���ĵ��Ʒ�ʽ
							p_3c_params->AV_p.UEP = 2;//����UEP��ʽ
							p_3c_params->AV_p.rate_up = 3;//������֧·��������
							p_3c_params->AV_p.rate_low = 3;//������֧·��������
							//p_3c_params->AV_p.L_mb = 216 * 32;//macbody����
							pModulation_mode->SetValue("BPSK");
							pModulation_fec->Enable(FALSE);
							pPayload_uep_eep->Enable(FALSE);
							break;
						case 10:
							p_3c_params->AV_p.MCS = 10;//����MCS
							p_3c_params->AV_p.modtype = 1;//���ĵ��Ʒ�ʽ
							p_3c_params->AV_p.UEP = 2;//����UEP��ʽ
							p_3c_params->AV_p.rate_up = 3;//������֧·��������
							p_3c_params->AV_p.rate_low = 3;//������֧·��������
							//p_3c_params->AV_p.L_mb = 216 * 32;//macbody����
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
							p_3c_params->AV_p.MCS = 0;//����MCS
							p_3c_params->AV_p.rate_up = 0;//������֧·��������
							p_3c_params->AV_p.rep = 9;
							break;
						case 1:
							p_3c_params->AV_p.MCS = 1;//����MCS
							p_3c_params->AV_p.rate_up = 1;//������֧·��������
							p_3c_params->AV_p.rep = 9;
							break;
						case 2:
							p_3c_params->AV_p.MCS = 2;//����MCS
							p_3c_params->AV_p.rate_up = 3;//������֧·��������
							p_3c_params->AV_p.rep = 9;
							break;
						case 3:
							p_3c_params->AV_p.MCS = 3;//����MCS
							p_3c_params->AV_p.rate_up = 3;//������֧·��������
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
				p_3c_params->set_signal_mode(AV);//���ò����������еĲ�������ʼ��
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
				p_3c_params->set_signal_mode(AV);//���ò����������еĲ�������ʼ��
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

	//��ע�͵���Ӧ�������ͳ�������������й�
	//SetFocus();
	//switch (id_changed)
	//{
	//case CONFIG_TRANS_TYPE:
	//	if (str.Compare("ACL(Asynchronous)") == 0){
	//		p_bluetoothparams->transtype = BlueTooth_ACL;//MessageBox(str);
	//	}else if (str.Compare(_T("SCO(Synchronous)")) == 0){
	//		p_bluetoothparams->transtype = BlueTooth_SCO;//MessageBox(str);
	//	}else{
	//		MessageBox("��֧�ֵĴ���ģʽ��",NULL,MB_ICONERROR);
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
	//		MessageBox("��֧�ֵ����ݰ����ͣ�",NULL,MB_ICONERROR);
	//	}
	//	break;
	//case CONFIG_LAPADDR://�д����
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
	//case CONFIG_MAX_LENGTH://�д����
	//	str.Remove(' ');
	//	break;
	//case CONFIG_DATA_SOURCE:
	//	if (0 == str.Compare("�������"))
	//	{
	//		//ѡ���������Ӧ���Ĵ���
	//		//MessageBox(str);
	//	}else if (0 == str.Compare("ѡ���ļ�"))
	//	{
	//		//ѡ���ȡ�ļ�Ӧ���Ĵ���
	//		//MessageBox(str);
	//	}
	//	break;
	//case CONFIG_OVERSAMP_FACTOR:
	//	str.Remove(' ');
	//	if(0 == atoi(str.GetBuffer()))
	//	{
	//		MessageBox("������ֵ��������",NULL,MB_ICONERROR);
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
	//case CONFIG_EFC_STATE://�д����
	//	break;
	//case CONFIG_CRC_STATE://�д����
	//	break;
	//case CONFIG_HEC_STATE://�д����
	//	break;
	//case CONFIG_BTB:
	//	str.Remove(' ');
	//	if ((0.0 == atof(str.GetBuffer())) || (atof(str.GetBuffer())>=1.0))
	//	{
	//		MessageBox("����ָ����������",NULL,MB_ICONERROR);
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
	//case CONFIG_NOISE_POWER://�д����
	//	break;
	//default:
	//	break;
	//}

	return 0;
}