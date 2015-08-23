##File I/O copy.c
##copy: get_num.o error_functions.o copy.c
##	gcc -o copy get_num.o error_functions.o copy.c

###seek_io:get_num.o error_functions.o seek_io.c
##	gcc -o seek_io get_num.o error_functions.o seek_io.c

## 4-1
##tee:get_num.o error_functions.o tee.c
##	gcc -o tee get_num.o error_functions.o tee.c

## 4-2
##cp_hole:get_num.o error_functions.o cp_hole.c
##	gcc -o cp_hole get_num.o error_functions.o cp_hole.c

makeall:get_num.o error_functions.o t_readv.o large_file.o \
	offappend_file.o \
	atomic_append.o \
	dup_new.o \
	filefd_test.o \
	rdwrv_new.o \
	display_env.o \
	t_mod_env.o \
	longjump.o \
	setjmp_vars.o \
	longjmp_alret.o \
	envsettings.o \
	free_and_sbrk.o \
	malloc_free_new.o \
	ugid_functions.o \
	check_password.o \
	getpwnam_new.o \
	idshow.o \
	calendar_time.o \
	strtime.o \
	show_time.o \
	process_time.o \
	t_sysconf.o \
	t_fpathconf.o \
	proc_list.o \
	procfs_pidmax.o \
	t_uname.o \
	proc_tree.o \
	proc_samefile.o \
	io_buffer_tail.o \
	t_mount.o \
	t_stat.o \
	t_chown.o \
	t_access.o \
	t_chmodall.o \
	t_chattr.o \
	xattr_view.o \
	setfattr_new.o \
	acl_view.o \
	acl_ug.o \
	t_unlink.o \
	list_files.o \
	nftw_dir_tree.o \
	view_symlink.o \
	t_dirbasename.o \
	t_realpath.o \
	list_files_r.o \
	t_getcwd.o \
	nftw_dir_tree_per.o \
	chdir_cmp.o \
	demo_inotify.o \
	recur_inotify.o \
	ouch.o \
	intquit.o \
	sig_sender.o \
	sig_receiver.o \
	sig_receiver_1.o \
	sig_ign_demo.o \
	sigaction_flags.o \
	sigaction_interrupt.o \
	nonreentrant.o \
	sigmask_longjmp_sig.o \
	sigmask_longjmp.o \
	t_signalstack.o \
	signal_abort.o

## Exercise 21-1
signal_abort.o:get_num.o error_functions.o
	gcc -o signal_abort error_functions.o get_num.o signal_abort.c

## Example 21-3
t_signalstack.o:get_num.o error_functions.o
	gcc -o t_signalstack error_functions.o get_num.o t_signalstack.c

## Example 21-2
sigmask_longjmp_sig.o:get_num.o error_functions.o
	gcc -DUSE_SIGSETJMP -o sigmask_longjmp_sig error_functions.o get_num.o signal_functions.c sigmask_longjmp.c
## Example 21-2
sigmask_longjmp.o:get_num.o error_functions.o
	gcc -o sigmask_longjmp error_functions.o get_num.o signal_functions.c sigmask_longjmp.c

## Example 21-1
nonreentrant.o:get_num.o error_functions.o
	gcc -lcrypt -o nonreentrant error_functions.o get_num.o nonreentrant.c

## Exercise 20-4
sigaction_interrupt.o:get_num.o error_functions.o
	gcc -o sigaction_interrupt error_functions.o sigaction_interrupt.c

## Exercise 20-3
sigaction_flags.o:get_num.o error_functions.o
	gcc -o sigaction_flags error_functions.o signal_functions.c sigaction_flags.c

## Exercise 20-2
sig_ign_demo.o:get_num.o error_functions.o
	gcc -o sig_ign_demo get_num.o error_functions.o signal_functions.c sig_ign_demo.c

## Exercise 20-1
sig_receiver_1.o:get_num.o error_functions.o
	gcc -o sig_receiver_1 get_num.o error_functions.o signal_functions.c sig_reciver_1.c

## Example 20-7
sig_receiver.o:get_num.o error_functions.o
	gcc -o sig_receiver get_num.o error_functions.o signal_functions.c sig_receiver.c

## Example 20-6
sig_sender.o:get_num.o error_functions.o
	gcc -o sig_sender get_num.o error_functions.o sig_sender.c

