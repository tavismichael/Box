/*
 * Copyright 2009 
 * All rights reserved.
 * 
 * Name: XMLBase.H
 * Author: ���˸�
 * Date: 08/16/2009  
 * Remarks:����XML�ļ�
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
	����ԭ��:CXMLBase();
	����˵��: ��
	����ֵ: ��
	��������:���캯��
	*/
	CXMLBase(void);

	/*
	����ԭ��:virtual ~CXMLBase(void);
	����˵��:��		
	����ֵ: ��
	��������:��������
	*/
	virtual ~CXMLBase(void);

	/*
	����ԭ��:BOOL Init(IN CString strFilePath)
	����˵��:		
		strFilePath		XML�ļ��ľ���·��		
	����ֵ: �ɹ�����TRUE ���򷵻�FALSE;
	��������:��ʼ��
	*/
	BOOL Init(IN CString strFilePath);
	
	/*
	����ԭ��:long GetDocNodeList(OUT IXMLDOMNodeListPtr &pNodeList);
	����˵��:	
		pNodeList	�ӽڵ㼯
	����ֵ: 
		�ӽڵ����
	��������:ȡ��XML�ļ����ڵ���ӽڵ�������ӽڵ����
	*/
	long GetDocNodeList(OUT IXMLDOMNodeListPtr &pNodeList);

	/*
	����ԭ��:long GetNodeList(IN IXMLDOMNodePtr &pNode, OUT IXMLDOMNodeListPtr &pNodeList);
	����˵��:
		IN	pNode		�ڵ�
		OUT pNodeList	�ڵ㼯
	����ֵ: 
		�ӽڵ����
	��������:ȡ�ýڵ��µ��ӽڵ�������ӽڵ����
	*/
	long GetNodeList(IN IXMLDOMNodePtr &pNode, OUT IXMLDOMNodeListPtr &pNodeList);

	/*
	����ԭ��:BOOL GetNode(IN IXMLDOMNodeListPtr &pNodeList, IN long nIndex, OUT IXMLDOMNodePtr &pNode);
	����˵��:
		IN	pNodeList		�ڵ㼯
		IN	nIndex		 	�ڵ�λ��
		OUT pNode			�ڵ�
	����ֵ: �ɹ�����TRUE, ʧ�ܷ���FALSE		
	��������:ȡ�ýڵ������еĽڵ�
	*/
	BOOL GetNode(IN IXMLDOMNodeListPtr &pNodeList, IN long nIndex, OUT IXMLDOMNodePtr &pNode);

	/*
	����ԭ��:CString GetNodeName(IN IXMLDOMNodePtr &pNode);
	����˵��:	
		pNode	�ڵ�
	����ֵ:�ڵ�����
	��������:ȡ�ýڵ�����
	*/
	CString GetNodeName(IN IXMLDOMNodePtr &pNode);

	/*
	����ԭ��:long GetNodeMap(IN IXMLDOMNodePtr &pNode, OUT IXMLDOMNamedNodeMapPtr &pAttrMap);
	����˵��:
		pNode		�ڵ�
		pAttrMap	���Լ�
	����ֵ: �ڵ����
	��������:ȡ�ýڵ����Լ�
	*/
	long GetNodeMap(IN IXMLDOMNodePtr &pNode, OUT IXMLDOMNamedNodeMapPtr &pAttrMap);

	/*
	����ԭ��:CString GetMapValue(IN IXMLDOMNamedNodeMapPtr &pAttrMap, IN long nIndex);
	����˵��:	
		pAttrMap	���Լ�
		nIndex		���
	����ֵ: ���Ե�ֵ
	��������:ȡ�ýڵ�ĵ�nIndex�����Ե�ֵ
	*/
	CString GetMapValue(IN IXMLDOMNamedNodeMapPtr &pAttrMap, IN long nIndex);

	/*
	����ԭ��:BOOL SaveXML(IN CString strXML);
	����˵��:	
		strXML	Ҫ���������
	����ֵ: �ɹ�����TRUE, ���߷���FALSE;
	��������:����XML
	*/
	BOOL SaveXML(IN CString strXML);
private:
	IXMLDOMDocumentPtr m_pDoc;
	IXMLDOMElementPtr  m_pElemRoot;
	IXMLDOMNodeListPtr m_pNodeList;
	CString			   m_strFilePath;

	CXMLBase(const CXMLBase& forbid); //�������캯������	
	CXMLBase & operator=(const CXMLBase &forbid);     //��ֵ���з�����
};

#endif 