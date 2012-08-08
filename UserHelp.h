#if !defined(AFX_USERHELP_H__475978A6_F08E_4301_9170_C1CB252A92EC__INCLUDED_)
#define AFX_USERHELP_H__475978A6_F08E_4301_9170_C1CB252A92EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UserHelp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUserHelp dialog

class CUserHelp : public CDialog
{
// Construction
public:
	CUserHelp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUserHelp)
	enum { IDD = IDD_DIALOG2 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserHelp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUserHelp)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERHELP_H__475978A6_F08E_4301_9170_C1CB252A92EC__INCLUDED_)
