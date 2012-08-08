// ConnectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RussiaRect.h"
#include "ConnectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConnectDlg dialog


CConnectDlg::CConnectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConnectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConnectDlg)
	m_iConnectStatus = 0;
	//m_HostIP = "127.0.0.1" ;
	//}}AFX_DATA_INIT
}


void CConnectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConnectDlg)
	DDX_Control(pDX, IDC_IP_HOST, m_HostIP);
	DDX_Radio(pDX, IDC_RADIO1, m_iConnectStatus);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConnectDlg, CDialog)
	//{{AFX_MSG_MAP(CConnectDlg)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IP_HOST, OnFieldchangedIpHost)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConnectDlg message handlers

//DEL void CConnectDlg::OnOK() 
//DEL {
//DEL 	// TODO: Add extra validation here
//DEL 	
//DEL 	CDialog::OnOK();
//DEL }

void CConnectDlg::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	
}

void CConnectDlg::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	
}

void CConnectDlg::OnFieldchangedIpHost(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}
