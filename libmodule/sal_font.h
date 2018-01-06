#ifndef __SAL_FONT_H__
#define __SAL_FONT_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

#define MAX_FONT_NUM 128   //���建��ش�ŵ��������

typedef struct
{
    int reference;         //���ü���
    int enc_len;           //���ֱ��볤��
    unsigned char enc[2];  //���ֱ���
    int font_size; // default font size 1
    int row;               //���ֵ�������
    int col;               //���ֵ�������
    unsigned char* array; // ���ֵ��� row*col
}font_s;


/*
 �� �� ��: font_init
 ��������: ���建��س�ʼ��������font_exit���ʹ��
 �������: ��
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int font_init();

/*
 �� �� ��: font_exit
 ��������: ���建��س�ʼ��������font_init���ʹ��
 �������: ��
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int font_exit();

/*
 �� �� ��: font_add
 ��������: �����建���������������������
 �������: enc ���ֱ���
            len ���ֱ��볤��
            src ���ֵ���
            row ���ֵ�������
            col ���ֵ�������
            font_size �����С��16x16�������СΪ1��32x32�������СΪ2���Դ����ƣ�
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int font_add(const unsigned char* enc, int len, char* src, int row, int col, int font_size);

/*
 �� �� ��: font_get
 ��������: ��ȡ���建����е��������������ݣ�����font_release���ʹ��
 �������: enc ���ֱ���
            len ���ֱ��볤��
            font_size �����С��16x16�������СΪ1��32x32�������СΪ2���Դ����ƣ�
 �������: ��
 �� �� ֵ: �ɹ������������������ݣ��ⲿ���ɸ��ģ�,ʧ�ܷ���NULL
*/
font_s* font_get(const unsigned char* enc, int len, int font_size);

/*
 �� �� ��: font_get
 ��������: �ͷ����建����е��������������ݣ�����font_get���ʹ��
 �������: font ��������������
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int font_release(font_s* font);

/*
 �� �� ��: font_get_num
 ��������: ��ȡ���建�����ʵ�ʻ���ĺ�������
 �������: ��
 �������: ��
 �� �� ֵ: �ɹ����ػ���ĺ�������,ʧ�ܷ���С��0
*/
int font_get_num();




#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
