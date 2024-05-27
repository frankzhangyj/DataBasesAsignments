// sys_stu.cpp: 实现文件
//

#include "pch.h"
#include "CEEVFsys.h"
#include "afxdialogex.h"
#include "sys_stu.h"
#include"modifyVul.h"


// sys_stu 对话框

IMPLEMENT_DYNAMIC(sys_stu, CDialogEx)

sys_stu::sys_stu(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_stu, pParent)
{

}

sys_stu::~sys_stu()
{
}

void sys_stu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, stu_list);
}


BEGIN_MESSAGE_MAP(sys_stu, CDialogEx)

	ON_BN_CLICKED(IDC_BUTTON_school1, &sys_stu::OnBnClickedButtonschool1)
	ON_BN_CLICKED(IDC_BUTTON_addv1, &sys_stu::OnBnClickedButtonaddv1)
	ON_EN_CHANGE(IDC_EDIT_id1, &sys_stu::OnEnChangeEditid1)
	ON_EN_CHANGE(IDC_EDIT_name1, &sys_stu::OnEnChangeEditname1)
	ON_EN_CHANGE(IDC_EDIT_class1, &sys_stu::OnEnChangeEditclass1)
	ON_EN_CHANGE(IDC_EDIT_log_id, &sys_stu::OnEnChangeEditlogid)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &sys_stu::OnLvnItemchangedList1)
	ON_EN_CHANGE(IDC_EDIT1, &sys_stu::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON3, &sys_stu::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON_vol, &sys_stu::OnBnClickedButtonvol)
	ON_BN_CLICKED(IDC_BUTTON_grade2, &sys_stu::OnBnClickedButtongrade2)
END_MESSAGE_MAP()


_RecordsetPtr sys_stu::DBRecordSetGet(LPCTSTR Sql)
{
	// TODO: 在此处添加实现代码.
	m_pRec.CreateInstance("ADODB.Recordset");
	m_pRec = m_pCon->Execute((_bstr_t)Sql, NULL, adCmdText);
	return m_pRec;
	//return _RecordsetPtr();
}


BOOL sys_stu::GetCollect(LPCTSTR Name, _variant_t& OutCol)
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

// sys_stu 消息处理程序


//HRESULT sys_stu::accDoDefaultAction(VARIANT varChild)
//{
	// TODO: 在此添加专用代码和/或调用基类

//	return CDialogEx::accDoDefaultAction(varChild);
//}


BOOL sys_stu::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString sql;
	sql.Format("exec Stud '%s'", m_sno);
	m_pRec = DBRecordSetGet(sql);

	_variant_t var;
	CString str;

	/*str.Format("学号：%s", m_sno);
	SetDlgItemText(IDC_EDIT6, str);*/

	// TODO : 修改
	GetCollect("log_id", var);
	CString temp = CString(var.bstrVal);
	str.Format("帐号：%s", temp);
	SetDlgItemText(IDC_EDIT_log_id, str);

	GetCollect("stu_id", var);
	int a = int(var.bstrVal);
	m_id = a;
	str.Format("学号：%d", a);
	SetDlgItemText(IDC_EDIT_id1, str);

	GetCollect("stu_name", var);
	CString b = CString(var.bstrVal);
	str.Format("姓名：%s", b);
	SetDlgItemText(IDC_EDIT_name1, str);

	GetCollect("class_id", var);
	CString c = CString(var.bstrVal);
	str.Format("班级：%s", c);
	SetDlgItemText(IDC_EDIT_class1, str);

	return TRUE;  
	// return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

