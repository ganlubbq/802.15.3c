// W.cpp : 实现文件
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "C.h"
#include "math.h"

// CC

IMPLEMENT_DYNAMIC(CC, CStatic)

CC::CC()
{
	controlRunDraw       = FALSE;//控制是否进行绘制曲线的标记
	m_ValueXRange        = 10;//X轴竖线个数10
	m_ValueYRange        = 6;//Y轴横线个数6

	m_ScaleValueYRange   = 0.000001;//Y轴起始值,0.000001
	m_ScaleValueXRange   = 0;//X轴起始值0
	m_ScaleValueXEnd     = 1.0;//X轴结束值7(调整横坐标最大范围）
	m_ScaleValueYEnd     = 1;//Y轴结束值0
	m_AllNum             =501;
	m_RealBaseYLine      = 0;
	m_RealValuenSize     = 0;//波形曲线点数初始化

	m_BkBrush.CreateSolidBrush(RGB(0,0,0));//背景，黑色
	m_CurveBrush.CreateSolidBrush(RGB(0,0,0));//网格线，黑色
	m_PenDarkLine.CreatePen(PS_SOLID,0,RGB(0x55,0x55,0x55));//网格线，暗线
	m_PenBrightLine.CreatePen(PS_SOLID,0,RGB(0xff,0xff,0xff));//网格线，明线

	//m_PenCurveA.CreatePen(PS_SOLID,1.5,RGB(0,128,0));//曲线画笔
	m_PenCurveA.CreatePen(PS_SOLID,2,RGB(0,128,0));//曲线画笔

	m_FontAxis.CreateFont(18,0,0,0,FW_THIN,FALSE,FALSE,FALSE,DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T("微软雅黑"));

}

CC::~CC()
{
}

BEGIN_MESSAGE_MAP(CC, CStatic)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CC 消息处理程序
BOOL CC::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rect;
	GetClientRect(&rect);//获取用户区域
	pDC->FillRect(&rect,&m_BkBrush);//Draw background填充最底层
	return CStatic::OnEraseBkgnd(pDC);
}

void CC::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	CRect rc;
	GetClientRect(&rc);//获取用户区域
	rc.InflateRect(0,0,0,0);//curve panel////curve panel确定显示框的大小和位置，距离左、上、右、下
	m_rectCurve = rc;//显示曲线
	m_rectCurve.InflateRect(-60,-35,-5,-40);//curve area确定黑色网格的总区域的大小
	CDC *pDC = GetDC();
	ValueTransform(pDC);//坐标转化
	DrawGrid(pDC);//绘制网格
	DrawAxis(pDC);//绘制刻度
	DrawXYtitle(pDC);//绘制标题

	if(controlRunDraw)
		Update();//更新曲线绘制

	// 不为绘图消息调用 CStatic::OnPaint()
}

//坐标转换函数
void CC::ValueTransform(CDC *pDC)
{
	m_RatioX = m_rectCurve.Width()/m_ValueXRange;//计算X轴比例
	m_RatioY = m_rectCurve.Height()/m_ValueYRange;//计算Y轴比例
	m_BaseXline = m_rectCurve.left;
	m_BaseYline = m_rectCurve.bottom;//XY轴基线
	m_RealValueXInterval = 1.0*m_rectCurve.Width()/(double)m_AllNum;////真实点的X轴间隔单位值
}
//绘制网格函数
void CC::DrawGrid(CDC *pDC)
{
	pDC->FillRect(&m_rectCurve,&m_CurveBrush);//画刷填充曲线面板

	CPen *pOldPen = pDC->SelectObject(&m_PenDarkLine);//设置m_PenDarkLine为默认画笔
	pDC->MoveTo(m_rectCurve.left,m_rectCurve.top);
	pDC->LineTo(m_rectCurve.left,m_rectCurve.bottom);
	pDC->MoveTo(m_rectCurve.left,m_rectCurve.top);
	pDC->LineTo(m_rectCurve.right,m_rectCurve.top);//用暗线勾画出面板的明暗对比效果
	
	int i;
	CString str;
	//	pDC->SelectObject(&m_PenGrid);//设置当前画笔为m_PenGrid
	//	pDC->SelectClipRgn(&m_rgnCurve);//设置当前默认区域为m_rgnCurve
	pDC->MoveTo(m_rectCurve.left,m_BaseYline);
	pDC->LineTo(m_rectCurve.right,m_BaseYline);	//绘制横向基线

	int nPosY;

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

	//用明线勾画出面板的明暗对比效果	
	pDC->SelectObject(&m_PenBrightLine);
	pDC->MoveTo(m_rectCurve.right,m_rectCurve.top);
	pDC->LineTo(m_rectCurve.right,m_rectCurve.bottom);
	pDC->MoveTo(m_rectCurve.left,m_rectCurve.bottom);
	pDC->LineTo(m_rectCurve.right,m_rectCurve.bottom);

	pDC->SelectObject(&pOldPen);//释放画笔
}

