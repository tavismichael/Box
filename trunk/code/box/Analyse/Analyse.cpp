/*
 * Copyright 2010 
 * All rights reserved.
 * 
 * Name:Analyse.cpp
 * Author: ���˸�   
 * Date: 05/29/2010
 *  Remarks: 
 * Revision history:                                 
*/

#include "../StdAfx.h"
#include "Analyse.h"
#include <comdef.h>
#include <math.h>
#include "../Log/Log.h"
#include <tlhelp32.h> 

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CAnalyse ccase;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
/*
����ԭ��:CAnalyse(void);
����˵��:��
����ֵ:��
��������:���캯��
*/
CAnalyse::CAnalyse(void)
{

}

/*
����ԭ��:virtual ~CAnalyse(void);
����˵��:��
����ֵ:��
��������:��������
*/
CAnalyse::~CAnalyse(void)
{

}

/*
����ԭ��:static UINT AnalyeKeyFile(LPVOID pParam);
����˵��:
	pParam		��Ϣ����
����ֵ:��
��������:����key�ļ��Ľӿں���
*/	
UINT CAnalyse::AnalyeKeyFile(IN LPVOID pParam)
//UINT CAnalyse::AnalyeKeyFile(HWND hWnd, IN CString strMeasurPath, IN double fDecValue)
{
	CoInitialize(NULL);	

	Type_ThreadMSG *msg= (Type_ThreadMSG*)pParam;
	int nLog;

	//��ȡ����
	ccase.m_SystemSet.Init();	
	ccase.m_SystemSet.GetSystem(ccase.m_Systems);

	//��¼���ھ��
	ccase.m_hWnd = msg->hWnd;
	//�Ż�Ŀ¼
	ccase.m_fDecValue = msg->fDecValue;
	//��ȡ��������
	nLog = ccase.ReadMeasureData(msg->strMeasurPath);

	//
	if (nLog == 0) 
	{
		nLog = ccase.Configure();
	}
	else
	{
		//��ȡ�������ݴ���
	}

	if (nLog == 0)
	{
		int popsize  = 100;
		int ngen     = 200;
		float pmut   = 0.10;
		float pcross = 0.9;
		unsigned int i = 0;
		unsigned int n = 0;
		unsigned int seed = 100;

		GARandomSeed(seed);

		float *target = new float;
		*target = ccase.m_fDecValue;
	
		GABin2DecPhenotype map;

		for(i=0; i<ccase.m_Systems.size(); i++)
		{
			if (ccase.m_Systems[i].bIsReverse == 1)
			{
				n++;
			}						
		}

		for(i=0; i<ccase.m_Systems.size(); i++)
		{
			if (ccase.m_Systems[i].bIsReverse == 1)
			{				
				map.add(8, atof(ccase.m_Systems[i].dDownStep), atof(ccase.m_Systems[i].dUpStep));	
				ccase.m_SystemOptName.push_back(ccase.m_Systems[i].szShortCaption);
			}						
		}

		GABin2DecGenome genome(map, Objective, (void *)target);
		GASimpleGA ga(genome);
		ga.populationSize(popsize);
		ga.nGenerations(ngen);
		ga.pMutation(pmut);
		ga.pCrossover(pcross);
		ga.scoreFilename("bog.dat");
		ga.flushFrequency(50);// dump scores to disk every 50th generation
		ga.evolve(seed);	

		genome.initialize();		
		genome = ga.statistics().bestIndividual();

		CString strLog = "���Ž�:";
		CString strTemp;
		for(i=0; i<map.nPhenotypes(); i++)
		{
			CString strKeyName = ccase.m_SystemOptName[i];
			
			strTemp.Format("(%s:%0.6f)", strKeyName, genome.phenotype(i));
			strLog += strTemp;
		}
		CLog::AddRunRecord(strLog);	

		// Clean up by freeing the memory we allocated.
		delete target;
	}
	else
	{
		//���ù���Ŀ¼����
	}


	//������������
	::SendMessage(msg->hWnd, MSG_COMPLETE, 0, 0);
	delete msg;
	return 0;	
} 

