// boxDlg.cpp : implementation file
//

#include "stdafx.h"
#include "box.h"
#include "boxDlg.h"
#include "SetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBoxDlg dialog

CBoxDlg::CBoxDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBoxDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBoxDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CBoxDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
		DDX_Text(pDX, IDC_EDIT_MEASUREPATH, m_valEditMeasurPath);
		DDX_Text(pDX, IDC_EDIT_KEYFILEPATH, m_valEditKeyFilePath);
		DDX_Control(pDX, IDC_COMBO_PARAMATER, m_ctrlParameter);
		DDX_Text(pDX, IDC_EDIT_PARAMATER, m_valEditParameter);		
		DDX_Text(pDX, IDC_EDIT_DECVALUE, m_valEditDecValue);
		DDX_Control(pDX, IDC_LIST_LOG, m_ctrlListLog);	
		DDX_Control(pDX, IDC_EDIT_DECVALUE,m_ctrlEditDecValue);
		DDX_Control(pDX, IDC_EDIT_PARAMATER, m_ctrlEditParameter);
		DDX_Control(pDX, IDC_BUTTON_SELMEASURFILE, m_ctrlButtonSelmeasurfile);
		DDX_Control(pDX, IDC_BUTTON_SELKEYFILE, m_ctrlButtonSelkeyfile);
		DDX_Control(pDX, IDC_BUTTON_SETKEY, m_ctrlButtonSetkey);
		DDX_Control(pDX, IDC_CLEARTEMP, m_ctrlButtonClearTemp);
		DDX_Control(pDX, IDC_BUTTON_ANALYSE, m_ctrlButtonAnalyse);
		DDX_Control(pDX, IDC_BUTTON_SET, m_ctrlButtonSet);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBoxDlg, CDialog)
	//{{AFX_MSG_MAP(CBoxDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ANALYSE, OnButtonAnalyse)
	ON_BN_CLICKED(IDC_BUTTON_SET, OnButtonSet)
	ON_BN_CLICKED(IDC_CLEARTEMP, OnButtonClearTemp)
	ON_BN_CLICKED(IDC_BUTTON_SELMEASURFILE, OnButtonSelmeasurfile)
	ON_BN_CLICKED(IDC_BUTTON_SELKEYFILE, OnButtonSelkeyfile)
	ON_CBN_EDITCHANGE(IDC_COMBO_PARAMATER, OnEditchangeComboParamater)
	ON_CBN_SELCHANGE(IDC_COMBO_PARAMATER, OnSelchangeComboParamater)
	ON_BN_CLICKED(IDC_BUTTON_SETKEY, OnButtonSetkey)
	ON_MESSAGE(MSG_INSERTLOG,OnInsertRunLog)
	ON_MESSAGE(MSG_COMPLETE,OnAnalyseComplete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBoxDlg message handlers

BOOL CBoxDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_ctrlParameter.AddString("MID");//
	m_ctrlParameter.AddString("RO");//
	m_ctrlParameter.AddString("E");//
	m_ctrlParameter.AddString("PR");//
	m_ctrlParameter.AddString("HR");//
	m_ctrlParameter.AddString("P2");//
	m_ctrlParameter.AddString("M");//
	m_ctrlParameter.AddString("R00");//
	m_ctrlParameter.AddString("R45");//
	m_ctrlParameter.AddString("R90");//
	m_ctrlParameter.AddString("LCID");//
	m_ctrlParameter.AddString("E0");//
	m_ctrlParameter.AddString("SPI");//
	m_ctrlParameter.AddString("AOPT");//

	GetFilePath();

	m_EditKeyFile.Init(m_szdynFilePath);
	
	m_ctrlListLog.ModifyStyle(0,LVS_REPORT);
	m_ctrlListLog.SetExtendedStyle (LVS_EX_INFOTIP | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	
 	m_ctrlListLog.InsertColumn(1, "时间", LVCFMT_CENTER, 60);//时间
	m_ctrlListLog.InsertColumn(2 ,"日志内容",LVCFMT_CENTER,400);//日志内容
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBoxDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBoxDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBoxDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CBoxDlg::OnButtonAnalyse() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString strButtonText;
	double fDecValue = 0.0;

	if (m_valEditMeasurPath == "")
	{
		AfxMessageBox("请输入试验测量材料参数值!");
		return;
	}

	if (m_valEditDecValue == "")
	{
		AfxMessageBox("请输入优化目标值!");
		return;
	}
	else
	{
		fDecValue = atof(m_valEditDecValue);
		if(fDecValue > 0)
		{
		}
		else
		{
			AfxMessageBox("输入优化目标值错误!");
			return;
		}
	}

	m_ctrlButtonAnalyse.GetWindowText(strButtonText);
	if (strButtonText == "开始分析")
	{
		Type_ThreadMSG *msg = new Type_ThreadMSG;

		msg->hWnd = this->m_hWnd;
		msg->strMeasurPath = m_valEditMeasurPath;
		msg->fDecValue = fDecValue;

	//CAnalyse::AnalyeKeyFile((void*)(long)msg);
		AfxBeginThread(CAnalyse::AnalyeKeyFile, (void*)(long)msg, THREAD_PRIORITY_HIGHEST);
		EnableCtrl(FALSE);
	}

}

void CBoxDlg::OnButtonSet() 
{
	// TODO: Add your control notification handler code here
	CSetDlg dlg;

	dlg.Init(m_szdynFilePath);
	dlg.DoModal();
}

void CBoxDlg::OnButtonSelmeasurfile() 
{
	// TODO: Add your control notification handler code here
	char szFilter[MAX_PATH];

	memset(szFilter, '0' , sizeof(szFilter));
	strcpy(szFilter, "Worksheet Files(*.xls)|*.xls|");
	CFileDialog	opendlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);

	if (opendlg.DoModal() == IDOK)
	{
		m_valEditMeasurPath	= opendlg.GetPathName();
		UpdateData(FALSE);
	}
	
}
//选择key文件并将key文件拷贝到..\Data\keyfile目录
void CBoxDlg::OnButtonSelkeyfile() 
{
	// TODO: Add your control notification handler code here
	char szFilter[MAX_PATH];

	memset(szFilter, '0' , sizeof(szFilter));
	strcpy(szFilter, "Worksheet Files(*.dyn)|*.dyn|");
	CFileDialog	opendlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);

	if (opendlg.DoModal() == IDOK)
	{
		WIN32_FIND_DATA FindFileData;
		HANDLE hFind;
		char szPath[MAX_PATH];
		CString strdynFilePath;
		CString strblkFilePath;
		CString stridxFilePath;
		CString strmodFilePath;		
		CString strFilePath;
		CString strFileName;

		strdynFilePath = opendlg.GetPathName();

		strFileName = strdynFilePath.Right(strdynFilePath.GetLength() - strdynFilePath.ReverseFind('\\') - 1);
		strFileName = strFileName.Left(strFileName.GetLength() - 4);		

		strFilePath = strdynFilePath.Left(strdynFilePath.ReverseFind('\\') + 1);

		strblkFilePath = strFilePath + strFileName + ".blk";
		stridxFilePath = strFilePath + strFileName + ".idx";
		strmodFilePath = strFilePath + strFileName + ".mod";

		memset(szPath, 0 ,sizeof(szPath));
		strcpy(szPath, strblkFilePath);
		hFind = FindFirstFile(szPath, &FindFileData);
		if (hFind == INVALID_HANDLE_VALUE) 
		{
			AfxMessageBox("未找到文件:" + strblkFilePath);
			return;
		}

		strcpy(szPath, stridxFilePath);
		hFind = FindFirstFile(szPath, &FindFileData);
		if (hFind == INVALID_HANDLE_VALUE) 
		{
			AfxMessageBox("未找到文件:" + stridxFilePath);
			return;
		}

		strcpy(szPath, strmodFilePath);
		hFind = FindFirstFile(szPath, &FindFileData);
		if (hFind == INVALID_HANDLE_VALUE) 
		{
			AfxMessageBox("未找到文件:" + strmodFilePath);
			return;
		}

		if(MessageBox("确认要使用新的key文件吗?", "选择key文件", MB_YESNO) == IDYES)
		{
			CopyFile(strdynFilePath, m_szdynFilePath, FALSE);
			CopyFile(strblkFilePath, m_szblkFilePath, FALSE);
			CopyFile(stridxFilePath, m_szidxFilePath, FALSE);
			CopyFile(strmodFilePath, m_szmodFilePath, FALSE);		
			
			m_valEditKeyFilePath = strdynFilePath;
			m_EditKeyFile.ReInit();
		}
		UpdateData(FALSE);
	}	
}

	
/*
函数原型:int	GetFilePath(void);
参数说明:无	
返回值:成功返回0 否则返回-1
功能描述:取得文件的相关路径
*/	
int CBoxDlg::GetFilePath(void)
{
	char szFileName[MAX_PATH];
	CString strTemp;

	memset(m_szFileExePath, 0 , MAX_PATH);
	memset(m_szFileDataPath, 0 , MAX_PATH);
	memset(m_szdynFilePath, 0 , MAX_PATH);
	memset(m_szblkFilePath, 0 , MAX_PATH);
	memset(m_szidxFilePath, 0 , MAX_PATH);
	memset(m_szmodFilePath, 0 , MAX_PATH);
	memset(szFileName, 0 , MAX_PATH);


	//读取程序当目录
	if(ERROR_SUCCESS == GetModuleFileName(NULL, szFileName, MAX_PATH))
	{
		//添加运行记录	
		return -1;//获取文件路径失败
	}
	

	strTemp = szFileName;
	strTemp = strTemp.Left(strTemp.ReverseFind('\\'));
	strcpy(m_szFileExePath, strTemp);

	strTemp = strTemp.Left(strTemp.ReverseFind('\\'));
	strTemp += "\\data";
	strcpy(m_szFileDataPath, strTemp);

	strcpy(m_szdynFilePath, strTemp + "\\keyfile\\28.dyn");
	strcpy(m_szblkFilePath, strTemp + "\\keyfile\\28.blk");
	strcpy(m_szidxFilePath, strTemp + "\\keyfile\\28.idx");
	strcpy(m_szmodFilePath, strTemp + "\\keyfile\\28.mod");

	return 0;
}
/*
函数原型:void EnableCtrl(IN BOOL bEnable);
参数说明:无	
返回值:无
功能描述:设置控件是否可用
*/	
void CBoxDlg::EnableCtrl(IN BOOL bEnable)
{
	m_ctrlParameter.EnableWindow(bEnable);
	m_ctrlEditDecValue.EnableWindow(bEnable);
	m_ctrlButtonSelmeasurfile.EnableWindow(bEnable);
	m_ctrlButtonSelkeyfile.EnableWindow(bEnable);
	m_ctrlButtonSetkey.EnableWindow(bEnable);
	m_ctrlButtonSet.EnableWindow(bEnable);
	m_ctrlEditParameter.EnableWindow(bEnable);
	m_ctrlButtonClearTemp.EnableWindow(bEnable);

	if (bEnable)
	{
		m_ctrlButtonAnalyse.SetWindowText("开始分析");
	}
	else
	{
		m_ctrlButtonAnalyse.SetWindowText("停止分析");
	}
}


