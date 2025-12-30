// my_malloc.h
#ifndef MY_MALLOC_H  // 防止重复引用
#define MY_MALLOC_H

#include <stddef.h>  //  size_t

// 1. 结构体定义
typedef struct block
{
    size_t size;
    int is_free;
    struct block *next;
} block;

// 2. 函数声明
void *my_alloc(size_t size);
void my_free(void *ptr);
void debug_heap();  

#endif
