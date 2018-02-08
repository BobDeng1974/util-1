#ifndef sal_mp4record_h__
#define sal_mp4record_h__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

#include "sal_standard.h"

/*
 �� �� ��: mp4EncoderInit
 ��������: ��ʼ��h264����mp4��װ��
 �������: filename �ļ���
            width ��Ƶ��
            height ��Ƶ��
            fps ��Ƶ֡��
 �������: ��
 �� �� ֵ: �ɹ����ط�װ��handle,ʧ�ܷ���NULL
*/
handle mp4EncoderInit(const char * filename,int width,int height, int fps);

/*
 �� �� ��: mp4VEncoderWrite
 ��������: ��mp4��װ��д����Ƶ֡
 �������: hndMp4 ��װ��handle
            frame ��Ƶ֡
            size ��Ƶ֡��С
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int mp4VEncoderWrite(handle hndMp4, unsigned char* frame ,int size);

/*
 �� �� ��: mp4AEncoderWrite
 ��������: ��mp4��װ��д����Ƶ֡
 �������: hndMp4 ��װ��handle
            frame ��Ƶ֡
            size ��Ƶ֡��С
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int mp4AEncoderWrite(handle hndMp4, unsigned char* frame ,int size);

/*
 �� �� ��: mp4Encoderclose
 ��������: �ر�mp4��װ��
 �������: hndMp4 ��װ��handle
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int mp4Encoderclose(handle hndMp4);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif 
