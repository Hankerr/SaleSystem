// SellDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SaleSystem.h"
#include "SellDlg.h"
#include "InfoFile.h"


// CSellDlg

IMPLEMENT_DYNCREATE(CSellDlg, CFormView)

CSellDlg::CSellDlg()
	: CFormView(DIALOG_SELL)
	, m_price(0)
	, m_num(0)
	, m_sellInfo(_T(""))
{

}

CSellDlg::~CSellDlg()
{
}

void CSellDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_price);
	DDX_Text(pDX, IDC_EDIT2, m_num);
	DDX_Text(pDX, IDC_EDIT3, m_sellInfo);
}

BEGIN_MESSAGE_MAP(CSellDlg, CFormView)
	ON_CBN_SELENDCANCEL(IDC_COMBO1, &CSellDlg::OnCbnSelendcancelCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CSellDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSellDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CSellDlg 诊断

#ifdef _DEBUG
void CSellDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CSellDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSellDlg 消息处理程序


void CSellDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end();it++) {
		m_combo.AddString((CString)it->name.c_str());
	}

	file.ls.clear();
	
	m_combo.SetCurSel(0);
}


void CSellDlg::OnCbnSelendcancelCombo1()
{
	CString text;
	int index = m_combo.GetCurSel();
	m_combo.GetLBText(index, text);

	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end();it++) {
		if (text==it->name.c_str()) {
			m_price = it->price;
			m_num = 0;
			UpdateData(FALSE);
		}
	}
	file.ls.clear();
}


void CSellDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	if (m_num == 0) {
		AfxMessageBox(_T("购买商品不能为0"));
		return;
	}

	CString type;
	int index = m_combo.GetCurSel();
	m_combo.GetLBText(index, type);

	CString str;
	str.Format(_T("商品：%s\r\n单价：%d\r\n个数：%d\r\n总价：%d"),type,m_price,m_num,m_price*m_num);
	m_sellInfo = str;
	UpdateData(FALSE);
	AfxMessageBox(str);

	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end();it++) {
		if (type == it->name.c_str()) {
			it->num = it->num - m_num;
		}
	}
	file.WirteDocline();

	file.ls.clear();
	m_sellInfo.Empty();
	m_num = 0;
	UpdateData(FALSE);
}


void CSellDlg::OnBnClickedButton2()
{
	m_combo.SetCurSel(0);
	m_sellInfo = "";
	m_num = 0;
	OnCbnSelendcancelCombo1();
}
