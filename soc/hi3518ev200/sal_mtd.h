#ifndef __SAL_MTD_H__
#define __SAL_MTD_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

#include "sal_standard.h"

/*
 �� �� ��: sal_mtd_erase
 ��������: �ӷ�����ʼ��ַ��ʼ����mtd����
 �������: devicename �����ڵ㣨eg. /dev/mtd0��
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int sal_mtd_erase(char *devicename);

/*
 �� �� ��: sal_mtd_rerase
 ��������: �ӷ���ĩ�˵�ַ��ʼ�������mtd����
 �������: devicename �����ڵ㣨eg. /dev/mtd0��
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int sal_mtd_rerase(char *devicename);

/*
 �� �� ��: sal_mtd_write
 ��������: д����
 �������:  filebuf ��д�������
            filesize ���ݴ�С
            devicename �����ڵ㣨eg. /dev/mtd0��
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int sal_mtd_write(char *filebuf, int filesize, char *devicename);

/*
 �� �� ��: sal_mtd_verify
 ��������: ��֤�����ڵ�������Ƿ���filebufһ��
 �������:  filebuf ����֤������
            filesize ���ݴ�С
            devicename �����ڵ㣨eg. /dev/mtd0��
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int sal_mtd_verify(char *filebuf, int filesize, char *devicename);

/*
 �� �� ��: sal_mtd_readflag
 ��������: ��ȡ����ĩ4�ֽڵ����ݣ�����ϵͳ˫����ʱʹ��
 �������:  len ����output����󳤶�
            devicename �����ڵ㣨eg. /dev/mtd0��
 �������: output ���4�ֽ�����
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int sal_mtd_readflag(char *devicename, char* output, int len);

/*
 �� �� ��: sal_mtd_writeflag
 ��������: д����ĩ4�ֽڵ����ݣ�����ϵͳ˫����ʱʹ��
 �������:  input ����4�ֽڵ�����
            len ����output����󳤶�
            devicename �����ڵ㣨eg. /dev/mtd0��
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int sal_mtd_writeflag(char *devicename, char* input, int len);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

