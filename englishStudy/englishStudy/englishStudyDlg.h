
// englishStudyDlg.h: 头文件
//

#pragma once
#include <CString>

// CenglishStudyDlg 对话框
class CenglishStudyDlg : public CDialogEx
{
// 构造
public:
	CenglishStudyDlg(CWnd* pParent = nullptr);	// 标准构造函数
	_ConnectionPtr m_pCon;
	_RecordsetPtr m_pRec;
	_RecordsetPtr DBRecordSetGet(LPCTSTR Sql);
	BOOL GetCollect(LPCTSTR Name, _variant_t& OutCol);

	int m_id;
	CString m_pwd;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ENGLISHSTUDY_DIALOG };
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
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
};
