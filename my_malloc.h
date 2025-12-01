// my_malloc.h
#ifndef MY_MALLOC_H  // 防止重复引用的“卫哨”
#define MY_MALLOC_H

#include <stddef.h>  // 为了 size_t

// 1. 把结构体定义搬到这里
// 这样 main.c 和 my_malloc.c 都能认识什么是 block
typedef struct block
{
    size_t size;
    int is_free;
    struct block *next;
} block;

// 2. 函数声明 (不要写函数体，只写分号)
void *my_alloc(size_t size);
void my_free(void *ptr);
void debug_heap();  // 把调试工具也暴露出来方便测试

#endif