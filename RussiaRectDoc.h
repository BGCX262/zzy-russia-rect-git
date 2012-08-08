// RussiaRectDoc.h : interface of the CRussiaRectDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RUSSIARECTDOC_H__EBA9B8C7_CFDC_430F_A4D0_52F96CA6C18B__INCLUDED_)
#define AFX_RUSSIARECTDOC_H__EBA9B8C7_CFDC_430F_A4D0_52F96CA6C18B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CRussiaRectDoc : public CDocument
{
protected: // create from serialization only
	CRussiaRectDoc();
	DECLARE_DYNCREATE(CRussiaRectDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRussiaRectDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRussiaRectDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CRussiaRectDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RUSSIARECTDOC_H__EBA9B8C7_CFDC_430F_A4D0_52F96CA6C18B__INCLUDED_)
