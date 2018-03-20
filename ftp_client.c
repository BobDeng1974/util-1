
#include "sal_list.h"
#include "sal_select.h"
#include "sal_debug.h"
#include "sal_malloc.h"
#include "sal_util.h"
#include "ftp_client.h"

#define GOTO(exp, exec, to, fmt...) do\
{\
    if (!(exp))\
    {\
        ERR(fmt);\
        exec;\
        goto to;\
    }\
}while(0)

//
//USER: ָ���û�����ͨ���ǿ������Ӻ��һ�������������USER gaoleyi\r\n���� �û���Ϊgaoleyi ��¼��
//PASS: ָ���û����롣��������� USER ����󡣡�PASS gaoleyi\r\n��������Ϊ gaoleyi��
//CWD: �ı乤��Ŀ¼���磺��CWD dirname\r\n����
//PASV: �÷����������ݶ˿ڼ��������뱻��ģʽ���磺��PASV\r\n����
//PORT: ���� FTP �������ͻ��˼����Ķ˿ںţ��� FTP ��������������ģʽ���ӿͻ��ˡ��磺��PORT h1,h2,h3,h4,p1,p2����
//RETR: �����ļ�����RETR file.txt \r\n���������ļ� file.txt��
//STOR: �ϴ��ļ�����STOR file.txt\r\n�����ϴ��ļ� file.txt��
//QUIT: �ر�������������ӡ�
// 
typedef enum FTP_STEP_E
{
    FTP_STEP_INVALID = 0,
    FTP_STEP_USER,      
    FTP_STEP_PASS,     
    FTP_STEP_TYPE,  
    FTP_STEP_PASV, 
    FTP_STEP_SIZE,  
    FTP_STEP_RETR,    //�����ļ�
    FTP_STEP_RETRING, //�������ݶ˿ڽ������ݽ���
    FTP_STEP_STOR,    //�ϴ��ļ�
    FTP_STEP_STORING, //�������ݶ˿ڽ������ݽ���
    FTP_STEP_QUIT,
    FTP_STEP_END,
}FTP_STEP_E;

typedef struct ftp_client_s
{
    handle hndSocketCmd;
    handle hndSocketData;
    int cache_size;
    int multi_pack_enable;
    int remain_size;
    int FdCmd;
    int FdData;
    int portCmd;
    int portData;
    pthread_t tPid;
    int bRunning;

    char szHost[256];
    char szIp[16];
    char szUserName[256];
    char szPassword[256];
    
    int logined;
    int timeout; //��ʱʱ�䣨���룩
    FTP_STATUS_E enStatus;
    FTP_STEP_E enFtpStep;
    int progress;
    char szFileName[256];
    
    int bGetEnable;
    int bPutEnable;
    
    unsigned char* pu8Content;        //��ftpget Ϊ malloc �ڲ����롣��ftpput Ϊ�ⲿ����buffer
    unsigned int u32ContentSize;      //buffer ��С
    unsigned int u32ContentOffset;    //��д��offset
}
ftp_client_s;

static int ftp_complete_cmd(void* _pData, int _u32DataLen, int* _pu32CompleteLen, void* cb_param)
{
    //DBG("_u32DataLen=%u\n", _u32DataLen);
    //ftp_client_s* pstFtpClient = (ftp_client_s*)cb_param;
    *_pu32CompleteLen = 0;
    char szLine[4*1024];
    int minSize = (sizeof(szLine) > _u32DataLen) ? _u32DataLen : sizeof(szLine);
    memcpy(szLine, _pData, minSize);
    szLine[sizeof(szLine)-1] = 0;
    
    char* szReturn = strstr(szLine, "\r\n");
    if (szReturn)
    {
        *_pu32CompleteLen = szReturn - szLine + 2;
    }

    //DBG("_u32DataLen: %u, CompleteLen: %d\n", _u32DataLen, *_pu32CompleteLen);
    
    return 0;
}

