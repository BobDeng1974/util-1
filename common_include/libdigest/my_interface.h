#ifndef __MA_LIVE555_INTERFACE_H__
#define __MA_LIVE555_INTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

/*
 �� �� ��: MY_Base64Encode
 ��������: base64���ܡ���Ϊ���ص�ָ�������ڲ�ʹ��malloc����ģ��ⲿ�����free�ͷ�
 �������: _au8Buf ����buf
            _u32BufSize buf�ĳ���
 �������: ��
 �� �� ֵ: �ɹ����ؼ��ܺ���ַ���,ʧ�ܷ���NULL
*/
char* MY_Base64Encode(unsigned char* _au8Buf, unsigned int _u32BufSize);

/*
 �� �� ��: MY_Authrization
 ��������: ����ժҪDigest����Ϊ���ص�ָ�������ڲ�ʹ��malloc����ģ��ⲿ�����free�ͷ�
 �������: _szCmd RTSP���DESCRIBE, SETUP, PLAY, OPTIONS, TEARDOWN��
            _szUrl RTSP��url
            _szUsr �û���
            _szPwd ����
            _szRealm RTSP������ָ����realm
            _szNonce RTSP������ָ����nonce��һ���������
 �������: ��
 �� �� ֵ: �ɹ�����ժҪDigest���ַ���,ʧ�ܷ���NULL
*/
char* MY_Authrization(char* _szCmd, char* _szUrl,
		char* _szUsr, char* _szPwd,
		char* _szRealm, char* _szNonce);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

