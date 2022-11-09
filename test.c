#include <sys/syscall.h>
#include <linux/netdevice.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
    
    if (argc < 2) {
    	printf("Usage: ./test <net_device_name>");
    	return -1;
    }
    struct rtnl_link_stats64 *stats = malloc(sizeof(struct rtnl_link_stats64));
    const char* device_name = argv[1];
    long status = syscall(335, device_name, stats);
    if (status == 0) {
   	printf("Device name: %s \n", device_name);
    	printf("Packets received: %llu \n", stats->rx_packets);
    	printf("Packets transmitted: %llu \n", stats->tx_packets);
    	printf("Bytes received: %llu \n", stats->rx_packets);
    	printf("Bytes transmitted: %llu \n", stats->tx_packets);
    	printf("Bad packets received: %llu \n", stats->rx_errors);
    	printf("Packet transmit fails: %llu \n", stats->tx_errors);
    	return 0;
    }
    printf("Device not found\n");
    return -1;
}