static int ftp_complete_data(void* _pData, int _u32DataLen, int* _pu32CompleteLen, void* cb_param)
{
    //DBG("_u32DataLen=%u\n", _u32DataLen);
    ftp_client_s* pstFtpClient = (ftp_client_s*)cb_param;
    *_pu32CompleteLen = 0;

    if (pstFtpClient->multi_pack_enable)
    {
        if (pstFtpClient->remain_size >= pstFtpClient->cache_size/2 
                && _u32DataLen >= pstFtpClient->cache_size/2)
        {
            *_pu32CompleteLen = pstFtpClient->cache_size/2;
            pstFtpClient->remain_size -= (*_pu32CompleteLen);
        }
        else if (pstFtpClient->remain_size == _u32DataLen)
        {
            *_pu32CompleteLen = pstFtpClient->remain_size;
            pstFtpClient->remain_size -= (*_pu32CompleteLen);
        }
        
        if (pstFtpClient->remain_size == 0)
        {
            pstFtpClient->multi_pack_enable = 0;
        }
        //DBG("multi_pack_enable: %d, remain_size: %d, _u32DataLen: %d, block size: %d, CompleteLen: %d\n", 
        //            pstFtpClient->multi_pack_enable, pstFtpClient->remain_size,
        //            _u32DataLen, pstFtpClient->cache_size/2, (*_pu32CompleteLen));
    }

    DBG("_u32DataLen: %u, CompleteLen: %d\n", _u32DataLen, *_pu32CompleteLen);

    return 0;
}

static int ftp_client_parseDomainName(char* szDomainName, char* szOutIp, int len)  
{  
    memset(szOutIp, 0, len);
    int ret = -1;
    struct addrinfo *answer = NULL;
    struct addrinfo hint;
    bzero(&hint, sizeof(hint));
    struct addrinfo* curr = NULL;
    char ipstr[16];
    memset(ipstr, 0, sizeof(ipstr));
    hint.ai_family = AF_INET;
    hint.ai_socktype = SOCK_STREAM;
    ret = getaddrinfo(szDomainName, NULL, &hint, &answer);
    CHECK(ret == 0, -1, "error with %#x: %s\n", ret, strerror(errno));
    
    for (curr = answer; curr != NULL; curr = curr->ai_next) 
    {
        memset(ipstr, 0, sizeof(ipstr));
        const char* pRet = inet_ntop(AF_INET, &(((struct sockaddr_in *)(curr->ai_addr))->sin_addr), ipstr, 16);
        CHECK(pRet != NULL, -1, "error with %#x: %s\n", ret, strerror(errno));
        DBG("ipaddress:%s\n", ipstr);
        
        if (strlen(szOutIp) == 0)
        {
            strcpy(szOutIp, ipstr);
        }
    }
    freeaddrinfo(answer); 
    return 0;  
} 

static int ftp_client_setup_tcp(char* ip, int port)
{
    int ret = -1;
    int Fd = socket(AF_INET, SOCK_STREAM, 0);
    CHECK(Fd > 0, -1, "error with %#x: %s\n", Fd, strerror(errno));

    struct sockaddr_in Addr;
    memset((char *)&Addr, 0, sizeof(struct sockaddr_in));
    Addr.sin_family = AF_INET;
    Addr.sin_port = htons(port);
    Addr.sin_addr.s_addr = inet_addr(ip);

    ret = connect(Fd, (struct sockaddr *)&Addr, sizeof(struct sockaddr));
    CHECK(ret == 0 || close(Fd), -1, "error with %#x: %s\n", ret, strerror(errno));
    
    return Fd;
}

static int ftp_client_GetKeyValue(char* _szBegin, char* _szEnd, char* _szStartKey,
                                   char* _szEndKey, char* _szValue, int _len)
{
    int ret = -1;
    char* szValue;
    char* szReturn;

    memset(_szValue, 0, _len);
    szValue = strstr(_szBegin, _szStartKey);
    //szValue = _SafeFind(_szBegin, _szEnd, _szStartKey);
    if (szValue != NULL)
    {
        szValue += strlen(_szStartKey);
        szReturn = strstr(szValue, _szEndKey);
        //szReturn = _SafeFind(szValue, _szEnd, _szEndKey);
        if (szReturn != NULL)
        {
            CHECK(_len > szReturn - szValue, -1, "buffer is too small[%d bytes]\n", _len);
            memcpy(_szValue, szValue, szReturn - szValue);
            _szValue[szReturn - szValue] = 0;
            ret = 0;
        }
    }
    return ret;
}

