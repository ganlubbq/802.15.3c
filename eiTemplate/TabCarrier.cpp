// TabCarrier.cpp : 实现文件
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "TabCarrier.h"
#include "afxdialogex.h"
#include "MainFrm.h"

// CTabCarrier 对话框

IMPLEMENT_DYNAMIC(CTabCarrier, CDialog)

CTabCarrier::CTabCarrier(CWnd* pParent /*=NULL*/)
	: CDialog(CTabCarrier::IDD, pParent)
{
	m_finished_ini = FALSE;
	p_3c_params = 0;//构造函数中先将指针赋为0，在OnInitDialog中再具体赋值
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
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED,OnPropertyChanged)//必须添加此文件以获取消息响应
END_MESSAGE_MAP()


// CTabCarrier 消息处理程序


void CTabCarrier::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	// CDialog::OnOK();
}


BOOL CTabCarrier::OnInitDialog()
{
	CDialog::OnInitDialog();
	//有关协议配置的指针传递到配置协议类
	p_3c_params = ((CMainFrame*)AfxGetMainWnd())->m_pass_to_thread.p_protocol_params_3c;//给3C参数指针赋值

	// TODO:  在此添加额外的初始化
	CRect rc;
	GetClientRect(&rc);
	//rc.bottom += 20;
	rc.left += 10;
	//rc.right += 10;
	rc.top += 10;
	m_MFCPropertyGridTwo.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,rc,this,3000);
	m_MFCPropertyGridTwo.EnableHeaderCtrl(FALSE,_T("参数"),_T("值"));
	m_MFCPropertyGridTwo.EnableDescriptionArea();
	m_MFCPropertyGridTwo.SetDescriptionRows(5);
	m_MFCPropertyGridTwo.SetVSDotNetLook();
	m_MFCPropertyGridTwo.MarkModifiedProperties();
	m_MFCPropertyGridTwo.SetAlphabeticMode(false); 
	m_MFCPropertyGridTwo.SetShowDragContext();

	pGroup11 = new CMFCPropertyGridProperty(_T("基本参数"));
	pGroup12 = new CMFCPropertyGridProperty(_T("波形控制"));
	pGroup13 = new CMFCPropertyGridProperty(_T("OFDM参数"));
	

	pPropS1 = new CMFCPropertyGridProperty(_T("波形名称"),_T("SC"),_T("选择IEEE 802.15.3c三种模式之一:SC/HSI/AV"),CARRI_SIG_MODE_3C);
	pPropS1->AddOption(_T("SC"));
	pPropS1->AddOption(_T("HSI"));
	pPropS1->AddOption(_T("AV"));
	pPropS1->AllowEdit(FALSE);
	pGroup11->AddSubItem(pPropS1);

