
#ifndef sal_vgs_h__
#define sal_vgs_h__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

#include "hi_comm.h"

typedef struct rectangle_s
{
    int x;      //������������
    int y;      //�������������
    int width;  //���ο��
    int height; //���θ߶�
}rectangle_s;

/*
 �� �� ��: sal_vgs_draw_rectangle
 ��������: ������
 �������: pstOutFrameInfo ֡��Ϣ��һ���vpssģ���ȡ
            u32Thick �߿� 2�ֽڶ���
            u32Color ��ɫ ��3�ֽڱ�ʾRGB eg.0x00FF00EE R: FF, G: 00, B: EE
            x ������������
            y �������������
            width ���ο��
            height ���θ߶�
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int sal_vgs_draw_rectangle(VIDEO_FRAME_INFO_S* pstOutFrameInfo, unsigned int u32Thick, unsigned int u32Color
                           , int x, int y, int width, int height);

/*
 �� �� ��: sal_vgs_draw_rectangle
 ��������: �����Σ������
 �������: pstOutFrameInfo ֡��Ϣ��һ���vpssģ���ȡ
            u32Thick �߿� 2�ֽڶ���
            u32Color ��ɫ ��3�ֽڱ�ʾRGB eg.0x00FF00EE R: FF, G: 00, B: EE
            pstArectangle ������Ϣ����
            num �������
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int sal_vgs_draw_rectangle1(VIDEO_FRAME_INFO_S* pstOutFrameInfo, unsigned int u32Thick, unsigned int u32Color
                            , rectangle_s* pstArectangle, int num);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

