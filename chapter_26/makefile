commFiles=tlpi_hdr.h get_num.h error_functions.h alt_functions.h get_num.c error_functions.c alt_functions.c

commObjects=get_num.o error_functions.o curr_time.o

commlib:tlpi_hdr.h get_num.h error_functions.h curr_time.h
	gcc -g -c get_num.c error_functions.c alt_functions.c curr_time.c
all:
	echo "make [somthing]"
#Example
#example:commlib
#        gcc -g -o example $(commObjects) example.c

ch26_1:commlib
	gcc -g -o multi_wait $(commObjects) multi_wait.c
ch26_2:commlib
	gcc -g -o child_status $(commObjects) print_wait_status.c child_status.c
ch26_3:commlib
	gcc -g -o make_zombie $(commObjects) make_zombie.c
ch26_4:commlib
	gcc -g -o multi_SIGCHLD $(commObjects) print_wait_status.c multi_SIGCHLD.c
exe_1:commlib
	gcc -g -o orphan_child $(commObjects) orphan_child.c
exe_2:commlib
	gcc -g -o check_grand_parent_child $(commObjects) check_grand_parent_child.c
exe_3:commlib
	gcc -g -o child_status_waitid $(commObjects) print_wait_status.c child_status_waitid.c
exe_4:commlib
	gcc -g -o zombie_signal $(commObjects) make_zombie_signal.c
clean:
	rm *.o

.PHONY:ch26_1
.PHONY:ch26_2
.PHONY:ch26_3
.PHONY:ch26_4
.PHONY:exe_1
.PHONY:exe_2
.PHONY:exe_3
.PHONY:exe_4
.PHONY:all
.PHONY:clean
