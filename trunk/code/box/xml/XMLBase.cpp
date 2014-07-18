/*
 * Copyright 2009 
 * All rights reserved.
 * 
 * Name: XMLBase.cpp
 * Author: ���˸�
 * Date: 08/16/2009  
 * Remarks:����XML�ļ�
 * Revision history:                                 
*/

#include "../StdAfx.h"
#include "XMLBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/************************************************************************/
/*                             CXMLBase                                 */
/************************************************************************/
/*
����ԭ��:CXMLBase();
����˵��:��		
����ֵ: ��
��������:���캯��
*/
CXMLBase::CXMLBase(void)
{
}

/*
����ԭ��:virtual ~CXMLBase(void);
����˵��:��		
����ֵ: ��
��������:��������
*/
CXMLBase::~CXMLBase(void)
{

}

/*
����ԭ��:BOOL Init(IN CString strFilePath)
����˵��:		
	strFilePath		XML�ļ��ľ���·��		
����ֵ: �ɹ�����TRUE ���򷵻�FALSE;
��������:��ʼ��
*/
BOOL CXMLBase::Init(IN CString strFilePath)
{
	HRESULT hr;
	_variant_t   varOut((bool)TRUE);   
	_variant_t varFilePath = strFilePath;
	m_strFilePath = strFilePath;

	hr = m_pDoc.CreateInstance(__uuidof(DOMDocument40));
	if(FAILED(hr))
	{  
		 AfxMessageBox("�޷�����DOMDocument���������Ƿ�װ��MS XML Parser ���п�!"); 
		 return FALSE;
	} 	

	//�����ļ� 
	varOut = m_pDoc->load(varFilePath);
	if((bool)varOut == FALSE)   
	{   
		IXMLDOMParseErrorPtr errPtr =  m_pDoc->GetparseError();   
		_bstr_t  bstrErr(errPtr->reason);  
		CString strError;

		strError.Format("Source = Line:%ld; Char:%ld\nError Description= %s\n", errPtr->line, errPtr->linepos,(char*)bstrErr);   
		AfxMessageBox(strError);

		 return FALSE;
	}   

	//ȡ�ø��ڵ�
	m_pElemRoot = m_pDoc->documentElement;

	if (m_pElemRoot == NULL)
	{
		AfxMessageBox(strFilePath + "�ļ������ڸ��ڵ�!");
		return FALSE;	
	}

	return TRUE;
}

/*
����ԭ��:long GetDocNodeList(OUT IXMLDOMNodeListPtr pNodeList);
����˵��:	
	pNodeList	�ӽڵ㼯
����ֵ: 
	�ӽڵ����
��������:ȡ��XML�ļ����ڵ���ӽڵ�������ӽڵ����
*/
long CXMLBase::GetDocNodeList(OUT IXMLDOMNodeListPtr &pNodeList)
{
	long nCount = 0;

	try
	{
		pNodeList = m_pElemRoot->childNodes;

		pNodeList->get_length(&nCount);			
	}
	catch (_com_error &e)
	{
		CString strErr;

		strErr = e.ErrorMessage();
		AfxMessageBox(strErr);	
		
		nCount = 0;
	}

	return nCount;
}

/*
����ԭ��:long GetNodeList(IN IXMLDOMNodePtr pNode, OUT IXMLDOMNodeListPtr pNodeList);
����˵��:
	IN	pNode		�ڵ�
	OUT pNodeList	�ڵ㼯
����ֵ: 
	�ӽڵ����
��������:ȡ�ýڵ��µ��ӽڵ�������ӽڵ����
*/
long CXMLBase::GetNodeList(IN IXMLDOMNodePtr &pNode, OUT IXMLDOMNodeListPtr &pNodeList)
{
	long nCount = 0;

	ASSERT(pNode != NULL);

	try
	{
 		pNode->get_childNodes(&pNodeList);
		pNodeList->get_length(&nCount);
	}
	catch (_com_error &e)
	{
		CString strErr;

		strErr = e.ErrorMessage();
		//AfxMessageBox(strErr);	
		
		nCount = 0;		
	}
		
	return nCount;
}

