/*
 * Copyright 2009 
 * All rights reserved.
 * 
 * Name: Log.h
 * Author: ���˸�
 * Date: 06/01/2010
 * Remarks:��¼��־
 * Revision history:                                 
*/
#ifndef AFX_LOG_H
#define AFX_LOG_H

#include <Afxmt.h>


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/************************************************************************/
/* �궨��                                                               */
/************************************************************************/

/************************************************************************/
/* �ṹ�嶨��                                                           */
/************************************************************************/

/************************************************************************/
/* ����ļ���־							                                */
/************************************************************************/
class  CLog
{
public:
	/*
	����ԭ�ͣ�
	����˵����
	����ֵ��
	�������������캯��
	*/
	CLog(void);
	
	/*
	����ԭ�ͣ�
	����˵����
	����ֵ��
	�������������캯��
	*/
	virtual ~CLog(void);

	/*
	����ԭ�ͣ�void AddRunRecord(IN LPCTSTR lpszFormat, ...);
	����˵����
		lpszFormat			��־��Ϣ
	����ֵ����
	���������������־
	*/
	static void AddRunRecord(IN LPCTSTR lpszFormat, ...);

private:
	static CLog			m_log;

	ULONG				m_dwCycleNum;
	FILE				*m_fpTRACE;//��ӡ�ļ���Ӧ�ı�ʶ
	CString				m_strLogPath;//��־Ŀ¼
	CCriticalSection	m_csTRACE;
	
	CLog(const CLog& Record); //�������캯������
	CLog & operator=(const CLog &Record);     //��ֵ���з�����

	/*
	����ԭ��:int fTRACE(LPCTSTR szFileName, LPCTSTR lpszFormat, ...)
	����˵��:		
	����ֵ: �ɹ�����������ݵĳ��ȣ����򷵻�-1
	��������:������ݵ�ָ���ļ������szFileName ΪNULL������E��DebugData�²���һ���Գ���ʼʱ��Ϊ���ֵ�Txt�ļ�����
	������Ҫ������������������֮�󴫵ݽ�ȥ
	*/
	int fTRACE(IN LPCTSTR szFileName, IN LPCTSTR lpszFormat, ...); // %RELAX<vararg> justification
};

#endif 
