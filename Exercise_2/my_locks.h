#ifndef MY_LOCKS_H
#define MY_LOCKS_H

#include <mutex>
#include <shared_mutex>

#define READ_THREAD_COUNT 	8
#define LOOP_COUNT 		1000000

typedef std::shared_lock<std::shared_timed_mutex> ReadLock; // shared_mutex not found in std
//typedef std::shared_lock<std::shared_mutex> ReadLock;

//typedef std::lock_guard<std::shared_timed_mutex> WriteLock;
typedef std::unique_lock<std::shared_timed_mutex> WriteLock;

#endif // MY_LOCKS_H