/*
����ԭ��:BOOL GetNode(IN IXMLDOMNodeListPtr &pNodeList, IN long nIndex, OUT IXMLDOMNodePtr &pNode);
����˵��:
	IN	pNodeList		�ڵ㼯
	IN	nIndex		 	�ڵ�λ��
	OUT pNode			�ڵ�
����ֵ: �ɹ�����TRUE, ʧ�ܷ���FALSE		
��������:ȡ�ýڵ������еĽڵ�
*/
BOOL CXMLBase::GetNode(IN IXMLDOMNodeListPtr &pNodeList, IN long nIndex, OUT IXMLDOMNodePtr &pNode)
{
	ASSERT(pNodeList != NULL);
	ASSERT(nIndex >= 0);

	try
	{
		 pNodeList->get_item(nIndex, &pNode);
	}
	catch(_com_error &e)
	{
		CString strErr;

		strErr = e.ErrorMessage();		
		//AfxMessageBox(strErr);	

		return FALSE;
	}

	return TRUE;
}

/*
����ԭ��:CString GetNodeName(IN IXMLDOMNodePtr pNode);
����˵��:	
	pNode	�ڵ�
����ֵ:�ڵ�����
��������:ȡ�ýڵ�����
*/
CString CXMLBase::GetNodeName(IN IXMLDOMNodePtr &pNode)
{
	 //�ڵ����� 
	 CString strName = "";

	 ASSERT(pNode != NULL);

	 try
	 {
		 strName = (char *)pNode->GetnodeName();
	 }
	 catch (_com_error &e)
	 {
		CString strErr;

		strErr = e.ErrorMessage();		
		//AfxMessageBox(strErr);	
	 }

	 return strName;
}

/*
����ԭ��:long GetNodeMap(IN IXMLDOMNodePtr &pNode, OUT IXMLDOMNamedNodeMapPtr &pAttrMap);
����˵��:
	pNode		�ڵ�
	pAttrMap	���Լ�
����ֵ: �ڵ����
��������:ȡ�ýڵ����Լ�
*/
long CXMLBase::GetNodeMap(IN IXMLDOMNodePtr &pNode, OUT IXMLDOMNamedNodeMapPtr &pAttrMap)
{
	long nCount = 0;

	try
	{
		 pNode->get_attributes(&pAttrMap);
		 pAttrMap->get_length(&nCount);
	}
	catch (_com_error &e)
	{
		CString strErr;

		strErr = e.ErrorMessage();		
		//AfxMessageBox(strErr);	
	}

	return nCount;
}
/*
����ԭ��:CString GetMapValue(IN IXMLDOMNamedNodeMapPtr &pAttrMap, IN long nIndex);
����˵��:	
	pAttrMap	���Լ�
	nIndex		���
����ֵ: ���Ե�ֵ
��������:ȡ�ýڵ�ĵ�nIndex�����Ե�ֵ
*/
CString CXMLBase::GetMapValue(IN IXMLDOMNamedNodeMapPtr &pAttrMap, IN long nIndex)
{
	CString strValue = "";

	try
	{
		IXMLDOMNodePtr   pAttrItem;
		_variant_t variantvalue;

		pAttrMap->get_item(nIndex,&pAttrItem);

		
		pAttrItem->get_nodeTypedValue(&variantvalue);
		strValue = _com_util::ConvertBSTRToString(variantvalue.bstrVal);	
 		
	}
	catch (_com_error &e)
	{
		CString strErr;

		strErr = e.ErrorMessage();		
		//AfxMessageBox(strErr);
	}

	return strValue;
}
/*
����ԭ��:BOOL SaveXML(IN CString strXML);
����˵��:	
	strXML	Ҫ���������
����ֵ: �ɹ�����TRUE, ���߷���FALSE;
��������:����XML
*/
BOOL CXMLBase::SaveXML(IN CString strXML)
{
	FILE *fFile = NULL;
	fFile = fopen(m_strFilePath, "w");//���ļ�
	fprintf(fFile, "%s\n", strXML);//д����
	fclose(fFile);
	return TRUE;
}
