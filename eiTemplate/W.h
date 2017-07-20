#pragma once

class CW : public CStatic
{
	DECLARE_DYNAMIC(CW)

public:
	CW();
	virtual ~CW();
public:
	double  m_ValueXRange;//网格X轴的范围大小
	double  m_ValueYRange;//网格Y轴的范围大小
	double  m_AllNum;//X轴总点数
	

	double  m_RatioX;//X轴刻度间像素值
	double  m_RatioY;//Y轴刻度间像素值
	double  m_RatioY_IorQ;
	int     m_BaseXline;//X轴的基线值
	int     m_BaseYline;//Y轴的基线值
	double  m_ScaleValueXRange;//刻度值X轴起始值
	double  m_ScaleValueYRange;//刻度值Y轴起始值
	double  m_ScaleValueXEnd;//刻度值X轴结束值
	double  m_ScaleValueYEnd;//刻度值Y轴结束值
	double  m_dDimX;
	double  m_dDimY;//幅度刻度间隔单位

	int     m_RealBaseYLine;//真实值Y基线
	int     m_RealBaseYLine2;//真实值Y基线，I|Q两个基线
	int     m_RealValuenSize;//真实波形点数
	int     m_FFT_AllNum;//FFT变换后的X轴个数
	int		m_Maxspectrum;//频谱最大坐标
	double  m_IQ_range;
	double  m_RealValueXInterval;//真实点的X轴间隔单位值
	double  m_FFT_RealValueXInterval;//FFT变换后X轴间隔单位值
	double  m_RealYRange;       //Y轴刻度范围
public:
	BOOL    controlRunDraw;//控制绘线标志
	double   *I_Data;
	double   *Q_Data;
	POINT   *pPointArray;
	POINT   *pPointArrayPower;
	POINT   *pPointArrayPowerIndex;
	POINT   *pPointArraySpectrum;
	POINT   *pPointArraySpectrumIndex;
	POINT   *pPointArrayIndexA;
	POINT   *pPointArrayIndexB;

private:
	CBrush  m_BkBrush;//黑色背景画刷
	CBrush  m_CurveBrush;//网格线画刷
	CRect	m_rectCurve;//波形图绘制区域
	CPen    m_PenDarkLine;//暗线画笔
	CPen    m_PenBrightLine;//明线画笔
	CFont   m_FontAxis;//显示字体
	CPen    m_PenCurvePower;//power曲线画笔
	CPen    m_PenCurveSpec;//频谱画笔
	CPen    m_PenCurveA;//曲线A画笔
	CPen    m_PenCurveB;//曲线A画笔

	BOOL    m_PowerFlg;//标记选择的波形类型0:功率; 
	BOOL    m_SpectrumFlg;//1:I+Q; 
	BOOL    m_IandQFlg;//2:I|Q; 
	BOOL    m_IorQFlg;//3:频谱
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	void    ValueTransform(CDC *pDC);//坐标与设备坐标的映射
	void    DrawGrid(CDC *pDC);//网格线
	void    DrawAxis(CDC *pDC);//刻度
	void    DrawXYtitle(CDC *pDC);//标题
	void    DrawCurveA(CDC *pDC);//曲线	
	void    Update();//更新
	void    runDraw();//控制绘制曲线
	void    PowerFlg();//选择曲线类型标记
	void    SpectrumFlg();
	void    IandQFlg();
	void    IorQFlg();
	void    AllClear();//清理内存
};


