// W.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "W.h"
#include "math.h"

// CW

IMPLEMENT_DYNAMIC(CW, CStatic)

CW::CW()
{
	
	m_PowerFlg           = FALSE;//���ѡ��Ĳ�������0:����; 1:I+Q; 2:I|Q; 3:Ƶ��
	m_SpectrumFlg        = FALSE;
	m_IandQFlg           = FALSE;
	m_IorQFlg            = FALSE;

	controlRunDraw       = FALSE;
	m_AllNum             = 10000;//���е���
	m_ValueXRange        = 12;//X�����߸���
	m_ValueYRange        = 6;//Y����߸���

	pPointArray          = NULL;//���յ�
	pPointArrayPower     = NULL;
	pPointArrayPowerIndex= NULL;
	pPointArraySpectrum  = NULL;
	pPointArraySpectrumIndex  = NULL;
	pPointArrayIndexA    = NULL;
	pPointArrayIndexB    = NULL;

	m_ScaleValueYRange   = -50;//Y����ʼֵ
	m_ScaleValueXRange   = 0;//X����ʼֵ
	m_ScaleValueXEnd     = 0;//X�����ֵ
	m_ScaleValueYEnd     = 0;//Y�����ֵ
	m_dDimX	             = 1.0;//x��̶ȵ�λ
	m_dDimY	             = 10.0;//y��̶ȵ�λ

	m_RealBaseYLine      = 0;//Y����ʵֵ���߳�ʼ��
	m_RealBaseYLine2     = 0;
	m_RealValuenSize     = 0;//�������ߵ�����ʼ��

	m_BkBrush.CreateSolidBrush(RGB(0,0,0));//��������ɫ
	m_CurveBrush.CreateSolidBrush(RGB(0,0,0));//�����ߣ���ɫ
	m_PenDarkLine.CreatePen(PS_SOLID,0,RGB(0x55,0x55,0x55));//�����ߣ�����
	m_PenBrightLine.CreatePen(PS_SOLID,0,RGB(0xff,0xff,0xff));//�����ߣ�����

	m_PenCurveA.CreatePen(PS_SOLID,1,RGB(0,0,255));//���߻���
	m_PenCurveB.CreatePen(PS_SOLID,1,RGB(200,100,0));//���߻���
	m_PenCurvePower.CreatePen(PS_SOLID,1,RGB(220,220,0));//Power����
	m_PenCurveSpec.CreatePen(PS_SOLID,1,RGB(0,128,0));//Ƶ�׻���

	m_FontAxis.CreateFont(15,0,0,0,FW_THIN,FALSE,FALSE,FALSE,DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T("Arial"));

}

CW::~CW()
{
}

BEGIN_MESSAGE_MAP(CW, CStatic)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CW ��Ϣ�������

BOOL CW::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CRect rect;
	GetClientRect(&rect);//��ȡ�û�����
	pDC->FillRect(&rect,&m_BkBrush);//Draw background�����ײ�

	return CStatic::OnEraseBkgnd(pDC);
}

void CW::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	CRect rc;
	GetClientRect(&rc);//��ȡ�û�����
	rc.InflateRect(0,0,0,0);//curve panel////curve panelȷ����ʾ��Ĵ�С��λ�ã��������ϡ��ҡ���
	m_rectCurve = rc;//��ʾ����
	m_rectCurve.InflateRect(-60,-40,-5,-30);//curve areaȷ����ɫ�����������Ĵ�С
	CDC *pDC = GetDC();
	ValueTransform(pDC);//����ת��
	DrawGrid(pDC);//����
	DrawAxis(pDC);//�̶�
	DrawXYtitle(pDC);//����
	if (controlRunDraw)
	{
		//CPen pen(PS_SOLID, 0, RGB(255,255,0));
		//pDC->SelectObject(&pen);	
		//pDC->MoveTo(m_rectCurve.left, m_rectCurve.top+m_rectCurve.Height()/m_ValueYRange);
		//pDC->LineTo(m_rectCurve.right, m_rectCurve.top+m_rectCurve.Height()/m_ValueYRange);
		//DrawCurveA(pDC);//����
		Update();
	}

	// ��Ϊ��ͼ��Ϣ���� CStatic::OnPaint()
}

