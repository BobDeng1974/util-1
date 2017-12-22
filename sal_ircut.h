#ifndef __SAL_IRCUT_H__
#define __SAL_IRCUT_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif


typedef enum
{
    SAL_IR_MODE_UNSUPPORT = -1,// Ӳ����֧�ֺ���
    SAL_IR_MODE_AUTO = 0,		// �Զ����⣬Ĭ��
    SAL_IR_MODE_ON   = 1,		// ǿ�ƿ�����
    SAL_IR_MODE_OFF  = 2,		// ǿ�ƹغ���
}SAL_IR_MODE;

/*
 �� �� ��: sal_ircut_init
 ��������  : ��ʼ��ircutģ�飬Ĭ��Ϊ�Զ�ģʽ
 �������  : ��
 �������  : ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int sal_ircut_init();

/*****************************************************************************
 �� �� ��: sal_ircut_exit
 ��������  : ȥ��ʼ��ircutģ��
 �������  : ��
 �������  : ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*****************************************************************************/
int sal_ircut_exit();

/*****************************************************************************
 �� �� ��: sal_ircut_mode_set
 ��������  : ����ircut����ģʽ
 �������  : mode ircut����ģʽ
 �������  : ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*****************************************************************************/
int sal_ircut_mode_set(SAL_IR_MODE mode);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif



