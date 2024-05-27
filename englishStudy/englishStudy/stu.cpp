// stu.cpp: 实现文件
//

#include "pch.h"
#include "englishStudy.h"
#include "afxdialogex.h"
#include "stu.h"


// stu 对话框

IMPLEMENT_DYNAMIC(stu, CDialogEx)

stu::stu(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_stu, pParent)
{

}

stu::~stu()
{
}

void stu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(stu, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &stu::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &stu::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &stu::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &stu::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT6, &stu::OnEnChangeEdit6)
	ON_BN_CLICKED(IDC_BUTTON6, &stu::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON5, &stu::OnBnClickedButton5)
	ON_EN_CHANGE(IDC_EDIT4, &stu::OnEnChangeEdit4)
	ON_BN_CLICKED(IDC_BUTTON2, &stu::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &stu::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON7, &stu::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &stu::OnBnClickedButton8)
	ON_EN_CHANGE(IDC_EDIT7, &stu::OnEnChangeEdit7)
END_MESSAGE_MAP()


// stu 消息处理程序

_RecordsetPtr stu::DBRecordSetGet(LPCTSTR Sql)
{
	// TODO: 在此处添加实现代码.
	m_pRec.CreateInstance("ADODB.Recordset");
	m_pRec = m_pCon->Execute((_bstr_t)Sql, NULL, adCmdText);
	return m_pRec;
	//return _RecordsetPtr();
}


BOOL stu::GetCollect(LPCTSTR Name, _variant_t& OutCol)
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

void stu::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	while (m_list.DeleteColumn(0));
	m_list.ModifyStyle(LVS_ICON | LVS_SMALLICON | LVS_LIST, LVS_REPORT);
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_list.InsertColumn(0, "单词"); m_list.InsertColumn(1, "中文");
	m_list.InsertColumn(2, "4 or 6 CET");
	RECT rect;
	m_list.GetWindowRect(&rect); int wid = (rect.right - rect.left) / 3;//wid 格宽度
	m_list.SetColumnWidth(0, wid); m_list.SetColumnWidth(1, wid);
	m_list.SetColumnWidth(2, wid);

	CString sql;
	sql.Format("exec Check_col '%d'", m_sno);
	m_pRec = DBRecordSetGet(sql);

	m_list.DeleteAllItems();
	int j = 0;
	while (!m_pRec->adoEOF)
	{
		m_list.InsertItem(j, "");
		_variant_t var;

		m_list.SetItemText(j, 0, (LPTSTR)(_bstr_t)m_pRec->GetCollect("word"));
		m_list.SetItemText(j, 1, (LPTSTR)(_bstr_t)m_pRec->GetCollect("trans"));
		m_list.SetItemText(j, 2, (LPTSTR)(_bstr_t)m_pRec->GetCollect("type"));

		m_pRec->MoveNext();
		j++;
	}

}


void stu::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void stu::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void stu::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


BOOL stu::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	CString sql;
	sql.Format("exec Stud '%d'", m_id);
	m_pRec = DBRecordSetGet(sql);

	_variant_t var;
	CString str;

	// TODO : 修改
	str.Format(" %d", m_id);
	SetDlgItemText(IDC_EDIT1, str);

	GetCollect("id", var);
	int a = int(var.bstrVal);
	m_sno = a;
	str.Format(" %d", a);
	SetDlgItemText(IDC_EDIT2, str);

	GetCollect("name", var);
	CString b = CString(var.bstrVal);
	str.Format(" %s", b);
	SetDlgItemText(IDC_EDIT3, str);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void stu::OnEnChangeEdit6()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void stu::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	GetDlgItemText(IDC_EDIT6, str);
	type = _ttoi(str);

	MessageBox("成功修改！");
}


