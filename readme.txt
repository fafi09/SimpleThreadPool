[root@localhost ThreadPool]# valgrind --leak-check=full -v ./testpool
==28452== Memcheck, a memory error detector.
==28452== Copyright (C) 2002-2006, and GNU GPL'd, by Julian Seward et al.
==28452== Using LibVEX rev 1658, a library for dynamic binary translation.
==28452== Copyright (C) 2004-2006, and GNU GPL'd, by OpenWorks LLP.
==28452== Using valgrind-3.2.1, a dynamic binary instrumentation framework.
==28452== Copyright (C) 2000-2006, and GNU GPL'd, by Julian Seward et al.
==28452== 
--28452-- Command line
--28452--    ./testpool
--28452-- Startup, with flags:
--28452--    --leak-check=full
--28452--    -v
--28452-- Contents of /proc/version:
--28452--   Linux version 2.6.18-128.el5PAE (mockbuild@hs20-bc1-5.build.redhat.com) (gcc version 4.1.2 20080704 (Red Hat 4.1.2-44)) #1 SMP Wed Dec 17 12:02:33 EST 2008
--28452-- Arch and hwcaps: X86, x86-sse1-sse2
--28452-- Valgrind library directory: /usr/lib/valgrind
--28452-- Reading syms from /lib/ld-2.5.so (0x9A2000)
--28452-- Reading syms from /var/ftp/02_Linux_allCodes/my/ThreadPool/testpool (0x8048000)
--28452-- Reading syms from /usr/lib/valgrind/x86-linux/memcheck (0x38000000)
--28452--    object doesn't have a dynamic symbol table
--28452-- Reading suppressions file: /usr/lib/valgrind/default.supp
--28452-- REDIR: 0x9B77B0 (index) redirected to 0x38027D0F (vgPlain_x86_linux_REDIR_FOR_index)
--28452-- Reading syms from /usr/lib/valgrind/x86-linux/vgpreload_core.so (0x4001000)
--28452-- Reading syms from /usr/lib/valgrind/x86-linux/vgpreload_memcheck.so (0x4003000)
==28452== WARNING: new redirection conflicts with existing -- ignoring it
--28452--     new: 0x009B77B0 (index     ) R-> 0x04006080 index
--28452-- REDIR: 0x9B7950 (strlen) redirected to 0x4006250 (strlen)
--28452-- Reading syms from /var/ftp/02_Linux_allCodes/my/ThreadPool/libsimplethreadpool.so (0x4009000)
--28452-- Reading syms from /lib/libpthread-2.5.so (0xB35000)
--28452-- Reading syms from /lib/libc-2.5.so (0x9C0000)
--28452-- REDIR: 0xA30BA0 (memset) redirected to 0x4006540 (memset)
--28452-- REDIR: 0xA31090 (memcpy) redirected to 0x4006C20 (memcpy)
--28452-- REDIR: 0xA2FD00 (rindex) redirected to 0x4005F60 (rindex)
--28452-- REDIR: 0xA2B330 (malloc) redirected to 0x400533B (malloc)
--28452-- REDIR: 0xA2B010 (calloc) redirected to 0x4004668 (calloc)
--28452-- REDIR: 0xA2F960 (strlen) redirected to 0x4006230 (strlen)
job waiting
add job done
add job done
add job done
add job done
threadpool callback fuction : 1.
--28452-- REDIR: 0xA2CB30 (free) redirected to 0x4004F55 (free)
threadpool callback fuction : 2.
threadpool callback fuction : 3.
threadpool callback fuction : 4.
job waiting
threadpool_destroy done
pthread_join before
--28452-- Reading syms from /lib/libgcc_s-4.1.2-20080825.so.1 (0x7A7000)
--28452--    object doesn't have a symbol table
pthread_join after
completed
==28452== 
==28452== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 17 from 1)
--28452-- 
--28452-- supp:   17 Fedora-Core-6-hack3-ld25
==28452== malloc/free: in use at exit: 912 bytes in 5 blocks.
==28452== malloc/free: 12 allocs, 7 frees, 1,300 bytes allocated.
==28452== 
==28452== searching for pointers to 5 not-freed blocks.
==28452== checked 72,548 bytes.
==28452== 
==28452== LEAK SUMMARY:
==28452==    definitely lost: 0 bytes in 0 blocks.
==28452==      possibly lost: 0 bytes in 0 blocks.
==28452==    still reachable: 912 bytes in 5 blocks.
==28452==         suppressed: 0 bytes in 0 blocks.
==28452== Reachable blocks (those to which a pointer was found) are not shown.
==28452== To see them, rerun with: --show-reachable=yes
--28452--  memcheck: sanity checks: 0 cheap, 1 expensive
--28452--  memcheck: auxmaps: 0 auxmap entries (0k, 0M) in use
--28452--  memcheck: auxmaps: 0 searches, 0 comparisons
--28452--  memcheck: SMs: n_issued      = 13 (208k, 0M)
--28452--  memcheck: SMs: n_deissued    = 0 (0k, 0M)
--28452--  memcheck: SMs: max_noaccess  = 65535 (1048560k, 1023M)
--28452--  memcheck: SMs: max_undefined = 0 (0k, 0M)
--28452--  memcheck: SMs: max_defined   = 179 (2864k, 2M)
--28452--  memcheck: SMs: max_non_DSM   = 13 (208k, 0M)
--28452--  memcheck: max sec V bit nodes:    0 (0k, 0M)
--28452--  memcheck: set_sec_vbits8 calls: 0 (new: 0, updates: 0)
--28452--  memcheck: max shadow mem size:   512k, 0M
--28452-- translate:            fast SP updates identified: 2,881 ( 90.6%)
--28452-- translate:   generic_known SP updates identified: 169 (  5.3%)
--28452-- translate: generic_unknown SP updates identified: 128 (  4.0%)
--28452--     tt/tc: 5,541 tt lookups requiring 5,691 probes
--28452--     tt/tc: 5,541 fast-cache updates, 3 flushes
--28452--  transtab: new        2,648 (57,616 -> 948,909; ratio 164:10) [0 scs]
--28452--  transtab: dumped     0 (0 -> ??)
--28452--  transtab: discarded  8 (187 -> ??)
--28452-- scheduler: 51,873 jumps (bb entries).
--28452-- scheduler: 0/3,072 major/minor sched events.
--28452--    sanity: 1 cheap, 1 expensive checks.
--28452--    exectx: 30,011 lists, 26 contexts (avg 0 per list)
--28452--    exectx: 36 searches, 10 full compares (277 per 1000)
--28452--    exectx: 10 cmp2, 59 cmp4, 0 cmpAll



