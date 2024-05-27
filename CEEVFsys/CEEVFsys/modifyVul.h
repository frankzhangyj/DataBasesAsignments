#pragma once
#include "pch.h"
#include "CEEVFsys.h"
#include "afxdialogex.h"


// modifyVul 对话框

class modifyVul : public CDialogEx
{
	DECLARE_DYNAMIC(modifyVul)

public:
	modifyVul(CWnd* pParent = nullptr);   // 标准构造函数

	int m_sno;
	int m_sch;
	int m_may;

	_ConnectionPtr m_pCon;
	_RecordsetPtr m_pRec;
	_RecordsetPtr DBRecordSetGet(LPCTSTR Sql);
	BOOL GetCollect(LPCTSTR Name, _variant_t& OutCol);

	virtual ~modifyVul();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_modifyVul };
#endif

protected:

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton1();
};
