#pragma once
#include "afxdialogex.h"


// stu 对话框

class stu : public CDialogEx
{
	DECLARE_DYNAMIC(stu)

public:
	stu(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~stu();

	_ConnectionPtr m_pCon;
	_RecordsetPtr m_pRec;
	_RecordsetPtr DBRecordSetGet(LPCTSTR Sql);
	BOOL GetCollect(LPCTSTR Name, _variant_t& OutCol);

	int m_id;
	int m_sno;//学号
	int type = 0;
	CString m_name;//密码

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_stu };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEdit6();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton5();
	CListCtrl m_list;
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnEnChangeEdit7();
};
