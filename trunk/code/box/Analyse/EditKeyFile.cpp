/*
 * Copyright 2010 
 * All rights reserved.
 * 
 * Name:EditKeyFile.cpp
 * Author: ���˸�   
 * Date: 05/29/2010
 * Remarks: �༭KEY�ļ�
 * Revision history:                                 
*/

#include "../StdAfx.h"
#include "EditKeyFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
/*
����ԭ��:CEditKeyFile();
����˵��:��
����ֵ:��
��������:���캯��
*/
CEditKeyFile::CEditKeyFile(void)
{

}

/*
����ԭ��:virtual ~CEditKeyFile();
����˵��:��
����ֵ:��
��������:��������
*/
CEditKeyFile::~CEditKeyFile(void)
{

}

/*
����ԭ��:UINT Init(IN CString strFilePath);
����˵��:
	strFilePath		key�ļ�·��
����ֵ:�ɹ�����0�� ���򷵻�-1
��������:��ʼ��
*/
UINT CEditKeyFile::Init(IN CString strFilePath)
{
	FILE *fKeyFile = NULL;
	int nLineCouter = 0;
	char szLineVale[1024];

	m_vstrKeyNames.push_back("MID");//
	m_vstrKeyNames.push_back("RO");//
	m_vstrKeyNames.push_back("E");//
	m_vstrKeyNames.push_back("PR");//
	m_vstrKeyNames.push_back("HR");//
	m_vstrKeyNames.push_back("P1");//
	m_vstrKeyNames.push_back("P2");//
	m_vstrKeyNames.push_back("M");//
	m_vstrKeyNames.push_back("R00");//
	m_vstrKeyNames.push_back("R45");//
	m_vstrKeyNames.push_back("R90");//
	m_vstrKeyNames.push_back("LCID");//
	m_vstrKeyNames.push_back("E0");//
	m_vstrKeyNames.push_back("SPI");//
	m_vstrKeyNames.push_back("AOPT");//
	
	m_strFilePath = strFilePath;
	fKeyFile = fopen(strFilePath, "r+");//���ļ�
	
	if (fKeyFile == NULL)
	{		
		AfxMessageBox("�޷����ļ�:" + strFilePath);
		return -1;
	}

	while(1)
	{
		//��ȡ�ļ�
		fscanf(fKeyFile, "%s", szLineVale);
		if (strcmp(szLineVale, "*MAT_3-PARAMETER_BARLAT") == 0)
		{
			for(int i=0; i<10; i++)
			{
				fscanf(fKeyFile, "%s", szLineVale);
			}
			
			for(i=0; i<7; i++)
			{
				fscanf(fKeyFile, "%s", szLineVale);
				m_vstrKeyValues.push_back(szLineVale);
			}
			
			for( i=0; i<8; i++)
			{
				fscanf(fKeyFile, "%s", szLineVale);
			}
	
			for(i=0; i<7; i++)
			{
				fscanf(fKeyFile, "%s", szLineVale);
				m_vstrKeyValues.push_back(szLineVale);
			}

			for( i=0; i<2; i++)
			{
				fscanf(fKeyFile, "%s", szLineVale);
			}	
			
			fscanf(fKeyFile, "%s", szLineVale);
			m_vstrKeyValues.push_back(szLineVale);

			break;
		}
	
		nLineCouter++;
		if (nLineCouter > 600)
		{
			//δ�ҵ�ֹͣ��ѯ
			fclose(fKeyFile);
			return -1;
		}
	}

	//����У��
	if (m_vstrKeyNames.size() != m_vstrKeyValues.size())
	{
		AfxMessageBox("ϵͳKEY�ļ��Ѿ���!�����¼���");
	}
	
	//�ر��ļ�
	fclose(fKeyFile);
	return 0;
}

/*
����ԭ��:UINT ReInit(void);
����˵��:
	����ֵ:�ɹ�����0�� ���򷵻�-1
��������:���¶�ȡ����
*/
UINT CEditKeyFile::ReInit(void)
{
	m_vstrKeyNames.clear();
	m_vstrKeyValues.clear();

	Init(m_strFilePath);
	return 0;
}

