/*
 * Copyright 2010 
 * All rights reserved.
 * 
 * Name:SystemSet.h
 * Author: 刘克富   
 * Date: 05/29/2010
 * Remarks: 系统参数设置
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
/*                                结构定义                              */
/************************************************************************/
typedef struct {
	char szShortCaption[32]; //材料参数简称
	char szCaption[32];		 //材料参数名称
	char dUpStep[32];		 //向上搜索值
	char dDownStep[32];		 //向下搜索值
	BYTE	bIsReverse;		 //是否反求
} Type_SystemSet;//材料参数

/************************************************************************/
/*                              CSystemSet                              */
/************************************************************************/
class CSystemSet  
{
public:
	/*
	函数原型:
	参数说明:无
	返回值:无
	功能描述:构造函数
	*/
	CSystemSet();

	/*
	函数原型:
	参数说明:无
	返回值:无
	功能描述:析构函数
	*/
	virtual ~CSystemSet();

	/*
	函数原型:UINT Init(void);
	参数说明:
	返回值:成功返回0，否者返回异常码
	功能描述:初始化
	*/
	UINT Init(void);

	/*
	函数原型:UINT GetSystem(OUT vector<Type_SystemSet> &vSystem);
	参数说明:
		vSystem		系统参数
	返回值:成功返回0 否者返回异常码
	功能描述:取得系统参数
	*/
	UINT GetSystem(OUT vector<Type_SystemSet> &vSystem);

	CXMLBase				m_xml;

protected:

	vector<Type_SystemSet>	m_system;
};

#endif // !defined(AFX_SYSTEMSET_H__D88B0574_18CC_4A28_926D_A41BAB02B48C__INCLUDED_)
