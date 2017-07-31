
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "Splash.h"
#include "htmlhelp.h"
#include "eiTemplateView.h"

#include "func.h"
#include <complex>

#include "MainFrm.h"
#include <iostream>
#include <fstream>
//#include "genParam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(ID_TEST, &CMainFrame::OnTest)
	ON_COMMAND(ID_HELP_DOC, &CMainFrame::OnHelpDoc)
	ON_COMMAND(ID_MAIN_RUN, &CMainFrame::OnMainRun)
	ON_COMMAND(ID_SYSTEM_CONFIG_WIZ, &CMainFrame::OnSystemConfigWiz)
	ON_COMMAND(ID_HARDWARE_CONNECTION_WIZ, &CMainFrame::OnHardwareConnectionWiz)
	ON_COMMAND(ID_MAIN_DOWNLOAD, &CMainFrame::OnMainDownload)//数据下载：绑定下载按钮
	ON_COMMAND(ID_BLUETOOTH_FRAME, &CMainFrame::OnFrameDiagram)
	ON_COMMAND(ID_DIAGRAM_MAC, &CMainFrame::OnDiagramMac)
END_MESSAGE_MAP()

/************************************************************************/
/* 状态栏中的几个选项资源标识                                           */
/************************************************************************/
static UINT indicators[]=
{
	ID_SEPARATOR,			//状态行指示器
	IDS_INSTRUMENT_STATE,	//仪器连接状态
	IDS_ERROR_INDICAROR,	//错误指示
	IDS_PROGRESS,			//进度条
};


// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
	m_bInitSplitter = FALSE;
	m_pass_to_thread.p_protocol_params = new BlueToothParams();//蓝牙参数
	m_pass_to_thread.p_protocol_params_3c = new Protocol_param_3C();//3C参数
	m_pass_to_thread.p_protocol_params_channel = new Protocol_param_channel();//信道参数
	b_instr_connected = FALSE;
	m_num_instr = 0;
	m_pass_to_thread.p_m_progress = &m_progress;   //主框架进度栏指针传入线程
}

CMainFrame::~CMainFrame()
{
	/************************************************************************/
	/* 关闭与仪器的连接                                                     */
	/************************************************************************/
	for (int i = 0;i<m_num_instr;i++)
	{
		viClose(vi[i]);
	}
	viClose(defaultRM);
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	/************************************************************************/
	/*添加工具栏                                                            */
	/************************************************************************/
	if (!m_wndToolBar.CreateEx(this,TBSTYLE_FLAT,WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}
	/*为工具栏设置背景颜色***************************************************/
	HBRUSH newBr=CreateSolidBrush(RGB(237,239,252));//RGB(237,239,252)
	SetClassLong(m_wndToolBar.m_hWnd,GCL_HBRBACKGROUND,(long)newBr);
	/*为工具栏添加自定义的图片，包括正常状态的图片，禁用的图片和激活的图片***/
	CImageList m_imgToolBar;//工具栏图标列表
	m_imgToolBar.Create(16,15,ILC_COLOR32|ILC_MASK,0,0);
	m_imgToolBar.Add(AfxGetApp()->LoadIcon(IDI_TOOLNEW_1));
	m_imgToolBar.Add(AfxGetApp()->LoadIcon(IDI_TOOLNEW_2));
	m_imgToolBar.Add(AfxGetApp()->LoadIcon(IDI_TOOLNEW_3));
	m_imgToolBar.Add(AfxGetApp()->LoadIcon(IDI_TOOLNEW_4));
	m_imgToolBar.Add(AfxGetApp()->LoadIcon(IDI_TOOLNEW_5));
	m_imgToolBar.Add(AfxGetApp()->LoadIcon(IDI_TOOLNEW_6));
	m_imgToolBar.Add(AfxGetApp()->LoadIcon(IDI_TOOLNEW_7));
	m_imgToolBar.Add(AfxGetApp()->LoadIcon(IDI_TOOLNEW_8));

	m_wndToolBar.GetToolBarCtrl().SetImageList(&m_imgToolBar);
	m_wndToolBar.GetToolBarCtrl().SetHotImageList(&m_imgToolBar);
	m_wndToolBar.GetToolBarCtrl().SetDisabledImageList(&m_imgToolBar);
	m_imgToolBar.Detach();//调用detach可以保证在局部变量销毁时m_imgToolBar不会出现内存问题
	m_wndToolBar.ShowWindow(SW_SHOW);
	
	/************************************************************************/
	/* 添加状态栏(工作状态指示，仪器连接情况，错误信息，进度条)             */
	/************************************************************************/
	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	m_wndStatusBar.SetPaneInfo(0,ID_SEPARATOR,SBPS_NORMAL,150);	//设置状态栏第一栏为工作状态指示
	m_wndStatusBar.SetPaneInfo(1,IDS_INSTRUMENT_STATE,SBPS_NORMAL,150);	//设置状态栏第二栏为仪器连接指示
	m_wndStatusBar.SetPaneInfo(2,IDS_ERROR_INDICAROR,SBPS_STRETCH ,0);	//设置状态栏第三栏为错误提示，为保证状态栏占据空间的完整，设为可拉伸的属性
	m_wndStatusBar.SetPaneInfo(3,IDS_PROGRESS,SBPS_NORMAL,200);	//设置状态栏最后一栏为进度条栏，准备放进度条在里面
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);	//显示状态栏

	/***********************在状态栏上创建进度条*****************************/
	CRect rect_progress;
	m_wndStatusBar.GetItemRect(3,&rect_progress);    //获取进度栏的大小
	m_progress.Create(WS_CHILD|WS_VISIBLE|PBS_SMOOTH,rect_progress,&m_wndStatusBar,IDC_PROGRESS);
	m_progress.SetRange(0,6);
	m_progress.SetStep(1);//步进
	m_progress.SetPos(0);//当前位置

	/************************************************************************/
	/* 设置主框架窗口的标题                                                 */
	/************************************************************************/
	SetWindowText("IEEE 802.15.3c宽带信号生成软件");

	/************************************************************************/
	/* 启动欢迎界面（调试时请注释下面两句）                                 */
	/************************************************************************/
	//CSplashWnd::ShowSplashScreen(this);
	//Sleep(2000);//欢迎界面的持续时间是2秒

	// TODO: 如果不需要可停靠工具栏，则删除这三行
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBar(&m_wndToolBar);

	CenterWindow();
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或样式
	cs.style &= ~FWS_ADDTOTITLE;
	cs.cx = 1127;
	cs.cy = 712;
	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序
BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类
	CRect cr; 
	GetClientRect( &cr);

	//将整个框架的客户区分为一行两列
	if ( !m_mainSplitter.CreateStatic( this, 1, 2 ,WS_CHILD/*|WS_BORDER*/|WS_VISIBLE) )
	{ 
		MessageBox( "Error setting up main splitter frames!", "Init Error!", MB_OK | MB_ICONERROR ); 
		return FALSE; 
	}
	//将第二列再分为两行一列，这样就形成了框架上的三个子块
	if ( !m_rightSplitter.CreateStatic( &m_mainSplitter, 2, 1 ,WS_CHILD/*|WS_BORDER*/|WS_VISIBLE,m_mainSplitter.IdFromRowCol(0,1)) )
	{ 
		MessageBox( "Error setting up right splitter frames!", "Init Error!", MB_OK | MB_ICONERROR ); 
		return FALSE; 
	}
	/************************************************************************/
	/* 为每个子显示区域生成相应的视图类                                     */
	/************************************************************************/
	//左侧的配置界面
	if ( !m_mainSplitter.CreateView(0, 0, RUNTIME_CLASS(CTabParent), CSize(500, cr.Height()), pContext ) ) 
	{ 
		MessageBox( "Error setting up splitter frames!", "Init Error!", MB_OK | MB_ICONERROR );
		return FALSE; 
	}
	//右上方的CCDF图
	if ( !m_rightSplitter.CreateView(0, 0, RUNTIME_CLASS(CGraphCCDF), CSize(cr.Width()-500, 300/*cr.Height()/2*/), pContext ) ) 
	{ 
		MessageBox( "Error setting up splitter frames!", "Init Error!", MB_OK | MB_ICONERROR );
		return FALSE; 
	}
	//右侧下方的波形图
	if ( !m_rightSplitter.CreateView( 1, 0, RUNTIME_CLASS(CGraphWAVE), CSize(cr.Width()-400, 300/*cr.Height()/2*/), pContext ) ) 
	{ 
		MessageBox( "Error setting up splitter frames!", "Init Error!", MB_OK | MB_ICONERROR );
		return FALSE;
	}

	m_bInitSplitter = TRUE;
	return TRUE;
}


