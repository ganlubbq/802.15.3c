#pragma once

// CC
class CC : public CStatic
{
	DECLARE_DYNAMIC(CC)
public:
	CC();
	virtual ~CC();
private:
	double  m_ValueXRange;//X轴竖线个数10
	double  m_ValueYRange;//Y轴横线个数6
	

	double  m_RatioX;//X轴刻度和实际显示刻度比例
	double  m_RatioY;//Y轴刻度比例
	int     m_BaseXline;//X轴的基线值
	int     m_BaseYline;//Y轴的基线值
	double  m_ScaleValueXRange;//X轴起始值0
	double  m_ScaleValueYRange;//Y轴起始值,0.000001
	
	double  m_ScaleValueYEnd;//刻度值Y轴结束值1
	double  m_dDimX;//幅度刻度间隔单位
	double  m_dDimY;

	int     m_RealBaseYLine;//真实值Y基线

	float   m_RealValueXInterval;//真实点的X轴间隔单位值
public:
	double  m_ScaleValueXEnd;//刻度值X轴结束值10
	int     m_AllNum;//X轴总点数
	int     m_RealValuenSize;//真实波形点数
	double CCDFNumInter;
	double *pPointArrayCCDF;//接收点
	POINT  *pPointArrayCCDFIndex;
	double  m_maxCCDFX;//CCDF最大值
	double *sumCCDF;//用于接收CCDF计算值
private:
	CBrush  m_BkBrush;//黑色背景画刷
	CBrush  m_CurveBrush;//网格线画刷
	CRect	m_rectCurve;//曲线区域
	CPen    m_PenDarkLine;//暗线画笔
	CPen    m_PenBrightLine;//明线画笔
	CFont   m_FontAxis;//标题字体
	CPen    m_PenCurveA;//曲线画笔
public:
	BOOL    controlRunDraw;//控制标记

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	void    ValueTransform(CDC *pDC);//坐标与设备坐标的映射转化
	void    DrawGrid(CDC *pDC);//网格线
	void    DrawAxis(CDC *pDC);//刻度
	void    DrawXYtitle(CDC *pDC);//标题
	void    DrawCurveA(CDC *pDC);//曲线	
	void    Update();//更新图像
	void    runDraw();//运行
};


