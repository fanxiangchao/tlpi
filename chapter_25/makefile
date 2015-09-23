commFiles=tlpi_hdr.h get_num.h error_functions.h alt_functions.h get_num.c error_functions.c alt_functions.c

commObjects=get_num.o error_functions.o

commlib:tlpi_hdr.h get_num.h error_functions.h
	gcc -g -c get_num.c error_functions.c alt_functions.c
ch25_1:commlib
	gcc -g -o exit_handlers $(commObjects) exit_handlers.c
ch25_2:commlib
	gcc -g -o fork_stdio_buf $(commObjects) fork_stdio_buf.c
exe_1:commlib
	gcc -g -o exit_child $(commObjects) exit_child.c
clean:
	rm *.o

.PHONY:exe_1
.PHONY:ch25_2
.PHONY:ch25_1
.PHONY:clean
