/**
 * hello-algo 列表  
 * C语言版本
*/

#include <stdlib.h>

/**
 * 初始容量：选取一个合理的数组初始容量。在本示例中，我们选择 10 作为初始容量。
 * 
 * 数量记录：声明一个变量 size ，用于记录列表当前元素数量，并随着元素插入和删除实时更新。
 * 根据此变量，我们可以定位列表尾部，以及判断是否需要扩容。
 * 
 * 扩容机制：若插入元素时列表容量已满，则需要进行扩容。
 * 先根据扩容倍数创建一个更大的数组，再将当前数组的所有元素依次移动至新数组。
 * 在本示例中，我们规定每次将数组扩容至之前的 2 倍。
*/

typedef struct {
    int *arr;          // 数组
    int capacity;      // 列表容量
    int size;          // 列表大小
    int extendRatio;   // 列表每次扩容的倍数
} MyList;

/* 构造函数 */ 
MyList *newMyList() {
    MyList *nums = (MyList *)malloc(sizeof(MyList));
    nums->capacity = 10; // 初始容量
    nums->arr = (int *)malloc(sizeof(int) * nums->capacity); // 申请内存
    nums->size = 0;
    nums->extendRatio = 2;
    return nums;
}

/* 析构函数 */
void delMyList(MyList *nums) {
    free(nums->arr);
    free(nums);
}

/* 获取列表长度 */
int size(MyList *nums) {
    return nums->size;
}

/* 向列表尾部插入一个元素 */
void insert(MyList *nums, int val) {
    if (nums->size == nums->capacity) {
        // 扩容
        int *newArr = (int *)malloc(sizeof(int) * nums->capacity * nums->extendRatio);
        for (int i = 0; i < nums->capacity; i++) {
            newArr[i] = nums->arr[i]; // 复制原数组
        }
    }
}











