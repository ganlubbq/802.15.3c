#pragma once

class CW : public CStatic
{
	DECLARE_DYNAMIC(CW)

public:
	CW();
	virtual ~CW();
public:
	double  m_ValueXRange;//����X��ķ�Χ��С
	double  m_ValueYRange;//����Y��ķ�Χ��С
	double  m_AllNum;//X���ܵ���

	double  m_RatioX;//X��̶Ⱥ�ʵ����ʾ�̶ȱ���
	double  m_RatioY;//Y��̶ȱ���
	int     m_BaseXline;//X��Ļ���ֵ
	int     m_BaseYline;//Y��Ļ���ֵ
	double  m_ScaleValueXRange;//�̶�ֵX����ʼֵ
	double  m_ScaleValueYRange;//�̶�ֵY����ʼֵ
	double  m_ScaleValueXEnd;//�̶�ֵX�����ֵ
	double  m_ScaleValueYEnd;//�̶�ֵY�����ֵ
	double  m_dDimX;
	double  m_dDimY;//���ȿ̶ȼ����λ

	int     m_RealBaseYLine;//��ʵֵY����
	int     m_RealBaseYLine2;//��ʵֵY���ߣ�I|Q��������
	int     m_RealValuenSize;//��ʵ���ε���
	double  m_RealValueXInterval;//��ʵ���X������λֵ
public:
	BOOL    controlRunDraw;//���ƻ��߱�־
	POINT   *pPointArray;//���յ�
	POINT   *pPointArrayPower;
	POINT   *pPointArrayPowerIndex;
	POINT   *pPointArraySpectrum;
	POINT   *pPointArraySpectrumIndex;
	POINT   *pPointArrayIndexA;
	POINT   *pPointArrayIndexB;

private:
	CBrush  m_BkBrush;//��ɫ������ˢ
	CBrush  m_CurveBrush;//�����߻�ˢ
	CRect	m_rectCurve;//��������
	CPen    m_PenDarkLine;//���߻���
	CPen    m_PenBrightLine;//���߻���
	CFont   m_FontAxis;//��ʾ����
	CPen    m_PenCurvePower;//power���߻���
	CPen    m_PenCurveSpec;//Ƶ�׻���
	CPen    m_PenCurveA;//����A����
	CPen    m_PenCurveB;//����A����

	BOOL    m_PowerFlg;//���ѡ��Ĳ�������0:����; 
	BOOL    m_SpectrumFlg;//1:I+Q; 
	BOOL    m_IandQFlg;//2:I|Q; 
	BOOL    m_IorQFlg;//3:Ƶ��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	void    ValueTransform(CDC *pDC);//�������豸�����ӳ��
	void    DrawGrid(CDC *pDC);//������
	void    DrawAxis(CDC *pDC);//�̶�
	void    DrawXYtitle(CDC *pDC);//����
	void    DrawCurveA(CDC *pDC);//����	
	void    Update();//����
	void    runDraw();//���ƻ�������
	void    PowerFlg();//ѡ���������ͱ��
	void    SpectrumFlg();
	void    IandQFlg();
	void    IorQFlg();
	void    AllClear();//�����ڴ�
};


