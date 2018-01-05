
#ifndef __SAL_JPEG_H__
#define __SAL_JPEG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif



/*
 �� �� ��: sal_jpeg_cb
 ��������: jpeg֡�ص�����
 �������: ��
 �������: frame ��Ƶ֡
            len ֡��С
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
typedef int (*sal_jpeg_cb)(char *frame, int len);


/*
 �� �� ��: sal_jpeg_init
 ��������: SAL��JPEG����ʹ��
 �������: cb �ص�����
 �������:
 �� �� ֵ: ���óɹ�����0, ʧ�ܷ���С��0
*/
int sal_jpeg_init(sal_jpeg_cb cb);

/*
 �� �� ��: sal_jpeg_exit
 ��������: SAL��JPEG����ȥ��ʼ�����ͷ���Դ
 �������: cb �ص�����
 �������:
 �� �� ֵ: ���óɹ�����0, ʧ�ܷ���С��0
*/
int sal_jpeg_exit();





#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

