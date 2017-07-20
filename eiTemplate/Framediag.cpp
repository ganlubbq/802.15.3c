// Framediag.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "Framediag.h"
#include "afxdialogex.h"


// CFramediag �Ի���

IMPLEMENT_DYNAMIC(CFramediag, CDialog)

CFramediag::CFramediag(CWnd* pParent /*=NULL*/)
	: CDialog(CFramediag::IDD, pParent)
{
	m_pic_framediag1 =(HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_DIAG_FRAME1),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS);
	m_pic_framediag2 =(HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_DIAG_FRAME2),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS);
	m_pic_framediag3 =(HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_DIAG_FRAME3),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS);
}

CFramediag::~CFramediag()
{
}

void CFramediag::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_FRAMEDIAG, m_ComFramediag);
	DDX_Control(pDX, IDC_STATIC_FRAMEDIAG, m_pic_framediag);
}


BEGIN_MESSAGE_MAP(CFramediag, CDialog)
	ON_WM_PAINT()
ON_CBN_SELCHANGE(IDC_COMBO_FRAMEDIAG, &CFramediag::OnCbnSelchangeComboFramediag)
END_MESSAGE_MAP()


// CFramediag ��Ϣ�������


void CFramediag::OnPaint()
{
	CRect   rect;    
	CPaintDC dc(this); // device context for painting
	GetClientRect(rect);  
	dc.FillSolidRect(rect,RGB(255,255,255));   //����Ϊ��ɫ����
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
}


BOOL CFramediag::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_ComFramediag.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CFramediag::OnCbnSelchangeComboFramediag()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	switch (m_ComFramediag.GetCurSel())
	{
	case 0:
		m_pic_framediag.SetBitmap(m_pic_framediag1);
		break;
	case 1:
		m_pic_framediag.SetBitmap(m_pic_framediag2);
		break;
	case 2:
		m_pic_framediag.SetBitmap(m_pic_framediag3);
		break;
	default:
		break;
	}
}
