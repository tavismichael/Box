/*
 * Copyright 2009 
 * All rights reserved.
 * 
 * Name: Log.h
 * Author: 刘克富
 * Date: 06/01/2010
 * Remarks:记录日志
 * Revision history:                                 
*/
#ifndef AFX_LOG_H
#define AFX_LOG_H

#include <Afxmt.h>


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/************************************************************************/
/* 宏定义                                                               */
/************************************************************************/

/************************************************************************/
/* 结构体定义                                                           */
/************************************************************************/

/************************************************************************/
/* 添加文件日志							                                */
/************************************************************************/
class  CLog
{
public:
	/*
	函数原型：
	参数说明：
	返回值：
	功能描述：构造函数
	*/
	CLog(void);
	
	/*
	函数原型：
	参数说明：
	返回值：
	功能描述：构造函数
	*/
	virtual ~CLog(void);

	/*
	函数原型：void AddRunRecord(IN LPCTSTR lpszFormat, ...);
	参数说明：
		lpszFormat			日志信息
	返回值：无
	功能描述：添加日志
	*/
	static void AddRunRecord(IN LPCTSTR lpszFormat, ...);

private:
	static CLog			m_log;

	ULONG				m_dwCycleNum;
	FILE				*m_fpTRACE;//打印文件对应的标识
	CString				m_strLogPath;//日志目录
	CCriticalSection	m_csTRACE;
	
	CLog(const CLog& Record); //拷贝构造函数禁用
	CLog & operator=(const CLog &Record);     //赋值运行符禁用

	/*
	函数原型:int fTRACE(LPCTSTR szFileName, LPCTSTR lpszFormat, ...)
	参数说明:		
	返回值: 成功返回输出数据的长度，否则返回-1
	功能描述:输出内容到指定文件，如果szFileName 为NULL，则在E盘DebugData下产生一个以程序开始时间为名字的Txt文件夹下
	在这里要将参数拷贝到出来，之后传递进去
	*/
	int fTRACE(IN LPCTSTR szFileName, IN LPCTSTR lpszFormat, ...); // %RELAX<vararg> justification
};

#endif 
