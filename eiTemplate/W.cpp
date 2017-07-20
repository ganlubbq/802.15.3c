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
	m_ValueXRange        = 12;//X轴竖线个数
	m_ValueYRange        = 7;//Y轴横线个数

	I_Data               =NULL;
	Q_Data               =NULL;
	pPointArrayPower     = NULL;
	pPointArrayPowerIndex= NULL;
	pPointArraySpectrum  = NULL;
	pPointArraySpectrumIndex  = NULL;
	pPointArrayIndexA    = NULL;
	pPointArrayIndexB    = NULL;

	m_dDimY	             = 5.0;//y轴刻度单位
	m_dDimX	             = 1.0;//x轴刻度单位
	m_ScaleValueYRange   = -(m_dDimY*m_ValueYRange);//Y轴起始值
	m_ScaleValueXRange   = 0;//X轴起始值
	m_ScaleValueXEnd     = 0;//X轴结束值
	m_ScaleValueYEnd     = 0;//Y轴结束值
	m_IQ_range           = 1;

	m_RealYRange         =m_dDimY*m_ValueYRange;

	m_RealBaseYLine      = 0;//Y轴真实值基线初始化
	m_RealBaseYLine2     = 0;
	m_RealValuenSize     = 0;//波形曲线点数初始化

	m_BkBrush.CreateSolidBrush(RGB(0,0,0));//背景，黑色
	m_CurveBrush.CreateSolidBrush(RGB(0,0,0));//网格线，黑色
	m_PenDarkLine.CreatePen(PS_SOLID,0,RGB(0x55,0x55,0x55));//网格线，暗线
	m_PenBrightLine.CreatePen(PS_SOLID,0,RGB(0xff,0xff,0xff));//网格线，明线

	m_PenCurveA.CreatePen(PS_SOLID,1,RGB(255,100,0));//曲线画笔
	m_PenCurveB.CreatePen(PS_SOLID,1,RGB(0,0,255));//曲线画笔
	m_PenCurvePower.CreatePen(PS_SOLID,1,RGB(220,220,0));//Power画笔
	m_PenCurveSpec.CreatePen(PS_SOLID,1,RGB(0,128,0));//频谱画笔

	m_FontAxis.CreateFont(18,0,0,0,FW_THIN,FALSE,FALSE,FALSE,DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T("微软雅黑"));

}

CW::~CW()
{
}

BEGIN_MESSAGE_MAP(CW, CStatic)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CW 消息处理程序
// WM_ERASEBKGND
BOOL CW::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rect;
	GetClientRect(&rect);//获取用户区域
	pDC->FillRect(&rect,&m_BkBrush);//Draw 黑色填充最底层
	return CStatic::OnEraseBkgnd(pDC);
}

//OnPaint()中调用Update()
void CW::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	CRect rc;
	GetClientRect(&rc);//获取用户区域
	rc.InflateRect(0,0,0,0);//curve panel////curve panel确定显示框的大小和位置
	m_rectCurve = rc;//显示曲线
	//curve area确定网格区域的大小，距离左、上、右、下
	m_rectCurve.InflateRect(-60,-40,-5,-30);
	//初始网格绘制
	CDC *pDC = GetDC();//获取当前Cwnd Client的DC
	ValueTransform(pDC);//坐标转化
	DrawGrid(pDC);//网格
	DrawAxis(pDC);//刻度
	DrawXYtitle(pDC);//标题
	if (controlRunDraw)
	{
		Update();          //绘制曲线
	}

	// 不为绘图消息调用 CStatic::OnPaint()
}

