// MacDiag.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "MacDiag.h"
#include "afxdialogex.h"


// CMacDiag �Ի���

IMPLEMENT_DYNAMIC(CMacDiag, CDialog)

CMacDiag::CMacDiag(CWnd* pParent /*=NULL*/)
	: CDialog(CMacDiag::IDD, pParent)
{
	m_pic_macdiag1 =(HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_DIAG_MACHEADER1),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS);
	m_pic_macdiag2 =(HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_DIAG_MACHEADER2),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS);
	m_pic_macdiag3 =(HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_DIAG_MACHEADER3),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS);
}

CMacDiag::~CMacDiag()
{
}

void CMacDiag::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_MACDIAG, m_ComMacdiag);
	DDX_Control(pDX, IDC_STATIC_DIAGMAC, m_pic_macdiag);
}


BEGIN_MESSAGE_MAP(CMacDiag, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_MACDIAG, &CMacDiag::OnCbnSelchangeComboMacdiag)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON1, &CMacDiag::OnBnClickedButton_MacConfig)
END_MESSAGE_MAP()


// CMacDiag ��Ϣ�������


void CMacDiag::OnCbnSelchangeComboMacdiag()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	switch (m_ComMacdiag.GetCurSel())
	{
	case 0:
		m_pic_macdiag.SetBitmap(m_pic_macdiag1);
		break;
	case 1:
		m_pic_macdiag.SetBitmap(m_pic_macdiag2);
		break;
	case 2:
		m_pic_macdiag.SetBitmap(m_pic_macdiag3);
		break;
	default:
		break;
	}
}


BOOL CMacDiag::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_ComMacdiag.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CMacDiag::OnPaint()
{
	CRect   rect;    
	CPaintDC dc(this); // device context for painting
	GetClientRect(rect);  
	dc.FillSolidRect(rect,RGB(255,255,255));   //����Ϊ��ɫ����
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
}


void CMacDiag::OnBnClickedButton_MacConfig()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMacConfig_SC Tab_macconfig_sc;
	Tab_macconfig_sc.DoModal();
}
