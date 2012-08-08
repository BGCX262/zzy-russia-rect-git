// RussiaRectDoc.cpp : implementation of the CRussiaRectDoc class
//

#include "stdafx.h"
#include "RussiaRect.h"

#include "RussiaRectDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRussiaRectDoc

IMPLEMENT_DYNCREATE(CRussiaRectDoc, CDocument)

BEGIN_MESSAGE_MAP(CRussiaRectDoc, CDocument)
	//{{AFX_MSG_MAP(CRussiaRectDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRussiaRectDoc construction/destruction

CRussiaRectDoc::CRussiaRectDoc()
{
	// TODO: add one-time construction code here

}

CRussiaRectDoc::~CRussiaRectDoc()
{
}

BOOL CRussiaRectDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CRussiaRectDoc serialization

void CRussiaRectDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CRussiaRectDoc diagnostics

#ifdef _DEBUG
void CRussiaRectDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRussiaRectDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRussiaRectDoc commands
