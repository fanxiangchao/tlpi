commFiles=tlpi_hdr.h get_num.h error_functions.h alt_functions.h get_num.c error_functions.c alt_functions.c

commObjects=get_num.o error_functions.o

commlib:tlpi_hdr.h get_num.h error_functions.h
	gcc -g -c get_num.c error_functions.c alt_functions.c
ch24_1:commlib
	gcc -g -o t_fork $(commObjects) t_fork.c
ch24_2:commlib
	gcc -g -o fork_file_sharing $(commObjects) fork_file_sharing.c
ch24_4:commlib
	gcc -g -o t_vfork $(commObjects) t_vfork.c
ch24_5:commlib
	gcc -g -o fork_whos_on_first $(commObjects) fork_whos_on_first.c
ch24_6:commlib
	gcc -g -o fork_sig_sync $(commObjects) curr_time.c fork_sig_sync.c
exe_1:commlib
	gcc -g -o fork_count $(commObjects) fork_count.c
exe_2:commlib
	gcc -g -o vfork_close_fd $(commObjects) vfork_close_fd.c
exe_5:commlib
	gcc -g -o fork_sig_sync_together $(commObjects) curr_time.c  fork_sig_sync_together.c
clean:
	rm *.o

.PHONY:exe_5
.PHONY:exe_2
.PHONY:exe_1
.PHONY:ch24_6
.PHONY:ch24_5
.PHONY:ch24_4
.PHONY:ch24_2
.PHONY:ch24_1
.PHONY:clean
