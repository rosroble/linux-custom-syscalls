#include <sys/syscall.h>
#include <linux/seccomp.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    
    if (argc < 2) {
    	printf("Usage: ./test_sc <process_pid>\n");
	return -1;
    }
    
    int pid = atoi(argv[1]);
    
    if (!pid) {
    	printf("Invalid PID: %s\n", argv[1]);
    	return -1;
    }
    
    struct seccomp_data sc_data;
    int status = syscall(336, pid, &sc_data);
    if (status != 0) {
    	printf("Something went wrong. See dmesg for more info\n");
    	return -1;
    }
    
    printf("----- SYSCALL_INFO START -----\n");
    printf("Syscall number: %d\n", sc_data.nr);
    printf("Instruction pointer: %p\n", sc_data.instruction_pointer);
    for (int i = 0; i < 6; i++) {
    	printf("Syscall arg %d: %lld\n", i, sc_data.args[i]);
    }
    printf("----- SYSCALL_INFO END -----\n");
    return 0;   
}
