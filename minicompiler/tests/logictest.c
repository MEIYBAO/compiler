// 单行注释：综合功能测试
/* 多行注释
   覆盖输入输出、循环、判断、运算等 */

int main() {
    // 声明与初始化
    int a = 3, b = 4, c, d;
    int e = 2;
    int f; // 未初始化，后面赋值

    // 赋值与算术运算（+, -, *, /, %, ^）
    c = a + b;       // 7
    d = c * 2 - 5;   // 9
    e = d % 4;       // 1
    f = a ^ b;       // 3^4 = 81（你的 ^ 实现是幂运算）

    // 输入输出：读取一个值并打印若干结果
    scanf(f);               // 读入到 f
    printf(c);              // 7
    printf(f);              // 用户输入
    printf(c * f);      // 组合算术

    // 关系与逻辑运算：==, !=, >, <, >=, <=, &&, ||, !
    if ((a < b && d >= c) || !(e == 0)) {
        printf(111); // 触发 true 分支
    } else {
        printf(222);
    }

    // while 循环：累加
    int sum = 0;
    while (sum < 5) {
        sum = sum + 1;
    }
    printf(sum); // 应为 5

    // for 循环：倒计数
       // for 循环：倒计数
    int i;
    for (i = 3; i > 0; i = i - 1) {
        printf(i);
    }


    // 再做一次 if-else 覆盖 !=
    if (sum != 5) {
        printf(333);
    } else {
        printf(444); // 预期走这里
    }

    return 0;
}
