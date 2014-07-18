/*
 * Copyright 2010 
 * All rights reserved.
 * 
 * Name:Analyse.cpp
 * Author: 刘克富   
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
函数原型:CAnalyse(void);
参数说明:无
返回值:无
功能描述:构造函数
*/
CAnalyse::CAnalyse(void)
{

}

/*
函数原型:virtual ~CAnalyse(void);
参数说明:无
返回值:无
功能描述:析构函数
*/
CAnalyse::~CAnalyse(void)
{

}

/*
函数原型:static UINT AnalyeKeyFile(LPVOID pParam);
参数说明:
	pParam		消息参数
返回值:无
功能描述:分析key文件的接口函数
*/	
UINT CAnalyse::AnalyeKeyFile(IN LPVOID pParam)
//UINT CAnalyse::AnalyeKeyFile(HWND hWnd, IN CString strMeasurPath, IN double fDecValue)
{
	CoInitialize(NULL);	

	Type_ThreadMSG *msg= (Type_ThreadMSG*)pParam;
	int nLog;

	//获取参数
	ccase.m_SystemSet.Init();	
	ccase.m_SystemSet.GetSystem(ccase.m_Systems);

	//记录窗口句柄
	ccase.m_hWnd = msg->hWnd;
	//优化目录
	ccase.m_fDecValue = msg->fDecValue;
	//读取测量数据
	nLog = ccase.ReadMeasureData(msg->strMeasurPath);

	//
	if (nLog == 0) 
	{
		nLog = ccase.Configure();
	}
	else
	{
		//读取测量数据错误
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

		CString strLog = "最优解:";
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
		//配置工作目录错误
	}


	//正常结束分析
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

	//更改参数		
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
			
			if (strKeyName == "E")//弹性模量
			{
				strKeyValue.Format("%0.2e", fKeyValue);//2.070E+05
				strKeyValue.Replace("e", "E");
				strtemp = strKeyValue;
				strKeyValue = strtemp.Left(strtemp.GetLength() - 3);
				strKeyValue += strtemp.Right(2);
			}
			else if (strKeyName == "PR")//泊松比
			{
				strKeyValue.Format("%0.2f", fKeyValue);//0.28								
			}
			else if (strKeyName == "P1")//K值
			{
				strKeyValue.Format("%0.1f", fKeyValue);//495.1								
			}
			else if (strKeyName == "P2")//n值
			{
				strKeyValue.Format("%0.2f", fKeyValue);//0.23								
			}
			
			ccase.m_EditKeyFile.SetKeyValue(strKeyName, strKeyValue);

			TRACE("KEYName:%s, KeyValue:%f,KeyValue:%s\n", strKeyName, fKeyValue, strKeyValue);			
			strtemp.Format("(%s:%s)", strKeyName, strKeyValue);
			strKeyWords += strtemp;
		}

		ccase.m_EditKeyFile.WriteData();
		
		//执行
		int nLog = ccase.ExeCommand();
			
		//结果分析
		if (nLog == 0)
		{
			value = ccase.AnalyeDynain();
		}	
		
		if (value < OPTI_DEFALTVAL)
		{
			strlog.Format("反求结果:%0.6f,", value);			
			strlog += strKeyWords;	
			CLog::AddRunRecord(strlog);	
		}
		
		if (value < *sequence)
		{
			//停止反求
			nStop = 1;

			//向界面发送消息
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
函数原型:UINT Configure(void)
参数说明:无
返回值:
	成功返回0, 否者返回异常码
功能描述:将KEY文件和分析器拷贝到临时目录
*/
UINT CAnalyse::Configure(void)
{
	char szFileName[MAX_PATH];//文件路径
	CString strDataPath;
	CString strDataTempPath;
	CString strAnalyseExePath;
	CString strTimeNow;
	CTime timeForPrint;
	
	//获取周期起始时间（时分秒）
	timeForPrint = CTime::GetCurrentTime();//获取当前时间
	strTimeNow.Format("%s", timeForPrint.Format("%H-%M-%S"));//格式化时间
	
	//读取程序当目录
	if(ERROR_SUCCESS == GetModuleFileName(NULL, szFileName, MAX_PATH))
	{
		//添加运行记录	
		return -1;//获取文件路径失败
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
		//在temp目录生产一个目录，将KEY文件和分析器程序拷入到目录下
		CString strSrcFile;
		CString strDecFile;
		vector<CString>	vstrKeyNames;

		//拷贝*.dyn
		strSrcFile = strDataPath + "keyfile\\28.dyn";
		strDecFile = strDataTempPath + "\\28.dyn";
		CopyFile(strSrcFile, strDecFile, FALSE);

		//拷贝*.blk
		strSrcFile = strDataPath + "keyfile\\28.blk";
		strDecFile = strDataTempPath + "\\28.blk";
		CopyFile(strSrcFile, strDecFile, FALSE);
		
		//拷贝*.idx
		strSrcFile = strDataPath + "keyfile\\28.idx";
		strDecFile = strDataTempPath + "\\28.idx";
		CopyFile(strSrcFile, strDecFile, FALSE);
		
		//拷贝*.mod
		strSrcFile = strDataPath + "keyfile\\28.mod";
		strDecFile = strDataTempPath + "\\28.mod";
		CopyFile(strSrcFile, strDecFile, FALSE);

		//拷分析器
		strSrcFile = strAnalyseExePath + "lsdyna.exe";
		strDecFile = strDataTempPath + "\\lsdyna.exe";
		CopyFile(strSrcFile, strDecFile, FALSE);

		m_strAnalyseExePath = strDataTempPath;
		m_strKeyfileName = "28.dyn";
		m_EditKeyFile.Init(m_strAnalyseExePath + "\\" + m_strKeyfileName);

		//读取key的初值
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
函数原型:UINT ExeCommand(void);
参数说明:无
返回值:
	成功返回0, 否者返回异常码
功能描述:执行分析器
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

	//删除上次执行的结果	
	strtemp = m_strAnalyseExePath + "\\28.dynain";
	strcpy(szAnalysePath, strtemp);
	hFind = FindFirstFile(szAnalysePath, &FindFileData);
	if (hFind != INVALID_HANDLE_VALUE) 
	{
		//删除文件
		DeleteFile(szAnalysePath);	
	}

	//执行分析器
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

	//检查进程是否结束
	while (1)
	{
		BOOL bIsFind = FALSE;
		PROCESSENTRY32 pe32;
		pe32.dwSize = sizeof(pe32); 
		HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if(hProcessSnap == INVALID_HANDLE_VALUE)
		{
			printf(" CreateToolhelp32Snapshot调用失败！ \n");
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
函数原型:UINT Configure(void)
参数说明:
	strMeasureDataPath	文件路径
返回值:
	成功返回0, 否者返回异常码
功能描述:读取测量数据
*/
UINT CAnalyse::ReadMeasureData(IN CString strMeasureDataPath)
{
	DWORD dwRet = 0;//返回值
	//Excel读写用参数
	_Application  ExcelApp;
	Workbooks wbsMyBooks;
	_Workbook wbMyBook;
	Worksheets wssMysheets;
	_Worksheet wsMysheet;
	Range rgMyRge;
	CString strSheet;//页名
	char szFileName[MAX_PATH];//配置文件路径	
	COleException pError; 

	m_vMeasures.clear();
	
	strcpy(szFileName, strMeasureDataPath);//生成最终的文件路径
	
	//判断有无Excel进程在运行
	while (::FindWindow("XLMAIN", NULL) != NULL)
	{
		if (MessageBox(NULL, "系统检测到有Excel程序正在运行。\n请关闭后再运行启动!",
			"仿真LEU", MB_RETRYCANCEL | MB_ICONINFORMATION) == IDCANCEL)
		{
			//添加运行记录
			return -1;//打开Excel进程失败
		}
	}
	
	//Excel处理
	if (!ExcelApp.CreateDispatch("Excel.Application", &pError))
	{
		char szError[1024];
		CString strmsg;

		pError.GetErrorMessage(szError, 1024);
		strmsg.Format("创建Excel服务失败:%s", szError);
		AfxMessageBox(strmsg);
		return -1;
	}	
	
	wbsMyBooks.AttachDispatch(ExcelApp.GetWorkbooks(), true);	
	wbMyBook.AttachDispatch(wbsMyBooks.Add(_variant_t(szFileName)));
	wssMysheets.AttachDispatch(wbMyBook.GetWorksheets(), true);//得到Worksheets
	
	//读取应答器简称与应答器应答器ID关系对照表
	strSheet = "Sheet1";//当前页名
	wsMysheet.AttachDispatch(wssMysheets.GetItem(_variant_t(strSheet)),true);//得到sheet
	rgMyRge.AttachDispatch(wsMysheet.GetCells(), true);//得到全部Cells，此时,rgMyRge是cells的集合
	GetMeasureDataFromExcel(&rgMyRge);//
	
	//释放资源	
	rgMyRge.ReleaseDispatch();
	wsMysheet.ReleaseDispatch();
	wssMysheets.ReleaseDispatch();
	wbMyBook.ReleaseDispatch();
	wbsMyBooks.ReleaseDispatch();
	ExcelApp.ReleaseDispatch();	
	
	//杀Excel进程
	HWND hwndExcel;
	while ((hwndExcel = ::FindWindow("XLMAIN", NULL)) != NULL)
	{
		::SendMessage(hwndExcel, WM_CLOSE, 0, 0);
	}	

	return 0;
}

/*
函数原型:void GetMeasureDataFromExcel(Range IN *prgMyRge);
参数说明:
prgMyRge				Excel类中的Range类，是一系列单元格的组合。每个Sheet对应着一个Range
nSheetIndex				表格序号
使用到的全局变量：
功能描述:工作簿中读取测量数据
返回值:无
*/
void  CAnalyse::GetMeasureDataFromExcel(Range IN *prgMyRge)
{
	long lColumn;//列号
	long lRow;//行号
	CString strInfo;//读取数据用到的缓冲区
	ASSERT(prgMyRge);//判断指针非空，防护空指针

	//逐行读
	lRow = 2;
	while(1)
	{
		Type_NodeThick stuMeasure;
		int nFrameIndex = 0;
		int nRealBYTENum = 0;
		CString strSql;
		CString strVBShortName;
		
		//节点编号	
		lColumn = 1;		//列号初始化
		strInfo = "";//读取数据用到的缓冲区初始化
		GetStringFromExcel(prgMyRge, lRow, lColumn, strInfo);//读指定行号列号对应的单元

		//未读取到节点编号停止查询
		if (strInfo == "")
		{
			break;
		}
		stuMeasure.nID = atol(strInfo);

		//厚度值	
		lColumn = 2;		//列号初始化
		strInfo = "";//读取数据用到的缓冲区初始化
		GetStringFromExcel(prgMyRge, lRow, lColumn, strInfo);//读指定行号列号对应的单元		
		stuMeasure.dthick = atof(strInfo);

		//X坐标	
		lColumn = 3;		//列号初始化
		strInfo = "";//读取数据用到的缓冲区初始化
		GetStringFromExcel(prgMyRge, lRow, lColumn, strInfo);//读指定行号列号对应的单元		
		stuMeasure.dPosX = atof(strInfo);

		//Y坐标	
		lColumn = 4;		//列号初始化
		strInfo = "";//读取数据用到的缓冲区初始化
		GetStringFromExcel(prgMyRge, lRow, lColumn, strInfo);//读指定行号列号对应的单元		
		stuMeasure.dPosY = atof(strInfo);

		//Z坐标	
		lColumn = 5;		//列号初始化
		strInfo = "";//读取数据用到的缓冲区初始化
		GetStringFromExcel(prgMyRge, lRow, lColumn, strInfo);//读指定行号列号对应的单元		
		stuMeasure.dPosZ = atof(strInfo);

		m_vMeasures.push_back(stuMeasure);
		lRow++;//行号
	}
}

/*
函数原型:void GetStringFromExcel(Range IN *prgMyRge, long IN lRow, long IN lCol, CString OUT &strItem)
参数说明:
prgMyRge							Excel信息类
lRow								行信息
lCol								列信息
strItem								第nRow行第nCol列的值
使用到的全局变量:
功能描述:将第nRow行第nCol列的值读取出来，并返回出去。之所以返回出去
返回值:无
*/
void  CAnalyse::GetStringFromExcel(Range IN *prgMyRge, long IN lRow, long IN lCol, CString OUT &strItem)
{
	_bstr_t bstrInfo;//转换字符串用
	char *pszBSTRToString;//从BSTR转换成String时用到的指针，用于释放内存，如果不使用此指针会因为使用ConvertBSTRToString产生内存泄露
	
	ASSERT(prgMyRge);//安全防护
	
	bstrInfo = (_bstr_t)prgMyRge->GetItem(_variant_t(lRow),_variant_t(lCol));//读指定行号列号对应的单元格
	pszBSTRToString = bstrInfo;//_com_util::ConvertBSTRToString((_bstr_t)bstrInfo);//将单元格的内容转换为char*，便于处理
	strItem = pszBSTRToString;//从char*变成CString便于处理
}

/*
函数原型:double AnalyeDynain(void);
参数说明:无
功能描述:从dynain文件中读取节点坐标和厚度，并按照目标函数进行分析
返回值:求得的优化函数值
*/
double CAnalyse::AnalyeDynain(void)
{
	double fvalue = OPTI_DEFALTVAL;//目标函数值
	//读取数据
	UINT nlog = ReadSimulateDataFromDynain();

	//从模拟值中查找与测量值最接近的点
	if (nlog == 0) 
	{
		SearchNearPoint();
	}
	
	//优化公司
	if (nlog == 0)
	{
		fvalue = OptimizeFunction();	
	}

	return fvalue;
}

/*
函数原型:UINT ReadSimulateDataFromDynain(void);
参数说明:无
功能描述:从.Dynain文件中读取模拟节点坐标和厚度
返回值:成功返回0 否则返回-1
*/
UINT CAnalyse::ReadSimulateDataFromDynain(void)
{
	CStdioFile fDynainFile;
	int nLineCouter = 0;
	CString strFilePath;
	CString strLineValue;//每一行的值
	map<long, long> mSearch;

	m_vSimulates.clear();
	strFilePath = m_strAnalyseExePath + "\\28.dynain";
	
	if(fDynainFile.Open(strFilePath, CFile::modeRead) == FALSE)//打开文件	
	{
		return -1;
	}

	while(1)
	{
		//读取文件
		fDynainFile.ReadString(strLineValue);

		//读取节点坐标
		if (strlen(strLineValue) > 0 && strcmp(strLineValue, "*NODE") == 0)
		{
			while(1)
			{
				Type_NodeThick stuNode;
				CString strtemp;
				strLineValue = "";
				fDynainFile.ReadString(strLineValue);

				//读取节点编号
				strtemp = strLineValue.Left(8);
				stuNode.nID = atol(strtemp);
				if (stuNode.nID <= 0)
				{
					//查找节点坐标结束
					break;
				}

				//读取x坐标
				strtemp = strLineValue.Right(strLineValue.GetLength() - 8);
				strtemp = strtemp.Left(16);
				stuNode.dPosX = atof(strtemp);

				//读取y坐标
				strtemp = strLineValue.Right(strLineValue.GetLength() - 24);
				strtemp = strtemp.Left(16);
				stuNode.dPosY = atof(strtemp);

				//读取z坐标
				strtemp = strLineValue.Right(strLineValue.GetLength() - 40);
				strtemp = strtemp.Left(16);
				stuNode.dPosZ = atof(strtemp);

				m_vSimulates.push_back(stuNode);
				mSearch[stuNode.nID] = m_vSimulates.size();
			}		
		}

		//读取节点厚度
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

				//读取节点编号
				for(i=0; i<4; i++)
				{
					strtemp = strLineValue.Right(strLineValue.GetLength() - 8*(2+i));
					strtemp = strtemp.Left(8);
					ldID[i] = atol(strtemp);
				}

				//读取节点厚度
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
			//未找到停止查询
			break;
		}
	}

	//关闭文件
	fDynainFile.Close();
	
	return 0;
}

/*
函数原型:void SearchNearPoint(void);
参数说明:无
功能描述:从模拟值中查找与测量值最接近的点
返回值:无
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
函数原型:double OptimizeFunction(void);
参数说明:无
功能描述:优化目标函数
返回值:返回优化函数值
*/
double CAnalyse::OptimizeFunction(void)
{
	double fSum = 0.0f;
	
	ASSERT(m_vMeasures.size() == m_vNearDatas.size());

	//优化公式
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

