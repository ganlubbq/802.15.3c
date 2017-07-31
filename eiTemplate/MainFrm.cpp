
// MainFrm.cpp : CMainFrame ���ʵ��
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
	ON_COMMAND(ID_MAIN_DOWNLOAD, &CMainFrame::OnMainDownload)//�������أ������ذ�ť
	ON_COMMAND(ID_BLUETOOTH_FRAME, &CMainFrame::OnFrameDiagram)
	ON_COMMAND(ID_DIAGRAM_MAC, &CMainFrame::OnDiagramMac)
END_MESSAGE_MAP()

/************************************************************************/
/* ״̬���еļ���ѡ����Դ��ʶ                                           */
/************************************************************************/
static UINT indicators[]=
{
	ID_SEPARATOR,			//״̬��ָʾ��
	IDS_INSTRUMENT_STATE,	//��������״̬
	IDS_ERROR_INDICAROR,	//����ָʾ
	IDS_PROGRESS,			//������
};


// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
	m_bInitSplitter = FALSE;
	m_pass_to_thread.p_protocol_params = new BlueToothParams();//��������
	m_pass_to_thread.p_protocol_params_3c = new Protocol_param_3C();//3C����
	m_pass_to_thread.p_protocol_params_channel = new Protocol_param_channel();//�ŵ�����
	b_instr_connected = FALSE;
	m_num_instr = 0;
	m_pass_to_thread.p_m_progress = &m_progress;   //����ܽ�����ָ�봫���߳�
}

CMainFrame::~CMainFrame()
{
	/************************************************************************/
	/* �ر�������������                                                     */
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
	/*��ӹ�����                                                            */
	/************************************************************************/
	if (!m_wndToolBar.CreateEx(this,TBSTYLE_FLAT,WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}
	/*Ϊ���������ñ�����ɫ***************************************************/
	HBRUSH newBr=CreateSolidBrush(RGB(237,239,252));//RGB(237,239,252)
	SetClassLong(m_wndToolBar.m_hWnd,GCL_HBRBACKGROUND,(long)newBr);
	/*Ϊ����������Զ����ͼƬ����������״̬��ͼƬ�����õ�ͼƬ�ͼ����ͼƬ***/
	CImageList m_imgToolBar;//������ͼ���б�
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
	m_imgToolBar.Detach();//����detach���Ա�֤�ھֲ���������ʱm_imgToolBar��������ڴ�����
	m_wndToolBar.ShowWindow(SW_SHOW);
	
	/************************************************************************/
	/* ���״̬��(����״ָ̬ʾ���������������������Ϣ��������)             */
	/************************************************************************/
	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	m_wndStatusBar.SetPaneInfo(0,ID_SEPARATOR,SBPS_NORMAL,150);	//����״̬����һ��Ϊ����״ָ̬ʾ
	m_wndStatusBar.SetPaneInfo(1,IDS_INSTRUMENT_STATE,SBPS_NORMAL,150);	//����״̬���ڶ���Ϊ��������ָʾ
	m_wndStatusBar.SetPaneInfo(2,IDS_ERROR_INDICAROR,SBPS_STRETCH ,0);	//����״̬��������Ϊ������ʾ��Ϊ��֤״̬��ռ�ݿռ����������Ϊ�����������
	m_wndStatusBar.SetPaneInfo(3,IDS_PROGRESS,SBPS_NORMAL,200);	//����״̬�����һ��Ϊ����������׼���Ž�����������
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);	//��ʾ״̬��

	/***********************��״̬���ϴ���������*****************************/
	CRect rect_progress;
	m_wndStatusBar.GetItemRect(3,&rect_progress);    //��ȡ�������Ĵ�С
	m_progress.Create(WS_CHILD|WS_VISIBLE|PBS_SMOOTH,rect_progress,&m_wndStatusBar,IDC_PROGRESS);
	m_progress.SetRange(0,6);
	m_progress.SetStep(1);//����
	m_progress.SetPos(0);//��ǰλ��

	/************************************************************************/
	/* ��������ܴ��ڵı���                                                 */
	/************************************************************************/
	SetWindowText("IEEE 802.15.3c����ź��������");

	/************************************************************************/
	/* ������ӭ���棨����ʱ��ע���������䣩                                 */
	/************************************************************************/
	//CSplashWnd::ShowSplashScreen(this);
	//Sleep(2000);//��ӭ����ĳ���ʱ����2��

	// TODO: �������Ҫ��ͣ������������ɾ��������
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
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
	cs.style &= ~FWS_ADDTOTITLE;
	cs.cx = 1127;
	cs.cy = 712;
	return TRUE;
}

