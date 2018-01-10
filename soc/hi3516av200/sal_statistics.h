#ifndef __SAL_STATISTICS_H__
#define __SAL_STATISTICS_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif


/*
 �� �� ��: sal_statistics_proc
 ��������: ����֡��ͳ�ƣ��ڲ�ʹ��API
 �������: id ��Ƶ��id
            pts ʱ���
            len ֡����
            keyFrame �Ƿ�ؼ�֡
            gop I֡���
            smooth_frames ������֡��ʼ����
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int sal_statistics_proc(int id, double pts, int len, int keyFrame, int gop, int smooth_frames);

/*
 �� �� ��: sal_statistics_bitrate_get
 ��������: ��ȡʵʱͳ�Ƶ�����
 �������: id ��Ƶ��id
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int sal_statistics_bitrate_get(int id);

/*
 �� �� ��: sal_statistics_framerate_get
 ��������: ��ȡʵʱͳ�Ƶ�֡��
 �������: id ��Ƶ��id
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int sal_statistics_framerate_get(int id);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif



