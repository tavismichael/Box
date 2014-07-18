/*
 * Copyright 2010 
 * All rights reserved.
 * 
 * Name:SystemSet.cpp
 * Author: ���˸�   
 * Date: 05/29/2010
 * Remarks: ϵͳ��������
 * Revision history:                                 
*/

#include "../StdAfx.h"
#include "SystemSet.h"
/************************************************************************/
/*                              CSystemSet                              */
/************************************************************************/
/*
����ԭ��:
����˵��:��
����ֵ:��
��������:���캯��
*/
CSystemSet::CSystemSet()
{

}

/*
����ԭ��:
����˵��:��
����ֵ:��
��������:��������
*/
CSystemSet::~CSystemSet()
{

}

/*
����ԭ��:UINT Init(void);
����˵��:
	strPathName		ϵͳĿ¼
����ֵ:��
��������:��ʼ��
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
	
	
	//��ȡ����Ŀ¼
	if(ERROR_SUCCESS == GetModuleFileName(NULL, szFileName, MAX_PATH))
	{
		//������м�¼	
		return -1;//��ȡ�ļ�·��ʧ��
	}
	strPathName = szFileName;
	strPathName = strPathName.Left(strPathName.ReverseFind('\\'));
	strPathName = strPathName.Left(strPathName.ReverseFind('\\'));
	strPathName += "\\data\\SystemSet.xml";

	m_xml.Init(strPathName);
	
	nCount = m_xml.GetDocNodeList(pNodeList);//ȡ�ø��ڵ��µĽڵ㼯 �ͽڵ����
	
	for (int j=0; j<nCount; j++)
	{		
		m_xml.GetNode(pNodeList, j, pNode);//ȡ�ýڵ㼯�µĵ�һ���ڵ�		
		strTemp = m_xml.GetNodeName(pNode); //�ڵ�����		
		if (strTemp == "material")//�߼�����ռ��/����״̬
		{
			Type_SystemSet stuSystemset;

			memset(&stuSystemset, 0, sizeof(stuSystemset));
			m_xml.GetNodeMap(pNode, pAttrMap);	

			//���ϲ������
			strTemp = m_xml.GetMapValue(pAttrMap, 0);
			strcpy(stuSystemset.szShortCaption, strTemp);

			//���ϲ�������
			strTemp = m_xml.GetMapValue(pAttrMap, 1);
			strcpy(stuSystemset.szCaption, strTemp);

			//��������ֵ
			strTemp = m_xml.GetMapValue(pAttrMap, 2);
			strcpy(stuSystemset.dDownStep, strTemp);

			//��������ֵ
			strTemp = m_xml.GetMapValue(pAttrMap, 3);
			strcpy(stuSystemset.dUpStep, strTemp);

			//�Ƿ���
			strTemp = m_xml.GetMapValue(pAttrMap, 4);
			if (strTemp == "��")
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
����ԭ��:UINT GetSystem(OUT vector<Type_SystemSet> &vSystem);
����˵��:
	vSystem		ϵͳ����
����ֵ:�ɹ�����0 ���߷����쳣��
��������:ȡ��ϵͳ����
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
