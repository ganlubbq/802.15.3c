// TabCarrier.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "TabCarrier.h"
#include "afxdialogex.h"
#include "MainFrm.h"

// CTabCarrier �Ի���

IMPLEMENT_DYNAMIC(CTabCarrier, CDialog)

CTabCarrier::CTabCarrier(CWnd* pParent /*=NULL*/)
	: CDialog(CTabCarrier::IDD, pParent)
{
	m_finished_ini = FALSE;
	p_3c_params = 0;//���캯�����Ƚ�ָ�븳Ϊ0����OnInitDialog���پ��帳ֵ
}

CTabCarrier::~CTabCarrier()
{
}

void CTabCarrier::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTabCarrier, CDialog)
	ON_WM_SIZE()
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED,OnPropertyChanged)//������Ӵ��ļ��Ի�ȡ��Ϣ��Ӧ
END_MESSAGE_MAP()


// CTabCarrier ��Ϣ�������


void CTabCarrier::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	// CDialog::OnOK();
}


BOOL CTabCarrier::OnInitDialog()
{
	CDialog::OnInitDialog();
	//�й�Э�����õ�ָ�봫�ݵ�����Э����
	p_3c_params = ((CMainFrame*)AfxGetMainWnd())->m_pass_to_thread.p_protocol_params_3c;//��3C����ָ�븳ֵ

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rc;
	GetClientRect(&rc);
	//rc.bottom += 20;
	rc.left += 10;
	//rc.right += 10;
	rc.top += 10;
	m_MFCPropertyGridTwo.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,rc,this,3000);
	m_MFCPropertyGridTwo.EnableHeaderCtrl(FALSE,_T("����"),_T("ֵ"));
	m_MFCPropertyGridTwo.EnableDescriptionArea();
	m_MFCPropertyGridTwo.SetDescriptionRows(5);
	m_MFCPropertyGridTwo.SetVSDotNetLook();
	m_MFCPropertyGridTwo.MarkModifiedProperties();
	m_MFCPropertyGridTwo.SetAlphabeticMode(false); 
	m_MFCPropertyGridTwo.SetShowDragContext();

	pGroup11 = new CMFCPropertyGridProperty(_T("��������"));
	pGroup12 = new CMFCPropertyGridProperty(_T("���ο���"));
	pGroup13 = new CMFCPropertyGridProperty(_T("OFDM����"));
	

	pPropS1 = new CMFCPropertyGridProperty(_T("��������"),_T("SC"),_T("ѡ��IEEE 802.15.3c����ģʽ֮һ:SC/HSI/AV"),CARRI_SIG_MODE_3C);
	pPropS1->AddOption(_T("SC"));
	pPropS1->AddOption(_T("HSI"));
	pPropS1->AddOption(_T("AV"));
	pPropS1->AllowEdit(FALSE);
	pGroup11->AddSubItem(pPropS1);

