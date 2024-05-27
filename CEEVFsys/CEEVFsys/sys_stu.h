#pragma once
#include "afxdialogex.h"


// sys_stu 对话框

class sys_stu : public CDialogEx
{
	DECLARE_DYNAMIC(sys_stu)

public:
	sys_stu(CWnd* pParent = nullptr);   // 标准构造函数
	// 学生帐号
	CString m_sno;
	int m_id;

	_ConnectionPtr m_pCon;
	_RecordsetPtr m_pRec;
	_RecordsetPtr DBRecordSetGet(LPCTSTR Sql);
	BOOL GetCollect(LPCTSTR Name, _variant_t& OutCol);
	virtual ~sys_stu();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_stu };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	virtual HRESULT accDoDefaultAction(VARIANT varChild);
	CListCtrl stu_list;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonschool1();
	afx_msg void OnBnClickedButtonaddv1();
	afx_msg void OnEnChangeEditid1();
	afx_msg void OnEnChangeEditname1();
	afx_msg void OnEnChangeEditclass1();
	afx_msg void OnEnChangeEditlogid();
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButtonvol();
	afx_msg void OnBnClickedButtongrade2();
	afx_msg void OnBnClickedButtondelete1();
};
