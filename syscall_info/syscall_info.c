#include <linux/ptrace.h>
#include <linux/pid.h>
#include <linux/syscalls.h>

static struct task_struct *task;

SYSCALL_DEFINE2(get_syscall_info, int, proc_pid, void*, target) {
    int status;
    struct syscall_info *sc_info;
    
    task = get_pid_task(find_get_pid(proc_pid), PIDTYPE_PID);
    if (!task) {
    	printk("Invalid PID: %d", proc_pid);
    	return -1;
    }
    
    sc_info = kmalloc(sizeof(struct syscall_info), GFP_KERNEL);
    status = task_current_syscall(task, sc_info);
    if (status == 0) {
    	memcpy(target, &(sc_info->data), sizeof(struct seccomp_data));
    	kfree(sc_info);
    	return 0;
    }
    kfree(sc_info);
    printk("Task %d is not blocked", proc_pid);
    return -1;  
}

// 336
