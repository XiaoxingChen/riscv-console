//
// Created by syf on 2022/10/23.
//
#include <stdlib.h>
#include <stddef.h>
#include "include/timer.h"
#include "include/SList.h"


/**
 * define the method of dealing with interrupt cause by timer
 * @param mcause
 * @return
 */
void increase_timer();

void handle_timer();

SLTNode* node;
extern volatile char *VIDEO_MEMORY;


int handle_time_interrupt(int mcause) {
    // determining whether the interrupt is caused by timer
    // fixme: whether to use == or seventh bits
    if (mcause & 0x7 != 7) {
        return 0;
    }
    // dispatch customized handlers
    handle_timer();
    // set up next trigger
    increase_timer();
}

void handle_timer() {
    SLTNode* curr = node->next;
    while(curr != NULL){
        (curr->data)(0);
        curr = curr->next;
    }
}

void increase_timer() {
    uint64_t NewCompare = (((uint64_t) MTIMECMP_HIGH) << 32) | MTIMECMP_LOW;
    NewCompare += 100;
    MTIMECMP_HIGH = NewCompare >> 32;
    MTIMECMP_LOW = NewCompare;
}

int register_handler(int(*ptr)(int event_code)) {
    if(node == NULL){
        node=initList();
    }
    if(node == NULL){
        VIDEO_MEMORY[10]='i';
    }
    insertNode(node, ptr);
    if(node == NULL){
        VIDEO_MEMORY[11]='j';
    }
    return 1;
}


int deregister_handler(int(*ptr)(int event_code)) {
    deleteNode(node, ptr);
    return 1;
}