// CMainFrame ���

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


// CMainFrame ��Ϣ�������
BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: �ڴ����ר�ô����/����û���
	CRect cr; 
	GetClientRect( &cr);

	//��������ܵĿͻ�����Ϊһ������
	if ( !m_mainSplitter.CreateStatic( this, 1, 2 ,WS_CHILD/*|WS_BORDER*/|WS_VISIBLE) )
	{ 
		MessageBox( "Error setting up main splitter frames!", "Init Error!", MB_OK | MB_ICONERROR ); 
		return FALSE; 
	}
	//���ڶ����ٷ�Ϊ����һ�У��������γ��˿���ϵ������ӿ�
	if ( !m_rightSplitter.CreateStatic( &m_mainSplitter, 2, 1 ,WS_CHILD/*|WS_BORDER*/|WS_VISIBLE,m_mainSplitter.IdFromRowCol(0,1)) )
	{ 
		MessageBox( "Error setting up right splitter frames!", "Init Error!", MB_OK | MB_ICONERROR ); 
		return FALSE; 
	}
	/************************************************************************/
	/* Ϊÿ������ʾ����������Ӧ����ͼ��                                     */
	/************************************************************************/
	//�������ý���
	if ( !m_mainSplitter.CreateView(0, 0, RUNTIME_CLASS(CTabParent), CSize(500, cr.Height()), pContext ) ) 
	{ 
		MessageBox( "Error setting up splitter frames!", "Init Error!", MB_OK | MB_ICONERROR );
		return FALSE; 
	}
	//���Ϸ���CCDFͼ
	if ( !m_rightSplitter.CreateView(0, 0, RUNTIME_CLASS(CGraphCCDF), CSize(cr.Width()-500, 300/*cr.Height()/2*/), pContext ) ) 
	{ 
		MessageBox( "Error setting up splitter frames!", "Init Error!", MB_OK | MB_ICONERROR );
		return FALSE; 
	}
	//�Ҳ��·��Ĳ���ͼ
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
	/*������ʵ�������������ʱ�Ҳನ��ͼ�İ��������ź�ͼ����Сֵ�Ķ���ͱ���*/
	/************************************************************************/
	if (nType == SIZE_MINIMIZED)	//��С����ʹ�ͻ������Ϊ0�����������������
	{
		return;
	}
	//���ҷָ�ڵĿ���(�������������С���Ϊ200���Ҳ�������С���Ϊ35)
	int widthLeft = 0;	//������Ŀ��
	int widthLeftMin = 0;
	int widthRight = 0;	//�Ҳ����Ŀ��
	int widthRightMin = 0;
	//���������ָ�ڵ���С��ȿ���
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
	//���·ָ����Ŀ��ƣ������������ĸ߶���Сֵ��Ϊ30��
	int heightRightTop = 0;		//���Ϸ����ĸ߶�
	int heightRightTopMin = 0;
	int heightRightBottom = 0;	//���·����ĸ߶�
	int heightRightBottomMin = 0;
	//���������ָ����ı�������
	double x = m_rightSplitter.m_splitterScale;	//ȡ����ǰ���ڷָ�ı���
	if ( m_rightSplitter.GetSafeHwnd() != NULL && m_bInitSplitter )
	{
		m_rightSplitter.SetRowInfo(0,(int)((cy-54)*x),0);
		m_rightSplitter.SetRowInfo(1,cy-(int)((cy-54)*x),0);
		m_rightSplitter.RecalcLayout();
	}
	//���������ָ�������С�߶ȿ���
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
	// ��Ϊ��ͼ��Ϣ���� CFrameWnd::OnPaint()

	/************************************************************************/
	/*�ػ���ƶ�״̬���ϵĽ�����                                            */
	/************************************************************************/
	CRect rect_progress;
	m_wndStatusBar.GetItemRect(3,&rect_progress);
	if (!m_progress.m_hWnd)
		m_progress.Create(WS_CHILD|WS_VISIBLE|PBS_SMOOTH,rect_progress,&m_wndStatusBar,IDC_PROGRESS);
	else
		m_progress.MoveWindow(rect_progress);
}



