// W.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "C.h"
#include "math.h"

// CC

IMPLEMENT_DYNAMIC(CC, CStatic)

CC::CC()
{
	controlRunDraw       = FALSE;//�����Ƿ���л������ߵı��
	m_ValueXRange        = 10;//X�����߸���10
	m_ValueYRange        = 6;//Y����߸���6

	m_ScaleValueYRange   = 0.000001;//Y����ʼֵ,0.000001
	m_ScaleValueXRange   = 0;//X����ʼֵ0
	m_ScaleValueXEnd     = 1.0;//X�����ֵ7(�������������Χ��
	m_ScaleValueYEnd     = 1;//Y�����ֵ0
	m_AllNum             =501;
	m_RealBaseYLine      = 0;
	m_RealValuenSize     = 0;//�������ߵ�����ʼ��

	m_BkBrush.CreateSolidBrush(RGB(0,0,0));//��������ɫ
	m_CurveBrush.CreateSolidBrush(RGB(0,0,0));//�����ߣ���ɫ
	m_PenDarkLine.CreatePen(PS_SOLID,0,RGB(0x55,0x55,0x55));//�����ߣ�����
	m_PenBrightLine.CreatePen(PS_SOLID,0,RGB(0xff,0xff,0xff));//�����ߣ�����

	//m_PenCurveA.CreatePen(PS_SOLID,1.5,RGB(0,128,0));//���߻���
	m_PenCurveA.CreatePen(PS_SOLID,2,RGB(0,128,0));//���߻���

	m_FontAxis.CreateFont(18,0,0,0,FW_THIN,FALSE,FALSE,FALSE,DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T("΢���ź�"));

}

CC::~CC()
{
}

BEGIN_MESSAGE_MAP(CC, CStatic)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CC ��Ϣ�������
BOOL CC::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CRect rect;
	GetClientRect(&rect);//��ȡ�û�����
	pDC->FillRect(&rect,&m_BkBrush);//Draw background�����ײ�
	return CStatic::OnEraseBkgnd(pDC);
}

void CC::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	CRect rc;
	GetClientRect(&rc);//��ȡ�û�����
	rc.InflateRect(0,0,0,0);//curve panel////curve panelȷ����ʾ��Ĵ�С��λ�ã��������ϡ��ҡ���
	m_rectCurve = rc;//��ʾ����
	m_rectCurve.InflateRect(-60,-35,-5,-40);//curve areaȷ����ɫ�����������Ĵ�С
	CDC *pDC = GetDC();
	ValueTransform(pDC);//����ת��
	DrawGrid(pDC);//��������
	DrawAxis(pDC);//���ƿ̶�
	DrawXYtitle(pDC);//���Ʊ���

	if(controlRunDraw)
		Update();//�������߻���

	// ��Ϊ��ͼ��Ϣ���� CStatic::OnPaint()
}

//����ת������
void CC::ValueTransform(CDC *pDC)
{
	m_RatioX = m_rectCurve.Width()/m_ValueXRange;//����X�����
	m_RatioY = m_rectCurve.Height()/m_ValueYRange;//����Y�����
	m_BaseXline = m_rectCurve.left;
	m_BaseYline = m_rectCurve.bottom;//XY�����
	m_RealValueXInterval = 1.0*m_rectCurve.Width()/(double)m_AllNum;////��ʵ���X������λֵ
}
//����������
void CC::DrawGrid(CDC *pDC)
{
	pDC->FillRect(&m_rectCurve,&m_CurveBrush);//��ˢ����������

	CPen *pOldPen = pDC->SelectObject(&m_PenDarkLine);//����m_PenDarkLineΪĬ�ϻ���
	pDC->MoveTo(m_rectCurve.left,m_rectCurve.top);
	pDC->LineTo(m_rectCurve.left,m_rectCurve.bottom);
	pDC->MoveTo(m_rectCurve.left,m_rectCurve.top);
	pDC->LineTo(m_rectCurve.right,m_rectCurve.top);//�ð��߹��������������Ա�Ч��
	
	int i;
	CString str;
	//	pDC->SelectObject(&m_PenGrid);//���õ�ǰ����Ϊm_PenGrid
	//	pDC->SelectClipRgn(&m_rgnCurve);//���õ�ǰĬ������Ϊm_rgnCurve
	pDC->MoveTo(m_rectCurve.left,m_BaseYline);
	pDC->LineTo(m_rectCurve.right,m_BaseYline);	//���ƺ������

	int nPosY;

	//Y��ĸ���С����
	for(i=1;i<=m_ValueYRange*2;i++)
	{
		if (m_rectCurve.top+i*m_RatioY*0.5<m_rectCurve.bottom)
		{
			pDC->MoveTo(m_BaseXline,m_rectCurve.top+i*m_RatioY*0.5);
			pDC->LineTo(m_BaseXline+4,m_rectCurve.top+i*m_RatioY*0.5);
		}
	}
	//X�Ḩ��С����
	for(i=1;i<=m_ValueXRange*2;i++)
	{
	if(m_rectCurve.left+0.5*i*m_RatioX<m_rectCurve.right)
	{
	pDC->MoveTo(m_rectCurve.left+0.5*i*m_RatioX,m_BaseYline-4);
	pDC->LineTo(m_rectCurve.left+0.5*i*m_RatioX,m_BaseYline);
	}
	}

	//������
	for(i=1;i<m_ValueYRange;i++)
	{
		nPosY = m_BaseYline-i*m_RatioY;
		if(nPosY<m_rectCurve.bottom)
		{
			pDC->MoveTo(m_rectCurve.left,nPosY);
			pDC->LineTo(m_rectCurve.right,nPosY);
		}
	}

	//������
	for(i=1;i<=m_ValueXRange;i++)
	{
		if(m_rectCurve.left+i*m_RatioX<m_rectCurve.right)
		{
			pDC->MoveTo(m_rectCurve.left+i*m_RatioX,m_rectCurve.top);
			pDC->LineTo(m_rectCurve.left+i*m_RatioX,m_rectCurve.bottom);
		}
	}

	//�����߹��������������Ա�Ч��	
	pDC->SelectObject(&m_PenBrightLine);
	pDC->MoveTo(m_rectCurve.right,m_rectCurve.top);
	pDC->LineTo(m_rectCurve.right,m_rectCurve.bottom);
	pDC->MoveTo(m_rectCurve.left,m_rectCurve.bottom);
	pDC->LineTo(m_rectCurve.right,m_rectCurve.bottom);

	pDC->SelectObject(&pOldPen);//�ͷŻ���
}

