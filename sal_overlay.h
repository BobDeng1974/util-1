
#ifndef __SAL_OVERLAY_H__
#define __SAL_OVERLAY_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

#define	RGB_VALUE_BLACK	    0x8000
#define	RGB_VALUE_WHITE		0xffff
#define	RGB_VALUE_RED		0xfc00

typedef struct
{
    int stream_id;                      /* stream id, attached encode channel */
    int handle;                         /* region handle */
    int posx;                           /* osd location x */
    int posy;                           /* osd location y */
    int width;                          /* pixel size of width */
    int height;                         /* pixel size of height */
    int factor;                         /* font size */
    int font_color;                     /*������ɫ*/
    int edge_color;                     /*�߿���ɫ*/
    void* bitmap_data;                  /*address of bitmap's data*/
}sal_overlay_s;

#define INVALID_REGION_HANDLE       0xffff


/*****************************************************************************
 �� �� ��: sal_overlay_create
 ��������  : SAL�㴴����Ƶ��������

 �������  : overlay��λ�ã���С��
 �������  :
 �� �� ֵ: ���óɹ�����0, ʧ�ܷ���С��0
*****************************************************************************/
int sal_overlay_create(sal_overlay_s *param);


/*****************************************************************************
 �� �� ��: sal_overlay_destory
 ��������  : SAL��������Ƶ��������

 �������  : overlay��λ�ã���С��
 �������  :
 �� �� ֵ: �ɹ�����0, ʧ�ܷ���С��0
*****************************************************************************/
int sal_overlay_destory(sal_overlay_s *param);


/*****************************************************************************
 �� �� ��: sal_overlay_refresh_bitmap
 ��������  : SAL��ˢ����Ƶ��������λͼ

 �������  : overlayλͼ��С������
 �������  :
 �� �� ֵ: �ɹ�����0, ʧ�ܷ���С��0
*****************************************************************************/
int sal_overlay_refresh_bitmap(sal_overlay_s *param);





#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

