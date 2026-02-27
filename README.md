#教程

本项目是brutus的改版，去除了openssl依赖（openssl 1.x），改用了Jubal Mordecai Velasco的[AES](https://github.com/mrdcvlsc/AES)实现

选择一个工作目录并进入,克隆 Brutus：
```
$ git clone https://github.com/pasze888/brutus.git
```

现在检查 `brutus_cc.cfg` 中的编译器标志。如果你的编译器较旧或系统特殊，可以放弃本地优化，使用通用选项，例如：
```
echo "gcc -Wall -O3" > brutus_cc.cfg 
```

准备编译库和测试框架。只需执行：
```
$ make
```
根据系统性能，这需要一定时间完成。首次调用 `make` 时，会先编译主测试代码和模块，然后 makefile 会调用 Python 编译脚本 `mk.py`（它替代了原有的 Bash 脚本 `mkaeadlibs.sh`）。

编译脚本 `mk.py` 会遍历 `crypto_aead/` 下的所有算法实现目录，将每个实现编译成共享库（`.so`）并放入 `aeadlibs/` 目录，同时将编译器的输出记录在对应的 `.err` 文件中。项目不再需要外部加密库（如 OpenSSL）。

最终，`aeadlibs.txt` 文件包含了成功生成库的算法列表。所有动态库都在 `aeadlibs` 子目录中。每个库的编译输出为 `*.err` 文件，`*.so` 是生成的共享库（如果存在）。例如：

```
$ ls aeadlibs/stribob192*
aeadlibs/stribob192r1-8bit.err    aeadlibs/stribob192r2d2-bitslice.err
aeadlibs/stribob192r1-8bit.so     aeadlibs/stribob192r2d2-bitslice.so
aeadlibs/stribob192r1-ref.err     aeadlibs/stribob192r2d2-neon.err
aeadlibs/stribob192r1-ref.so      aeadlibs/stribob192r2d2-ref.err
aeadlibs/stribob192r1-xmm.err     aeadlibs/stribob192r2d2-ref.so
aeadlibs/stribob192r1-xmm.so      aeadlibs/stribob192r2d2-ssse3.err
aeadlibs/stribob192r2d2-8bit.err  aeadlibs/stribob192r2d2-ssse3.so
aeadlibs/stribob192r2d2-8bit.so
```

我们还有一个可执行文件 `brutus`：

```
$ ./brutus
用法: brutus [选项] aead1.so aead2.so ..
  -h   快速帮助
  -q   关闭详细输出
  -kN  生成最大长度 N 的 KAT
  -tN  N 秒后强制退出
  -rN  使用随机种子 N
  -cN  一致性测试（超时 N 秒）
  -sN  加密/认证速度测试（每个 N 秒）
  -fN  快速吞吐量测试（加密/解密各 N 秒）
```

调用 Brutus 时需要指定选项和库文件名。下面的通配符命令可以快速测试 Keyak 的所有变体的速度和一致性。注意所有数字参数 `N` 都是可选的，有默认值。

```
$ ./brutus -c2 -f aeadlibs/*keyakv1-*.so

BRUTUS (2014年9月24日) 作者 Markku-Juhani O. Saarinen <mjos@iki.fi>
[lakekeyakv1-ref] 一致性检查 (限制=2秒)  key=16  nsec=0  npub=16  a=16
[lakekeyakv1-ref] 吞吐量测试 (限制=1秒)  key=16  nsec=0  npub=16 a=16
[lakekeyakv1-ref] 43788.04 kB/s  加密(mlen=65536 adlen=0)
[lakekeyakv1-ref] 43811.63 kB/s  解密(mlen=65536 adlen=0)
[oceankeyakv1-ref] 一致性检查 (限制=2秒)  key=16  nsec=0  npub=16  a=16
[oceankeyakv1-ref] 吞吐量测试 (限制=1秒)  key=16  nsec=0  npub=16 a=16
[oceankeyakv1-ref] 43156.03 kB/s  加密(mlen=65536 adlen=0)
[oceankeyakv1-ref] 43047.13 kB/s  解密(mlen=65536 adlen=0)
[riverkeyakv1-ref] 一致性检查 (限制=2秒)  key=16  nsec=0  npub=16  a=16
[riverkeyakv1-ref] 吞吐量测试 (限制=1秒)  key=16  nsec=0  npub=16 a=16
[riverkeyakv1-ref] 18984.20 kB/s  加密(mlen=65536 adlen=0)
[riverkeyakv1-ref] 18877.08 kB/s  解密(mlen=65536 adlen=0)
[seakeyakv1-ref] 一致性检查 (限制=2秒)  key=16  nsec=0  npub=16  a=16
[seakeyakv1-ref] 吞吐量测试 (限制=1秒)  key=16  nsec=0  npub=16 a=16
[seakeyakv1-ref] 42998.03 kB/s  加密(mlen=65536 adlen=0)
[seakeyakv1-ref] 43321.04 kB/s  解密(mlen=65536 adlen=0)
```