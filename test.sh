#! /bin/bash

#  mkaeadlibs.sh 
#  21-Sep-14  Markku-Juhani O. Saarinen <mjos@iki.fi>

CRYPTO_AEAD=crypto_aead
AEADLIBS=aeadlibs
BRUTUS_CC=`cat brutus_cc.cfg`

# cleanup
rm -rf $AEADLIBS aeadlibs.txt 
mkdir $AEADLIBS

# 核心修改：遍历 $CRYPTO_AEAD 下所有叶子目录（无后续子目录的目录）
find $CRYPTO_AEAD -type d -exec bash -c '
  # 检查当前目录是否是叶子目录（无直接子目录）
  if [ -z "$(find "{}" -mindepth 1 -maxdepth 1 -type d)" ]; then
    echo "{}"
  fi
' \; | {
	while read srcdir
	do
		# 保持原有逻辑：将目录路径转换为 aead 名称（替换/为-）
		aead=`echo $srcdir | sed 's@'$CRYPTO_AEAD'/@@g' | tr '/' '-'`
		echo == $aead == 
		# 查找当前叶子目录下的所有源码文件
		srcfiles=`ls -1 $srcdir/*.c $srcdir/*.cpp $srcdir/*.cc \
			$srcdir/*.s $srcdir/*.S  2> /dev/null`
		echo COMPILING $srcfiles
		# 编译共享库（原有编译逻辑不变）
		$BRUTUS_CC -shared -fPIC -o $AEADLIBS/$aead.so \
			-Iinc -I$srcdir -DBRUTUS_NAME='"'$aead'"' \
			$srcfiles src/aead_params.c -lcrypto 2> $AEADLIBS/$aead.err
		if [ -e $AEADLIBS/$aead.so ]
		then
			echo -n 'OK.  ' 
			du -b $AEADLIBS/$aead.so 
		else
			echo -n 'FAIL:' 
			wc $AEADLIBS/$aead.err
		fi
		echo
	done } | tee mkaeadlibs.log

# create the list
ls -1 $AEADLIBS/*.so > aeadlibs.txt