//坐标转换函数
void CW::ValueTransform(CDC *pDC)
{
	m_RatioX = m_rectCurve.Width()/m_ValueXRange;//计算X轴比例
	m_RatioY = m_rectCurve.Height()/m_ValueYRange;//计算Y轴比例
	m_RatioY_IorQ=((double)(m_rectCurve.Height()-30))/m_IQ_range/4.0;
	m_BaseXline = m_rectCurve.left;
	m_BaseYline = m_rectCurve.bottom;//XY轴基线
	m_RealValueXInterval = 1.0*m_rectCurve.Width()/(double)m_RealValuenSize;////真实点的X轴间隔单位值
	m_FFT_RealValueXInterval=1.0*m_rectCurve.Width()/(double)m_FFT_AllNum;//FFT后
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
			if(m_rectCurve.left+i*m_RatioX<m_rectCurve.right)//增加一个判断，网格最右边的线位置不超过绘图区域
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
		pDC->SelectObject(&m_PenBrightLine);//换画笔
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
			pDC->MoveTo(m_BaseXline,m_BaseYline-m*(m_rectCurve.Height()/8));
			pDC->LineTo(m_BaseXline+4,m_BaseYline-m*(m_rectCurve.Height()/8));
		}
		//X轴辅助小竖线
		for(m=1;m<=m_ValueXRange*2;m++)
		{
			if(m_rectCurve.left+0.5*m*m_RatioX<m_rectCurve.right)
			{
				pDC->MoveTo(m_rectCurve.left+0.5*m*m_RatioX,m_BaseYline-4);
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
		pDC->SelectObject(&m_PenBrightLine);//换画笔
		pDC->MoveTo(m_rectCurve.right,m_rectCurve.top);
		pDC->LineTo(m_rectCurve.right,m_rectCurve.bottom);
		pDC->MoveTo(m_rectCurve.left,m_rectCurve.bottom);
		pDC->LineTo(m_rectCurve.right,m_rectCurve.bottom);

		pDC->SelectObject(&pOldPen);//释放画笔
	}
	else
	{
		// I/Q 网格间间隔30个像素
		//下部网格
		pDC->MoveTo(m_rectCurve.left,m_BaseYline);
		pDC->LineTo(m_rectCurve.left,m_BaseYline-m_rectCurve.Height()/2+15);
		pDC->MoveTo(m_rectCurve.left,m_BaseYline-m_rectCurve.Height()/2+15);
		pDC->LineTo(m_rectCurve.right,m_BaseYline-m_rectCurve.Height()/2+15);//用暗线勾画出面板的明暗对比效果

		pDC->MoveTo(m_rectCurve.left,m_BaseYline);
		pDC->LineTo(m_rectCurve.right,m_BaseYline);	//绘制横向基线

		//上部网格
		pDC->MoveTo(m_rectCurve.left,m_rectCurve.top);
		pDC->LineTo(m_rectCurve.left,m_rectCurve.top+m_rectCurve.Height()/2-15);
		pDC->MoveTo(m_rectCurve.left,m_rectCurve.top);
		pDC->LineTo(m_rectCurve.right,m_rectCurve.top);//用暗线勾画出面板的明暗对比效果

		pDC->MoveTo(m_rectCurve.left,m_rectCurve.top+m_rectCurve.Height()/2-15);
		pDC->LineTo(m_rectCurve.right,m_rectCurve.top+m_rectCurve.Height()/2-15);	//绘制横向基线*/

		//下部网格 画横线
		pDC->MoveTo(m_rectCurve.left,m_rectCurve.bottom-(m_rectCurve.Height()-30)/4);
		pDC->LineTo(m_rectCurve.right,m_rectCurve.bottom-(m_rectCurve.Height()-30)/4);

		//下部网格 画竖线
		for(int i=1;i<=m_ValueXRange;i++)
		{
			if(m_rectCurve.left+i*m_RatioX<m_rectCurve.right)
			{
				pDC->MoveTo(m_rectCurve.left+i*m_RatioX,m_BaseYline);
				pDC->LineTo(m_rectCurve.left+i*m_RatioX,m_BaseYline-m_rectCurve.Height()/2+15);
			}
		}

		//上部网格 画横线
		pDC->MoveTo(m_rectCurve.left,m_rectCurve.top+(m_rectCurve.Height()-30)/4);
		pDC->LineTo(m_rectCurve.right,m_rectCurve.top+(m_rectCurve.Height()-30)/4);

		//上部网格 画竖线
		for(int j=1;j<=m_ValueXRange;j++)
		{
			if(m_rectCurve.left+j*m_RatioX<m_rectCurve.right)
			{
				pDC->MoveTo(m_rectCurve.left+j*m_RatioX,m_rectCurve.top);
				pDC->LineTo(m_rectCurve.left+j*m_RatioX,m_rectCurve.top+2*((m_rectCurve.Height()-30)/4));
			}
		}

		//用明线勾画出面板的明暗对比效果	
		//下部网格
		pDC->SelectObject(&m_PenBrightLine);
		pDC->MoveTo(m_rectCurve.right,m_BaseYline-m_rectCurve.Height()/2+15);
		pDC->LineTo(m_rectCurve.right,m_rectCurve.bottom);
		pDC->MoveTo(m_rectCurve.left,m_rectCurve.bottom);
		pDC->LineTo(m_rectCurve.right,m_rectCurve.bottom);
		//上部网格
		pDC->SelectObject(&m_PenBrightLine);
		pDC->MoveTo(m_rectCurve.right,m_rectCurve.top+2*((m_rectCurve.Height()-30)/4));
		pDC->LineTo(m_rectCurve.right,m_rectCurve.top);
		pDC->MoveTo(m_rectCurve.left,m_rectCurve.top+2*((m_rectCurve.Height()-30)/4));
		pDC->LineTo(m_rectCurve.right,m_rectCurve.top+2*((m_rectCurve.Height()-30)/4));	

		pDC->SelectObject(&pOldPen);//释放画笔
	}
}