static int ftp_client_send_request(ftp_client_s* pstFtpClient)
{
    int ret = -1;
    char szRequest[512];
    memset(szRequest, 0, sizeof(szRequest));
    
    if (pstFtpClient->enFtpStep == FTP_STEP_USER)
    {
        sprintf(szRequest, "USER %s\r\n", pstFtpClient->szUserName);
    }
    else if (pstFtpClient->enFtpStep == FTP_STEP_PASS)
    {
        sprintf(szRequest, "PASS %s\r\n", pstFtpClient->szPassword);
    }
    else if (pstFtpClient->enFtpStep == FTP_STEP_TYPE)
    {
        sprintf(szRequest, "TYPE I\r\n");
    }
    else if (pstFtpClient->enFtpStep == FTP_STEP_PASV)
    {
        sprintf(szRequest, "PASV\r\n");
    }
    else if (pstFtpClient->enFtpStep == FTP_STEP_SIZE)
    {
        sprintf(szRequest, "SIZE %s\r\n", pstFtpClient->szFileName);
    }
    else if (pstFtpClient->enFtpStep == FTP_STEP_RETR)
    {
        sprintf(szRequest, "RETR %s\r\n", pstFtpClient->szFileName);
    }
    else if (pstFtpClient->enFtpStep == FTP_STEP_STOR)
    {
        sprintf(szRequest, "STOR %s\r\n", pstFtpClient->szFileName);
    }
    else if (pstFtpClient->enFtpStep == FTP_STEP_QUIT)
    {
        sprintf(szRequest, "QUIT\r\n");
    }
    
    if (strlen(szRequest) > 0)
    {
        DBG("send: \n%s\n", szRequest);
        ret = select_send(pstFtpClient->hndSocketCmd, szRequest, strlen(szRequest));
        CHECK(ret == 0, -1, "Error with %#x\n", ret);
        
        if (pstFtpClient->enFtpStep == FTP_STEP_RETR)
        {
            //�������ݶ˿�
            pstFtpClient->enFtpStep = FTP_STEP_RETRING;
        }
        else if (pstFtpClient->enFtpStep == FTP_STEP_STOR)
        {
            //�������ݶ˿�
            pstFtpClient->enFtpStep = FTP_STEP_STORING;
        }
        else
        {
            pstFtpClient->enFtpStep = FTP_STEP_INVALID;
        }
    }

    return 0;
}

//�ͻ��˷��� FTP ����󣬷�����������Ӧ�롣
//��Ӧ������λ���ֱ����ʾ��
//��һ�����ָ���������״̬��һ����ָʾ��������Ӧ�ɹ���ʧ�ܻ�������
//�ڶ�����������Ӧ���͵ķ��࣬�� 2 ����������йص���Ӧ��3 �����û���֤��
//�����������ṩ�˸�����ϸ����Ϣ��
//��һ�����ֵĺ������£�
//1 ��ʾ��������ȷ������Ϣ����δ����
//2 ��ʾ�������Ѿ���ȷ������Ϣ��
//3 ��ʾ��������ȷ������Ϣ�����ڴ���
//4 ��ʾ��Ϣ��ʱ����
//5 ��ʾ��Ϣ���ô���
//�ڶ������ֵĺ������£�
//0 ��ʾ�﷨��
//1 ��ʾϵͳ״̬����Ϣ��
//2 ��ʾ����״̬��
//3 ��ʾ���û���֤�йص���Ϣ��
//4 ��ʾδ���塣
//5 ��ʾ���ļ�ϵͳ�йص���Ϣ��
// exsample
//125 ����ͨ���Ѿ���;���俪ʼ�� 
//200 ������� 
//214 �������ġ� 
//331 �û���������Ҫ�������� 
//425 ���ܴ�����ͨ���� 
//500 �﷨����(δ�Ͽ�����)�� 
//501 �﷨����(��Ч����)�� 
//502 δʵ�ֵ�MODE(��ʽ����)���͡�
// 
//wireshark ftpget sample
//220 Welcome to LZL's FTP Server V4.0.0
//USER root
//331 Password required for root
//PASS 123456
//230 Client :root successfully logged in. Client IP :192.168.0.120
//TYPE I
//200 Type set to I
//PASV
//227 Entering Passive Mode (192,168,136,32,4,0).
//SIZE treeinfo.wc
//213 448647
//RETR treeinfo.wc
//150 Opening BINARY mode data connection for file transfer.
//226 Transfer complete.
//QUIT
//220 Bye
// 
//wireshark ftpput sample
//220 Welcome to LZL's FTP Server V4.0.0
//USER root
//331 Password required for root
//PASS 123456
//230 Client :root successfully logged in. Client IP :192.168.0.120
//TYPE I
//200 Type set to I
//PASV
//227 Entering Passive Mode (192,168,136,32,4,6).
//STOR snap_11.jpg
//150 Opening BINARY mode data connection for file transfer.
//226 Transfer complete.
//QUIT
//220 Bye
// 
//STOR �ļ���\r\n	�ϴ��ļ�
//APPE �ļ���\r\n	�ϴ��ļ�,����ļ����Ѵ���,�����ݲ���β��
//DELE �ļ���\r\n	ɾ��ָ���ļ�
//REST �ֽڸ���\r\n	�����ֽ���,�̵�����,�����ļ�ǰʹ��,ʹRETR���������ƫ�ƺ�Ĳ���
//RETR �ļ���\r\n	�����ļ�
//ABOR\r\n	��������һ���ļ�,���ر��ļ��׽���ͨ��
// TYPE �ַ�\r\n	ѡ��������
//AΪ�ı�ģʽ
//IΪ������ģʽ
//EΪEBCDIC
//NΪNonprint�Ǵ�ӡģʽ
//TΪTelnet��ʽ���Ʒ�

static int ftp_client_recv_response(ftp_client_s* pstFtpClient, char* szResponse, int len)
{
    int ret = -1;

    DBG("recv: \n%s\n", szResponse);
    //DBG("logined: %d\n", pstFtpClient->logined);
    if (!pstFtpClient->logined && !strncmp(szResponse, "220", 3))
    {
        pstFtpClient->enFtpStep = FTP_STEP_USER;
    }
    else if (!strncmp(szResponse, "331", 3))
    {
        pstFtpClient->enFtpStep = FTP_STEP_PASS;
    }
    else if (!strncmp(szResponse, "230", 3))
    {
        pstFtpClient->enFtpStep = FTP_STEP_TYPE;
        pstFtpClient->logined = 1;
    }
    else if (!strncmp(szResponse, "200", 3))
    {
        pstFtpClient->enFtpStep = FTP_STEP_PASV;
    }
    else if (!strncmp(szResponse, "227", 3))
    {
        char szTmp[512];
        memset(szTmp, 0, sizeof(szTmp));
        ret = ftp_client_GetKeyValue(szResponse, szResponse + strlen(szResponse), "(", ")", szTmp, sizeof(szTmp));
        CHECK(ret == 0, -1, "error with %#x\n", ret);
        
        DBG("szTmp: %s\n", szTmp);
        int digit[6] = {0};
        int idx = 0;
        digit[idx++] = atoi(szTmp);
        char* find = strstr(szTmp, ",");
        if (find)
        {
            digit[idx++] = atoi(find+1);
        }
        find = strstr(find+1, ",");
        if (find)
        {
            digit[idx++] = atoi(find+1);
        }
        find = strstr(find+1, ",");
        if (find)
        {
            digit[idx++] = atoi(find+1);
        }
        find = strstr(find+1, ",");
        if (find)
        {
            digit[idx++] = atoi(find+1);
        }
        find = strstr(find+1, ",");
        if (find)
        {
            digit[idx++] = atoi(find+1);
        }
        DBG("digit[6]: %d %d %d %d %d %d\n", digit[0], digit[1], digit[2], digit[3], digit[4], digit[5]);
        pstFtpClient->portData = digit[4] * 256 + digit[5];
        
        if (pstFtpClient->bGetEnable)
        {
            pstFtpClient->enFtpStep = FTP_STEP_SIZE;
        }
        if (pstFtpClient->bPutEnable)
        {
            pstFtpClient->enFtpStep = FTP_STEP_STOR;
        }
    }
    else if (!strncmp(szResponse, "213", 3))
    {
        pstFtpClient->u32ContentSize = atoi(szResponse+4);
        pstFtpClient->u32ContentOffset = 0;
        pstFtpClient->pu8Content = mem_malloc(pstFtpClient->u32ContentSize+1);
        CHECK(pstFtpClient->pu8Content, -1, "error with %#x\n", pstFtpClient->pu8Content);
        memset(pstFtpClient->pu8Content, 0, pstFtpClient->u32ContentSize+1);
        pstFtpClient->remain_size = pstFtpClient->u32ContentSize;
        pstFtpClient->multi_pack_enable = 1;
        
        pstFtpClient->enFtpStep = FTP_STEP_RETR;
    }
    else if (!strncmp(szResponse, "150", 3))
    {
        //pstFtpClient->enFtpStep = FTP_STEP_INVALID;
        //pstFtpClient->enFtpStep = FTP_STEP_RETRING;
    }
    else if (!strncmp(szResponse, "226", 3))
    {
        //pstFtpClient->enFtpStep = FTP_STEP_QUIT;
    }
    else if (!strncmp(szResponse, "220", 3))
    {
        pstFtpClient->enFtpStep = FTP_STEP_END;
    }
    else
    {
        WRN("Unknown response: %s\n", szResponse);
        return -1;
    }
    
    //DBG("enFtpStep: %d\n", pstFtpClient->enFtpStep);

    return 0;
}

