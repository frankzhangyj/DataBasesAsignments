#pragma once
#include "afxdialogex.h"


// modifySch 对话框

class modifySch : public CDialogEx
{
	DECLARE_DYNAMIC(modifySch)

public:
	modifySch(CWnd* pParent = nullptr);   // 标准构造函数

	CString sch;
	CString may;
	int score;

	_ConnectionPtr m_pCon;
	_RecordsetPtr m_pRec;
	_RecordsetPtr DBRecordSetGet(LPCTSTR Sql);
	BOOL GetCollect(LPCTSTR Name, _variant_t& OutCol);

	virtual ~modifySch();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_modifySch };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnBnClickedButton1();
};
