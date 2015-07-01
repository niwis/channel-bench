/*
 * Copyright 2014, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */


#ifndef __MANAGER_H 
#define __MANAGER_H 


#include <autoconf.h>
#include <sel4/bootinfo.h>

#include <vka/vka.h>
#include <sel4utils/elf.h>
#include <sel4utils/process.h>

#include <simple/simple.h>
/*common definitions*/
#include "../../bench_common.h"


typedef struct {

    vka_t vka;      
    vspace_t vspace; 
    
    /*abstracts over kernel version and boot envior*/
    simple_t simple; 

    /*path for the default timer irq handler*/
    cspacepath_t irq_path; 
#ifdef CONFIG_ARCH_ARM 
    /*frame for the default timer*/ 
    cspacepath_t frame_path; 
#endif 

#ifdef CONFIG_ARCH_IA32 
    /*io port for the default timer*/ 
    seL4_CPtr io_port_cap; 
#endif 
    /*extra caps to the record data frames for mapping into 
     the benchmark vspace*/ 
    seL4_CPtr record_frames[CONFIG_BENCH_RECORD_PAGES]; 

    /*virtual address for recording data, used by root*/ 
    void *record_vaddr; 

    /*benchmark thread structure*/
    sel4utils_process_t bench_thread; 

    /*endpoint that root thread is waiting on*/ 
    seL4_CPtr bench_ep;

} m_env_t;  /*environment used by the manager*/  


/*interfaces in data.c*/

/*analysing benchmark results*/
void bench_process_data(m_env_t *env, seL4_Word result); 

#endif
