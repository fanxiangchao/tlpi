commFiles=tlpi_hdr.h get_num.h error_functions.h alt_functions.h get_num.c error_functions.c alt_functions.c

commObjects=get_num.o error_functions.o curr_time.o

commlib:tlpi_hdr.h get_num.h error_functions.h curr_time.h
	gcc -g -c get_num.c error_functions.c alt_functions.c curr_time.c
all:
	echo "make [somthing]"
#Example
#example:commlib
#        gcc -g -o example $(commObjects) example.c

ch27_1:commlib
	gcc -g -o t_execve $(commObjects) t_execve.c
ch27_2:commlib
	gcc -g -o envargs $(commObjects) envargs.c
ch27_3:commlib
	gcc -g -o t_execlp $(commObjects) t_execlp.c
ch27_4:commlib
	gcc -g -o t_execle $(commObjects) t_execle.c
ch27_5:commlib
	gcc -g -o t_execl $(commObjects) t_execl.c
ch27_6:commlib
	gcc -g -o closeonexec $(commObjects) closeonexec.c
ch27_7:commlib
	gcc -g -o t_system $(commObjects) print_wait_status.c t_system.c
exe_2:commlib
	gcc -g -o t_execlp_1 $(commObjects) t_execlp_impl.c t_execlp_1.c
exe_6:commlib
	gcc -g -o exe_6 $(commObjects) exe_6.c
clean:
	rm *.o

.PHONY:ch27_1
.PHONY:ch27_2
.PHONY:ch27_3
.PHONY:ch27_4
.PHONY:ch27_5
.PHONY:ch27_6
.PHONY:ch27_7
.PHONY:exe_2
.PHONY:exe_6
.PHONY:all
.PHONY:clean
