
#ifndef __SAL_AV_H__
#define __SAL_AV_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

#include "sal_standard.h"

typedef enum SAL_BITRATE_CONTROL_E
{
    SAL_BITRATE_CONTROL_CBR = 0,
    SAL_BITRATE_CONTROL_VBR = 1,
    SAL_BITRATE_CONTROL_BUTT,
}SAL_BITRATE_CONTROL_E;

typedef enum SAL_ENCODE_TYPE_E
{
    SAL_ENCODE_TYPE_H264 = 0,
    SAL_ENCODE_TYPE_H265 = 1,
    SAL_ENCODE_TYPE_BUTT,
}SAL_ENCODE_TYPE_E;

typedef struct sal_stream_s
{
    int enable;
    int height;
    int width;
    int framerate;
    int bitrate;  //kbps
    int gop;
    SAL_BITRATE_CONTROL_E bitrate_ctl;
    SAL_ENCODE_TYPE_E encode_type;
}sal_stream_s;

typedef struct sal_video_qp_s
{
    int min_qp;
    int max_qp;
    int min_i_qp;
    int max_i_qp;
}sal_video_qp_s;

/*
 �� �� ��: sal_video_frame_cb
 ��������: ��Ƶ֡�ص�����
 �������: ��
 �������: stream ��id
            pts ʱ���(us) ����ʱ��
            frame ��Ƶ֡
            len ֡��С
            key �ؼ�֡��־
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
typedef int (*sal_video_frame_cb)(int stream, char *frame, unsigned long len, int key, double pts, SAL_ENCODE_TYPE_E encode_type);

typedef struct sal_video_s
{
    sal_stream_s stream[2];
    sal_video_frame_cb cb;
    int rotate; // 0-->none, 1-->90 degree rotation
    int scale_enable;
    int smartP_enable;
    int wdr_enable;
}sal_video_s;


/*
 �� �� ��: sal_sys_init
 ��������: ��ʼ��dspϵͳ��Դ
 �������: video ��Ƶ����
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int sal_sys_init(sal_video_s* video);


/*
 �� �� ��: sal_sys_exit
 ��������: dspϵͳ�˳����ͷ���Դ
 �������: ��
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int sal_sys_exit(void);

/*
 �� �� ��: sal_sys_version
 ��������: ��ȡMPP�汾��Ϣ���Լ�libipc.so�İ汾��Ϣ
 �������:    buffer ����buffer
            len     ����buffer�ĳ��ȣ���bufferС�������С������ʧ��
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int sal_sys_version(char* buffer, int len);

/*
 �� �� ��: sal_video_force_idr
 ��������: ǿ��I֡
 �������: stream ����id
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int sal_video_force_idr(int stream);

 /*
 �� �� ��: sal_video_mirror_set
 ��������: ����ˮƽ��ת
 �������: enable ʹ�ܱ�־
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int sal_video_mirror_set(int enable);

 /*
 �� �� ��: sal_video_flip_set
 ��������: ���ô�ֱ��ת
 �������: enable ʹ�ܱ�־
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int sal_video_flip_set(int enable);

 /*
 �� �� ��: sal_video_vi_framerate_set
 ��������: ����VI֡��
 �������: framerate ֡��
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int sal_video_vi_framerate_set(int framerate);

 /*
 �� �� ��  : sal_video_framerate_set
 ��������: ���ñ���֡��
 �������: stream ����id
            framerate VENC֡��
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int sal_video_framerate_set(int stream, int framerate);

/*
 �� �� ��: sal_video_bitrate_set
 ��������: ��������
 �������: stream ����id
            bitrate_ctl �����ʻ������
            bitrate ���� kbps
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int sal_video_bitrate_set(int stream, SAL_BITRATE_CONTROL_E bitrate_ctl, int bitrate);

 /*
 �� �� ��: sal_video_gop_set
 ��������: ����GOP
 �������: stream ����id
            gop I֡��� һ����Ϊ֡�ʵ�������
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int sal_video_gop_set(int stream, int gop);

/*
 �� �� ��: sal_video_args_get
 ��������: ��ȡ��Ƶ����Ϣ
 �������: stream ����id
 �������: video ��Ƶ����Ϣ
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int sal_video_args_get(int stream, sal_stream_s* video);

 /*
 �� �� ��: sal_video_cbr_qp_set
 ��������: ����CBRģʽ�µ�QP
 �������: stream ����id
            qp_args QP��ز���
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int sal_video_cbr_qp_set(int stream, sal_video_qp_s* qp_args);

 /*
 �� �� ��: sal_video_cbr_qp_get
 ��������: ��ȡCBRģʽ�µ�QP
 �������: stream ����id
 �������: qp_args QP��ز���
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int sal_video_cbr_qp_get(int stream, sal_video_qp_s* qp_args);

/*
 �� �� ��: sal_video_lbr_set
 ��������: �������� ���ڲ�lbrģ��ʹ�ã��Ա���û���CBR��LBRʹ�õ�CBR
 �������: stream ����id
            bitrate_ctl �����ʻ������
            bitrate ���� kbps
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int sal_video_lbr_set(int stream, SAL_BITRATE_CONTROL_E bitrate_ctl, int bitrate);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

