/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CFactor.h
//��  �ܣ�		����������
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��12��
//��  �£�		2021��03��13��
//��  �£�		2021��03��29��
//��  �ȣ�		210��
/////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <map>							//mapͷ�ļ�
#include <set>							//setͷ�ļ�
#include <string>						//stringͷ�ļ�
#include <list>							//listͷ�ļ�
#include <vector>						//vectorͷ�ļ�
#include <algorithm>					//algorithm��ͷ�ļ�
#include <numeric>						//numeric��ͷ�ļ�
#include <sstream>						//sstream��ͷ�ļ�
#include <fstream>						//fstream��ͷ�ļ�
#include <time.h>						//ʱ�亯����ͷ�ļ�
#include "math.h"						//��ѧ����ͷ�ļ�
#include "Helper.h"						//��������ͷ�ļ�


//���������ռ�
using namespace std;					//ʹ�ñ�׼�����ռ�


//����������
typedef struct
{
	vector<unsigned int> ValueIDs;								//01 ����ֵID���б����ձ���ID�б��˳������
	double fValue;												//02 ���ӵ�ֵ
}FACTOR_ROW;


//����������
class CFactor
{
	//���캯������������
public:
	CFactor();													//���캯��
	~CFactor();													//��������

	//���з���
public:
	//��ʼ��
	void SetFactorVariableIDs(vector<unsigned int>&);			//�������ӵı���ID�б�
	void SetFactorRow(vector<unsigned int>&, double&);			//���������е�ֵ
	//����
	vector<unsigned int> GetFactorVariableIDs();				//��ȡ����ID�б�
	//����
	void ReduceGivenVariable(unsigned int, unsigned int);		//���ӻ���������������ID���ͱ���ֵID
	void SumOutVariable(unsigned int);								//������͵���������ID
	void Normalize();											//���ӹ�һ��
	//��ѯ
	double Query(vector<unsigned int>&,vector<unsigned int>&);	//���ݸ�������ID���ϡ�����ֵID�ļ��ϣ���ȡ�����ѯ�ĸ���ֵ

	//�������ӻ�
	CFactor operator*(const CFactor& second)
	{
		//�����µġ������ص�����
		CFactor factor;

        //������ͬ����ID���ӵ������ӵ���β����λ�õ�ӳ�䡣�����3��������Ӧ�ڵ�5������
        map<unsigned int, unsigned int> First_S;
        for (unsigned int i = 0; i <m_VariableIDs.size(); i++)
        {
            unsigned int nFirstVID = m_VariableIDs[i];
            for (unsigned int j = 0; j < second.m_VariableIDs.size(); j++){
                unsigned int nSecondVID = second.m_VariableIDs[j];
                if (nFirstVID == nSecondVID)
                    First_S.insert(make_pair(i, j));
            }
        }

        set<unsigned int> Re_seconds;
        for (map<unsigned int, unsigned int>::iterator it = First_S.begin(); it != First_S.end(); it++)
            Re_seconds.insert(it->second);

        if (!First_S.size()){
            for (unsigned int i = 0; i < m_FactorRows.size(); i++)
                for (unsigned int j = 0; j < second.m_FactorRows.size(); ++j){
                    FACTOR_ROW factor_row;
                    factor_row.ValueIDs = m_FactorRows[i].ValueIDs;
                    for (unsigned int m = 0; m < second.m_FactorRows[j].ValueIDs.size(); ++m)
                        factor_row.ValueIDs.push_back(second.m_FactorRows[j].ValueIDs[m]);

                    factor_row.fValue = m_FactorRows[i].fValue*second.m_FactorRows[j].fValue;
                    factor.m_FactorRows.push_back(factor_row);
                }

            factor.m_VariableIDs = m_VariableIDs;
            for (unsigned int i = 0; i < second.m_VariableIDs.size(); ++i)
                factor.m_VariableIDs.push_back(second.m_VariableIDs[i]);
        }

        else {
            for (unsigned int i = 0; i < m_FactorRows.size(); ++i) {
                for (unsigned int j = 0; j < second.m_FactorRows.size(); ++j) {
                    if (IsConsistentValueID(m_FactorRows[i], second.m_FactorRows[j], First_S)) {
                        FACTOR_ROW factor_row;
                        factor_row.ValueIDs = m_FactorRows[i].ValueIDs;
                        for (unsigned int m = 0; m < second.m_FactorRows[j].ValueIDs.size(); m++)
                            if (!IsINTInSet(m, Re_seconds))
                                factor_row.ValueIDs.push_back(second.m_FactorRows[j].ValueIDs[m]);
                        factor_row.fValue = m_FactorRows[i].fValue * second.m_FactorRows[j].fValue;
                        factor.m_FactorRows.push_back(factor_row);
                    }
                }
            }
            factor.m_VariableIDs = m_VariableIDs;
            for (unsigned int i = 0; i < second.m_VariableIDs.size(); ++i)
                if (!IsINTInSet(i, Re_seconds))
                    factor.m_VariableIDs.push_back(second.m_VariableIDs[i]);
        }
		return factor;
	};		
	
	//˽�з���
private:
	//�����ӻ�ʱ�ж������Ƿ���Ժϲ�
	bool IsConsistentValueID(const FACTOR_ROW&, const FACTOR_ROW&, map<unsigned int, unsigned int>&);	//��������Ƿ����	
	//�����ʱ�����ӵ�ֵ�ϲ�������
	void MergeIntoFirstRow(FACTOR_ROW&);
	
	//˽������
private:	
	vector<unsigned int> m_VariableIDs;					//���ӱ���ID�б�
	vector<FACTOR_ROW> m_FactorRows;					//�����е��б�
};