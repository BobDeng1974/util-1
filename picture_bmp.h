#ifndef __bmp_h__
#define __bmp_h__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif


typedef struct                       /**** BMP file header structure ****/
{
    unsigned int   bfSize;           /* Size of file */
    unsigned short bfReserved1;      /* Reserved */
    unsigned short bfReserved2;      /* ... */
    unsigned int   bfOffBits;        /* Offset to bitmap data */
} MyBITMAPFILEHEADER;

typedef struct                       /**** BMP file info structure ****/
{
    unsigned int   biSize;           /* Size of info header */
    int            biWidth;          /* Width of image */
    int            biHeight;         /* Height of image */
    unsigned short biPlanes;         /* Number of color planes */
    unsigned short biBitCount;       /* Number of bits per pixel */
    unsigned int   biCompression;    /* Type of compression to use */
    unsigned int   biSizeImage;      /* Size of image data */
    int            biXPelsPerMeter;  /* X pixels per meter */
    int            biYPelsPerMeter;  /* Y pixels per meter */
    unsigned int   biClrUsed;        /* Number of colors used */
    unsigned int   biClrImportant;   /* Number of important colors */
}MyBITMAPINFOHEADER;

typedef struct tagRGBQUAD
{  
    unsigned char rgbBlue;//��ɫ�����ȣ�ֵ��ΧΪ0-255)  
    unsigned char rgbGreen;//��ɫ�����ȣ�ֵ��ΧΪ0-255)  
    unsigned char rgbRed;//��ɫ�����ȣ�ֵ��ΧΪ0-255)  
    unsigned char rgbReserved;//����������Ϊ0  
}RGBQUAD;


/*
 �� �� ��: bmp_rgb2yuv
 ��������: rgb����ת��Ϊyuv����
 �������: r ��ɫ����
            g ��ɫ����
            b ��ɫ����
 �������: y ���ȷ���
            u cbɫ�ȷ���
            v crɫ�ȷ���
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int bmp_rgb2yuv(unsigned char r, unsigned char g, unsigned char b, unsigned char* y, unsigned char* u, unsigned char* v);

/*
 �� �� ��: bmp_yuv2rgb
 ��������: yuv����ת��Ϊrgb����
 �������: y ���ȷ���
            u cbɫ�ȷ���
            v crɫ�ȷ���
 �������: r ��ɫ����
            g ��ɫ����
            b ��ɫ����
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int bmp_yuv2rgb(unsigned char y, unsigned char u, unsigned char v, unsigned char* r, unsigned char* g, unsigned char* b);

/*
 �� �� ��: bmp_rgb2bgr
 ��������: rgb����ת��Ϊbgr���ݣ�һ������ռ3�ֽڡ�
            rgb�����Ǵ����Ҵ��ϵ��µ�rgb˳�����ݣ�bgr�����Ǵ����Ҵ��µ��ϵ�bgr˳�����ݣ�
 �������: buffer �������ݣ�ͬ��Ҳ��Ϊ�������СΪwidth*height*3
            width ��
            height ��
 �������: buffer ������ݣ�ͬ��Ҳ��Ϊ���롣��СΪwidth*height*3
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int bmp_rgb2bgr(unsigned char* buffer, int width, int height);

/*
 �� �� ��: bmp_bgr2rgb
 ��������: bgr����ת��Ϊrgb���ݣ�һ������ռ3�ֽڡ�
            rgb�����Ǵ����Ҵ��ϵ��µ�rgb˳�����ݣ�bgr�����Ǵ����Ҵ��µ��ϵ�bgr˳�����ݣ�
 �������: buffer �������ݣ�ͬ��Ҳ��Ϊ�������СΪwidth*height*3
            width ��
            height ��
 �������: buffer ������ݣ�ͬ��Ҳ��Ϊ���롣��СΪwidth*height*3
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int bmp_bgr2rgb(unsigned char* buffer, int width, int height);

/*
 �� �� ��: bmp_save2file
 ��������: ��bgrͼ�����ݱ��浽�ļ���
 �������: path �ļ�·��
            bgrbuffer ͼ������
            width ��
            height ��
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int bmp_save2file(const char* path, unsigned char* bgrbuffer,int width,int height);

/*
 �� �� ��: bmp_fileParse
 ��������: ��bmp�ļ�������bgr���ݡ�
 �������: path �ļ�·��
 �������: outBgrBuffer ���bgr����
            outsize outBgrBuffer��С
            width ��
            height ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int bmp_fileParse(const char* path, unsigned char** outBgrBuffer, unsigned int* outsize, int* width, int* height);

/*
 �� �� ��: bmp_rgb2rgb1555
 ��������: ��rgb888����ת��Ϊrgb1555���ݡ�
            rgb888һ������ռ3�ֽڣ�rgb1555һ������ռ2�ֽڣ��������λ��ʶalpha��͸���ȣ�
 �������: rgb888buffer rgb888���ݣ���СΪwidth*height*3
            width ��
            height ��
 �������: rgb1555buffer rgb1555buffer���ݣ���СΪwidth*height*2
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int bmp_rgb2rgb1555(unsigned char* rgb888buffer, unsigned char* rgb1555buffer, int width, int height);

/*
 �� �� ��: bmp_copy
 ��������: С���ο���������ε�buffer���ݡ�
 �������: src_buffer Դ���Σ���СΪsrc_width*src_height*bpp
            src_width Դ��
            src_height Դ��
            dst_width Ŀ�Ŀ�
            dst_height Ŀ�ĸ�
            bpp һ������ռ���ֽ�����byte per pixel��
            start_widht ��ʼ����������
            start_height ��ʼ����������
 �������: dst_buffer Ŀ�ľ��Σ���СΪdst_width*dst_height*bpp
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int bmp_copy(unsigned char* src_buffer, int src_width, int src_height, 
             unsigned char* dst_buffer, int dst_width, int dst_height, int bpp, int start_widht, int start_height);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif // __bmp_h__
