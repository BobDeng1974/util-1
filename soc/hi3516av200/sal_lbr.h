
#ifndef __SAL_LBR_H__
#define __SAL_LBR_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif


/*
 �� �� ��: sal_lbr_init
 ��������: ��ʼ��������ģ��
 �������: ��
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int sal_lbr_init();

/*
 �� �� ��: sal_lbr_exit
 ��������: ȥ��ʼ��������ģ��
 �������: ��
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int sal_lbr_exit();

/*
 �� �� ��: sal_lbr_get_str
 ��������: ��ȡlbr��ǰ��ģʽ���ڲ�ʹ�ýӿ�
 �������: buf������buffer
            len: buf�ĳ���
 �������: buf�����lbr��ǰ��ģʽ
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int sal_lbr_get_str(char* buf, int len);

/*
 �� �� ��: sal_lbr_get_vpstr
 ��������: ��ȡlbr��ǰ����ģʽ��ͳ����Ϣ���ڲ�ʹ�ýӿ�
 �������: buf������buffer
            len: buf�ĳ���
 �������: buf�����lbr��ǰ��ģʽ
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int sal_lbr_get_vpstr(char* buf, int len);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