// For this objective function we try to match the values in the array of float
// that is passed to us as userData.  If the values in the genome map to 
// values that are close, we return a better score.  We are limited to positive
// values for the objective value (because we're using linear scaling - the
// default scaling method for SimpleGA), so we take the reciprocal of the 
// absolute value of the difference between the value from the phenotype and 
// the value in the sequence.
float CAnalyse::Objective(GAGenome& g)
{
	GABin2DecGenome & genome = (GABin2DecGenome &)g;
	float *sequence = (float *)g.userData();
	float value = OPTI_DEFALTVAL;
	static int nStop = 0;

	//���Ĳ���		
	ASSERT(genome.nPhenotypes() == ccase.m_SystemOptName.size());
	if (nStop == 0)
	{
		CString strlog;
		CString strKeyWords;

		for(int i=0; i<genome.nPhenotypes(); i++)
		{
			CString strtemp;
			float fKeyValue;
			CString strKeyValue = "";
			CString strKeyName = "";

			strKeyName = ccase.m_SystemOptName[i];
			fKeyValue = genome.phenotype(i);
			
			if (strKeyName == "E")//����ģ��
			{
				strKeyValue.Format("%0.2e", fKeyValue);//2.070E+05
				strKeyValue.Replace("e", "E");
				strtemp = strKeyValue;
				strKeyValue = strtemp.Left(strtemp.GetLength() - 3);
				strKeyValue += strtemp.Right(2);
			}
			else if (strKeyName == "PR")//���ɱ�
			{
				strKeyValue.Format("%0.2f", fKeyValue);//0.28								
			}
			else if (strKeyName == "P1")//Kֵ
			{
				strKeyValue.Format("%0.1f", fKeyValue);//495.1								
			}
			else if (strKeyName == "P2")//nֵ
			{
				strKeyValue.Format("%0.2f", fKeyValue);//0.23								
			}
			
			ccase.m_EditKeyFile.SetKeyValue(strKeyName, strKeyValue);

			TRACE("KEYName:%s, KeyValue:%f,KeyValue:%s\n", strKeyName, fKeyValue, strKeyValue);			
			strtemp.Format("(%s:%s)", strKeyName, strKeyValue);
			strKeyWords += strtemp;
		}

		ccase.m_EditKeyFile.WriteData();
		
		//ִ��
		int nLog = ccase.ExeCommand();
			
		//�������
		if (nLog == 0)
		{
			value = ccase.AnalyeDynain();
		}	
		
		if (value < OPTI_DEFALTVAL)
		{
			strlog.Format("������:%0.6f,", value);			
			strlog += strKeyWords;	
			CLog::AddRunRecord(strlog);	
		}
		
		if (value < *sequence)
		{
			//ֹͣ����
			nStop = 1;

			//����淢����Ϣ
			CString *strRunRecord = new CString;
			*strRunRecord = strlog;
			::SendMessage( ccase.m_hWnd, MSG_INSERTLOG, (long)strRunRecord, 0);
		}

	}
	TRACE("%0.5f\n", value);  
	value = 1.0 / value;

	return value;
}


/*
����ԭ��:UINT Configure(void)
����˵��:��
����ֵ:
	�ɹ�����0, ���߷����쳣��
��������:��KEY�ļ��ͷ�������������ʱĿ¼
*/
UINT CAnalyse::Configure(void)
{
	char szFileName[MAX_PATH];//�ļ�·��
	CString strDataPath;
	CString strDataTempPath;
	CString strAnalyseExePath;
	CString strTimeNow;
	CTime timeForPrint;
	
	//��ȡ������ʼʱ�䣨ʱ���룩
	timeForPrint = CTime::GetCurrentTime();//��ȡ��ǰʱ��
	strTimeNow.Format("%s", timeForPrint.Format("%H-%M-%S"));//��ʽ��ʱ��
	
	//��ȡ����Ŀ¼
	if(ERROR_SUCCESS == GetModuleFileName(NULL, szFileName, MAX_PATH))
	{
		//������м�¼	
		return -1;//��ȡ�ļ�·��ʧ��
	}
	strDataPath = szFileName;
	strDataPath = strDataPath.Left(strDataPath.ReverseFind('\\'));
	strDataPath = strDataPath.Left(strDataPath.ReverseFind('\\'));
	strAnalyseExePath = strDataPath +"\\lib\\";	
	strDataTempPath = strDataPath + "\\temp\\" + strTimeNow;
	strDataPath += "\\data\\";
	
	SECURITY_ATTRIBUTES attribute;
	attribute.nLength = sizeof(attribute);
	attribute.lpSecurityDescriptor = NULL;
	attribute.bInheritHandle = FALSE;
	if(CreateDirectory(strDataTempPath, &attribute) != 0)
	{
		//��tempĿ¼����һ��Ŀ¼����KEY�ļ��ͷ����������뵽Ŀ¼��
		CString strSrcFile;
		CString strDecFile;
		vector<CString>	vstrKeyNames;

		//����*.dyn
		strSrcFile = strDataPath + "keyfile\\28.dyn";
		strDecFile = strDataTempPath + "\\28.dyn";
		CopyFile(strSrcFile, strDecFile, FALSE);

		//����*.blk
		strSrcFile = strDataPath + "keyfile\\28.blk";
		strDecFile = strDataTempPath + "\\28.blk";
		CopyFile(strSrcFile, strDecFile, FALSE);
		
		//����*.idx
		strSrcFile = strDataPath + "keyfile\\28.idx";
		strDecFile = strDataTempPath + "\\28.idx";
		CopyFile(strSrcFile, strDecFile, FALSE);
		
		//����*.mod
		strSrcFile = strDataPath + "keyfile\\28.mod";
		strDecFile = strDataTempPath + "\\28.mod";
		CopyFile(strSrcFile, strDecFile, FALSE);

		//��������
		strSrcFile = strAnalyseExePath + "lsdyna.exe";
		strDecFile = strDataTempPath + "\\lsdyna.exe";
		CopyFile(strSrcFile, strDecFile, FALSE);

		m_strAnalyseExePath = strDataTempPath;
		m_strKeyfileName = "28.dyn";
		m_EditKeyFile.Init(m_strAnalyseExePath + "\\" + m_strKeyfileName);

		//��ȡkey�ĳ�ֵ
		m_EditKeyFile.GetKeyValues(m_vstrKeyNames, vstrKeyNames);

		for(int i=0; i<vstrKeyNames.size(); i++)
		{
			float fvalue = atof(vstrKeyNames[i]);

			m_vfKeyValues.push_back(fvalue);
		}	
	}
	else
	{
		return -1;
	}
	
	return 0;
}
	
