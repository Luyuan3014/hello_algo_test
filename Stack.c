/**
 * hello-algo 栈 stack  
 * 栈 是一种遵循先入后出逻辑的线性数据结构。
 * 我们把堆叠元素的顶部称为“栈顶”，底部称为“栈底”。
 * 将把元素添加到栈顶的操作叫作“入栈”, < push >，
 * 删除栈顶元素的操作叫作“出栈”, < pop >。
 * 
 * 只能从栈顶添加或则删除元素，可以视为一种受限制的数组或链表。
 * 
 * C语言版本
*/

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX_SIZE 1000  // 基于数组实现的栈的最大容量
// #define LINKED_LIST_STACK
#define ARRAY_STACK
/* 基于链表实现的栈 */
#ifdef LINKED_LIST_STACK 
typedef struct ListNode {
    int val;
    struct ListNode *next;
} ListNode;

typedef struct {
    ListNode *top;  // 将头节点作为栈顶
    int size;       // 栈的大小
} LinkedListStack;

/* 构造函数 */
LinkedListStack *newLinkedListStack() {
    LinkedListStack *s = malloc(sizeof(LinkedListStack));
    s->top = NULL;
    s->size = 0;
    return s;
}

/* 析构函数 */
void delLinkedListStack(LinkedListStack *s) {
    while (s->top) {
        ListNode *n = s->top->next;
        free(s->top);
        s->top = n;
    }
    free(s);
}

/* 获取栈的长度 */
int size(LinkedListStack *s) {
    return s->size;
}

/* 判断栈是否为空 */
bool isEmpty(LinkedListStack *s) {
    return size(s) == 0;
}


/* 入栈 */
void push(LinkedListStack *s, int val) {
    ListNode *n = (ListNode *)malloc(sizeof(ListNode));
    n->val = val;     // 更新新加节点值域
    n->next = s->top; // 更新新加节点指针域
    s->top = n;       // 更新栈顶
    s->size++;        // 更新栈大小
}

/* 访问栈顶元素 */
int peek(LinkedListStack *s) {
    if (isEmpty(s)) {
        return -1;
    }
    return s->top->val;
}

/* 出栈 */
int pop(LinkedListStack *s) {
    if (isEmpty(s)) {
        return -1;
    }
    int val = s->top->val;
    ListNode *n = s->top->next;
    free(s->top);
    s->top = n;
    s->size--;
    return val;
}

#endif

/* 基于数组实现的栈 */
#ifdef ARRAY_STACK
typedef struct {
    int *data; // 栈的数组
    int size;
} ArrayStack;

/* 构造函数 */
ArrayStack *newArrayStack() {
    ArrayStack *stack = (ArrayStack *)malloc(sizeof(ArrayStack));
    // 初始化一个大容量，避免扩容
    stack->data = (int *)malloc(sizeof(int) * MAX_SIZE);
    stack->size = 0;
    return stack;
}

/* 析构函数 */
void delArrayStack(ArrayStack *stack) {
    free(stack->data);
    free(stack);
}

/* 获取栈的长度 */
int size(ArrayStack *stack) {
    return stack->size;
}

/* 判断栈是否为空 */
bool isEmpty(ArrayStack *stack) {
    return size(stack) == 0;
}

/* 入栈 */
void push(ArrayStack *stack, int num) {
    if (stack->size == MAX_SIZE) {
        printf("栈满了\n");
        return ;
    }
    stack->data[stack->size] = num;
    stack->size++;
}

/* 访问栈顶元素 */
int peek(ArrayStack *stack) {
    if (stack->size == 0) {
        printf("栈为空\n");
        return -1;
    }
    return stack->data[stack->size-1];
}

/* 出栈 */
int pop(ArrayStack *stack) {
    int val = peek(stack);
    stack->size--;
    return val;
}

#endif



/**
 * >> 两种实现对比 
 * 基于数组实现的栈在触发扩容时效率会降低，但由于扩容是低频操作，因此平均效率更高。
 * 基于链表实现的栈可以提供更加稳定的效率表现。
 * 
 * >> 典型应用
 * 浏览器中的后退与前进。
 * 程序内存管理。
*/