// back_end_sys.cpp: 实现文件
//

#include "pch.h"
#include "CEEVFsys.h"
#include "afxdialogex.h"
#include "back_end_sys.h"


// back_end_sys 对话框

IMPLEMENT_DYNAMIC(back_end_sys, CDialogEx)

back_end_sys::back_end_sys(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SYS, pParent)
{

}

back_end_sys::~back_end_sys()
{
}

void back_end_sys::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(back_end_sys, CDialogEx)
END_MESSAGE_MAP()


// back_end_sys 消息处理程序
