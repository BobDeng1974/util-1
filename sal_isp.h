
#ifndef __SAL_ISP_H__
#define __SAL_ISP_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

 typedef enum SAL_ISP_MODE_E
 {
     SAL_ISP_MODE_DAY = 1,
     SAL_ISP_MODE_NIGHT = 0,
 }SAL_ISP_MODE_E;

 typedef enum
 {
     SAL_IMAGE_SATURATION = 0,
     SAL_IMAGE_CONTRAST,
     SAL_IMAGE_BRIGHTNESS,
     SAL_IMAGE_SHARPNESS
 }SAL_IMAGE_E;

 typedef struct sal_exposure_info_s
 {
     unsigned int ExpTime;
     unsigned int AGain;
     unsigned int DGain;
     unsigned int ISPGain;
     unsigned char AveLuma;
     unsigned int ColorTemp;
 }sal_exposure_info_s;

 typedef struct
 {
     unsigned char saturation;
     unsigned char contrast;
     unsigned char brightness;
     unsigned char sharpness;
 }sal_image_attr_s;

 typedef struct
 {
    int slow_shutter_enable;    //0 disable / 1 enable
    sal_image_attr_s image_attr;
 }sal_isp_s;


/*****************************************************************************
 �� �� ��: sal_isp_init
 ��������  : SAL��isp��ʼ������Ҫ����iq ��xml�����ļ�����ʹ�ܵ�dsp
 �������  : ��
 �������  : ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*****************************************************************************/
int sal_isp_init(sal_isp_s* param);


/*****************************************************************************
 �� �� ��: sal_isp_exit
 ��������  : SAL��ispȥ��ʼ��������isp ģ���õ���ϵͳ��Դ
 �������  : ��
 �������  : ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*****************************************************************************/
int sal_isp_exit(void);


/*****************************************************************************
 �� �� ��: sal_isp_day_night_switch
 ��������  : SAL��isp�л���ҹiq����
 �������  : mode ��ҹģʽ
            attr ͼ���������
 �������  : ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*****************************************************************************/
int sal_isp_day_night_switch(SAL_ISP_MODE_E mode, sal_image_attr_s* attr);


/*****************************************************************************
 �� �� ��: sal_isp_image_attr_set
 ��������  : SAL������ͼ������
 �������  :    type  (���Ͷȣ��Աȶȣ����ȣ����)
            value ͼ�����Ե�����ֵ����Χ0-255��128��Ĭ��ֵ
                  �紫��Ĭ��ֵ��Ҫ����isp�ڲ��Զ�����
 �������  : ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*****************************************************************************/
int sal_isp_image_attr_set(SAL_IMAGE_E type, unsigned char value);

/*****************************************************************************
 �� �� ��: sal_isp_slow_shutter_set
 ��������  : SAL���Ƿ�ʹ�ܽ�֡
 �������  : 1 enable /0 disable
 �������  : ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*****************************************************************************/
int sal_isp_slow_shutter_set(int enable);


/*****************************************************************************
 �� �� ��: sal_isp_exposure_info_get
 ��������  : SAL���ȡisp���ع������Ϣ��:
            �ع�ʱ�䡢sensorģ�����桢sensor�������桢isp������
 �������  : ��
 �������  : sal_exposure_info_s ����
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*****************************************************************************/
int sal_isp_exposure_info_get(sal_exposure_info_s* info);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

