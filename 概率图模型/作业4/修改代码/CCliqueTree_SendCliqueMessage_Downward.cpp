/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CCliqueTree_SendCliqueMessage_Downward.cpp
//��  �ܣ�		���·�������Ϣ
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��04��04��
//��  �£�		2021��05��18��
//��  �ȣ�		60��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CCliqueTree.h"							//������ȷ������ͷ�ļ�
#include "Helper.h"									//��������ͷ�ļ�


//��  �ƣ�		SendCliqueMessage_Downward()
//��  �ܣ�		���·�������Ϣ
//��  ����		unsigned int
//����ֵ��		��
void CCliqueTree::SendCliqueMessage_Downward(unsigned int nID,unsigned int nChildID)
{
	//�ҵ��ཻ�ı���ID����
	set<unsigned int> CommonVariableIDs;

	//��ȡ�����ŵı���ID����
	FindCommonVariableIDs(nID, nChildID, CommonVariableIDs);
    unsigned int nPos = GetCliquePosByID(nChildID);
    set<unsigned int> Clique_ids = m_Cliques[nChildID].GetVariableIDs();
    set<unsigned int> Eliminate_ids;
    SubtractBetweenSets(Clique_ids, CommonVariableIDs, Eliminate_ids);

    SEP_SET sep_set;
    sep_set.nStartID = nChildID;
    sep_set.nEndID = nID;
    sep_set.clique = m_Cliques[nPos];
    sep_set.bReady = true;

    for (set<unsigned int>::iterator it = Eliminate_ids.begin(); it != Eliminate_ids.end(); it++)
        sep_set.clique.SumOutVariable(*it);
    m_SEPSets.push_back(sep_set);
}