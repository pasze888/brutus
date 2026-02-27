#!/usr/bin/env python3
# mk.py - 编译所有 AEAD 实现为共享库


import subprocess
from pathlib import Path
import shutil
import shlex

# 配置
CRYPTO_AEAD = Path("crypto_aead")
AEADLIBS = Path("aeadlibs")
COMPILER_CFG = Path("brutus_cc.cfg")
INC_DIRS = ["inc"]  # 额外的头文件搜索路径


def read_compiler():
    """从配置文件读取编译器命令"""
    with open(COMPILER_CFG) as f:
        return f.read().strip()


def find_impl_dirs(base_dir):
    """返回所有算法实现目录列表（格式：base_dir/alg/impl）"""
    p = []
    flag = 0
    for i in Path(base_dir).iterdir():
        if i.is_dir():
            flag = 1
            p.extend(find_impl_dirs(i))
    if flag == 0:
        p.append(base_dir)
    return p


def collect_sources(impl_dir):
    """收集实现目录下的所有源文件"""
    patterns = ["*.c", "*.cpp", "*.cc", "*.s", "*.S"]
    sources = []
    for pat in patterns:
        sources.extend(impl_dir.glob(pat))
    return sources


def compile_impl(compiler, impl_dir, lib_dir):
    """编译单个实现，返回成功标志"""
    lib_name = f"{impl_dir.parent.name}-{impl_dir.name}"
    lib_file = lib_dir / f"{lib_name}.so"
    err_file = lib_dir / f"{lib_name}.err"

    print(f"== {lib_name} ==")

    sources = collect_sources(impl_dir)
    src_list = [str(s) for s in sources] + ["src/aead_params.cpp", "src/aead_params.c"]
    print(f"源文件: {' '.join(src_list)}")

    # 构建编译命令
    compiler_args = shlex.split(compiler)
    cmd = compiler_args
    cmd.extend(["-shared", "-fPIC"])
    cmd.extend(["-o", str(lib_file)])
    for inc in INC_DIRS:
        cmd.append(f"-I{inc}")
    cmd.append(f"-I{impl_dir}")
    cmd.append(f'-DBRUTUS_NAME="{lib_name}"')
    cmd.append("-DUSE_INTEL_AESNI")
    cmd.extend(src_list)

    # 执行编译，捕获错误输出
    with open(err_file, "w") as errf:
        result = subprocess.run(cmd, stderr=errf)

    if result.returncode == 0 and lib_file.exists():
        size = lib_file.stat().st_size
        print(f"OK. 大小: {size} 字节")
        return True
    else:
        err_lines = sum(1 for _ in open(err_file))
        print(f"FAIL. 错误行数: {err_lines} (详情见 {err_file})")
        return False


def main():
    # 初始化
    compiler = read_compiler()
    # 清理并创建输出目录
    if AEADLIBS.exists():
        shutil.rmtree(AEADLIBS)
    AEADLIBS.mkdir(parents=True)

    impl_dirs = find_impl_dirs(CRYPTO_AEAD)
    log_file = "mkaeadlibs.log"

    with open(log_file, "w") as log:
        for impl_dir in impl_dirs:
            success = compile_impl(compiler, impl_dir, AEADLIBS)
            log.write(f"{success}\n")
            print(success)
            # 同时输出到屏幕和日志文件（通过 print 和 log.write）
            # 这里简单用 print，但需要将输出同时写入 log
            # 可以改用 tee 方式，但为简洁，此处省略完整 tee 实现

    # 生成库列表
    libs = sorted(AEADLIBS.glob("*.so"))
    with open("aeadlibs.txt", "w") as f:
        for lib in libs:
            f.write(str(lib) + "\n")


if __name__ == "__main__":
    main()
