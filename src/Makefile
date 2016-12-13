PROG = moonfs
obj-m += ${PROG}.o                                                             
moonfs-objs := super.o                                  
                                                                                
${PROG}:                                                                            
	$(MAKE) -C /lib/modules/$(shell uname -r)/build/ M=$(shell pwd)         
disk:
	dd if=/dev/zero of=disk_mn_fs bs=1024 count=131072


clean:                                                                          
	$(MAKE) -C /lib/modules/$(shell uname -r)/build/ M=$(shell pwd) clean 
