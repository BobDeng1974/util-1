
#ifndef __SAL_COVER_H__
#define __SAL_COVER_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

#define INVALID_REGION_HANDLE       0xffff

typedef struct
{
    int handle;
    int posx;
    int posy;
    int width;
    int height;
}sal_cover_s;


/*
 �� �� ��: sal_cover_create
 ��������: SAL�㴴����Ƶ�ڵ�����

 �������: �ڵ������λ�úʹ�С
 �������:
 �� �� ֵ: ���óɹ�����0, ʧ�ܷ���С��0
*/
int sal_cover_create(sal_cover_s *param);

/*
 �� �� ��: sal_cover_destory
 ��������: SAL��������Ƶ�ڵ�����

 �������:�ڵ������λ�úʹ�С
 �������:
 �� �� ֵ: ���óɹ�����0, ʧ�ܷ���С��0
*/
int sal_cover_destory(sal_cover_s *param);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

