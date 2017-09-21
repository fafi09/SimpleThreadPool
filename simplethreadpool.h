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
	int poolsize;       //�̳߳��п����̵߳ĸ���
	int queue_max_num;    //���������job�ĸ���
	struct job* head;
	struct job* tail;
	pthread_t* pthread_nums;
	pthread_mutex_t mutex; //�߳���
	pthread_cond_t queue_empty;    //�ȴ�ֱ������Ϊ�յ�������
	pthread_cond_t queue_not_empty;    //�ȴ�ֱ�����в�Ϊ�յ�������
	pthread_cond_t queue_not_full;    //�ȴ�ֱ�����в�����������
	int cur_job_nums;
	int queue_close;  //���û�����ֵ,������destroy poolʱ,
										//run jobһֱ�ȴ�,���ܵ���destroy pool
										//���йرվͲ�������������
	int pool_close;   //�̳߳عر�Ҳ�������������ˣ�
										//Ҳ�����ٴε��������̳߳�
	
};

struct simplethreadpool* threadpool_init(int poolsize, int queue_max_num);
int threadpool_add_job(struct simplethreadpool* pool, void *(*callback_function)(void* arg), void *arg);
void* threadpool_function(void* pool);
int threadpool_destroy(struct simplethreadpool* threadpool);

#endif
