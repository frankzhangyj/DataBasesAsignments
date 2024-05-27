// modifySch.cpp: 实现文件
//

#include "pch.h"
#include "CEEVFsys.h"
#include "afxdialogex.h"
#include "modifySch.h"


// modifySch 对话框

IMPLEMENT_DYNAMIC(modifySch, CDialogEx)

modifySch::modifySch(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_modifySch, pParent)
{

}

modifySch::~modifySch()
{
}

void modifySch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(modifySch, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &modifySch::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &modifySch::OnEnChangeEdit2)
	ON_BN_CLICKED(IDOK, &modifySch::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT3, &modifySch::OnEnChangeEdit3)
	ON_BN_CLICKED(IDC_BUTTON1, &modifySch::OnBnClickedButton1)
END_MESSAGE_MAP()


// modifySch 消息处理程序

void modifySch::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	// CDialogEx::OnOK();
	_variant_t var;
	int sch_id;
	int may_id;

	// 插入学校
	GetDlgItemText(IDC_EDIT1, sch);

	if (strlen(sch) > 1) {
		CString sql1;
		sql1.Format("exec insert_sch '%s'", sch);
		m_pRec = DBRecordSetGet(sql1);

		CString sql2;
		sql2.Format("exec Find_sch_id '%s'", sch);
		m_pRec = DBRecordSetGet(sql2);

		GetCollect("id", var);
		sch_id = int(var.bstrVal);
	}

	// 插入专业 (可能会出现重复)
	GetDlgItemText(IDC_EDIT2, may);

	if (strlen(may) > 1) {
		CString sql3;
		sql3.Format("exec insert_may '%s'", may);
		m_pRec = DBRecordSetGet(sql3);

		CString sql4;
		sql4.Format("exec Find_may_id '%s'", may);
		m_pRec = DBRecordSetGet(sql4);

		GetCollect("id", var);
		may_id = int(var.bstrVal);
	}

	// 插入分数
	CString temp;
	GetDlgItemText(IDC_EDIT3, temp);

	if (strlen(temp) > 1) {
		score = _ttoi(temp);

		CString sql5;
		sql5.Format("exec Insert_sm_rel '%d', '%d', '%d'", sch_id, may_id, score);
		m_pRec = DBRecordSetGet(sql5);
	}
	
	if (strlen(sch) < 1 && strlen(may) < 1 && strlen(temp) < 1) {
		MessageBox("插入失败");
		return;
	}
	
	MessageBox("Succeed");

}

void modifySch::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	_variant_t var;
	int sch_id;
	int may_id;

	// 
	GetDlgItemText(IDC_EDIT1, sch);

	if (strlen(sch) > 1) {
		CString sql1;
		sql1.Format("exec Find_sch_id '%s'", sch);
		m_pRec = DBRecordSetGet(sql1);

		GetCollect("id", var);
		sch_id = int(var.bstrVal);

		CString sql2;
		sql2.Format("exec Del_s_rel '%d'", sch_id);
		m_pRec = DBRecordSetGet(sql2);

		CString sql3;
		sql3.Format("exec Del_sch '%s'", sch);
		m_pRec = DBRecordSetGet(sql3);

		}
	// 
	GetDlgItemText(IDC_EDIT2, may);

	if (strlen(may) > 1) {
		CString sql4;
		sql4.Format("exec Find_may_id '%s'", may);
		m_pRec = DBRecordSetGet(sql4);

		GetCollect("id", var);
		may_id = int(var.bstrVal);

		CString sql5;
		sql5.Format("exec Del_m_rel '%d'", may_id);
		m_pRec = DBRecordSetGet(sql5);

		CString sql6;
		sql6.Format("exec Del_may '%s'", may);
		m_pRec = DBRecordSetGet(sql6);

	}

	MessageBox("Succeed");
}


_RecordsetPtr modifySch::DBRecordSetGet(LPCTSTR Sql)
{
	// TODO: 在此处添加实现代码.
	m_pRec.CreateInstance("ADODB.Recordset");
	m_pRec = m_pCon->Execute((_bstr_t)Sql, NULL, adCmdText);
	return m_pRec;
	//return _RecordsetPtr();
}


BOOL modifySch::GetCollect(LPCTSTR Name, _variant_t& OutCol)
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

BOOL modifySch::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void modifySch::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void modifySch::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void modifySch::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}



