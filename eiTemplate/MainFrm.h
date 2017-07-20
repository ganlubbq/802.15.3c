
// MainFrm.h : CMainFrame 类的接口
//

#pragma once

#include "C.h"
#include "W.h"
// 下面的三个类是主框架上动态创建的三个视图
#include "TabParent.h"
#include "GraphCCDF.h"
#include "GraphWAVE.h"
// 协议实现的函数
#include "BlueToothProtocal.h"
#include "genParam.h"//3c协议配置
#include "channel.h"//信道配置信息
// 系统配置向导
#include "SysConfigWizard.h"
// MAC相关功能
#include "Framediag.h"
#include "MacDiag.h"

typedef struct Data_Graph//包含了图像绘制、配置参数等具体实现的实例
{
	CGraphCCDF* p_graphCCDF;
	CGraphWAVE* p_graphWAVE;
	BlueToothParams* p_protocol_params;
	Protocol_param_3C* p_protocol_params_3c;//153c参数
	Protocol_param_channel* p_protocol_params_channel;//信道参数
	int file_size; //数据下载：定义生成文件的大小，写数据的时候要用到
	CProgressCtrl	  *p_m_progress;		//进度条
}data_and_graph;

class CMainFrame : public CFrameWnd
{
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:
	//分割窗口相关的三个变量
	CMySplitterWnd m_mainSplitter;
	CMySplitterWnd m_rightSplitter;
	BOOL m_bInitSplitter;

	CWinThread *draw_thread_id;	//生成信号和绘制图线的线程
	data_and_graph m_pass_to_thread;//传递给线程的结构体

	//仪器连接相关的变量
	int m_num_instr;
	ViSession defaultRM;
	ViSession vi[8];
	BOOL b_instr_connected;
// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CToolBar          m_wndToolBar;		//工具栏
	CStatusBar        m_wndStatusBar;	//状态栏
	CProgressCtrl	  m_progress;		//进度条
// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnTest();
	afx_msg void OnHelpDoc();
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnMainRun();
	afx_msg void OnSystemConfigWiz();
	afx_msg void OnHardwareConnectionWiz();
	afx_msg void OnMainDownload();//数据下载-申明
	afx_msg void OnFrameDiagram();
	afx_msg void OnDiagramMac();
};

UINT ThreadFune(LPVOID lpParam);	//生成信号，绘制图线的线程