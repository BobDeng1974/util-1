#ifndef __CACHE_H__
#define __CACHE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

#include "sal_standard.h"

/*
 �� �� ��: cache_init
 ��������: ��ʼ������ģ�飬����cache_destroy���ʹ��
 �������: size ���õĻ����С
 �������: ��
 �� �� ֵ: �ɹ����ػ�����,ʧ�ܷ���NULL
*/
handle cache_init(int size);

/*
 �� �� ��: cache_init
 ��������: ȥ��ʼ������ģ�飬����cache_init���ʹ��
 �������: hndcache ������
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int cache_destroy(handle hndcache);

/*
 �� �� ��: cache_writable
 ��������: ��ȡ�����д����ʼ��ַ�Լ���д����
 �������: hndcache ������
 �������: begin ��д����ʼ��ַ
            len ��д����
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int cache_writable(handle hndcache, void** begin, int* len);

/*
 �� �� ��: cache_readable
 ��������: ��ȡ����ɶ�����ʼ��ַ�Լ��ɶ�����
 �������: hndcache ������
 �������: begin �ɶ�����ʼ��ַ
            len �ɶ�����
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int cache_readable(handle hndcache, void** begin, int* len);

/*
 �� �� ��: cache_offset_writable
 ��������: ���Ի������д����������ô˽ӿڸ��߻���ģ��Կ�д��ַ����ƫ��
 �������: hndcache ������
            length ��д����
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int cache_offset_writable(handle hndcache, int length);

/*
 �� �� ��: cache_offset_readable
 ��������: ���Ի�����ж�����������ô˽ӿڸ��߻���ģ��Կɶ���ַ����ƫ��
 �������: hndcache ������
            length �Ѷ�����
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int cache_offset_readable(handle hndcache, int length);

/*
 �� �� ��: cache_clean
 ��������: ���Ի�����ж�ζ�д����������ô˽ӿ������Ѷ�ȡ������
 �������: hndcache ������
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int cache_clean(handle hndcache);

/*
 �� �� ��: cache_reset
 ��������: ���û���Ķ�дλ�ã���0��ʼ��
 �������: hndcache ������
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int cache_reset(handle hndcache);

/*
 �� �� ��: cache_debug
 ��������: �Ƿ�ʹ�ܻ���ģ���ڵĴ�ӡ��Ϣ��Ĭ��Ϊfalse
 �������: hndcache ������
            enable ʹ�ܱ�־
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int cache_debug(handle hndcache, int enable);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif


