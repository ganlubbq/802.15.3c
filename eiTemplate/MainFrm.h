
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once

#include "C.h"
#include "W.h"
// �������������������϶�̬������������ͼ
#include "TabParent.h"
#include "GraphCCDF.h"
#include "GraphWAVE.h"
// Э��ʵ�ֵĺ���
#include "BlueToothProtocal.h"
#include "genParam.h"//3cЭ������
#include "channel.h"//�ŵ�������Ϣ
// ϵͳ������
#include "SysConfigWizard.h"
// MAC��ع���
#include "Framediag.h"
#include "MacDiag.h"

typedef struct Data_Graph//������ͼ����ơ����ò����Ⱦ���ʵ�ֵ�ʵ��
{
	CGraphCCDF* p_graphCCDF;
	CGraphWAVE* p_graphWAVE;
	BlueToothParams* p_protocol_params;
	Protocol_param_3C* p_protocol_params_3c;//153c����
	Protocol_param_channel* p_protocol_params_channel;//�ŵ�����
	int file_size; //�������أ����������ļ��Ĵ�С��д���ݵ�ʱ��Ҫ�õ�
	CProgressCtrl	  *p_m_progress;		//������
}data_and_graph;

class CMainFrame : public CFrameWnd
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:
	//�ָ����ص���������
	CMySplitterWnd m_mainSplitter;
	CMySplitterWnd m_rightSplitter;
	BOOL m_bInitSplitter;

	CWinThread *draw_thread_id;	//�����źźͻ���ͼ�ߵ��߳�
	data_and_graph m_pass_to_thread;//���ݸ��̵߳Ľṹ��

	//����������صı���
	int m_num_instr;
	ViSession defaultRM;
	ViSession vi[8];
	BOOL b_instr_connected;
// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CToolBar          m_wndToolBar;		//������
	CStatusBar        m_wndStatusBar;	//״̬��
	CProgressCtrl	  m_progress;		//������
// ���ɵ���Ϣӳ�亯��
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
	afx_msg void OnMainDownload();//��������-����
	afx_msg void OnFrameDiagram();
	afx_msg void OnDiagramMac();
};

UINT ThreadFune(LPVOID lpParam);	//�����źţ�����ͼ�ߵ��߳