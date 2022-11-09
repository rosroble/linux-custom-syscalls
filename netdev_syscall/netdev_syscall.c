#include <linux/syscalls.h>
#include <linux/netdevice.h>
#include <linux/kernel.h>

SYSCALL_DEFINE2(netdev_info, const char*, name, void*, target) {
    struct net_device *device = dev_get_by_name(&init_net, name);
    
    if (device) {
    	struct rtnl_link_stats64 *stats = kmalloc(sizeof(struct rtnl_link_stats64), GFP_KERNEL); 
    	stats = dev_get_stats(device, stats);
	memcpy(target, stats, sizeof(struct rtnl_link_stats64));
    	kfree(stats);
    	printk("Syscall executed successfully");
    	return 0;
    }
    
    printk("Device not found");
    return -1;
}

// 335
