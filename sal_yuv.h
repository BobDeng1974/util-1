
#ifndef __SAL_YUV_H__
#define __SAL_YUV_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif


/*****************************************************************************
 �� �� ��: sal_yuv_get
 ��������  : SAL���ȡͨ��yuv sp420
 �������  : stream ͨ��id
            buffer ����buffer��������Ҫ���� width*height*1.5 ��С���ڴ�
            len     ����buffer�ĳ��ȣ�
            ��bufferС�������С��ֱ�ӷ���ʧ��
 �������  :
 �� �� ֵ: �ɹ�����yuv��ʵ�ʴ�С, ʧ�ܷ���С��0
*****************************************************************************/
int sal_yuv_get(int stream, char* buffer, int len);





#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

