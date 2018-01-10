#!/bin/sh
#�������е�������Դ�⣬��������̬���ͷ�ļ�����ǰĿ¼
#ע���ѹԴ����Ŀ¼��������ͷ�ļ���Ŀ¼����

#COMPILE=arm-hisiv300-linux-
COMPILE=arm-hisiv600-linux-

echo "COMPILE=${COMPILE}"
sleep 1

#libcurl.a
rm -rf libcurl
rm -rf curl-7.53.1
mkdir -p libcurl
tar -xzvf curl-7.53.1.tar.gz
cd ./curl-7.53.1;
./configure CC=${COMPILE}gcc --host=arm-linux
make
cp ./lib/.libs/libcurl.a ../ -af
cp include/curl/*.h ../libcurl -af
cd ../

#libixml.a
rm -rf libixml
rm -rf libixml-1.0
mkdir -p libixml
tar -xzvf libixml-1.0.tar.gz
cd ./libixml-1.0;
make CROSS=${COMPILE}
cp ./release/libixml.a ../ -af
cp ./*.h ../libixml -af
cd ../



