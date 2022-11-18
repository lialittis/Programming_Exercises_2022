#ifndef __MY_LOCKS_H__
#define __MY_LOCKS_H__

#include <mutex>
#include <shared_mutex>

#define LOOP_COUNT 		2000000

typedef std::shared_lock<std::shared_timed_mutex> ReadLock;
//typedef std::shared_lock<std::shared_mutex> ReadLock;

//typedef std::lock_guard<std::shared_timed_mutex> WriteLock;
typedef std::unique_lock<std::shared_timed_mutex> WriteLock;

#endif // __MY_LOCKS_H__
