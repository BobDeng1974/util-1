#ifndef __LIST_H__
#define __LIST_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

#include "sal_standard.h"

/*
 �� �� ��: list_init
 ��������: ��ʼ��һ��˫����������list_destroy���ʹ��
 �������:  _s32NodeDataSize ����ڵ��ŵ����ݴ�С
 �������: ��
 �� �� ֵ: �ɹ�����������,ʧ�ܷ���NULL
*/
handle list_init(int _s32NodeDataSize);

/*
 �� �� ��: list_destroy
 ��������: ȥ��ʼ��һ��˫����������list_init���ʹ��
 �������:  _hndList ������
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int list_destroy(handle _hndList);

/*
 �� �� ��: list_push_front
 ��������: ������ͷ������һ���ڵ�
 �������:  _hndList ������
            _pData �ڵ�����
            _s32DataSize �ڵ��С
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int list_push_front(handle _hndList, void* _pData, int _s32DataSize);

/*
 �� �� ��: list_push_back
 ��������: ������β������һ���ڵ�
 �������:  _hndList ������
            _pData �ڵ�����
            _s32DataSize �ڵ��С
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int list_push_back(handle _hndList, void* _pData, int _s32DataSize);

/*
 �� �� ��: list_del
 ��������: ��������ɾ��ָ���ڵ�
 �������:  _hndList ������
            pData ��ɾ���Ľڵ�
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int list_del(handle _hndList, void* pData);

/*
 �� �� ��: list_pop_front
 ��������: ������ͷ��ɾ��һ���ڵ�
 �������:  _hndList ������
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int list_pop_front(handle _hndList);

/*
 �� �� ��: list_pop_back
 ��������: ������β��ɾ��һ���ڵ�
 �������:  _hndList ������
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int list_pop_back(handle _hndList);

/*
 �� �� ��: list_clear
 ��������: ɾ���������нڵ�
 �������:  _hndList ������
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int list_clear(handle _hndList);

/*
 �� �� ��: list_size
 ��������: ��ȡ�����нڵ����Ŀ
 �������:  _hndList ������
 �������: ��
 �� �� ֵ: �ɹ�����������Ŀ,ʧ�ܷ���С��0
*/
int list_size(handle _hndList);

/*
 �� �� ��: list_front
 ��������: ��ȡ������ͷ�ڵ�
 �������:  _hndList ������
 �������: ��
 �� �� ֵ: �ɹ����ؽڵ�,ʧ�ܷ���NULL
*/
void* list_front(handle _hndList);

/*
 �� �� ��: list_back
 ��������: ��ȡ������β�ڵ�
 �������:  _hndList ������
 �������: ��
 �� �� ֵ: �ɹ����ؽڵ�,ʧ�ܷ���NULL
*/
void* list_back(handle _hndList);

/*
 �� �� ��: list_next
 ��������: ��ȡ�����к�һ���ڵ�
 �������:  _hndList ������
            pData �ڵ�
 �������: ��
 �� �� ֵ: �ɹ����ؽڵ�,ʧ�ܷ���NULL
*/
void* list_next(handle _hndList, void* pData);

/*
 �� �� ��: list_prev
 ��������: ��ȡ������ǰһ���ڵ�
 �������:  _hndList ������
            pData �ڵ�
 �������: ��
 �� �� ֵ: �ɹ����ؽڵ�,ʧ�ܷ���NULL
*/
void* list_prev(handle _hndList, void* pData);

/*
 �� �� ��: list_empty
 ��������: �����Ƿ�Ϊ��
 �������:  _hndList ������
 �������: ��
 �� �� ֵ: �ɹ�������,ʧ�ܷ��ؼ�
*/
int list_empty(handle _hndList);

/*
 �� �� ��: list_exist
 ��������: �ڵ��Ƿ����������
 �������:  _hndList ������
            pData �ڵ�
 �������: ��
 �� �� ֵ: �ɹ�������,ʧ�ܷ��ؼ�
*/
int list_exist(handle _hndList, void* pData);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

