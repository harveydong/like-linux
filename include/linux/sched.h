#ifndef __SCHED_H_
#define __SCHED_H_
#include <linux/list.h>
#include <asm/page.h>
#include <linux/personality.h>
#include <asm/processor.h>
#include <asm/uaccess.h>
#include <asm/pgtable.h>
#include <asm/atomic.h>
#include <asm/semaphore.h>
#include <asm/param.h>
#include <linux/stddef.h>


#define SCHED_OTHER 0
#define SCHED_FIFO 1
#define SCHED_RR 2

struct mm_struct{
	struct vm_area_struct *mmap;
	struct vm_area_struct *mmap_avl;
	struct vm_area_struct *mmap_cache;
	pgd_t *pgd;
	atomic_t mm_users;
	atomic_t mm_count;
	int map_count;
	struct semaphore mmap_sem;
	struct list_head mmlist;
		

};

#define DEF_COUNTER (10*HZ/100)
#define DEF_NICE (0)


#define INIT_MM(name) \
{	.mmap = &init_mmap,\
	.mmap_avl = NULL,\
	.mmap_cache = NULL,\
	.pgd = swapper_pg_dir,\
	.mm_users = ATOMIC_INIT(2),\
	.mm_count = ATOMIC_INIT(1),\
	.map_count = 1,\
	.mmap_sem = __MUTEX_INITIALIZER(name.mmap_sem),\
	.mmlist = LIST_HEAD_INIT(name.mmlist),\
}

struct task_struct{
	volatile long state;
	unsigned long flags;
	int sigpending;
	mm_segment_t addr_limit;
	struct exec_domain *exec_domain;
	volatile long need_resched;
	int lock_depth;
	long counter;
	long nice;
	unsigned long policy;
	struct mm_struct *mm;
	int has_cpu,processor;
	unsigned long cpus_allowed;
	struct list_head run_list;
	struct task_struct *next_task,*prev_task;
	struct mm_struct *active_mm;

	struct task_struct *p_opptr,*p_pptr;
	char comm[16];		

};


extern struct mm_struct init_mm;
extern struct task_struct init_task;


#define INIT_TASK(tsk) \
{			\
	.state = 0,	\
	.flags = 0,	\
	.sigpending = 0,\
	.addr_limit = KERNEL_DS,\
	.exec_domain = &default_exec_domain,\
	.lock_depth = -1,\
	.counter = DEF_COUNTER,\
	.nice = DEF_NICE,\
	.policy = SCHED_OTHER,\
	.mm = NULL,	\
	.active_mm = &init_mm,\
	.cpus_allowed = -1,\
	.run_list = LIST_HEAD_INIT(tsk.run_list),\
	.next_task = &tsk,\
	.prev_task = &tsk,\
	.p_opptr = &tsk,\
	.p_pptr = &tsk,\
	.comm = "swapper",\
}

#ifndef INIT_TASK_SIZE
#define INIT_TASK_SIZE 2048*sizeof(long)
#endif


union task_union {
	struct task_struct task;
	unsigned long stack[INIT_TASK_SIZE/sizeof(long)];

};

#endif
