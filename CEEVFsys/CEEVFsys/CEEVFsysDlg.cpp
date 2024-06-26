﻿
// CEEVFsysDlg.cpp: 实现文件
//
#include "resource.h"
#include "pch.h"
#include "framework.h"
#include "CEEVFsys.h"
#include "CEEVFsysDlg.h"
#include "afxdialogex.h"
#include "sys_admin.h"
#include "sys_stu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCEEVFsysDlg 对话框



CCEEVFsysDlg::CCEEVFsysDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CEEVFSYS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCEEVFsysDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCEEVFsysDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CCEEVFsysDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CCEEVFsysDlg::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT_NAME, &CCEEVFsysDlg::OnEnChangeEditName)
END_MESSAGE_MAP()


// CCEEVFsysDlg 消息处理程序

BOOL CCEEVFsysDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCEEVFsysDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCEEVFsysDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCEEVFsysDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCEEVFsysDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	// TODO 为什么进入不了stu后台 和doModal有关？了解procedure 存储过程实现原理
	GetDlgItemText(IDC_EDIT_NAME, m_sno);
	GetDlgItemText(IDC_EDIT_PWD, m_pw);
	int mode;

	// 匹配帐号密码
	CString sql1;
	sql1.Format("exec Login '%s','%s'", m_sno, m_pw);//存储过程
	m_pRec = DBRecordSetGet(sql1);

	_variant_t var;
	GetCollect("cnt", var);//cnt 与你创建的存储过程里的名称对应
	int temp = var.intVal;

	if (strlen(m_sno) < 1) {
		MessageBox("请输入用户名！");
		return;
	}
	if (strlen(m_pw) < 1) {
		MessageBox("请输入密码！");
		return;
	}

	if (temp == 0) {
		MessageBox("帐号或密码错误!");
		return;
	}

	// 找到用户模式
	CString sql2;
	sql2.Format("exec Find_mode '%s'", m_sno);
	m_pRec = DBRecordSetGet(sql2);

	GetCollect("mode", var);
	mode = var.intVal;

	if (temp == 1)
	{
		if (mode == 0) {
			CDialogEx::OnOK();
			sys_stu dlg;
			dlg.m_pCon = m_pCon;
			dlg.m_sno = m_sno;
			dlg.DoModal();
		}
		else {
			CDialogEx::OnOK();
			sys_admin dlg;
			dlg.m_pCon = m_pCon;
			//dlg.m_sno = m_sno;
			dlg.DoModal();
		}
	}		
}

_RecordsetPtr CCEEVFsysDlg::DBRecordSetGet(LPCTSTR Sql)
{
	// TODO: 在此处添加实现代码.
	m_pRec.CreateInstance("ADODB.Recordset");
	m_pRec = m_pCon->Execute((_bstr_t)Sql, NULL, adCmdText);
	return m_pRec;
	//return _RecordsetPtr();
}

BOOL CCEEVFsysDlg::GetCollect(LPCTSTR Name, _variant_t& OutCol)
{
	// TODO: 在此处添加实现代码
	_variant_t vt;
	vt = m_pRec->GetCollect(Name);
	if (vt.vt != VT_NULL) {
		OutCol = vt;
		return TRUE;
	}
	else
		return FALSE;
}


void CCEEVFsysDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CCEEVFsysDlg::OnEnChangeEditName()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