void CBoxDlg::OnEditchangeComboParamater() 
{
	// TODO: Add your control notification handler code here
}

void CBoxDlg::OnSelchangeComboParamater() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString strParameterName;
	
	int nSel = m_ctrlParameter.GetCurSel();
	m_ctrlParameter.GetLBText(nSel, strParameterName);

	if (strParameterName != "")
	{
		CString strKeyValue;

		if(m_EditKeyFile.GetKeyValue(strParameterName, strKeyValue) == 0)
		{
			m_valEditParameter = strKeyValue;
		}
	}	
	
	UpdateData(FALSE);
}

void CBoxDlg::OnButtonClearTemp()
{
	CString strPath;
	SECURITY_ATTRIBUTES attribute;

	strPath = m_szFileExePath;
	strPath = strPath.Left(strPath.ReverseFind('\\'));
	strPath += "\\temp";

	//删除目录
	DeleteDirectory(strPath);
	
	//创建目录
	attribute.nLength = sizeof(attribute);
	attribute.lpSecurityDescriptor = NULL;
	attribute.bInheritHandle = FALSE;
	CreateDirectory(strPath, &attribute);
}
//删除目录
BOOL CBoxDlg::DeleteDirectory(CString strPath)
{
	
	CFileFind tempFind;	
	char tempFileFind[MAX_PATH];
	
	sprintf(tempFileFind,"%s\\*.*",strPath);	
	BOOL IsFinded=(BOOL)tempFind.FindFile(tempFileFind);
	
	while(IsFinded)		
	{		
		IsFinded=(BOOL)tempFind.FindNextFile();		
		if(!tempFind.IsDots())			
		{
			char foundFileName[MAX_PATH];			
			strcpy(foundFileName,tempFind.GetFileName().GetBuffer(MAX_PATH));			
			if(tempFind.IsDirectory())				
			{				
				char tempDir[MAX_PATH];				
				sprintf(tempDir,"%s\\%s",strPath,foundFileName);				
				DeleteDirectory(tempDir);				
			}			
			else				
			{				
				char tempFileName[MAX_PATH];				
				sprintf(tempFileName,"%s\\%s",strPath,foundFileName);				
				DeleteFile(tempFileName);				
			}			
		}		
	}
	
	tempFind.Close();

	if(!RemoveDirectory(strPath))		
	{		
		//AfxMessageBox("删除目录失败!");		
		return FALSE;		
	}
	return TRUE;	
}


