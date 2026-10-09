"""verify-answers.py —— 核验讲义里的答案与程序实际输出是否一致

用途：改了讲义或演示程序后跑一遍，确认数字没写错。
      （教学材料的数字一旦写错，比代码出错更误导人。）

用法（在 c-learning 目录下）：
    python verify-answers.py

说明：用正则提取数值，不依赖空格数。需要先编译过各程序：
    .\b            # 编译运行全部，产出 build\*.exe
""""""严格核验：review_ch7 讲义里的答案 是否与各演示程序的实际输出一致。
用正则提取数值，不依赖空格数，避免上次那种误报。
"""
import os
import re
import subprocess
import sys

sys.stdout.reconfigure(encoding="utf-8", errors="replace")

CL = os.path.dirname(os.path.abspath(__file__))
os.chdir(CL)

BLOCK = re.compile(r"blocked|阻止|Application Control")


def run(name):
    exe = os.path.join(CL, "build", name + ".exe")
    if not os.path.exists(exe):
        return "NOEXE"
    try:
        r = subprocess.run([exe], capture_output=True, text=True,
                           encoding="utf-8", errors="replace", timeout=25)
    except OSError:
        return "BLOCKED"
    out = (r.stdout or "") + (r.stderr or "")
    return "BLOCKED" if BLOCK.search(out) else out


def grab(text, pattern, group=1):
    """从输出里抓一个数，找不到返回 None"""
    m = re.search(pattern, text)
    return m.group(group) if m else None


results = []


def check(desc, got, want):
    ok = (got == want)
    results.append((ok, desc, got, want))


print("=" * 72)
print("核验：讲义答案 vs 程序实际输出")
print("=" * 72)

# ---------------- sizes.c ----------------
s = run("sizes")
if s in ("NOEXE", "BLOCKED"):
    print("\n[sizes.c] 无法运行: {}".format(s))
else:
    print("\n[sizes.c] 各类型字节数")
    for label, pat, want in [
        ("char",    r"char\s+(\d+)\s*字节\s+范围", "1"),
        ("short",   r"short\s+(\d+)\s*字节", "2"),
        ("int",     r"(?m)^\s*int\s+(\d+)\s*字节", "4"),
        ("long",    r"(?m)^\s*long\s+(\d+)\s*字节", "4"),
        ("long long", r"long long\s+(\d+)\s*字节", "8"),
        ("float",   r"float\s+(\d+)\s*字节", "4"),
        ("double",  r"double\s+(\d+)\s*字节", "8"),
        ("char*",   r"char\s+\*\s+(\d+)\s*字节", "8"),
        ("int*",    r"int\s+\*\s+(\d+)\s*字节", "8"),
        ("double*", r"double\s+\*\s+(\d+)\s*字节", "8"),
        ("void*",   r"void\s+\*\s+(\d+)\s*字节", "8"),
        ("int ai[5]", r"ai\[5\]\s+(\d+)\s*字节", "20"),
        ("char ac[5]", r"ac\[5\]\s+(\d+)\s*字节", "5"),
        ("double ad[5]", r"ad\[5\]\s+(\d+)\s*字节", "40"),
    ]:
        got = grab(s, pat)
        check("sizes: sizeof(%s)" % label, got, want)
        print("   {:<16} = {:<4} (期望 {})".format(label, got, want))

# ---------------- ptr_sizeof.c ----------------
p = run("ptr_sizeof")
if p in ("NOEXE", "BLOCKED"):
    print("\n[ptr_sizeof.c] 无法运行: {}".format(p))
