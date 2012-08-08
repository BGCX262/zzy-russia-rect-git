// GameExitDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RussiaRect.h"
#include "GameExitDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGameExitDlg dialog


CGameExitDlg::CGameExitDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGameExitDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGameExitDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CGameExitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGameExitDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGameExitDlg, CDialog)
	//{{AFX_MSG_MAP(CGameExitDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGameExitDlg message handlers
