// W.cpp : 实现文件
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "W.h"
#include "math.h"

// CW

IMPLEMENT_DYNAMIC(CW, CStatic)

CW::CW()
{
	
	m_PowerFlg           = FALSE;//标记选择的波形类型0:功率; 1:I+Q; 2:I|Q; 3:频谱
	m_SpectrumFlg        = FALSE;
	m_IandQFlg           = FALSE;
	m_IorQFlg            = FALSE;

	controlRunDraw       = FALSE;
	m_AllNum             = 10000;//所有点数
	m_ValueXRange        = 12;//X轴竖线个数
	m_ValueYRange        = 6;//Y轴横线个数

	pPointArray          = NULL;//接收点
	pPointArrayPower     = NULL;
	pPointArrayPowerIndex= NULL;
	pPointArraySpectrum  = NULL;
	pPointArraySpectrumIndex  = NULL;
	pPointArrayIndexA    = NULL;
	pPointArrayIndexB    = NULL;

	m_ScaleValueYRange   = -50;//Y轴起始值
	m_ScaleValueXRange   = 0;//X轴起始值
	m_ScaleValueXEnd     = 0;//X轴结束值
	m_ScaleValueYEnd     = 0;//Y轴结束值
	m_dDimX	             = 1.0;//x轴刻度单位
	m_dDimY	             = 10.0;//y轴刻度单位

	m_RealBaseYLine      = 0;//Y轴真实值基线初始化
	m_RealBaseYLine2     = 0;
	m_RealValuenSize     = 0;//波形曲线点数初始化

	m_BkBrush.CreateSolidBrush(RGB(0,0,0));//背景，黑色
	m_CurveBrush.CreateSolidBrush(RGB(0,0,0));//网格线，黑色
	m_PenDarkLine.CreatePen(PS_SOLID,0,RGB(0x55,0x55,0x55));//网格线，暗线
	m_PenBrightLine.CreatePen(PS_SOLID,0,RGB(0xff,0xff,0xff));//网格线，明线

	m_PenCurveA.CreatePen(PS_SOLID,1,RGB(0,0,255));//曲线画笔
	m_PenCurveB.CreatePen(PS_SOLID,1,RGB(200,100,0));//曲线画笔
	m_PenCurvePower.CreatePen(PS_SOLID,1,RGB(220,220,0));//Power画笔
	m_PenCurveSpec.CreatePen(PS_SOLID,1,RGB(0,128,0));//频谱画笔

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

// CW 消息处理程序

BOOL CW::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rect;
	GetClientRect(&rect);//获取用户区域
	pDC->FillRect(&rect,&m_BkBrush);//Draw background填充最底层

	return CStatic::OnEraseBkgnd(pDC);
}

void CW::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	CRect rc;
	GetClientRect(&rc);//获取用户区域
	rc.InflateRect(0,0,0,0);//curve panel////curve panel确定显示框的大小和位置，距离左、上、右、下
	m_rectCurve = rc;//显示曲线
	m_rectCurve.InflateRect(-60,-40,-5,-30);//curve area确定黑色网格的总区域的大小
	CDC *pDC = GetDC();
	ValueTransform(pDC);//坐标转化
	DrawGrid(pDC);//网格
	DrawAxis(pDC);//刻度
	DrawXYtitle(pDC);//标题
	if (controlRunDraw)
	{
		//CPen pen(PS_SOLID, 0, RGB(255,255,0));
		//pDC->SelectObject(&pen);	
		//pDC->MoveTo(m_rectCurve.left, m_rectCurve.top+m_rectCurve.Height()/m_ValueYRange);
		//pDC->LineTo(m_rectCurve.right, m_rectCurve.top+m_rectCurve.Height()/m_ValueYRange);
		//DrawCurveA(pDC);//曲线
		Update();
	}

	// 不为绘图消息调用 CStatic::OnPaint()
}