static void* ftp_client_proc(void* arg)
{
    int ret = -1;
    ftp_client_s* pstFtpClient = (ftp_client_s*)arg;

    ret = ftp_client_parseDomainName(pstFtpClient->szHost, pstFtpClient->szIp, sizeof(pstFtpClient->szIp));
    GOTO(ret == 0, pstFtpClient->enStatus = FTP_STATUS_FINISH_ERROR, _EXIT, "Error with: %#x\n", ret);

    unsigned int u32ExpectTimeout = 0;
    unsigned int u32Timeout = 0;
    char* data = NULL;
    int len = 0;
    
    DBG("bGetEnable: %d, bPutEnable: %d\n", pstFtpClient->bGetEnable, pstFtpClient->bPutEnable);

    while (pstFtpClient->bRunning)
    {
        if (pstFtpClient->hndSocketCmd == NULL)
        {
            pstFtpClient->FdCmd = ftp_client_setup_tcp(pstFtpClient->szIp, pstFtpClient->portCmd);
            GOTO(pstFtpClient->FdCmd > 0, pstFtpClient->enStatus = FTP_STATUS_FINISH_ERROR, _EXIT, "Error with: %#x\n", pstFtpClient->FdCmd);

            pstFtpClient->cache_size = 4*1024;
            pstFtpClient->hndSocketCmd = select_init(ftp_complete_cmd, pstFtpClient, pstFtpClient->cache_size, pstFtpClient->FdCmd);
            GOTO(pstFtpClient->hndSocketCmd, pstFtpClient->enStatus = FTP_STATUS_FINISH_ERROR, _EXIT, "Error with: %#x\n", pstFtpClient->hndSocketCmd);

            ret = select_debug(pstFtpClient->hndSocketCmd, 0);
            GOTO(ret == 0, pstFtpClient->enStatus = FTP_STATUS_FINISH_ERROR, _EXIT, "Error with: %#x\n", ret);
        }
        
        u32ExpectTimeout = pstFtpClient->timeout;
        u32Timeout = select_rtimeout(pstFtpClient->hndSocketCmd);
        GOTO(u32Timeout < u32ExpectTimeout, pstFtpClient->enStatus = FTP_STATUS_READ_TIMEOUT, _EXIT, "Read  Timeout %u, expect %u\n", u32Timeout, u32ExpectTimeout);

        u32ExpectTimeout = pstFtpClient->timeout;
        u32Timeout = select_wtimeout(pstFtpClient->hndSocketCmd);
        GOTO(u32Timeout < u32ExpectTimeout, pstFtpClient->enStatus = FTP_STATUS_WRITE_TIMEOUT, _EXIT, "Write Timeout %u, expect %u\n", u32Timeout, u32ExpectTimeout);
        
        ret = ftp_client_send_request(pstFtpClient);
        GOTO(ret == 0, pstFtpClient->enStatus = FTP_STATUS_FINISH_ERROR, _EXIT, "Error with: %#x\n", ret);
        
        do
        {
            data = NULL;
            len = 0;
            ret = select_recv_get(pstFtpClient->hndSocketCmd, (void**)&data, &len);
            GOTO(ret == 0, pstFtpClient->enStatus = FTP_STATUS_FINISH_ERROR, _EXIT, "Error with: %#x\n", ret);
            if (data != NULL)
            {
                GOTO((((unsigned int)data)%4) == 0, pstFtpClient->enStatus = FTP_STATUS_FINISH_ERROR, _EXIT, "pData %p is not align\n", data);
                //DBG("recv package.size: %d\n", len);
                
                char szTmp[1024];
                memset(szTmp, 0, sizeof(szTmp));
                
                memcpy(szTmp, data, len);
                ret = ftp_client_recv_response(pstFtpClient, szTmp, len);
                GOTO(ret == 0, pstFtpClient->enStatus = FTP_STATUS_FINISH_ERROR, _EXIT, "Error with: %#x\n", ret);

                ret = select_recv_release(pstFtpClient->hndSocketCmd, (void**)&data, &len);
                GOTO(ret == 0, pstFtpClient->enStatus = FTP_STATUS_FINISH_ERROR, _EXIT, "Error with: %#x\n", ret);
            }
        }
        while (data != NULL && pstFtpClient->bRunning);
        
        //���ݶ˿���������ݴ��䣬��ʼ������˿ڷ���QUIT
        if ((pstFtpClient->enFtpStep == FTP_STEP_RETRING || pstFtpClient->enFtpStep == FTP_STEP_STORING) 
                && pstFtpClient->progress == 100)
        {
            pstFtpClient->enFtpStep = FTP_STEP_QUIT;
        }
        
        ret = select_rw(pstFtpClient->hndSocketCmd);
        GOTO(ret == 0, pstFtpClient->enStatus = FTP_STATUS_FINISH_ERROR, _EXIT, "Error with: %#x\n", ret);
        
        if (pstFtpClient->enFtpStep == FTP_STEP_END)
        {
            //DBG("pstFtpClient->enFtpStep: %d\n", pstFtpClient->enFtpStep);
            pstFtpClient->enStatus = FTP_STATUS_FINISH_OK;
            goto _EXIT;
        }
        
        //�������ݶ˿ڽ��н�������
        if (pstFtpClient->enFtpStep == FTP_STEP_RETRING || pstFtpClient->enFtpStep == FTP_STEP_STORING)
        {
            //DBG("pstFtpClient->enFtpStep: %d\n", pstFtpClient->enFtpStep);
            if (pstFtpClient->hndSocketData == NULL)
            {
                pstFtpClient->FdData = ftp_client_setup_tcp(pstFtpClient->szIp, pstFtpClient->portData);
                GOTO(pstFtpClient->FdData > 0, pstFtpClient->enStatus = FTP_STATUS_FINISH_ERROR, _EXIT, "Error with: %#x\n", pstFtpClient->FdData);

                pstFtpClient->cache_size = 1024*1024;
                pstFtpClient->hndSocketData = select_init(ftp_complete_data, pstFtpClient, pstFtpClient->cache_size, pstFtpClient->FdData);
                GOTO(pstFtpClient->hndSocketData, pstFtpClient->enStatus = FTP_STATUS_FINISH_ERROR, _EXIT, "Error with: %#x\n", pstFtpClient->hndSocketData);

                ret = select_debug(pstFtpClient->hndSocketData, 0);
                GOTO(ret == 0, pstFtpClient->enStatus = FTP_STATUS_FINISH_ERROR, _EXIT, "Error with: %#x\n", ret);
            }
            
            if (pstFtpClient->bGetEnable)
            {
                u32ExpectTimeout = pstFtpClient->timeout;
                u32Timeout = select_rtimeout(pstFtpClient->hndSocketData);
                GOTO(u32Timeout < u32ExpectTimeout, pstFtpClient->enStatus = FTP_STATUS_READ_TIMEOUT, _EXIT, "Read  Timeout %u, expect %u\n", u32Timeout, u32ExpectTimeout);
            }
            if (pstFtpClient->bPutEnable)
            {
                u32ExpectTimeout = pstFtpClient->timeout;
                u32Timeout = select_wtimeout(pstFtpClient->hndSocketData);
                GOTO(u32Timeout < u32ExpectTimeout, pstFtpClient->enStatus = FTP_STATUS_WRITE_TIMEOUT, _EXIT, "Write Timeout %u, expect %u\n", u32Timeout, u32ExpectTimeout);
            }
            
            do
            {
                data = NULL;
                len = 0;
                ret = select_recv_get(pstFtpClient->hndSocketData, (void**)&data, &len);
                GOTO(ret == 0, pstFtpClient->enStatus = FTP_STATUS_FINISH_ERROR, _EXIT, "Error with: %#x\n", ret);
                if (data != NULL)
                {
                    GOTO((((unsigned int)data)%4) == 0, pstFtpClient->enStatus = FTP_STATUS_FINISH_ERROR, _EXIT, "pData %p is not align\n", data);
                    DBG("recv package.size: %d\n", len);
                    
                    if (pstFtpClient->bGetEnable && pstFtpClient->pu8Content)
                    {
                        memcpy(pstFtpClient->pu8Content+pstFtpClient->u32ContentOffset, data, len);
                        pstFtpClient->u32ContentOffset += len;
                        pstFtpClient->progress = pstFtpClient->u32ContentOffset*100/pstFtpClient->u32ContentSize;
                    }

                    ret = select_recv_release(pstFtpClient->hndSocketData, (void**)&data, &len);
                    GOTO(ret == 0, pstFtpClient->enStatus = FTP_STATUS_FINISH_ERROR, _EXIT, "Error with: %#x\n", ret);

                    if (pstFtpClient->bGetEnable && pstFtpClient->pu8Content && pstFtpClient->u32ContentOffset == pstFtpClient->u32ContentSize)
                    {
                        DBG("recv complete content: %d\n", pstFtpClient->u32ContentSize);
                        pstFtpClient->progress = 100;

                        //�ȹر�����socket,����socket�����յ� 226 Transfer complete.
                        close(pstFtpClient->FdData);
                        pstFtpClient->FdData = -1;
                    }
                }
            }
            while (data != NULL && pstFtpClient->bRunning);
            
            if (pstFtpClient->bPutEnable && pstFtpClient->multi_pack_enable)
            {
                int send_size = 0;
                if (pstFtpClient->remain_size >= pstFtpClient->cache_size)
                {
                    send_size = pstFtpClient->cache_size;
                    
                }
                else
                {
                    send_size = pstFtpClient->remain_size;
                }
                //DBG("send_size: %d\n", send_size);
                //DBG("ftpput progress: %d\n", pstFtpClient->progress);
                if (send_size > 0 && select_wlist_empty(pstFtpClient->hndSocketData))
                {
                    ret = select_send(pstFtpClient->hndSocketData, pstFtpClient->pu8Content+pstFtpClient->u32ContentOffset, send_size);
                    GOTO(ret == 0, pstFtpClient->enStatus = FTP_STATUS_FINISH_ERROR, _EXIT, "Error with: %#x\n", ret);

                    pstFtpClient->u32ContentOffset += send_size;
                    pstFtpClient->remain_size -= send_size;
                    //ʵ�ʻ�û����ȥ�����cache_size�㹻��Ļ�������progress�͵���100�ˡ�
                    // ������-1����������ɺ�����߼��ж�
                    pstFtpClient->progress = pstFtpClient->u32ContentOffset*100/pstFtpClient->u32ContentSize-1;
                    pstFtpClient->progress = (pstFtpClient->progress < 0) ? 0 : pstFtpClient->progress;
                }

                if (pstFtpClient->pu8Content && pstFtpClient->u32ContentOffset == pstFtpClient->u32ContentSize 
                        && select_wlist_empty(pstFtpClient->hndSocketData))
                {
                    DBG("send complete content: %d\n", pstFtpClient->u32ContentSize);
                    pstFtpClient->progress = 100;

                    //�ȹر�����socket,����socket�����յ� 226 Transfer complete.
                    close(pstFtpClient->FdData);
                    pstFtpClient->FdData = -1;
                }
            }
            
            //���ݶ˿ڽ�����ɲ���Ҫ�ٵ���select_rw����ΪԶ���Ѿ��رգ��᷵�ش��󡣵���ֱ���˳�����ʱ�������δ���
            if (!select_wlist_empty(pstFtpClient->hndSocketData) || pstFtpClient->progress != 100)
            {
                ret = select_rw(pstFtpClient->hndSocketData);
                GOTO(ret == 0, pstFtpClient->enStatus = FTP_STATUS_FINISH_ERROR, _EXIT, "Error with: %#x\n", ret);
            }
        }
    }
    
_EXIT:
    if (pstFtpClient->hndSocketCmd)
    {
        ret = select_destroy(pstFtpClient->hndSocketCmd);
        CHECK(ret == 0, NULL, "Error with %#x\n", ret);
        pstFtpClient->hndSocketCmd = NULL;
    }
    if (pstFtpClient->hndSocketData)
    {
        ret = select_destroy(pstFtpClient->hndSocketData);
        CHECK(ret == 0, NULL, "Error with %#x\n", ret);
        pstFtpClient->hndSocketData = NULL;
    }
    
    pstFtpClient->bRunning = 0;

    if (pstFtpClient->FdCmd > 0)
    {
        DBG("ftp client cmd[%d] exit done.\n", pstFtpClient->FdCmd);
        close(pstFtpClient->FdCmd);
        pstFtpClient->FdCmd = -1;
    }
    if (pstFtpClient->FdData > 0)
    {
        DBG("ftp client data[%d] exit done.\n", pstFtpClient->FdData);
        close(pstFtpClient->FdData);
        pstFtpClient->FdData = -1;
    }
    
    return NULL;
}