/*
����ԭ��:UINT ExeCommand(void);
����˵��:��
����ֵ:
	�ɹ�����0, ���߷����쳣��
��������:ִ�з�����
*/
UINT CAnalyse::ExeCommand(void)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	char  szExeName[1024];
	char  szExePath[1024];
	char  szCommandLine[1024];
	CString strtemp;

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	char szAnalysePath[MAX_PATH];

	//ɾ���ϴ�ִ�еĽ��	
	strtemp = m_strAnalyseExePath + "\\28.dynain";
	strcpy(szAnalysePath, strtemp);
	hFind = FindFirstFile(szAnalysePath, &FindFileData);
	if (hFind != INVALID_HANDLE_VALUE) 
	{
		//ɾ���ļ�
		DeleteFile(szAnalysePath);	
	}

	//ִ�з�����
	memset(&si, 0, sizeof(STARTUPINFO));
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_SHOW;	

	memset(szExeName, 0, sizeof(szExeName));
	strcpy(szExeName, "lsdyna.exe");

	memset(szExePath, 0, sizeof(szExePath));
	strcpy(szExePath, m_strAnalyseExePath); 

	memset(szCommandLine, 0, sizeof(szCommandLine));
	strtemp.Format("%s i=%s", "lsdyna.exe", m_strKeyfileName);
	strcpy(szCommandLine, strtemp);

	if(SetCurrentDirectory(szExePath))
	{
		CreateProcess(NULL, szCommandLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	}

	//�������Ƿ����
	while (1)
	{
		BOOL bIsFind = FALSE;
		PROCESSENTRY32 pe32;
		pe32.dwSize = sizeof(pe32); 
		HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if(hProcessSnap == INVALID_HANDLE_VALUE)
		{
			printf(" CreateToolhelp32Snapshot����ʧ�ܣ� \n");
			return -1;
		}
		BOOL bMore = ::Process32First(hProcessSnap, &pe32);
		while(bMore)
		{

			if(pe32.th32ProcessID == pi.dwProcessId)
			{
				bIsFind = TRUE;
				break;
			}

			bMore = ::Process32Next(hProcessSnap, &pe32);
		}

		::CloseHandle(hProcessSnap);

		if (bIsFind == FALSE)
		{
			break;
		}		
	}

	return 0;
}

