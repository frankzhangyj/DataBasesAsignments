﻿
// CEEVFsys.cpp: 定义应用程序的类行为。
//

#include "pch.h"
#include "framework.h"
#include "CEEVFsys.h"
#include "CEEVFsysDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCEEVFsysApp

BEGIN_MESSAGE_MAP(CCEEVFsysApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CCEEVFsysApp 构造

CCEEVFsysApp::CCEEVFsysApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 CCEEVFsysApp 对象

CCEEVFsysApp theApp;


// CCEEVFsysApp 初始化

BOOL CCEEVFsysApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	// 连接数据库
	CString strLinkWord = "Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;Initial Catalog=studentDataBase;Data Source=LAPTOP-UN7O0L73";
	if (!ConnectDataBase(strLinkWord))
	{
		return FALSE;
	}
		
	// 创建窗口对象
	CCEEVFsysDlg dlg;
	dlg.m_pCon = m_pCon;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

// 连接数据库函数
BOOL CCEEVFsysApp::ConnectDataBase(CString strLinkWord)
{
	// TODO: 在此处添加实现代码.
	::CoInitialize(NULL);

	if (!SUCCEEDED(m_pCon.CreateInstance(__uuidof(Connection))))
	{
		m_pCon = NULL;
		TRACE("Failed!");
	}
	ASSERT(m_pCon != NULL);
	try
	{
		return SUCCEEDED(m_pCon->Open(_bstr_t(strLinkWord), _bstr_t(""), _bstr_t(""), adModeUnknown));
	}
	catch (_com_error& e)
	{
		CString str;
		str.Format("%s\n", e.ErrorMessage());
		AfxMessageBox(str);
		return FALSE;
	}
}

