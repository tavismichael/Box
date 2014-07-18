/*
 * Copyright 2009 
 * All rights reserved.
 * 
 * Name: XMLBase.cpp
 * Author: 刘克富
 * Date: 08/16/2009  
 * Remarks:解析XML文件
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
函数原型:CXMLBase();
参数说明:无		
返回值: 无
功能描述:构造函数
*/
CXMLBase::CXMLBase(void)
{
}

/*
函数原型:virtual ~CXMLBase(void);
参数说明:无		
返回值: 无
功能描述:析构函数
*/
CXMLBase::~CXMLBase(void)
{

}

/*
函数原型:BOOL Init(IN CString strFilePath)
参数说明:		
	strFilePath		XML文件的绝对路径		
返回值: 成功返回TRUE 否则返回FALSE;
功能描述:初始化
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
		 AfxMessageBox("无法创建DOMDocument对象，请检查是否安装了MS XML Parser 运行库!"); 
		 return FALSE;
	} 	

	//加载文件 
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

	//取得根节点
	m_pElemRoot = m_pDoc->documentElement;

	if (m_pElemRoot == NULL)
	{
		AfxMessageBox(strFilePath + "文件不存在根节点!");
		return FALSE;	
	}

	return TRUE;
}

/*
函数原型:long GetDocNodeList(OUT IXMLDOMNodeListPtr pNodeList);
参数说明:	
	pNodeList	子节点集
返回值: 
	子节点个数
功能描述:取得XML文件根节点的子节点链表和子节点个数
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
函数原型:long GetNodeList(IN IXMLDOMNodePtr pNode, OUT IXMLDOMNodeListPtr pNodeList);
参数说明:
	IN	pNode		节点
	OUT pNodeList	节点集
返回值: 
	子节点个数
功能描述:取得节点下的子节点链表和子节点个数
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
函数原型:BOOL GetNode(IN IXMLDOMNodeListPtr &pNodeList, IN long nIndex, OUT IXMLDOMNodePtr &pNode);
参数说明:
	IN	pNodeList		节点集
	IN	nIndex		 	节点位置
	OUT pNode			节点
返回值: 成功返回TRUE, 失败返回FALSE		
功能描述:取得节点链表中的节点
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
函数原型:CString GetNodeName(IN IXMLDOMNodePtr pNode);
参数说明:	
	pNode	节点
返回值:节点名称
功能描述:取得节点名称
*/
CString CXMLBase::GetNodeName(IN IXMLDOMNodePtr &pNode)
{
	 //节点名称 
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
函数原型:long GetNodeMap(IN IXMLDOMNodePtr &pNode, OUT IXMLDOMNamedNodeMapPtr &pAttrMap);
参数说明:
	pNode		节点
	pAttrMap	属性集
返回值: 节点个数
功能描述:取得节点属性集
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
函数原型:CString GetMapValue(IN IXMLDOMNamedNodeMapPtr &pAttrMap, IN long nIndex);
参数说明:	
	pAttrMap	属性集
	nIndex		序号
返回值: 属性的值
功能描述:取得节点的第nIndex个属性的值
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
函数原型:BOOL SaveXML(IN CString strXML);
参数说明:	
	strXML	要保存的内容
返回值: 成功返回TRUE, 否者返回FALSE;
功能描述:保存XML
*/
BOOL CXMLBase::SaveXML(IN CString strXML)
{
	FILE *fFile = NULL;
	fFile = fopen(m_strFilePath, "w");//打开文件
	fprintf(fFile, "%s\n", strXML);//写数据
	fclose(fFile);
	return TRUE;
}
