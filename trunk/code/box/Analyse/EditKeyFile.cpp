/*
 * Copyright 2010 
 * All rights reserved.
 * 
 * Name:EditKeyFile.cpp
 * Author: 刘克富   
 * Date: 05/29/2010
 * Remarks: 编辑KEY文件
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
函数原型:CEditKeyFile();
参数说明:无
返回值:无
功能描述:构造函数
*/
CEditKeyFile::CEditKeyFile(void)
{

}

/*
函数原型:virtual ~CEditKeyFile();
参数说明:无
返回值:无
功能描述:析构函数
*/
CEditKeyFile::~CEditKeyFile(void)
{

}

/*
函数原型:UINT Init(IN CString strFilePath);
参数说明:
	strFilePath		key文件路径
返回值:成功返回0， 否则返回-1
功能描述:初始化
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
	fKeyFile = fopen(strFilePath, "r+");//打开文件
	
	if (fKeyFile == NULL)
	{		
		AfxMessageBox("无法打开文件:" + strFilePath);
		return -1;
	}

	while(1)
	{
		//读取文件
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
			//未找到停止查询
			fclose(fKeyFile);
			return -1;
		}
	}

	//数据校验
	if (m_vstrKeyNames.size() != m_vstrKeyValues.size())
	{
		AfxMessageBox("系统KEY文件已经损坏!请重新加载");
	}
	
	//关闭文件
	fclose(fKeyFile);
	return 0;
}

/*
函数原型:UINT ReInit(void);
参数说明:
	返回值:成功返回0， 否则返回-1
功能描述:重新读取数据
*/
UINT CEditKeyFile::ReInit(void)
{
	m_vstrKeyNames.clear();
	m_vstrKeyValues.clear();

	Init(m_strFilePath);
	return 0;
}

/*
函数原型:UINT GetKeyValues(OUT vector<CString> &vstrKeyName, OUT vector<CString> &vstrKeyValue);
参数说明:
	vstrKeyName  材料参数名称
	vstrKeyValue 材料参数值
返回值:成返回0 否则返回-1
功能描述:取得所有KEY值
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
函数原型:UINT GetKeyValue(IN CString strKeyName, OUT CString &strKeyValue);
参数说明:
	strKeyName  材料参数名称
	strKeyValue 材料参数值
返回值:成返回0 否则返回-1
功能描述:取得KEY值
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
函数原型:UINT SetKeyValue(IN CString strKeyName, IN CString strKeyValue);
参数说明:
	strKeyName  材料参数名称
	strKeyValue 材料参数值
返回值:成返回0 否则返回-1
功能描述:设置KEY值
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
函数原型:UINT WriteData(void);
参数说明:无
返回值:成返回0 否则返回-1
功能描述:将修改的数据写入KEY文件
*/
UINT CEditKeyFile::WriteData(void)
{
	int nLineCouter = 0;
//	char szLineVale[1024];
	CString strValue;
	int iResult = 0;//操作结果
	CStdioFile file;
    CString str;
	
    file.Open(m_strFilePath,CFile::modeReadWrite);

	while(1)
	{
		//读取文件
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
			//未找到停止查询
			file.Close();
			return -1;
		}
	}

    file.Close();
	return 0;
}
