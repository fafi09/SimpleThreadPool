#include "simplethreadpool.h"

struct simplethreadpool* threadpool_init(int poolsize, int queue_max_num)
{
	int i;
	struct simplethreadpool* threadpool 
			= (struct simplethreadpool*)malloc(sizeof(struct simplethreadpool));
	
	if(threadpool == NULL)
	{ 
		printf("thread pool malloc error\n");
		return NULL;
	}
	threadpool->poolsize = poolsize;
	threadpool->queue_max_num = queue_max_num;
	threadpool->cur_job_nums = 0;
	//初始化工作队列头
	threadpool->head = NULL;
	//初始化工作队列尾
	threadpool->tail = NULL;
	threadpool->queue_close = 0;
	threadpool->pool_close = 0;
	threadpool->pthread_nums = malloc(sizeof(pthread_t) * poolsize);
	if(threadpool->pthread_nums == NULL) 
	{ 
		printf("thread pool pthread_nums malloc error\n");
		return NULL;
	}
	
	//初始化线程互斥锁
	pthread_mutex_init(&(threadpool->mutex),NULL);
	
	//初始化条件变量
	pthread_cond_init(&(threadpool->queue_empty),NULL);
	pthread_cond_init(&(threadpool->queue_not_empty),NULL);
	pthread_cond_init(&(threadpool->queue_not_full),NULL);
	
	//启动线程
	for(i = 0; i < poolsize; i++)
	{
		pthread_create(&(threadpool->pthread_nums[i]),NULL,threadpool_function, (void *)threadpool);
	}
	
	return threadpool;
	//free(threadpool);
	
}


int threadpool_add_job(struct simplethreadpool* pool, void *(*callback_function)(void*), void *arg)
{
	struct job* job = NULL;
	struct simplethreadpool* threadpool = (struct simplethreadpool*)pool;
	pthread_mutex_lock(&(threadpool->mutex));
	//工作项在队列中已满
	while((threadpool->cur_job_nums == threadpool->queue_max_num) 
					&& !(threadpool->queue_close || threadpool->pool_close))
	{
		printf("add job waiting\n");
		pthread_cond_wait(&(threadpool->queue_not_full),&(threadpool->mutex));
	}
	
	if(threadpool->queue_close || threadpool->pool_close)
	{
		pthread_mutex_unlock(&(threadpool->mutex));
		return -1;
	}
	printf("add job done\n");
	job = malloc(sizeof(struct job));
	job->callback_function = callback_function;
	job->arg = arg;
	job->next = NULL;
	
	if(threadpool->head == NULL)
	{
		threadpool->head = threadpool->tail = job;
		pthread_cond_broadcast(&(threadpool->queue_not_empty));
	}
	else
	{
		threadpool->tail->next = job;
		threadpool->tail = job;
	}
	threadpool->cur_job_nums++;
	pthread_mutex_unlock(&(threadpool->mutex));
}

void* threadpool_function(void* pool)
{
	struct job* pjob = NULL;
	struct simplethreadpool* threadpool = (struct simplethreadpool*)pool;
	
	while(1)
	{
		pthread_mutex_lock(&(threadpool->mutex));
		//队列中没有工作项,那么等待有工作项在执行
		//线程池关闭时结束等待
		//队列关闭时当前线程数还有可能不为0，队列关闭主要针对不允许增加任务
		while(threadpool->cur_job_nums == 0 && threadpool->pool_close != 1)
		{
			printf("job waiting\n");
			pthread_cond_wait(&(threadpool->queue_not_empty),&(threadpool->mutex));
		}
		//线程池关闭时退出线程
		if(threadpool->pool_close == 1)
		{
			pthread_mutex_unlock(&(threadpool->mutex));
			pthread_exit(NULL);
		}
		
		if(threadpool->head != NULL)
		{
			threadpool->head->callback_function(threadpool->head->arg);
			pjob = threadpool->head;
			threadpool->head = threadpool->head->next;
			pjob->next = NULL;
			free(pjob);
			threadpool->cur_job_nums--;
		}
		
		//pthread_cond_broadcast(&(threadpool->queue_empty));
		//pthread_cond_broadcast(&(threadpool->queue_not_full));
		if (threadpool->cur_job_nums == 0)
    {
        pthread_cond_signal(&(threadpool->queue_empty));        //队列为空，就可以通知threadpool_destroy函数，销毁线程函数
        																												//通知某一个线程销毁就可以
    }
    if (threadpool->cur_job_nums == threadpool->queue_max_num - 1)
    {
        pthread_cond_broadcast(&(threadpool->queue_not_full));  //队列非满，就可以通知threadpool_add_job函数，添加新任务
        																												//通知所有线程增加任务
    }
		pthread_mutex_unlock(&(threadpool->mutex));
		
	}
}

int threadpool_destroy(struct simplethreadpool* threadpool)
{
	int i;
	struct job* job = NULL;
	pthread_mutex_lock(&(threadpool->mutex));
	
	if(threadpool->queue_close || threadpool->pool_close)
	{
		pthread_mutex_unlock(&(threadpool->mutex));
		return -1;
	}
	
	threadpool->queue_close = 1; //主动关闭工作队列
	while(threadpool->cur_job_nums != 0)
	{
		printf("threadpool_destroy waiting\n");
		pthread_cond_wait(&(threadpool->queue_empty),&(threadpool->mutex));
	}
	
	threadpool->pool_close = 1; //主动关闭线程池
	printf("threadpool_destroy done\n");
	pthread_mutex_unlock(&(threadpool->mutex));
	//唤醒等待的线程
	pthread_cond_broadcast(&(threadpool->queue_not_empty));
	pthread_cond_broadcast(&(threadpool->queue_not_full));
	
	printf("pthread_join before\n");
	//等线程都执行完
	for(i = 0; i < threadpool->poolsize; i++)
	{
		pthread_join(threadpool->pthread_nums[i], NULL);
	}
	printf("pthread_join after\n");
	
	pthread_cond_destroy(&(threadpool->queue_empty));
	pthread_cond_destroy(&(threadpool->queue_not_empty));
	pthread_cond_destroy(&(threadpool->queue_not_full));
	
	pthread_mutex_destroy(&(threadpool->mutex));
	
	free(threadpool->pthread_nums);
	
	while(threadpool->head != NULL)
	{
		job = threadpool->head;
		threadpool->head = job->next;
		free(job);
	}
	free(threadpool);
	return 0;
}
