commFiles=tlpi_hdr.h get_num.h error_functions.h alt_functions.h get_num.c error_functions.c alt_functions.c

commObjects=get_num.o error_functions.o curr_time.o

commlib:tlpi_hdr.h get_num.h error_functions.h curr_time.h
	gcc -g -c get_num.c error_functions.c alt_functions.c curr_time.c
all:
	echo "make [somthing]"
#Example
#example:commlib
#        gcc -g -o example $(commObjects) example.c

ch30_1:commlib
	gcc -g -lpthread -o thread_incr $(commObjects) thread_incr.c
ch30_2:commlib
	gcc -g -lpthread -o thread_incr_mutex $(commObjects) thread_incr_mutex.c
ch30_4:commlib
	gcc -g -lpthread -o thread_multjoin $(commObjects) thread_multjoin.c
exe30_1:commlib
	gcc -g -lpthread -o thread_incr_mutex_print $(commObjects) thread_incr_mutex_print.c
exe30_2:commlib
	gcc -g -lpthread -o thread_tree $(commObjects) thread_tree.c
clean:
	rm *.o

.PHONY:all
.PHONY:ch30_1
.PHONY:ch30_2
.PHONY:ch30_4
.PHONY:exe30_1
.PHONY:exe30_2
.PHONY:clean