void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);
	/************************************************************************/
	/*本函数实现了主框架缩放时右侧波形图的按比例缩放和图像最小值的定义和保护*/
	/************************************************************************/
	if (nType == SIZE_MINIMIZED)	//最小化会使客户区宽高为0，所以这里必须跳过
	{
		return;
	}
	//左右分割窗口的控制(定义左侧面板的最小宽度为200，右侧面板的最小宽度为35)
	int widthLeft = 0;	//左侧面板的宽度
	int widthLeftMin = 0;
	int widthRight = 0;	//右侧面板的宽度
	int widthRightMin = 0;
	//左右两个分割窗口的最小宽度控制
	if ( m_rightSplitter.GetSafeHwnd() != NULL && m_bInitSplitter )
	{
		m_mainSplitter.GetColumnInfo(0,widthLeft,widthLeftMin);
		m_mainSplitter.GetColumnInfo(1,widthRight,widthRightMin);
		if (widthLeft<=200)
		{
			m_mainSplitter.SetColumnInfo(0,200,0);
			m_mainSplitter.SetColumnInfo(1,cx-11-200,0);
		}
		if (widthRight<=35)
		{
			m_mainSplitter.SetColumnInfo(0,cx-11-35,0);
			m_mainSplitter.SetColumnInfo(1,35,0);
		}
		m_mainSplitter.RecalcLayout();
	}
	//上下分割面板的控制（定义上下面板的高度最小值均为30）
	int heightRightTop = 0;		//右上方面板的高度
	int heightRightTopMin = 0;
	int heightRightBottom = 0;	//右下方面板的高度
	int heightRightBottomMin = 0;
	//上下两个分割面板的比例控制
	double x = m_rightSplitter.m_splitterScale;	//取出当前窗口分割的比例
	if ( m_rightSplitter.GetSafeHwnd() != NULL && m_bInitSplitter )
	{
		m_rightSplitter.SetRowInfo(0,(int)((cy-54)*x),0);
		m_rightSplitter.SetRowInfo(1,cy-(int)((cy-54)*x),0);
		m_rightSplitter.RecalcLayout();
	}
	//上下两个分割面板的最小高度控制
	if ( m_rightSplitter.GetSafeHwnd() != NULL && m_bInitSplitter )
	{
		m_rightSplitter.GetRowInfo(0,heightRightTop,heightRightTopMin);
		m_rightSplitter.GetRowInfo(1,heightRightBottom,heightRightBottomMin);
		if (heightRightTop<=30)
		{
			m_rightSplitter.SetRowInfo(0,30,0);
			m_rightSplitter.SetRowInfo(1,cy-54-30,0);
		}
		if (heightRightBottom<=30)
		{
			m_rightSplitter.SetRowInfo(0,cy-54-30,0);
			m_rightSplitter.SetRowInfo(1,30,0);
		}
		m_rightSplitter.RecalcLayout();
	}
}


void CMainFrame::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// 不为绘图消息调用 CFrameWnd::OnPaint()

	/************************************************************************/
	/*重绘和移动状态栏上的进度条                                            */
	/************************************************************************/
	CRect rect_progress;
	m_wndStatusBar.GetItemRect(3,&rect_progress);
	if (!m_progress.m_hWnd)
		m_progress.Create(WS_CHILD|WS_VISIBLE|PBS_SMOOTH,rect_progress,&m_wndStatusBar,IDC_PROGRESS);
	else
		m_progress.MoveWindow(rect_progress);
}



void CMainFrame::OnHelpDoc()//打开帮助文档
{
	/************************************************************************/
	/*下面这种方法也凑合，但是相当于在本程序之外又打开了一个帮助文档实例，有*/
	/*失软件著作的专业性													*/
	/************************************************************************/
	//::ShellExecute(NULL, "open", "test.chm", NULL, NULL, SW_SHOW);
	
	/************************************************************************/
	/*在安装软件的时候可以将帮助文档的路径写入注册表替换现在直接调用文件名的*/
	/*方法，这样会使帮助文档作为应用程序的一部分打开，应用程序关闭的时候帮助*/
	/*随之关闭，体现了软件的专业性											*/
	/************************************************************************/
	::HtmlHelp(this->m_hWnd,"16de_help.chm",HH_DISPLAY_TOPIC,NULL);
	/*::HtmlHelp(this->m_hWnd,_T("16de_help.chm.chm"),HH_DISPLAY_TOPIC,NULL);*/
}



void CMainFrame::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	/************************************************************************/
	/* 设置主框架窗口能够缩到的最小值                                       */
	/************************************************************************/
	lpMMI->ptMinTrackSize.x = 650;
	lpMMI->ptMinTrackSize.y = 300;
}


void CMainFrame::OnTest()//测试接口
{
	//for (int i = 0;i<50;i++)//测试进度条
	//{
	//	m_progress.StepIt();
	//	Sleep(10);
	//}

	////微电子所测试要求格式探索
	//char temp[32] = "";
	//CString str="";
	//itoa(1023,temp,2);
	//str.Format("%010s",temp);
	//MessageBox(str);

	/************************************************************************/
	/* 测试仪器连接和数据读取                                               */
	/************************************************************************/
	ViStatus error_no = 0;
	ViUInt32 cnt = 0;
	ViUInt32  length_max = 100;
	ViSession testRM;
	ViSession test_vi;
	char ch[256] = "";
	double freq = 0;
	error_no = viOpenDefaultRM(&testRM);
	Sleep(10);
	error_no = viOpen(testRM,"TCPIP0::172.141.114.253::5001::SOCKET",VI_NULL,VI_NULL,&test_vi);
	Sleep(10);
	//error_no = viOpen(testRM,"TCPIP0::127.0.0.1::5001::SOCKET",VI_NULL,VI_NULL,&test_vi);
	error_no = viSetAttribute(test_vi,VI_ATTR_TMO_VALUE,2000);
	Sleep(10);
	error_no = viSetAttribute(test_vi,VI_ATTR_TERMCHAR_EN,VI_TRUE);
	Sleep(10);
	error_no = viSetAttribute(test_vi,VI_ATTR_TERMCHAR,'\n');
	Sleep(10);
	//error_no = viPrintf(test_vi,"*RST\n");//写仪器参数
	//Sleep(100);

	//error_no = viWrite(test_vi,(ViBuf)"FREQ?\n",length_max,&cnt);//写查询命令
	//Sleep(100);
	//error_no = viRead(test_vi,(ViBuf)ch,length_max,&cnt);//读取相应的数据

	//error_no = viPrintf(test_vi,"FREQ?\n");//写查询命令
	//error_no = viScanf(test_vi,"%t",ch);
	
	//ch[cnt] = '\0';
	//error_no = viWrite(test_vi,(ViBuf)"FREQ 1GHZ\n",length_max,&cnt);
	//error_no = viWrite(test_vi,(ViBuf)"POW 10dBm\n",length_max,&cnt);
	//error_no = viWrite(test_vi,(ViBuf)"OUTP ON\n",length_max,&cnt);
	//error_no = viWrite(test_vi,(ViBuf)"POW:ALC:STAT OFF\n",length_max,&cnt);

	//error_no = viQueryf(test_vi,"POW?\n","%t",ch);
	//error_no = viQueryf(test_vi,"FREQ?\n","%t",ch);
	//error_no = viQueryf(test_vi,"OUTP?\n","%t",ch);
	//error_no = viQueryf(test_vi,"*IDN?\n","%t",ch);
	//MessageBox(ch);
	//error_no = viQueryf(test_vi,"POW:ALC:STAT?\n","%t",ch);

	/************************************************************************/
	/* 文件传输                                                             */
	/************************************************************************/
	INT32 NMBYTE = 13060;
	INT32 nBlockNum = 2 * NMBYTE;
	char *SendData = NULL;
	UINT64 response = 0;
	INT32 nReadByte = 0;

	//do 
	//{
	//	nBlockNum -= NMBYTE;
	//	if (nBlockNum<=0)
	//	{
	//		break;
	//	}
	//	SendData = new char[nBlockNum];
	//} while (SendData == NULL);

	//
	//memset(SendData,0,nBlockNum);

	//CFile filedata;
	//CString CFilename = _T("NewSignalData.seg");
	//filedata.Open(CFilename.GetBuffer(),CFile::modeRead);
	//error_no = viWrite(test_vi,(ViBuf)"MEMORY:DATA NewSignalData2.seg,#513060\n",39,&cnt);///////////
	//filedata.SeekToBegin();
	//nReadByte = filedata.Read((void*)SendData,nBlockNum);
	//error_no = viWrite(test_vi,(unsigned char*)SendData,13060,&cnt);
	
	Sleep(100);
	//error_no = viWrite(test_vi,(ViBuf)"RADIO:ARB:SEQUENCE NONE,NewSignalData1.seg,1,NONE\n",100,&cnt);
	//error_no = viWrite(test_vi,(ViBuf)"RADIO:ARB:SEQUENCE wlan,NewSignalData0.seg,1,NONE,NewSignalData1.seg,1,NONE,NewSignalData2.seg,1,NONE,NewSignalData3.seg,1,NONE\n",100,&cnt);
	//error_no = viWrite(test_vi,(ViBuf)"RADIO:ARB:SEQUENCE wlan,NewSignalData0.seg,1,NONE\n",100,&cnt);
	//error_no = viWrite(test_vi,(ViBuf)"RADIO:ARB:SEQUENCE wlan,NewSignalData0.seg,1,NONE,NewSignalData1.seg,1,NONE,NewSignalData2.seg,1,NONE,NewSignalData3.seg,1,NONE\n",1000,&cnt);
	error_no = viWrite(test_vi,(ViBuf)"RADIO:ARB:SEQUENCE NONE,NewSignalData0.seg,10,NONE,NewSignalData1.seg,1,NONE,NewSignalData2.seg,1,M1,NewSignalData3.seg,1,M1M2\n",1000,&cnt);
	error_no = viWrite(test_vi,(ViBuf)"RADIO:ARB:STATE ON\n",19,&cnt);//下载并播放
	Sleep(100);



	error_no = viClear(test_vi);
	Sleep(10);
	error_no = viClose(test_vi);
	Sleep(10);
	error_no = viClose(testRM);

	//sprintf(str,"%d",GetSystemMetrics(SM_CXSIZEFRAME));//获取分隔条的宽度
	//MessageBox(str);
	//((CGraphWAVE*)m_rightSplitter.GetPane(1,0))->Run();
}

void CMainFrame::OnMainRun()//物理层程序处理
{
	// TODO: 在此添加命令处理程序代码
	m_pass_to_thread.p_graphCCDF = (CGraphCCDF*)(m_rightSplitter.GetPane(0,0));
	m_pass_to_thread.p_graphWAVE = (CGraphWAVE*)(m_rightSplitter.GetPane(1,0));
	draw_thread_id = AfxBeginThread(ThreadFune,&m_pass_to_thread);
}