// 	CMFCPropertyGridProperty *pPropS2=new CMFCPropertyGridProperty(_T("总采样点数"),_T("0000"),_T("采样点数目"));
// 	pPropS2->Enable(FALSE);
// 	pGroup11->AddSubItem(pPropS2);

	pGroup12->AddSubItem(new CMFCPropertyGridProperty(_T("过采样率"),_T("1"),_T("关于过采样率的说明")));
	CMFCPropertyGridProperty* pPropS3 = new CMFCPropertyGridProperty(_T("镜像频谱"),_T("Off"),_T("镜像频谱状态：ON或OFF"));
	pPropS3->AddOption(_T("On"));  
	pPropS3->AddOption(_T("Off"));     
	pPropS3->AllowEdit(FALSE);
	pGroup12->AddSubItem(pPropS3);

	p_quadrature_angle_adjustment = new CMFCPropertyGridProperty(_T("正交角度调整"),_T("0.00 Deg"),_T("这是参数的说明"),CARRI_QUADRATURE_ANGLE_ADJUST);
	pGroup12->AddSubItem(p_quadrature_angle_adjustment);

	p_IQ_gain_balance = new CMFCPropertyGridProperty(_T("I/Q平衡增益"), _T("0.00 dB"), _T("这是参数的说明"),CARRI_IQ_BALANCE_GAIN);
	pGroup12->AddSubItem(p_IQ_gain_balance);

	/*CMFCPropertyGridProperty* pPropS4 = new CMFCPropertyGridProperty(_T("多径状态"),_T("Off"),_T("多径状态：ON或OFF"));
	pPropS4->AddOption(_T("On"));  
	pPropS4->AddOption(_T("Off"));     
	pPropS4->AllowEdit(FALSE);
	pGroup12->AddSubItem(pPropS4);*/

	/*CMFCPropertyGridProperty* pPropS5=new CMFCPropertyGridProperty(_T("多径数"), _T("0"), _T("这是参数的说明"));
	pPropS5->Enable(FALSE);
	pGroup12->AddSubItem(pPropS5);*/

	//OFDM子菜单
	CMFCPropertyGridProperty* pPropS4 = new CMFCPropertyGridProperty(_T("码片周期"),_T("0.38 ns"),_T("单个码片持续时间"));
	pGroup13->AddSubItem(pPropS4);

	CMFCPropertyGridProperty* pPropS5 = new CMFCPropertyGridProperty(_T("子载波数"),_T("512"),_T("OFDM子载波数量/FFT大小"));
	pGroup13->AddSubItem(pPropS5);

	CMFCPropertyGridProperty* pPropS6 = new CMFCPropertyGridProperty(_T("数据载波数"),_T("336"),_T("OFDM符号中承载数据的子载波数目"));
	pGroup13->AddSubItem(pPropS6);

	CMFCPropertyGridProperty* pPropS7 = new CMFCPropertyGridProperty(_T("导频载波数"),_T("16"),_T("OFDM符号中承载导频的子载波数目"));
	pGroup13->AddSubItem(pPropS7);

	CMFCPropertyGridProperty* pPropS8 = new CMFCPropertyGridProperty(_T("保护载波数"),_T("141"),_T("OFDM符号中承载的保护子载波数目"));
	pGroup13->AddSubItem(pPropS8);

	CMFCPropertyGridProperty* pPropS9 = new CMFCPropertyGridProperty(_T("直流载波数"),_T("3"),_T("OFDM符号中承载直流载波的子载波数目"));
	pGroup13->AddSubItem(pPropS9);

	CMFCPropertyGridProperty* pPropS10 = new CMFCPropertyGridProperty(_T("使用载波数"),_T("352"),_T("使用载波数：数据载波数+导频载波数"));
	pGroup13->AddSubItem(pPropS10);

	CMFCPropertyGridProperty* pPropS11 = new CMFCPropertyGridProperty(_T("保护间隔"),_T("64"),_T("循环前缀长度"));
	pGroup13->AddSubItem(pPropS11);

	CMFCPropertyGridProperty* pPropS12 = new CMFCPropertyGridProperty(_T("载波频率间隔"),_T("5.15625 MHz"),_T("OFDM载波之间的频率间隔"));
	pGroup13->AddSubItem(pPropS12);

	CMFCPropertyGridProperty* pPropS13 = new CMFCPropertyGridProperty(_T("实际使用带宽"),_T("1815 MHz"),_T("实际所使用的带宽：使用载波数*载波频率间隔"));
	pGroup13->AddSubItem(pPropS13);

	CMFCPropertyGridProperty* pPropS14 = new CMFCPropertyGridProperty(_T("FFT周期"),_T("193.94 ns"),_T("IFFT/FFT周期"));
	pGroup13->AddSubItem(pPropS14);

	CMFCPropertyGridProperty* pPropS15 = new CMFCPropertyGridProperty(_T("保护间隔持续时间"),_T("24.24 ns"),_T("循环前缀持续时间"));
	pGroup13->AddSubItem(pPropS15);

	CMFCPropertyGridProperty* pPropS16 = new CMFCPropertyGridProperty(_T("OFDM符号周期"),_T("218.18 ns"),_T("单个OFDM符号持续时间：FFT周期+保护间隔持续时间"));
	pGroup13->AddSubItem(pPropS16);

	CMFCPropertyGridProperty* pPropS17 = new CMFCPropertyGridProperty(_T("OFDM符号速率"),_T("4.583 MHz"),_T("OFDM符号速率"));
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
	// 异常: OCX 属性页应返回 FALSE
}


void CTabCarrier::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (IsWindowVisible() || m_finished_ini)
	{
		m_MFCPropertyGridTwo.MoveWindow(10,15,cx-32,cy-35);
	}
}

LRESULT CTabCarrier::OnPropertyChanged(__in WPARAM wparam,__in LPARAM lparam)
{
	CMFCPropertyGridProperty* pProp = (CMFCPropertyGridProperty*) lparam;
	CString str;
	CW* p_wave = &(((CGraphWAVE*)(((CMainFrame*)AfxGetMainWnd())->m_rightSplitter.GetPane(1,0)))->m_wave);//获取改变变量
	CTabProtocolConfig &T_Proto = ((CTabParent*)(((CMainFrame*)AfxGetMainWnd())->m_mainSplitter.GetPane(0,0)))->m_tabProtocolConfig;//跨页联动
	str = pProp->GetValue();
	CString str_temp = "";
	int id_changed = pProp->GetData();//获取当前值发生变化的属性的ID

	regex patten_iqgainbalance("^[-]?\\d+(\\.\\d*)?(dB)?(db)?$",regex::icase);	//正则表达式验证输入是否正确
	regex patten_quad_deg_ad("^[-]?\\d+(\\.\\d*)?(deg)?$",regex::icase);
	bool match_result = false;

	/*******************153c界面参数传入*************************/
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
			MessageBox("不支持的信号模式！",NULL,MB_ICONERROR);
		}
		break;
	case CARRI_QUADRATURE_ANGLE_ADJUST:
		str.Remove(' ');//移除空格
		match_result = regex_match(str.GetBuffer(),patten_quad_deg_ad);//正则验证
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
			MessageBox("正交角度设置有误！");
		}
		break;
	case CARRI_IQ_BALANCE_GAIN:
		str.Remove(' ');//移除空格
		match_result = regex_match(str.GetBuffer(),patten_iqgainbalance);//正则验证
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
			MessageBox("I\Q平衡增益设置有误！");
		}
		break;
	default:
		break;
	}
	return 0;
}