handle ftp_client_init(char* szHost, int portCmd, char* szUserName, char* szPassword)
{
    //int s32Ret = -1;
    ftp_client_s* pstFtpClient = (ftp_client_s*)mem_malloc(sizeof(ftp_client_s));
    CHECK(pstFtpClient, NULL, "error with %#x\n", pstFtpClient);
    memset(pstFtpClient, 0, sizeof(ftp_client_s));
    
    CHECK(strlen(szHost) < sizeof(pstFtpClient->szHost), NULL, "invalid szHost %s\n", szHost);
    strcpy(pstFtpClient->szHost, szHost);
    
    CHECK(strlen(szUserName) < sizeof(pstFtpClient->szUserName), NULL, "invalid szUserName %s\n", szUserName);
    strcpy(pstFtpClient->szUserName, szUserName);
    
    CHECK(strlen(szPassword) < sizeof(pstFtpClient->szPassword), NULL, "invalid szPassword %s\n", szPassword);
    strcpy(pstFtpClient->szPassword, szPassword);
    
    pstFtpClient->portCmd = portCmd;
    
    return pstFtpClient;
}

int ftp_client_exit(handle hndftpClient)
{
    CHECK(hndftpClient, -1, "hndftpClient is not valid\n");
    
    //int ret = -1;
    ftp_client_s* pstFtpClient = (ftp_client_s*)hndftpClient;

    mem_free(pstFtpClient);
    pstFtpClient = NULL;
    return 0;
}

