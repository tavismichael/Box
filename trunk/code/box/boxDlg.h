// boxDlg.h : header file
//

#if !defined(AFX_BOXDLG_H__D96D2151_DE46_4A00_9AD2_E7A2A4566794__INCLUDED_)
#define AFX_BOXDLG_H__D96D2151_DE46_4A00_9AD2_E7A2A4566794__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Analyse/Analyse.h"
#include "Analyse/EditKeyFile.h"

/////////////////////////////////////////////////////////////////////////////
// CBoxDlg dialog

class CBoxDlg : public CDialog
{
// Construction
public:
	CBoxDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CBoxDlg)
	enum { IDD = IDD_BOX_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBoxDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	
	CString		m_valEditMeasurPath;//�������ϲ����ļ�
	CButton		m_ctrlButtonSelmeasurfile;

	CString		m_valEditKeyFilePath;//���ϲ�����ʼֵkey�ļ�
	CButton		m_ctrlButtonSelkeyfile;

	CComboBox	m_ctrlParameter;//���ϲ���
	CString 	m_valEditParameter;//���ϲ���ֵ
	CEdit		m_ctrlEditParameter;
	CButton		m_ctrlButtonSetkey;
	CButton		m_ctrlButtonClearTemp;//

	CString		m_valEditDecValue;//�Ż�Ŀ��
	CEdit		m_ctrlEditDecValue;

	CListCtrl	m_ctrlListLog;//������־
	
	CButton		m_ctrlButtonAnalyse;
	CButton		m_ctrlButtonSet;

	char		m_szFileExePath[MAX_PATH];
	char		m_szFileDataPath[MAX_PATH];
	char		m_szdynFilePath[MAX_PATH];
	char		m_szblkFilePath[MAX_PATH];
	char		m_szidxFilePath[MAX_PATH];
	char		m_szmodFilePath[MAX_PATH];

	CEditKeyFile  m_EditKeyFile;
	
	/*
	����ԭ��:int	GetFilePath(void);
	����˵��:��	
	����ֵ:�ɹ�����0 ���򷵻�-1
	��������:ȡ���ļ������·��
	*/	
	int GetFilePath(void);

	/*
	����ԭ��:void EnableCtrl(IN BOOL bEnable);
	����˵��:��	
	����ֵ:��
	��������:���ÿؼ��Ƿ����
	*/	
	void EnableCtrl(IN BOOL bEnable);
	/*
	����ԭ��:BOOL DeleteDirectory(CString strPath);
	����˵��:��	
	����ֵ:��
	��������:ɾ��Ŀ¼
	*/	
	BOOL DeleteDirectory(CString strPath);

	// Generated message map functions
	//{{AFX_MSG(CBoxDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonAnalyse();
	afx_msg void OnButtonSet();
	afx_msg void OnButtonSelmeasurfile();
	afx_msg void OnButtonSelkeyfile();
	afx_msg void OnEditchangeComboParamater();
	afx_msg void OnSelchangeComboParamater();
	afx_msg void OnButtonSetkey();
	afx_msg void OnInsertRunLog(WPARAM wParam, LPARAM lParam);
	afx_msg void OnAnalyseComplete(WPARAM wParam, LPARAM lParam);
	afx_msg void OnButtonClearTemp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BOXDLG_H__D96D2151_DE46_4A00_9AD2_E7A2A4566794__INCLUDED_)