// 查看学校
void sys_stu::OnBnClickedButtonschool1()
{
	// TODO: 在此添加控件通知处理程序代码
	// 插入数据 完成学校查询和专业查询
	while (stu_list.DeleteColumn(0));
	stu_list.ModifyStyle(LVS_ICON | LVS_SMALLICON | LVS_LIST, LVS_REPORT);
	stu_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	stu_list.InsertColumn(0, "学校号");
	stu_list.InsertColumn(1, "学校"); 
	stu_list.InsertColumn(2, "录取分数线");
	RECT rect;
	stu_list.GetWindowRect(&rect); int wid = (rect.right - rect.left) / 3;//wid 格宽度
	stu_list.SetColumnWidth(0, wid); 
	stu_list.SetColumnWidth(1, wid);
	stu_list.SetColumnWidth(2, wid);

	CString sql;
	sql.Format("exec Find_sch");
	m_pRec = DBRecordSetGet(sql);

	if (m_pRec->adoEOF)
		return;

	stu_list.DeleteAllItems();
	int j = 0;
	while (!m_pRec->adoEOF)
	{
		stu_list.InsertItem(j, "");
		_variant_t var;

		stu_list.SetItemText(j, 0, (LPTSTR)(_bstr_t)m_pRec->GetCollect("sch_id"));
		stu_list.SetItemText(j, 1, (LPTSTR)(_bstr_t)m_pRec->GetCollect("sch_name"));
		stu_list.SetItemText(j, 2, (LPTSTR)(_bstr_t)m_pRec->GetCollect("min_score"));
		/* var = m_pRec->GetCollect("sum");
		if (var.vt != VT_NULL)
		{
			stu_list.SetItemText(j, 4, (LPTSTR)(_bstr_t)var);
		}
		else
			stu_list.SetItemText(j, 4, TEXT("")); */
		m_pRec->MoveNext();
		j++;
	}
}

// 查看学校专业分数
void sys_stu::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	int m_sch_id;
	CString m_sch_name;
	_variant_t var;

	GetDlgItemText(IDC_EDIT1, m_sch_name);
	CString sql1;
	sql1.Format("exec Find_sch_id '%s'", m_sch_name);//存储过程
	m_pRec = DBRecordSetGet(sql1);

	if (m_pRec->adoEOF) {
		MessageBox("学校名不存在！");
		return;
	}

	GetCollect("id", var);
	m_sch_id = int(var.bstrVal);

	while (stu_list.DeleteColumn(0));
	stu_list.ModifyStyle(LVS_ICON | LVS_SMALLICON | LVS_LIST, LVS_REPORT);
	stu_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	stu_list.InsertColumn(0, "专业号");
	stu_list.InsertColumn(1, "专业名");
	stu_list.InsertColumn(2, "录取分数线");
	RECT rect;
	stu_list.GetWindowRect(&rect); int wid = (rect.right - rect.left) / 3;//wid 格宽度
	stu_list.SetColumnWidth(0, wid); 
	stu_list.SetColumnWidth(1, wid);
	stu_list.SetColumnWidth(2, wid);

	CString sql2;
	sql2.Format("exec Find_sch_may '%d'", m_sch_id);
	m_pRec = DBRecordSetGet(sql2);

	if (m_pRec->adoEOF)
		return;

	int j = 0;
	while (!m_pRec->adoEOF)
	{
		stu_list.InsertItem(j, "");

		stu_list.SetItemText(j, 0, (LPTSTR)(_bstr_t)m_pRec->GetCollect("id"));
		stu_list.SetItemText(j, 1, (LPTSTR)(_bstr_t)m_pRec->GetCollect("major_name"));
		stu_list.SetItemText(j, 2, (LPTSTR)(_bstr_t)m_pRec->GetCollect("rel_soce"));
		m_pRec->MoveNext();
		j++;
	}

}

