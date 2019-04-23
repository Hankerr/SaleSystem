// LoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SaleSystem.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include "InfoFile.h"


// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(DIALOG_LOGIN, pParent)
	, m_user(_T(""))
	, m_pwd(_T(""))
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_user);
	DDX_Text(pDX, IDC_EDIT2, m_pwd);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CLoginDlg::OnBnClickedButton1)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON2, &CLoginDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_user = _T("请输入用户名");
	m_pwd = _T("请输入密码");
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

//login
void CLoginDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);

	CInfoFile file;
	CString user, pwd;

	file.ReadLogin(user, pwd);

	if (m_user == user) {
		if (m_pwd==pwd) {
			CDialogEx::OnOK();
		}
		else {
			AfxMessageBox(_T("密码错误！"));
			m_user.Empty();
			m_pwd.Empty();
		}
	}
	else {
		AfxMessageBox(_T("用户不存在！"));
		m_user.Empty();
		m_pwd.Empty();
	}
}


void CLoginDlg::OnClose()
{
	exit(0);
	CDialogEx::OnClose();
}


void CLoginDlg::OnBnClickedButton2()
{
	exit(0);
}


void CLoginDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}
