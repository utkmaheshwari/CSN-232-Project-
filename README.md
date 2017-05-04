# CSN-232-Project-
# Banker's Algorithm and Producer-Consumer Implementation using counting semaphore and mutex. The code has been documented.
 
# Project Members
Utkarsh Maheshwari    	13115130
Hari Eswar Sm           13115053
Aman Pahariya           13115016
Avishek De              13113030
Shubham Sharma        	13115116

 
# Problem Statement
The concept of the producer-consumer problem was introduced in detailed in the class. So in this project, you need to implement the famous producer consumer problem using Pthreads.
The following points should be taken care of properly for successful compilation of the project:
1. Rather than using binary semaphores for empty and full, you will be using standard counting semaphores and mutex lock to replace mutex binary semaphore.
2.  The programs should be thread safe.
3. Standard mutex locks can be used
Extend the above module using a multithreaded program that implements the banker’s algorithm. The banker will grant the request only if it leaves the system in a safe state. Here also mutex locks will be used to safe data access. A thorough analysis is to be done to showcase the working of the model. The team will get additional credits if they improve the model with different ideas.
 
# Introduction
A thread is a stream of instructions that can be scheduled as an independent unit. A thread exists within a process, and uses the process resources. Since threads are very small compared with processes, thread creation is relatively cheap in terms of CPU costs.
Multithreaded programs may have several threads running through different code paths simultaneously.
 
# Pthreads
The Pthreads library is a POSIX C API thread library that has standardized functions for using threads across different platforms. Historically, hardware vendors have implemented their own proprietary versions of threads. These implementations differed substantially from each other making it difficult for programmers to develop portable threaded applications. In order to take full advantage of the capabilities provided by threads, a standardized programming interface was required.
For UNIX systems, this interface has been specified by the IEEE POSIX 1003.1c standard (1995). Implementations that adhere to this standard are referred to as POSIX threads, or Pthreads. Most hardware vendors now offer Pthreads in addition to their proprietary API's. Pthreads are defined as a set of C language programming types and procedure calls. Vendors usually provide a Pthreads implementation in the form of a header/include file and a library that you link with your program.
 
# Semaphores
A semaphore is an abstract datatype manually defined that will enable access/control access in a concurrent system with certain conditions that would be followed. A semaphore is usually non negative. Semaphores are typically used to coordinate access to resources, with the semaphore count initialized to the number of free resources. Threads then atomically increment the count when resources are added and atomically decrement the count when resources are removed. This is just convention and implementation could also be done on the negative scale of the number line.
Semaphores must be initialized before use, but they do not have attributes. The declaration can be seen as a Class datatype. There are two type of Semaphores:
1. Binary semaphores are binary, they can have two values only; one to represent that a process/thread is in the critical section(code that access the shared resource) and others should wait, the other indicating the critical section is free.
2. Counting semaphores take more than two values, they can have any value you want. The max value X they take allows X process/threads to access the shared resource simultaneously.
The project is implemented through counting semaphore as evident in the problem statement. The max value that a counting semaphore can take is the number of processes you want to allow into the critical section at the same time.
 
# Software Requirements
C++14 compiler is required for this purpose. The libraries imported were unistd and pthreads.
 
# Implementation
# 1. Producer Consumer Problem
In computing, the producer–consumer problem (also known as the bounded-buffer problem) is a classic example of a multi-process synchronization problem. The problem describes two processes, the producer and the consumer, who share a common, fixed-size buffer used as a queue. The producer's job is to generate data, put it into the buffer, and start again. At the same time, the consumer is consuming the data (i.e., removing it from the buffer), one piece at a time. The problem is to make sure that the producer won't try to add data into the buffer if it's full and that the consumer won't try to remove data from an empty buffer.
There are two semaphores used in this process:
1. notEmpty – to check if the buffer is not empty
2. notFull - to check if the buffer is not full
Mutual Exclusion is implemented with the help of pthreads. Pthread module is already available in C++ under the header pthread.h
# Producer Process:
If buffer is full, we cannot produce further processes. So the producer goes into an infinite loop. Else, start producing process by maintain the count variable i.
buffer[in] = nextProduced;
in = (in+1)%buffer_size;
counter++;
# Consumer Process:
If buffer is empty, we cannot consume any process. So the consumer goes into an infinite loop. Else, start consuming process by using another count variable.
nextConsumed = buffer[out];
out = (out+1)%buffer_size;
counter--;
 
 
# 2. Banker’s Algorithm
The Banker's algorithm, sometimes referred to as the avoidance algorithm, is a resource allocation and deadlock avoidance algorithm. It tests for safety by simulating the allocation of predetermined maximum possible amounts of all resources, and then makes an s-state check to test for possible deadlock conditions for all other pending activities, before deciding whether allocation should be allowed to continue.
Resources may be allocated to a process only if it satisfies the following condition:
request ≤ available, otherwise process waits until resources are available.
Some of the resources that are tracked in real systems are memory, semaphores and interface access.
The Banker's Algorithm derives its name from the fact that this algorithm could be used in a banking system to ensure that the bank does not run out of resources, because the bank would never allocate its money in such a way that it can no longer satisfy the needs of all its customers . By using the Banker's algorithm, the bank ensures that when customers request money the bank never leaves a safe state. If the customer's request does not cause the bank to leave a safe state, the cash will be allocated, otherwise the customer must wait until some other customer deposits enough.
Basic data structures to be maintained to implement the Banker's Algorithm:
Let n be the number of processes in the system and m be the number of resource types. Then we need the following data structures:
Available: A vector of length m indicates the number of available resources of each type. If Available[j] = k, there are k instances of resource type Rj available.
Max: An n×m matrix defines the maximum demand of each process. If Max[i,j] = k, then Pi may request at most k instances of resource type Rj.
Allocation: An n×m matrix defines the number of resources of each type currently allocated to each process. If Allocation[i,j] = k, then process Pi is currently allocated k instances of resource type Rj.
Need: An n×m matrix indicates the remaining resource need of each process. If Need[i,j] = k, then Pi may need k more instances of resource type Rj to complete the task.
  
# Conclusion
The producer consumer problem for multi-threaded processes is implemented with pthreads. Following this Banker’s Algorithm was also implemented using pthreads. Checks were implemented to check resource allocation conditions.
 


