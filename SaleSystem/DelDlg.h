#pragma once
#include "afxwin.h"



// CDelDlg ������ͼ

class CDelDlg : public CFormView
{
	DECLARE_DYNCREATE(CDelDlg)

protected:
	CDelDlg();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CDelDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_combo;
	int m_price;
	int m_num;
	virtual void OnInitialUpdate();
};

