#ifndef http_client_h__
#define http_client_h__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

#include "sal_standard.h"

//socket �������̵߳����
typedef enum
{
    HTTP_STATUS_INVALID = 0,
    HTTP_STATUS_PROGRESS,      //���ڽ�����
    HTTP_STATUS_FINISH_OK,     //���ok
    HTTP_STATUS_FINISH_ERROR,  //���error
    HTTP_STATUS_WRITE_TIMEOUT, //д��ʱ
    HTTP_STATUS_READ_TIMEOUT,  //����ʱ
    HTTP_STATUS_UNKNOWN,
}HTTP_STATUS_E;

/*
 �� �� ��: http_client_init
 ��������: ��ʼ��http�ͻ���ģ��
 �������: szUrl ��Ҫ���ʵ�http url(eg. http://192.168.0.32:8186/uImage)
            timeout ��ʱʱ�䣨ms��
 �������: ��
 �� �� ֵ: �ɹ����ؾ��,ʧ�ܷ���NULL
*/
handle http_client_init(char* szUrl, int timeout);

/*
 �� �� ��: http_client_exit
 ��������: ȥ��ʼ��http�ͻ���ģ��
 �������: hndHttpClient ���
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int http_client_exit(handle hndHttpClient);

/*
 �� �� ��: http_client_Query
 ��������: ��ѯhttp״̬
 �������: hndHttpClient ���
 �������: status ��ѯ״̬
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int http_client_Query(handle hndHttpClient, HTTP_STATUS_E* status);

/*
 �� �� ��: http_client_HeaderGet
 ��������: ��ȡhttp��ͷ��
 �������: hndHttpClient ���
 �������: output ���buffer
            len buffer����
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int http_client_HeaderGet(handle hndHttpClient, unsigned char** output, int* len);

/*
 �� �� ��: http_client_ContentGet
 ��������: ��ȡhttp������
 �������: hndHttpClient ���
 �������: output ���buffer
            len buffer����
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int http_client_ContentGet(handle hndHttpClient, unsigned char** output, int* len);

/*
 �� �� ��: http_client_ProgressGet
 ��������: ��ȡhttp�Ľ���
 �������: hndHttpClient ���
 �������: progress ���ȣ�0-100��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int http_client_ProgressGet(handle hndHttpClient, int* progress);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