int ftp_client_startGet(handle hndftpClient, char* szFileName, int timeout)
{
    CHECK(hndftpClient, -1, "hndftpClient is not valid\n");

    ftp_client_s* pstFtpClient = (ftp_client_s*)hndftpClient;
    int s32Ret = -1;

    CHECK(strlen(szFileName) < sizeof(pstFtpClient->szFileName), -1, "invalid szFileName %s\n", szFileName);
    strcpy(pstFtpClient->szFileName, szFileName);
    pstFtpClient->timeout = timeout;
    
    pstFtpClient->bGetEnable = 1;
    pstFtpClient->bPutEnable = 0;
    
    pstFtpClient->pu8Content = NULL;
    pstFtpClient->u32ContentSize = 0;
    pstFtpClient->u32ContentOffset = 0;
    
    pstFtpClient->enStatus = FTP_STATUS_PROGRESS;
    pstFtpClient->bRunning = 1;
    s32Ret = pthread_create(&pstFtpClient->tPid, NULL, ftp_client_proc, pstFtpClient);
    ASSERT(s32Ret == 0, "s32Ret is %d\n", s32Ret);

    return 0;
}

int ftp_client_startPut(handle hndftpClient, unsigned char* buffer, int len, char* szRemoteFileName, int timeout)
{
    CHECK(hndftpClient, -1, "hndftpClient is not valid\n");

    ftp_client_s* pstFtpClient = (ftp_client_s*)hndftpClient;
    int s32Ret = -1;

    CHECK(strlen(szRemoteFileName) < sizeof(pstFtpClient->szFileName), -1, "invalid szFileName %s\n", szRemoteFileName);
    strcpy(pstFtpClient->szFileName, szRemoteFileName);
    pstFtpClient->timeout = timeout;

    pstFtpClient->bGetEnable = 0;
    pstFtpClient->bPutEnable = 1;
    
    pstFtpClient->pu8Content = buffer;
    pstFtpClient->u32ContentSize = len;
    pstFtpClient->u32ContentOffset = 0;
    
    pstFtpClient->remain_size = pstFtpClient->u32ContentSize;
    pstFtpClient->multi_pack_enable = 1;

    pstFtpClient->enStatus = FTP_STATUS_PROGRESS;
    pstFtpClient->bRunning = 1;
    s32Ret = pthread_create(&pstFtpClient->tPid, NULL, ftp_client_proc, pstFtpClient);
    ASSERT(s32Ret == 0, "s32Ret is %d\n", s32Ret);

    return 0;
}

