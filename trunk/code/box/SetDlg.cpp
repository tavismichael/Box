// Set.cpp : implementation file
//

#include "stdafx.h"
#include "box.h"
#include "SetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetDlg dialog


CSetDlg::CSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SET, m_ctrlListSet);

	//{{AFX_DATA_MAP(CSetDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetDlg, CDialog)
	//{{AFX_MSG_MAP(CSetDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetDlg message handlers
void CSetDlg::Init(IN CString strKeyFilePath)
{
	m_EditKeyFile.Init(strKeyFilePath);
}

BOOL CSetDlg::OnInitDialog() 
{
	int nColNum = 0;

	CDialog::OnInitDialog();	
	
	m_ctrlListSet.ModifyStyle(0, LVS_REPORT);
	m_ctrlListSet.SetExtendedStyle (LVS_EX_INFOTIP | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	
 	m_ctrlListSet.InsertColumn(nColNum++, "简称", LVCFMT_LEFT, 40);//材料参数简称
	m_ctrlListSet.InsertColumn(nColNum++, "全称", LVCFMT_LEFT, 60);//材料参数名称
	m_ctrlListSet.InsertColumn(nColNum++, "初值", LVCFMT_LEFT, 90);//向上搜索值
	m_ctrlListSet.InsertColumn(nColNum++, "反求最小值", LVCFMT_LEFT, 90);//向上搜索值
	m_ctrlListSet.InsertColumn(nColNum++, "反求最大值", LVCFMT_LEFT, 90);//向下搜索值
	m_ctrlListSet.InsertColumn(nColNum++, "是否反求", LVCFMT_LEFT, 70);//是否进行反求
	m_ctrlListSet.SetEableEdit(1, false);
	m_ctrlListSet.SetEableEdit(2, false);
	m_ctrlListSet.SetEableEdit(3, false);

	//添加参数值
	m_SystemSet.Init();	
	m_SystemSet.GetSystem(m_Systems);
	
	for (int i=0; i<m_Systems.size(); i++)
	{
		CString strtemp;
		CString strKeyShortName;

		Type_SystemSet stuSystemSet = m_Systems[i];
	
		//材料参数简称
		strtemp = stuSystemSet.szShortCaption;
		m_ctrlListSet.InsertItem(0,strtemp);
		strKeyShortName = strtemp;

		//材料参数名称
		strtemp = stuSystemSet.szCaption;
		m_ctrlListSet.SetItemText(0, 1, strtemp);

		//材料参数初值
		m_EditKeyFile.GetKeyValue(strKeyShortName, strtemp);
		m_ctrlListSet.SetItemText(0, 2, strtemp);
		
		//向下搜索值
		strtemp = stuSystemSet.dDownStep;
		m_ctrlListSet.SetItemText(0, 3, strtemp);	

		//向上搜索值
		strtemp = stuSystemSet.dUpStep;
		m_ctrlListSet.SetItemText(0, 4, strtemp);

		//是否进行反求
		strtemp.Format("%d", stuSystemSet.bIsReverse);
		m_ctrlListSet.SetItemText(0, 5, strtemp);	
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSetDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	int nCount = m_ctrlListSet.GetItemCount();
	CString strXML;
	strXML = "<?xml version=\"1.0\" encoding=\"GB2312\" standalone=\"yes\"?>\n";
	strXML += "<SystemSet>\n";
	strXML += " <!--材料参数-->\n";

	for(int i=nCount; i>0; i--)
	{
		CString strTemp;
		CString strKeyShortName = m_ctrlListSet.GetItemText(i - 1, 0);
		CString strKeyName = m_ctrlListSet.GetItemText(i - 1, 1);
		CString strDownStep = m_ctrlListSet.GetItemText(i - 1, 3);	
		CString strUpStep = m_ctrlListSet.GetItemText(i - 1, 4);	
		CString strIsReverse = m_ctrlListSet.GetItemText(i - 1, 5);	
		if (strIsReverse == "0")
		{
			strIsReverse = "否";
		}
		else
		{
			strIsReverse = "是";	
		}
		
		strTemp.Format("<material ShortCaption=\"%s\" szCaption=\"%s\" dDownStep=\"%s\" dUpStep=\"%s\"  bIsReverse=\"%s\"/>\n",
			strKeyShortName, strKeyName, strDownStep, strUpStep, strIsReverse);
		strXML += strTemp;		
	}
	
	strXML += "</SystemSet>";	
	
	m_SystemSet.m_xml.SaveXML(strXML);
	CDialog::OnOK();
}

void CSetDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
