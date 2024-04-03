/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CFactor_ReduceGivenVariable.cpp
//��  �ܣ�		���ݸ����ı�����ֵ���������ӡ����ڼ����������ʷֲ�
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��13��
//��  �£�		2021��03��14��
//��  �£�		2021��03��23��
//��  �£�		2021��03��29��
//��  �ȣ�		50��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CFactor.h"								//������ͷ�ļ�
#include "Helper.h"									//��������ͷ�ļ�


//��  �ƣ�		ReduceGivenVariable()
//��  �ܣ�		���ݸ����ı���ID��ֵID����������
//��  ����		unsigned int,unsigned int
//����ֵ��		��
void CFactor::ReduceGivenVariable(unsigned int nVariableID, unsigned int nValueID)
{
	//��ͬѧ����
    unsigned int nPos = 0;
    if (IsINTInVector(nVariableID, m_VariableIDs,nPos)){
        vector<FACTOR_ROW>::iterator it = m_FactorRows.begin();
        while (it != m_FactorRows.end()){
            if (nValueID == it->ValueIDs[nPos])
                it++;
            else
                it = m_FactorRows.erase(it);
        }
    }
}