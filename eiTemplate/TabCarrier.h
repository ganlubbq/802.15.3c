#pragma once


// CTabCarrier 对话框

class CTabCarrier : public CDialog
{
	DECLARE_DYNAMIC(CTabCarrier)

public:
	CTabCarrier(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTabCarrier();

// 对话框数据
	enum { IDD = IDD_TAB_CARRIER_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	BOOL m_finished_ini;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnPropertyChanged(__in WPARAM wparam,__in LPARAM lparam);//处理界面参数设置以及各个页面的联动
	Protocol_param_3C* p_3c_params;//3c参数配置类

	CMFCPropertyGridCtrl m_MFCPropertyGridTwo;//a/b/g协议参数列表
	CMFCPropertyGridProperty *pGroup11;//基本参数
	CMFCPropertyGridProperty *pGroup12;//波形控制
	CMFCPropertyGridProperty *pGroup13;//OFDM参数

	CMFCPropertyGridProperty *pPropS1;//信号模式设置SC、HSI、AV

	CMFCPropertyGridProperty* p_IQ_gain_balance;	//IQ平衡增益
	CMFCPropertyGridProperty* p_quadrature_angle_adjustment;	//正交角度调制
};