void CMainFrame::OnHelpDoc()//�򿪰����ĵ�
{
	/************************************************************************/
	/*�������ַ���Ҳ�պϣ������൱���ڱ�����֮���ִ���һ�������ĵ�ʵ������*/
	/*ʧ���������רҵ��													*/
	/************************************************************************/
	//::ShellExecute(NULL, "open", "test.chm", NULL, NULL, SW_SHOW);
	
	/************************************************************************/
	/*�ڰ�װ�����ʱ����Խ������ĵ���·��д��ע����滻����ֱ�ӵ����ļ�����*/
	/*������������ʹ�����ĵ���ΪӦ�ó����һ���ִ򿪣�Ӧ�ó���رյ�ʱ�����*/
	/*��֮�رգ������������רҵ��											*/
	/************************************************************************/
	::HtmlHelp(this->m_hWnd,"16de_help.chm",HH_DISPLAY_TOPIC,NULL);
	/*::HtmlHelp(this->m_hWnd,_T("16de_help.chm.chm"),HH_DISPLAY_TOPIC,NULL);*/
}



void CMainFrame::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	/************************************************************************/
	/* ��������ܴ����ܹ���������Сֵ                                       */
	/************************************************************************/
	lpMMI->ptMinTrackSize.x = 650;
	lpMMI->ptMinTrackSize.y = 300;
}


void CMainFrame::OnTest()//���Խӿ�
{
	//for (int i = 0;i<50;i++)//���Խ�����
	//{
	//	m_progress.StepIt();
	//	Sleep(10);
	//}

	////΢����������Ҫ���ʽ̽��
	//char temp[32] = "";
	//CString str="";
	//itoa(1023,temp,2);
	//str.Format("%010s",temp);
	//MessageBox(str);

	/************************************************************************/
	/* �����������Ӻ����ݶ�ȡ                                               */
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
	//error_no = viPrintf(test_vi,"*RST\n");//д��������
	//Sleep(100);

	//error_no = viWrite(test_vi,(ViBuf)"FREQ?\n",length_max,&cnt);//д��ѯ����
	//Sleep(100);
	//error_no = viRead(test_vi,(ViBuf)ch,length_max,&cnt);//��ȡ��Ӧ������

	//error_no = viPrintf(test_vi,"FREQ?\n");//д��ѯ����
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
	/* �ļ�����                                                             */
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
	error_no = viWrite(test_vi,(ViBuf)"RADIO:ARB:STATE ON\n",19,&cnt);//���ز�����
	Sleep(100);



	error_no = viClear(test_vi);
	Sleep(10);
	error_no = viClose(test_vi);
	Sleep(10);
	error_no = viClose(testRM);

	//sprintf(str,"%d",GetSystemMetrics(SM_CXSIZEFRAME));//��ȡ�ָ����Ŀ��
	//MessageBox(str);
	//((CGraphWAVE*)m_rightSplitter.GetPane(1,0))->Run();
}

