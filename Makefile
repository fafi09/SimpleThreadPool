#export LD_LIBRARY_PATH=/lib:/usr/lib:.:
DEL_FILE      = rm -f
DEBUG_OPTION  = -g
Jpt:lnk
	gcc $(DEBUG_OPTION) main.c  simplethreadpool.h -lsimplethreadpool -lpthread -L. -otestpool
lnk:compile
	gcc -shared -olibsimplethreadpool.so simplethreadpool.o
compile:
	gcc -c -fpic simplethreadpool.c simplethreadpool.h
clean:
	$(DEL_FILE) simplethreadpool.o
	$(DEL_FILE) simplethreadpool.h.gch
	