## Example 20-2
intquit.o:get_num.o error_functions.o
	gcc -o intquit get_num.o error_functions.o intquit.c

## Example 20-1
ouch.o:get_num.o error_functions.o
	gcc -o ouch get_num.o error_functions.o ouch.c

## Exercise 19-1
recur_inotify.o:get_num.o error_functions.o
	gcc -o recur_inotify get_num.o error_functions.o recur_inotify.c

## Example 19-1
demo_inotify.o:get_num.o error_functions.o
	gcc -o demo_inotify get_num.o error_functions.o demo_inotify.c

## Exercise 18-9
chdir_cmp.o:get_num.o error_functions.o
	gcc -o chdir_cmp get_num.o error_functions.o chdir_cmp.c

## Exercise 18-7
nftw_dir_tree_per.o:get_num.o error_functions.o 
	gcc -o nftw_dir_tree_per get_num.o error_functions.o nftw_dir_tree_per.c

## Exercise 18-5
t_getcwd.o:get_num.o error_functions.o
	gcc -o t_getcwd get_num.o error_functions.o t_getcwd.c

## Exercise 18-4
list_files_r.o:get_num.o error_functions.o
	gcc -o list_files_r get_num.o error_functions.o list_files_r.c

## Exercise 18-3
t_realpath.o:get_num.o error_functions.o
	gcc -o t_realpath get_num.o error_functions.o t_realpath.c

## Example 18-5
t_dirbasename.o:get_num.o error_functions.o
	gcc -o t_dirbasename get_num.o error_functions.o t_dirbasename.c

## Example 18-4
view_symlink.o:get_num.o error_functions.o
	gcc -o view_symlink get_num.o error_functions.o view_symlink.c

## Example 18-3
nftw_dir_tree.o:get_num.o error_functions.o
	gcc -o nftw_dir_tree get_num.o error_functions.o nftw_dir_tree.c

## Example 18-2
list_files.o:get_num.o error_functions.o
	gcc -o list_files get_num.o error_functions.o list_files.c

## Example 18-1
t_unlink.o:get_num.o error_functions.o
	gcc -o t_unlink get_num.o error_functions.o t_unlink.c

## Exercise 17-1
acl_ug.o:get_num.o error_functions.o
	gcc -lacl -o acl_ug get_num.o error_functions.o ugid_functions_tlpi.c acl_ug.c 

## Example 17-1
acl_view.o:get_num.o error_functions.o
	gcc -lacl -o acl_view get_num.o error_functions.o ugid_functions_tlpi.c acl_view.c

## Exercise 16-1
setfattr_new.o:get_num.o error_functions.o
	gcc -o setfattr_new get_num.o error_functions.o setfattr_new.c

## Example 16-1
xattr_view.o:get_num.o error_functions.o
	gcc -o xattr_view get_num.o error_functions.o xattr_view.c

## Exercise 15-7
t_chattr.o:get_num.o error_functions.o
	gcc -o t_chattr get_num.o error_functions.o t_chattr.c

## Exercise 15-6
t_chmodall.o:get_num.o error_functions.o
	gcc -o t_chmodall get_num.o error_functions.o t_chmodall.c

## Exercise 15-4
t_access.o:get_num.o error_functions.o
	gcc -o t_access get_num.o error_functions.o t_access.c

## Example 15-2
t_chown.o:get_num.o error_functions.o
	gcc -o t_chown get_num.o error_functions.o t_chown.c

## Example 15-1
t_stat.o:get_num.o error_functions.o
	gcc -o t_stat get_num.o error_functions.o t_stat.c file_perms.c


## Example 14-1
t_mount.o:get_num.o error_functions.o
	gcc -o t_mount get_num.o error_functions.o t_mount.c

## Exercise 13-5
io_buffer_tail.o:get_num.o error_functions.o
	gcc -o io_buffer_tail get_num.o error_functions.o io_buffer_tail.c

## Exercise 12-3
proc_samefile.o:get_num.o error_functions.o
	gcc -o proc_samefile get_num.o error_functions.o mylib.c proc_samefile.c

## Exercise 12-2
proc_tree.o:get_num.o error_functions.o
	gcc -o proc_tree get_num.o error_functions.o mylib.c proc_tree.c

## Example 12-2
t_uname.o:get_num.o error_functions.o
	gcc -o t_uname get_num.o error_functions.o t_uname.c

