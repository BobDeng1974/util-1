#ifndef __XML_H__
#define __XML_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

typedef void* handle_doc; //xml�ļ�ָ��
typedef void* handle_node;//xml�ڵ�ָ��
typedef void* handle_attr;//xml�ڵ�����ָ��

/*
 �� �� ��: xml_new
 ��������: ����һ��xml�ļ�ָ�룬����xml_delete���ʹ��
 �������: ��
 �������: ��
 �� �� ֵ: �ɹ������ļ�ָ��,ʧ�ܷ���С��NULL
*/
handle_doc xml_new();

/*
 �� �� ��: xml_delete
 ��������: �ͷ�һ��xml�ļ�ָ�룬����xml_new���ʹ��
 �������: hnddoc �ļ�ָ��
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int xml_delete(handle_doc hnddoc);

/*
 �� �� ��: xml_data
 ��������: ��xml���е����ݣ��ı����ݣ���д��buf����
 �������:  hnd �ļ�ָ��
            size buf��󳤶�
 �������: buf ���buf
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int xml_data(handle_doc hnd, char* buf, unsigned int size);

/*
 �� �� ��: xml_savefile
 ��������: ��xml�ĵ�ָ�뱣�浽�ļ�
 �������:  hnd �ļ�ָ��
            path �ļ�·��
 �������: ��
 �� �� ֵ: �ɹ�����0,ʧ�ܷ���С��0
*/
int xml_savefile(handle_doc hnd, char* path);

/*
 �� �� ��: xml_root_append
 ��������: ����һ�����ڵ㣨������xml_new֮�󣩣�ֻ����һ�����ڵ�
 �������:  hnd �ļ�ָ��
            node_name �ڵ�����
            node_text �ڵ�����
 �������: ��
 �� �� ֵ: �ɹ����������ڵ�ָ��,ʧ�ܷ���NULL
*/
handle_node xml_root_append(handle_doc hnd, char *node_name, char *node_text);

/*
 �� �� ��: xml_node_append
 ��������: ׷��һ����ͨ���ӽڵ�
 �������:  parent ���ڵ�
            node_name �ڵ�����
            node_text �ڵ�����
 �������: ��
 �� �� ֵ: �ɹ����������ڵ�ָ��,ʧ�ܷ���NULL
*/
handle_node xml_node_append(handle_node parent, char *node_name, char *node_text);

/*
 �� �� ��: xml_attr_append
 ��������: ׷��һ���ڵ�����
 �������:  parent ���ڵ�
            node_name �ڵ�����
            node_text �ڵ�����
 �������: ��
 �� �� ֵ: �ɹ��������ӽڵ�ָ��,ʧ�ܷ���NULL
*/
handle_node xml_attr_append(handle_node hndnode, char *attr_name, char *attr_text);

/*
 �� �� ��: xml_load_file
 ��������: ����һ��xml�ļ�����Ҫ��xml_unload���ʹ��
 �������:  path �ļ�·��
 �������: ��
 �� �� ֵ: �ɹ������ļ�ָ��,ʧ�ܷ���NULL
*/
handle_doc xml_load_file(char* path);

/*
 �� �� ��: xml_load_data
 ��������: ����һ��xml���ݣ���Ҫ��xml_unload���ʹ��
 �������:  data xml����
 �������: ��
 �� �� ֵ: �ɹ������ļ�ָ��,ʧ�ܷ���NULL
*/
handle_doc xml_load_data(char* data);

/*
 �� �� ��: xml_unload
 ��������: �ͷ��ļ�ָ�룬��Ҫ��xml_load_file/xml_load_data���ʹ��
 �������:  data xml����
 �������: ��
 �� �� ֵ: �ɹ������ļ�ָ��,ʧ�ܷ���NULL
*/
int xml_unload(handle_doc hnddoc);

/*
 �� �� ��: xml_node_root
 ��������: ��ȡ���ڵ�
 �������:  hnddoc �ļ�ָ��
 �������: ��
 �� �� ֵ: �ɹ����ؽڵ�ָ��,ʧ�ܷ���NULL
*/
handle_node xml_node_root(handle_doc hnddoc);

/*
 �� �� ��: xml_node_child
 ��������: ��ȡ���ӽڵ�
 �������:  hndnode �ڵ�ָ��
 �������: ��
 �� �� ֵ: �ɹ����ؽڵ�ָ��,ʧ�ܷ���NULL
*/
handle_node xml_node_child(handle_node hndnode);

/*
 �� �� ��: xml_node_next
 ��������: ��ȡͬ����һ���ڵ�
 �������:  hndnode �ڵ�ָ��
 �������: ��
 �� �� ֵ: �ɹ����ؽڵ�ָ��,ʧ�ܷ���NULL
*/
handle_node xml_node_next(handle_node hndnode);

/*
 �� �� ��: xml_node_name
 ��������: ��ȡ�ڵ�����
 �������:  hndnode �ڵ�ָ��
 �������: ��
 �� �� ֵ: �ɹ����ؽڵ�����,ʧ�ܷ���NULL
*/
const char* xml_node_name(handle_node hndnode);

/*
 �� �� ��: xml_node_text
 ��������: ��ȡ�ڵ�����
 �������:  hndnode �ڵ�ָ��
 �������: ��
 �� �� ֵ: �ɹ����ؽڵ�����,ʧ�ܷ���NULL
*/
const char* xml_node_text(handle_node hndnode);

/*
 �� �� ��: xml_attr_child
 ��������: ��ȡ�ڵ�ĵ�һ������
 �������:  hndnode �ڵ�ָ��
 �������: ��
 �� �� ֵ: �ɹ����ؽڵ�����,ʧ�ܷ���NULL
*/
handle_attr xml_attr_child(handle_node hndnode);

/*
 �� �� ��: xml_attr_next
 ��������: ��ȡͬ�����Ե���һ������
 �������:  hndattr �ڵ�����
 �������: ��
 �� �� ֵ: �ɹ����ؽڵ�����,ʧ�ܷ���NULL
*/
handle_attr xml_attr_next(handle_attr hndattr);

/*
 �� �� ��: xml_attr_name
 ��������: ��ȡ��������
 �������:  hndattr �ڵ�����
 �������: ��
 �� �� ֵ: �ɹ�������������,ʧ�ܷ���NULL
*/
const char* xml_attr_name(handle_attr hndattr);

/*
 �� �� ��: xml_attr_text
 ��������: ��ȡ��������
 �������:  hndattr �ڵ�����
 �������: ��
 �� �� ֵ: �ɹ�������������,ʧ�ܷ���NULL
*/
const char* xml_attr_text(handle_attr hndattr);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif

