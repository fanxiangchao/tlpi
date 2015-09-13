commFiles=tlpi_hdr.h get_num.h error_functions.h alt_functions.h get_num.c error_functions.c alt_functions.c

commObjects=get_num.o error_functions.o

commlib:tlpi_hdr.h get_num.h error_functions.h
	gcc -g -c get_num.c error_functions.c alt_functions.c
ch23_1:commlib
	gcc -g -o real_timer $(commObjects) real_timer.c
ch23_2:commlib
	gcc -g -o timed_read $(commObjects) timed_read.c
ch23_3:commlib
	gcc -g -o t_nanosleep $(commObjects) t_nanosleep.c
ch23_5:commlib
	gcc -g -lrt -o ptmr_sigev_signal $(commObjects) curr_time.c itimerspec_from_str.c ptmr_sigev_signal.c
ch23_7:commlib
	gcc -g -lrt -o ptmr_sigev_thread $(commObjects) curr_time.c itimerspec_from_str.c ptmr_sigev_thread.c
ch23_8:commlib
	gcc -g -lrt -o demo_timerfd $(commObjects) itimerspec_from_str.c demo_timerfd.c
exe_1:commlib
	gcc -g -o exe_alarm_impl $(commObjects) exe_alarm_impl.c
exe_2:commlib
	gcc -g -lrt -o exe_nanosleep $(commObjects) exe_nanosleep.c
exe_3:commlib
	gcc -g -lrt -o ptmr_sigev_signal_verify $(commObjects) curr_time.c itimerspec_from_str.c ptmr_sigev_signal_verify.c
exe_4:commlib
	gcc -g -lrt -o ptmr_sigev_signal_wait $(commObjects) curr_time.c itimerspec_from_str.c ptmr_sigev_signal_wait.c

clean:
	rm *.o

.PHONY:exe_4
.PHONY:exe_3
.PHONY:exe_2
.PHONY:exe_1
.PHONY:ch23_8
.PHONY:ch23_7
.PHONY:ch23_5
.PHONY:ch23_3
.PHONY:ch23_2
.PHONY:ch23_1
.PHONY:clean