void stu::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码

	if (type == 0) {
		while (m_list.DeleteColumn(0));
		m_list.ModifyStyle(LVS_ICON | LVS_SMALLICON | LVS_LIST, LVS_REPORT);
		m_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
		m_list.InsertColumn(0, "单词"); m_list.InsertColumn(1, "中文");
		m_list.InsertColumn(2, "4 or 6 CET");
		RECT rect;
		m_list.GetWindowRect(&rect); int wid = (rect.right - rect.left) / 3;//wid 格宽度
		m_list.SetColumnWidth(0, wid); m_list.SetColumnWidth(1, wid);
		m_list.SetColumnWidth(2, wid);

		CString sql;
		sql.Format("exec Find_all_word");
		m_pRec = DBRecordSetGet(sql);

		m_list.DeleteAllItems();
		int j = 0;
		while (!m_pRec->adoEOF)
		{
			m_list.InsertItem(j, "");
			_variant_t var;

			m_list.SetItemText(j, 0, (LPTSTR)(_bstr_t)m_pRec->GetCollect("word"));
			m_list.SetItemText(j, 1, (LPTSTR)(_bstr_t)m_pRec->GetCollect("trans"));
			m_list.SetItemText(j, 2, (LPTSTR)(_bstr_t)m_pRec->GetCollect("type"));

			m_pRec->MoveNext();
			j++;
		}
	}
	else if (type == 4) {
		while (m_list.DeleteColumn(0));
		m_list.ModifyStyle(LVS_ICON | LVS_SMALLICON | LVS_LIST, LVS_REPORT);
		m_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
		m_list.InsertColumn(0, "单词"); m_list.InsertColumn(1, "中文");
		m_list.InsertColumn(2, "4 or 6 CET");
		RECT rect;
		m_list.GetWindowRect(&rect); int wid = (rect.right - rect.left) / 3;//wid 格宽度
		m_list.SetColumnWidth(0, wid); m_list.SetColumnWidth(1, wid);
		m_list.SetColumnWidth(2, wid);

		CString sql;
		sql.Format("exec Find_4_word");
		m_pRec = DBRecordSetGet(sql);

		m_list.DeleteAllItems();
		int j = 0;
		while (!m_pRec->adoEOF)
		{
			m_list.InsertItem(j, "");
			_variant_t var;

			m_list.SetItemText(j, 0, (LPTSTR)(_bstr_t)m_pRec->GetCollect("word"));
			m_list.SetItemText(j, 1, (LPTSTR)(_bstr_t)m_pRec->GetCollect("trans"));
			m_list.SetItemText(j, 2, (LPTSTR)(_bstr_t)m_pRec->GetCollect("type"));

			m_pRec->MoveNext();
			j++;
		}
	}
	else {
		while (m_list.DeleteColumn(0));
		m_list.ModifyStyle(LVS_ICON | LVS_SMALLICON | LVS_LIST, LVS_REPORT);
		m_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
		m_list.InsertColumn(0, "单词"); m_list.InsertColumn(1, "中文");
		m_list.InsertColumn(2, "4 or 6 CET");
		RECT rect;
		m_list.GetWindowRect(&rect); int wid = (rect.right - rect.left) / 3;//wid 格宽度
		m_list.SetColumnWidth(0, wid); m_list.SetColumnWidth(1, wid);
		m_list.SetColumnWidth(2, wid);

		CString sql;
		sql.Format("exec Find_6_word");
		m_pRec = DBRecordSetGet(sql);

		m_list.DeleteAllItems();
		int j = 0;
		while (!m_pRec->adoEOF)
		{
			m_list.InsertItem(j, "");
			_variant_t var;

			m_list.SetItemText(j, 0, (LPTSTR)(_bstr_t)m_pRec->GetCollect("word"));
			m_list.SetItemText(j, 1, (LPTSTR)(_bstr_t)m_pRec->GetCollect("trans"));
			m_list.SetItemText(j, 2, (LPTSTR)(_bstr_t)m_pRec->GetCollect("type"));

			m_pRec->MoveNext();
			j++;
		}
	}


}


void stu::OnEnChangeEdit4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void stu::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	int w_id;
	CString word;
	_variant_t var;

	GetDlgItemText(IDC_EDIT4, word);
	CString sql1;
	sql1.Format("exec Find_word_id '%s'", word);//存储过程
	m_pRec = DBRecordSetGet(sql1);

	GetCollect("id", var);
	w_id = int(var.bstrVal);

	CString sql2;
	sql2.Format("exec insert_col '%d', '%d'", w_id, m_sno);
	m_pRec = DBRecordSetGet(sql2);

	MessageBox("已收藏！");
}


void stu::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	int w_id;
	CString word;
	_variant_t var;

	GetDlgItemText(IDC_EDIT4, word);
	CString sql1;
	sql1.Format("exec Find_word_id '%s'", word);//存储过程
	m_pRec = DBRecordSetGet(sql1);

	GetCollect("id", var);
	w_id = int(var.bstrVal);

	CString sql2;
	sql2.Format("exec del_col '%d'", w_id);
	m_pRec = DBRecordSetGet(sql2);

	MessageBox("已删除！");
}


