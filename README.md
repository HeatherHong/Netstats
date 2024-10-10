If you wnats to use this module please follow this steps:

  Compiling the Module:
  make
  Insert the module into the kernel:
  sudo insmod netstats.ko
  Check the network statistics:
  cat /proc/netstats
  Unload the module:
  sudo rmmod netstats
  Clean up the compiled files:
  make clean
