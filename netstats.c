#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/netdevice.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A Simple Module to Show Network Statistics");
MODULE_VERSION("1.0");

#define PROC_FILENAME "netstats"

static int show_net_stats(struct seq_file *m, void *v) {
    struct net_device *dev;

    // Iterate through the list of network devices
    for_each_netdev(&init_net, dev) {
        struct rtnl_link_stats64 temp;
        const struct rtnl_link_stats64 *stats;

        // Get network statistics for the device
        stats = dev_get_stats(dev, &temp);

        seq_printf(m, "Device: %s\n", dev->name);
        seq_printf(m, "  RX packets: %llu\n", stats->rx_packets);
        seq_printf(m, "  TX packets: %llu\n", stats->tx_packets);
        seq_printf(m, "  RX bytes: %llu\n", stats->rx_bytes);
        seq_printf(m, "  TX bytes: %llu\n", stats->tx_bytes);
        seq_printf(m, "  RX errors: %llu\n", stats->rx_errors);
        seq_printf(m, "  TX errors: %llu\n", stats->tx_errors);
        seq_printf(m, "  RX dropped: %llu\n", stats->rx_dropped);
        seq_printf(m, "  TX dropped: %llu\n\n", stats->tx_dropped);
    }
    
    return 0;
}

static int netstats_proc_open(struct inode *inode, struct file *file) {
    return single_open(file, show_net_stats, NULL);
}

static const struct proc_ops netstats_proc_ops = {
    .proc_open = netstats_proc_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int __init netstats_init(void) {
    proc_create(PROC_FILENAME, 0, NULL, &netstats_proc_ops);
    printk(KERN_INFO "Netstats module loaded.\n");
    return 0;
}

static void __exit netstats_exit(void) {
    remove_proc_entry(PROC_FILENAME, NULL);
    printk(KERN_INFO "Netstats module unloaded.\n");
}

module_init(netstats_init);
module_exit(netstats_exit);