#5 blocks 未释放,是pthread库的调用引起的

#下面的代码验证得出此结论

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>
void call()
{
	pthread_exit("Kill");
	return ;
}
void* run(void* data)
{
	while(1)
	{
		printf("我是线程！%s\n",data);
		sched_yield();
		//return "hello";
		pthread_exit("world");		
	}
}
main()
{
	pthread_t  tid;
	char *re;
	pthread_create(&tid,0,run,"Jack");	
	pthread_join(tid,(void**)&re);
	printf("%s\n",re);
	
}

//=====================验证结果,仍然5 blocks的leak========================
[root@localhost day12]# valgrind --leak-check=full -v ./createth
==28499== Memcheck, a memory error detector.
==28499== Copyright (C) 2002-2006, and GNU GPL'd, by Julian Seward et al.
==28499== Using LibVEX rev 1658, a library for dynamic binary translation.
==28499== Copyright (C) 2004-2006, and GNU GPL'd, by OpenWorks LLP.
==28499== Using valgrind-3.2.1, a dynamic binary instrumentation framework.
==28499== Copyright (C) 2000-2006, and GNU GPL'd, by Julian Seward et al.
==28499== 
--28499-- Command line
--28499--    ./createth
--28499-- Startup, with flags:
--28499--    --leak-check=full
--28499--    -v
--28499-- Contents of /proc/version:
--28499--   Linux version 2.6.18-128.el5PAE (mockbuild@hs20-bc1-5.build.redhat.com) (gcc version 4.1.2 20080704 (Red Hat 4.1.2-44)) #1 SMP Wed Dec 17 12:02:33 EST 2008
--28499-- Arch and hwcaps: X86, x86-sse1-sse2
--28499-- Valgrind library directory: /usr/lib/valgrind
--28499-- Reading syms from /lib/ld-2.5.so (0x9A2000)
--28499-- Reading syms from /var/ftp/02_Linux_allCodes/day12/createth (0x8048000)
--28499-- Reading syms from /usr/lib/valgrind/x86-linux/memcheck (0x38000000)
--28499--    object doesn't have a dynamic symbol table
--28499-- Reading suppressions file: /usr/lib/valgrind/default.supp
--28499-- REDIR: 0x9B77B0 (index) redirected to 0x38027D0F (vgPlain_x86_linux_REDIR_FOR_index)
--28499-- Reading syms from /usr/lib/valgrind/x86-linux/vgpreload_core.so (0x4001000)
--28499-- Reading syms from /usr/lib/valgrind/x86-linux/vgpreload_memcheck.so (0x4003000)
==28499== WARNING: new redirection conflicts with existing -- ignoring it
--28499--     new: 0x009B77B0 (index     ) R-> 0x04006080 index
--28499-- REDIR: 0x9B7950 (strlen) redirected to 0x4006250 (strlen)
--28499-- Reading syms from /lib/libpthread-2.5.so (0xB35000)
--28499-- Reading syms from /lib/libc-2.5.so (0x9C0000)
--28499-- REDIR: 0xA30BA0 (memset) redirected to 0x4006540 (memset)
--28499-- REDIR: 0xA31090 (memcpy) redirected to 0x4006C20 (memcpy)
--28499-- REDIR: 0xA2FD00 (rindex) redirected to 0x4005F60 (rindex)
--28499-- REDIR: 0xA2B010 (calloc) redirected to 0x4004668 (calloc)
--28499-- REDIR: 0xA2F960 (strlen) redirected to 0x4006230 (strlen)
我是线程！Jack
--28499-- REDIR: 0xA2B330 (malloc) redirected to 0x400533B (malloc)
--28499-- Reading syms from /lib/libgcc_s-4.1.2-20080825.so.1 (0x7A7000)
--28499--    object doesn't have a symbol table
world
--28499-- REDIR: 0xA2CB30 (free) redirected to 0x4004F55 (free)
==28499== 
==28499== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 15 from 1)
--28499-- 
--28499-- supp:   15 Fedora-Core-6-hack3-ld25
==28499== malloc/free: in use at exit: 912 bytes in 5 blocks.
==28499== malloc/free: 6 allocs, 1 frees, 1,048 bytes allocated.
==28499== 
==28499== searching for pointers to 5 not-freed blocks.
==28499== checked 64,388 bytes.
==28499== 
==28499== LEAK SUMMARY:
==28499==    definitely lost: 0 bytes in 0 blocks.
==28499==      possibly lost: 0 bytes in 0 blocks.
==28499==    still reachable: 912 bytes in 5 blocks.
==28499==         suppressed: 0 bytes in 0 blocks.
==28499== Reachable blocks (those to which a pointer was found) are not shown.
==28499== To see them, rerun with: --show-reachable=yes
--28499--  memcheck: sanity checks: 0 cheap, 1 expensive
--28499--  memcheck: auxmaps: 0 auxmap entries (0k, 0M) in use
--28499--  memcheck: auxmaps: 0 searches, 0 comparisons
--28499--  memcheck: SMs: n_issued      = 13 (208k, 0M)
--28499--  memcheck: SMs: n_deissued    = 0 (0k, 0M)
--28499--  memcheck: SMs: max_noaccess  = 65535 (1048560k, 1023M)
--28499--  memcheck: SMs: max_undefined = 0 (0k, 0M)
--28499--  memcheck: SMs: max_defined   = 179 (2864k, 2M)
--28499--  memcheck: SMs: max_non_DSM   = 13 (208k, 0M)
--28499--  memcheck: max sec V bit nodes:    0 (0k, 0M)
--28499--  memcheck: set_sec_vbits8 calls: 0 (new: 0, updates: 0)
--28499--  memcheck: max shadow mem size:   512k, 0M
--28499-- translate:            fast SP updates identified: 2,603 ( 90.6%)
--28499-- translate:   generic_known SP updates identified: 150 (  5.2%)
--28499-- translate: generic_unknown SP updates identified: 120 (  4.1%)
--28499--     tt/tc: 5,125 tt lookups requiring 5,248 probes
--28499--     tt/tc: 5,125 fast-cache updates, 3 flushes
--28499--  transtab: new        2,441 (53,442 -> 881,295; ratio 164:10) [0 scs]
--28499--  transtab: dumped     0 (0 -> ??)
--28499--  transtab: discarded  8 (187 -> ??)
--28499-- scheduler: 40,014 jumps (bb entries).
--28499-- scheduler: 0/2,774 major/minor sched events.
--28499--    sanity: 1 cheap, 1 expensive checks.
--28499--    exectx: 30,011 lists, 17 contexts (avg 0 per list)
--28499--    exectx: 22 searches, 5 full compares (227 per 1000)
--28499--    exectx: 10 cmp2, 55 cmp4, 0 cmpAll
