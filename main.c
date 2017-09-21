#include "simplethreadpool.h"

void* work(void* arg)
{
    char *p = (char*) arg;
    printf("threadpool callback fuction : %s.\n", p);
    sleep(1);
}


int main(int argc, char *argv[])
{
	
	struct simplethreadpool *pool = threadpool_init(10, 20);
  threadpool_add_job(pool, work, "1");
  threadpool_add_job(pool, work, "2");
  threadpool_add_job(pool, work, "3");
	threadpool_add_job(pool, work, "4");
	
  sleep(5);
  threadpool_destroy(pool);
  printf("completed\n");
  
  
  /*
  struct simplethreadpool* threadpool 
			= (struct simplethreadpool*)malloc(sizeof(struct simplethreadpool));
	threadpool->pthread_nums = malloc(sizeof(pthread_t) * 1);
	free(threadpool->pthread_nums);
	free(threadpool);
	*/
  return 0;
}
