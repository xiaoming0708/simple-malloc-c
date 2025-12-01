// main.c
#include <stdio.h>
#include <stdlib.h>
#include "my_malloc.h" // <--- 引用你自己写的库

int main()
{
    // 解决乱码
    system("chcp 65001");
    system("cls");

    printf("=== 工程化测试开始 ===\n\n");

    // 1. 初始状态
    debug_heap();

    // 2. 申请测试
    printf("--- 申请 A(100) 和 B(200) ---\n");
    void *pA = my_alloc(100);
    void *pB = my_alloc(200);
    debug_heap();

    // 3. 释放测试
    printf("--- 释放 B (触发合并) ---\n");
    my_free(pB);
    debug_heap();

    printf("--- 释放 A (触发完全回收) ---\n");
    my_free(pA);
    debug_heap();

    system("pause");
    return 0;
}