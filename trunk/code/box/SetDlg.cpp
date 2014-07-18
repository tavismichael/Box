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
	
 	m_ctrlListSet.InsertColumn(nColNum++, "���", LVCFMT_LEFT, 40);//���ϲ������
	m_ctrlListSet.InsertColumn(nColNum++, "ȫ��", LVCFMT_LEFT, 60);//���ϲ�������
	m_ctrlListSet.InsertColumn(nColNum++, "��ֵ", LVCFMT_LEFT, 90);//��������ֵ
	m_ctrlListSet.InsertColumn(nColNum++, "������Сֵ", LVCFMT_LEFT, 90);//��������ֵ
	m_ctrlListSet.InsertColumn(nColNum++, "�������ֵ", LVCFMT_LEFT, 90);//��������ֵ
	m_ctrlListSet.InsertColumn(nColNum++, "�Ƿ���", LVCFMT_LEFT, 70);//�Ƿ���з���
	m_ctrlListSet.SetEableEdit(1, false);
	m_ctrlListSet.SetEableEdit(2, false);
	m_ctrlListSet.SetEableEdit(3, false);

	//��Ӳ���ֵ
	m_SystemSet.Init();	
	m_SystemSet.GetSystem(m_Systems);
	
	for (int i=0; i<m_Systems.size(); i++)
	{
		CString strtemp;
		CString strKeyShortName;

		Type_SystemSet stuSystemSet = m_Systems[i];
	
		//���ϲ������
		strtemp = stuSystemSet.szShortCaption;
		m_ctrlListSet.InsertItem(0,strtemp);
		strKeyShortName = strtemp;

		//���ϲ�������
		strtemp = stuSystemSet.szCaption;
		m_ctrlListSet.SetItemText(0, 1, strtemp);

		//���ϲ�����ֵ
		m_EditKeyFile.GetKeyValue(strKeyShortName, strtemp);
		m_ctrlListSet.SetItemText(0, 2, strtemp);
		
		//��������ֵ
		strtemp = stuSystemSet.dDownStep;
		m_ctrlListSet.SetItemText(0, 3, strtemp);	

		//��������ֵ
		strtemp = stuSystemSet.dUpStep;
		m_ctrlListSet.SetItemText(0, 4, strtemp);

		//�Ƿ���з���
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
	strXML += " <!--���ϲ���-->\n";

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
			strIsReverse = "��";
		}
		else
		{
			strIsReverse = "��";	
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
