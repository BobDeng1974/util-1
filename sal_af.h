
#ifndef __SAL_AF_H__
#define __SAL_AF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

/*
 �� �� ��: sal_af_register_callback
 ��������: AFģ��ע����ػص����ڲ�ʹ�ú����ӿ�
 �������:
 �������:
 �� �� ֵ: ���óɹ�����0, ʧ�ܷ���С��0
*/
int sal_af_register_callback(void);

/*
 �� �� ��: sal_af_unregister_callback
 ��������: AFģ�鷴ע����ػص����ڲ�ʹ�ú����ӿ�
 �������:
 �������:
 �� �� ֵ: ���óɹ�����0, ʧ�ܷ���С��0
*/
int sal_af_unregister_callback(void);

/*
 �� �� ��: sal_af_get_fv
 ��������: SAL���ȡAF��ֵ���ⲿ�ɵ���
 �������:
 �������:
 �� �� ֵ: ���óɹ�����0, ʧ�ܷ���С��0
*/
int sal_af_get_fv(int *value);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