////��ֵ�̶ȱ��
void CC::DrawAxis(CDC *pDC)
{
	CFont *pOldFont;
	int j,nPosY;
	CString str;
	CString str_1;
	pOldFont = pDC->SelectObject(&m_FontAxis);//���õ�ǰ����Ĭ��ΪAxis���������壩
	pDC->SetTextColor(RGB(255,255,255));//����Ĭ����ɫΪ��ɫ��������ɫ��
	pDC->SetBkMode(TRANSPARENT);//����Ĭ������Ϊ͸��
	pDC->SetTextAlign(TA_RIGHT|TA_BASELINE);//����Ĭ���ı�ģʽ���Ҷ��룬���߶��룩
	nPosY = m_BaseYline;

	//������
	for(j=0;j<=m_ValueYRange;j++)
	{
		switch(j)
		{
		case 0:
			str="0.0001%";
			break;
		case 1:
			str="0.001%";
			break;
		case 2:
			str="0.01%";
			break;
		case 3:
			str="0.1%";
			break;
		case 4:
			str="1%";
			break;
		case 5:
			str="10%";
			break;
		case 6:
			str="100%";
			break;
		}
		pDC->TextOut(m_rectCurve.left-8,m_BaseYline-j*m_RatioY+6,str);
		//���ȿ̶ȵı�ʾ��ʽ

	}

	//������
	pDC->SetTextAlign(TA_LEFT|TA_TOP);//����Ĭ���ı�Ϊ����룬�ö�
	pDC->SetTextAlign(TA_CENTER|TA_TOP);

	//X����ʼֵ
	if (abs(m_ScaleValueXRange)<1&&m_ScaleValueXRange!=0)
		str.Format(_T("%.1f"),m_ScaleValueXRange);
	else
		str.Format(_T("%.0f"),m_ScaleValueXRange);
	pDC->TextOut(m_BaseXline+2,m_BaseYline+2,str);

	//X���յ�ֵ
	if (abs(m_ScaleValueXEnd)<1&&m_ScaleValueXEnd!=0)
		str.Format(_T("%.1fdB"),m_ScaleValueXEnd);
	else
		str.Format(_T("%.0fdB"),m_ScaleValueXEnd);
	pDC->TextOut(m_rectCurve.right-12,m_BaseYline+2,str);
	//X��̶ȱ�ʾ��ʽ

	pDC->SetTextAlign(TA_RIGHT|TA_TOP);
	str="--dB";
	if(m_RealValuenSize!=0)
		str.Format(_T("max: %.2fdB"),m_maxCCDFX);
	else
	str.Format(_T("max:")); //��ʼ��
	pDC->TextOut(m_rectCurve.right-m_rectCurve.Width()*0.25,m_rectCurve.bottom+2,str);//���һ��ֵ
	pDC->SelectObject(&pOldFont);//�ͷŵ�ǰ����

	m_RealBaseYLine = m_BaseYline-m_rectCurve.Height();//������ʵֵ����

}
////XY���������
void CC::DrawXYtitle(CDC *pDC)//XY���������
{
	CFont *pOldFontTitle;
	CString str;

	pOldFontTitle = pDC->SelectObject(&m_FontAxis);//���õ�ǰ����Ĭ��ΪAxis���������壩
	pDC->SetTextColor(RGB(0,255,0));//����Ĭ����ɫΪ
	pDC->SetBkMode(TRANSPARENT);//����Ĭ������Ϊ͸��
	pDC->SetTextAlign(TA_LEFT|TA_TOP);//����Ĭ���ı�Ϊ����룬�ö�
	pDC->SetTextAlign(TA_CENTER|TA_TOP);

	//X�����
	str="(Power/Avg.Power)/dB";
	pDC->TextOut(m_BaseXline+m_rectCurve.Width()/2,m_BaseYline+17,str);
	//ͷ������
	pOldFontTitle = pDC->SelectObject(&m_FontAxis);//���õ�ǰ����Ĭ��ΪAxis���������壩
	pDC->SetTextColor(RGB(0,128,0));//����Ĭ����ɫΪ
	str="Wave CCDF";
	pDC->TextOut(m_BaseXline+10,m_BaseYline-m_rectCurve.Height()-24,str);
}
//���Ʋ��κ���
void CC::DrawCurveA(CDC *pDC)
{
	CPen *pOldPen = pDC->SelectObject(&m_PenCurveA);//���õ�ǰ����Ϊm_PenCurveA
	pPointArrayCCDFIndex =(POINT *) new POINT[m_AllNum];//�趨һ������
	//pPointArrayCCDFIndex[0].x=m_BaseXline;
	//pPointArrayCCDFIndex[0].y=m_RealBaseYLine;
	for (int flg=0;flg<m_AllNum;flg++)
	{
		pPointArrayCCDFIndex[flg].x = m_BaseXline+flg*m_RealValueXInterval;
		pPointArrayCCDFIndex[flg].y = m_RealBaseYLine+(-log10(pPointArrayCCDF[flg]))*(m_rectCurve.Height()/(double)m_ValueYRange);
	
		if(pPointArrayCCDFIndex[flg].y<m_RealBaseYLine)
			pPointArrayCCDFIndex[flg].y=m_RealBaseYLine+m_rectCurve.Height();
	}
	
	pDC->Polyline(pPointArrayCCDFIndex,m_AllNum);//��������ߵĵ�ȫ�����Ƴ���
	pDC->SelectObject(pOldPen);//�ͷŻ���
	pDC->SelectClipRgn(NULL);
}

void CC::Update()
{
	CClientDC dc(this);
	CRect rect;
	GetClientRect(&rect);//��ȡ�ͻ�����
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);//����ǰ��������Ϊλͼ����memDC��
	CBitmap bitmap,*pOldBmp;
	bitmap.CreateCompatibleBitmap(&dc,rect.Width(),rect.Height());//����λͼ&dc����ʼ������
	pOldBmp = memDC.SelectObject(&bitmap);//��λͼbitmap���ݸ�memDC
	DrawGrid(&memDC);//���û�������
	DrawAxis(&memDC);//���û��ƿ̶�
	DrawXYtitle(&memDC);//����
	DrawCurveA(&memDC);//��������

	dc.BitBlt(m_rectCurve.left,m_rectCurve.top,m_rectCurve.Width(),m_rectCurve.Height(),
		&memDC,m_rectCurve.left,m_rectCurve.top,SRCCOPY);//��λͼ���Ƶ�dc��
	memDC.SelectObject(pOldBmp);//�ͷŵ�ǰλͼ	
}
//���������Ƿ���л��Ƶ��ⲿ�ӿں���
void  CC::runDraw()
{
	controlRunDraw = TRUE;
	Invalidate();
}