## Example 12-1
procfs_pidmax.o:get_num.o error_functions.o
	gcc -o procfs_pidmax get_num.o error_functions.o procfs_pidmax.c

## Exercise 12-1
proc_list.o:get_num.o error_functions.o
	gcc -o proc_list get_num.o error_functions.o mylib.c  proc_list.c

## Example 11-2
t_fpathconf.o:get_num.o error_functions.o
	gcc -o t_fpathconf get_num.o error_functions.o t_fpathconf.c

## Example 11-1
t_sysconf.o:get_num.o error_functions.o
	gcc -o t_sysconf get_num.o error_functions.o t_sysconf.c

## Example 10-5
process_time.o:get_num.o error_functions.o
	gcc -o process_time get_num.o error_functions.o process_time.c

## Example 10-4
show_time.o:get_num.o error_functions.o
	gcc -o show_time get_num.o error_functions.o show_time.c

## Example 10-3
strtime.o:get_num.o error_functions.o
	gcc -o strtime get_num.o error_functions.o curr_time.c strtime.c

## Example 10-1
calendar_time.o:get_num.o error_functions.o
	gcc -o calendar_time get_num.o error_functions.o calendar_time.c

## Exammple 9-1
idshow.o:get_num.o error_functions.o
	gcc -o idshow get_num.o error_functions.o idshow.c

## Exercise 8-2
getpwnam_new.o:get_num.o error_functions.o
	gcc -o getpwnam_new get_num.o error_functions.o getpwnam_new.c

## Example 8-2
check_password.o:get_num.o error_functions.o
	gcc -o check_password -lcrypt get_num.o error_functions.o check_password.c

## Example 8-1
ugid_functions.o:get_num.o error_functions.o
	gcc -o ugid_functions get_num.o error_functions.o ugid_functions.c

## Exercise 7-2
malloc_free_new.o:get_num.o error_functions.o
	gcc -o malloc_free_new get_num.o error_functions.o malloc_free_new.c

## 7-1 Example
free_and_sbrk.o:get_num.o error_functions.o
	gcc -o free_and_sbrk get_num.o error_functions.o free_and_sbrk.c

## 6-3 Exercise
envsettings.o:get_num.o error_functions.o
	gcc -o envsettings get_num.o error_functions.o envsettings.c

## 6-2 Exercise
longjmp_alret.o:get_num.o error_functions.o
	gcc -o longjmp_alret get_num.o error_functions.o longjmp_alret.c

## 6-6 Example
setjmp_vars.o:
	gcc -o setjmp_vars setjmp_vars.c

## 6-5 Example
longjump.o:get_num.o error_functions.o
	gcc -o longjump get_num.o error_functions.o longjump.c

## 6-4 Example
t_mod_env.o:get_num.o error_functions.o
	gcc -o modify_env get_num.o error_functions.o modify_env.c

## 6-3 Example 
display_env.o:get_num.o error_functions.o
	gcc -o display_env get_num.o error_functions.o display_env.c

## 5-2 Example--> readv()
t_readv.o:get_num.o error_functions.o 
	gcc -o t_readv get_num.o error_functions.o t_readv.c

## 5-1 
large_file.o:get_num.o error_functions.o
	gcc -o large_file -D_FILE_OFFSET_BITS=64 get_num.o error_functions.o large_file.c
## 5-2
offappend_file.o:get_num.o error_functions.o
	gcc -o offappend_file get_num.o error_functions.o offappend_file.c

## 5-3
atomic_append.o:get_num.o error_functions.o
	gcc -o atomic_append get_num.o error_functions.o atomic_append.c

## 5-4
dup_new.o:get_num.o error_functions.o
	gcc -o dup_new get_num.o error_functions.o dup_new.c

## 5-5 5-6
filefd_test.o:get_num.o error_functions.o
	gcc -o filefd_test get_num.o error_functions.o filefd_test.c

## 5-7
rdwrv_new.o:get_num.o error_functions.o
	gcc -o rdwrv_new get_num.o error_functions.o rdwrv_new.c

get_num.o: get_num.c get_num.h
	gcc -c get_num.c

error_functions.o: error_functions.c error_functions.h tlpi_hdr.h ename.c.inc
	gcc -c error_functions.c

alt_functions.o: alt_functions.c alt_functions.h 
	gcc -c alt_functions.c
