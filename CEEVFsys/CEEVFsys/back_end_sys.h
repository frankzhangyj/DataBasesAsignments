#pragma once
#include "afxdialogex.h"


// back_end_sys 对话框

class back_end_sys : public CDialogEx
{
	DECLARE_DYNAMIC(back_end_sys)

public:
	back_end_sys(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~back_end_sys();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SYS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
