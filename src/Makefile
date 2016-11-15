obj-m += moonfs.o                                                             
moonfs-objs := super.o                                  
                                                                                
all:                                                                            
	$(MAKE) -C /lib/modules/$(shell uname -r)/build/ M=$(shell pwd)         
		                                                                                
clean:                                                                          
	$(MAKE) -C /lib/modules/$(shell uname -r)/build/ M=$(shell pwd) clean 
