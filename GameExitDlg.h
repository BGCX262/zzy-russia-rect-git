#if !defined(AFX_GAMEEXITDLG_H__1D762E50_894E_4FD6_8836_DE97C25D2A22__INCLUDED_)
#define AFX_GAMEEXITDLG_H__1D762E50_894E_4FD6_8836_DE97C25D2A22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GameExitDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGameExitDlg dialog

class CGameExitDlg : public CDialog
{
// Construction
public:
	CGameExitDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGameExitDlg)
	enum { IDD = IDD_DIALOG3 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGameExitDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGameExitDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GAMEEXITDLG_H__1D762E50_894E_4FD6_8836_DE97C25D2A22__INCLUDED_)
