// 有意包含多种语义/类型错误的示例
int main() {
    int a = 1;
    int a = 2;       // 重复定义
    b = 3;           // 未声明使用
    int c = "str";   // 类型不匹配（字符串赋给 int）
    int d = 4 / 0;   // 除以 0（常量折叠时可提示）
    return a + b;    // b 未声明
}
