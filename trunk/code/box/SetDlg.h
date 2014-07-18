#if !defined(AFX_SET_H__5AD71E1C_C717_4EFA_821C_EB95F3B2AAEF__INCLUDED_)
#define AFX_SET_H__5AD71E1C_C717_4EFA_821C_EB95F3B2AAEF__INCLUDED_

#include "Analyse/SystemSet.h"
#include "Analyse/EditKeyFile.h"
#include "EditListCtrl.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Set.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetDlg dialog

class CSetDlg : public CDialog
{
// Construction
public:
	CSetDlg(CWnd* pParent = NULL);   // standard constructor

	void Init(IN CString strKeyFilePath);

// Dialog Data
	//{{AFX_DATA(CSetDlg)
	enum { IDD = IDD_BOX_SET };
		// NOTE: the ClassWizard will add data members here
	CEditListCtrl	m_ctrlListSet;

	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CSystemSet					m_SystemSet;
	vector<Type_SystemSet>		m_Systems;
	CEditKeyFile				m_EditKeyFile;

	// Generated message map functions
	//{{AFX_MSG(CSetDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SET_H__5AD71E1C_C717_4EFA_821C_EB95F3B2AAEF__INCLUDED_)
