/*
 * Copyright 2009 
 * All rights reserved.
 * 
 * Name: Log.cpp
 * Author: 刘克富
 * Date: 06/01/2010
 * Remarks:记录日志
 * Revision history:                                 
*/

#include "../StdAfx.h"
#include "Log.h"

CLog CLog::m_log;
/*
函数原型：
参数说明：
返回值：
功能描述：构造函数
*/
CLog::CLog(void)
{
	m_dwCycleNum = 0;
	m_fpTRACE = NULL;

	char szFileName[MAX_PATH];//文件路径
	
	//读取程序当目录
	if(ERROR_SUCCESS == GetModuleFileName(NULL, szFileName, MAX_PATH))
	{
		//添加运行记录
		AfxMessageBox("CLog::CLog(void)初始化目录失败!");
	}
	
	m_strLogPath = szFileName;
	m_strLogPath = m_strLogPath.Left(m_strLogPath.ReverseFind('\\'));
	m_strLogPath = m_strLogPath.Left(m_strLogPath.ReverseFind('\\'));
	m_strLogPath += "\\LogData\\";
}
	
/*
函数原型：
参数说明：
返回值：
功能描述：构造函数
*/
CLog::~CLog(void)
{
}

/*
函数原型：void AddRunRecord(IN LPCTSTR lpszFormat, ...);
参数说明：
	lpszFormat			日志信息
返回值：无
功能描述：添加日志
*/
void CLog::AddRunRecord(IN LPCTSTR lpszFormat, ...)
{
	va_list args;//参数列表
	TCHAR szBuffer[65535];
	int iResult = 0;//操作结果
	CString strLog;
	
	memset(szBuffer, 0, sizeof(szBuffer));
	
	//格式化串
	va_start(args, lpszFormat);
	iResult = _vsntprintf(szBuffer, sizeof(szBuffer), lpszFormat, args);
	va_end(args);
	
	if (iResult > 0)
	{
		CString strTimeNow;
		CTime timeForPrint;

		//获取周期起始时间（时分秒）
		timeForPrint = CTime::GetCurrentTime();//获取当前时间
		strTimeNow.Format("%s", timeForPrint.Format("%H:%M:%S"));//格式化时间

		//内容赋值
		strLog = szBuffer;
		strLog = "【" + strTimeNow + "】" + strLog;
		
		m_log.fTRACE(NULL, "%s\n", strLog);	
	}
}

/*
函数原型:int fTRACE(LPCTSTR szFileName, LPCTSTR lpszFormat, ...)
参数说明:		
返回值: 成功返回输出数据的长度，否则返回-1
功能描述:输出内容到指定文件，如果szFileName 为NULL，则在E盘DebugData下产生一个以程序开始时间为名字的Txt文件夹下
在这里要将参数拷贝到出来，之后传递进去
*/
int CLog::fTRACE(IN LPCTSTR szFileName, IN LPCTSTR lpszFormat, ...) // %RELAX<vararg> justification
{
	TCHAR szBuffer[65535];
	int nFileRecordCount = 10000; //每个日志文件记录的日志周期数

	va_list args;//参数列表
	int iResult = -1;//操作结果
	m_dwCycleNum ++;
	
	if (m_dwCycleNum % nFileRecordCount == 0)
	{
		m_fpTRACE = NULL;
	}
	
	if (m_fpTRACE == NULL)
	{
		//创建一个文件
		if (szFileName == NULL)
		{
			CTime time;			
			CString strFileName;
			CString strCycleNum;
			
			//创建一个默认的目录和默认的文件
			CreateDirectory(m_strLogPath,NULL);
			//获取当前时间
			time = CTime::GetCurrentTime();
			//以当前的运行时间为文件名
			strFileName.Format("%s\\%s", m_strLogPath, time.Format( "%Y年%B%d_%H_%M_%S"));
			strCycleNum.Format("_%d.log", m_dwCycleNum/nFileRecordCount);			
			strFileName += strCycleNum;
			//创建文件
			m_fpTRACE = fopen(strFileName, "a+");
			if (m_fpTRACE == NULL) //追加形式创建
			{
				//文件打开失败
				return -1;
			}
		}
		else
		{
			//在这里不对路径的合法性作判断
			//创建这个文件
			m_fpTRACE = fopen(szFileName, "a+");
			if (m_fpTRACE == NULL) //追加形式创建
			{
				//向用户提示 创建文件失败
				AfxMessageBox("创建文件%s失败!");
				return -1;
			}
		}
	}
	
	if (m_fpTRACE != NULL)
	{
		//线程同步锁闭
		m_csTRACE.Lock();
		
		memset(szBuffer, 0, sizeof(szBuffer));
		va_start(args, lpszFormat);//准备参数
		iResult = _vsntprintf(szBuffer, 65535, lpszFormat, args);
		iResult = fprintf(m_fpTRACE, "%s", szBuffer);
		
		if (iResult != -1)
		{
			//向文件写入文本
			fflush(m_fpTRACE);
		}
		va_end(args);
		
		//现场同步解锁
		m_csTRACE.Unlock();
	}
	return iResult;
}