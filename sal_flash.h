
#ifndef __SAL_FLASH_H__
#define __SAL_FLASH_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif


/*****************************************************************************
 �� �� ��: sal_flashcp
 ��������  : SAL��flash��д
 �������  : buf ����
            size �����С,
            devicename  mtdģ��ڵ� ���磬"/dev/mtd1"
 �������  :
 �� �� ֵ: �ɹ�����0, ʧ�ܷ���С��0
*****************************************************************************/
int sal_flashcp(char *buf, int size,  char *devicename);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

