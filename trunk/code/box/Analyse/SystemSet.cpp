/*
 * Copyright 2010 
 * All rights reserved.
 * 
 * Name:SystemSet.cpp
 * Author: 刘克富   
 * Date: 05/29/2010
 * Remarks: 系统参数设置
 * Revision history:                                 
*/

#include "../StdAfx.h"
#include "SystemSet.h"
/************************************************************************/
/*                              CSystemSet                              */
/************************************************************************/
/*
函数原型:
参数说明:无
返回值:无
功能描述:构造函数
*/
CSystemSet::CSystemSet()
{

}

/*
函数原型:
参数说明:无
返回值:无
功能描述:析构函数
*/
CSystemSet::~CSystemSet()
{

}

/*
函数原型:UINT Init(void);
参数说明:
	strPathName		系统目录
返回值:无
功能描述:初始化
*/
UINT CSystemSet::Init(void)
{
	long nCount;
	CString strTemp;
	MSXML2::IXMLDOMNodeListPtr pNodeList;
	MSXML2::IXMLDOMNodePtr pNode;
	MSXML2::IXMLDOMNamedNodeMapPtr pAttrMap;
	char szFileName[MAX_PATH];
	CString strPathName;
	
	
	//读取程序当目录
	if(ERROR_SUCCESS == GetModuleFileName(NULL, szFileName, MAX_PATH))
	{
		//添加运行记录	
		return -1;//获取文件路径失败
	}
	strPathName = szFileName;
	strPathName = strPathName.Left(strPathName.ReverseFind('\\'));
	strPathName = strPathName.Left(strPathName.ReverseFind('\\'));
	strPathName += "\\data\\SystemSet.xml";

	m_xml.Init(strPathName);
	
	nCount = m_xml.GetDocNodeList(pNodeList);//取得根节点下的节点集 和节点个数
	
	for (int j=0; j<nCount; j++)
	{		
		m_xml.GetNode(pNodeList, j, pNode);//取得节点集下的第一个节点		
		strTemp = m_xml.GetNodeName(pNode); //节点名称		
		if (strTemp == "material")//逻辑区段占用/空闲状态
		{
			Type_SystemSet stuSystemset;

			memset(&stuSystemset, 0, sizeof(stuSystemset));
			m_xml.GetNodeMap(pNode, pAttrMap);	

			//材料参数简称
			strTemp = m_xml.GetMapValue(pAttrMap, 0);
			strcpy(stuSystemset.szShortCaption, strTemp);

			//材料参数名称
			strTemp = m_xml.GetMapValue(pAttrMap, 1);
			strcpy(stuSystemset.szCaption, strTemp);

			//向下搜索值
			strTemp = m_xml.GetMapValue(pAttrMap, 2);
			strcpy(stuSystemset.dDownStep, strTemp);

			//向上搜索值
			strTemp = m_xml.GetMapValue(pAttrMap, 3);
			strcpy(stuSystemset.dUpStep, strTemp);

			//是否反求
			strTemp = m_xml.GetMapValue(pAttrMap, 4);
			if (strTemp == "是")
			{
				stuSystemset.bIsReverse = 1;
			}
			else
			{
				stuSystemset.bIsReverse = 0;
			}

			m_system.push_back(stuSystemset);			
		}
	}
	return 0;
}

/*
函数原型:UINT GetSystem(OUT vector<Type_SystemSet> &vSystem);
参数说明:
	vSystem		系统参数
返回值:成功返回0 否者返回异常码
功能描述:取得系统参数
*/
UINT CSystemSet::GetSystem(OUT vector<Type_SystemSet> &vSystem)
{
	vSystem.clear();

	for(int i=0; i<m_system.size(); i++)
	{
		vSystem.push_back(m_system[i]);
	}

	return 0;
}
