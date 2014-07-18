/*
 * Copyright 2010 
 * All rights reserved.
 * 
 * Name:EditKeyFile.h
 * Author: 刘克富   
 * Date: 05/29/2010
 * Remarks: 编辑KEY文件
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
/*                        类定义                                        */
/************************************************************************/
class CEditKeyFile  
{
public:
	/*
	函数原型:CEditKeyFile();
	参数说明:无
	返回值:无
	功能描述:构造函数
	*/
	CEditKeyFile(void);

	/*
	函数原型:virtual ~CEditKeyFile();
	参数说明:无
	返回值:无
	功能描述:析构函数
	*/
	virtual ~CEditKeyFile(void);

	/*
	函数原型:UINT Init(IN CString strFilePath);
	参数说明:
		strFilePath		key文件路径
	返回值:成功返回0， 否则返回-1
	功能描述:初始化
	*/
	UINT Init(IN CString strFilePath);

	/*
	函数原型:UINT ReInit(void);
	参数说明:
		返回值:成功返回0， 否则返回-1
	功能描述:重新读取数据
	*/
	UINT ReInit(void);

	/*
	函数原型:UINT GetKeyValues(OUT vector<CString> &vstrKeyName, OUT vector<CString> &vstrKeyValue);
	参数说明:
		vstrKeyName  材料参数名称
		vstrKeyValue 材料参数值
	返回值:成返回0 否则返回-1
	功能描述:取得所有KEY值
	*/
	UINT GetKeyValues(OUT vector<CString> &vstrKeyName, OUT vector<CString> &vstrKeyValue);

	/*
	函数原型:UINT GetKeyValue(IN CString strKeyName, OUT CString &strKeyValue);
	参数说明:
		strKeyName  材料参数名称
		strKeyValue 材料参数值
	返回值:成返回0 否则返回-1
	功能描述:取得KEY值
	*/
	UINT GetKeyValue(IN CString strKeyName, OUT CString &strKeyValue);

	/*
	函数原型:UINT SetKeyValue(IN CString strKeyName, IN CString strKeyValue);
	参数说明:
		strKeyName  材料参数名称
		strKeyValue 材料参数值
	返回值:成返回0 否则返回-1
	功能描述:设置KEY值
	*/
	UINT SetKeyValue(IN CString strKeyName, IN CString strKeyValue);

	/*
	函数原型:UINT WriteData(void);
	参数说明:无
	返回值:成返回0 否则返回-1
	功能描述:将修改的数据写入KEY文件
	*/
	UINT WriteData(void);

protected:	
	vector<CString> m_vstrKeyNames;
	vector<CString> m_vstrKeyValues;
	CString			m_strFilePath;

};

#endif // !defined(AFX_EDITKEYFILE_H__6EE33680_8BBA_485A_A32E_704AB70398E5__INCLUDED_)