int ftp_client_stop(handle hndftpClient)
{
    CHECK(hndftpClient, -1, "hndftpClient is not valid\n");

    //int ret = -1;
    ftp_client_s* pstFtpClient = (ftp_client_s*)hndftpClient;
    
    if (pstFtpClient->tPid != 0)
    {
        pstFtpClient->bRunning = 0;
        pthread_join(pstFtpClient->tPid, NULL);
    }
    if (pstFtpClient->bGetEnable && pstFtpClient->pu8Content)
    {
        mem_free(pstFtpClient->pu8Content);
        pstFtpClient->pu8Content = NULL;
        pstFtpClient->u32ContentOffset = 0;
        pstFtpClient->u32ContentSize = 0;
    }

    return 0;
}

int ftp_client_Query(handle hndftpClient, FTP_STATUS_E* status)
{
    CHECK(hndftpClient, -1, "hndftpClient is not valid\n");
    CHECK(status, -1, "invalid parameter %#x\n", status);
    
    ftp_client_s* pstFtpClient = (ftp_client_s*)hndftpClient;
    *status = pstFtpClient->enStatus;

    return 0;
}

int ftp_client_ContentGet(handle hndftpClient, unsigned char** output, int* len)
{
    CHECK(hndftpClient, -1, "hndftpClient is not valid\n");
    CHECK(output, -1, "invalid parameter %#x\n", output);
    CHECK(len, -1, "invalid parameter %#x\n", len);

    ftp_client_s* pstFtpClient = (ftp_client_s*)hndftpClient;
    *output = pstFtpClient->pu8Content;
    *len = pstFtpClient->u32ContentSize;

    return 0;
}

int ftp_client_ProgressGet(handle hndftpClient, int* progress)
{
    CHECK(hndftpClient, -1, "hndftpClient is not valid\n");
    CHECK(progress, -1, "invalid parameter %#x\n", progress);

    ftp_client_s* pstFtpClient = (ftp_client_s*)hndftpClient;
    *progress = pstFtpClient->progress;

    return 0;
}