/*
����ԭ��:UINT Configure(void)
����˵��:
	strMeasureDataPath	�ļ�·��
����ֵ:
	�ɹ�����0, ���߷����쳣��
��������:��ȡ��������
*/
UINT CAnalyse::ReadMeasureData(IN CString strMeasureDataPath)
{
	DWORD dwRet = 0;//����ֵ
	//Excel��д�ò���
	_Application  ExcelApp;
	Workbooks wbsMyBooks;
	_Workbook wbMyBook;
	Worksheets wssMysheets;
	_Worksheet wsMysheet;
	Range rgMyRge;
	CString strSheet;//ҳ��
	char szFileName[MAX_PATH];//�����ļ�·��	
	COleException pError; 

	m_vMeasures.clear();
	
	strcpy(szFileName, strMeasureDataPath);//�������յ��ļ�·��
	
	//�ж�����Excel����������
	while (::FindWindow("XLMAIN", NULL) != NULL)
	{
		if (MessageBox(NULL, "ϵͳ��⵽��Excel�����������С�\n��رպ�����������!",
			"����LEU", MB_RETRYCANCEL | MB_ICONINFORMATION) == IDCANCEL)
		{
			//������м�¼
			return -1;//��Excel����ʧ��
		}
	}
	
	//Excel����
	if (!ExcelApp.CreateDispatch("Excel.Application", &pError))
	{
		char szError[1024];
		CString strmsg;

		pError.GetErrorMessage(szError, 1024);
		strmsg.Format("����Excel����ʧ��:%s", szError);
		AfxMessageBox(strmsg);
		return -1;
	}	
	
	wbsMyBooks.AttachDispatch(ExcelApp.GetWorkbooks(), true);	
	wbMyBook.AttachDispatch(wbsMyBooks.Add(_variant_t(szFileName)));
	wssMysheets.AttachDispatch(wbMyBook.GetWorksheets(), true);//�õ�Worksheets
	
	//��ȡӦ���������Ӧ����Ӧ����ID��ϵ���ձ�
	strSheet = "Sheet1";//��ǰҳ��
	wsMysheet.AttachDispatch(wssMysheets.GetItem(_variant_t(strSheet)),true);//�õ�sheet
	rgMyRge.AttachDispatch(wsMysheet.GetCells(), true);//�õ�ȫ��Cells����ʱ,rgMyRge��cells�ļ���
	GetMeasureDataFromExcel(&rgMyRge);//
	
	//�ͷ���Դ	
	rgMyRge.ReleaseDispatch();
	wsMysheet.ReleaseDispatch();
	wssMysheets.ReleaseDispatch();
	wbMyBook.ReleaseDispatch();
	wbsMyBooks.ReleaseDispatch();
	ExcelApp.ReleaseDispatch();	
	
	//ɱExcel����
	HWND hwndExcel;
	while ((hwndExcel = ::FindWindow("XLMAIN", NULL)) != NULL)
	{
		::SendMessage(hwndExcel, WM_CLOSE, 0, 0);
	}	

	return 0;
}

/*
����ԭ��:void GetMeasureDataFromExcel(Range IN *prgMyRge);
����˵��:
prgMyRge				Excel���е�Range�࣬��һϵ�е�Ԫ�����ϡ�ÿ��Sheet��Ӧ��һ��Range
nSheetIndex				������
ʹ�õ���ȫ�ֱ�����
��������:�������ж�ȡ��������
����ֵ:��
*/
void  CAnalyse::GetMeasureDataFromExcel(Range IN *prgMyRge)
{
	long lColumn;//�к�
	long lRow;//�к�
	CString strInfo;//��ȡ�����õ��Ļ�����
	ASSERT(prgMyRge);//�ж�ָ��ǿգ�������ָ��

	//���ж�
	lRow = 2;
	while(1)
	{
		Type_NodeThick stuMeasure;
		int nFrameIndex = 0;
		int nRealBYTENum = 0;
		CString strSql;
		CString strVBShortName;
		
		//�ڵ���	
		lColumn = 1;		//�кų�ʼ��
		strInfo = "";//��ȡ�����õ��Ļ�������ʼ��
		GetStringFromExcel(prgMyRge, lRow, lColumn, strInfo);//��ָ���к��кŶ�Ӧ�ĵ�Ԫ

		//δ��ȡ���ڵ���ֹͣ��ѯ
		if (strInfo == "")
		{
			break;
		}
		stuMeasure.nID = atol(strInfo);

		//���ֵ	
		lColumn = 2;		//�кų�ʼ��
		strInfo = "";//��ȡ�����õ��Ļ�������ʼ��
		GetStringFromExcel(prgMyRge, lRow, lColumn, strInfo);//��ָ���к��кŶ�Ӧ�ĵ�Ԫ		
		stuMeasure.dthick = atof(strInfo);

		//X����	
		lColumn = 3;		//�кų�ʼ��
		strInfo = "";//��ȡ�����õ��Ļ�������ʼ��
		GetStringFromExcel(prgMyRge, lRow, lColumn, strInfo);//��ָ���к��кŶ�Ӧ�ĵ�Ԫ		
		stuMeasure.dPosX = atof(strInfo);

		//Y����	
		lColumn = 4;		//�кų�ʼ��
		strInfo = "";//��ȡ�����õ��Ļ�������ʼ��
		GetStringFromExcel(prgMyRge, lRow, lColumn, strInfo);//��ָ���к��кŶ�Ӧ�ĵ�Ԫ		
		stuMeasure.dPosY = atof(strInfo);

		//Z����	
		lColumn = 5;		//�кų�ʼ��
		strInfo = "";//��ȡ�����õ��Ļ�������ʼ��
		GetStringFromExcel(prgMyRge, lRow, lColumn, strInfo);//��ָ���к��кŶ�Ӧ�ĵ�Ԫ		
		stuMeasure.dPosZ = atof(strInfo);

		m_vMeasures.push_back(stuMeasure);
		lRow++;//�к�
	}
}

