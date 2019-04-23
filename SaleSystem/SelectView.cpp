// SelectView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SaleSystem.h"
#include "SelectView.h"
#include "MainFrm.h"


// CSelectView

IMPLEMENT_DYNCREATE(CSelectView, CTreeView)

CSelectView::CSelectView()
{

}

CSelectView::~CSelectView()
{
}

BEGIN_MESSAGE_MAP(CSelectView, CTreeView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CSelectView::OnTvnSelchanged)
END_MESSAGE_MAP()


// CSelectView ���

#ifdef _DEBUG
void CSelectView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CSelectView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSelectView ��Ϣ�������


void CSelectView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	HICON icon = AfxGetApp()->LoadIconW(IDI_ICON_RE);
	m_imageList.Create(30, 30, ILC_COLOR32, 1, 1);
	m_imageList.Add(icon);
	m_treeCtrl = &GetTreeCtrl();
	m_treeCtrl->SetImageList(&m_imageList, TVSIL_NORMAL);

	m_treeCtrl->InsertItem(_T("������Ϣ"), 0, 0, NULL);
	m_treeCtrl->InsertItem(_T("���۹���"), 0, 0, NULL);
	m_treeCtrl->InsertItem(_T("�����Ϣ"), 0, 0, NULL);
	m_treeCtrl->InsertItem(_T("������"), 0, 0, NULL);
	m_treeCtrl->InsertItem(_T("���ɾ��"), 0, 0, NULL);
}


void CSelectView::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	HTREEITEM items = m_treeCtrl->GetSelectedItem();
	CString item = m_treeCtrl->GetItemText(items);
	if (item==_T("������Ϣ")) {
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(),NM_A,(WPARAM)NM_A,(LPARAM)0);
	}else if(item==_T("���۹���")){
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_B, (WPARAM)NM_B, (LPARAM)0);
	}
	else if (item == _T("�����Ϣ")) {
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_C, (WPARAM)NM_C, (LPARAM)0);
	}
	else if (item == _T("������")) {
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_D, (WPARAM)NM_D, (LPARAM)0);
	}
	else if (item == _T("���ɾ��")) {
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_E, (WPARAM)NM_E, (LPARAM)0);
	}
}
