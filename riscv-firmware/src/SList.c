//
// Created by syf on 2022/10/23.
//
#include "include/SList.h"
#include <stdlib.h>

extern volatile char *VIDEO_MEMORY;

void insertNode(SLTNode* pplist, ptr t){
    SLTNode* newNode = (SLTNode*)malloc(sizeof(SLTNode));
    newNode->data =t;
    newNode->next= NULL;
    VIDEO_MEMORY[6]='f';

    if(pplist == NULL){
        pplist = newNode;
        VIDEO_MEMORY[7]='g';
    }else{
        VIDEO_MEMORY[7]='h';
        SLTNode* cur = pplist;
        while(cur->next != NULL){
            cur = cur->next;
        }
        cur->next = newNode;
    }
}

void deleteNode(SLTNode* pplist,ptr t){
    if(pplist == NULL){
        return;
    }

    SLTNode* prev = pplist;
    SLTNode* curr = pplist;
    while(curr->next != NULL && curr->data != t){
        prev = curr;
        curr = curr->next;
    }
    prev->next = curr->next;
    curr->next = NULL;
}

SLTNode* initList(){
    SLTNode* newNode = (SLTNode*)malloc(sizeof(SLTNode));
    newNode->next = NULL;
    return newNode;
}