//坐标转换函数
void CW::ValueTransform(CDC *pDC)
{
	m_RatioX = m_rectCurve.Width()/m_ValueXRange;//计算X轴比例
	m_RatioY = m_rectCurve.Height()/m_ValueYRange;//计算Y轴比例
	m_BaseXline = m_rectCurve.left;
	m_BaseYline = m_rectCurve.bottom;//XY轴基线
	m_RealValueXInterval = 1.0*m_rectCurve.Width()/(double)m_AllNum;////真实点的X轴间隔单位值
}
//坐标网格绘制
void CW::DrawGrid(CDC *pDC)
{
	CPen *pOldPen = pDC->SelectObject(&m_PenDarkLine);//设置m_PenDarkLine为默认画笔	

	if(m_PowerFlg||m_SpectrumFlg)
	{
		int i;
		pDC->MoveTo(m_rectCurve.left,m_rectCurve.top);
		pDC->LineTo(m_rectCurve.left,m_rectCurve.bottom);
		pDC->MoveTo(m_rectCurve.left,m_rectCurve.top);
		pDC->LineTo(m_rectCurve.right,m_rectCurve.top);//用暗线勾画出面板的明暗对比效果

		pDC->MoveTo(m_rectCurve.left,m_rectCurve.bottom);
		pDC->LineTo(m_rectCurve.right,m_rectCurve.bottom);	//绘制横向基线

		int nPosY;

		//画横线
		for(i=1;i<m_ValueYRange;i++)
		{
			nPosY = m_BaseYline-i*m_RatioY;
			if(nPosY<m_rectCurve.bottom)
			{
				pDC->MoveTo(m_rectCurve.left,nPosY);
				pDC->LineTo(m_rectCurve.right,nPosY);
			}
		}

		//画竖线
		for(i=1;i<=m_ValueXRange;i++)
		{
			if(m_rectCurve.left+i*m_RatioX<m_rectCurve.right)
			{
				pDC->MoveTo(m_rectCurve.left+i*m_RatioX,m_rectCurve.top);
				pDC->LineTo(m_rectCurve.left+i*m_RatioX,m_rectCurve.bottom);
			}
		}

		//Y轴的辅助小横线
		for(i=1;i<=m_ValueYRange*2;i++)
		{
			if (m_rectCurve.top+i*m_RatioY*0.5<m_rectCurve.bottom)
			{
				pDC->MoveTo(m_BaseXline,m_rectCurve.top+i*m_RatioY*0.5);
				pDC->LineTo(m_BaseXline+4,m_rectCurve.top+i*m_RatioY*0.5);
			}
		}
		//X轴辅助小竖线
		for(i=1;i<=m_ValueXRange*2;i++)
		{
			if(m_rectCurve.left+0.5*i*m_RatioX<m_rectCurve.right)
			{
				pDC->MoveTo(m_rectCurve.left+0.5*i*m_RatioX,m_BaseYline-4);
				pDC->LineTo(m_rectCurve.left+0.5*i*m_RatioX,m_BaseYline);
			}
		}

		//用明线勾画出面板的明暗对比效果	
		pDC->SelectObject(&m_PenBrightLine);
		pDC->MoveTo(m_rectCurve.right,m_rectCurve.top);
		pDC->LineTo(m_rectCurve.right,m_rectCurve.bottom);
		pDC->MoveTo(m_rectCurve.left,m_rectCurve.bottom);
		pDC->LineTo(m_rectCurve.right,m_rectCurve.bottom);

		pDC->SelectObject(&pOldPen);//释放画笔
	}
	else if (m_IandQFlg)
	{
		int m;
		pDC->MoveTo(m_rectCurve.left,m_rectCurve.top);
		pDC->LineTo(m_rectCurve.left,m_rectCurve.bottom);
		pDC->MoveTo(m_rectCurve.left,m_rectCurve.top);
		pDC->LineTo(m_rectCurve.right,m_rectCurve.top);//用暗线勾画出面板的明暗对比效果

		pDC->MoveTo(m_rectCurve.left,m_BaseYline);
		pDC->LineTo(m_rectCurve.right,m_BaseYline);	//绘制横向基线

		int nPosYM;

		//Y轴的辅助小横线
		for(m=1;m<=7;m++)
		{
			if (m_rectCurve.top+m*(m_rectCurve.Height()/8)<m_rectCurve.bottom)
			{
				pDC->MoveTo(m_BaseXline,m_BaseYline-m*(m_rectCurve.Height()/8)-2);
				pDC->LineTo(m_BaseXline+4,m_BaseYline-m*(m_rectCurve.Height()/8)-2);
			}
		}
		//X轴辅助小竖线
		for(m=1;m<=m_ValueXRange*2;m++)
		{
			if(m_rectCurve.left+0.5*m*m_RatioX<m_rectCurve.right)
			{
				pDC->MoveTo(m_rectCurve.left+0.5*m*m_RatioX,m_BaseYline-6);
				pDC->LineTo(m_rectCurve.left+0.5*m*m_RatioX,m_BaseYline);
			}
		}

		//画横线
		for(m=1;m<4;m++)
		{
			nPosYM = m_BaseYline-m*(m_rectCurve.Height()/4);
			if(nPosYM<m_rectCurve.bottom)
			{
				pDC->MoveTo(m_rectCurve.left,nPosYM);
				pDC->LineTo(m_rectCurve.right,nPosYM);
			}
		}

		//画竖线
		for(m=1;m<=m_ValueXRange;m++)
		{
			if(m_rectCurve.left+m*m_RatioX<m_rectCurve.right)
			{
				pDC->MoveTo(m_rectCurve.left+m*m_RatioX,m_rectCurve.top);
				pDC->LineTo(m_rectCurve.left+m*m_RatioX,m_rectCurve.bottom);
			}
		}

		//用明线勾画出面板的明暗对比效果	
		pDC->SelectObject(&m_PenBrightLine);
		pDC->MoveTo(m_rectCurve.right,m_rectCurve.top);
		pDC->LineTo(m_rectCurve.right,m_rectCurve.bottom);
		pDC->MoveTo(m_rectCurve.left,m_rectCurve.bottom);
		pDC->LineTo(m_rectCurve.right,m_rectCurve.bottom);

		pDC->SelectObject(&pOldPen);//释放画笔
	}
	else
	{
		//下部网格
		pDC->MoveTo(m_BaseXline,m_BaseYline);
		pDC->LineTo(m_BaseXline,m_BaseYline-m_rectCurve.Height()/2+10);
		pDC->MoveTo(m_BaseXline,m_BaseYline-m_rectCurve.Height()/2+10);
		pDC->LineTo(m_BaseXline+m_rectCurve.Width(),m_BaseYline-m_rectCurve.Height()/2+10);//用暗线勾画出面板的明暗对比效果

		pDC->MoveTo(m_rectCurve.left,m_BaseYline);
		pDC->LineTo(m_rectCurve.right,m_BaseYline);	//绘制横向基线

		//上部网格
		pDC->MoveTo(m_BaseXline,m_BaseYline-m_rectCurve.Height());
		pDC->LineTo(m_BaseXline,m_BaseYline-m_rectCurve.Height()/2-20);
		pDC->MoveTo(m_BaseXline,m_BaseYline-m_rectCurve.Height());
		pDC->LineTo(m_BaseXline+m_rectCurve.Width(),m_BaseYline-m_rectCurve.Height());//用暗线勾画出面板的明暗对比效果

		pDC->MoveTo(m_rectCurve.left,m_BaseYline-m_rectCurve.Height()/2-20);
		pDC->LineTo(m_rectCurve.right,m_BaseYline-m_rectCurve.Height()/2-20);	//绘制横向基线*/

		//下部网格 画横线
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

		//下部网格 画竖线
		for(i=1;i<=m_ValueXRange;i++)
		{
			if(m_rectCurve.left+i*m_RatioX<m_rectCurve.right)
			{
				pDC->MoveTo(m_rectCurve.left+i*m_RatioX,m_BaseYline);
				pDC->LineTo(m_rectCurve.left+i*m_RatioX,m_BaseYline-m_rectCurve.Height()/2+10);
			}
		}

		//上部网格 画横线
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
		//上部网格 画竖线
		for(j=1;j<=m_ValueXRange;j++)
		{
			if(m_rectCurve.left+j*m_RatioX<m_rectCurve.right)
			{
				pDC->MoveTo(m_rectCurve.left+j*m_RatioX,m_BaseYline-m_rectCurve.Height()/2-20);
				pDC->LineTo(m_rectCurve.left+j*m_RatioX,m_BaseYline-m_rectCurve.Height());
			}
		}

		//用明线勾画出面板的明暗对比效果	
		//下部网格
		pDC->SelectObject(&m_PenBrightLine);
		pDC->MoveTo(m_rectCurve.right,m_BaseYline-m_rectCurve.Height()/2+10);
		pDC->LineTo(m_rectCurve.right,m_rectCurve.bottom);
		pDC->MoveTo(m_rectCurve.left,m_rectCurve.bottom);
		pDC->LineTo(m_rectCurve.right,m_rectCurve.bottom);
		//上部网格
		pDC->SelectObject(&m_PenBrightLine);
		pDC->MoveTo(m_rectCurve.right,m_BaseYline-m_rectCurve.Height()/2-20);
		pDC->LineTo(m_rectCurve.right,m_rectCurve.top);
		pDC->MoveTo(m_rectCurve.left,m_BaseYline-m_rectCurve.Height()/2-20);
		pDC->LineTo(m_rectCurve.right,m_BaseYline-m_rectCurve.Height()/2-20);	

		pDC->SelectObject(&pOldPen);//释放画笔
	}
}

