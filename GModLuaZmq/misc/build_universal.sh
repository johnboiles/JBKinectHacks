#!/bin/bash
# from http://permalink.gmane.org/gmane.network.zeromq.devel/5836
MY_ZMQ_PATH="/Users/johnb/Programming/Kinect"
echo "
...zeromq2 build autogen.sh...

"
cd $MY_ZMQ_PATH/zeromq2
sh autogen.sh

echo "

...zeromq2 build i386...

"
CFLAGS="-arch i386" CXXFLAGS="-arch i386" LDFLAGS="-arch i386" ./configure --prefix=$MY_ZMQ_PATH/zeromq2/lib_i386
echo "
...zeromq2 i386 make...

"
make clean
make

echo "
...zeromq2 i386 make check...

"
make check
make install

echo "

...zeromq2 i386 lipo:
"
lipo -info $MY_ZMQ_PATH/zeromq2/lib_i386/lib/libzmq.a

echo "

...zeromq2 x86_64 ./configure...
"
CFLAGS="-arch x86_64" CXXFLAGS="-arch x86_64" LDFLAGS="-arch x86_64" ./configure --prefix=$MY_ZMQ_PATH/zeromq2/lib_x86_64

echo "

...zeromq2 x86_64 make...
"
make clean
make

echo "

...zeromq2 x86_64 make check...
"
make check

echo "

...zeromq2 x86_64 make install...
"
make install

echo "

...zeromq2 x86_64 lipo:
"
lipo -info $MY_ZMQ_PATH/zeromq2/lib_x86_64/lib/libzmq.a

echo "

...zeromq2, using lipo to make universal library...
"
mkdir $MY_ZMQ_PATH/zeromq2/lib_universal
lipo -create  $MY_ZMQ_PATH/zeromq2/lib_i386/lib/libzmq.a $MY_ZMQ_PATH/zeromq2/lib_x86_64/lib/libzmq.a -output $MY_ZMQ_PATH/zeromq2/lib_universal/libzmq.a
lipo -create  $MY_ZMQ_PATH/zeromq2/lib_i386/lib/libzmq.1.dylib $MY_ZMQ_PATH/zeromq2/lib_x86_64/lib/libzmq.1.dylib -output $MY_ZMQ_PATH/zeromq2/lib_universal/libzmq.1.dylib

cd $MY_ZMQ_PATH/zeromq2/lib_universal
ln -sf libzmq.1.dylib libzmq.dylib

echo "

...zeromq2 build final lipo:
"
lipo -info $MY_ZMQ_PATH/zeromq2/lib_universal/libzmq.a

echo "

=== === zeromq2 build done === ===

"