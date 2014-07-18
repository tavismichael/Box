/*
 * Copyright 2010 
 * All rights reserved.
 * 
 * Name:SystemSet.h
 * Author: ���˸�   
 * Date: 05/29/2010
 * Remarks: ϵͳ��������
 * Revision history:                                 
*/
#if !defined(AFX_SYSTEMSET_H__D88B0574_18CC_4A28_926D_A41BAB02B48C__INCLUDED_)
#define AFX_SYSTEMSET_H__D88B0574_18CC_4A28_926D_A41BAB02B48C__INCLUDED_

#include "../xml/XMLBase.h"
#include <vector>
using namespace std;

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/************************************************************************/
/*                                �ṹ����                              */
/************************************************************************/
typedef struct {
	char szShortCaption[32]; //���ϲ������
	char szCaption[32];		 //���ϲ�������
	char dUpStep[32];		 //��������ֵ
	char dDownStep[32];		 //��������ֵ
	BYTE	bIsReverse;		 //�Ƿ���
} Type_SystemSet;//���ϲ���

/************************************************************************/
/*                              CSystemSet                              */
/************************************************************************/
class CSystemSet  
{
public:
	/*
	����ԭ��:
	����˵��:��
	����ֵ:��
	��������:���캯��
	*/
	CSystemSet();

	/*
	����ԭ��:
	����˵��:��
	����ֵ:��
	��������:��������
	*/
	virtual ~CSystemSet();

	/*
	����ԭ��:UINT Init(void);
	����˵��:
	����ֵ:�ɹ�����0�����߷����쳣��
	��������:��ʼ��
	*/
	UINT Init(void);

	/*
	����ԭ��:UINT GetSystem(OUT vector<Type_SystemSet> &vSystem);
	����˵��:
		vSystem		ϵͳ����
	����ֵ:�ɹ�����0 ���߷����쳣��
	��������:ȡ��ϵͳ����
	*/
	UINT GetSystem(OUT vector<Type_SystemSet> &vSystem);

	CXMLBase				m_xml;

protected:

	vector<Type_SystemSet>	m_system;
};

#endif // !defined(AFX_SYSTEMSET_H__D88B0574_18CC_4A28_926D_A41BAB02B48C__INCLUDED_)
