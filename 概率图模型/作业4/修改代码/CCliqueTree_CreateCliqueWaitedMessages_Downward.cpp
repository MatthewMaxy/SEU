/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CCliqueTree_CreateCliqueWaitedMessages_Downward.cpp
//��  �ܣ�		���´�����Ϣʱ�������ŵĵȴ���Ϣ����
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��04��04��
//��  �£�		2021��05��18��
//��  �ȣ�		70��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CCliqueTree.h"							//������ȷ������ͷ�ļ�
#include "Helper.h"									//��������ͷ�ļ�


//��  �ƣ�		CreateCliqueWaitedMessages_Downward()
//��  �ܣ�		���´�����Ϣʱ�������ŵĵȴ���Ϣ����
//��  ����		map<unsigned int,set<unsigned int>>&
//����ֵ��		��
void CCliqueTree::CreateCliqueWaitedMessages_Downward(map<unsigned int, set<unsigned int>>& WaitedMessages)
{
	////////////////////////////////////////////////////////////////////////////////
	//����1�����������ţ���ʼ�����´�����Ϣʱ���ŵĵȴ���Ϣ����Ϊ��
    for (unsigned int i = 0; i < m_CTNodes.size(); i++){
		unsigned int Clique_id= m_CTNodes[i].nID;
		set<unsigned int> null_Message;
		WaitedMessages.insert(make_pair(Clique_id, null_Message));
	}
	for (map<unsigned int, unsigned int>::iterator it = m_UpwardTree.begin(); it != m_UpwardTree.end(); it++){
		unsigned int Parent_id= it->first;
		unsigned int Clique_id= it->second;
		InsertToWaitedMessages(Parent_id, Clique_id, WaitedMessages);
	}
}