// 显示学生志愿
void sys_stu::OnBnClickedButtonvol()
{
	// TODO: 在此添加控件通知处理程序代码
		// TODO: 在此添加控件通知处理程序代码
	// 插入数据 完成学校查询和专业查询

	while (stu_list.DeleteColumn(0));

	_variant_t var;

	// 得到志愿
	stu_list.ModifyStyle(LVS_ICON | LVS_SMALLICON | LVS_LIST, LVS_REPORT);
	stu_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	stu_list.InsertColumn(0, "学校"); stu_list.InsertColumn(1, "专业");
	RECT rect;
	stu_list.GetWindowRect(&rect); int wid = (rect.right - rect.left) / 2;//wid 格宽度
	stu_list.SetColumnWidth(0, wid); stu_list.SetColumnWidth(1, wid);

	CString sql;
	sql.Format("exec Find_stu_vul '%d'", m_id);
	m_pRec = DBRecordSetGet(sql);

	if (m_pRec->adoEOF) {
		MessageBox("该学生未填报志愿！");
		return;
	}

	stu_list.DeleteAllItems();
	int j = 0;
	while (!m_pRec->adoEOF)
	{
		stu_list.InsertItem(j, "");
		_variant_t var;

		stu_list.SetItemText(j, 0, (LPTSTR)(_bstr_t)m_pRec->GetCollect("sch"));
		stu_list.SetItemText(j, 1, (LPTSTR)(_bstr_t)m_pRec->GetCollect("may"));
		m_pRec->MoveNext();
		j++;
	}
}

// 查看学生成绩
void sys_stu::OnBnClickedButtongrade2()
{
	// TODO: 在此添加控件通知处理程序代码
	while (stu_list.DeleteColumn(0));
	stu_list.ModifyStyle(LVS_ICON | LVS_SMALLICON | LVS_LIST, LVS_REPORT);
	stu_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	stu_list.InsertColumn(0, "语文"); stu_list.InsertColumn(1, "数学");
	stu_list.InsertColumn(2, "英语"); stu_list.InsertColumn(3, "综合");
	stu_list.InsertColumn(4, "总分");
	RECT rect;
	stu_list.GetWindowRect(&rect); int wid = (rect.right - rect.left) / 6;//wid 格宽度
	stu_list.SetColumnWidth(0, wid); stu_list.SetColumnWidth(1, wid);
	stu_list.SetColumnWidth(2, wid); stu_list.SetColumnWidth(3, wid);
	stu_list.SetColumnWidth(4, 2 * wid);

	CString sql;
	sql.Format("exec Scla '%d'", m_id);
	m_pRec = DBRecordSetGet(sql);

	if (m_pRec->adoEOF) {
		MessageBox("该学生暂无成绩！");
		return;
	}

	stu_list.DeleteAllItems();
	int j = 0;
	while (!m_pRec->adoEOF)
	{
		stu_list.InsertItem(j, "");
		_variant_t var;

		stu_list.SetItemText(j, 0, (LPTSTR)(_bstr_t)m_pRec->GetCollect("chinese"));
		stu_list.SetItemText(j, 1, (LPTSTR)(_bstr_t)m_pRec->GetCollect("math"));
		stu_list.SetItemText(j, 2, (LPTSTR)(_bstr_t)m_pRec->GetCollect("english"));
		stu_list.SetItemText(j, 3, (LPTSTR)(_bstr_t)m_pRec->GetCollect("overall"));
		stu_list.SetItemText(j, 4, (LPTSTR)(_bstr_t)m_pRec->GetCollect("sum"));
		/* var = m_pRec->GetCollect("sum");
		if (var.vt != VT_NULL)
		{
			stu_list.SetItemText(j, 4, (LPTSTR)(_bstr_t)var);
		}
		else
			stu_list.SetItemText(j, 4, TEXT("")); */
		m_pRec->MoveNext();
		j++;
	}

}

// 添加志愿 
void sys_stu::OnBnClickedButtonaddv1()
{
	// TODO: 在此添加控件通知处理程序代码
	modifyVul dlg;
	dlg.m_pCon = m_pCon;
	dlg.m_sno = m_id;
	dlg.DoModal();
		// TODO: 在此处添加实现代码.
}

// 删除志愿
void sys_stu::OnBnClickedButtondelete1()
{
	// TODO: 在此添加控件通知处理程序代码
	modifyVul dlg;
	dlg.m_pCon = m_pCon;
	dlg.m_sno = m_id;
	dlg.DoModal();
}


void sys_stu::OnEnChangeEditid1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void sys_stu::OnEnChangeEditname1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void sys_stu::OnEnChangeEditclass1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}



void sys_stu::OnEnChangeEditlogid()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void sys_stu::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void sys_stu::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}