void CBoxDlg::OnButtonSetkey() 
{
	// TODO: Add your control notification handler code here
	CString strParameterName = "";	
	int nSel = 0;
	UpdateData(TRUE);

	nSel = m_ctrlParameter.GetCurSel();
	if (nSel >= 0) 
	{
		m_ctrlParameter.GetLBText(nSel, strParameterName);
	}

	if (strParameterName != "" && m_valEditParameter != "")
	{
		m_EditKeyFile.SetKeyValue(strParameterName, m_valEditParameter);
		m_EditKeyFile.WriteData();		
	}	
	else
	{
		AfxMessageBox("请输入材料参数初始值!");
	}
}
//添加日志
void CBoxDlg::OnInsertRunLog(WPARAM wParam, LPARAM lParam) 
{
	
	CString strTimeNow;
	CTime timeForPrint;
	CString *strLog = (CString*)wParam;
	CString strtemp = *strLog;
	delete strLog;
	
	//获取时间（时分秒）
	timeForPrint = CTime::GetCurrentTime();//获取当前时间
	strTimeNow.Format("%s", timeForPrint.Format("%H:%M:%S"));//格式化时间

	m_ctrlListLog.InsertItem(0, strTimeNow);
	m_ctrlListLog.SetItemText(0,1,strtemp);	
}
void CBoxDlg::OnAnalyseComplete(WPARAM wParam, LPARAM lParam)
{
	EnableCtrl(TRUE);
}