else:
    print("\n[ptr_sizeof.c] 指针算术 / sizeof / 2[a]")
    for desc, pat, want in [
        ("字节差(3个int)", r"字节差\s*=\s*(\d+)\s*字节", "12"),
        ("元素差", r"元素差\s*=\s*(\d+)\s*个元素", "3"),
        ("sizeof(a)", r"sizeof\(a\)\s*=\s*(\d+)", "20"),
        ("sizeof(p)", r"sizeof\(p\)\s*=\s*(\d+)", "8"),
        ("元素个数", r"元素个数\s*=\s*sizeof\(a\)\s*/\s*sizeof\(a\[0\]\)\s*=\s*(\d+)", "5"),
        ("sizeof(a+0)", r"sizeof\(a\+0\)\s*=\s*(\d+)", "8"),
        ("a[2]", r"a\[2\]\s*=\s*(\d+)", "30"),
        ("2[a]", r"2\[a\]\s*=\s*(\d+)", "30"),
        ("函数内 sizeof(arr)", r"sizeof\(arr\)\s*=\s*(\d+)", "8"),
    ]:
        got = grab(p, pat)
        check("ptr_sizeof: %s" % desc, got, want)
        print("   {:<20} = {:<4} (期望 {})".format(desc, repr(got), want))

# ---------------- ex_7_3.c ----------------
e = run("ex_7_3")
if e in ("NOEXE", "BLOCKED"):
    print("\n[ex_7_3.c] 无法运行: {}".format(e))
else:
    print("\n[ex_7_3.c] b[4] 那 4 道题")
    for desc, pat, want in [
        ("*(q+2)", r"\*\(q\s*\+\s*2\)\s*=\s*(\d+)", "300"),
        ("字节差", r"字节差\s*=\s*(\d+)\s*字节", "8"),
        ("sizeof(b)", r"sizeof\(b\)\s*=\s*(\d+)", "16"),
        ("sizeof(q)", r"sizeof\(q\)\s*=\s*(\d+)", "8"),
        ("sizeof(b)/sizeof(b[0])", r"16\s*/\s*4\s*=\s*(\d+)", "4"),
    ]:
        got = grab(e, pat)
        check("ex_7_3: %s" % desc, got, want)
        print("   {:<24} = {:<4} (期望 {})".format(desc, repr(got), want))

# ---------------- func_array.c ----------------
f = run("func_array")
if f in ("NOEXE", "BLOCKED"):
    print("\n[func_array.c] 无法运行: {}".format(f))
else:
    print("\n[func_array.c] 数组作函数参数")
    for desc, pat, want in [
        ("main 里 sizeof(a)", r"在 main 里:\s*sizeof\(a\)\s*=\s*(\d+)", "20"),
        ("函数内 sizeof(arr)", r"\[函数内\]\s*sizeof\(arr\)\s*=\s*(\d+)", "8"),
        ("sum_array 结果", r"sum_array 的结果\s*=\s*(\d+)", "150"),
        ("wrong_length (陷阱)", r"wrong_length\(a\)\s*=\s*(\d+)", "2"),
        ("sum_ptr", r"sum_ptr\(a, n\)\s*=\s*(\d+)", "150"),
    ]:
        got = grab(f, pat)
        check("func_array: %s" % desc, got, want)
        print("   {:<24} = {:<4} (期望 {})".format(desc, repr(got), want))

# ---------------- string_basic.c ----------------
b = run("string_basic")
if b in ("NOEXE", "BLOCKED"):
    print("\n[string_basic.c] 无法运行: {}".format(b))
else:
    print("\n[string_basic.c] 字符串基础")
    for desc, pat, want in [
        ("sizeof(s) cat", r"共\s*(\d+)\s*字节", "4"),
        ("sizeof(s1) cat", r"sizeof\(s\)\s*=\s*(\d+)\s*<-- 整个数组", "4"),
        ("sizeof(p) cat", r"sizeof\(p\)\s*=\s*(\d+)\s*<-- 只是个指针", "8"),
        ("strlen(cat)", r"strlen\(s\)\s*=\s*(\d+)", "3"),
    ]:
        got = grab(b, pat)
        check("string_basic: %s" % desc, got, want)
        print("   {:<24} = {:<4} (期望 {})".format(desc, repr(got), want))

# ---------------- 汇总 ----------------
print("\n" + "=" * 72)
bad = [r for r in results if not r[0]]
good = [r for r in results if r[0]]
print("一致: {} / {}".format(len(good), len(results)))
if bad:
    print("\n不一致的项:")
    for _, desc, got, want in bad:
        print("   {} : 实际 {!r}  期望 {!r}".format(desc, repr(got), want))
else:
    print("讲义里的所有答案与程序实际输出完全一致。")
print("=" * 72)
