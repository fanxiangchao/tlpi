commFiles=tlpi_hdr.h get_num.h error_functions.h alt_functions.h get_num.c error_functions.c alt_functions.c

commObjects=get_num.o error_functions.o curr_time.o

commlib:tlpi_hdr.h get_num.h error_functions.h curr_time.h
	gcc -g -c get_num.c error_functions.c alt_functions.c curr_time.c
all:
	echo "make [somthing]"
#Example
#example:commlib
#        gcc -g -o example $(commObjects) example.c

exe_1:commlib
	gcc -g -lpthread -o thread_sig $(commObjects) signal_functions.c thread_sig.c
clean:
	rm *.o

.PHONY:all
.PHONY:exe_1
.PHONY:clean
