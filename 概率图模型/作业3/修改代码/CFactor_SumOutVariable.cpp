/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CFactor_SumOutVariable.cpp
//��  �ܣ�		���ݸ������������������
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��13��
//��  �£�		2021��03��23��
//��  �£�		2021��03��29��
//��  �ȣ�		150��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CFactor.h"								//������ͷ�ļ�
#include "Helper.h"									//��������ͷ�ļ�


//��  �ƣ�		SumOutVariable()
//��  �ܣ�		���ݸ������������������
//��  ����		unsigned int
//����ֵ��		��
void CFactor::SumOutVariable(unsigned int nVariableID)
{
	//��ͬѧ����
    unsigned int nRemovePos = 0;
    if (IsINTInVector(nVariableID, m_VariableIDs, nRemovePos))
    {
        vector<unsigned int>::iterator it = m_VariableIDs.begin();
        unsigned int nCurPos = 0;
        while (it != m_VariableIDs.end()){
            if (nCurPos == nRemovePos){
                it = m_VariableIDs.erase(it);
                break;
            }
            else{
                nCurPos++;
                it++;
            }
        }

        for (unsigned int i = 0; i < m_FactorRows.size(); i++){
            vector<unsigned int>::iterator it = m_FactorRows[i].ValueIDs.begin();
            unsigned int nCurPos = 0;
            while (it != m_FactorRows[i].ValueIDs.end()){
                if (nCurPos == nRemovePos){
                    it = m_FactorRows[i].ValueIDs.erase(it);
                    break;
                }
                else{
                    nCurPos++;
                    it++;
                }
            }
        }

        vector<FACTOR_ROW> FactorRows;
        while (m_FactorRows.size()>0)
        {
            FACTOR_ROW first_row = m_FactorRows[0];
            MergeIntoFirstRow(first_row);
            FactorRows.push_back(first_row);
        }
        m_FactorRows = FactorRows;
    }
}

//��  �ƣ�		MergeIntoFirstRow()
//��  �ܣ�		�ۻ�����ֵ������
//��  ����		FACTOR_ROW&
//����ֵ��		��
void CFactor::MergeIntoFirstRow(FACTOR_ROW& first_row)
{
	//��������������
	vector<FACTOR_ROW>::iterator it = m_FactorRows.begin();

	//ɾ������
	it = m_FactorRows.erase(it);

	//����Ƿ����
	while (it != m_FactorRows.end())
	{
		//������ֵID���б��Ƿ����
		if (first_row.ValueIDs == it->ValueIDs)
		{
			//�ۼ�����ֵ
			first_row.fValue += it->fValue;

			//ɾ���������µ�����
			it = m_FactorRows.erase(it);
		}
		else
		{
			//���µ�����
			it++;
		}
	}
}