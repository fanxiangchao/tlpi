commFiles=tlpi_hdr.h get_num.h error_functions.h alt_functions.h get_num.c error_functions.c alt_functions.c

commObjects=get_num.o error_functions.o

sigFuncObjects=signal_functions.o

commlib:tlpi_hdr.h get_num.h error_functions.h
	gcc -g -c get_num.c error_functions.c alt_functions.c
sigFunclib:signal_functions.c signal_functions.h
	gcc -g -c  signal_functions.c

ch22_2:commlib
	gcc -g -o t_sigqueue  $(commObjects) t_sigqueue.c
ch22_3:commlib
	gcc -g -o catch_rtsigs $(commObjects) catch_rtsigs.c
ch22_5:commlib sigFunclib
	gcc -g -o t_sigsuspend $(commObjects) $(sigFuncObjects) t_sigsuspend.c
ch22_6:commlib
	gcc -g -o t_sigwaitinfo $(commObjects) t_sigwaitinfo.c
ch22_7:commlib
	gcc -g -o signalfd_sigval $(commObjects) signalfd_sigval.c
clean:
	rm -r *.o 

.PHONY:ch22_5
.PHONY:ch22_2
.PHONY:ch22_3
.PHONY:ch22_6
.PHONY:ch22_7
.PHONY:clean
