cmd_netdev_syscall/built-in.a := rm -f netdev_syscall/built-in.a;  printf "netdev_syscall/%s " netdev_syscall.o | xargs ar cDPrST netdev_syscall/built-in.a
