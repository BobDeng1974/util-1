#ifndef __SAL_OSD_H__
#define __SAL_OSD_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

#define RGB_VALUE_BLACK     0x8000  //��
#define RGB_VALUE_WHITE     0xffff  // ��ɫ
#define RGB_VALUE_BG        0x7fff //͸��


typedef enum OSD_TITLE_TYPE_E
{
    TITLE_ADD_NOTHING = 0,
    TITLE_ADD_RESOLUTION = 1,
    TITLE_ADD_BITRATE = 2,
    TITLE_ADD_ALL = 3,
    TITLE_ADD_BUTT,
}OSD_TITLE_TYPE_E;

typedef enum OSD_LOCATION_E
{
    OSD_LEFT_TOP = 0,
    OSD_LEFT_BOTTOM = 1,
    OSD_RIGHT_TOP = 2,
    OSD_RIGHT_BOTTOM = 3,
    OSD_HIDE = 4,
}OSD_LOCATION_E;

typedef struct sal_osd_item_s
{
    int enable;
    OSD_LOCATION_E location;

    unsigned long tmformat;              //only valid for time
    OSD_TITLE_TYPE_E type;              //only valid for title title type
    char buffer[256];
    char buffer_bak[256];              //only for title type eg: add bitrate
}sal_osd_item_s;

/*
 �� �� ��: sal_osd_init
 ��������: ��ʼ��OSDģ�飬Ĭ����ʾʱ��ͱ���
 �������: ��
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int sal_osd_init();

/*
 �� �� ��: sal_osd_exit
 ��������: ȥ��ʼ��OSDģ��
 �������: ��
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int sal_osd_exit();


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
