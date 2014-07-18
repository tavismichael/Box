/*
 * Copyright 2009 
 * All rights reserved.
 * 
 * Name: Log.cpp
 * Author: ���˸�
 * Date: 06/01/2010
 * Remarks:��¼��־
 * Revision history:                                 
*/

#include "../StdAfx.h"
#include "Log.h"

CLog CLog::m_log;
/*
����ԭ�ͣ�
����˵����
����ֵ��
�������������캯��
*/
CLog::CLog(void)
{
	m_dwCycleNum = 0;
	m_fpTRACE = NULL;

	char szFileName[MAX_PATH];//�ļ�·��
	
	//��ȡ����Ŀ¼
	if(ERROR_SUCCESS == GetModuleFileName(NULL, szFileName, MAX_PATH))
	{
		//������м�¼
		AfxMessageBox("CLog::CLog(void)��ʼ��Ŀ¼ʧ��!");
	}
	
	m_strLogPath = szFileName;
	m_strLogPath = m_strLogPath.Left(m_strLogPath.ReverseFind('\\'));
	m_strLogPath = m_strLogPath.Left(m_strLogPath.ReverseFind('\\'));
	m_strLogPath += "\\LogData\\";
}
	
/*
����ԭ�ͣ�
����˵����
����ֵ��
�������������캯��
*/
CLog::~CLog(void)
{
}

/*
����ԭ�ͣ�void AddRunRecord(IN LPCTSTR lpszFormat, ...);
����˵����
	lpszFormat			��־��Ϣ
����ֵ����
���������������־
*/
void CLog::AddRunRecord(IN LPCTSTR lpszFormat, ...)
{
	va_list args;//�����б�
	TCHAR szBuffer[65535];
	int iResult = 0;//�������
	CString strLog;
	
	memset(szBuffer, 0, sizeof(szBuffer));
	
	//��ʽ����
	va_start(args, lpszFormat);
	iResult = _vsntprintf(szBuffer, sizeof(szBuffer), lpszFormat, args);
	va_end(args);
	
	if (iResult > 0)
	{
		CString strTimeNow;
		CTime timeForPrint;

		//��ȡ������ʼʱ�䣨ʱ���룩
		timeForPrint = CTime::GetCurrentTime();//��ȡ��ǰʱ��
		strTimeNow.Format("%s", timeForPrint.Format("%H:%M:%S"));//��ʽ��ʱ��

		//���ݸ�ֵ
		strLog = szBuffer;
		strLog = "��" + strTimeNow + "��" + strLog;
		
		m_log.fTRACE(NULL, "%s\n", strLog);	
	}
}

/*
����ԭ��:int fTRACE(LPCTSTR szFileName, LPCTSTR lpszFormat, ...)
����˵��:		
����ֵ: �ɹ�����������ݵĳ��ȣ����򷵻�-1
��������:������ݵ�ָ���ļ������szFileName ΪNULL������E��DebugData�²���һ���Գ���ʼʱ��Ϊ���ֵ�Txt�ļ�����
������Ҫ������������������֮�󴫵ݽ�ȥ
*/
int CLog::fTRACE(IN LPCTSTR szFileName, IN LPCTSTR lpszFormat, ...) // %RELAX<vararg> justification
{
	TCHAR szBuffer[65535];
	int nFileRecordCount = 10000; //ÿ����־�ļ���¼����־������

	va_list args;//�����б�
	int iResult = -1;//�������
	m_dwCycleNum ++;
	
	if (m_dwCycleNum % nFileRecordCount == 0)
	{
		m_fpTRACE = NULL;
	}
	
	if (m_fpTRACE == NULL)
	{
		//����һ���ļ�
		if (szFileName == NULL)
		{
			CTime time;			
			CString strFileName;
			CString strCycleNum;
			
			//����һ��Ĭ�ϵ�Ŀ¼��Ĭ�ϵ��ļ�
			CreateDirectory(m_strLogPath,NULL);
			//��ȡ��ǰʱ��
			time = CTime::GetCurrentTime();
			//�Ե�ǰ������ʱ��Ϊ�ļ���
			strFileName.Format("%s\\%s", m_strLogPath, time.Format( "%Y��%B%d_%H_%M_%S"));
			strCycleNum.Format("_%d.log", m_dwCycleNum/nFileRecordCount);			
			strFileName += strCycleNum;
			//�����ļ�
			m_fpTRACE = fopen(strFileName, "a+");
			if (m_fpTRACE == NULL) //׷����ʽ����
			{
				//�ļ���ʧ��
				return -1;
			}
		}
		else
		{
			//�����ﲻ��·���ĺϷ������ж�
			//��������ļ�
			m_fpTRACE = fopen(szFileName, "a+");
			if (m_fpTRACE == NULL) //׷����ʽ����
			{
				//���û���ʾ �����ļ�ʧ��
				AfxMessageBox("�����ļ�%sʧ��!");
				return -1;
			}
		}
	}
	
	if (m_fpTRACE != NULL)
	{
		//�߳�ͬ������
		m_csTRACE.Lock();
		
		memset(szBuffer, 0, sizeof(szBuffer));
		va_start(args, lpszFormat);//׼������
		iResult = _vsntprintf(szBuffer, 65535, lpszFormat, args);
		iResult = fprintf(m_fpTRACE, "%s", szBuffer);
		
		if (iResult != -1)
		{
			//���ļ�д���ı�
			fflush(m_fpTRACE);
		}
		va_end(args);
		
		//�ֳ�ͬ������
		m_csTRACE.Unlock();
	}
	return iResult;
}