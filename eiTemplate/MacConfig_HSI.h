#pragma once


// CMacConfig_HSI 对话框

class CMacConfig_HSI : public CDialog
{
	DECLARE_DYNAMIC(CMacConfig_HSI)

public:
	CMacConfig_HSI(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMacConfig_HSI();
	CMFCPropertyGridCtrl     m_MFCPropertyGrid_MacConfigHSI;//协议的配置项列表
	CMFCPropertyGridProperty *pGroup11;//基本参数
// 对话框数据
	enum { IDD = IDD_MAC_CONFIG_HSI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL m_finished_ini;
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
