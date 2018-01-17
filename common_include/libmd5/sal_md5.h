#ifndef __SAL_MD5_H__
#define __SAL_MD5_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

/*
 �� �� ��: md5_filesum
 ��������: �����ļ���md5ֵ
 �������: _szFilePath �ļ�·��
 �������: sum �ļ���md5ֵ
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int md5_filesum(char* _szFilePath, unsigned char sum[64]);

/*
 �� �� ��: md5_memsum
 ��������: ����buf��md5ֵ
 �������: input ����buf
            len buf�ĳ���
 �������: sum �ļ���md5ֵ
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int md5_memsum(char* input, int len, unsigned char sum[64]);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