void stu::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	if (type == 0) {
		while (m_list.DeleteColumn(0));
		m_list.ModifyStyle(LVS_ICON | LVS_SMALLICON | LVS_LIST, LVS_REPORT);
		m_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
		m_list.InsertColumn(0, "文章号"); m_list.InsertColumn(1, "文章");
		m_list.InsertColumn(2, "4 or 6 CET");
		RECT rect;
		m_list.GetWindowRect(&rect); int wid = (rect.right - rect.left) / 4;//wid 格宽度
		m_list.SetColumnWidth(0, wid); m_list.SetColumnWidth(1, 2 * wid);
		m_list.SetColumnWidth(2, wid);

		CString sql;
		sql.Format("exec Find_all_article '%d'", m_sno);
		m_pRec = DBRecordSetGet(sql);

		m_list.DeleteAllItems();
		int j = 0;
		while (!m_pRec->adoEOF)
		{
			m_list.InsertItem(j, "");
			_variant_t var;

			m_list.SetItemText(j, 0, (LPTSTR)(_bstr_t)m_pRec->GetCollect("id"));
			m_list.SetItemText(j, 1, (LPTSTR)(_bstr_t)m_pRec->GetCollect("name"));
			m_list.SetItemText(j, 2, (LPTSTR)(_bstr_t)m_pRec->GetCollect("type"));

			m_pRec->MoveNext();
			j++;
		}
	}
	else if (type == 4) {
		while (m_list.DeleteColumn(0));
		m_list.ModifyStyle(LVS_ICON | LVS_SMALLICON | LVS_LIST, LVS_REPORT);
		m_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
		m_list.InsertColumn(0, "文章号"); m_list.InsertColumn(1, "文章");
		m_list.InsertColumn(2, "4 or 6 CET");
		RECT rect;
		m_list.GetWindowRect(&rect); int wid = (rect.right - rect.left) / 4;//wid 格宽度
		m_list.SetColumnWidth(0, wid); m_list.SetColumnWidth(1, 2 * wid);
		m_list.SetColumnWidth(2, wid);

		CString sql;
		sql.Format("exec Find_4_article '%d'", m_sno);
		m_pRec = DBRecordSetGet(sql);

		m_list.DeleteAllItems();
		int j = 0;
		while (!m_pRec->adoEOF)
		{
			m_list.InsertItem(j, "");
			_variant_t var;

			m_list.SetItemText(j, 0, (LPTSTR)(_bstr_t)m_pRec->GetCollect("id"));
			m_list.SetItemText(j, 1, (LPTSTR)(_bstr_t)m_pRec->GetCollect("name"));
			m_list.SetItemText(j, 2, (LPTSTR)(_bstr_t)m_pRec->GetCollect("type"));

			m_pRec->MoveNext();
			j++;
		}
	}
	else {
		while (m_list.DeleteColumn(0));
		m_list.ModifyStyle(LVS_ICON | LVS_SMALLICON | LVS_LIST, LVS_REPORT);
		m_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
		m_list.InsertColumn(0, "文章号"); m_list.InsertColumn(1, "文章");
		m_list.InsertColumn(2, "4 or 6 CET");
		RECT rect;
		m_list.GetWindowRect(&rect); int wid = (rect.right - rect.left) / 4;//wid 格宽度
		m_list.SetColumnWidth(0, wid); m_list.SetColumnWidth(1, 2 * wid);
		m_list.SetColumnWidth(2, wid);

		CString sql;
		sql.Format("exec Find_6_article '%d'", m_sno);
		m_pRec = DBRecordSetGet(sql);

		m_list.DeleteAllItems();
		int j = 0;
		while (!m_pRec->adoEOF)
		{
			m_list.InsertItem(j, "");
			_variant_t var;

			m_list.SetItemText(j, 0, (LPTSTR)(_bstr_t)m_pRec->GetCollect("id"));
			m_list.SetItemText(j, 1, (LPTSTR)(_bstr_t)m_pRec->GetCollect("name"));
			m_list.SetItemText(j, 2, (LPTSTR)(_bstr_t)m_pRec->GetCollect("type"));

			m_pRec->MoveNext();
			j++;
		}
	}

}


void stu::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	int a_id;
	_variant_t var;

	CString temp;
	GetDlgItemText(IDC_EDIT7, temp);
	a_id = _ttoi(temp);
	CString sql1;
	sql1.Format("exec insert_rel '%d', '%d'", a_id, m_sno);//存储过程
	m_pRec = DBRecordSetGet(sql1);
	MessageBox("success！");
}


void stu::OnEnChangeEdit7()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
