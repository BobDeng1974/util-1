
#ifndef __SAL_MD_H__
#define __SAL_MD_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

/*
 �� �� ��: sal_md_cb
 ��������: �ƶ����ص�����
 �������: ��
 �������: precent ÿһ���⵽�˶�������ռ����ֱȣ������ң���������
            num ����
            pixel_num �ƶ�����������
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
typedef int (*sal_md_cb)(int* precent, int num, int pixel_num);

/*
 �� �� ��: sal_md_init
 ��������: ��ʼ���ƶ����
 �������: block_h ˮƽ����ֿ���
            block_v ��ֱ����ֿ���
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int sal_md_init(int block_h, int block_v);

/*
 �� �� ��: sal_md_exit
 ��������: �˳��ƶ���⣬�ͷ���Դ
 �������: ��
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int sal_md_exit(void);

/*
 �� �� ��: sal_md_set
 ��������: ���÷ֿ����
 �������: block_h ˮƽ����ֿ���
            block_v ��ֱ����ֿ���
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int sal_md_set(int block_h, int block_v);

/*
 �� �� ��: sal_md_cb_set
 ��������: �����ƶ����ص�����
 �������: cb �ص�����
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int sal_md_cb_set(sal_md_cb cb);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