UINT ThreadFune(LPVOID lpParam)
{
	CC* p_ccdf;
	CW* p_wave;
	data_and_graph *DataAndGraph = (data_and_graph *)lpParam;
	p_ccdf = &(DataAndGraph->p_graphCCDF->m_ccdf);
	p_wave = &(DataAndGraph->p_graphWAVE->m_wave);


	//在绘图过程中禁用掉两个图像显示窗口上的comboBox，避免误操作产生异常
	DataAndGraph->p_graphCCDF->m_comboCCDF.EnableWindow(FALSE);
	DataAndGraph->p_graphWAVE->m_comboWAVE.EnableWindow(FALSE);
	
	int i,j,m,n,N=0,Num_of_space,m_AllNum,ScaleXend;
	double max_power;
	double max_specturm;
	double max_ccdf;
	CProgressCtrl *p_m_progress = DataAndGraph->p_m_progress;
	/************************************************************************/
	/* 生成蓝牙基带信号                                                     */
	/************************************************************************/
	//int Packet_len;//基带未经过采样生成的数据长度
	//int data_inlen;//输入01比特的长度
	//int sig_len;//整个基带信号（包括过采样）的数据长度
	//char bit_source[192]={0,1,0,1,0,0,1,1,1,1,1,1,0,0,1,0,1,0,1,0,0,0,1,1,0,0,1,1,1,1,0,1,1,1,0,1,0,1,1,0,1,0,0,1,1,0,1,1,0,1,0,1,0,0,1,1,1,1,1,1,0,0,1,0,1,0,1,0,0,0,1,1,0,0,1,1,1,1,0,1,1,1,0,1,0,1,1,0,1,0,0,1,1,0,1,1,0,1,0,1,0,0,1,1,1,1,1,1,0,0,1,0,1,0,1,0,0,0,1,1,0,0,1,1,1,1,0,1,1,1,0,1,0,1,1,0,1,0,0,1,1,0,1,1,0,1,0,1,0,0,1,1,1,1,1,1,0,0,1,0,1,0,1,0,0,0,1,1,0,0,1,1,1,1,0,1,1,1,0,1,0,1,1,0,1,0,0,1,1,0,1,1};
	//data_inlen = sizeof(bit_source)/sizeof(bit_source[0]);
	//double I_gfsk[30000]={0};//用于存储I路数据
	//double Q_gfsk[30000]={0};//用于存储Q路数据
	//bluetooth_waveform_generator(DataAndGraph->p_protocol_params,I_gfsk,Q_gfsk,bit_source,data_inlen,Packet_len);
	//sig_len = Packet_len * DataAndGraph->p_protocol_params->oversample;

	//ofstream of("data.txt");
	//for (i = 0;i<sig_len;i++)
	//{
	//	of<<Q_gfsk[i]<<endl;
	//}
	//of.close();

	/* 生成3c基带信号 */
	/************************************************************************/
	//HSI_param HSI_p;//HSI参数设置
	//HSI_p.Nfram = 1;
	//HSI_p.modtype = 2;
	//HSI_p.FECrate = 0;
	//HSI_p.sp = 1;
	//HSI_p.L_mh = 272;
	//HSI_p.Agr = 0;
	//HSI_p.UEP = 0;
	//HSI_p.MCS = 1;
	//HSI_p.L_fram = 336 * 16;
	//HSI_p.pretype = 1;
	//HSI_p.Bt = 0;
	//HSI_p.Llat = 0;
	//HSI_p.bits_inter = 1;
	//HSI_p.PCES = 0;
	//HSI_p.skewed_map = 0;
	//for (int i = 0; i < 10; ++i)
	//	HSI_p.Rsv[i] = 0;
	//vector<int> macheader_HSI;
	//gen_prbs(macheader_HSI, HSI_p.L_mh);//产生macheader
	//vector<int> macbody_HSI;
	//gen_prbs(macbody_HSI, HSI_p.L_fram);//产生macbody
	//vector<complex<double> > HSI_PHY;
	//genHSI(macbody_HSI, macheader_HSI, HSI_PHY, HSI_p);
	p_m_progress->SetPos(0);
	int Nheader_3c = gen_lmh_3c(*(DataAndGraph->p_protocol_params_3c));
	int Nbody_3c = gen_lmb_3c(*(DataAndGraph->p_protocol_params_3c));
	vector<int> macheader;
	vector<int> macbody;
	int source_type = DataAndGraph->p_protocol_params_3c->data_source;
	char *filepath_sc_temp = DataAndGraph->p_protocol_params_3c->filepath_ds;
	//gen_prbs(macheader, Nheader_3c);//产生macheader
	//gen_prbs(macbody, Nbody_3c);//产生macbody
	macheader = GenerateSource(source_type, Nheader_3c, 10, filepath_sc_temp);
	macbody = GenerateSource(source_type, Nbody_3c, 10, filepath_sc_temp);
	vector<complex<double> > dataout;
	vector<complex<double> > dataout_chan;
	p_m_progress->StepIt();
	waveform_generator_3c(macheader, macbody, dataout, *DataAndGraph->p_protocol_params_3c);
	p_m_progress->StepIt();
	int sig_len = 0;
	if ((*DataAndGraph->p_protocol_params_channel).chanel_switch == 0)
		sig_len = dataout.size();//整个基带信号（包括过采样）的数据长度
	else
	{
		tg3c_tsv_eval_r7((*DataAndGraph->p_protocol_params_channel).cm_num,(*DataAndGraph->p_protocol_params_channel).fc,dataout,dataout_chan);
		sig_len = dataout_chan.size();
	}
	double I_Q_max=0.0,I_data,Q_data=0.0;
	double *I_gfsk=new double[sig_len];
	double *Q_gfsk=new double[sig_len];
	double real_temp = 0;
	double imag_temp = 0;
	double IQ_gain = DataAndGraph->p_protocol_params_3c->IQ_gain;
	double qAngleAD = DataAndGraph->p_protocol_params_3c->quan_angle_adjust;
	if ((*DataAndGraph->p_protocol_params_channel).chanel_switch == 0)
	{
		for (int i = 0; i < sig_len; ++i)
		{
			real_temp = dataout[i].real() - pow(10,(IQ_gain/10))*sin(qAngleAD)*dataout[i].imag();
			imag_temp = pow(10,(IQ_gain/10))*cos(qAngleAD)*dataout[i].imag();
			I_gfsk[i]=real_temp;
			Q_gfsk[i]=imag_temp;
			I_data =abs(real_temp);
			Q_data =abs(imag_temp);
            if(I_Q_max<max(I_data,Q_data))
				I_Q_max =max(I_data,Q_data);
			
		}
		//if(I_Q_max<0.1)
		//	I_Q_max =1;
		p_wave->m_IQ_range =I_Q_max;
	}
	else
	{
		for (int i = 0; i < sig_len; ++i)
		{
			I_gfsk[i]=dataout_chan[i].real();
			Q_gfsk[i]=dataout_chan[i].imag();
			I_data =abs(dataout_chan[i].real());
			Q_data =abs(dataout_chan[i].imag());
			if(I_Q_max<max(I_data,Q_data))
				I_Q_max =max(I_data,Q_data);

		}
		//if(I_Q_max<0.1)
		//	I_Q_max =1;
		p_wave->m_IQ_range =I_Q_max;
	}
	p_m_progress->StepIt();
	///************************************************************************/
	///* 生成 41 要求格式的信号文件   //数据下载copy!!!!step3!!!!                   */
	///************************************************************************/
	//CFile file;
	//file.Open(_T("bluetooth.seg"),CFile::modeCreate|CFile::modeWrite);
	//CArchive ar(&file,CArchive::store);//写操作

	////256字节头部
	//char ei41Name[8] = {'e','i','4','1'};//公司名称
	//for (int i=0;i!=8;i++)
	//	ar<<ei41Name[i];

	//INT64 timeFrequency = 1000000;//1MHz时钟频率
	//ar<<timeFrequency;

	//INT64 elementLength = 1;//码元长度
	//ar<<elementLength;

	//INT64 samplePoints = 1;//过采样点数
	//ar<<samplePoints;

	//INT64 points = sig_len;//样点个数
	//ar<<points;

	//INT64 cycleTime = points / timeFrequency * 1000;//周期 = 样点个数*时钟频率 毫秒为单位；
	//ar<<cycleTime;

	//INT64  padBits[26]={0};//填充208位字节
	//for (int i =0;i!=26;i++)
	//	ar<<padBits[i];

	////基带信号数据段
	//for (int i=0;i!=sig_len;i++)
	//{
	//	ar<<(INT16)(I_gfsk[i]*23347200)<<(INT16)(Q_gfsk[i]*23347200);
	//}

	//ar.Close();
	//file.Close();
	//DataAndGraph->file_size = 256 + sig_len * 2 * 2; // 每个sig_len有2字节，一个长度对应实部和虚部两位，所以最后乘以4
	/************************************************************************/
	/************************************************************************/
	/* WAVE图绘制（I+Q、I|Q、power、Spectrum）                              */
	/************************************************************************/
	p_wave->m_RealValuenSize = sig_len;	//运行生成的数据长度
	p_wave->m_ScaleValueXEnd = sig_len;
	/**********I+Q 数据导入绘图类**********/
		p_wave->I_Data = I_gfsk;
		p_wave->Q_Data = Q_gfsk;
	/**********Power图的绘制**********/
	p_wave->pPointArrayPower =(POINT *) new POINT[sig_len];
	max_power=pow(I_gfsk[0],2)+pow(Q_gfsk[0],2);
	//找到功率最大点
	for (j=0;j<sig_len;j++)
	{
		double temp = pow(I_gfsk[j],2)+pow(Q_gfsk[j],2);
		if (temp > max_power)
		{
			max_power = temp;
		}
		//max_power = temp > max_power ? temp : max_power;
	}
	//计算每个信号点相对于最大功率点的dB值
	for (j=0;j<sig_len;j++)
	{
		p_wave->pPointArrayPower[j].x=long(j);
		p_wave->pPointArrayPower[j].y=10*log10((pow(I_gfsk[j],2)+pow(Q_gfsk[j],2))/max_power);
	}
	p_m_progress->StepIt();
	/**********Spectrum的绘制**********/
	//数组转容器
	vector<complex<double>> data_in;
	if (sig_len > 65536)
	{
		sig_len = 65536;
		for (m=0;m<sig_len;m++)
		{
			data_in.push_back(complex<double>(I_gfsk[m],Q_gfsk[m]));
		}
	}
	else
	{
		for (m=0;m<sig_len;m++)
		{
			data_in.push_back(complex<double>(I_gfsk[m],Q_gfsk[m]));
		}
	}
	
	//FFT计算频谱
	N = FFT(data_in,sig_len);
	//FFTShift(data_in);//频谱搬移，先注释掉
	p_wave->pPointArraySpectrum =(POINT *) new POINT[N];

	p_wave->m_FFT_AllNum=N;
	//max_specturm
	max_specturm=abs(data_in[0]);
	for(m=1;m<N;m++)
	{
		if(abs(data_in[m])>max_specturm)
			max_specturm=abs(data_in[m]);
	}

	for (m=0;m<N;m++)
	{
		p_wave->pPointArraySpectrum[m].x=long(m);
		p_wave->pPointArraySpectrum[m].y=10*log10(abs(data_in[m])/max_specturm);
	}
	p_wave->IorQFlg();	//图像生成完毕后首先显示I|Q图像
	p_m_progress->StepIt();
	/************************************************************************/
	/* CCDF图的绘制                                                         */
	/************************************************************************/
	p_ccdf->m_RealValuenSize = sig_len;

	double *pPointArrayCCDF;
	//设定一个中间变量数组，存放实际数据的功率
	pPointArrayCCDF =(double*)new double[sig_len];

	//CCDF设定一个数组，固定长度
	//确定间隔个数 == X轴总点数-1
	Num_of_space=(p_ccdf->m_AllNum)-1;
	m_AllNum=p_ccdf->m_AllNum;
	ScaleXend=p_ccdf->m_ScaleValueXEnd;
	p_ccdf->pPointArrayCCDF=(double*)new double[m_AllNum];
	//计算功率
	for (i=0;i<sig_len;i++)
	{
		pPointArrayCCDF[i]=pow(I_gfsk[i],2)+pow(Q_gfsk[i],2);
	}

	max_ccdf=sumCCDF(p_ccdf->pPointArrayCCDF,pPointArrayCCDF,sig_len,ScaleXend,Num_of_space);
	//ofstream of("data.txt");
	//for (i = 0;i<Num_of_space;i++)
	//{
	//	of<<p_ccdf->pPointArrayCCDF[i]<<endl;
	//}
	//of.close();

	p_ccdf->m_maxCCDFX=max_ccdf;

	
	p_ccdf->runDraw();

	p_m_progress->StepIt();
	//在图像的绘制操作完成后，再使能两个图像上的comboBox
	DataAndGraph->p_graphCCDF->m_comboCCDF.SetCurSel(0);
	DataAndGraph->p_graphWAVE->m_comboWAVE.SetCurSel(0);
	DataAndGraph->p_graphCCDF->m_comboCCDF.EnableWindow(TRUE);
	DataAndGraph->p_graphWAVE->m_comboWAVE.EnableWindow(TRUE);

	return 0;
}

