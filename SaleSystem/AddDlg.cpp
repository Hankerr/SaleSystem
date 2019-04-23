// AddDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SaleSystem.h"
#include "AddDlg.h"
#include "InfoFile.h"


// CAddDlg

IMPLEMENT_DYNCREATE(CAddDlg, CFormView)

CAddDlg::CAddDlg()
	: CFormView(DIALOG_ADD)
	, m_price1(0)
	, m_num1(0)
	, m_name2(_T(""))
	, m_price2(0)
	, m_num2(0)
{

}

CAddDlg::~CAddDlg()
{
}

void CAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_price1);
	DDX_Text(pDX, IDC_EDIT2, m_num1);
	DDX_Text(pDX, IDC_EDIT5, m_name2);
	DDX_Text(pDX, IDC_EDIT3, m_price2);
	DDX_Text(pDX, IDC_EDIT4, m_num2);
}

BEGIN_MESSAGE_MAP(CAddDlg, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CAddDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CAddDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CAddDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CAddDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CAddDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CAddDlg ���

#ifdef _DEBUG
void CAddDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAddDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAddDlg ��Ϣ�������


void CAddDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++) {
		m_combo.AddString((CString)it->name.c_str());
	}

	file.ls.clear();

	m_combo.SetCurSel(0);
}


void CAddDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	if (m_num1==0) {
		AfxMessageBox(_T("��Ʒ��������Ϊ��"));
	}
	CString type;
	int index = m_combo.GetCurSel();
	m_combo.GetLBText(index, type);

	CString str;
	str.Format(_T("�������Ʒ��%s\r\n ���ۣ�%d\r\n ����:%d"), type, m_price1, m_num1);
	AfxMessageBox(str);
	CInfoFile file;
	file.ReadDocline(); //��ȡ��Ʒ��Ϣ
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (type == it->name.c_str())
		{
			it->num += m_num1;
		}
	}
	file.WirteDocline(); //�����ļ�����

	file.ls.clear(); //���list������

	m_num1 = 0;
	UpdateData(FALSE); //���µ���Ӧ�Ŀؼ�


}

void CAddDlg::OnCbnSelchangeCombo1()
{
	CString text;
	int index = m_combo.GetCurSel();
	m_combo.GetLBText(index, text);

	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++) {
		if (text == it->name.c_str()) {
			m_price1 = it->price;
			m_num1 = 0;
			UpdateData(FALSE);
		}
	}
	file.ls.clear();
}

void CAddDlg::OnBnClickedButton2()
{
	m_combo.SetCurSel(0);
	m_num1 = 0;
	OnCbnSelchangeCombo1();
}

void CAddDlg::OnBnClickedButton3()
{
	UpdateData(TRUE); //��ȡ�ؼ�����

	if (m_num2 <= 0 || m_price2 <= 0 || m_name2.IsEmpty())
	{
		AfxMessageBox(_T("������Ϣ����"));
		return;
	}

	//��Ҫ����#include "InfoFile.h"
	CInfoFile file;
	file.ReadDocline(); //��ȡ��Ʒ��Ϣ
	file.Addline(m_name2, m_num2, m_price2); //�����Ʒ
	file.WirteDocline(); //д�ļ�
	file.ls.clear(); //���list������
	AfxMessageBox(_T("��ӳɹ�"));

	m_name2.Empty();
	m_num2 = 0;
	m_price2 = 0;
	UpdateData(FALSE);
}


void CAddDlg::OnBnClickedButton4()
{
	m_name2.Empty();
	m_num2 = 0;
	m_price2 = 0;
	UpdateData(FALSE);
}
