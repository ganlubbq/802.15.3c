// MacConfig_HSI.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "MacConfig_HSI.h"
#include "afxdialogex.h"


// CMacConfig_HSI �Ի���

IMPLEMENT_DYNAMIC(CMacConfig_HSI, CDialog)

CMacConfig_HSI::CMacConfig_HSI(CWnd* pParent /*=NULL*/)
	: CDialog(CMacConfig_HSI::IDD, pParent)
{

}

CMacConfig_HSI::~CMacConfig_HSI()
{
}

void CMacConfig_HSI::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMacConfig_HSI, CDialog)
END_MESSAGE_MAP()


// CMacConfig_HSI ��Ϣ�������


BOOL CMacConfig_HSI::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
