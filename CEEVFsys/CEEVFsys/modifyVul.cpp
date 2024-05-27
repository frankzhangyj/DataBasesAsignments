// modifyVul.cpp: 实现文件
//
#include "pch.h"
#include "modifyVul.h"

// modifyVul 对话框

IMPLEMENT_DYNAMIC(modifyVul, CDialogEx)

modifyVul::modifyVul(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_modifyVul, pParent)
{

}

modifyVul::~modifyVul()
{
}


BEGIN_MESSAGE_MAP(modifyVul, CDialogEx)
	ON_BN_CLICKED(IDOK, &modifyVul::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT2, &modifyVul::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT1, &modifyVul::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, &modifyVul::OnBnClickedButton1)
END_MESSAGE_MAP()


// modifyVul 消息处理程序


void modifyVul::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	// CDialogEx::OnOK();
	CString sch;
	CString may;
	GetDlgItemText(IDC_EDIT1, sch);
	GetDlgItemText(IDC_EDIT2, may);

	m_sch = _ttoi(sch);
	m_may = _ttoi(may);

	CString sql1;
	sql1.Format("exec check_sch '%d'", m_sch);
	m_pRec = DBRecordSetGet(sql1);

	_variant_t var;
	GetCollect("cnt", var);//cnt 与你创建的存储过程里的名称对应
	int temp = var.intVal;

	if (temp == 0) {
		MessageBox("学校不存在！");
		return;
	}

	CString sql2;
	sql2.Format("exec check_may '%d'", m_may);
	m_pRec = DBRecordSetGet(sql2);

	GetCollect("cnt", var);//cnt 与你创建的存储过程里的名称对应
	temp = var.intVal;

	if (temp == 0) {
		MessageBox("专业不存在！");
		return;
	}

	CString sql3;
	sql3.Format("exec check_dup '%d', '%d', '%d'", m_sno, m_sch, m_may);
	m_pRec = DBRecordSetGet(sql3);

	GetCollect("cnt", var);//cnt 与你创建的存储过程里的名称对应
	temp = var.intVal;

	if (temp != 0) {
		MessageBox("志愿已经存在！");
		return;
	}

	CString sql;
	sql.Format("exec add_stu_vul '%d','%d', '%d'", m_sno, m_sch, m_may);
	m_pRec = DBRecordSetGet(sql);
	if (m_pRec == NULL)
		return;
	else
		MessageBox("Succeed");
}

void modifyVul::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString sch;
	CString may;
	GetDlgItemText(IDC_EDIT1, sch);
	GetDlgItemText(IDC_EDIT2, may);

	_variant_t var;
	int temp;

	m_sch = _ttoi(sch);
	m_may = _ttoi(may);

	CString sql;
	sql.Format("exec check_dup '%d', '%d', '%d'", m_sno, m_sch, m_may);
	m_pRec = DBRecordSetGet(sql);

	GetCollect("cnt", var);//cnt 与你创建的存储过程里的名称对应
	temp = var.intVal;

	if (temp == 0) {
		MessageBox("志愿不存在！");
		return;
	}

	CString sql1;
	sql1.Format("exec del_stu_vul '%d','%d','%d'", m_sno, m_sch, m_may);
	m_pRec = DBRecordSetGet(sql1);
	if (m_pRec == NULL)
		return;
	else
		MessageBox("Succeed");

}


BOOL modifyVul::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

_RecordsetPtr modifyVul::DBRecordSetGet(LPCTSTR Sql)
{
	// TODO: 在此处添加实现代码.
	m_pRec.CreateInstance("ADODB.Recordset");
	m_pRec = m_pCon->Execute((_bstr_t)Sql, NULL, adCmdText);
	return m_pRec;
	//return _RecordsetPtr();
}


BOOL modifyVul::GetCollect(LPCTSTR Name, _variant_t& OutCol)
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


void modifyVul::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void modifyVul::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