////数值刻度标记
void CW::DrawAxis(CDC *pDC)
{
	CFont *pOldFont;
	int j,nPosY;
	CString str;
	pOldFont = pDC->SelectObject(&m_FontAxis);//设置当前字体默认为Axis（数字字体）
	//设置默认颜色为白色（数字颜色）,默认输入为透明,默认文本模式（右对齐，基线对齐）
	pDC->SetTextColor(RGB(255,255,255));
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextAlign(TA_RIGHT|TA_BASELINE);

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
				else
					str.Format(_T("%.0f"),j*m_dDimY+m_ScaleValueYRange);
				pDC->TextOut(m_rectCurve.left-6,m_BaseYline-j*m_RatioY+6,str);
			}

			/**********************************************************************/
            //记录刻度值为0的点的位置
			/**********************************************************************/
			if (j*m_dDimY+m_ScaleValueYRange==0)
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
				else
					str.Format(_T("%.0f"),j*m_dDimY+m_ScaleValueYRange);
				pDC->TextOut(m_rectCurve.left-6,m_BaseYline-j*m_RatioY+6,str);
			}//幅度刻度的表示形式
			/**********************************************************************/
			//记录刻度值为0的点的位置
			/**********************************************************************/
			if (j*m_dDimY+m_ScaleValueYRange==0)
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
		//X轴结束值
		str.Format("%d",m_FFT_AllNum);
		pDC->TextOut(m_BaseXline+m_rectCurve.Width()-10,m_BaseYline+15,str);
	}
	else if (m_IandQFlg)
	{
		//纵坐标
		CString str_1,str_2,str_3,str_4;
		str_1.Format("%.1f",m_IQ_range);
		str_2.Format("-%.1f",m_IQ_range);
		str_3.Format("%.2f",m_IQ_range/2);
		str_4.Format("-%.2f",m_IQ_range/2);
		pDC->TextOut(m_BaseXline-6,m_BaseYline,str_2);
		pDC->TextOut(m_BaseXline-6,m_BaseYline-m_rectCurve.Height()/4+4,str_4);
		pDC->TextOut(m_BaseXline-6,m_BaseYline-m_rectCurve.Height()/2,_T("0"));
		pDC->TextOut(m_BaseXline-6,m_BaseYline-3*(m_rectCurve.Height()/4)+4,str_3);
		pDC->TextOut(m_BaseXline-6,m_BaseYline-m_rectCurve.Height()+4,str_1);
		//横坐标
		//X轴起始值
		if (abs(m_ScaleValueXRange)<1&&m_ScaleValueXRange!=0)
			str.Format(_T("%.1f"),m_ScaleValueXRange);
		else
			str.Format(_T("%.0f"),m_ScaleValueXRange);
		pDC->TextOut(m_BaseXline+5,m_BaseYline+15,str);
		//X轴结束值
		str.Format("%.0f",m_ScaleValueXEnd);
		pDC->TextOut(m_BaseXline+m_rectCurve.Width()-10,m_BaseYline+15,str);
		/**********************************************************************/
		//记录刻度值为0的点的位置
		/**********************************************************************/
		m_RealBaseYLine = m_rectCurve.bottom-m_rectCurve.Height()/2;
	}
	else //在初始化都为m_IorQFlg==false下可以先绘制I/Q网格
	{
		nPosY = m_BaseYline-m_rectCurve.Height()/2-20;

		CString str_1,str_2;
		str_1.Format("%.1f",m_IQ_range);
		str_2.Format("-%.1f",m_IQ_range);
		double m_IorQ=(m_rectCurve.Height()-30)/4;
		//下部Q纵坐标
		pDC->TextOut(m_BaseXline-6,m_BaseYline+3,str_2);
		pDC->TextOut(m_BaseXline-6,m_BaseYline-m_IorQ+3,_T("0"));
		pDC->TextOut(m_BaseXline-6,m_BaseYline-2*m_IorQ+3,str_1);

		//上部I纵坐标
		pDC->TextOut(m_BaseXline-6,m_BaseYline-2*m_IorQ-30+3,str_2);
		pDC->TextOut(m_BaseXline-6,m_BaseYline-3*m_IorQ-30+3,_T("0"));
		pDC->TextOut(m_BaseXline-6,m_BaseYline-4*m_IorQ-30+3,str_1);

		//横坐标
		//X轴起始值
		if (abs(m_ScaleValueXRange)<1&&m_ScaleValueXRange!=0)
			str.Format(_T("%.1f"),m_ScaleValueXRange);
		else
			str.Format(_T("%.0f"),m_ScaleValueXRange);
		pDC->TextOut(m_BaseXline+5,m_BaseYline+15,str);
		//X轴结束值
		//Q
		str.Format("%.0f",m_ScaleValueXEnd);
		pDC->TextOut(m_BaseXline+m_rectCurve.Width()-10,m_BaseYline+15,str);
		//I
		str.Format("%.0f",m_ScaleValueXEnd);
		pDC->TextOut(m_BaseXline+m_rectCurve.Width()-10,m_BaseYline-2*m_IorQ-30+15,str);
		//Y轴真实值基线
		m_RealBaseYLine = m_BaseYline-3*m_IorQ-30;
		m_RealBaseYLine2 = m_BaseYline-m_IorQ;
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
		pOldFont = pDC->SelectObject(&m_FontAxis);//设置当前字体默认为Axis（数字字体）
		pDC->SetTextColor(RGB(255,255,0));//设置默认颜色为（数字颜色）
		Titalstr=_T("功率");
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
		pDC->SetTextColor(RGB(200,100,0));//设置默认颜色为（数字颜色）
		Titalstr=_T("I");
		pDC->TextOut(m_BaseXline+10,m_BaseYline-m_rectCurve.Height()-20,Titalstr);

		pOldFont = pDC->SelectObject(&m_FontAxis);//设置当前字体默认为Axis（数字字体）
		pDC->SetTextColor(RGB(255,255,255));//设置默认颜色为（数字颜色）
		Titalstr=_T("+");
		pDC->TextOut(m_BaseXline+20,m_BaseYline-m_rectCurve.Height()-20,Titalstr);

		pOldFont = pDC->SelectObject(&m_FontAxis);//设置当前字体默认为Axis（数字字体）
		pDC->SetTextColor(RGB(0,0,255));//设置默认颜色为（数字颜色）
		Titalstr=_T("Q");
		pDC->TextOut(m_BaseXline+30,m_BaseYline-m_rectCurve.Height()-20,Titalstr);

	}
	else
	{
		pOldFont = pDC->SelectObject(&m_FontAxis);//设置当前字体默认为Axis（数字字体）
		pDC->SetTextColor(RGB(200,100,0));//设置默认颜色为（数字颜色）
		Titalstr=_T("I");
		pDC->TextOut(m_BaseXline+10,m_BaseYline-m_rectCurve.Height()-20,Titalstr);

		pOldFont = pDC->SelectObject(&m_FontAxis);//设置当前字体默认为Axis（数字字体）
		pDC->SetTextColor(RGB(255,255,255));//设置默认颜色为（数字颜色）
		Titalstr=_T("|");
		pDC->TextOut(m_BaseXline+20,m_BaseYline-m_rectCurve.Height()-20,Titalstr);

		pOldFont = pDC->SelectObject(&m_FontAxis);//设置当前字体默认为Axis（数字字体）
		pDC->SetTextColor(RGB(0,0,255));//设置默认颜色为（数字颜色）
		Titalstr=_T("Q");
		pDC->TextOut(m_BaseXline+30,m_BaseYline-m_rectCurve.Height()-20,Titalstr);
	}

}

