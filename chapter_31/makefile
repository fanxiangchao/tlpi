commFiles=tlpi_hdr.h get_num.h error_functions.h alt_functions.h get_num.c error_functions.c alt_functions.c

commObjects=get_num.o error_functions.o curr_time.o

commlib:tlpi_hdr.h get_num.h error_functions.h curr_time.h
	gcc -g -c get_num.c error_functions.c alt_functions.c curr_time.c
all:
	echo "make [somthing]"
#Example
#example:commlib
#        gcc -g -o example $(commObjects) example.c

ch31_2:commlib
	gcc -g -lpthread -o strerror_test $(commObjects) strerror.c strerror_test.c
ch31_3:commlib
	gcc -g -lpthread -o strerror_tsd_test $(commObjects) strerror_tsd.c strerror_test.c
ch31_4:commlib
	gcc -g -lpthread -o strerror_tsl_test $(commObjects) strerror_tsl.c strerror_test.c
exe_1:commlib
	gcc -g -lpthread -o strerror_tsd_cus_test $(commObjects) one_time_init.c strerror_tsd_cus.c strerror_test.c
exe_2_1:commlib
	gcc -g -lpthread -o dirname_safe_test $(commObjects) dirname_safe.c dirname_safe_test.c
exe_2_2:commlib
	gcc -g -lpthread -o basename_safe_test $(commObjects) basename_safe.c basename_safe_test.c
clean:
	rm *.o

.PHONY:all
.PHONY:ch31_2
.PHONY:ch31_3
.PHONY:ch31_4
.PHONY:exe_1
.PHONY:exe_2_1
.PHONY:exe_2_2
.PHONY:clean
