/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CFactor_Normalize.cpp
//��  �ܣ�		�淶������
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��15��
//��  �£�		2021��03��23��
//��  �£�		2021��03��29��
//��  �ȣ�		40��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CFactor.h"								//������ͷ�ļ�
#include "Helper.h"									//��������ͷ�ļ�


//��  �ƣ�		Normalize()
//��  �ܣ�		�淶������
//��  ����		��
//����ֵ��		��
void CFactor::Normalize()
{
    //����
    float Normal_num = 0.0f;
    for (unsigned int i = 0; i < m_FactorRows.size(); ++i)
        Normal_num += m_FactorRows[i].fValue;

    for (unsigned int i = 0; i < m_FactorRows.size(); ++i)
        m_FactorRows[i].fValue /= Normal_num;
}