// 	CMFCPropertyGridProperty *pPropS2=new CMFCPropertyGridProperty(_T("�ܲ�������"),_T("0000"),_T("��������Ŀ"));
// 	pPropS2->Enable(FALSE);
// 	pGroup11->AddSubItem(pPropS2);

	pGroup12->AddSubItem(new CMFCPropertyGridProperty(_T("��������"),_T("1"),_T("���ڹ������ʵ�˵��")));
	CMFCPropertyGridProperty* pPropS3 = new CMFCPropertyGridProperty(_T("����Ƶ��"),_T("Off"),_T("����Ƶ��״̬��ON��OFF"));
	pPropS3->AddOption(_T("On"));  
	pPropS3->AddOption(_T("Off"));     
	pPropS3->AllowEdit(FALSE);
	pGroup12->AddSubItem(pPropS3);

	p_quadrature_angle_adjustment = new CMFCPropertyGridProperty(_T("�����Ƕȵ���"),_T("0.00 Deg"),_T("���ǲ�����˵��"),CARRI_QUADRATURE_ANGLE_ADJUST);
	pGroup12->AddSubItem(p_quadrature_angle_adjustment);

	p_IQ_gain_balance = new CMFCPropertyGridProperty(_T("I/Qƽ������"), _T("0.00 dB"), _T("���ǲ�����˵��"),CARRI_IQ_BALANCE_GAIN);
	pGroup12->AddSubItem(p_IQ_gain_balance);

	/*CMFCPropertyGridProperty* pPropS4 = new CMFCPropertyGridProperty(_T("�ྶ״̬"),_T("Off"),_T("�ྶ״̬��ON��OFF"));
	pPropS4->AddOption(_T("On"));  
	pPropS4->AddOption(_T("Off"));     
	pPropS4->AllowEdit(FALSE);
	pGroup12->AddSubItem(pPropS4);*/

	/*CMFCPropertyGridProperty* pPropS5=new CMFCPropertyGridProperty(_T("�ྶ��"), _T("0"), _T("���ǲ�����˵��"));
	pPropS5->Enable(FALSE);
	pGroup12->AddSubItem(pPropS5);*/

	//OFDM�Ӳ˵�
	CMFCPropertyGridProperty* pPropS4 = new CMFCPropertyGridProperty(_T("��Ƭ����"),_T("0.38 ns"),_T("������Ƭ����ʱ��"));
	pGroup13->AddSubItem(pPropS4);

	CMFCPropertyGridProperty* pPropS5 = new CMFCPropertyGridProperty(_T("���ز���"),_T("512"),_T("OFDM���ز�����/FFT��С"));
	pGroup13->AddSubItem(pPropS5);

	CMFCPropertyGridProperty* pPropS6 = new CMFCPropertyGridProperty(_T("�����ز���"),_T("336"),_T("OFDM�����г������ݵ����ز���Ŀ"));
	pGroup13->AddSubItem(pPropS6);

	CMFCPropertyGridProperty* pPropS7 = new CMFCPropertyGridProperty(_T("��Ƶ�ز���"),_T("16"),_T("OFDM�����г��ص�Ƶ�����ز���Ŀ"));
	pGroup13->AddSubItem(pPropS7);

	CMFCPropertyGridProperty* pPropS8 = new CMFCPropertyGridProperty(_T("�����ز���"),_T("141"),_T("OFDM�����г��صı������ز���Ŀ"));
	pGroup13->AddSubItem(pPropS8);

	CMFCPropertyGridProperty* pPropS9 = new CMFCPropertyGridProperty(_T("ֱ���ز���"),_T("3"),_T("OFDM�����г���ֱ���ز������ز���Ŀ"));
	pGroup13->AddSubItem(pPropS9);

	CMFCPropertyGridProperty* pPropS10 = new CMFCPropertyGridProperty(_T("ʹ���ز���"),_T("352"),_T("ʹ���ز����������ز���+��Ƶ�ز���"));
	pGroup13->AddSubItem(pPropS10);

	CMFCPropertyGridProperty* pPropS11 = new CMFCPropertyGridProperty(_T("�������"),_T("64"),_T("ѭ��ǰ׺����"));
	pGroup13->AddSubItem(pPropS11);

	CMFCPropertyGridProperty* pPropS12 = new CMFCPropertyGridProperty(_T("�ز�Ƶ�ʼ��"),_T("5.15625 MHz"),_T("OFDM�ز�֮���Ƶ�ʼ��"));
	pGroup13->AddSubItem(pPropS12);

	CMFCPropertyGridProperty* pPropS13 = new CMFCPropertyGridProperty(_T("ʵ��ʹ�ô���"),_T("1815 MHz"),_T("ʵ����ʹ�õĴ���ʹ���ز���*�ز�Ƶ�ʼ��"));
	pGroup13->AddSubItem(pPropS13);

	CMFCPropertyGridProperty* pPropS14 = new CMFCPropertyGridProperty(_T("FFT����"),_T("193.94 ns"),_T("IFFT/FFT����"));
	pGroup13->AddSubItem(pPropS14);

	CMFCPropertyGridProperty* pPropS15 = new CMFCPropertyGridProperty(_T("�����������ʱ��"),_T("24.24 ns"),_T("ѭ��ǰ׺����ʱ��"));
	pGroup13->AddSubItem(pPropS15);

	CMFCPropertyGridProperty* pPropS16 = new CMFCPropertyGridProperty(_T("OFDM��������"),_T("218.18 ns"),_T("����OFDM���ų���ʱ�䣺FFT����+�����������ʱ��"));
	pGroup13->AddSubItem(pPropS16);

	CMFCPropertyGridProperty* pPropS17 = new CMFCPropertyGridProperty(_T("OFDM��������"),_T("4.583 MHz"),_T("OFDM��������"));
	pGroup13->AddSubItem(pPropS17);

	pPropS3->AllowEdit(FALSE);
	pPropS4->AllowEdit(FALSE);
	pPropS5->AllowEdit(FALSE);
	pPropS6->AllowEdit(FALSE);
	pPropS7->AllowEdit(FALSE);
	pPropS8->AllowEdit(FALSE);
	pPropS9->AllowEdit(FALSE);
	pPropS10->AllowEdit(FALSE);
	pPropS11->AllowEdit(FALSE);
	pPropS12->AllowEdit(FALSE);
	pPropS13->AllowEdit(FALSE);
	pPropS14->AllowEdit(FALSE);
	pPropS15->AllowEdit(FALSE);
	pPropS16->AllowEdit(FALSE);
	pPropS17->AllowEdit(FALSE);




	m_MFCPropertyGridTwo.AddProperty(pGroup11);
	m_MFCPropertyGridTwo.AddProperty(pGroup12);
	m_MFCPropertyGridTwo.AddProperty(pGroup13);

	m_MFCPropertyGridTwo.EnableDescriptionArea(TRUE);
	m_MFCPropertyGridTwo.SetCustomColors(RGB(250,250,250),RGB(0,0,0),RGB(230,230,230),RGB(100,100,100),RGB(230,230,230),RGB(0,0,0),RGB(220,220,220));
	m_MFCPropertyGridTwo.ShowWindow(TRUE);

	m_finished_ini = TRUE;
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CTabCarrier::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if (IsWindowVisible() || m_finished_ini)
	{
		m_MFCPropertyGridTwo.MoveWindow(10,15,cx-32,cy-35);
	}
}