////数值刻度标记函数
void CW::DrawAxis(CDC *pDC)
{
	CFont *pOldFont;
	int j,nPosY;
	CString str;
	pOldFont = pDC->SelectObject(&m_FontAxis);//设置当前字体默认为Axis（数字字体）
	pDC->SetTextColor(RGB(255,255,255));//设置默认颜色为白色（数字颜色）
	pDC->SetBkMode(TRANSPARENT);//设置默认输入为透明
	pDC->SetTextAlign(TA_RIGHT|TA_BASELINE);//设置默认文本模式（右对齐，基线对齐）

	if (m_PowerFlg)
	{
		//Y轴起始值
		if (abs(m_ScaleValueYRange)<1)
			str.Format(_T("%.1fdB"),m_ScaleValueYRange);
		else
			str.Format(_T("%.0fdB"),m_ScaleValueYRange);
		pDC->TextOut(m_BaseXline-6,m_BaseYline,str);

		//纵坐标
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
			}//幅度刻度的表示形式
			if (j*m_dDimY+m_ScaleValueYRange==0)//判断真实值的基线
			{
				m_RealBaseYLine = m_BaseYline-j*m_RatioY;
			}
		}

		//横坐标
		//X轴起始值
		if (abs(m_ScaleValueXRange)<1&&m_ScaleValueXRange!=0)
			str.Format(_T("%.1f"),m_ScaleValueXRange);
		else
			str.Format(_T("%.0f"),m_ScaleValueXRange);
		pDC->TextOut(m_BaseXline+5,m_BaseYline+15,str);
	}
	else if (m_SpectrumFlg)
	{
		//Y轴起始值
		if (abs(m_ScaleValueYRange)<1)
			str.Format(_T("%.1fdB"),m_ScaleValueYRange-10);
		else
			str.Format(_T("%.0fdB"),m_ScaleValueYRange-10);
		pDC->TextOut(m_BaseXline-6,m_BaseYline,str);

		//纵坐标
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
			}//幅度刻度的表示形式
			if (j*m_dDimY+m_ScaleValueYRange-10==0)//判断真实值的基线
			{
				m_RealBaseYLine = m_BaseYline-j*m_RatioY;
			}
		}

		//横坐标
		//X轴起始值
		if (abs(m_ScaleValueXRange)<1&&m_ScaleValueXRange!=0)
			str.Format(_T("%.1f"),m_ScaleValueXRange);
		else
			str.Format(_T("%.0f"),m_ScaleValueXRange);
		pDC->TextOut(m_BaseXline+5,m_BaseYline+15,str);
	}
	else if (m_IandQFlg)
	{
		//纵坐标
		pDC->TextOut(m_BaseXline-6,m_BaseYline,_T("-0.4"));
		pDC->TextOut(m_BaseXline-6,m_BaseYline-m_rectCurve.Height()/4+5,_T("-0.2"));
		pDC->TextOut(m_BaseXline-6,m_BaseYline-2*(m_rectCurve.Height()/4)+5,_T("0"));
		pDC->TextOut(m_BaseXline-6,m_BaseYline-3*(m_rectCurve.Height()/4)+5,_T("0.2"));
		pDC->TextOut(m_BaseXline-6,m_BaseYline-m_rectCurve.Height()+5,_T("0.4"));
		//横坐标
		//X轴起始值
		if (abs(m_ScaleValueXRange)<1&&m_ScaleValueXRange!=0)
			str.Format(_T("%.1f"),m_ScaleValueXRange);
		else
			str.Format(_T("%.0f"),m_ScaleValueXRange);
		pDC->TextOut(m_BaseXline+5,m_BaseYline+15,str);

		//Y轴真实值基线
		m_RealBaseYLine = m_BaseYline-2*(m_rectCurve.Height()/4)+5;
	}
	else
	{
		nPosY = m_BaseYline-m_rectCurve.Height()/2-20;

		//下部Q纵坐标
		pDC->TextOut(m_BaseXline-6,m_BaseYline,_T("-0.5"));
		pDC->TextOut(m_BaseXline-6,m_BaseYline-(m_rectCurve.Height()/2-20)/2,_T("0"));
		pDC->TextOut(m_BaseXline-6,m_BaseYline-m_rectCurve.Height()/2+20,_T("0.5"));

		//上部I纵坐标
		pDC->TextOut(m_BaseXline-6,nPosY,_T("-0.5"));
		pDC->TextOut(m_BaseXline-6,nPosY-(m_rectCurve.Height()/2-25)/2,_T("0"));
		pDC->TextOut(m_BaseXline-6,nPosY-m_rectCurve.Height()/2+25,_T("0.5"));

		//横坐标
		//X轴起始值
		if (abs(m_ScaleValueXRange)<1&&m_ScaleValueXRange!=0)
			str.Format(_T("%.1f"),m_ScaleValueXRange);
		else
			str.Format(_T("%.0f"),m_ScaleValueXRange);
		pDC->TextOut(m_BaseXline+5,m_BaseYline+15,str);

		//Y轴真实值基线
		m_RealBaseYLine = m_BaseYline-(m_rectCurve.Height()/2-20)/2;
		m_RealBaseYLine2 = nPosY-(m_rectCurve.Height()/2-25)/2;
	}
	
}

