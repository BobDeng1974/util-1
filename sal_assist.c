
#include "sal_standard.h"
#include "sal_overlay.h"
#include "sal_util.h"
#include "sal_debug.h"
#include "sal_bitmap.h"
#include "sal_osd.h"
#include "sal_config.h"
#include "sal_statistics.h"
#include "sal_isp.h"
#include "sal_lbr.h"
#include "sal_af.h"
#include "sal_jpeg.h"
#include "sal_draw_rectangle.h"

/*
* �����������
* �˺���ֻ��Ϊ������libipc.so��ʱ�򣬰Ѻ����������ӽ�libipc.so��
* ��������ã���ô����libipc.so��ʱ�򣬻��Զ��޳����������š��ݲ���ԭ��
*/

int sal_assist()
{
	sal_jpeg_init(NULL);
    sal_dr_init();
	
	return 0;
}


