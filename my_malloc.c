// my_malloc.c
#include <stdio.h>
#include "my_malloc.h"

// 静态内存池
static char memory_pool[1024]; 

// 初始化函数
block *initialize()
{
    block *initblock = (block *)memory_pool;
    initblock->size = sizeof(memory_pool) - sizeof(block);
    initblock->is_free = 1;
    initblock->next = NULL;
    return initblock;
}



void *my_alloc(size_t size)
{
    static block *freelist = NULL;
    if (freelist == NULL) {
        freelist = initialize();
    }
    


    block *curr = freelist;
    while (curr != NULL) {
        if (curr->is_free && curr->size >= size) {
             if (curr->size > size + sizeof(block)) {
                block *newblock = (block *)((char *)curr + sizeof(block) + size);
                newblock->size = curr->size - size - sizeof(block);
                newblock->is_free = 1;
                newblock->next = curr->next;
                curr->size = size;
                curr->is_free = 0;
                curr->next = newblock;
            } else {
                curr->is_free = 0;
            }
            return (void *)((char *)curr + sizeof(block));
        }
        curr = curr->next;
    }
    return NULL;
}

void my_free(void *ptr)
{

    if (ptr == NULL) return;
    block *curr = (block *)((char *)ptr - sizeof(block));
    curr->is_free = 1;
    if (curr->next != NULL && curr->next->is_free) {
        curr->size += sizeof(block) + curr->next->size;
        curr->next = curr->next->next;
        printf("  [系统提示] 触发合并！Block %p 吃掉了它的后继\n", curr);
    }
}

void debug_heap()
{

    block *curr = (block *)memory_pool;
    printf("-------- 堆内存现状 (Header大小: %zu) --------\n", sizeof(block));
    int i = 0;
    while (curr != NULL) {
        printf("Block %d: [%s] 地址:%p | 数据区大小:%zu | Next:%p\n", 
            i++, curr->is_free ? "FREE" : "USED", curr, curr->size, curr->next);
        curr = curr->next;
    }
    printf("--------------------------------------------\n\n");
}