void CMainFrame::OnSystemConfigWiz()
{
	// TODO: 在此添加命令处理程序代码
	CSysConfigWizard wzd("系统配置向导",this,0);
	//将当前的连接信息传入向导，如果重新设置了连接信息，由向导将其关闭
	wzd.defaultRM = defaultRM;
	for (int i = 0;i<8;i++)
	{
		wzd.vi[i] = vi[i];
	}
	//下面是向导退出后的一些操作
	if (ID_WIZFINISH == wzd.DoModal() && wzd.b_instr_connected)
	{
		b_instr_connected = TRUE;
		m_num_instr = wzd.m_num_instruments;
		defaultRM = wzd.defaultRM;

		CTabInstrument* p_tab_instrument = &(((CTabParent*)m_mainSplitter.GetPane(0,0))->m_tabInstrument);
		CTabInstrument &T_INSTRU = ((CTabParent*)(((CMainFrame*)AfxGetMainWnd())->m_mainSplitter.GetPane(0,0)))->m_tabInstrument;//根据仪器参数修改界面
		p_tab_instrument->m_combo_instrument_index.ResetContent();//将仪器配置页的仪器索引清空
		p_tab_instrument->send_command_enabled = TRUE;//将仪器配置页实时更新仪器状态的功能打开

		CString str_temp = "";
		char ch[256] = "";
		ViStatus error_no = 0;
		ViUInt32 write_cnt = 0;
		ViUInt32 read_cnt = 0;
		for(int i = 0;i<m_num_instr;i++)
		{
			vi[i] = wzd.vi[i];

			str_temp.Format("%d",i+1);
			p_tab_instrument->m_combo_instrument_index.InsertString(i,str_temp);
			//读取FREQ
			error_no = viWrite(vi[i],(ViBuf)"FREQ?\n",256,&write_cnt);//写查询命令
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//读取相应的数据
			ch[read_cnt-1] = '\0';//将返回的'\n'置为'\0',避免回车键对配置的影响
			str_temp.Format("%sHz",ch);
			p_tab_instrument->instr_params[i].frequency = str_temp;
			//读取POW
			error_no = viWrite(vi[i],(ViBuf)"POW?\n",256,&write_cnt);//写查询命令
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//读取相应的数据
			ch[read_cnt-1] = '\0';
			str_temp.Format("%sdBm",ch);
			p_tab_instrument->instr_params[i].amplitude = str_temp;
			//读取射频开关状态
			error_no = viWrite(vi[i],(ViBuf)"OUTP?\n",256,&write_cnt);//写查询命令
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//读取相应的数据
			ch[read_cnt-1] = '\0';
			str_temp.Format("%s",ch);
			p_tab_instrument->instr_params[i].RF_output = atoi(str_temp.GetBuffer())==0 ? "OFF" : "ON";
			//读取IQ调整(DM:IQAD:STAT)
			error_no = viWrite(vi[i],(ViBuf)"DM:IQAD:STAT?\n",256,&write_cnt);//写查询命令
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//读取相应的数据
			ch[read_cnt-1] = '\0';
			str_temp.Format("%s",ch);
			if (atoi(str_temp.GetBuffer())==1)//通过读取的状态更改界面
			{
				T_INSTRU.p_I_offset->Enable(TRUE);
				T_INSTRU.p_Q_offset->Enable(TRUE);
				T_INSTRU.p_IQ_gain_balance->Enable(TRUE);
				T_INSTRU.p_quadrature_angle_adjustment->Enable(TRUE);
			}
			else
			{
				T_INSTRU.p_I_offset->Enable(FALSE);
				T_INSTRU.p_Q_offset->Enable(FALSE);
				T_INSTRU.p_IQ_gain_balance->Enable(FALSE);
				T_INSTRU.p_quadrature_angle_adjustment->Enable(FALSE);
			}
			p_tab_instrument->instr_params[i].IQ_ADJ = atoi(str_temp.GetBuffer())==0 ? "OFF" : "ON";
			//读取I偏置
			error_no = viWrite(vi[i],(ViBuf)"DM:IQAD:IOFF?\n",256,&write_cnt);//写查询命令
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//读取相应的数据
			ch[read_cnt-1] = '\0';//将返回的'\n'置为'\0',避免回车键对配置的影响
			str_temp.Format("%s%s",ch,"%");
			p_tab_instrument->instr_params[i].I_offset = str_temp;
			//读取Q偏置
			error_no = viWrite(vi[i],(ViBuf)"DM:IQAD:QOFF?\n",256,&write_cnt);//写查询命令
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//读取相应的数据
			ch[read_cnt-1] = '\0';//将返回的'\n'置为'\0',避免回车键对配置的影响
			str_temp.Format("%s%s",ch,"%");
			p_tab_instrument->instr_params[i].Q_offset = str_temp;
			//读取IQ均衡增益
			error_no = viWrite(vi[i],(ViBuf)"DM:IQAD:GAIN?\n",256,&write_cnt);//写查询命令
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//读取相应的数据
			ch[read_cnt-1] = '\0';//将返回的'\n'置为'\0',避免回车键对配置的影响
			str_temp.Format("%sdB",ch);
			p_tab_instrument->instr_params[i].IQ_gain_balance = str_temp;
			//读取IQ正交偏离
			error_no = viWrite(vi[i],(ViBuf)"DM:IQAD:QSK?\n",256,&write_cnt);//写查询命令
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//读取相应的数据
			ch[read_cnt-1] = '\0';//将返回的'\n'置为'\0',避免回车键对配置的影响
			str_temp.Format("%sDeg",ch);
			p_tab_instrument->instr_params[i].quadrature_angle_adjustment = str_temp;
			//读取ALC状态
			error_no = viWrite(vi[i],(ViBuf)"POW:ALC:STAT?\n",256,&write_cnt);//写查询命令
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//读取相应的数据
			ch[read_cnt-1] = '\0';
			str_temp.Format("%s",ch);
			if (atoi(str_temp.GetBuffer())==1)
			{
				T_INSTRU.p_power_search_method->Enable(FALSE);
				T_INSTRU.p_power_search_ref->Enable(FALSE);
			}
			else
			{
				T_INSTRU.p_power_search_method->Enable(TRUE);
				T_INSTRU.p_power_search_ref->Enable(TRUE);
			}
			p_tab_instrument->instr_params[i].ALC = atoi(str_temp.GetBuffer())==0 ? "OFF" : "ON";
			//读取ALC带宽
			error_no = viWrite(vi[i],(ViBuf)"POW:ALC:BAND:AUTO?\n",256,&write_cnt);//写查询命令
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//读取相应的数据
			ch[read_cnt-1] = '\0';
			str_temp.Format("%s",ch);
			if (atoi(str_temp.GetBuffer())==1)
			{
				p_tab_instrument->instr_params[i].ALC_band = "ON";
			}
			else//查询手动ALC带宽设置
			{
				error_no = viWrite(vi[i],(ViBuf)"POW:ALC:BAND?\n",256,&write_cnt);//写查询命令
				Sleep(10);
				error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//读取相应的数据
				ch[read_cnt-1] = '\0';
				str_temp.Format("%s",ch);
				p_tab_instrument->instr_params[i].ALC_band = str_temp;
			}
			//p_tab_instrument->instr_params[i].ALC_band = atoi(str_temp.GetBuffer())==1 ? "OFF" : "ON";
			//读取ALC搜索参考
			error_no = viWrite(vi[i],(ViBuf)"POW:ALC:SEAR:REF?\n",256,&write_cnt);//写查询命令
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//读取相应的数据
			ch[read_cnt-1] = '\0';
			str_temp.Format("%s",ch);
			p_tab_instrument->instr_params[i].ALC_search_ref = str_temp=="FIX" ? "固定" : "调制";
			//读取搜索模式
			error_no = viWrite(vi[i],(ViBuf)"POW:ALC:SEAR?\n",256,&write_cnt);//写查询命令
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//读取相应的数据
			ch[read_cnt-1] = '\0';
			str_temp.Format("%s",ch);
			p_tab_instrument->instr_params[i].ALC_search_method = atoi(str_temp.GetBuffer())==0 ? "手动" : "自动";
			//读取时钟类型
			error_no = viWrite(vi[i],(ViBuf)"RAD:ARB:SEQ:CLOCK?\n",256,&write_cnt);//写查询命令
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//读取相应的数据
			ch[read_cnt-1] = '\0';
			str_temp.Format("%s",ch);
			if (str_temp=="CURR")//通过读取的状态更改界面
			{
				T_INSTRU.p_ARB_clock_freq->Enable(FALSE);
				str_temp.Format("%s","不变");
			}
			else if (str_temp=="HIGH")
			{
				T_INSTRU.p_ARB_clock_freq->Enable(FALSE);
				str_temp.Format("%s","最高");
			}
			else
			{
				T_INSTRU.p_ARB_clock_freq->Enable(TRUE);
				str_temp.Format("%s","自定义");
			}
			p_tab_instrument->instr_params[i].ARB_clock_type = str_temp;
			//读取ARB时钟频率
			error_no = viWrite(vi[i],(ViBuf)"RAD:ARB:SCL:RATE?\n",256,&write_cnt);//写查询命令
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//读取相应的数据
			ch[read_cnt-1] = '\0';//将返回的'\n'置为'\0',避免回车键对配置的影响
			str_temp.Format("%.6f MHz",atof(ch)/1000000);
			p_tab_instrument->instr_params[i].ARB_clock_freq = str_temp;
			//读取触发模式
			error_no = viWrite(vi[i],(ViBuf)"RAD:CUST:TRIG:TYPE?\n",256,&write_cnt);//写查询命令
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//读取相应的数据
			ch[read_cnt-1] = '\0';
			str_temp.Format("%s",ch);
			if (str_temp=="CONT")//通过读取的状态更改界面
			{
				T_INSTRU.p_trigger_cont_type->Enable(TRUE);
				T_INSTRU.p_trigger_gate_type->Enable(FALSE);
				str_temp.Format("%s","连续");
			}
			else if (str_temp=="SING")
			{
				T_INSTRU.p_trigger_cont_type->Enable(FALSE);
				T_INSTRU.p_trigger_gate_type->Enable(FALSE);
				str_temp.Format("%s","单次");
			}
			else
			{
				T_INSTRU.p_trigger_cont_type->Enable(FALSE);
				T_INSTRU.p_trigger_gate_type->Enable(TRUE);
				str_temp.Format("%s","门控");
			}
			p_tab_instrument->instr_params[i].TRIG_mode = str_temp;
			//读取触发连续模式
			error_no = viWrite(vi[i],(ViBuf)"RAD:CUST:TRIG:TYPE:CONT:TYPE?\n",256,&write_cnt);//写查询命令
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//读取相应的数据
			ch[read_cnt-1] = '\0';
			str_temp.Format("%s",ch);
			if (str_temp == "FREE")
				str_temp.Format("%s", "自动");
			else if (str_temp == "TRIG")
				str_temp.Format("%s", "触发");
			else
				str_temp.Format("%s", "实时");
			p_tab_instrument->instr_params[i].TRIG_mode_cont = str_temp;
			//读取触发门控模式
			error_no = viWrite(vi[i],(ViBuf)"RAD:CUST:TRIG:TYPE:GATE:ACT?\n",256,&write_cnt);//写查询命令
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//读取相应的数据
			ch[read_cnt-1] = '\0';
			str_temp.Format("%s",ch);
			if (str_temp == "LOW")
				str_temp.Format("%s", "低有效");
			else
				str_temp.Format("%s", "高有效");
			p_tab_instrument->instr_params[i].TRIG_mode_gate = str_temp;
			//读取触发源
			error_no = viWrite(vi[i],(ViBuf)"RAD:CUST:TRIG:SOUR?\n",256,&write_cnt);//写查询命令
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//读取相应的数据
			ch[read_cnt-1] = '\0';
			str_temp.Format("%s",ch);
			if (str_temp=="KEY")//通过读取的状态更改界面
			{
				T_INSTRU.p_trigger_slope->Enable(FALSE);
				T_INSTRU.p_trigger_delay_active->Enable(FALSE);
				T_INSTRU.p_trigger_delay->Enable(FALSE);
				str_temp.Format("%s","触发键");
			}
			else if (str_temp=="BUS")
			{
				T_INSTRU.p_trigger_slope->Enable(FALSE);
				T_INSTRU.p_trigger_delay_active->Enable(FALSE);
				T_INSTRU.p_trigger_delay->Enable(FALSE);
				str_temp.Format("%s","总线");
			}
			else
			{
				T_INSTRU.p_trigger_slope->Enable(TRUE);
				T_INSTRU.p_trigger_delay_active->Enable(TRUE);
				T_INSTRU.p_trigger_delay->Enable(TRUE);
				str_temp.Format("%s","外部");
			}
			p_tab_instrument->instr_params[i].TRIG_source = str_temp;
			//读取外部触发极性
			error_no = viWrite(vi[i],(ViBuf)"RAD:CUST:TRIG:EXT:SOUR:SLOP?\n",256,&write_cnt);//写查询命令
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//读取相应的数据
			ch[read_cnt-1] = '\0';
			str_temp.Format("%s",ch);
			if (str_temp == "POS")
				str_temp.Format("%s", "正");
			else
				str_temp.Format("%s", "负");
			p_tab_instrument->instr_params[i].TRIG_EXT_slope = str_temp;
			//读取外部延迟开关
			error_no = viWrite(vi[i],(ViBuf)"RAD:CUST:TRIG:EXT:DEL:STAT?\n",256,&write_cnt);//写查询命令
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//读取相应的数据
			ch[read_cnt-1] = '\0';
			str_temp.Format("%s",ch);
			p_tab_instrument->instr_params[i].TRIG_EXT_delay_switch = atoi(str_temp.GetBuffer())==0 ? "关" : "开";
			//读取外部延迟
			error_no = viWrite(vi[i],(ViBuf)"RAD:CUST:TRIG:EXT:SOUR:DEL?\n",256,&write_cnt);//写查询命令
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//读取相应的数据
			ch[read_cnt-1] = '\0';
			str_temp.Format("%s bit",ch);
			p_tab_instrument->instr_params[i].TRIG_EXT_delay = str_temp;
			//读取AWGN开关
			error_no = viWrite(vi[i],(ViBuf)"RAD:AWGN:ARB?\n",256,&write_cnt);//写查询命令
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//读取相应的数据
			ch[read_cnt-1] = '\0';
			str_temp.Format("%s",ch);
			p_tab_instrument->instr_params[i].AWGN_state = atoi(str_temp.GetBuffer())==0 ? "OFF" : "ON";
			//读取噪声带宽
			error_no = viWrite(vi[i],(ViBuf)"RAD:AWGN:ARB:BWID?\n",256,&write_cnt);//写查询命令
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//读取相应的数据
			ch[read_cnt-1] = '\0';
			str_temp.Format("%.9f Mhz",atof(ch)/1000000);
			p_tab_instrument->instr_params[i].Noise_band = str_temp;
		}
		p_tab_instrument->m_combo_instrument_index.SetCurSel(0);
		p_tab_instrument->vi = vi[0];
		p_tab_instrument->p_frequency->SetValue((COleVariant)p_tab_instrument->instr_params[0].frequency);//从仪器中读取数据写入界面
		p_tab_instrument->p_amplitude->SetValue((COleVariant)p_tab_instrument->instr_params[0].amplitude);
		p_tab_instrument->p_RF_output->SetValue((COleVariant)p_tab_instrument->instr_params[0].RF_output);
		p_tab_instrument->p_IQ_adjustments->SetValue((COleVariant)p_tab_instrument->instr_params[0].IQ_ADJ);
		p_tab_instrument->p_I_offset->SetValue((COleVariant)p_tab_instrument->instr_params[0].I_offset);
		p_tab_instrument->p_Q_offset->SetValue((COleVariant)p_tab_instrument->instr_params[0].Q_offset);
		p_tab_instrument->p_IQ_gain_balance->SetValue((COleVariant)p_tab_instrument->instr_params[0].IQ_gain_balance);
		p_tab_instrument->p_quadrature_angle_adjustment->SetValue((COleVariant)p_tab_instrument->instr_params[0].quadrature_angle_adjustment);
		p_tab_instrument->p_ALC->SetValue((COleVariant)p_tab_instrument->instr_params[0].ALC);
		p_tab_instrument->p_ALC_bandwidth->SetValue((COleVariant)p_tab_instrument->instr_params[0].ALC_band);
		p_tab_instrument->p_power_search_ref->SetValue((COleVariant)p_tab_instrument->instr_params[0].ALC_search_ref);
		p_tab_instrument->p_power_search_method->SetValue((COleVariant)p_tab_instrument->instr_params[0].ALC_search_method);
		p_tab_instrument->p_trigger_mod->SetValue((COleVariant)p_tab_instrument->instr_params[0].TRIG_mode);
		p_tab_instrument->p_trigger_cont_type->SetValue((COleVariant)p_tab_instrument->instr_params[0].TRIG_mode_cont);
		p_tab_instrument->p_trigger_gate_type->SetValue((COleVariant)p_tab_instrument->instr_params[0].TRIG_mode_gate);
		p_tab_instrument->p_trigger_source->SetValue((COleVariant)p_tab_instrument->instr_params[0].TRIG_source);
		p_tab_instrument->p_trigger_slope->SetValue((COleVariant)p_tab_instrument->instr_params[0].TRIG_EXT_slope);
		p_tab_instrument->p_trigger_delay_active->SetValue((COleVariant)p_tab_instrument->instr_params[0].TRIG_EXT_delay_switch);
		p_tab_instrument->p_trigger_delay->SetValue((COleVariant)p_tab_instrument->instr_params[0].TRIG_EXT_delay);
		p_tab_instrument->p_rt_noise_state->SetValue((COleVariant)p_tab_instrument->instr_params[0].AWGN_state);
		p_tab_instrument->p_noise_bandwidth->SetValue((COleVariant)p_tab_instrument->instr_params[0].Noise_band);
	}else{
		b_instr_connected = FALSE;
	}
}


