// UserDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SaleSystem.h"
#include "UserDlg.h"


// CUserDlg

IMPLEMENT_DYNCREATE(CUserDlg, CFormView)

CUserDlg::CUserDlg()
	: CFormView(DIALOG_USER)
	, m_user(_T(""))
	, m_newPwd(_T(""))
	, m_surePwd(_T(""))
	, m_name(_T(""))
{

}

CUserDlg::~CUserDlg()
{
}

void CUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_user);
	DDX_Text(pDX, IDC_EDIT3, m_newPwd);
	DDX_Text(pDX, IDC_EDIT4, m_surePwd);
	DDX_Text(pDX, IDC_EDIT2, m_name);
}

BEGIN_MESSAGE_MAP(CUserDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CUserDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CUserDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CUserDlg 诊断

#ifdef _DEBUG
void CUserDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CUserDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CUserDlg 消息处理程序


void CUserDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);

	m_user = _T("销售员");
	m_name = name;

	UpdateData(FALSE);
}


void CUserDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if (m_newPwd.IsEmpty()||m_surePwd.IsEmpty()) {
		AfxMessageBox(_T("密码不能为空"));
		return;
	}

	if (m_newPwd!=m_surePwd) {
		AfxMessageBox(_T("输入密码和确认密码不一致"));
		return;
	}

	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);

	if (m_surePwd==pwd) {
		AfxMessageBox(_T("输入密码和原始密码一致"));
		return;
	}
	
	char *tmpName, *tmpPwd;
	CStringA tmp1;
	tmp1 = name;
	tmpName = tmp1.GetBuffer();

	CStringA tmp2;
	tmp2 = pwd;
	tmpPwd = tmp2.GetBuffer();

	file.WritePwd(tmpName, tmpPwd);

	AfxMessageBox(_T("修改密码成功"));
	m_surePwd.Empty();
	m_newPwd.Empty();
	UpdateData(FALSE);
}


void CUserDlg::OnBnClickedButton2()
{
	m_surePwd.Empty();
	m_newPwd.Empty();
	UpdateData(FALSE);
}
