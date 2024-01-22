/**
 * hello-algo  哈希表 hash table  
 * 通过建立键key与值value之间的映射关系，实现高效的数据存储和检索，
 * 我们向哈希表中输入一个键 key ，则可以在 O(1) 时间内获取对应的值 value 。
 *  
 * C语言版本
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 哈希表容量 */ 
#define HASHTABLE_CAPACITY 100

/* 键值对 int->string */
typedef struct {
    int key;
    char* val;
} Pair;

/* 基于数组实现的哈希表 */
typedef struct {
    Pair *buckets[HASHTABLE_CAPACITY]; // 桶
} ArrayHashMap;

/* 构造函数 */
ArrayHashMap *newArrayHashMap() {
    ArrayHashMap *hashmap = malloc(sizeof(ArrayHashMap));
    return hashmap;
}

/* 析构函数 */
void delArrayHashMap(ArrayHashMap *hashmap) {
    int i;
    for (i = 0; i < HASHTABLE_CAPACITY; i++) {
        if (hashmap->buckets != NULL) {
            free(hashmap->buckets[i]->val);
            free(hashmap->buckets[i]);
        }
    }
    free(hashmap);
}

/* 添加操作 */
void put(ArrayHashMap *hashmap, const int key, const char *val) {
    Pair *Pair = malloc(sizeof(Pair));
    Pair->key = key;
    Pair->val = malloc(strlen(val) + 1); // 加1，用于保存'\0'
    strcpy(Pair->val, val);

    int index = hashFunc(key);
    hashmap->buckets[index] = Pair;
}

/* 删除操作 */
void removeItem(ArrayHashMap *hashmap, const int key) {
    int index = hashFunc(key);
    free(hashmap->buckets[index]->val);
    free(hashmap->buckets[index]);
    hashmap->buckets[index] = NULL;
}

/* 获取到所有键值对 */
typedef struct {
    Pair *get;
    int len;
} MapGet;
void pairGet(ArrayHashMap *hashmap, MapGet *get) {
    Pair *entries;
    int i = 0;
    int index = 0;
    int total = 0;
    /* 统计有效键值对数量 */
    for (i = 0; i < HASHTABLE_CAPACITY; i++) {
        if (hashmap->buckets[i] != NULL) {
            total++;
        }
    }
    entries = malloc(sizeof(Pair) * total);
    for (i = 0; i < HASHTABLE_CAPACITY; i++) {
        if (hashmap->buckets[i] != NULL) {
            entries[index].key = hashmap->buckets[i]->key;
            entries[index].val = malloc(strlen(hashmap->buckets[i]->val) +1);
            strcpy(entries[index].val, hashmap->buckets[i]->val);
            index++;
        }
    }
    get->get = entries;
    get->len = total;
}

/* 获取所有的键 */
void keyGet(ArrayHashMap *hashmap, MapGet *get) {
    int *keys;
    int i = 0;
    int index = 0;
    int total = 0;
    /* 统计有效键值对数量 */
    for (i = 0; i < HASHTABLE_CAPACITY; i++) {
        if (hashmap->buckets[i] != NULL) {
            total++;
        }
    }
    keys = malloc(total *sizeof(int));
    for (i = 0; i < HASHTABLE_CAPACITY; i++) {
        if (hashmap->buckets[i] != NULL) {
            keys[index++] = hashmap->buckets[i]->key;
            index++;
        }
    }
    get->get = keys;
    get->len = total;
}

/* 获取所有的值 */
void valueSet(ArrayHashMap *hmap, MapGet *get) {
    char **vals;
    int i = 0, index = 0;
    int total = 0;
    /* 统计有效键值对数量 */
    for (i = 0; i < HASHTABLE_CAPACITY; i++) {
        if (hmap->buckets[i] != NULL) {
            total++;
        }
    }
    vals = malloc(total * sizeof(char *));
    for (i = 0; i < HASHTABLE_CAPACITY; i++) {
        if (hmap->buckets[i] != NULL) {
            vals[index] = hmap->buckets[i]->val;
            index++;
        }
    }
    get->get = vals;
    get->len = total;
}

/* 打印哈希表 */
void printHashMap(ArrayHashMap *hashmap) {
    int i;
    MapGet get;
    pairGet(hashmap, &get);
    Pair *entries = (Pair*)get.get;
    for (i = 0; i < get.len; i++) {
        printf("%d->%s\n", entries[i].key, entries[i].val);
    }
    free(get.get);
}