void CMainFrame::OnMainRun()//����������
{
	// TODO: �ڴ���������������
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


	//�ڻ�ͼ�����н��õ�����ͼ����ʾ�����ϵ�comboBox����������������쳣
	DataAndGraph->p_graphCCDF->m_comboCCDF.EnableWindow(FALSE);
	DataAndGraph->p_graphWAVE->m_comboWAVE.EnableWindow(FALSE);
	
	int i,j,m,n,N=0,Num_of_space,m_AllNum,ScaleXend;
	double max_power;
	double max_specturm;
	double max_ccdf;
	CProgressCtrl *p_m_progress = DataAndGraph->p_m_progress;
	/************************************************************************/
	/* �������������ź�                                                     */
	/************************************************************************/
	//int Packet_len;//����δ�����������ɵ����ݳ���
	//int data_inlen;//����01���صĳ���
	//int sig_len;//���������źţ������������������ݳ���
	//char bit_source[192]={0,1,0,1,0,0,1,1,1,1,1,1,0,0,1,0,1,0,1,0,0,0,1,1,0,0,1,1,1,1,0,1,1,1,0,1,0,1,1,0,1,0,0,1,1,0,1,1,0,1,0,1,0,0,1,1,1,1,1,1,0,0,1,0,1,0,1,0,0,0,1,1,0,0,1,1,1,1,0,1,1,1,0,1,0,1,1,0,1,0,0,1,1,0,1,1,0,1,0,1,0,0,1,1,1,1,1,1,0,0,1,0,1,0,1,0,0,0,1,1,0,0,1,1,1,1,0,1,1,1,0,1,0,1,1,0,1,0,0,1,1,0,1,1,0,1,0,1,0,0,1,1,1,1,1,1,0,0,1,0,1,0,1,0,0,0,1,1,0,0,1,1,1,1,0,1,1,1,0,1,0,1,1,0,1,0,0,1,1,0,1,1};
	//data_inlen = sizeof(bit_source)/sizeof(bit_source[0]);
	//double I_gfsk[30000]={0};//���ڴ洢I·����
	//double Q_gfsk[30000]={0};//���ڴ洢Q·����
	//bluetooth_waveform_generator(DataAndGraph->p_protocol_params,I_gfsk,Q_gfsk,bit_source,data_inlen,Packet_len);
	//sig_len = Packet_len * DataAndGraph->p_protocol_params->oversample;

	//ofstream of("data.txt");
	//for (i = 0;i<sig_len;i++)
	//{
	//	of<<Q_gfsk[i]<<endl;
	//}
	//of.close();

	/* ����3c�����ź� */
	/************************************************************************/
	//HSI_param HSI_p;//HSI��������
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
	//gen_prbs(macheader_HSI, HSI_p.L_mh);//����macheader
	//vector<int> macbody_HSI;
	//gen_prbs(macbody_HSI, HSI_p.L_fram);//����macbody
	//vector<complex<double> > HSI_PHY;
	//genHSI(macbody_HSI, macheader_HSI, HSI_PHY, HSI_p);
	p_m_progress->SetPos(0);
	int Nheader_3c = gen_lmh_3c(*(DataAndGraph->p_protocol_params_3c));
	int Nbody_3c = gen_lmb_3c(*(DataAndGraph->p_protocol_params_3c));
	vector<int> macheader;
	vector<int> macbody;
	int source_type = DataAndGraph->p_protocol_params_3c->data_source;
	char *filepath_sc_temp = DataAndGraph->p_protocol_params_3c->filepath_ds;
	//gen_prbs(macheader, Nheader_3c);//����macheader
	//gen_prbs(macbody, Nbody_3c);//����macbody
	macheader = GenerateSource(source_type, Nheader_3c, 10, filepath_sc_temp);
	macbody = GenerateSource(source_type, Nbody_3c, 10, filepath_sc_temp);
	vector<complex<double> > dataout;
	vector<complex<double> > dataout_chan;
	p_m_progress->StepIt();
	waveform_generator_3c(macheader, macbody, dataout, *DataAndGraph->p_protocol_params_3c);
	p_m_progress->StepIt();
	int sig_len = 0;
	if ((*DataAndGraph->p_protocol_params_channel).chanel_switch == 0)
		sig_len = dataout.size();//���������źţ������������������ݳ���
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
	///* ���� 41 Ҫ���ʽ���ź��ļ�   //��������copy!!!!step3!!!!                   */
	///************************************************************************/
	//CFile file;
	//file.Open(_T("bluetooth.seg"),CFile::modeCreate|CFile::modeWrite);
	//CArchive ar(&file,CArchive::store);//д����

	////256�ֽ�ͷ��
	//char ei41Name[8] = {'e','i','4','1'};//��˾����
	//for (int i=0;i!=8;i++)
	//	ar<<ei41Name[i];

	//INT64 timeFrequency = 1000000;//1MHzʱ��Ƶ��
	//ar<<timeFrequency;

	//INT64 elementLength = 1;//��Ԫ����
	//ar<<elementLength;

	//INT64 samplePoints = 1;//����������
	//ar<<samplePoints;

	//INT64 points = sig_len;//�������
	//ar<<points;

	//INT64 cycleTime = points / timeFrequency * 1000;//���� = �������*ʱ��Ƶ�� ����Ϊ��λ��
	//ar<<cycleTime;

	//INT64  padBits[26]={0};//���208λ�ֽ�
	//for (int i =0;i!=26;i++)
	//	ar<<padBits[i];

	////�����ź����ݶ�
	//for (int i=0;i!=sig_len;i++)
	//{
	//	ar<<(INT16)(I_gfsk[i]*23347200)<<(INT16)(Q_gfsk[i]*23347200);
	//}

	//ar.Close();
	//file.Close();
	//DataAndGraph->file_size = 256 + sig_len * 2 * 2; // ÿ��sig_len��2�ֽڣ�һ�����ȶ�Ӧʵ�����鲿��λ������������4
	/************************************************************************/
	/************************************************************************/
	/* WAVEͼ���ƣ�I+Q��I|Q��power��Spectrum��                              */
	/************************************************************************/
	p_wave->m_RealValuenSize = sig_len;	//�������ɵ����ݳ���
	p_wave->m_ScaleValueXEnd = sig_len;
	/**********I+Q ���ݵ����ͼ��**********/
		p_wave->I_Data = I_gfsk;
		p_wave->Q_Data = Q_gfsk;
	/**********Powerͼ�Ļ���**********/
	p_wave->pPointArrayPower =(POINT *) new POINT[sig_len];
	max_power=pow(I_gfsk[0],2)+pow(Q_gfsk[0],2);
	//�ҵ���������
	for (j=0;j<sig_len;j++)
	{
		double temp = pow(I_gfsk[j],2)+pow(Q_gfsk[j],2);
		if (temp > max_power)
		{
			max_power = temp;
		}
		//max_power = temp > max_power ? temp : max_power;
	}
	//����ÿ���źŵ����������ʵ��dBֵ
	for (j=0;j<sig_len;j++)
	{
		p_wave->pPointArrayPower[j].x=long(j);
		p_wave->pPointArrayPower[j].y=10*log10((pow(I_gfsk[j],2)+pow(Q_gfsk[j],2))/max_power);
	}
	p_m_progress->StepIt();
	/**********Spectrum�Ļ���**********/
	//����ת����
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
	
	//FFT����Ƶ��
	N = FFT(data_in,sig_len);
	//FFTShift(data_in);//Ƶ�װ��ƣ���ע�͵�
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
	p_wave->IorQFlg();	//ͼ��������Ϻ�������ʾI|Qͼ��
	p_m_progress->StepIt();
	/************************************************************************/
	/* CCDFͼ�Ļ���                                                         */
	/************************************************************************/
	p_ccdf->m_RealValuenSize = sig_len;

	double *pPointArrayCCDF;
	//�趨һ���м�������飬���ʵ�����ݵĹ���
	pPointArrayCCDF =(double*)new double[sig_len];

	//CCDF�趨һ�����飬�̶�����
	//ȷ��������� == X���ܵ���-1
	Num_of_space=(p_ccdf->m_AllNum)-1;
	m_AllNum=p_ccdf->m_AllNum;
	ScaleXend=p_ccdf->m_ScaleValueXEnd;
	p_ccdf->pPointArrayCCDF=(double*)new double[m_AllNum];
	//���㹦��
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
	//��ͼ��Ļ��Ʋ�����ɺ���ʹ������ͼ���ϵ�comboBox
	DataAndGraph->p_graphCCDF->m_comboCCDF.SetCurSel(0);
	DataAndGraph->p_graphWAVE->m_comboWAVE.SetCurSel(0);
	DataAndGraph->p_graphCCDF->m_comboCCDF.EnableWindow(TRUE);
	DataAndGraph->p_graphWAVE->m_comboWAVE.EnableWindow(TRUE);

	return 0;
}

