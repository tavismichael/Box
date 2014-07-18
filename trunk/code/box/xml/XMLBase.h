/*
 * Copyright 2009 
 * All rights reserved.
 * 
 * Name: XMLBase.H
 * Author: 刘克富
 * Date: 08/16/2009  
 * Remarks:解析XML文件
 * Revision history:                                 
*/

#ifndef AFX_XMLBASE_H
#define AFX_XMLBASE_H

#import <msxml4.dll>
#pragma   warning   (disable:4786)

using namespace MSXML2;

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/************************************************************************/
/*                             CXMLBase                                 */
/************************************************************************/
class CXMLBase //%RELAX<hmdef> justification
{
public:
	/* 
	函数原型:CXMLBase();
	参数说明: 无
	返回值: 无
	功能描述:构造函数
	*/
	CXMLBase(void);

	/*
	函数原型:virtual ~CXMLBase(void);
	参数说明:无		
	返回值: 无
	功能描述:析构函数
	*/
	virtual ~CXMLBase(void);

	/*
	函数原型:BOOL Init(IN CString strFilePath)
	参数说明:		
		strFilePath		XML文件的绝对路径		
	返回值: 成功返回TRUE 否则返回FALSE;
	功能描述:初始化
	*/
	BOOL Init(IN CString strFilePath);
	
	/*
	函数原型:long GetDocNodeList(OUT IXMLDOMNodeListPtr &pNodeList);
	参数说明:	
		pNodeList	子节点集
	返回值: 
		子节点个数
	功能描述:取得XML文件根节点的子节点链表和子节点个数
	*/
	long GetDocNodeList(OUT IXMLDOMNodeListPtr &pNodeList);

	/*
	函数原型:long GetNodeList(IN IXMLDOMNodePtr &pNode, OUT IXMLDOMNodeListPtr &pNodeList);
	参数说明:
		IN	pNode		节点
		OUT pNodeList	节点集
	返回值: 
		子节点个数
	功能描述:取得节点下的子节点链表和子节点个数
	*/
	long GetNodeList(IN IXMLDOMNodePtr &pNode, OUT IXMLDOMNodeListPtr &pNodeList);

	/*
	函数原型:BOOL GetNode(IN IXMLDOMNodeListPtr &pNodeList, IN long nIndex, OUT IXMLDOMNodePtr &pNode);
	参数说明:
		IN	pNodeList		节点集
		IN	nIndex		 	节点位置
		OUT pNode			节点
	返回值: 成功返回TRUE, 失败返回FALSE		
	功能描述:取得节点链表中的节点
	*/
	BOOL GetNode(IN IXMLDOMNodeListPtr &pNodeList, IN long nIndex, OUT IXMLDOMNodePtr &pNode);

	/*
	函数原型:CString GetNodeName(IN IXMLDOMNodePtr &pNode);
	参数说明:	
		pNode	节点
	返回值:节点名称
	功能描述:取得节点名称
	*/
	CString GetNodeName(IN IXMLDOMNodePtr &pNode);

	/*
	函数原型:long GetNodeMap(IN IXMLDOMNodePtr &pNode, OUT IXMLDOMNamedNodeMapPtr &pAttrMap);
	参数说明:
		pNode		节点
		pAttrMap	属性集
	返回值: 节点个数
	功能描述:取得节点属性集
	*/
	long GetNodeMap(IN IXMLDOMNodePtr &pNode, OUT IXMLDOMNamedNodeMapPtr &pAttrMap);

	/*
	函数原型:CString GetMapValue(IN IXMLDOMNamedNodeMapPtr &pAttrMap, IN long nIndex);
	参数说明:	
		pAttrMap	属性集
		nIndex		序号
	返回值: 属性的值
	功能描述:取得节点的第nIndex个属性的值
	*/
	CString GetMapValue(IN IXMLDOMNamedNodeMapPtr &pAttrMap, IN long nIndex);

	/*
	函数原型:BOOL SaveXML(IN CString strXML);
	参数说明:	
		strXML	要保存的内容
	返回值: 成功返回TRUE, 否者返回FALSE;
	功能描述:保存XML
	*/
	BOOL SaveXML(IN CString strXML);
private:
	IXMLDOMDocumentPtr m_pDoc;
	IXMLDOMElementPtr  m_pElemRoot;
	IXMLDOMNodeListPtr m_pNodeList;
	CString			   m_strFilePath;

	CXMLBase(const CXMLBase& forbid); //拷贝构造函数禁用	
	CXMLBase & operator=(const CXMLBase &forbid);     //赋值运行符禁用
};

#endif 