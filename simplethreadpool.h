#ifndef SIMPLE_THREAD_POOL_H
#define SIMPLE_THREAD_POOL_H

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

struct job
{
	void *(*callback_function)(void* arg);
	void *arg;
	struct job *next;
};

struct simplethreadpool
{
	int poolsize;       //线程池中开启线程的个数
	int queue_max_num;    //队列中最大job的个数
	struct job* head;
	struct job* tail;
	pthread_t* pthread_nums;
	pthread_mutex_t mutex; //线程锁
	pthread_cond_t queue_empty;    //等待直到队列为空的条件量
	pthread_cond_t queue_not_empty;    //等待直到队列不为空的条件量
	pthread_cond_t queue_not_full;    //等待直到队列不满的条件量
	int cur_job_nums;
	int queue_close;  //如果没有这个值,当主动destroy pool时,
										//run job一直等待,不能到达destroy pool
										//队列关闭就不能增加任务了
	int pool_close;   //线程池关闭也不能增加任务了，
										//也不能再次调用销毁线程池
	
};

struct simplethreadpool* threadpool_init(int poolsize, int queue_max_num);
int threadpool_add_job(struct simplethreadpool* pool, void *(*callback_function)(void* arg), void *arg);
void* threadpool_function(void* pool);
int threadpool_destroy(struct simplethreadpool* threadpool);

#endif
