// MacConfig_HSI.cpp : 实现文件
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "MacConfig_HSI.h"
#include "afxdialogex.h"


// CMacConfig_HSI 对话框

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


// CMacConfig_HSI 消息处理程序


BOOL CMacConfig_HSI::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
