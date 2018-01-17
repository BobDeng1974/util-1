#ifndef __SAL_BITMAP_H__
#define __SAL_BITMAP_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

#define FORE_GROUND 'X'  //���ֵ���ǰ��������Ч��Ҫ��ʾ���ַ���
#define BACK_GROUND '-'  //���ֵ��󱳾���������Ҫ��ʾ���ַ���
#define FONT_EDGE 'o'    //���ֵ���ǰ�������ܱ�Ե

#define MAX_LINE_NUM 20   //����������ͨ�� ^ ���������л���
#define MAX_LINE_PLL 100  //ÿ�е�����ֽ���

typedef struct
{
    int row;   //���ֵ�������
    int col;   //���ֵ�������
    char* bit_map;  //���ֵ���
}result_s;


/*
 �� �� ��: bitmap_create
 ��������: ��ʼ��bitmapģ�飬����bitmap_destroy���ʹ��
 �������: hz_path �����ֿ��ļ�·��
            is_gbk �Ƿ�Ϊgbk�ֿ�
            asc_path asc16�ֿ��ļ�·��
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int bitmap_create(const char* hz_path, int is_gbk, const char* asc_path);

/*
 �� �� ��: bitmap_destroy
 ��������: ȥ��ʼ��bitmapģ�飬����bitmap_create���ʹ��
 �������: ��
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int bitmap_destroy();

/*
 �� �� ��: bitmap_alloc
 ��������: ��ȡһ�����ֵ�bitmap������bitmap_free���ʹ��
 �������: chs ���־���
            font_size �����С
            edge_enable �Ƿ���а��ߴ���
            gap ������֮��ļ�϶
 �������: result �����ص�bitmap���ⲿ���ɸ���
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int bitmap_alloc(const unsigned char* chs, int font_size, int edge_enable, int gap, result_s* result);

/*
 �� �� ��: bitmap_free
 ��������: �ͷ�һ�����ֵ�bitmap������bitmap_alloc���ʹ��
 �������: result ��ص�bitmap����
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int bitmap_free(result_s* result);

/*
 �� �� ��: bitmap_demo
 ��������: ʹ�ô�ģ���demo�����ο�
 �������: ��
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int bitmap_demo();




#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
