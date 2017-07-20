#pragma once
#include "MacDiag.h"


// CMacConfig_SC 对话框

class CMacConfig_SC : public CDialog
{
	DECLARE_DYNAMIC(CMacConfig_SC)

public:
	CMacConfig_SC(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMacConfig_SC();
	CMFCPropertyGridCtrl     m_MFCPropertyGrid_MacConfigSC;//协议的配置项列表
	CMFCPropertyGridProperty *pGroup_SC;//Mac设置SC-PHY
	CMFCPropertyGridProperty *pGroup_HSI;//Mac设置HSI-PHY
	CMFCPropertyGridProperty *pGroup_AV;//Mac设置AV-PHY

	//SC-PHY配置项
	CMFCPropertyGridProperty *pPropSC_seed;
	CMFCPropertyGridProperty *pPropSC_aggregation;
	CMFCPropertyGridProperty *pPropSC_uep;
	CMFCPropertyGridProperty *pPropSC_mcs;
	CMFCPropertyGridProperty *pPropSC_frame_length;
	CMFCPropertyGridProperty *pPropSC_pre_type;
	CMFCPropertyGridProperty *pPropSC_beam_track;
	CMFCPropertyGridProperty *pPropSC_latency_mode;
	CMFCPropertyGridProperty *pPropSC_pilot_length;
	CMFCPropertyGridProperty *pPropSC_pces;
	CMFCPropertyGridProperty *pPropSC_reserved;

	//HSI-PHY配置项
	CMFCPropertyGridProperty *pPropHSI_seed;
	CMFCPropertyGridProperty *pPropHSI_aggregation;
	CMFCPropertyGridProperty *pPropHSI_uep;
	CMFCPropertyGridProperty *pPropHSI_mcs;
	CMFCPropertyGridProperty *pPropHSI_frame_length;
	CMFCPropertyGridProperty *pPropHSI_pre_type;
	CMFCPropertyGridProperty *pPropHSI_beam_track;
	CMFCPropertyGridProperty *pPropHSI_latency_mode;
	CMFCPropertyGridProperty *pPropHSI_bitsinter;
	CMFCPropertyGridProperty *pPropHSI_pces;
	CMFCPropertyGridProperty *pPropHSI_skewed_map;
	CMFCPropertyGridProperty *pPropHSI_reserved;

	//AV-PHY配置项
	CMFCPropertyGridProperty *pPropAV_reserved_00;
	CMFCPropertyGridProperty *pPropAV_uep;
	CMFCPropertyGridProperty *pPropAV_seed;
	CMFCPropertyGridProperty *pPropAV_reserved_01;

// 对话框数据
	enum { IDD = IDD_MAC_CONFIG_SC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	BOOL m_finished_ini;
public:
	virtual BOOL OnInitDialog();
};