void CMainFrame::OnSystemConfigWiz()
{
	// TODO: �ڴ���������������
	CSysConfigWizard wzd("ϵͳ������",this,0);
	//����ǰ��������Ϣ�����򵼣��������������������Ϣ�����򵼽���ر�
	wzd.defaultRM = defaultRM;
	for (int i = 0;i<8;i++)
	{
		wzd.vi[i] = vi[i];
	}
	//���������˳����һЩ����
	if (ID_WIZFINISH == wzd.DoModal() && wzd.b_instr_connected)
	{
		b_instr_connected = TRUE;
		m_num_instr = wzd.m_num_instruments;
		defaultRM = wzd.defaultRM;

		CTabInstrument* p_tab_instrument = &(((CTabParent*)m_mainSplitter.GetPane(0,0))->m_tabInstrument);
		CTabInstrument &T_INSTRU = ((CTabParent*)(((CMainFrame*)AfxGetMainWnd())->m_mainSplitter.GetPane(0,0)))->m_tabInstrument;//�������������޸Ľ���
		p_tab_instrument->m_combo_instrument_index.ResetContent();//����������ҳ�������������
		p_tab_instrument->send_command_enabled = TRUE;//����������ҳʵʱ��������״̬�Ĺ��ܴ�

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
			//��ȡFREQ
			error_no = viWrite(vi[i],(ViBuf)"FREQ?\n",256,&write_cnt);//д��ѯ����
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//��ȡ��Ӧ������
			ch[read_cnt-1] = '\0';//�����ص�'\n'��Ϊ'\0',����س��������õ�Ӱ��
			str_temp.Format("%sHz",ch);
			p_tab_instrument->instr_params[i].frequency = str_temp;
			//��ȡPOW
			error_no = viWrite(vi[i],(ViBuf)"POW?\n",256,&write_cnt);//д��ѯ����
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//��ȡ��Ӧ������
			ch[read_cnt-1] = '\0';
			str_temp.Format("%sdBm",ch);
			p_tab_instrument->instr_params[i].amplitude = str_temp;
			//��ȡ��Ƶ����״̬
			error_no = viWrite(vi[i],(ViBuf)"OUTP?\n",256,&write_cnt);//д��ѯ����
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//��ȡ��Ӧ������
			ch[read_cnt-1] = '\0';
			str_temp.Format("%s",ch);
			p_tab_instrument->instr_params[i].RF_output = atoi(str_temp.GetBuffer())==0 ? "OFF" : "ON";
			//��ȡIQ����(DM:IQAD:STAT)
			error_no = viWrite(vi[i],(ViBuf)"DM:IQAD:STAT?\n",256,&write_cnt);//д��ѯ����
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//��ȡ��Ӧ������
			ch[read_cnt-1] = '\0';
			str_temp.Format("%s",ch);
			if (atoi(str_temp.GetBuffer())==1)//ͨ����ȡ��״̬���Ľ���
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
			//��ȡIƫ��
			error_no = viWrite(vi[i],(ViBuf)"DM:IQAD:IOFF?\n",256,&write_cnt);//д��ѯ����
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//��ȡ��Ӧ������
			ch[read_cnt-1] = '\0';//�����ص�'\n'��Ϊ'\0',����س��������õ�Ӱ��
			str_temp.Format("%s%s",ch,"%");
			p_tab_instrument->instr_params[i].I_offset = str_temp;
			//��ȡQƫ��
			error_no = viWrite(vi[i],(ViBuf)"DM:IQAD:QOFF?\n",256,&write_cnt);//д��ѯ����
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//��ȡ��Ӧ������
			ch[read_cnt-1] = '\0';//�����ص�'\n'��Ϊ'\0',����س��������õ�Ӱ��
			str_temp.Format("%s%s",ch,"%");
			p_tab_instrument->instr_params[i].Q_offset = str_temp;
			//��ȡIQ��������
			error_no = viWrite(vi[i],(ViBuf)"DM:IQAD:GAIN?\n",256,&write_cnt);//д��ѯ����
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//��ȡ��Ӧ������
			ch[read_cnt-1] = '\0';//�����ص�'\n'��Ϊ'\0',����س��������õ�Ӱ��
			str_temp.Format("%sdB",ch);
			p_tab_instrument->instr_params[i].IQ_gain_balance = str_temp;
			//��ȡIQ����ƫ��
			error_no = viWrite(vi[i],(ViBuf)"DM:IQAD:QSK?\n",256,&write_cnt);//д��ѯ����
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//��ȡ��Ӧ������
			ch[read_cnt-1] = '\0';//�����ص�'\n'��Ϊ'\0',����س��������õ�Ӱ��
			str_temp.Format("%sDeg",ch);
			p_tab_instrument->instr_params[i].quadrature_angle_adjustment = str_temp;
			//��ȡALC״̬
			error_no = viWrite(vi[i],(ViBuf)"POW:ALC:STAT?\n",256,&write_cnt);//д��ѯ����
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//��ȡ��Ӧ������
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
			//��ȡALC����
			error_no = viWrite(vi[i],(ViBuf)"POW:ALC:BAND:AUTO?\n",256,&write_cnt);//д��ѯ����
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//��ȡ��Ӧ������
			ch[read_cnt-1] = '\0';
			str_temp.Format("%s",ch);
			if (atoi(str_temp.GetBuffer())==1)
			{
				p_tab_instrument->instr_params[i].ALC_band = "ON";
			}
			else//��ѯ�ֶ�ALC��������
			{
				error_no = viWrite(vi[i],(ViBuf)"POW:ALC:BAND?\n",256,&write_cnt);//д��ѯ����
				Sleep(10);
				error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//��ȡ��Ӧ������
				ch[read_cnt-1] = '\0';
				str_temp.Format("%s",ch);
				p_tab_instrument->instr_params[i].ALC_band = str_temp;
			}
			//p_tab_instrument->instr_params[i].ALC_band = atoi(str_temp.GetBuffer())==1 ? "OFF" : "ON";
			//��ȡALC�����ο�
			error_no = viWrite(vi[i],(ViBuf)"POW:ALC:SEAR:REF?\n",256,&write_cnt);//д��ѯ����
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//��ȡ��Ӧ������
			ch[read_cnt-1] = '\0';
			str_temp.Format("%s",ch);
			p_tab_instrument->instr_params[i].ALC_search_ref = str_temp=="FIX" ? "�̶�" : "����";
			//��ȡ����ģʽ
			error_no = viWrite(vi[i],(ViBuf)"POW:ALC:SEAR?\n",256,&write_cnt);//д��ѯ����
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//��ȡ��Ӧ������
			ch[read_cnt-1] = '\0';
			str_temp.Format("%s",ch);
			p_tab_instrument->instr_params[i].ALC_search_method = atoi(str_temp.GetBuffer())==0 ? "�ֶ�" : "�Զ�";
			//��ȡʱ������
			error_no = viWrite(vi[i],(ViBuf)"RAD:ARB:SEQ:CLOCK?\n",256,&write_cnt);//д��ѯ����
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//��ȡ��Ӧ������
			ch[read_cnt-1] = '\0';
			str_temp.Format("%s",ch);
			if (str_temp=="CURR")//ͨ����ȡ��״̬���Ľ���
			{
				T_INSTRU.p_ARB_clock_freq->Enable(FALSE);
				str_temp.Format("%s","����");
			}
			else if (str_temp=="HIGH")
			{
				T_INSTRU.p_ARB_clock_freq->Enable(FALSE);
				str_temp.Format("%s","���");
			}
			else
			{
				T_INSTRU.p_ARB_clock_freq->Enable(TRUE);
				str_temp.Format("%s","�Զ���");
			}
			p_tab_instrument->instr_params[i].ARB_clock_type = str_temp;
			//��ȡARBʱ��Ƶ��
			error_no = viWrite(vi[i],(ViBuf)"RAD:ARB:SCL:RATE?\n",256,&write_cnt);//д��ѯ����
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//��ȡ��Ӧ������
			ch[read_cnt-1] = '\0';//�����ص�'\n'��Ϊ'\0',����س��������õ�Ӱ��
			str_temp.Format("%.6f MHz",atof(ch)/1000000);
			p_tab_instrument->instr_params[i].ARB_clock_freq = str_temp;
			//��ȡ����ģʽ
			error_no = viWrite(vi[i],(ViBuf)"RAD:CUST:TRIG:TYPE?\n",256,&write_cnt);//д��ѯ����
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//��ȡ��Ӧ������
			ch[read_cnt-1] = '\0';
			str_temp.Format("%s",ch);
			if (str_temp=="CONT")//ͨ����ȡ��״̬���Ľ���
			{
				T_INSTRU.p_trigger_cont_type->Enable(TRUE);
				T_INSTRU.p_trigger_gate_type->Enable(FALSE);
				str_temp.Format("%s","����");
			}
			else if (str_temp=="SING")
			{
				T_INSTRU.p_trigger_cont_type->Enable(FALSE);
				T_INSTRU.p_trigger_gate_type->Enable(FALSE);
				str_temp.Format("%s","����");
			}
			else
			{
				T_INSTRU.p_trigger_cont_type->Enable(FALSE);
				T_INSTRU.p_trigger_gate_type->Enable(TRUE);
				str_temp.Format("%s","�ſ�");
			}
			p_tab_instrument->instr_params[i].TRIG_mode = str_temp;
			//��ȡ��������ģʽ
			error_no = viWrite(vi[i],(ViBuf)"RAD:CUST:TRIG:TYPE:CONT:TYPE?\n",256,&write_cnt);//д��ѯ����
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//��ȡ��Ӧ������
			ch[read_cnt-1] = '\0';
			str_temp.Format("%s",ch);
			if (str_temp == "FREE")
				str_temp.Format("%s", "�Զ�");
			else if (str_temp == "TRIG")
				str_temp.Format("%s", "����");
			else
				str_temp.Format("%s", "ʵʱ");
			p_tab_instrument->instr_params[i].TRIG_mode_cont = str_temp;
			//��ȡ�����ſ�ģʽ
			error_no = viWrite(vi[i],(ViBuf)"RAD:CUST:TRIG:TYPE:GATE:ACT?\n",256,&write_cnt);//д��ѯ����
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//��ȡ��Ӧ������
			ch[read_cnt-1] = '\0';
			str_temp.Format("%s",ch);
			if (str_temp == "LOW")
				str_temp.Format("%s", "����Ч");
			else
				str_temp.Format("%s", "����Ч");
			p_tab_instrument->instr_params[i].TRIG_mode_gate = str_temp;
			//��ȡ����Դ
			error_no = viWrite(vi[i],(ViBuf)"RAD:CUST:TRIG:SOUR?\n",256,&write_cnt);//д��ѯ����
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//��ȡ��Ӧ������
			ch[read_cnt-1] = '\0';
			str_temp.Format("%s",ch);
			if (str_temp=="KEY")//ͨ����ȡ��״̬���Ľ���
			{
				T_INSTRU.p_trigger_slope->Enable(FALSE);
				T_INSTRU.p_trigger_delay_active->Enable(FALSE);
				T_INSTRU.p_trigger_delay->Enable(FALSE);
				str_temp.Format("%s","������");
			}
			else if (str_temp=="BUS")
			{
				T_INSTRU.p_trigger_slope->Enable(FALSE);
				T_INSTRU.p_trigger_delay_active->Enable(FALSE);
				T_INSTRU.p_trigger_delay->Enable(FALSE);
				str_temp.Format("%s","����");
			}
			else
			{
				T_INSTRU.p_trigger_slope->Enable(TRUE);
				T_INSTRU.p_trigger_delay_active->Enable(TRUE);
				T_INSTRU.p_trigger_delay->Enable(TRUE);
				str_temp.Format("%s","�ⲿ");
			}
			p_tab_instrument->instr_params[i].TRIG_source = str_temp;
			//��ȡ�ⲿ��������
			error_no = viWrite(vi[i],(ViBuf)"RAD:CUST:TRIG:EXT:SOUR:SLOP?\n",256,&write_cnt);//д��ѯ����
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//��ȡ��Ӧ������
			ch[read_cnt-1] = '\0';
			str_temp.Format("%s",ch);
			if (str_temp == "POS")
				str_temp.Format("%s", "��");
			else
				str_temp.Format("%s", "��");
			p_tab_instrument->instr_params[i].TRIG_EXT_slope = str_temp;
			//��ȡ�ⲿ�ӳٿ���
			error_no = viWrite(vi[i],(ViBuf)"RAD:CUST:TRIG:EXT:DEL:STAT?\n",256,&write_cnt);//д��ѯ����
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//��ȡ��Ӧ������
			ch[read_cnt-1] = '\0';
			str_temp.Format("%s",ch);
			p_tab_instrument->instr_params[i].TRIG_EXT_delay_switch = atoi(str_temp.GetBuffer())==0 ? "��" : "��";
			//��ȡ�ⲿ�ӳ�
			error_no = viWrite(vi[i],(ViBuf)"RAD:CUST:TRIG:EXT:SOUR:DEL?\n",256,&write_cnt);//д��ѯ����
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//��ȡ��Ӧ������
			ch[read_cnt-1] = '\0';
			str_temp.Format("%s bit",ch);
			p_tab_instrument->instr_params[i].TRIG_EXT_delay = str_temp;
			//��ȡAWGN����
			error_no = viWrite(vi[i],(ViBuf)"RAD:AWGN:ARB?\n",256,&write_cnt);//д��ѯ����
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//��ȡ��Ӧ������
			ch[read_cnt-1] = '\0';
			str_temp.Format("%s",ch);
			p_tab_instrument->instr_params[i].AWGN_state = atoi(str_temp.GetBuffer())==0 ? "OFF" : "ON";
			//��ȡ��������
			error_no = viWrite(vi[i],(ViBuf)"RAD:AWGN:ARB:BWID?\n",256,&write_cnt);//д��ѯ����
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);//��ȡ��Ӧ������
			ch[read_cnt-1] = '\0';
			str_temp.Format("%.9f Mhz",atof(ch)/1000000);
			p_tab_instrument->instr_params[i].Noise_band = str_temp;
		}
		p_tab_instrument->m_combo_instrument_index.SetCurSel(0);
		p_tab_instrument->vi = vi[0];
		p_tab_instrument->p_frequency->SetValue((COleVariant)p_tab_instrument->instr_params[0].frequency);//�������ж�ȡ����д�����
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
	// TODO: �ڴ���������������
	CSysConfigWizard wzd("",this,0);
	wzd.SetActivePage(2);
	if (ID_WIZFINISH == wzd.DoModal())
	{
		MessageBox("��ɰ�ť���");
	}
}

void CMainFrame::OnMainDownload()//��������
{
	// TODO: �ڴ���������������
	ViStatus error_no = 0;
	ViUInt32 cnt = 0;
	ViUInt32  length_max = 100;


	INT32 NMBYTE = m_pass_to_thread.file_size;

	//INT32 NMBYTE = 10000000;//����10M�Ŀռ�
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
		int nums = 0;// �ļ���С��λ��
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
		error_no = viWrite(vi[0],(ViBuf)"RADIO:ARB:STATE ON\n",19,&cnt);//���ز�����
		Sleep(10);
	}
	delete[] SendData;
}


void CMainFrame::OnFrameDiagram()
{
	// TODO: �ڴ���������������
	CFramediag Tab_framediag;
	Tab_framediag.DoModal();
}


void CMainFrame::OnDiagramMac()
{
	// TODO: �ڴ���������������
	CMacDiag Tab_macdiag;
	Tab_macdiag.DoModal();
}