////XY轴标题设置
void CW::DrawXYtitle(CDC *pDC)//XY轴标题设置
{
	CFont *pOldFont;
	CString str;
	CString Titalstr;
	CString XMaxstr;
	CString Otherstr;

	pOldFont = pDC->SelectObject(&m_FontAxis);//设置当前字体默认为Axis（数字字体）
	pDC->SetTextColor(RGB(255,255,255));//设置默认颜色为（数字颜色）
	pDC->SetBkMode(TRANSPARENT);//设置默认输入为透明
	pDC->SetTextAlign(TA_LEFT|TA_TOP);//设置默认文本为左对齐，置顶
	pDC->SetTextAlign(TA_CENTER|TA_TOP);

	if (m_PowerFlg)
	{
		//X轴标题
		XMaxstr.Format(_T("maxNum: %d"),10000);
		pDC->TextOut(m_rectCurve.right-42,m_rectCurve.bottom+2,XMaxstr);//最后一点值
	}
	else if (m_SpectrumFlg)
	{
		XMaxstr.Format(_T("maxNum: %d"),10000);
		CString Center=_T("--");
		pDC->TextOut(m_BaseXline+m_rectCurve.Width()/2,m_BaseYline-m_rectCurve.Height()-20,Center);//最后一点值
		pDC->TextOut(m_rectCurve.right-42,m_rectCurve.bottom+2,XMaxstr);//最后一点值
	}
	else if (m_IandQFlg)
	{
		XMaxstr.Format(_T("maxNum: %d"),10000);
		pDC->TextOut(m_rectCurve.right-42,m_rectCurve.bottom+2,XMaxstr);//最后一点值
	}
	else
	{
		XMaxstr.Format(_T("maxNum: %d"),10000);
		pDC->TextOut(m_rectCurve.right-42,m_rectCurve.bottom+2,XMaxstr);//最后一点值
	}
	pOldFont = pDC->SelectObject(&m_FontAxis);//设置当前字体默认为Axis（数字字体）
	pDC->SetTextColor(RGB(0,255,0));
	str.Format(_T("Points: %d"),m_RealValuenSize);
	pDC->TextOut(m_BaseXline+m_rectCurve.Width()-60,m_BaseYline-m_rectCurve.Height()-20,str);

	if (m_PowerFlg)
	{
		//X轴标题
		pOldFont = pDC->SelectObject(&m_FontAxis);//设置当前字体默认为Axis（数字字体）
		pDC->SetTextColor(RGB(255,255,0));//设置默认颜色为（数字颜色）
		Titalstr=_T("功率谱");
		pDC->TextOut(m_BaseXline+20,m_BaseYline-m_rectCurve.Height()-25,Titalstr);
	}
	else if (m_SpectrumFlg)
	{
		pOldFont = pDC->SelectObject(&m_FontAxis);//设置当前字体默认为Axis（数字字体）
		pDC->SetTextColor(RGB(0,128,0));//设置默认颜色为（数字颜色）
		Titalstr=_T("频谱");
		pDC->TextOut(m_BaseXline+20,m_BaseYline-m_rectCurve.Height()-25,Titalstr);
	}
	else if (m_IandQFlg)
	{
		pOldFont = pDC->SelectObject(&m_FontAxis);//设置当前字体默认为Axis（数字字体）
		pDC->SetTextColor(RGB(0,0,255));//设置默认颜色为（数字颜色）
		Titalstr=_T("I");
		pDC->TextOut(m_BaseXline+10,m_BaseYline-m_rectCurve.Height()-20,Titalstr);

		pOldFont = pDC->SelectObject(&m_FontAxis);//设置当前字体默认为Axis（数字字体）
		pDC->SetTextColor(RGB(255,255,255));//设置默认颜色为（数字颜色）
		Titalstr=_T("+");
		pDC->TextOut(m_BaseXline+20,m_BaseYline-m_rectCurve.Height()-20,Titalstr);

		pOldFont = pDC->SelectObject(&m_FontAxis);//设置当前字体默认为Axis（数字字体）
		pDC->SetTextColor(RGB(200,100,0));//设置默认颜色为（数字颜色）
		Titalstr=_T("Q");
		pDC->TextOut(m_BaseXline+30,m_BaseYline-m_rectCurve.Height()-20,Titalstr);
	}
	else
	{
		pOldFont = pDC->SelectObject(&m_FontAxis);//设置当前字体默认为Axis（数字字体）
		pDC->SetTextColor(RGB(0,0,255));//设置默认颜色为（数字颜色）
		Titalstr=_T("I");
		pDC->TextOut(m_BaseXline+10,m_BaseYline-m_rectCurve.Height()-20,Titalstr);

		pOldFont = pDC->SelectObject(&m_FontAxis);//设置当前字体默认为Axis（数字字体）
		pDC->SetTextColor(RGB(255,255,255));//设置默认颜色为（数字颜色）
		Titalstr=_T("|");
		pDC->TextOut(m_BaseXline+20,m_BaseYline-m_rectCurve.Height()-20,Titalstr);

		pOldFont = pDC->SelectObject(&m_FontAxis);//设置当前字体默认为Axis（数字字体）
		pDC->SetTextColor(RGB(200,100,0));//设置默认颜色为（数字颜色）
		Titalstr=_T("Q");
		pDC->TextOut(m_BaseXline+30,m_BaseYline-m_rectCurve.Height()-20,Titalstr);
	}

}

