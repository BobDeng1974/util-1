
#ifndef sal_jpeg1_h__
#define sal_jpeg1_h__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

/*
 �� �� ��: jpeg1_create_chn
 ��������: ����JPEG����ͨ������HI_MPI_VENC_SendFrame�ֶ���֡
 �������: channel VENC ����ͨ���������������ı���ͨ����ͻ
            widht ��
            height ��
 �������:
 �� �� ֵ: ���óɹ�����0, ʧ�ܷ���С��0
*/
int jpeg1_create_chn(int channel, int widht, int height);

/*
 �� �� ��: jpeg1_destroy_chn
 ��������: ����JPEG����ͨ��
 �������: channel VENC ����ͨ���������������ı���ͨ����ͻ
 �������:
 �� �� ֵ: ���óɹ�����0, ʧ�ܷ���С��0
*/
int jpeg1_destroy_chn(int channel);

/*
 �� �� ��: jpeg1_set_Qfactor
 ��������: ����JPEG���� 1-100
 �������: channel VENC ����ͨ���������������ı���ͨ����ͻ
            Qfactor ���� 1-100
 �������:
 �� �� ֵ: ���óɹ�����0, ʧ�ܷ���С��0
*/
int jpeg1_set_Qfactor(int channel, int Qfactor);

/*
 �� �� ��: jpeg1_get_picture
 ��������: ȡjpeg������ͼ��
 �������: channel VENC ����ͨ���������������ı���ͨ����ͻ
 �������: out ���ͼ��
            len ���ͼ�񳤶�
 �� �� ֵ: ���óɹ�����0, ʧ�ܷ���С��0
*/
int jpeg1_get_picture(int channel, unsigned char** out, int* len);

/*
 �� �� ��: jpeg1_release_picture
 ��������: �ͷ�ͼ����Դ
 �������: channel VENC ����ͨ���������������ı���ͨ����ͻ
            in ͼ��
            len ͼ�񳤶�
 �������: ��
 �� �� ֵ: ���óɹ�����0, ʧ�ܷ���С��0
*/
int jpeg1_release_picture(int channel, unsigned char** in, int* len);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

