﻿
// CEEVFsysDlg.h: 头文件
//

#pragma once
#include "back_end_sys.h"

// CCEEVFsysDlg 对话框
class CCEEVFsysDlg : public CDialogEx
{
// 构造
public:
	CCEEVFsysDlg(CWnd* pParent = nullptr);	// 标准构造函数
	_ConnectionPtr m_pCon;
	_RecordsetPtr m_pRec;
	_RecordsetPtr DBRecordSetGet(LPCTSTR Sql);
	BOOL GetCollect(LPCTSTR Name, _variant_t& OutCol);

	CString m_sno;//学号
	CString m_pw;//密码
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CEEVFSYS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeEditName();
};