//����ת������
void CW::ValueTransform(CDC *pDC)
{
	m_RatioX = m_rectCurve.Width()/m_ValueXRange;//����X�����
	m_RatioY = m_rectCurve.Height()/m_ValueYRange;//����Y�����
	m_BaseXline = m_rectCurve.left;
	m_BaseYline = m_rectCurve.bottom;//XY�����
	m_RealValueXInterval = 1.0*m_rectCurve.Width()/(double)m_AllNum;////��ʵ���X������λֵ
}
//�����������
void CW::DrawGrid(CDC *pDC)
{
	CPen *pOldPen = pDC->SelectObject(&m_PenDarkLine);//����m_PenDarkLineΪĬ�ϻ���	

	if(m_PowerFlg||m_SpectrumFlg)
	{
		int i;
		pDC->MoveTo(m_rectCurve.left,m_rectCurve.top);
		pDC->LineTo(m_rectCurve.left,m_rectCurve.bottom);
		pDC->MoveTo(m_rectCurve.left,m_rectCurve.top);
		pDC->LineTo(m_rectCurve.right,m_rectCurve.top);//�ð��߹��������������Ա�Ч��

		pDC->MoveTo(m_rectCurve.left,m_rectCurve.bottom);
		pDC->LineTo(m_rectCurve.right,m_rectCurve.bottom);	//���ƺ������

		int nPosY;

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

		//�����߹��������������Ա�Ч��	
		pDC->SelectObject(&m_PenBrightLine);
		pDC->MoveTo(m_rectCurve.right,m_rectCurve.top);
		pDC->LineTo(m_rectCurve.right,m_rectCurve.bottom);
		pDC->MoveTo(m_rectCurve.left,m_rectCurve.bottom);
		pDC->LineTo(m_rectCurve.right,m_rectCurve.bottom);

		pDC->SelectObject(&pOldPen);//�ͷŻ���
	}
	else if (m_IandQFlg)
	{
		int m;
		pDC->MoveTo(m_rectCurve.left,m_rectCurve.top);
		pDC->LineTo(m_rectCurve.left,m_rectCurve.bottom);
		pDC->MoveTo(m_rectCurve.left,m_rectCurve.top);
		pDC->LineTo(m_rectCurve.right,m_rectCurve.top);//�ð��߹��������������Ա�Ч��

		pDC->MoveTo(m_rectCurve.left,m_BaseYline);
		pDC->LineTo(m_rectCurve.right,m_BaseYline);	//���ƺ������

		int nPosYM;

		//Y��ĸ���С����
		for(m=1;m<=7;m++)
		{
			if (m_rectCurve.top+m*(m_rectCurve.Height()/8)<m_rectCurve.bottom)
			{
				pDC->MoveTo(m_BaseXline,m_BaseYline-m*(m_rectCurve.Height()/8)-2);
				pDC->LineTo(m_BaseXline+4,m_BaseYline-m*(m_rectCurve.Height()/8)-2);
			}
		}
		//X�Ḩ��С����
		for(m=1;m<=m_ValueXRange*2;m++)
		{
			if(m_rectCurve.left+0.5*m*m_RatioX<m_rectCurve.right)
			{
				pDC->MoveTo(m_rectCurve.left+0.5*m*m_RatioX,m_BaseYline-6);
				pDC->LineTo(m_rectCurve.left+0.5*m*m_RatioX,m_BaseYline);
			}
		}

		//������
		for(m=1;m<4;m++)
		{
			nPosYM = m_BaseYline-m*(m_rectCurve.Height()/4);
			if(nPosYM<m_rectCurve.bottom)
			{
				pDC->MoveTo(m_rectCurve.left,nPosYM);
				pDC->LineTo(m_rectCurve.right,nPosYM);
			}
		}

		//������
		for(m=1;m<=m_ValueXRange;m++)
		{
			if(m_rectCurve.left+m*m_RatioX<m_rectCurve.right)
			{
				pDC->MoveTo(m_rectCurve.left+m*m_RatioX,m_rectCurve.top);
				pDC->LineTo(m_rectCurve.left+m*m_RatioX,m_rectCurve.bottom);
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
	else
	{
		//�²�����
		pDC->MoveTo(m_BaseXline,m_BaseYline);
		pDC->LineTo(m_BaseXline,m_BaseYline-m_rectCurve.Height()/2+10);
		pDC->MoveTo(m_BaseXline,m_BaseYline-m_rectCurve.Height()/2+10);
		pDC->LineTo(m_BaseXline+m_rectCurve.Width(),m_BaseYline-m_rectCurve.Height()/2+10);//�ð��߹��������������Ա�Ч��

		pDC->MoveTo(m_rectCurve.left,m_BaseYline);
		pDC->LineTo(m_rectCurve.right,m_BaseYline);	//���ƺ������

		//�ϲ�����
		pDC->MoveTo(m_BaseXline,m_BaseYline-m_rectCurve.Height());
		pDC->LineTo(m_BaseXline,m_BaseYline-m_rectCurve.Height()/2-20);
		pDC->MoveTo(m_BaseXline,m_BaseYline-m_rectCurve.Height());
		pDC->LineTo(m_BaseXline+m_rectCurve.Width(),m_BaseYline-m_rectCurve.Height());//�ð��߹��������������Ա�Ч��

		pDC->MoveTo(m_rectCurve.left,m_BaseYline-m_rectCurve.Height()/2-20);
		pDC->LineTo(m_rectCurve.right,m_BaseYline-m_rectCurve.Height()/2-20);	//���ƺ������*/

		//�²����� ������
		int nPosY;
		int i;
		for(i=1;i<2;i++)
		{
			nPosY = m_BaseYline-i*m_RatioY*1.5+5;
			if(nPosY<m_rectCurve.bottom)
			{
				pDC->MoveTo(m_rectCurve.left,nPosY);
				pDC->LineTo(m_rectCurve.right,nPosY);
			}
		}

		//�²����� ������
		for(i=1;i<=m_ValueXRange;i++)
		{
			if(m_rectCurve.left+i*m_RatioX<m_rectCurve.right)
			{
				pDC->MoveTo(m_rectCurve.left+i*m_RatioX,m_BaseYline);
				pDC->LineTo(m_rectCurve.left+i*m_RatioX,m_BaseYline-m_rectCurve.Height()/2+10);
			}
		}

		//�ϲ����� ������
		int nPosYB;
		int j;
		for(j=1;j<2;j++)
		{
			nPosYB = m_BaseYline-m_rectCurve.Height()/2-20-j*m_RatioY*1.5+10;
			if(nPosY<m_rectCurve.bottom)
			{
				pDC->MoveTo(m_rectCurve.left,nPosYB);
				pDC->LineTo(m_rectCurve.right,nPosYB);
			}
		}
		//�ϲ����� ������
		for(j=1;j<=m_ValueXRange;j++)
		{
			if(m_rectCurve.left+j*m_RatioX<m_rectCurve.right)
			{
				pDC->MoveTo(m_rectCurve.left+j*m_RatioX,m_BaseYline-m_rectCurve.Height()/2-20);
				pDC->LineTo(m_rectCurve.left+j*m_RatioX,m_BaseYline-m_rectCurve.Height());
			}
		}

		//�����߹��������������Ա�Ч��	
		//�²�����
		pDC->SelectObject(&m_PenBrightLine);
		pDC->MoveTo(m_rectCurve.right,m_BaseYline-m_rectCurve.Height()/2+10);
		pDC->LineTo(m_rectCurve.right,m_rectCurve.bottom);
		pDC->MoveTo(m_rectCurve.left,m_rectCurve.bottom);
		pDC->LineTo(m_rectCurve.right,m_rectCurve.bottom);
		//�ϲ�����
		pDC->SelectObject(&m_PenBrightLine);
		pDC->MoveTo(m_rectCurve.right,m_BaseYline-m_rectCurve.Height()/2-20);
		pDC->LineTo(m_rectCurve.right,m_rectCurve.top);
		pDC->MoveTo(m_rectCurve.left,m_BaseYline-m_rectCurve.Height()/2-20);
		pDC->LineTo(m_rectCurve.right,m_BaseYline-m_rectCurve.Height()/2-20);	

		pDC->SelectObject(&pOldPen);//�ͷŻ���
	}
}

////��ֵ�̶ȱ�Ǻ���
void CW::DrawAxis(CDC *pDC)
{
	CFont *pOldFont;
	int j,nPosY;
	CString str;
	pOldFont = pDC->SelectObject(&m_FontAxis);//���õ�ǰ����Ĭ��ΪAxis���������壩
	pDC->SetTextColor(RGB(255,255,255));//����Ĭ����ɫΪ��ɫ��������ɫ��
	pDC->SetBkMode(TRANSPARENT);//����Ĭ������Ϊ͸��
	pDC->SetTextAlign(TA_RIGHT|TA_BASELINE);//����Ĭ���ı�ģʽ���Ҷ��룬���߶��룩

	if (m_PowerFlg)
	{
		//Y����ʼֵ
		if (abs(m_ScaleValueYRange)<1)
			str.Format(_T("%.1fdB"),m_ScaleValueYRange);
		else
			str.Format(_T("%.0fdB"),m_ScaleValueYRange);
		pDC->TextOut(m_BaseXline-6,m_BaseYline,str);

		//������
		for(j=1;j<=m_ValueYRange;j++)
		{
			if(m_BaseYline-j*m_RatioY<=m_rectCurve.bottom)
			{
				if(abs(m_dDimY)<1)
					str.Format(_T("%.1fdB"),j*m_dDimY+m_ScaleValueYRange);
				else if(m_dDimY<1000)
					str.Format(_T("%.0fdB"),j*m_dDimY+m_ScaleValueYRange);
				else
					str.Format(_T("%.0f"),(j*m_dDimY+m_ScaleValueYRange)/1000);
				pDC->TextOut(m_rectCurve.left-6,m_BaseYline-j*m_RatioY+6,str);
			}//���ȿ̶ȵı�ʾ��ʽ
			if (j*m_dDimY+m_ScaleValueYRange==0)//�ж���ʵֵ�Ļ���
			{
				m_RealBaseYLine = m_BaseYline-j*m_RatioY;
			}
		}

		//������
		//X����ʼֵ
		if (abs(m_ScaleValueXRange)<1&&m_ScaleValueXRange!=0)
			str.Format(_T("%.1f"),m_ScaleValueXRange);
		else
			str.Format(_T("%.0f"),m_ScaleValueXRange);
		pDC->TextOut(m_BaseXline+5,m_BaseYline+15,str);
	}
	else if (m_SpectrumFlg)
	{
		//Y����ʼֵ
		if (abs(m_ScaleValueYRange)<1)
			str.Format(_T("%.1fdB"),m_ScaleValueYRange-10);
		else
			str.Format(_T("%.0fdB"),m_ScaleValueYRange-10);
		pDC->TextOut(m_BaseXline-6,m_BaseYline,str);

		//������
		for(j=1;j<=m_ValueYRange;j++)
		{
			if(m_BaseYline-j*m_RatioY<=m_rectCurve.bottom)
			{
				if(abs(m_dDimY)<1)
					str.Format(_T("%.1fdB"),j*m_dDimY-60);
				else if(m_dDimY<1000)
					str.Format(_T("%.0fdB"),j*m_dDimY-60);
				else
					str.Format(_T("%.0f"),(j*m_dDimY-60)/1000);
				pDC->TextOut(m_rectCurve.left-6,m_BaseYline-j*m_RatioY+6,str);
			}//���ȿ̶ȵı�ʾ��ʽ
			if (j*m_dDimY+m_ScaleValueYRange-10==0)//�ж���ʵֵ�Ļ���
			{
				m_RealBaseYLine = m_BaseYline-j*m_RatioY;
			}
		}

		//������
		//X����ʼֵ
		if (abs(m_ScaleValueXRange)<1&&m_ScaleValueXRange!=0)
			str.Format(_T("%.1f"),m_ScaleValueXRange);
		else
			str.Format(_T("%.0f"),m_ScaleValueXRange);
		pDC->TextOut(m_BaseXline+5,m_BaseYline+15,str);
	}
	else if (m_IandQFlg)
	{
		//������
		pDC->TextOut(m_BaseXline-6,m_BaseYline,_T("-0.4"));
		pDC->TextOut(m_BaseXline-6,m_BaseYline-m_rectCurve.Height()/4+5,_T("-0.2"));
		pDC->TextOut(m_BaseXline-6,m_BaseYline-2*(m_rectCurve.Height()/4)+5,_T("0"));
		pDC->TextOut(m_BaseXline-6,m_BaseYline-3*(m_rectCurve.Height()/4)+5,_T("0.2"));
		pDC->TextOut(m_BaseXline-6,m_BaseYline-m_rectCurve.Height()+5,_T("0.4"));
		//������
		//X����ʼֵ
		if (abs(m_ScaleValueXRange)<1&&m_ScaleValueXRange!=0)
			str.Format(_T("%.1f"),m_ScaleValueXRange);
		else
			str.Format(_T("%.0f"),m_ScaleValueXRange);
		pDC->TextOut(m_BaseXline+5,m_BaseYline+15,str);

		//Y����ʵֵ����
		m_RealBaseYLine = m_BaseYline-2*(m_rectCurve.Height()/4)+5;
	}
	else
	{
		nPosY = m_BaseYline-m_rectCurve.Height()/2-20;

		//�²�Q������
		pDC->TextOut(m_BaseXline-6,m_BaseYline,_T("-0.5"));
		pDC->TextOut(m_BaseXline-6,m_BaseYline-(m_rectCurve.Height()/2-20)/2,_T("0"));
		pDC->TextOut(m_BaseXline-6,m_BaseYline-m_rectCurve.Height()/2+20,_T("0.5"));

		//�ϲ�I������
		pDC->TextOut(m_BaseXline-6,nPosY,_T("-0.5"));
		pDC->TextOut(m_BaseXline-6,nPosY-(m_rectCurve.Height()/2-25)/2,_T("0"));
		pDC->TextOut(m_BaseXline-6,nPosY-m_rectCurve.Height()/2+25,_T("0.5"));

		//������
		//X����ʼֵ
		if (abs(m_ScaleValueXRange)<1&&m_ScaleValueXRange!=0)
			str.Format(_T("%.1f"),m_ScaleValueXRange);
		else
			str.Format(_T("%.0f"),m_ScaleValueXRange);
		pDC->TextOut(m_BaseXline+5,m_BaseYline+15,str);

		//Y����ʵֵ����
		m_RealBaseYLine = m_BaseYline-(m_rectCurve.Height()/2-20)/2;
		m_RealBaseYLine2 = nPosY-(m_rectCurve.Height()/2-25)/2;
	}
	
}

////XY���������
void CW::DrawXYtitle(CDC *pDC)//XY���������
{
	CFont *pOldFont;
	CString str;
	CString Titalstr;
	CString XMaxstr;
	CString Otherstr;

	pOldFont = pDC->SelectObject(&m_FontAxis);//���õ�ǰ����Ĭ��ΪAxis���������壩
	pDC->SetTextColor(RGB(255,255,255));//����Ĭ����ɫΪ��������ɫ��
	pDC->SetBkMode(TRANSPARENT);//����Ĭ������Ϊ͸��
	pDC->SetTextAlign(TA_LEFT|TA_TOP);//����Ĭ���ı�Ϊ����룬�ö�
	pDC->SetTextAlign(TA_CENTER|TA_TOP);

	if (m_PowerFlg)
	{
		//X�����
		XMaxstr.Format(_T("maxNum: %d"),10000);
		pDC->TextOut(m_rectCurve.right-42,m_rectCurve.bottom+2,XMaxstr);//���һ��ֵ
	}
	else if (m_SpectrumFlg)
	{
		XMaxstr.Format(_T("maxNum: %d"),10000);
		CString Center=_T("--");
		pDC->TextOut(m_BaseXline+m_rectCurve.Width()/2,m_BaseYline-m_rectCurve.Height()-20,Center);//���һ��ֵ
		pDC->TextOut(m_rectCurve.right-42,m_rectCurve.bottom+2,XMaxstr);//���һ��ֵ
	}
	else if (m_IandQFlg)
	{
		XMaxstr.Format(_T("maxNum: %d"),10000);
		pDC->TextOut(m_rectCurve.right-42,m_rectCurve.bottom+2,XMaxstr);//���һ��ֵ
	}
	else
	{
		XMaxstr.Format(_T("maxNum: %d"),10000);
		pDC->TextOut(m_rectCurve.right-42,m_rectCurve.bottom+2,XMaxstr);//���һ��ֵ
	}
	pOldFont = pDC->SelectObject(&m_FontAxis);//���õ�ǰ����Ĭ��ΪAxis���������壩
	pDC->SetTextColor(RGB(0,255,0));
	str.Format(_T("Points: %d"),m_RealValuenSize);
	pDC->TextOut(m_BaseXline+m_rectCurve.Width()-60,m_BaseYline-m_rectCurve.Height()-20,str);

	if (m_PowerFlg)
	{
		//X�����
		pOldFont = pDC->SelectObject(&m_FontAxis);//���õ�ǰ����Ĭ��ΪAxis���������壩
		pDC->SetTextColor(RGB(255,255,0));//����Ĭ����ɫΪ��������ɫ��
		Titalstr=_T("������");
		pDC->TextOut(m_BaseXline+20,m_BaseYline-m_rectCurve.Height()-25,Titalstr);
	}
	else if (m_SpectrumFlg)
	{
		pOldFont = pDC->SelectObject(&m_FontAxis);//���õ�ǰ����Ĭ��ΪAxis���������壩
		pDC->SetTextColor(RGB(0,128,0));//����Ĭ����ɫΪ��������ɫ��
		Titalstr=_T("Ƶ��");
		pDC->TextOut(m_BaseXline+20,m_BaseYline-m_rectCurve.Height()-25,Titalstr);
	}
	else if (m_IandQFlg)
	{
		pOldFont = pDC->SelectObject(&m_FontAxis);//���õ�ǰ����Ĭ��ΪAxis���������壩
		pDC->SetTextColor(RGB(0,0,255));//����Ĭ����ɫΪ��������ɫ��
		Titalstr=_T("I");
		pDC->TextOut(m_BaseXline+10,m_BaseYline-m_rectCurve.Height()-20,Titalstr);

		pOldFont = pDC->SelectObject(&m_FontAxis);//���õ�ǰ����Ĭ��ΪAxis���������壩
		pDC->SetTextColor(RGB(255,255,255));//����Ĭ����ɫΪ��������ɫ��
		Titalstr=_T("+");
		pDC->TextOut(m_BaseXline+20,m_BaseYline-m_rectCurve.Height()-20,Titalstr);

		pOldFont = pDC->SelectObject(&m_FontAxis);//���õ�ǰ����Ĭ��ΪAxis���������壩
		pDC->SetTextColor(RGB(200,100,0));//����Ĭ����ɫΪ��������ɫ��
		Titalstr=_T("Q");
		pDC->TextOut(m_BaseXline+30,m_BaseYline-m_rectCurve.Height()-20,Titalstr);
	}
	else
	{
		pOldFont = pDC->SelectObject(&m_FontAxis);//���õ�ǰ����Ĭ��ΪAxis���������壩
		pDC->SetTextColor(RGB(0,0,255));//����Ĭ����ɫΪ��������ɫ��
		Titalstr=_T("I");
		pDC->TextOut(m_BaseXline+10,m_BaseYline-m_rectCurve.Height()-20,Titalstr);

		pOldFont = pDC->SelectObject(&m_FontAxis);//���õ�ǰ����Ĭ��ΪAxis���������壩
		pDC->SetTextColor(RGB(255,255,255));//����Ĭ����ɫΪ��������ɫ��
		Titalstr=_T("|");
		pDC->TextOut(m_BaseXline+20,m_BaseYline-m_rectCurve.Height()-20,Titalstr);

		pOldFont = pDC->SelectObject(&m_FontAxis);//���õ�ǰ����Ĭ��ΪAxis���������壩
		pDC->SetTextColor(RGB(200,100,0));//����Ĭ����ɫΪ��������ɫ��
		Titalstr=_T("Q");
		pDC->TextOut(m_BaseXline+30,m_BaseYline-m_rectCurve.Height()-20,Titalstr);
	}

}

//���Ʋ��κ���
void CW::DrawCurveA(CDC *pDC)
{
	//�����׻��ƹ���
	if (m_PowerFlg)
	{
		CPen *pOldPen = pDC->SelectObject(&m_PenCurvePower);//���õ�ǰ����Ϊm_PenCurveA

		pPointArrayPowerIndex =(POINT *) new POINT[2*m_AllNum];//�趨һ������
		for (int i=0;i<=2*m_RealValuenSize;i++)
		{
			pPointArrayPowerIndex[i].x = m_BaseXline+0.5*i*m_RealValueXInterval;
			pPointArrayPowerIndex[i].y = m_RealBaseYLine+pPointArrayPower[i].y*(-m_rectCurve.Height()/60)/10000;
			if (m_RealBaseYLine+pPointArrayPower[i].y*(-m_rectCurve.Height()/60)/10000 < m_RealBaseYLine-m_rectCurve.Height()/6)
			{
				pPointArrayPowerIndex[i].y=m_RealBaseYLine-m_rectCurve.Height()/6;
			}
			if (m_RealBaseYLine+pPointArrayPower[i].y*(-m_rectCurve.Height()/60)/10000 > m_RealBaseYLine+5*m_rectCurve.Height()/6)
			{
				pPointArrayPowerIndex[i].y=m_RealBaseYLine+5*m_rectCurve.Height()/6;
			}
		}
		for (int j=2*m_RealValuenSize+1;j<=2*m_AllNum;j++)
		{
			pPointArrayPowerIndex[j].x = m_BaseXline+0.5*j*m_RealValueXInterval;
			pPointArrayPowerIndex[j].y = m_RealBaseYLine-m_rectCurve.Height()/6;
		}
		pDC->Polyline(pPointArrayPowerIndex,2*m_AllNum);//��������ߵĵ�ȫ�����Ƴ���
		pDC->SelectObject(pOldPen);//�ͷŻ���
		pDC->SelectClipRgn(NULL);

	}
	//Ƶ�׻��ƹ���
	else if (m_SpectrumFlg)
	{
		CPen *pOldPen = pDC->SelectObject(&m_PenCurveSpec);//���õ�ǰ����Ϊm_PenCurveA

		pPointArraySpectrumIndex =(POINT *) new POINT[m_AllNum];//�趨һ������

		for (int i=0;i<=m_RealValuenSize;i++)
		{
			pPointArraySpectrumIndex[i].x = m_BaseXline+i*m_RealValueXInterval;
			pPointArraySpectrumIndex[i].y = m_RealBaseYLine+pPointArraySpectrum[i].y*(-m_rectCurve.Height()/60)/10000;

			if (m_RealBaseYLine+pPointArraySpectrum[i].y*(-m_rectCurve.Height()/60)/10000 < m_RealBaseYLine)
			{
				pPointArraySpectrumIndex[i].y=m_RealBaseYLine;
			}
			if (m_RealBaseYLine+pPointArraySpectrum[i].y*(-m_rectCurve.Height()/60)/10000 > m_RealBaseYLine+m_rectCurve.Height())
			{
				pPointArraySpectrumIndex[i].y=m_RealBaseYLine+m_rectCurve.Height();
			}
		}
		for (int j=m_RealValuenSize+1;j<m_AllNum;j++)
		{
			pPointArraySpectrumIndex[j].x = m_BaseXline+j*m_RealValueXInterval;
			pPointArraySpectrumIndex[j].y = m_RealBaseYLine;
		}
		pDC->Polyline(pPointArraySpectrumIndex,m_AllNum);//��������ߵĵ�ȫ�����Ƴ���
		pDC->SelectObject(pOldPen);//�ͷŻ���
		pDC->SelectClipRgn(NULL);
	}
	//I+Q���ƹ���
	else if (m_IandQFlg)
	{
		CPen *pOldPen = pDC->SelectObject(&m_PenCurveA);//���õ�ǰ����Ϊm_PenCurveA

		pPointArrayIndexA =(POINT *) new POINT[m_AllNum];//�趨һ������

		for (int i=0;i<=m_RealValuenSize;i++)
		{
			pPointArrayIndexA[i].x = m_BaseXline+i*m_RealValueXInterval;
			pPointArrayIndexA[i].y = m_RealBaseYLine-5+2.5*pPointArray[i].x*(-m_rectCurve.Height()/2)/10000;
		}
		for (int m=m_RealValuenSize;m<=m_AllNum;m++)
		{
			pPointArrayIndexA[m].x = m_BaseXline+m*m_RealValueXInterval;
			pPointArrayIndexA[m].y = m_RealBaseYLine-5;
		}
		pDC->Polyline(pPointArrayIndexA,m_AllNum);//��������ߵĵ�ȫ�����Ƴ���
		pDC->SelectObject(pOldPen);//�ͷŻ���
		pDC->SelectClipRgn(NULL);

		CPen *pOldPenB = pDC->SelectObject(&m_PenCurveB);//���õ�ǰ����Ϊm_PenCurveA

		pPointArrayIndexB =(POINT *) new POINT[m_AllNum];//�趨һ������
		for (int j=0;j<=m_RealValuenSize;j++)
		{
			pPointArrayIndexB[j].x = m_BaseXline+j*m_RealValueXInterval;
			pPointArrayIndexB[j].y = m_RealBaseYLine-5+2.5*pPointArray[j].y*(-m_rectCurve.Height()/2)/10000;
		}
		for (int n=m_RealValuenSize;n<=m_AllNum;n++)
		{
			pPointArrayIndexB[n].x = m_BaseXline+n*m_RealValueXInterval;
			pPointArrayIndexB[n].y = m_RealBaseYLine-5;
		}
		pDC->Polyline(pPointArrayIndexB,m_AllNum);//��������ߵĵ�ȫ�����Ƴ���
		pDC->SelectObject(pOldPenB);//�ͷŻ���
		pDC->SelectClipRgn(NULL);
	}
	//I|Q���ƹ���
	else
	{
		CPen *pOldPen = pDC->SelectObject(&m_PenCurveA);//���õ�ǰ����Ϊm_PenCurveA

		pPointArrayIndexA =(POINT *) new POINT[m_AllNum];//�趨һ������

		for (int i=0;i<=m_RealValuenSize;i++)
		{
			pPointArrayIndexA[i].x = m_BaseXline+i*m_RealValueXInterval;
			pPointArrayIndexA[i].y = m_RealBaseYLine2-5+2*pPointArray[i].x*(-m_rectCurve.Height()/4-5)/10000;
		}
		for (int m=m_RealValuenSize;m<=m_AllNum;m++)
		{
			pPointArrayIndexA[m].x = m_BaseXline+m*m_RealValueXInterval;
			pPointArrayIndexA[m].y = m_RealBaseYLine2-5;
		}
		pDC->Polyline(pPointArrayIndexA,m_AllNum);//��������ߵĵ�ȫ�����Ƴ���
		pDC->SelectObject(pOldPen);//�ͷŻ���
		pDC->SelectClipRgn(NULL);

		CPen *pOldPenB = pDC->SelectObject(&m_PenCurveB);//���õ�ǰ����Ϊm_PenCurveA

		pPointArrayIndexB =(POINT *) new POINT[m_AllNum];//�趨һ������
		for (int j=0;j<=m_RealValuenSize;j++)
		{
			pPointArrayIndexB[j].x = m_BaseXline+j*m_RealValueXInterval;
			pPointArrayIndexB[j].y = m_RealBaseYLine-5-2*pPointArray[j].y*(-m_rectCurve.Height()/4-5)/10000;
		}
		for (int n=m_RealValuenSize;n<=m_AllNum;n++)
		{
			pPointArrayIndexB[n].x = m_BaseXline+n*m_RealValueXInterval;
			pPointArrayIndexB[n].y = m_RealBaseYLine-5;
		}
		pDC->Polyline(pPointArrayIndexB,m_AllNum);//��������ߵĵ�ȫ�����Ƴ���
		pDC->SelectObject(pOldPenB);//�ͷŻ���
		pDC->SelectClipRgn(NULL);
	}
}
//�϶����ڴ�С�ߴ�ʱ���߻��Ƹ��¹���
void CW::Update()
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
void CW::runDraw()
{
	controlRunDraw = TRUE;
	Invalidate();
}
//��������ѡ��
void CW::PowerFlg()
{
	m_PowerFlg      = TRUE;
	m_SpectrumFlg   = FALSE;
	m_IandQFlg      = FALSE;
	m_IorQFlg       = FALSE;
	runDraw();
}
//Ƶ������ѡ��
void CW::SpectrumFlg()
{
	m_PowerFlg      = FALSE;
	m_SpectrumFlg   = TRUE;
	m_IandQFlg      = FALSE;
	m_IorQFlg       = FALSE;
	runDraw();
}
//I+Q����ѡ��
void CW::IandQFlg()
{
	m_PowerFlg      = FALSE;
	m_SpectrumFlg   = FALSE;
	m_IandQFlg      = TRUE;
	m_IorQFlg       = FALSE;
	runDraw();
}
//I|Q����ѡ��
void CW::IorQFlg()
{
	m_PowerFlg      = FALSE;
	m_SpectrumFlg   = FALSE;
	m_IandQFlg      = FALSE;
	m_IorQFlg       = TRUE;
	runDraw();
}
//����ڴ�
void CW::AllClear()
{
	delete []pPointArray;//���յ�
	delete []pPointArrayPower;
	delete []pPointArrayPowerIndex;
	delete []pPointArraySpectrum;
	delete []pPointArraySpectrumIndex;
	delete []pPointArrayIndexA;
	delete []pPointArrayIndexB;
	/*pPointArray = NULL;
	pPointArrayPower = NULL;//���յ�
	pPointArrayPowerIndex = NULL;
	pPointArraySpectrum = NULL;
	pPointArraySpectrumIndex = NULL;
	pPointArrayIndexA = NULL;
	pPointArrayIndexB = NULL;*/
}