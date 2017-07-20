// MacConfig_SC.cpp : 实现文件
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "MacConfig_SC.h"
#include "afxdialogex.h"


// CMacConfig_SC 对话框

IMPLEMENT_DYNAMIC(CMacConfig_SC, CDialog)

CMacConfig_SC::CMacConfig_SC(CWnd* pParent /*=NULL*/)
	: CDialog(CMacConfig_SC::IDD, pParent)
{
	m_finished_ini = FALSE;
}

CMacConfig_SC::~CMacConfig_SC()
{
}

void CMacConfig_SC::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMacConfig_SC, CDialog)
END_MESSAGE_MAP()


// CMacConfig_SC 消息处理程序


BOOL CMacConfig_SC::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rc;
	GetClientRect(&rc);
	//rc.bottom = 100;
	rc.left = 0;
	//rc.right = 100;
	rc.top = 0;
	m_MFCPropertyGrid_MacConfigSC.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,rc,this,3000);
	m_MFCPropertyGrid_MacConfigSC.EnableHeaderCtrl(FALSE,_T("参数"),_T("值"));
	m_MFCPropertyGrid_MacConfigSC.EnableDescriptionArea();
	m_MFCPropertyGrid_MacConfigSC.SetDescriptionRows(3);
	m_MFCPropertyGrid_MacConfigSC.SetVSDotNetLook();
	m_MFCPropertyGrid_MacConfigSC.MarkModifiedProperties();
	m_MFCPropertyGrid_MacConfigSC.SetAlphabeticMode(false); 
	m_MFCPropertyGrid_MacConfigSC.SetShowDragContext();

	/************************SC-PHY**************************/
	pGroup_SC = new CMFCPropertyGridProperty(_T("SC-PHY"));

	pPropSC_seed = new CMFCPropertyGridProperty(_T("Scrambler Seed"),_T("1010"),_T("设置Scrambler seed：4bits"));
	pGroup_SC->AddSubItem(pPropSC_seed);

	pPropSC_aggregation = new CMFCPropertyGridProperty(_T("Aggregation"),_T("0"),_T("设置Aggregation位：1bit，使用聚合置1，否则置0。"));
	pGroup_SC->AddSubItem(pPropSC_aggregation);

	pPropSC_uep = new CMFCPropertyGridProperty(_T("UEP"),_T("0"),_T("设置UEP位：1bit，使用UEP置1，否则置0。"));
	pGroup_SC->AddSubItem(pPropSC_uep);
	
	pPropSC_mcs = new CMFCPropertyGridProperty(_T("MCS"),_T("00101"),_T("设置MCS位：5bits，填入MCS序号对应的二进制序列。"));
	pGroup_SC->AddSubItem(pPropSC_mcs);

	pPropSC_frame_length = new CMFCPropertyGridProperty(_T("Frame Length"),_T("001001000100110101011"),_T("设置Frame length位：20bits，填入帧长对应的二进制序列。"));
	pGroup_SC->AddSubItem(pPropSC_frame_length);

	pPropSC_pre_type = new CMFCPropertyGridProperty(_T("Preamble Type"),_T("01"),_T("设置Preamble type位：2bits，填入前导类型所对应的序号。"));
	pGroup_SC->AddSubItem(pPropSC_pre_type);

	pPropSC_beam_track = new CMFCPropertyGridProperty(_T("Beam Tracking"),_T("0"),_T("设置Beam Tracking位：1bit，若在波束跟踪里出现训练序列，则置1，否则置0。"));
	pGroup_SC->AddSubItem(pPropSC_beam_track);

	pPropSC_latency_mode = new CMFCPropertyGridProperty(_T("Low-latency Mode"),_T("1"),_T("设置Low-latency Mode位：1bit，若帧使用低时延聚合模式，则置1，否则置0。"));
	pGroup_SC->AddSubItem(pPropSC_latency_mode);

	pPropSC_pilot_length = new CMFCPropertyGridProperty(_T("Pilot Word Length"),_T("0"),_T("设置Pilot Word Length位：2bits，设置导频长度所对应的比特。"));
	pGroup_SC->AddSubItem(pPropSC_pilot_length);

	pPropSC_pces = new CMFCPropertyGridProperty(_T("PCES"),_T("00"),_T("设置PCES位：2bits，若帧内包括信道估计序列则置1，否则置0。"));
	pGroup_SC->AddSubItem(pPropSC_pces);

	pPropSC_reserved = new CMFCPropertyGridProperty(_T("Reserved"),_T("00"),_T("设置保留比特位：2bits"));
	pGroup_SC->AddSubItem(pPropSC_reserved);

	/************************HSI-PHY**************************/
	pGroup_HSI = new CMFCPropertyGridProperty(_T("HSI-PHY"));

	pPropHSI_seed = new CMFCPropertyGridProperty(_T("Scramble Seed"),_T("0101"),_T("设置Scrambler seed：4bits"));
	pGroup_HSI->AddSubItem(pPropHSI_seed);

	pPropHSI_aggregation = new CMFCPropertyGridProperty(_T("Aggregation"),_T("1"),_T("设置Aggregation位：1bit，使用聚合置1，否则置0。"));
	pGroup_HSI->AddSubItem(pPropHSI_aggregation);

	pPropHSI_uep = new CMFCPropertyGridProperty(_T("UEP"),_T("0"),_T("设置UEP位：1bit，使用UEP置1，否则置0。"));
	pGroup_HSI->AddSubItem(pPropHSI_uep);

	pPropHSI_mcs = new CMFCPropertyGridProperty(_T("MCS"),_T("00111"),_T("设置MCS位：5bits，填入MCS序号对应的二进制序列。"));
	pGroup_HSI->AddSubItem(pPropHSI_mcs);

	pPropHSI_frame_length = new CMFCPropertyGridProperty(_T("Frame Length"),_T("001010011000111000110"),_T("设置Frame length位：20bits，填入帧长对应的二进制序列。"));
	pGroup_HSI->AddSubItem(pPropHSI_frame_length);

	pPropHSI_pre_type = new CMFCPropertyGridProperty(_T("Preamble Type"),_T("00"),_T("设置Preamble type位：2bits，填入前导类型所对应的序号。"));
	pGroup_HSI->AddSubItem(pPropHSI_pre_type);

	pPropHSI_beam_track = new CMFCPropertyGridProperty(_T("Beam Tracking"),_T("0"),_T("设置Beam Tracking位：1bit，若在波束跟踪里出现训练序列，则置1，否则置0。"));
	pGroup_HSI->AddSubItem(pPropHSI_beam_track);

	pPropHSI_latency_mode = new CMFCPropertyGridProperty(_T("Low-latency Mode"),_T("1"),_T("设置Low-latency Mode位：1bit，若帧使用低时延聚合模式，则置1，否则置0。"));
	pGroup_HSI->AddSubItem(pPropHSI_latency_mode);

	pPropHSI_bitsinter = new CMFCPropertyGridProperty(_T("Bit Interleaver"),_T("1"),_T("设置Bit interleaver位：1bit，若帧中数据使用了比特交织则置1，否则置0。"));
	pGroup_HSI->AddSubItem(pPropHSI_bitsinter);

	pPropHSI_pces = new CMFCPropertyGridProperty(_T("PCES"),_T("0"),_T("设置PCES位：1bit，若帧内包括信道估计序列则置1，否则置0。"));
	pGroup_HSI->AddSubItem(pPropHSI_pces);

	pPropHSI_skewed_map = new CMFCPropertyGridProperty(_T("Skewed Constellation"),_T("0"),_T("设置Skewed constellation位：1bit，若不等差错保护使用星座映射方式则置1，否则置0。"));
	pGroup_HSI->AddSubItem(pPropHSI_skewed_map);

	pPropHSI_reserved = new CMFCPropertyGridProperty(_T("Reserved"),_T("0100101000"),_T("设置保留比特位：10bits"));
	pGroup_HSI->AddSubItem(pPropHSI_reserved);

	/************************AV-PHY**************************/
	pGroup_AV = new CMFCPropertyGridProperty(_T("AV-PHY"));

	pPropAV_reserved_00 = new CMFCPropertyGridProperty(_T("Reserved Bit"),_T("0"),_T("设置保留比特位：1bit。"));
	pGroup_AV->AddSubItem(pPropAV_reserved_00);

	pPropAV_uep = new CMFCPropertyGridProperty(_T("UEP Mapping"),_T("0"),_T("设置UEP mapping位：1bit，若使用UEP则置1，否则置0。"));
	pGroup_AV->AddSubItem(pPropAV_uep);

	pPropAV_seed = new CMFCPropertyGridProperty(_T("Scramble Seed"),_T("0110"),_T("设置Scrambler seed：4bits。"));
	pGroup_AV->AddSubItem(pPropAV_seed);

	pPropAV_reserved_01 = new CMFCPropertyGridProperty(_T("Reserved Bits"),_T("10"),_T("设置保留比特位：2bits。"));
	pGroup_AV->AddSubItem(pPropAV_reserved_01);


	m_MFCPropertyGrid_MacConfigSC.AddProperty(pGroup_SC);
	m_MFCPropertyGrid_MacConfigSC.AddProperty(pGroup_HSI);
	m_MFCPropertyGrid_MacConfigSC.AddProperty(pGroup_AV);

	//根据所选模式调整界面
	HWND hWnd=::FindWindow(NULL,_T("MAC配置图例")); 
	CMacDiag *pMacdiag = (CMacDiag *)CMacDiag::FromHandle(hWnd);
	switch(pMacdiag->m_ComMacdiag.GetCurSel())
	{
	case 0:
		{
			pGroup_SC->Expand(TRUE);
			pGroup_HSI->Expand(FALSE);
			pGroup_AV->Expand(FALSE);
		}
		break;
	case 1:
		{
			pGroup_SC->Expand(FALSE);
			pGroup_HSI->Expand(TRUE);
			pGroup_AV->Expand(FALSE);
		}
		break;
	case 2:
		{
			pGroup_SC->Expand(FALSE);
			pGroup_HSI->Expand(FALSE);
			pGroup_AV->Expand(TRUE);
		}
		break;
	default:
		break;
	}

	m_finished_ini = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