LRESULT CTabCarrier::OnPropertyChanged(__in WPARAM wparam,__in LPARAM lparam)
{
	CMFCPropertyGridProperty* pProp = (CMFCPropertyGridProperty*) lparam;
	CString str;
	CW* p_wave = &(((CGraphWAVE*)(((CMainFrame*)AfxGetMainWnd())->m_rightSplitter.GetPane(1,0)))->m_wave);//��ȡ�ı����
	CTabProtocolConfig &T_Proto = ((CTabParent*)(((CMainFrame*)AfxGetMainWnd())->m_mainSplitter.GetPane(0,0)))->m_tabProtocolConfig;//��ҳ����
	str = pProp->GetValue();
	CString str_temp = "";
	int id_changed = pProp->GetData();//��ȡ��ǰֵ�����仯�����Ե�ID

	regex patten_iqgainbalance("^[-]?\\d+(\\.\\d*)?(dB)?(db)?$",regex::icase);	//������ʽ��֤�����Ƿ���ȷ
	regex patten_quad_deg_ad("^[-]?\\d+(\\.\\d*)?(deg)?$",regex::icase);
	bool match_result = false;

	/*******************153c�����������*************************/
	SetFocus();
	switch (id_changed)
	{
	case CARRI_SIG_MODE_3C:
		if (str.Compare("SC") == 0)
		{
			p_3c_params->Sig_mode = SC;
			T_Proto.pModulation_mcs->RemoveAllOptions();
			T_Proto.pModulation_mcs->AddOption(_T("0"));
			T_Proto.pModulation_mcs->AddOption(_T("1"));
			T_Proto.pModulation_mcs->AddOption(_T("2"));
			T_Proto.pModulation_mcs->AddOption(_T("3"));
			T_Proto.pModulation_mcs->AddOption(_T("4"));
			T_Proto.pModulation_mcs->AddOption(_T("5"));
			T_Proto.pModulation_mcs->AddOption(_T("6"));
			T_Proto.pModulation_mcs->AddOption(_T("7"));
			T_Proto.pModulation_mcs->AddOption(_T("8"));
			T_Proto.pModulation_mcs->AddOption(_T("9"));
			T_Proto.pModulation_mcs->AddOption(_T("10"));
			T_Proto.pModulation_mcs->AddOption(_T("11"));
			T_Proto.pModulation_mcs->AddOption(_T("12"));
			T_Proto.pModulation_mcs->AddOption(_T("13"));
			T_Proto.pModulation_mcs->AllowEdit(FALSE);
			p_wave->m_Maxspectrum = 1760;
			T_Proto.pCarrier_sig_mode->SetValue("SC");
			T_Proto.pPayload_tone_inter->Enable(FALSE);
		}
		else if (str.Compare("HSI") == 0)
		{
			p_3c_params->Sig_mode = HSI;
			T_Proto.pModulation_mcs->RemoveAllOptions();
			T_Proto.pModulation_mcs->AddOption(_T("0"));
			T_Proto.pModulation_mcs->AddOption(_T("1"));
			T_Proto.pModulation_mcs->AddOption(_T("2"));
			T_Proto.pModulation_mcs->AddOption(_T("3"));
			T_Proto.pModulation_mcs->AddOption(_T("4"));
			T_Proto.pModulation_mcs->AddOption(_T("5"));
			T_Proto.pModulation_mcs->AddOption(_T("6"));
			T_Proto.pModulation_mcs->AddOption(_T("7"));
			T_Proto.pModulation_mcs->AddOption(_T("8"));
			T_Proto.pModulation_mcs->AddOption(_T("9"));
			T_Proto.pModulation_mcs->AddOption(_T("10"));
			T_Proto.pModulation_mcs->AddOption(_T("11"));
			T_Proto.pModulation_mcs->AllowEdit(FALSE);
			p_wave->m_Maxspectrum = 2640;
			T_Proto.pCarrier_sig_mode->SetValue("HSI");
			T_Proto.pPayload_tone_inter->Enable(TRUE);
		}
		else if (str.Compare("AV") == 0)
		{
			p_3c_params->Sig_mode = AV;
			T_Proto.pModulation_mcs->RemoveAllOptions();
			T_Proto.pModulation_mcs->AddOption(_T("0"));
			T_Proto.pModulation_mcs->AddOption(_T("1"));
			T_Proto.pModulation_mcs->AddOption(_T("2"));
			T_Proto.pModulation_mcs->AddOption(_T("3"));
			T_Proto.pModulation_mcs->AddOption(_T("4"));
			T_Proto.pModulation_mcs->AddOption(_T("5"));
			T_Proto.pModulation_mcs->AddOption(_T("6"));
			T_Proto.pModulation_mcs->AllowEdit(FALSE);
			p_wave->m_Maxspectrum = 2538;
			T_Proto.pCarrier_sig_mode->SetValue("AV");
			T_Proto.pPayload_tone_inter->Enable(TRUE);
		}
		else
		{
			MessageBox("��֧�ֵ��ź�ģʽ��",NULL,MB_ICONERROR);
		}
		break;
	case CARRI_QUADRATURE_ANGLE_ADJUST:
		str.Remove(' ');//�Ƴ��ո�
		match_result = regex_match(str.GetBuffer(),patten_quad_deg_ad);//������֤
		if (match_result)
		{
			double quad_angle_ad = atof(str);
			if (quad_angle_ad > 90)
				quad_angle_ad = 90;
			else if (quad_angle_ad < -90)
				quad_angle_ad = -90;
			p_3c_params->quan_angle_adjust = quad_angle_ad;
			str_temp.Format("%f Deg", quad_angle_ad);
			pProp->SetValue(str_temp);
		}
		else
		{
			MessageBox("�����Ƕ���������");
		}
		break;
	case CARRI_IQ_BALANCE_GAIN:
		str.Remove(' ');//�Ƴ��ո�
		match_result = regex_match(str.GetBuffer(),patten_iqgainbalance);//������֤
		if (match_result)
		{
			double IQ_gain = atof(str);
			if (IQ_gain > 10)
				IQ_gain = 10;
			else if (IQ_gain < -10)
				IQ_gain = -10;
			p_3c_params->IQ_gain = IQ_gain;
			str_temp.Format("%f dB", IQ_gain);
			pProp->SetValue(str_temp);
		}
		else
		{
			MessageBox("I\Qƽ��������������");
		}
		break;
	default:
		break;
	}
	return 0;
}