////数值刻度标记
void CC::DrawAxis(CDC *pDC)
{
	CFont *pOldFont;
	int j,nPosY;
	CString str;
	CString str_1;
	pOldFont = pDC->SelectObject(&m_FontAxis);//设置当前字体默认为Axis（数字字体）
	pDC->SetTextColor(RGB(255,255,255));//设置默认颜色为白色（数字颜色）
	pDC->SetBkMode(TRANSPARENT);//设置默认输入为透明
	pDC->SetTextAlign(TA_RIGHT|TA_BASELINE);//设置默认文本模式（右对齐，基线对齐）
	nPosY = m_BaseYline;

	//纵坐标
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
		//幅度刻度的表示形式

	}

	//横坐标
	pDC->SetTextAlign(TA_LEFT|TA_TOP);//设置默认文本为左对齐，置顶
	pDC->SetTextAlign(TA_CENTER|TA_TOP);

	//X轴起始值
	if (abs(m_ScaleValueXRange)<1&&m_ScaleValueXRange!=0)
		str.Format(_T("%.1f"),m_ScaleValueXRange);
	else
		str.Format(_T("%.0f"),m_ScaleValueXRange);
	pDC->TextOut(m_BaseXline+2,m_BaseYline+2,str);

	//X轴终点值
	if (abs(m_ScaleValueXEnd)<1&&m_ScaleValueXEnd!=0)
		str.Format(_T("%.1fdB"),m_ScaleValueXEnd);
	else
		str.Format(_T("%.0fdB"),m_ScaleValueXEnd);
	pDC->TextOut(m_rectCurve.right-12,m_BaseYline+2,str);
	//X轴刻度表示形式

	pDC->SetTextAlign(TA_RIGHT|TA_TOP);
	str="--dB";
	if(m_RealValuenSize!=0)
		str.Format(_T("max: %.2fdB"),m_maxCCDFX);
	else
	str.Format(_T("max:")); //初始化
	pDC->TextOut(m_rectCurve.right-m_rectCurve.Width()*0.25,m_rectCurve.bottom+2,str);//最后一点值
	pDC->SelectObject(&pOldFont);//释放当前字体

	m_RealBaseYLine = m_BaseYline-m_rectCurve.Height();//设置真实值基线

}
////XY轴标题设置
void CC::DrawXYtitle(CDC *pDC)//XY轴标题设置
{
	CFont *pOldFontTitle;
	CString str;

	pOldFontTitle = pDC->SelectObject(&m_FontAxis);//设置当前字体默认为Axis（数字字体）
	pDC->SetTextColor(RGB(0,255,0));//设置默认颜色为
	pDC->SetBkMode(TRANSPARENT);//设置默认输入为透明
	pDC->SetTextAlign(TA_LEFT|TA_TOP);//设置默认文本为左对齐，置顶
	pDC->SetTextAlign(TA_CENTER|TA_TOP);

	//X轴标题
	str="(Power/Avg.Power)/dB";
	pDC->TextOut(m_BaseXline+m_rectCurve.Width()/2,m_BaseYline+17,str);
	//头部标题
	pOldFontTitle = pDC->SelectObject(&m_FontAxis);//设置当前字体默认为Axis（数字字体）
	pDC->SetTextColor(RGB(0,128,0));//设置默认颜色为
	str="Wave CCDF";
	pDC->TextOut(m_BaseXline+10,m_BaseYline-m_rectCurve.Height()-24,str);
}
//绘制波形函数
void CC::DrawCurveA(CDC *pDC)
{
	CPen *pOldPen = pDC->SelectObject(&m_PenCurveA);//设置当前画笔为m_PenCurveA
	pPointArrayCCDFIndex =(POINT *) new POINT[m_AllNum];//设定一个数组
	//pPointArrayCCDFIndex[0].x=m_BaseXline;
	//pPointArrayCCDFIndex[0].y=m_RealBaseYLine;
	for (int flg=0;flg<m_AllNum;flg++)
	{
		pPointArrayCCDFIndex[flg].x = m_BaseXline+flg*m_RealValueXInterval;
		pPointArrayCCDFIndex[flg].y = m_RealBaseYLine+(-log10(pPointArrayCCDF[flg]))*(m_rectCurve.Height()/(double)m_ValueYRange);
	
		if(pPointArrayCCDFIndex[flg].y<m_RealBaseYLine)
			pPointArrayCCDFIndex[flg].y=m_RealBaseYLine+m_rectCurve.Height();
	}
	
	pDC->Polyline(pPointArrayCCDFIndex,m_AllNum);//将组成曲线的点全部绘制出来
	pDC->SelectObject(pOldPen);//释放画笔
	pDC->SelectClipRgn(NULL);
}

void CC::Update()
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
void  CC::runDraw()
{
	controlRunDraw = TRUE;
	Invalidate();
}