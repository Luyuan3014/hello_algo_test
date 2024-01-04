/**
 * hello-algo 队列 queue  
 * 队列 是一种遵循先入先出逻辑的线性数据结构。
 * 我们把队列头部称为“队首“ ，把队列尾部称为“队尾”，
 * 将把元素加入队尾的操作叫作“入队”,
 * 删除队首元素的操作叫作“出队”。
 *  
 * C语言版本
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define RING_ARRAY_QUEUE

/* 基于链表实现的队列 */
#ifdef LINKED_LIST_QUEUE
typedef struct ListNode {
    int val;
    struct ListNode *next;
} ListNode;

typedef struct {
    ListNode *front, *rear;
    int queSize;
} LinkedListQueue;

/* 构造函数 */
LinkedListQueue *newLinkedListQueue() {
    LinkedListQueue *queue = (LinkedListQueue *)malloc(sizeof(LinkedListQueue));
    queue->front = NULL;
    queue->rear = NULL;
    queue->queSize = 0;
    return queue;
}

/* 析构函数 */
void delLinkedListQueue(LinkedListQueue *queue) {
    // 释放所有节点  
    while (queue->front!= NULL) {
        ListNode *tmp = queue->front;
        queue->front = queue->front->next;
        free(tmp);
    }
    free(queue);
}

/* 获取队列的长度 */
int size(LinkedListQueue *queue) {
    return queue->queSize;
}

/* 判断队列是否为空 */
bool empty(LinkedListQueue *queue) {
    return queue->front == NULL;
}

/* 入队 */
void push(LinkedListQueue *queue, int num) {
    // 尾节点处添加 node
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    // 如果队列为空，则令头、尾节点都指向该节点
    if (queue->front == NULL) {
        queue->front = node;
        queue->rear = node;
    }
    // 否则，将该节点添加到尾节点的下一个节点处
    else {
        queue->rear->next = node;
        queue->rear->val = num;
    }
    queue->queSize++;
}

/* 访问队首元素 */
int peek(LinkedListQueue *queue) {
    if (queue->front == NULL) {
        return -1;
    }
    return queue->front->val;
}

/* 出队 */
int pop(LinkedListQueue *queue) {
    int num = peek(queue); // 获取队首元素
    ListNode *tmp = queue->front; // 保存队首元素
    queue->front = queue->front->next; 
    free(tmp);
    queue->queSize--;
    return num;
}




/* 打印队列 */
void printLinkedListQueue(LinkedListQueue *queue) {
    int *arr = (int *)malloc(sizeof(int) * queue->queSize);
    // 拷贝队列元素到数组中
    int i;
    ListNode *node;
    for (i = 0, node = queue->front; i < queue->queSize; i++) {
        arr[i] = node->val;
        printf("%d ", arr[i]);
        node = node->next;
    }
    free(arr);
}

#endif

/* 基于数组实现的队列 */

/**
 * 使用一个变量 front 指向队首元素的索引，并维护一个变量 size 用于记录队列长度。
 * 定义 rear = front + size ，
 * 这个公式计算出的 rear 指向队尾元素之后的下一个位置.
 * 
 * >> 入队操作：将输入元素赋值给 rear 索引处，并将 size 增加 1 。
 * >> 出队操作：只需将 front 增加 1 ，并将 size 减少 1 
 * 
 * front 和 rear 都在向右移动，当它们到达数组尾部时就无法继续移动了。
 * 为了解决此问题，我们可以将数组视为首尾相接的“环形数组”
 * 
*/

/* 基于环形数组实现的队列 */
#ifdef RING_ARRAY_QUEUE
typedef struct {
    int *nums;       // 用于存储队列元素的数组
    int front;       // 队首指针，指向队首元素
    int queSize;     // 尾指针，指向队尾 + 1
    int queCapacity; // 队列容量
} ArrayQueue;

/* 构造函数 */
ArrayQueue *newArrayQueue(int capacity) {
    ArrayQueue *queue = (ArrayQueue *)malloc(sizeof(ArrayQueue));
    // 初始化数组
    queue->queCapacity = capacity;
    queue->nums = (int *)malloc(sizeof(int) * queue->queCapacity);
    queue->front = queue->queSize = 0;
    return queue;
}

/* 析构函数 */
void delArrayQueue(ArrayQueue *queue) {
    free(queue->nums);
    free(queue);
}

/* 获取队列的容量 */
int capacity(ArrayQueue *queue) {
    return queue->queCapacity;
}

/* 获取队列的长度 */
int size(ArrayQueue *queue) {
    return queue->queSize;
}

/* 判断队列是否为空 */
bool empty(ArrayQueue *queue) {
    return queue->queSize == 0;
}

/* 访问队首元素 */
int peek(ArrayQueue *queue) {
    assert(size(queue) != 0);
    return queue->nums[queue->front];
}

/* 入队 */
void push(ArrayQueue *queue, int num) {
    if (size(queue) == capacity(queue)) {
        printf("队列已满\r\n");
        return;
    }
    // 计算队尾指针，指向队尾索引 + 1
    // 通过取余操作实现 rear 越过数组尾部后回到头部
    int rear = (queue->front + queue->queSize) % queue->queCapacity;
    // 将 num 添加至队尾
    queue->nums[rear] = num;
    queue->queSize++;
}

/* 出队 */
int pop(ArrayQueue *queue) {
    int num = peek(queue);
    // 队首指针向后移动一位，若越过尾部，则返回到数组头部
    queue->front = (queue->front + 1) % queue->queCapacity;
    queue->queSize--;
    return num;
}

#endif










































