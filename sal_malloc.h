#ifndef __MALLOC_H__
#define __MALLOC_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

#include "sal_standard.h"

//��HEAP_TESTΪ0ʱ���ر��ڴ���
//��HEAP_TESTΪ1ʱ�������ڴ���
//�����ʽ������Ӧ�ÿ����ڴ���
// mem_malloc/mem_realloc����mem_free���ʹ��
#define HEAP_TEST 0

#if HEAP_TEST
#define mem_malloc(size) mem_malloc1(size, __FUNCTION__, __LINE__)
#define mem_realloc(original, size) mem_realloc1(original, size, __FUNCTION__, __LINE__)
#define mem_free(ptr) mem_free1(ptr)
#else
#define mem_malloc(size) malloc(size)
#define mem_realloc(original, size) realloc(original, size)
#define mem_free(ptr) free(ptr)
#endif

/*
 �� �� ��: mem_malloc1
 ��������: �����ڴ棬ֻ��mem_malloc����á��ڲ�ʹ��API
 �������: bytes �����ڴ��С
            func ��������
            line �к�
 �������: ��
 �� �� ֵ: �ɹ������ڴ�ָ��,ʧ�ܷ���NULL
*/
void* mem_malloc1(int bytes, const char* func, int line);

/*
 �� �� ��: mem_realloc1
 ��������: �����ڴ棬ֻ��mem_realloc����á��ڲ�ʹ��API
 �������:  original ԭ���Ķ��ڴ�ָ��
            new_bytes ���������ڴ��С
            func ��������
            line �к�
 �������: ��
 �� �� ֵ: �ɹ������ڴ�ָ��,ʧ�ܷ���NULL
*/
void* mem_realloc1(void* original, int new_bytes, const char* func, int line);

/*
 �� �� ��: mem_free1
 ��������: �ͷ��ڴ棬ֻ��mem_free����á��ڲ�ʹ��API
 �������:  ptr ���ڴ�ָ��
 �������: ��
 �� �� ֵ: ��
*/
void mem_free1(void* ptr);

/*
 �� �� ��: mem_get_malloc_sum
 ��������: ��ȡ�ѶԶ��ڴ�������ܴ�С
 �������: ��
 �������: ��
 �� �� ֵ: �ɹ����ض��ڴ�������ܴ�С,ʧ�ܷ���С��0
*/
int mem_get_malloc_sum();

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

