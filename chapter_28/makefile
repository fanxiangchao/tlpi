commFiles=tlpi_hdr.h get_num.h error_functions.h alt_functions.h get_num.c error_functions.c alt_functions.c

commObjects=get_num.o error_functions.o curr_time.o

commlib:tlpi_hdr.h get_num.h error_functions.h curr_time.h
	gcc -g -c get_num.c error_functions.c alt_functions.c curr_time.c
all:
	echo "make [somthing]"
#Example
#example:commlib
#        gcc -g -o example $(commObjects) example.c

ch28_1:commlib
	gcc -g -o acct_on $(commObjects) acct_on.c
ch28_2:commlib
	gcc -g -o acct_view $(commObjects) ugid_functions_tlpi.c acct_view.c
ch28_2_1:commlib
	gcc -g -o acct_v3.view $(commObjects) ugid_functions_tlpi.c acct_v3.view.c
ch28_2_2:commlib
	gcc -g -o acct_view_tlpi $(commObjects) ugid_functions_tlpi.c acct_view_tlpi.c
ch28_3:commlib
	gcc -g -o t_clone $(commObjects) t_clone.c
exe_1:commlib
	gcc -g -o fork_time $(commObjects) fork_time.c
clean:
	rm *.o

.PHONY:all
.PHONY:ch28_1
.PHONY:ch28_2
.PHONY:ch28_2_1
.PHONY:ch28_2_2
.PHONY:ch28_3
.PHONY:exe_1
.PHONY:clean
