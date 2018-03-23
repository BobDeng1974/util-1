#ifndef __SAL_UTIL_H__
#define __SAL_UTIL_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

#include "sal_standard.h"

/*
 �� �� ��: util_time_abs
 ��������: ��ȡϵͳ����ʱ��
 �������: ��
 �������: pTime ϵͳ����ʱ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int util_time_abs(struct timeval* pTime);

/*
 �� �� ��: util_time_local
 ��������: ��ȡϵͳʱ��ʱ��
 �������: ��
 �������: pTime ϵͳ����ʱ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int util_time_local(struct timeval* pTime);

/*
 �� �� ��: util_time_sub
 ��������: ��ȡʱ����λ���룩
 �������: pStart ��ʼʱ��
            pEnd ����ʱ��
 �������: ��
 �� �� ֵ: �ɹ�����ʱ���(ms),ʧ�ܷ���С��0
*/
int util_time_sub(struct timeval* pStart, struct timeval* pEnd);

/*
 �� �� ��: util_time_sub
 ��������: ��ȡ֮ǰ��ʱ���뵱ǰ��ʱ����λ���룩
 �������: previous ֮ǰ��ʱ�䣨��ʼʱ�䣩
 �������: ��
 �� �� ֵ: �ɹ�����ʱ���(ms),ʧ�ܷ���С��0
*/
int util_time_pass(struct timeval* previous);

/*
 �� �� ��: util_file_size
 ��������: ��ȡ�ļ���С
 �������: path �ļ�·��
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int util_file_size(char* path);

/*
 �� �� ��: util_file_read
 ��������: ��ȡ�ļ��е�����
 �������: path �ļ�·��
            len �������󳤶�
 �������: buf �������
 �� �� ֵ: �ɹ������Ѷ�ȡ��С,ʧ�ܷ���С��0
*/
int util_file_read(const char* path, unsigned char* buf, int len);

/*
 �� �� ��: util_file_write
 ��������: ��һ���ڴ�д���ļ���
 �������: path �ļ�·��
            buf buffer�ڴ�
            len �������󳤶�
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int util_file_write(const char* path, unsigned char* buf, int len);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