/*
����ԭ��:void GetStringFromExcel(Range IN *prgMyRge, long IN lRow, long IN lCol, CString OUT &strItem)
����˵��:
prgMyRge							Excel��Ϣ��
lRow								����Ϣ
lCol								����Ϣ
strItem								��nRow�е�nCol�е�ֵ
ʹ�õ���ȫ�ֱ���:
��������:����nRow�е�nCol�е�ֵ��ȡ�����������س�ȥ��֮���Է��س�ȥ
����ֵ:��
*/
void  CAnalyse::GetStringFromExcel(Range IN *prgMyRge, long IN lRow, long IN lCol, CString OUT &strItem)
{
	_bstr_t bstrInfo;//ת���ַ�����
	char *pszBSTRToString;//��BSTRת����Stringʱ�õ���ָ�룬�����ͷ��ڴ棬�����ʹ�ô�ָ�����Ϊʹ��ConvertBSTRToString�����ڴ�й¶
	
	ASSERT(prgMyRge);//��ȫ����
	
	bstrInfo = (_bstr_t)prgMyRge->GetItem(_variant_t(lRow),_variant_t(lCol));//��ָ���к��кŶ�Ӧ�ĵ�Ԫ��
	pszBSTRToString = bstrInfo;//_com_util::ConvertBSTRToString((_bstr_t)bstrInfo);//����Ԫ�������ת��Ϊchar*�����ڴ���
	strItem = pszBSTRToString;//��char*���CString���ڴ���
}

/*
����ԭ��:double AnalyeDynain(void);
����˵��:��
��������:��dynain�ļ��ж�ȡ�ڵ�����ͺ�ȣ�������Ŀ�꺯�����з���
����ֵ:��õ��Ż�����ֵ
*/
double CAnalyse::AnalyeDynain(void)
{
	double fvalue = OPTI_DEFALTVAL;//Ŀ�꺯��ֵ
	//��ȡ����
	UINT nlog = ReadSimulateDataFromDynain();

	//��ģ��ֵ�в��������ֵ��ӽ��ĵ�
	if (nlog == 0) 
	{
		SearchNearPoint();
	}
	
	//�Ż���˾
	if (nlog == 0)
	{
		fvalue = OptimizeFunction();	
	}

	return fvalue;
}

/*
����ԭ��:UINT ReadSimulateDataFromDynain(void);
����˵��:��
��������:��.Dynain�ļ��ж�ȡģ��ڵ�����ͺ��
����ֵ:�ɹ�����0 ���򷵻�-1
*/
UINT CAnalyse::ReadSimulateDataFromDynain(void)
{
	CStdioFile fDynainFile;
	int nLineCouter = 0;
	CString strFilePath;
	CString strLineValue;//ÿһ�е�ֵ
	map<long, long> mSearch;

	m_vSimulates.clear();
	strFilePath = m_strAnalyseExePath + "\\28.dynain";
	
	if(fDynainFile.Open(strFilePath, CFile::modeRead) == FALSE)//���ļ�	
	{
		return -1;
	}

	while(1)
	{
		//��ȡ�ļ�
		fDynainFile.ReadString(strLineValue);

		//��ȡ�ڵ�����
		if (strlen(strLineValue) > 0 && strcmp(strLineValue, "*NODE") == 0)
		{
			while(1)
			{
				Type_NodeThick stuNode;
				CString strtemp;
				strLineValue = "";
				fDynainFile.ReadString(strLineValue);

				//��ȡ�ڵ���
				strtemp = strLineValue.Left(8);
				stuNode.nID = atol(strtemp);
				if (stuNode.nID <= 0)
				{
					//���ҽڵ��������
					break;
				}

				//��ȡx����
				strtemp = strLineValue.Right(strLineValue.GetLength() - 8);
				strtemp = strtemp.Left(16);
				stuNode.dPosX = atof(strtemp);

				//��ȡy����
				strtemp = strLineValue.Right(strLineValue.GetLength() - 24);
				strtemp = strtemp.Left(16);
				stuNode.dPosY = atof(strtemp);

				//��ȡz����
				strtemp = strLineValue.Right(strLineValue.GetLength() - 40);
				strtemp = strtemp.Left(16);
				stuNode.dPosZ = atof(strtemp);

				m_vSimulates.push_back(stuNode);
				mSearch[stuNode.nID] = m_vSimulates.size();
			}		
		}

		//��ȡ�ڵ���
		if (strlen(strLineValue) > 0 && strcmp(strLineValue, "*ELEMENT_SHELL_THICKNESS") == 0)
		{
			//
			while(1)
			{
				CString strtemp;
				long ldID[4];
				int i;
				
				strLineValue = "";
				fDynainFile.ReadString(strLineValue);

				if (strcmp(strLineValue, "*CONSTRAINED_ADAPTIVITY") == 0)
				{
					break;
				}

				//��ȡ�ڵ���
				for(i=0; i<4; i++)
				{
					strtemp = strLineValue.Right(strLineValue.GetLength() - 8*(2+i));
					strtemp = strtemp.Left(8);
					ldID[i] = atol(strtemp);
				}

				//��ȡ�ڵ���
				fDynainFile.ReadString(strLineValue);
				for(i=0; i<4; i++)
				{
					long ldIndex;

					strtemp = strLineValue.Right(strLineValue.GetLength() - 16*i);
					strtemp = strtemp.Left(16);

					ldIndex = mSearch[ldID[i]];
					ASSERT(ldIndex > 0);

					m_vSimulates[ldIndex - 1].dthick = atof(strtemp);
				}
			}
			
			break;
		}
	
		nLineCouter++;
		if (nLineCouter > 600)
		{
			//δ�ҵ�ֹͣ��ѯ
			break;
		}
	}

	//�ر��ļ�
	fDynainFile.Close();
	
	return 0;
}

/*
����ԭ��:void SearchNearPoint(void);
����˵��:��
��������:��ģ��ֵ�в��������ֵ��ӽ��ĵ�
����ֵ:��
*/
void CAnalyse::SearchNearPoint(void)
{
	m_vNearDatas.clear();

	for(int i=0; i<m_vMeasures.size(); i++)
	{
		Type_NodeThick stuMeasure = m_vMeasures[i];
		double fMinDistance = 10000000.0f;
		long ldMinIndex = 0;
		double fDistance = 0.0f;

		for(int j=0; j<m_vSimulates.size(); j++)
		{
			Type_NodeThick stuSimulate = m_vSimulates[j];

			fDistance = sqrt((stuMeasure.dPosZ - stuSimulate.dPosZ) * (stuMeasure.dPosZ - stuSimulate.dPosZ) 
				+ (stuMeasure.dPosY - stuSimulate.dPosY) * (stuMeasure.dPosY - stuSimulate.dPosY)
				+ (stuMeasure.dPosX - stuSimulate.dPosX) * (stuMeasure.dPosX - stuSimulate.dPosX));
			
			if(fDistance < fMinDistance)
			{
				fMinDistance = fDistance;
				ldMinIndex = j;
			}
		}

		m_vNearDatas.push_back(m_vSimulates[ldMinIndex]);		
	}	
}

/*
����ԭ��:double OptimizeFunction(void);
����˵��:��
��������:�Ż�Ŀ�꺯��
����ֵ:�����Ż�����ֵ
*/
double CAnalyse::OptimizeFunction(void)
{
	double fSum = 0.0f;
	
	ASSERT(m_vMeasures.size() == m_vNearDatas.size());

	//�Ż���ʽ
	for(int i=0; i<m_vMeasures.size(); i++)
	{
		double fThick = 0.0f;

		fThick = double(m_vNearDatas[i].dthick - m_vMeasures[i].dthick);
		fThick /= m_vMeasures[i].dthick;
		fThick = fThick * fThick;

		fSum += fThick;
	}

	return fSum;
}