//绘制波形函数
void CW::DrawCurveA(CDC *pDC)
{
	//功率谱绘制过程
	if (m_PowerFlg)
	{
		CPen *pOldPen = pDC->SelectObject(&m_PenCurvePower);//设置当前画笔为m_PenCurveA

		pPointArrayPowerIndex =(POINT *) new POINT[2*m_AllNum];//设定一个数组
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
		pDC->Polyline(pPointArrayPowerIndex,2*m_AllNum);//将组成曲线的点全部绘制出来
		pDC->SelectObject(pOldPen);//释放画笔
		pDC->SelectClipRgn(NULL);

	}
	//频谱绘制过程
	else if (m_SpectrumFlg)
	{
		CPen *pOldPen = pDC->SelectObject(&m_PenCurveSpec);//设置当前画笔为m_PenCurveA

		pPointArraySpectrumIndex =(POINT *) new POINT[m_AllNum];//设定一个数组

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
		pDC->Polyline(pPointArraySpectrumIndex,m_AllNum);//将组成曲线的点全部绘制出来
		pDC->SelectObject(pOldPen);//释放画笔
		pDC->SelectClipRgn(NULL);
	}
	//I+Q绘制过程
	else if (m_IandQFlg)
	{
		CPen *pOldPen = pDC->SelectObject(&m_PenCurveA);//设置当前画笔为m_PenCurveA

		pPointArrayIndexA =(POINT *) new POINT[m_AllNum];//设定一个数组

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
		pDC->Polyline(pPointArrayIndexA,m_AllNum);//将组成曲线的点全部绘制出来
		pDC->SelectObject(pOldPen);//释放画笔
		pDC->SelectClipRgn(NULL);

		CPen *pOldPenB = pDC->SelectObject(&m_PenCurveB);//设置当前画笔为m_PenCurveA

		pPointArrayIndexB =(POINT *) new POINT[m_AllNum];//设定一个数组
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
		pDC->Polyline(pPointArrayIndexB,m_AllNum);//将组成曲线的点全部绘制出来
		pDC->SelectObject(pOldPenB);//释放画笔
		pDC->SelectClipRgn(NULL);
	}
	//I|Q绘制过程
	else
	{
		CPen *pOldPen = pDC->SelectObject(&m_PenCurveA);//设置当前画笔为m_PenCurveA

		pPointArrayIndexA =(POINT *) new POINT[m_AllNum];//设定一个数组

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
		pDC->Polyline(pPointArrayIndexA,m_AllNum);//将组成曲线的点全部绘制出来
		pDC->SelectObject(pOldPen);//释放画笔
		pDC->SelectClipRgn(NULL);

		CPen *pOldPenB = pDC->SelectObject(&m_PenCurveB);//设置当前画笔为m_PenCurveA

		pPointArrayIndexB =(POINT *) new POINT[m_AllNum];//设定一个数组
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
		pDC->Polyline(pPointArrayIndexB,m_AllNum);//将组成曲线的点全部绘制出来
		pDC->SelectObject(pOldPenB);//释放画笔
		pDC->SelectClipRgn(NULL);
	}
}
//拖动窗口大小尺寸时曲线绘制更新过程
void CW::Update()
{
	CClientDC dc(this);
	CRect rect;
	GetClientRect(&rect);//获取客户区域
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);//将当前的曲线作为位图存入memDC中
	CBitmap bitmap,*pOldBmp;
	bitmap.CreateCompatibleBitmap(&dc,rect.Width(),rect.Height());//调入位图&dc并初始化界面
	pOldBmp = memDC.SelectObject(&bitmap);//将位图bitmap传递给memDC
	DrawGrid(&memDC);//调用绘制网格
	DrawAxis(&memDC);//调用绘制刻度
	DrawXYtitle(&memDC);//标题
	DrawCurveA(&memDC);//绘制曲线

	dc.BitBlt(m_rectCurve.left,m_rectCurve.top,m_rectCurve.Width(),m_rectCurve.Height(),
		&memDC,m_rectCurve.left,m_rectCurve.top,SRCCOPY);//将位图复制到dc中
	memDC.SelectObject(pOldBmp);//释放当前位图	
}
//控制曲线是否进行绘制的外部接口函数
void CW::runDraw()
{
	controlRunDraw = TRUE;
	Invalidate();
}
//功率曲线选择
void CW::PowerFlg()
{
	m_PowerFlg      = TRUE;
	m_SpectrumFlg   = FALSE;
	m_IandQFlg      = FALSE;
	m_IorQFlg       = FALSE;
	runDraw();
}
//频谱曲线选择
void CW::SpectrumFlg()
{
	m_PowerFlg      = FALSE;
	m_SpectrumFlg   = TRUE;
	m_IandQFlg      = FALSE;
	m_IorQFlg       = FALSE;
	runDraw();
}
//I+Q曲线选择
void CW::IandQFlg()
{
	m_PowerFlg      = FALSE;
	m_SpectrumFlg   = FALSE;
	m_IandQFlg      = TRUE;
	m_IorQFlg       = FALSE;
	runDraw();
}
//I|Q曲线选择
void CW::IorQFlg()
{
	m_PowerFlg      = FALSE;
	m_SpectrumFlg   = FALSE;
	m_IandQFlg      = FALSE;
	m_IorQFlg       = TRUE;
	runDraw();
}
//清除内存
void CW::AllClear()
{
	delete []pPointArray;//接收点
	delete []pPointArrayPower;
	delete []pPointArrayPowerIndex;
	delete []pPointArraySpectrum;
	delete []pPointArraySpectrumIndex;
	delete []pPointArrayIndexA;
	delete []pPointArrayIndexB;
	/*pPointArray = NULL;
	pPointArrayPower = NULL;//接收点
	pPointArrayPowerIndex = NULL;
	pPointArraySpectrum = NULL;
	pPointArraySpectrumIndex = NULL;
	pPointArrayIndexA = NULL;
	pPointArrayIndexB = NULL;*/
}