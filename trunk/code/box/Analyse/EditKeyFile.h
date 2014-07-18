/*
 * Copyright 2010 
 * All rights reserved.
 * 
 * Name:EditKeyFile.h
 * Author: ���˸�   
 * Date: 05/29/2010
 * Remarks: �༭KEY�ļ�
 * Revision history:                                 
*/

#if !defined(AFX_EDITKEYFILE_H__6EE33680_8BBA_485A_A32E_704AB70398E5__INCLUDED_)
#define AFX_EDITKEYFILE_H__6EE33680_8BBA_485A_A32E_704AB70398E5__INCLUDED_

#include <vector>
using namespace std;

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/************************************************************************/
/*                        �ඨ��                                        */
/************************************************************************/
class CEditKeyFile  
{
public:
	/*
	����ԭ��:CEditKeyFile();
	����˵��:��
	����ֵ:��
	��������:���캯��
	*/
	CEditKeyFile(void);

	/*
	����ԭ��:virtual ~CEditKeyFile();
	����˵��:��
	����ֵ:��
	��������:��������
	*/
	virtual ~CEditKeyFile(void);

	/*
	����ԭ��:UINT Init(IN CString strFilePath);
	����˵��:
		strFilePath		key�ļ�·��
	����ֵ:�ɹ�����0�� ���򷵻�-1
	��������:��ʼ��
	*/
	UINT Init(IN CString strFilePath);

	/*
	����ԭ��:UINT ReInit(void);
	����˵��:
		����ֵ:�ɹ�����0�� ���򷵻�-1
	��������:���¶�ȡ����
	*/
	UINT ReInit(void);

	/*
	����ԭ��:UINT GetKeyValues(OUT vector<CString> &vstrKeyName, OUT vector<CString> &vstrKeyValue);
	����˵��:
		vstrKeyName  ���ϲ�������
		vstrKeyValue ���ϲ���ֵ
	����ֵ:�ɷ���0 ���򷵻�-1
	��������:ȡ������KEYֵ
	*/
	UINT GetKeyValues(OUT vector<CString> &vstrKeyName, OUT vector<CString> &vstrKeyValue);

	/*
	����ԭ��:UINT GetKeyValue(IN CString strKeyName, OUT CString &strKeyValue);
	����˵��:
		strKeyName  ���ϲ�������
		strKeyValue ���ϲ���ֵ
	����ֵ:�ɷ���0 ���򷵻�-1
	��������:ȡ��KEYֵ
	*/
	UINT GetKeyValue(IN CString strKeyName, OUT CString &strKeyValue);

	/*
	����ԭ��:UINT SetKeyValue(IN CString strKeyName, IN CString strKeyValue);
	����˵��:
		strKeyName  ���ϲ�������
		strKeyValue ���ϲ���ֵ
	����ֵ:�ɷ���0 ���򷵻�-1
	��������:����KEYֵ
	*/
	UINT SetKeyValue(IN CString strKeyName, IN CString strKeyValue);

	/*
	����ԭ��:UINT WriteData(void);
	����˵��:��
	����ֵ:�ɷ���0 ���򷵻�-1
	��������:���޸ĵ�����д��KEY�ļ�
	*/
	UINT WriteData(void);

protected:	
	vector<CString> m_vstrKeyNames;
	vector<CString> m_vstrKeyValues;
	CString			m_strFilePath;

};

#endif // !defined(AFX_EDITKEYFILE_H__6EE33680_8BBA_485A_A32E_704AB70398E5__INCLUDED_)
