#pragma once
#include "afxdialogex.h"

// sys_admin 对话框

class sys_admin : public CDialogEx
{
	DECLARE_DYNAMIC(sys_admin)

public:
	sys_admin(CWnd* pParent = nullptr);   // 标准构造函数

	_ConnectionPtr m_pCon;
	_RecordsetPtr m_pRec;
	_RecordsetPtr DBRecordSetGet(LPCTSTR Sql);
	BOOL GetCollect(LPCTSTR Name, _variant_t& OutCol);

	virtual ~sys_admin();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_admin };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton1();
	CListCtrl m_list;
	afx_msg void OnBnClickedButton6();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton5();

	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit6();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit4();
};
