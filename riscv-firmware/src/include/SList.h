//
// Created by syf on 2022/10/23.
//
#pragma once
#include <stdint.h>

typedef uint32_t (*ptr)(uint32_t);

typedef struct SListNode{
    int identifier;
    ptr data;
    struct SListNode* next;
}SLTNode;
/**
 * add a new listener
 */
void insertNode(SLTNode* pplist, ptr t);

/**
 * 从链表中删除一个节点
 */
void deleteNode(SLTNode* pplist,ptr t);

/**
 * 初始化一个链表节点，作为head
 */
SLTNode* initList();

uint32_t hand(uint32_t code);

