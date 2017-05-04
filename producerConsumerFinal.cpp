#include<iostream>
#include<stdio.h>
#include<pthread.h>
#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;

pthread_mutex_t the_mutex;//mutex to protect buffer from race conditions
int size = 10;//buffer size
int cnt = 20;//number of producers and consumers
int buffer[10];//buffer on which producer and consumer operate
int in = 0;//index used by producer
int out = 0;//index used by consumer

class semaphore{//implentation of counting semaphore using mutex and condition variable
private:
    std::mutex mutex_;//mutex to lock count
    std::condition_variable condition_;//condition variable for threads to wait on
    int count_;//counter for semaphore

public:
	semaphore(int count_){
		this->count_=count_;//initialise count_ variable
	}
	
    void notify() {
        std::unique_lock<decltype(mutex_)> lock(mutex_);//lock mutex for count variable
        ++count_;//increase count_
        if(count_<=0){//if threads are still waiting on this condition
        	condition_.notify_one();//notify one of them	
        }
    }

    void wait() {
        std::unique_lock<decltype(mutex_)> lock(mutex_);//lock mutex for count variable
        --count_;//decrease count_
        if(count_<0){//if thread can't be run now
        	condition_.wait(lock);//wait on the condition
        } 
    }
};

semaphore notEmpty(0);//counting semaphore for consumer to wait for not empty condition 
semaphore notFull(size);//counting semaphore for producer to wait for not full condition 

void* producer(void *ptr) {
	for(int i=1;i<=cnt;++i){
		cout<<"Producer "<<i<<endl;
	 	notFull.wait();//wait for buffer to be not full
	    pthread_mutex_lock(&the_mutex);//protect buffer
	    buffer[in] = i;//insert item
	    in = (in+1)%size;
	    cout<<"Producer produced : "<<i<<endl;
	    pthread_mutex_unlock(&the_mutex);//release the buffer
	    notEmpty.notify();//notify consumer that buffer is not empty
	}
    pthread_exit(0);
}
 
void* consumer(void *ptr) {
	for(int i=1;i<=cnt;++i){
		cout<<"Consumer "<<i<<endl;
		notEmpty.wait();//wait for buffer to be not full
		pthread_mutex_lock(&the_mutex);//protect buffer
		int item = buffer[out];//remove item
		out = (out+1)%size;
		cout<<"Consumer consumed : "<<item<<endl;
		pthread_mutex_unlock(&the_mutex);//release the buffer
		notFull.notify();//notify producer that buffer is not full
	}
  	pthread_exit(0);
}

int main() {
	//Define Threads and Mutexes
	pthread_t pro, con;
  	pthread_mutex_init(&the_mutex, NULL);	

  	//Create the threads
  	pthread_create(&con, NULL, consumer, NULL);	
  	sleep(1);
  	pthread_create(&pro, NULL, producer, NULL);	
  	
  	//Join Threads
  	pthread_join(con, NULL);
  	pthread_join(pro, NULL);
 
  	//Destroy Mutexes
  	pthread_mutex_destroy(&the_mutex);
	return 0;
}