//绘制波形函数
void CW::DrawCurveA(CDC *pDC)
{
	CString str;
	//功率谱绘制过程
	if (m_PowerFlg)
	{
		CPen *pOldPen = pDC->SelectObject(&m_PenCurvePower);//设置当前画笔为m_PenCurveA

		pPointArrayPowerIndex =(POINT *) new POINT[m_RealValuenSize];//设定一个数组
		for (int i=0;i<m_RealValuenSize;i++)
		{
			pPointArrayPowerIndex[i].x = m_BaseXline+i*m_RealValueXInterval;
			pPointArrayPowerIndex[i].y = m_rectCurve.top+pPointArrayPower[i].y*(-m_rectCurve.Height()/m_RealYRange);
			
			if ( pPointArrayPowerIndex[i].y > m_rectCurve.bottom)
			{
				pPointArrayPowerIndex[i].y=m_rectCurve.bottom;
			}
		}
		
		pDC->Polyline(pPointArrayPowerIndex,m_RealValuenSize);//将组成曲线的点全部绘制出来
		pDC->SelectObject(pOldPen);//释放画笔
		pDC->SelectClipRgn(NULL);//无区域作为剪切区域

	}
	//频谱绘制过程
	else if (m_SpectrumFlg)
	{
		CPen *pOldPen = pDC->SelectObject(&m_PenCurveSpec);//设置当前画笔为m_PenCurveA

		pPointArraySpectrumIndex =(POINT *) new POINT[m_FFT_AllNum];//设定一个数组

		for (int i=0;i<m_FFT_AllNum;i++)
		{
			pPointArraySpectrumIndex[i].x = m_BaseXline+i*m_FFT_RealValueXInterval;
			pPointArraySpectrumIndex[i].y = m_rectCurve.top+pPointArraySpectrum[i].y*(-m_rectCurve.Height()/m_RealYRange);

		
			if (pPointArraySpectrumIndex[i].y  > m_RealBaseYLine+m_rectCurve.Height())
			{
				pPointArraySpectrumIndex[i].y=m_rectCurve.bottom;
			}
		}
		
		pDC->Polyline(pPointArraySpectrumIndex,m_FFT_AllNum);//将组成曲线的点全部绘制出来
		pDC->SelectObject(pOldPen);//释放画笔
		pDC->SelectClipRgn(NULL);
	}
	//I+Q绘制过程
	else if (m_IandQFlg)
	{
		CPen *pOldPen = pDC->SelectObject(&m_PenCurveA);//设置当前画笔为m_PenCurveA

		// I路绘图
		pPointArrayIndexA =(POINT *) new POINT[m_RealValuenSize];//设定一个数组

		for (int i=0;i<m_RealValuenSize;i++)
		{
			pPointArrayIndexA[i].x = m_BaseXline+i*m_RealValueXInterval;
			pPointArrayIndexA[i].y = m_RealBaseYLine+I_Data[i]*(-m_rectCurve.Height()/m_IQ_range/2.0);
			
		}
		
		pDC->Polyline(pPointArrayIndexA,m_RealValuenSize);//将组成曲线的点全部绘制出来
		pDC->SelectObject(pOldPen);//释放画笔
		pDC->SelectClipRgn(NULL);

		CPen *pOldPenB = pDC->SelectObject(&m_PenCurveB);//设置当前画笔为m_PenCurveB

		pPointArrayIndexB =(POINT *) new POINT[m_RealValuenSize];//设定一个数组
		for (int j=0;j<=m_RealValuenSize;j++)
		{
			pPointArrayIndexB[j].x = m_BaseXline+j*m_RealValueXInterval;
			pPointArrayIndexB[j].y = m_RealBaseYLine+Q_Data[j]*(-m_rectCurve.Height()/m_IQ_range/2.0);
			
		}
		
		pDC->Polyline(pPointArrayIndexB,m_RealValuenSize);//将组成曲线的点全部绘制出来
		pDC->SelectObject(pOldPenB);//释放画笔
		pDC->SelectClipRgn(NULL);
	}
	//I|Q绘制过程
	else
	{
		CPen *pOldPen = pDC->SelectObject(&m_PenCurveA);//设置当前画笔为m_PenCurveA

		pPointArrayIndexA =(POINT *) new POINT[m_RealValuenSize];//设定一个数组

		for (int i=0;i<=m_RealValuenSize;i++)
		{
			pPointArrayIndexA[i].x = m_BaseXline+i*m_RealValueXInterval;
			pPointArrayIndexA[i].y = m_RealBaseYLine+I_Data[i]*(-m_RatioY_IorQ);
			if( pPointArrayIndexA[i].y >= m_BaseYline-2*((m_rectCurve.Height()-30)/4)-30)
				pPointArrayIndexA[i].y =m_BaseYline-2*((m_rectCurve.Height()-30)/4)-30-1;
			if( pPointArrayIndexA[i].y <= m_rectCurve.top)
				pPointArrayIndexA[i].y =m_rectCurve.top+1;
		}
		
		pDC->Polyline(pPointArrayIndexA,m_RealValuenSize);//将组成曲线的点全部绘制出来
		pDC->SelectObject(pOldPen);//释放画笔
		pDC->SelectClipRgn(NULL);

		CPen *pOldPenB = pDC->SelectObject(&m_PenCurveB);//设置当前画笔为m_PenCurveB

		pPointArrayIndexB =(POINT *) new POINT[m_RealValuenSize];//设定一个数组
		for (int j=0;j<m_RealValuenSize;j++)
		{
			pPointArrayIndexB[j].x = m_BaseXline+j*m_RealValueXInterval;
			pPointArrayIndexB[j].y = m_RealBaseYLine2+Q_Data[j]*(-m_RatioY_IorQ);
			if( pPointArrayIndexB[j].y >= m_BaseYline)
				pPointArrayIndexB[j].y =m_BaseYline-1;
			/*if( pPointArrayIndexB[j].y <=  m_BaseYline-2*m_RatioY_IorQ)
			pPointArrayIndexB[j].y =m_BaseYline-2*m_RatioY_IorQ+1;*/
		}
		
		pDC->Polyline(pPointArrayIndexB,m_RealValuenSize);//将组成曲线的点全部绘制出来
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

    //将当前的曲线作为位图存入memDC中
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);//创建兼容dc
	CBitmap bitmap,*pOldBmp;
   //根据新的客户区大小创建兼容位图
	bitmap.CreateCompatibleBitmap(&dc,rect.Width(),rect.Height());
   //将位图bitmap传递给memDC
	pOldBmp = memDC.SelectObject(&bitmap);
   //重新绘制
	DrawGrid(&memDC);//调用绘制网格
	DrawAxis(&memDC);//调用绘制刻度
	DrawXYtitle(&memDC);//标题
	DrawCurveA(&memDC);//绘制曲线

    //将位图复制到dc中
	dc.BitBlt(m_rectCurve.left,m_rectCurve.top,m_rectCurve.Width(),m_rectCurve.Height(),
		&memDC,m_rectCurve.left,m_rectCurve.top,SRCCOPY);
	memDC.SelectObject(pOldBmp);//释放当前位图	
}
//控制曲线是否进行绘制的外部接口函数
void CW::runDraw()
{
	controlRunDraw = TRUE;
	Invalidate();  //窗口更新时重绘背景
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
	delete []I_Data;//接收点
	delete []Q_Data;
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