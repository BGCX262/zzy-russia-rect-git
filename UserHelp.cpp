// UserHelp.cpp : implementation file
//

#include "stdafx.h"
#include "RussiaRect.h"
#include "UserHelp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserHelp dialog


CUserHelp::CUserHelp(CWnd* pParent /*=NULL*/)
	: CDialog(CUserHelp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUserHelp)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CUserHelp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserHelp)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUserHelp, CDialog)
	//{{AFX_MSG_MAP(CUserHelp)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserHelp message handlers
