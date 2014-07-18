/*
 * Copyright 2010 
 * All rights reserved.
 * 
 * Name:Analyse.h
 * Author: ���˸�   
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
/*                          �궨��	                                    */
/************************************************************************/
#define MSG_INSERTLOG		WM_USER +101	//�����־
#define MSG_COMPLETE		WM_USER +102	//��������

#define OPTI_DEFALTVAL		100.0f
/************************************************************************/
/*                          �ṹ����                                    */
/************************************************************************/
typedef struct {
	long nID;			 //���
	double  dthick;		 //���ֵ
	double	dPosX;		 //x����
	double	dPosY;		 //y����
	double	dPosZ;		 //z����
} Type_NodeThick;//�������

typedef struct {
	HWND hWnd;				  //���ھ��
	CString strMeasurPath;	  //����������ϲ���Excel��·��
	double fDecValue;		  //�Ż�Ŀ��ֵ
} Type_ThreadMSG;//�������
/************************************************************************/
/*                    ����Key�ļ���                                     */
/************************************************************************/
class CAnalyse  
{
public:
	/*
	����ԭ��:CAnalyse(void);
	����˵��:��
	����ֵ:��
	��������:���캯��
	*/
	CAnalyse(void);

	/*
	����ԭ��:virtual ~CAnalyse(void);
	����˵��:��
	����ֵ:��
	��������:��������
	*/
	virtual ~CAnalyse(void);

	/*
	����ԭ��:static UINT AnalyeKeyFile(LPVOID pParam);
	����˵��:
		pParam		��Ϣ����
	����ֵ:��
	��������:����key�ļ��Ľӿں���
	*/	
	static UINT AnalyeKeyFile(IN LPVOID pParam);

	/*
	����ԭ��:static float Objective(GAGenome& g);
	����˵��:		
	����ֵ:
	��������:�Ŵ��㷨Ŀ�꺯��
	*/	
	static float Objective(GAGenome& g);
protected:
	CString						m_strAnalyseExePath;//ִ�з�����Ŀ¼
	CString						m_strKeyfileName;//key�ļ�������
	vector<Type_NodeThick>		m_vMeasures;//��������
	vector<Type_NodeThick>		m_vSimulates;//ģ������
	vector<Type_NodeThick>		m_vNearDatas;//ģ��ֵ�������ֵ����ӽ��ĵ�							
	double						m_fDecValue;//�Ż�Ŀ��ֵ
	CEditKeyFile				m_EditKeyFile;//key�ļ�
	HWND						m_hWnd;//���ھ��
	
	vector<CString>				m_vstrKeyNames;
	vector<float>				m_vfKeyValues;

	//keyֵ�仯
	CSystemSet					m_SystemSet;
	vector<Type_SystemSet>		m_Systems;
	vector<CString>				m_SystemOptName;

	/*
	����ԭ��:UINT Configure(void)
	����˵��:��
	����ֵ:
		�ɹ�����0, ���߷����쳣��
	��������:��KEY�ļ��ͷ�������������ʱĿ¼
	*/
	UINT Configure(void);

	/*
	����ԭ��:UINT ExeCommand(void);
	����˵��:��
	����ֵ:
		�ɹ�����0, ���߷����쳣��
	��������:ִ�з�����
	*/
	UINT ExeCommand(void);

	/*
	����ԭ��:UINT Configure(void)
	����˵��:
		strMeasureDataPath	�ļ�·��
	����ֵ:
		�ɹ�����0, ���߷����쳣��
	��������:��ȡ��������
	*/
	UINT ReadMeasureData(IN CString strMeasureDataPath);
	
	/*
	����ԭ��:void GetMeasureDataFromExcel(Range IN *prgMyRge);
	����˵��:
	prgMyRge				Excel���е�Range�࣬��һϵ�е�Ԫ�����ϡ�ÿ��Sheet��Ӧ��һ��Range
	nSheetIndex				������
	ʹ�õ���ȫ�ֱ�����
	��������:�������ж�ȡ��������
	����ֵ:��
	*/
	void GetMeasureDataFromExcel(Range IN *prgMyRge);

	/*
	����ԭ��:void GetStringFromExcel(Range IN *prgMyRge, long IN lRow, long IN lCol, CString OUT &strItem)
	����˵��:
	prgMyRge							Excel��Ϣ��
	lRow								����Ϣ
	lCol								����Ϣ
	strItem								��nRow�е�nCol�е�ֵ
	ʹ�õ���ȫ�ֱ���:
	��������:����nRow�е�nCol�е�ֵ��ȡ�����������س�ȥ��֮���Է��س�ȥ
	����ֵ:��
	*/
	void GetStringFromExcel(Range IN *prgMyRge, long IN lRow, long IN lCol, CString OUT &strItem);

	/*
	����ԭ��:double AnalyeDynain(void);
	����˵��:��
	��������:��dynain�ļ��ж�ȡ�ڵ�����ͺ�ȣ�������Ŀ�꺯�����з���
	����ֵ:��õ��Ż�����ֵ
	*/
	double AnalyeDynain(void);

	/*
	����ԭ��:UINT ReadSimulateDataFromDynain(void);
	����˵��:��
	��������:��.Dynain�ļ��ж�ȡģ��ڵ�����ͺ��
	����ֵ:�ɹ�����0 ���򷵻�-1
	*/
	UINT ReadSimulateDataFromDynain(void);

	/*
	����ԭ��:void SearchNearPoint(void);
	����˵��:��
	��������:��ģ��ֵ�в��������ֵ��ӽ��ĵ�
	����ֵ:��
	*/
	void SearchNearPoint(void);

	/*
	����ԭ��:double OptimizeFunction(void);
	����˵��:��
	��������:�Ż�Ŀ�꺯��
	����ֵ:�����Ż�����ֵ
	*/
	double OptimizeFunction(void);
	
};

#endif // !defined(AFX_ANALYSE_H__4C9D5088_42CD_41E7_8439_3B0D4AA69334__INCLUDED_)
