/*
 * Copyright 2010 
 * All rights reserved.
 * 
 * Name:Analyse.h
 * Author: 刘克富   
 * Date: 05/29/2010
 *  Remarks: 
 * Revision history:                                 
*/

#if !defined(AFX_ANALYSE_H__4C9D5088_42CD_41E7_8439_3B0D4AA69334__INCLUDED_)
#define AFX_ANALYSE_H__4C9D5088_42CD_41E7_8439_3B0D4AA69334__INCLUDED_

#include "../excel/excel9.h"
#include "EditKeyFile.h"
#include "SystemSet.h"
#include "../GA/ga/GASimpleGA.h"
#include "../GA/ga/GABin2DecGenome.h"
#include "../GA/ga/std_stream.h"

#include <vector>
#include <map>
using namespace std;

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/************************************************************************/
/*                          宏定义	                                    */
/************************************************************************/
#define MSG_INSERTLOG		WM_USER +101	//添加日志
#define MSG_COMPLETE		WM_USER +102	//分析结束

#define OPTI_DEFALTVAL		100.0f
/************************************************************************/
/*                          结构定义                                    */
/************************************************************************/
typedef struct {
	long nID;			 //编号
	double  dthick;		 //厚度值
	double	dPosX;		 //x坐标
	double	dPosY;		 //y坐标
	double	dPosZ;		 //z坐标
} Type_NodeThick;//测量结果

typedef struct {
	HWND hWnd;				  //窗口句柄
	CString strMeasurPath;	  //试验测量材料参数Excel表路径
	double fDecValue;		  //优化目标值
} Type_ThreadMSG;//测量结果
/************************************************************************/
/*                    分析Key文件类                                     */
/************************************************************************/
class CAnalyse  
{
public:
	/*
	函数原型:CAnalyse(void);
	参数说明:无
	返回值:无
	功能描述:构造函数
	*/
	CAnalyse(void);

	/*
	函数原型:virtual ~CAnalyse(void);
	参数说明:无
	返回值:无
	功能描述:析构函数
	*/
	virtual ~CAnalyse(void);

	/*
	函数原型:static UINT AnalyeKeyFile(LPVOID pParam);
	参数说明:
		pParam		消息参数
	返回值:无
	功能描述:分析key文件的接口函数
	*/	
	static UINT AnalyeKeyFile(IN LPVOID pParam);

	/*
	函数原型:static float Objective(GAGenome& g);
	参数说明:		
	返回值:
	功能描述:遗传算法目标函数
	*/	
	static float Objective(GAGenome& g);
protected:
	CString						m_strAnalyseExePath;//执行分析器目录
	CString						m_strKeyfileName;//key文件的名称
	vector<Type_NodeThick>		m_vMeasures;//测量数据
	vector<Type_NodeThick>		m_vSimulates;//模拟数据
	vector<Type_NodeThick>		m_vNearDatas;//模拟值中与测量值中最接近的点							
	double						m_fDecValue;//优化目标值
	CEditKeyFile				m_EditKeyFile;//key文件
	HWND						m_hWnd;//窗口句柄
	
	vector<CString>				m_vstrKeyNames;
	vector<float>				m_vfKeyValues;

	//key值变化
	CSystemSet					m_SystemSet;
	vector<Type_SystemSet>		m_Systems;
	vector<CString>				m_SystemOptName;

	/*
	函数原型:UINT Configure(void)
	参数说明:无
	返回值:
		成功返回0, 否者返回异常码
	功能描述:将KEY文件和分析器拷贝到临时目录
	*/
	UINT Configure(void);

	/*
	函数原型:UINT ExeCommand(void);
	参数说明:无
	返回值:
		成功返回0, 否者返回异常码
	功能描述:执行分析器
	*/
	UINT ExeCommand(void);

	/*
	函数原型:UINT Configure(void)
	参数说明:
		strMeasureDataPath	文件路径
	返回值:
		成功返回0, 否者返回异常码
	功能描述:读取测量数据
	*/
	UINT ReadMeasureData(IN CString strMeasureDataPath);
	
	/*
	函数原型:void GetMeasureDataFromExcel(Range IN *prgMyRge);
	参数说明:
	prgMyRge				Excel类中的Range类，是一系列单元格的组合。每个Sheet对应着一个Range
	nSheetIndex				表格序号
	使用到的全局变量：
	功能描述:工作簿中读取测量数据
	返回值:无
	*/
	void GetMeasureDataFromExcel(Range IN *prgMyRge);

	/*
	函数原型:void GetStringFromExcel(Range IN *prgMyRge, long IN lRow, long IN lCol, CString OUT &strItem)
	参数说明:
	prgMyRge							Excel信息类
	lRow								行信息
	lCol								列信息
	strItem								第nRow行第nCol列的值
	使用到的全局变量:
	功能描述:将第nRow行第nCol列的值读取出来，并返回出去。之所以返回出去
	返回值:无
	*/
	void GetStringFromExcel(Range IN *prgMyRge, long IN lRow, long IN lCol, CString OUT &strItem);

	/*
	函数原型:double AnalyeDynain(void);
	参数说明:无
	功能描述:从dynain文件中读取节点坐标和厚度，并按照目标函数进行分析
	返回值:求得的优化函数值
	*/
	double AnalyeDynain(void);

	/*
	函数原型:UINT ReadSimulateDataFromDynain(void);
	参数说明:无
	功能描述:从.Dynain文件中读取模拟节点坐标和厚度
	返回值:成功返回0 否则返回-1
	*/
	UINT ReadSimulateDataFromDynain(void);

	/*
	函数原型:void SearchNearPoint(void);
	参数说明:无
	功能描述:从模拟值中查找与测量值最接近的点
	返回值:无
	*/
	void SearchNearPoint(void);

	/*
	函数原型:double OptimizeFunction(void);
	参数说明:无
	功能描述:优化目标函数
	返回值:返回优化函数值
	*/
	double OptimizeFunction(void);
	
};

#endif // !defined(AFX_ANALYSE_H__4C9D5088_42CD_41E7_8439_3B0D4AA69334__INCLUDED_)