void CMainFrame::OnHardwareConnectionWiz()
{
	// TODO: 在此添加命令处理程序代码
	CSysConfigWizard wzd("",this,0);
	wzd.SetActivePage(2);
	if (ID_WIZFINISH == wzd.DoModal())
	{
		MessageBox("完成按钮点击");
	}
}

void CMainFrame::OnMainDownload()//数据下载
{
	// TODO: 在此添加命令处理程序代码
	ViStatus error_no = 0;
	ViUInt32 cnt = 0;
	ViUInt32  length_max = 100;


	INT32 NMBYTE = m_pass_to_thread.file_size;

	//INT32 NMBYTE = 10000000;//申请10M的空间
	//INT32 nBlockNum = 2 * NMBYTE;
	char *SendData = NULL;
	UINT64 response = 0;
	INT32 nReadByte = 0;

	if (b_instr_connected)
	{
		do 
		{
			//nBlockNum -= NMBYTE;
			//if (nBlockNum<=0)
			//{
			//	break;
			//}
			SendData = new char[NMBYTE];
		} while (SendData == NULL);


		memset(SendData,0,NMBYTE);

		CFile filedata;
		CString CFilename = _T("bluetooth.seg");
		filedata.Open(CFilename.GetBuffer(),CFile::modeRead);

		char str[100] = {0};
		int nums = 0;// 文件大小的位数
		int temp = NMBYTE;
		while(temp != 0)
		{
			temp = temp / 10;
			nums++;
		}
		sprintf(str,"MEMORY:DATA bluetooth.seg,#%d%d\n",nums,NMBYTE);
		error_no = viWrite(vi[0],(ViBuf)str,strlen(str),&cnt);///////////
		//error_no = viWrite(vi[0],(ViBuf)"MEMORY:DATA NewSignalData.seg,#513060\n",39,&cnt);///////////

		filedata.SeekToBegin();
		nReadByte = filedata.Read((void*)SendData,NMBYTE);
		error_no = viWrite(vi[0],(unsigned char*)SendData,NMBYTE,&cnt);

		Sleep(100);
		error_no = viWrite(vi[0],(ViBuf)"RADIO:ARB:SEQUENCE NONE,bluetooth.seg,1,NONE\n",100,&cnt);
		//error_no = viWrite(test_vi,(ViBuf)"RADIO:ARB:SEQUENCE wlan,NewSignalData0.seg,1,NONE,NewSignalData1.seg,1,NONE,NewSignalData2.seg,1,NONE,NewSignalData3.seg,1,NONE\n",100,&cnt);
		//error_no = viWrite(test_vi,(ViBuf)"RADIO:ARB:SEQUENCE wlan,NewSignalData0.seg,1,NONE\n",100,&cnt);
		//error_no = viWrite(test_vi,(ViBuf)"RADIO:ARB:SEQUENCE wlan,NewSignalData0.seg,1,NONE,NewSignalData1.seg,1,NONE,NewSignalData2.seg,1,NONE,NewSignalData3.seg,1,NONE\n",1000,&cnt);
		//error_no = viWrite(test_vi,(ViBuf)"RADIO:ARB:SEQUENCE NONE,NewSignalData0.seg,10,NONE,NewSignalData1.seg,1,NONE,NewSignalData2.seg,1,M1,NewSignalData3.seg,1,M1M2\n",1000,&cnt);
		Sleep(300);
		error_no = viWrite(vi[0],(ViBuf)"RADIO:ARB:STATE ON\n",19,&cnt);//下载并播放
		Sleep(10);
	}
	delete[] SendData;
}


void CMainFrame::OnFrameDiagram()
{
	// TODO: 在此添加命令处理程序代码
	CFramediag Tab_framediag;
	Tab_framediag.DoModal();
}


void CMainFrame::OnDiagramMac()
{
	// TODO: 在此添加命令处理程序代码
	CMacDiag Tab_macdiag;
	Tab_macdiag.DoModal();
}
