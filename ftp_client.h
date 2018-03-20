
#ifndef ftp_client_h__
#define ftp_client_h__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

#include "sal_standard.h"


//socket �������̵߳����
typedef enum FTP_STATUS_E
{
    FTP_STATUS_INVALID = 0,
    FTP_STATUS_PROGRESS,      //���ڽ�����
    FTP_STATUS_FINISH_OK,     //���ok
    FTP_STATUS_FINISH_ERROR,  //���error
    FTP_STATUS_WRITE_TIMEOUT, //д��ʱ
    FTP_STATUS_READ_TIMEOUT,  //����ʱ
    FTP_STATUS_UNKNOWN,
}FTP_STATUS_E;

/*
 �� �� ��: ftp_client_init
 ��������: ��ʼ��ftp�ͻ���ģ��
 �������: szHost ��Ҫ���ʵ�FTP Server������ip
            portCmd ftp �˿�Ĭ��Ϊ21
            szUserName �û���
            szPassword ����
 �������: ��
 �� �� ֵ: �ɹ����ؾ��,ʧ�ܷ���NULL
*/
handle ftp_client_init(char* szHost, int portCmd, char* szUserName, char* szPassword);

/*
 �� �� ��: ftp_client_exit
 ��������: ȥ��ʼ��ftp�ͻ���ģ��
 �������: hndftpClient ���
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int ftp_client_exit(handle hndftpClient);

/*
 �� �� ��: ftp_client_startGet
 ��������: ftpget �����ļ�
 �������: hndftpClient ���
            szFileName �ļ���
            timeout ��ʱʱ�䣨���룩
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int ftp_client_startGet(handle hndftpClient, char* szFileName, int timeout);

/*
 �� �� ��: ftp_client_startPut
 ��������: ftpput �ϴ��ļ�
 �������: hndftpClient ���
            buffer �ļ�buffer
            len �ļ�����
            szRemoteFileName �ϴ���ftp���������ļ���
            timeout ��ʱʱ�䣨���룩
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int ftp_client_startPut(handle hndftpClient, unsigned char* buffer, int len, char* szRemoteFileName, int timeout);

/*
 �� �� ��: ftp_client_stop
 ��������: ֹͣ�ϴ������أ��ͷ���Դ
 �������: hndftpClient ���
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int ftp_client_stop(handle hndftpClient);

/*
 �� �� ��: ftp_client_Query
 ��������: ��ѯftp״̬
 �������: hndftpClient ���
 �������: status ��ѯ״̬
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int ftp_client_Query(handle hndftpClient, FTP_STATUS_E* status);

/*
 �� �� ��: ftp_client_ContentGet
 ��������: ��ȡftpget�����ݣ������ļ���
 �������: hndftpClient ���
 �������: output ���buffer
            len buffer����
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int ftp_client_ContentGet(handle hndftpClient, unsigned char** output, int* len);

/*
 �� �� ��: ftp_client_ProgressGet
 ��������: ��ȡftpget/ftpput�Ľ���
 �������: hndftpClient ���
 �������: progress ���ȣ�0-100��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int ftp_client_ProgressGet(handle hndftpClient, int* progress);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