/*
����ԭ��:UINT GetKeyValues(OUT vector<CString> &vstrKeyName, OUT vector<CString> &vstrKeyValue);
����˵��:
	vstrKeyName  ���ϲ�������
	vstrKeyValue ���ϲ���ֵ
����ֵ:�ɷ���0 ���򷵻�-1
��������:ȡ������KEYֵ
*/
UINT CEditKeyFile::GetKeyValues(OUT vector<CString> &vstrKeyName, OUT vector<CString> &vstrKeyValue)
{
	vstrKeyName.clear();
	vstrKeyValue.clear();
	
	for(int i=0; i<m_vstrKeyNames.size(); i++)
	{
		vstrKeyName.push_back(m_vstrKeyNames[i]);	
	}

	for(i=0; i<m_vstrKeyValues.size(); i++)
	{
		vstrKeyValue.push_back(m_vstrKeyValues[i]);	
	}

	return 0;
}

/*
����ԭ��:UINT GetKeyValue(IN CString strKeyName, OUT CString &strKeyValue);
����˵��:
	strKeyName  ���ϲ�������
	strKeyValue ���ϲ���ֵ
����ֵ:�ɷ���0 ���򷵻�-1
��������:ȡ��KEYֵ
*/
UINT CEditKeyFile::GetKeyValue(IN CString strKeyName, OUT CString &strKeyValue)
{
	for(int i=0; i<m_vstrKeyNames.size(); i++)
	{
		if (strcmp(strKeyName, m_vstrKeyNames[i]) == 0)
		{
			strKeyValue = m_vstrKeyValues[i];
			return 0;
		}
	}

	return -1;	
}

/*
����ԭ��:UINT SetKeyValue(IN CString strKeyName, IN CString strKeyValue);
����˵��:
	strKeyName  ���ϲ�������
	strKeyValue ���ϲ���ֵ
����ֵ:�ɷ���0 ���򷵻�-1
��������:����KEYֵ
*/
UINT CEditKeyFile::SetKeyValue(IN CString strKeyName, IN CString strKeyValue)
{	
	for(int i=0; i<m_vstrKeyNames.size(); i++)
	{
		if (strcmp(strKeyName, m_vstrKeyNames[i]) == 0)
		{
			m_vstrKeyValues[i] = strKeyValue;
			return 0;
		}
	}
	
	return -1;
}

/*
����ԭ��:UINT WriteData(void);
����˵��:��
����ֵ:�ɷ���0 ���򷵻�-1
��������:���޸ĵ�����д��KEY�ļ�
*/
UINT CEditKeyFile::WriteData(void)
{
	int nLineCouter = 0;
//	char szLineVale[1024];
	CString strValue;
	int iResult = 0;//�������
	CStdioFile file;
    CString str;
	
    file.Open(m_strFilePath,CFile::modeReadWrite);

	while(1)
	{
		//��ȡ�ļ�
		file.ReadString(str);

		if (strcmp(str, "*MAT_3-PARAMETER_BARLAT") == 0)
		{
			file.ReadString(str);
			file.ReadString(str);
			file.Seek(0,CFile::current);
			
			strValue = ""; 
			for(int i=0; i<7; i++)
			{
				CString strtemp = "          ";
				CString strkeyValue = m_vstrKeyValues[i];
				int nStart = 10 - strkeyValue.GetLength();
				
				for(int j=0; j<strkeyValue.GetLength(); j++)
				{
					strtemp.SetAt(nStart++, strkeyValue.GetAt(j));
				}

				strValue += strtemp;				
			}

            file.Write(strValue,strlen(strValue));
			file.Flush();

			file.ReadString(str);
			file.ReadString(str);		
			file.Seek(0,CFile::current);
			
			strValue = ""; 
			for(i=7; i<14; i++)
			{
				CString strtemp = "          ";
				CString strkeyValue = m_vstrKeyValues[i];
				int nStart = 10 - strkeyValue.GetLength();
				
				for(int j=0; j<strkeyValue.GetLength(); j++)
				{
					strtemp.SetAt(nStart++, strkeyValue.GetAt(j));
				}
				
				strValue += strtemp;				
			}

            file.Write(strValue,strlen(strValue));
			file.Flush();

			break;
		}
	
		nLineCouter++;
		if (nLineCouter > 600)
		{
			//δ�ҵ�ֹͣ��ѯ
			file.Close();
			return -1;
		}
	}

    file.Close();
	return 0;
}
