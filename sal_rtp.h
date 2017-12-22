#ifndef __MA_RTP_H__
#define __MA_RTP_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "sal_standard.h"

typedef struct
{
    unsigned char flag;
    unsigned char channel;
    unsigned short size;
} RTSP_INTERLEAVED_FRAME;

/******************************************************************
RTP_FIXED_HEADER
0                   1                   2                   3
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|V=2|P|X|  CC   |M|     PT      |       sequence number         |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                           timestamp                           |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|           synchronization source (SSRC) identifier            |
+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
|            contributing source (CSRC) identifiers             |
|                             ....                              |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

******************************************************************/

typedef struct
{
    /* byte 0 */
    unsigned char csrc_len:4; /* CC expect 0 */
    unsigned char extension:1;/* X  expect 1, see RTP_OP below */
    unsigned char padding:1;  /* P  expect 0 */
    unsigned char version:2;  /* V  expect 2 */
    /* byte 1 */
    unsigned char payload:7; /* PT  RTP_PAYLOAD_RTSP */
    unsigned char marker:1;  /* M   expect 1 */
    /* byte 2,3 */
    unsigned short seq_no;   /*sequence number*/
    /* byte 4-7 */
    unsigned  long timestamp;
    /* byte 8-11 */
    unsigned long ssrc; /* stream number is used here. */
} RTP_FIXED_HEADER;/*12 bytes*/

/******************************************************************
NALU_HEADER
+---------------+
|0|1|2|3|4|5|6|7|
+-+-+-+-+-+-+-+-+
|F|NRI|  Type   |
+---------------+
******************************************************************/
typedef struct
{
    //byte 0
    unsigned char TYPE:5;
    unsigned char NRI:2;
    unsigned char F:1;
} NALU_HEADER; /* 1 byte */


/******************************************************************
FU_INDICATOR
+---------------+
|0|1|2|3|4|5|6|7|
+-+-+-+-+-+-+-+-+
|F|NRI|  Type   |
+---------------+
******************************************************************/
typedef struct
{
    //byte 0
    unsigned char TYPE:5;
    unsigned char NRI:2;
    unsigned char F:1;
} FU_INDICATOR; /*1 byte */


/******************************************************************
FU_HEADER
+---------------+
|0|1|2|3|4|5|6|7|
+-+-+-+-+-+-+-+-+
|S|E|R|  Type   |
+---------------+
******************************************************************/
typedef struct
{
    //byte 0
    unsigned char TYPE:5;
    unsigned char R:1;
    unsigned char E:1;
    unsigned char S:1;
} FU_HEADER; /* 1 byte */

typedef struct
{
    int startcodeprefix_len;      //! 4 for parameter sets and first slice in picture, 3 for everything else (suggested)
    unsigned len;                 //! Length of the NAL unit (Excluding the start code, which does not belong to the NALU)
    unsigned max_size;            //! Nal Unit Buffer size
    int forbidden_bit;            //! should be always FALSE
    int nal_reference_idc;        //! NALU_PRIORITY_xxxx
    int nal_unit_type;            //! NALU_TYPE_xxxx
    char *buf;                    //! contains the first byte followed by the EBSP
    unsigned short lost_packets;  //! true, if packet loss is detected
} NALU_t;

#define UDP_MAX_SIZE (1399)
#define H264 (96)
#define AMR (97)
#define G711 (0)

typedef struct
{
    unsigned char* pu8Buf;        //�������RTP����buffer
    unsigned int u32BufSize;      //buffer�Ĵ�С
    unsigned int u32SegmentCount; //RTP���ĸ���
    unsigned char** ppu8Segment;  //ÿһ��RTP���ĵ�ַoffset����Դ��pu8Buf
    unsigned int* pU32SegmentSize;//ÿһ��RTP���Ĵ�С
} RTP_SPLIT_S;

typedef struct
{
    int sps_offset;
    int sps_len;
    int pps_offset;
    int pps_len;
    int sei_offset;
    int sei_len;
    int idr_offset;
    int idr_len;
} RTP_KEY_S;

/*
 �� �� ��: rtp_amr_alloc
 ��������: RTP��װAMR����Ƶ֡ ÿ��RTP��������RTP OVER TCP�Ľ���֡ͷ
 �������: _pu8Frame ��Ƶ֡
            _u32FrameSize ֡��С
            _pu16SeqNumber RTP�������
            _u32Timestamp RTP����ʱ���
            _Ssrc RTP����ssrc
 �������: _pRetRtpSplit ����RTP����Ľ���������rtp_free���ͷ�
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int rtp_amr_alloc(unsigned char* _pu8Frame, unsigned int _u32FrameSize,
                      unsigned short* _pu16SeqNumber, unsigned int _u32Timestamp,
                      unsigned long _Ssrc, RTP_SPLIT_S* _pRetRtpSplit);

/*
 �� �� ��: rtp_g711_alloc
 ��������: RTP��װG711����Ƶ֡ ÿ��RTP��������RTP OVER TCP�Ľ���֡ͷ
 �������: _pu8Frame ��Ƶ֡
            _u32FrameSize ֡��С
            _pu16SeqNumber RTP�������
            _u32Timestamp RTP����ʱ���
            _Ssrc RTP����ssrc
 �������: _pRetRtpSplit ����RTP����Ľ���������rtp_free���ͷ�
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int rtp_g711a_alloc(unsigned char* _pu8Frame, unsigned int _u32FrameSize,
                      unsigned short* _pu16SeqNumber, unsigned int _u32Timestamp,
                      unsigned long _Ssrc, RTP_SPLIT_S* _pRetRtpSplit);

/*
 �� �� ��: rtp_h264_split
 ��������: h264�����ָ�nalu����ȡÿ��nalu�ķֽ��
 �������: _pu8Frame ��Ƶ֡
            _u32FrameSize ֡��С
 �������: ��
 �� �� ֵ: �ɹ����صڶ���nalu�ķֽ��,ʧ�ܷ���С��0
*/
int rtp_h264_split(unsigned char* _pu8Frame, unsigned int _u32FrameSize);

/*
 �� �� ��: rtp_h264_alloc
 ��������: RTP��װh264����Ƶ֡��ÿ��RTP��������RTP OVER TCP�Ľ���֡ͷ
 �������: _pu8Frame ��Ƶ֡
            _u32FrameSize ֡��С
            _pu16SeqNumber RTP�������
            _u32Timestamp RTP����ʱ���
 �������: _pRetRtpSplit ����RTP����Ľ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int rtp_h264_alloc(unsigned char* _pu8Frame, unsigned int _u32FrameSize,
                       unsigned short* _pu16SeqNumber, unsigned int _u32Timestamp,
                       RTP_SPLIT_S* _pRetRtpSplit);

/*
 �� �� ��: rtp_free
 ��������: �ͷ�RTP����װ����Դ
 �������: _pRetRtpSplit ����RTP����Ľ��
 �������:
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int rtp_free(RTP_SPLIT_S* _pRetRtpSplit);


int rtp_payload_get(char* encode_type);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif


