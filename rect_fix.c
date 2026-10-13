/* ============================================================
   rect_fix.c —— 你那道矩形题：三个语法错误逐个讲

   你写的：
       if(w,h>0){              ← 错 1：逗号
       *area=w*h;
       *peri=2(w+h);}          ← 错 2：数学的隐式乘法
       else{*area,*peri=-1;}   ← 错 3：逗号串赋值

   这个程序把「错法」和「对法」并排跑，让你看清差别。
   ============================================================ */
#include <stdio.h>
#include "utf8_console.h"

/* ============================================================
   ✅ 正确写法
   ============================================================ */
void rect_ok(double w, double h, double *area, double *peri)
{
    if (w > 0 && h > 0) {
        *area = w * h;
        *peri = 2 * (w + h);
    } else {
        *area = -1;
        *peri = -1;
    }
}

int main(void)
{
    enable_utf8_console();
    double a, p;

    printf("############################################################\n");
    printf("#   矩形题：你写的三个错误 vs 正确写法                      #\n");
    printf("############################################################\n\n");

    /* ---------- 错误 1：逗号 ---------- */
    printf("============================================================\n");
    printf("错误 1：if(w,h>0)   —— 逗号不是「并且」\n");
    printf("============================================================\n\n");
    printf("  你写的：  if (w, h > 0)\n");
    printf("  编译器：  warning: left-hand operand of comma expression has no effect\n\n");
    printf("  为什么错：\n");
    printf("    逗号运算符的规则是【从左到右算，只取最后一个的值】\n");
    printf("    所以 (w, h>0) 相当于：先算 w（算完就丢掉），再看 h>0\n");
    printf("    => w 根本没参与判断！只要 h>0 就通过\n\n");

    printf("  实测对比（w=-5, h=3，w 是负数不该通过）：\n\n");
    {
        double w = -5, h = 3;

        /* 错的写法 */
        int cond_wrong = (w, h > 0);
        printf("      错法 if (w, h>0)  -> 条件 = %d  %s\n",
               cond_wrong, cond_wrong ? "【通过了！】<- 本该拒绝" : "拒绝了");

        /* 对的写法 */
        int cond_ok = (w > 0 && h > 0);
        printf("      对法 if (w>0 && h>0) -> 条件 = %d  %s\n",
               cond_ok, cond_ok ? "通过了" : "【拒绝了】<- 正确");
    }
    printf("\n  ✅ 正确写法：if (w > 0 && h > 0)\n");
    printf("     「并且」在 C 里是 && ，不是逗号\n");
    printf("     && = 两边都真才真    || = 有一个真就真\n");

    /* ---------- 错误 2：隐式乘法 ---------- */
    printf("\n============================================================\n");
    printf("错误 2：*peri = 2(w+h)   —— C 不认数学的隐式乘法\n");
    printf("============================================================\n\n");
    printf("  你写的：  2(w+h)\n");
    printf("  编译器：  error: called object is not a function or function pointer\n\n");
    printf("  为什么错：\n");
    printf("    在数学里 2(x+y) 是「2 乘以 (x+y)」\n");
    printf("    但在 C 里，【东西后面跟一对括号】的意思是「调用函数」\n");
    printf("    所以编译器认为：你要调用一个名字叫 2 的函数 —— 当然找不到\n\n");

    printf("  实测正确写法（w=3, h=4，周长应该是 2*(3+4)=14）：\n\n");
    {
        double w = 3, h = 4;
        double peri = 2 * (w + h);
        printf("      2 * (w + h)  = %g\n", peri);
        printf("      周长正确 = 14\n");
    }
    printf("\n  ✅ 正确写法：2 * (w + h)\n");
    printf("     ⚠️ C 里【乘法必须写 *】，一个都不能省\n");
    printf("        数学写法         C 里要写成\n");
    printf("        2(x+y)           2 * (x + y)\n");
    printf("        3ab              3 * a * b\n");
    printf("        (a+b)(c+d)       (a + b) * (c + d)\n");
    printf("        2πr              2 * 3.14159 * r\n");

    /* ---------- 错误 3：逗号串赋值 ---------- */
    printf("\n============================================================\n");
    printf("错误 3：else{*area,*peri=-1;}   —— 逗号不能这样用\n");
    printf("============================================================\n\n");
    printf("  你写的：  *area, *peri = -1;\n");
    printf("  编译器：  warning: left-hand operand of comma expression has no effect\n\n");
    printf("  实际发生的：\n");
    printf("    *area 被算了一下（读出它的值），然后【丢掉】\n");
    printf("    只有 *peri = -1 真正执行了\n");
    printf("    => *area 根本没被赋值！\n\n");

    printf("  实测对比：\n\n");
    {
        double area = 999, peri = 999;   /* 先给个能看出来的初值 */

        /* 错的写法 */
        double area_w = 999, peri_w = 999;
        area_w, peri_w = -1;             /* 只有右边那个被赋值 */
        printf("      错法: area = %g   peri = %g   <- area 没变！\n",
               area_w, peri_w);

        /* 对的写法 */
        area = -1;
        peri = -1;
        printf("      对法: area = %g   peri = %g   <- 两个都赋值了\n", area, peri);
    }
    printf("\n  ✅ 正确写法：\n");
    printf("        *area = -1;\n");
    printf("        *peri = -1;\n");
    printf("     或者写在一行也行（用分号隔开）：\n");
    printf("        *area = -1;  *peri = -1;\n");

    /* ---------- 完整对照 ---------- */
    printf("\n############################################################\n");
    printf("#  你的代码 vs 正确代码                                     #\n");
    printf("############################################################\n\n");
    printf("  ❌ 你写的                        ✅ 正确写法\n");
    printf("  ------------------------------  ------------------------------\n");
    printf("  if(w,h>0){                      if (w > 0 && h > 0) {\n");
    printf("  *area=w*h;                      *area = w * h;\n");
    printf("  *peri=2(w+h);}                  *peri = 2 * (w + h);\n");
    printf("  else{*area,*peri=-1;}           } else {\n");
    printf("                                      *area = -1;\n");
    printf("                                      *peri = -1;\n");
    printf("                                  }\n");

    /* ---------- 跑通验证 ---------- */
    printf("\n############################################################\n");
    printf("#  用正确写法跑几组（验证逻辑也对）                         #\n");
    printf("############################################################\n\n");
    printf("     输入 w  h        面积      周长\n");
    printf("     ------------  --------  --------\n");
    {
        struct { double w, h; } cases[] = {
            {3, 4}, {5, 5}, {0, 4}, {-2, 3}, {1, 1}, {2.5, 4},
        };
        int i;
        for (i = 0; i < 6; i++) {
            rect_ok(cases[i].w, cases[i].h, &a, &p);
            printf("     %5.1f %5.1f   %8.2f  %8.2f", cases[i].w, cases[i].h, a, p);
            if (cases[i].w <= 0 || cases[i].h <= 0) {
                printf("   <- 非正数，按题目要求返回 -1");
            }
            printf("\n");
        }
    }

    printf("\n############################################################\n");
    printf("#  记住这三条                                               #\n");
    printf("############################################################\n\n");
    printf("  1. 「并且」写 && ，不是逗号\n");
    printf("         if (w > 0 && h > 0)\n\n");
    printf("  2. C 里乘法必须写 * ，不能像数学那样省略\n");
    printf("         2 * (w + h)    不是   2(w + h)\n\n");
    printf("  3. 给两个变量赋值要写两条语句，逗号不干活\n");
    printf("         *area = -1;  *peri = -1;\n\n");
    printf("  ★ 共同点：数学的写法在 C 里【不一定合法】。\n");
    printf("     编译器报错其实是在帮你 —— 它比数学老师严格。\n");

    return 0;
}
