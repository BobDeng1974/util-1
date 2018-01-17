#!/bin/sh
#�������е�������Դ�⣬��������̬�⵽��ǰĿ¼

#COMPILE=arm-hisiv300-linux
COMPILE=arm-hisiv600-linux

echo "COMPILE=${COMPILE}"
sleep 3

# #libcurl.a
# rm -rf curl-7.53.1
# tar -xzvf curl-7.53.1.tar.gz
# cd ./curl-7.53.1;
# ./configure CC=${COMPILE}-gcc --host=arm-linux
# make
# cp ./lib/.libs/libcurl.a ../ -af
# cd ../

# #libixml.a
# rm -rf libixml-1.0
# tar -xzvf libixml-1.0.tar.gz
# cd ./libixml-1.0;
# make CROSS=${COMPILE}-
# cp ./release/libixml.a ../ -af
# cd ../

# #libjpeg.a
# rm -rf jpeg-8c
# tar -xzvf jpegsrc.v8c.tar.gz
# cd ./jpeg-8c;
# ./configure --host=${COMPILE}
# make
# cp ./.libs/libjpeg.a ../ -af
# cd ../

#libmd5.a
rm -rf libmd5
tar -xzvf libmd5.tar.gz
cd ./libmd5;
make CROSS_COMPILE=${COMPILE}
cp ./libmd5.a ../ -af
cd ../

#libtinyxml.a
rm -rf libtinyxml
tar -xzvf libtinyxml.tar.gz
cd ./libtinyxml;
make CROSS_COMPILE=${COMPILE}
cp ./libtinyxml.a ../ -af
cd ../

#libdigest.a
rm -rf libdigest
tar -xzvf libdigest.tar.gz
cd ./libdigest;
make CROSS_COMPILE=${COMPILE}
cp ./libdigest.a ../ -af
cd ../


