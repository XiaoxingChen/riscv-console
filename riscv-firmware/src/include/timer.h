//
// Created by syf on 2022/10/23.
//
#pragma once
#include <stdint.h>
#include "SList.h"
/**
 * define the memory location of  mtime and mtimecmp instructions
 */
#define MTIME_LOW       (*((volatile uint32_t *)0x40000008))
#define MTIME_HIGH      (*((volatile uint32_t *)0x4000000C))
#define MTIMECMP_LOW    (*((volatile uint32_t *)0x40000010))
#define MTIMECMP_HIGH   (*((volatile uint32_t *)0x40000014))
/**
 * the function processing customized timer handler
 * @param mcause
 * @return
 */
int handle_time_interrupt(int mcause);
/**
 * register a customized handler will be invoked when timer interrupts occur.
 * @return the identifier of the handler,used to mark a unique handler.
 */
int register_handler(int(*ptr)(int event_code));
/**
 * cancle a handler using the identifier given at the register step
 * @param handler_identifier
 * @return 1-successful, 0-failed
 */
int deregister_handler(int(*ptr)(int event_code));



