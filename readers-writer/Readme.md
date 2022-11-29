# Readers-Writer Lock

About Readers-Writer Lock, we may have to consider the priority policies.
If we choose read-preferring, there could be problem of starvation.
If we choose write-preferring, it may allow for less concurrency.

## Read-preferring

I offered two ways of implementing(using mutex and semaphore),
they are in `rw_lock_mutex.cpp` and `rw_lock_sem.cpp`. As setting the initial
semaphore as 1, it performs as same as mutex.

- readersCount: count the numebr of current readers
- countMutex: protect the readersCount
- writeMutex: protect the writing process

**Read Starts(Reader Lock):**
- get countMutex lock
- increment the count
- if readersCount is 1(the first reader), get the writer lock(let the writer wait)
- release countMutex lock

**Read End(Reader Unlock):**
- get countMutex lock
- decrease the count
- if the readerCount is 0, release the writer lock(no readers)
- release the countMutex lock

**Write Starts(Writer Lock):**
- get the writer lock

**Write Ends(Writer Unlock):**
- release the writer lock

## Writing-preferring

It is implmented in `rw_lock_con.cpp`

- r: count the numebr of current readers
- w: count the numebr of waiting writers
- mutex: lock to protect counters
- cond: condition variable

**Read Starts(Reader Lock):**
- get lock
- while the number of writers > 0, wait for the condition(stop reading)
- after the waiting, increment the reader count
- release lock

**Read End(Reader Unlock):**
- get lock
- decrease the reader count
- if the reader count is 0, reach the condition and wake up the blocked threads
- release the lock


**Write Starts(Writer Lock):**
- get lock
- while waiting writers is not zero or readers number > 0, wait for the contition(wait for other writers or readers)
- after waiting, set the number of writer as 1
- release the lock

**Write Ends(Writer Unlock):**
- get lock
- set the writer count as 0
- wake up the blocked threads
- release the lock

