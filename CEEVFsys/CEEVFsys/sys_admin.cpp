// sys_admin.cpp: 实现文件
//

#include "pch.h"
#include "CEEVFsys.h"
#include "afxdialogex.h"
#include "sys_admin.h"
#include "modifySch.h"


// sys_admin 对话框

IMPLEMENT_DYNAMIC(sys_admin, CDialogEx)

sys_admin::sys_admin(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_admin, pParent)
{

}

sys_admin::~sys_admin()
{
}

void sys_admin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(sys_admin, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &sys_admin::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &sys_admin::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &sys_admin::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON6, &sys_admin::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON5, &sys_admin::OnBnClickedButton5)
	ON_EN_CHANGE(IDC_EDIT1, &sys_admin::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT6, &sys_admin::OnEnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT2, &sys_admin::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &sys_admin::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, &sys_admin::OnEnChangeEdit4)
END_MESSAGE_MAP()


// sys_admin 消息处理程序

BOOL sys_admin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


// 查看学校信息
void sys_admin::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	while (m_list.DeleteColumn(0));
	m_list.ModifyStyle(LVS_ICON | LVS_SMALLICON | LVS_LIST, LVS_REPORT);
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_list.InsertColumn(0, "学校号"); m_list.InsertColumn(1, "学校名");
	m_list.InsertColumn(2, "专业号"); m_list.InsertColumn(3, "专业名");
	m_list.InsertColumn(4, "专业录取分数");
	RECT rect;
	m_list.GetWindowRect(&rect); int wid = (rect.right - rect.left) / 6;//wid 格宽度
	m_list.SetColumnWidth(0, wid); m_list.SetColumnWidth(1, wid);
	m_list.SetColumnWidth(2, wid); m_list.SetColumnWidth(3, wid);
	m_list.SetColumnWidth(4, 2 * wid);

	CString sql;
	sql.Format("exec Find_admin_sch_may");
	m_pRec = DBRecordSetGet(sql);

	if (m_pRec->adoEOF)
		return;

	int j = 0;
	while (!m_pRec->adoEOF)
	{
		m_list.InsertItem(j, "");

		m_list.SetItemText(j, 0, (LPTSTR)(_bstr_t)m_pRec->GetCollect("sch_id"));
		m_list.SetItemText(j, 1, (LPTSTR)(_bstr_t)m_pRec->GetCollect("sch_name"));
		m_list.SetItemText(j, 2, (LPTSTR)(_bstr_t)m_pRec->GetCollect("m_id"));
		m_list.SetItemText(j, 3, (LPTSTR)(_bstr_t)m_pRec->GetCollect("m_name"));
		m_list.SetItemText(j, 4, (LPTSTR)(_bstr_t)m_pRec->GetCollect("score"));
		m_pRec->MoveNext();
		j++;
	}
}

// 查看学生信息
void sys_admin::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
		// TODO: 在此添加控件通知处理程序代码
	// 插入数据
	while (m_list.DeleteColumn(0));
	m_list.ModifyStyle(LVS_ICON | LVS_SMALLICON | LVS_LIST, LVS_REPORT);
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_list.InsertColumn(0, "学号");
	m_list.InsertColumn(1, "姓名");
	m_list.InsertColumn(2, "班级");
	m_list.InsertColumn(3, "总分");
	RECT rect;
	m_list.GetWindowRect(&rect); int wid = (rect.right - rect.left) / 4;//wid 格宽度
	m_list.SetColumnWidth(0, wid);
	m_list.SetColumnWidth(1, wid);
	m_list.SetColumnWidth(2, wid);
	m_list.SetColumnWidth(3, wid);

	CString sql;
	sql.Format("exec Find_all_stu");
	m_pRec = DBRecordSetGet(sql);

	if (m_pRec->adoEOF)
		return;

	m_list.DeleteAllItems();
	int j = 0;
	while (!m_pRec->adoEOF)
	{
		m_list.InsertItem(j, "");
		_variant_t var;

		m_list.SetItemText(j, 0, (LPTSTR)(_bstr_t)m_pRec->GetCollect("id"));
		m_list.SetItemText(j, 1, (LPTSTR)(_bstr_t)m_pRec->GetCollect("name"));
		m_list.SetItemText(j, 2, (LPTSTR)(_bstr_t)m_pRec->GetCollect("class"));
		m_list.SetItemText(j, 3, (LPTSTR)(_bstr_t)m_pRec->GetCollect("score"));
		m_pRec->MoveNext();
		j++;
	}
}

void sys_admin::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

}

// 修改学校信息
void sys_admin::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码

	modifySch dlg;
	dlg.m_pCon = m_pCon;
	dlg.DoModal();

}


void sys_admin::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CString m_class;
	CString m_cou;
	GetDlgItemText(IDC_EDIT1, m_class);
	GetDlgItemText(IDC_EDIT6, m_cou);

	CString sql;
	int t = _ttoi(m_class);
	sql.Format("exec Find_score '%d', '%s'", t, m_cou);
	m_pRec = DBRecordSetGet(sql);

	// 设置最高最低平均分
	_variant_t var;
	CString str;

	GetCollect("Average_Score", var);
	int temp = int(var.bstrVal);
	str.Format("%d", temp);
	SetDlgItemText(IDC_EDIT2, str);

	GetCollect("Highest_Score", var);
	temp = int(var.bstrVal);
	str.Format("%d", temp);
	SetDlgItemText(IDC_EDIT3, str);

	GetCollect("Lowest_Score", var);
	temp = int(var.bstrVal);
	str.Format("%d", temp);
	SetDlgItemText(IDC_EDIT4, str);
	
}
_RecordsetPtr sys_admin::DBRecordSetGet(LPCTSTR Sql)
{
	// TODO: 在此处添加实现代码.
	m_pRec.CreateInstance("ADODB.Recordset");
	m_pRec = m_pCon->Execute((_bstr_t)Sql, NULL, adCmdText);
	return m_pRec;
	//return _RecordsetPtr();
}


BOOL sys_admin::GetCollect(LPCTSTR Name, _variant_t& OutCol)
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




void sys_admin::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void sys_admin::OnEnChangeEdit6()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void sys_admin::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void sys_admin::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void sys_admin::OnEnChangeEdit4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
