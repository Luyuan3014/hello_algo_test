/**
 * hello-algo 链表  
 * 链表 是一种线性数据结构，其中的每个元素都是一个节点对象，各个节点通过<指针>相连接
 * 无须使用者考虑容量限制的问题。可以基于链表或数组实现。
 * 链表的设计使得各个节点可以分散存储在内存各处，它们的内存地址无须连续。
 * 
 * C语言版本
*/


#include <stdio.h>
#include <unistd.h>

int find (int *nums, int size, int target) {
	for (int i = 0; i < size; i++) {
		if (nums[i] == target)
			return i;
	}
	return -1;
}

/* 链表节点结构体 */
typedef struct ListNode {
	int val;
	struct ListNode *next;
} ListNode;

/* 构造函数 */
ListNode *newListNode(int val) {
	ListNode *node;
	node = (ListNode *)malloc(sizeof(ListNode));
	node ->val = val;
	node->next = NULL;
	return node;
}

/* 在链表的节点 n0 之后插入节点 P */
void insert(ListNode *n0, ListNode *p) {
	ListNode *n1 = n0->next;
	p->next = n1;
	n0->next = p;
}

/* 删除链表的节点 n0 之后的首个节点 */
void removeItem(ListNode *n0) {
	if (!n0->next)
		return;
	ListNode *p = n0->next;
	ListNode *n1 = p->next; 
	n0->next = n1;
	free(p);
}

/**
 *  访问链表索引为 index 的节点
 *  访问链表第 i 个节点需要i-1轮，时间复杂度为O(n) 
*/ 

ListNode *access(ListNode *head, int index) {
    for (int i = 0; i < index; i++) {
        if (head == NULL)
            return NULL;
        head = head->next;
    }
    return head;
}

/**
 * 查找节点
 * 遍历链表，查找其中值为 target 的节点，输出该节点在链表中的索引。此过程也属于线性查找。 
*/
int find(ListNode *head, int target) {
    for (int i = 0; head != NULL; i++) {
        if (head->val == target)
            return i;
        head = head->next;
        i ++;
    }    
    return -1;
}

/**
 * 常见链表类型：
 * 单向链表
 * 环形链表 ：尾节点指向头节点，任意节点都可以视作为头节点。
 * 双向链表 ：每个节点都有两个指针，分别指向前一个节点和后一个节点。（更灵活但是也占用更多内存）
 * 
 * > 环形链表  常用于需要周期性操作的场景，比如操作系统的资源调度。（时间片轮转调度算法、数据缓冲区）
 * > 双向链表  常用于需要快速查找前一个和后一个元素的场景。 
*/

/* 双向链表节点结构体 */
typedef struct ListNode {
	int val;  // 节点的值
	struct ListNode *next; // 指向下一个节点
	struct ListNode *prev; // 指向上一个节点
} ListNode;

/* 构造函数 */
ListNode *newListNode(int val) {
	ListNode *node;
	node = (ListNode *)malloc(sizeof(ListNode));
	node->val = val;
	node->next =NULL;
	node->prev = NULL;
	return node;
}



int main(void)
{
	int i;
	alarm(1);
	for(i = 0; ; i++)
		printf("%d\n", i);
	return 0;

	ListNode *n0 = newListNode(1);
	ListNode *n1 = newListNode(2);
	ListNode *n2 = newListNode(3);
	ListNode *n3 = newListNode(4);
	ListNode *n4 = newListNode(5);

	n0->next = n1;
	n1->next = n2;
	n2->next = n3;
	n3->next = n0;
}

