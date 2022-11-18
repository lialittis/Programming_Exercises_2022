#ifndef __MY_HASH_H__
#define __MY_HASH_H__

#include <shared_mutex>
#include <vector>
#include <type_traits>
#include <iostream>
#include "my_locks.h"
#pragma once

#define DEFAULT_SIZE 		10

template <class Key, class Value>
class HashTable {
private:
	struct DataEntry{
		Key key;
		Value value;
		DataEntry* next;
		DataEntry(const Key& key = Key(), const Value& val = Value()) : key(key),value(val),next(NULL) {}
	};
	int count;
	std::vector<DataEntry*> arr;
	std::shared_timed_mutex m_lock;
public:
	explicit HashTable(int size = DEFAULT_SIZE):count(0), arr(size) {
		printf("Create a hash table with size :%d\n",size);
	};
	
	~HashTable() {}


	int get_size(){
		return arr.size();
	}

	int get_count(){
		return count;
	}

	/**
	 * hash function
	 *
	 * hash(key) = key % hashsize
	 * Note that, key is converted into char and then do the calculation
	 */
	int hash(const Key& key) const{
		unsigned int hashVal = 0; // initialization

		const char* strc = reinterpret_cast<const char*>(&key);
		
		for(size_t i = 0; i < sizeof(Key); ++i) {
			hashVal = 37 * hashVal + strc[i];  // get ascii value of strc[i]
		}

		return hashVal % arr.size();
	}

	/**
	 * hashfind
	 */
	DataEntry* hashfind(const Key& key){

		int position = hash(key);
		DataEntry* p = arr[position];
		for(;p!=NULL;p=p->next){
			if(p->key==key) // TODO : overwrite == operator
				return p;
		}
		return NULL;
	}

	bool get(const Key& key,Value& val){
		// ReadLock
		ReadLock lock(m_lock);
		
		int position = hash(key);
		DataEntry* p = arr[position];
		
		if(!p) return 0;

		while(p->key != key && p->next){ // TODO : may need overwrite != operator 
			p = p->next;
		}
		if(p) { 
			val = p->value;
			return 1;
		}
		else{
			return 0; // return empty
		}
	
	}

	void insert(const Key& key, const Value& val){
		// Write Lock
		WriteLock lock(m_lock);

		int position;
		DataEntry* p;
		if((p=hashfind(key))==NULL){ // there is no key stored
			position = hash(key);
			p = new DataEntry(key,val);
			p->next = arr[position]; // insert the key value as the new header of the linked list
			arr[position] = p;
			count++;
		}else{ // the key is already existed
			p->value = val; // TODO : do I need to delete the original value or not ?
		}
	}

	bool delete_key(const Key& key){
		// Write Lock
		WriteLock lock(m_lock);
		
		int position = hash(key);
		DataEntry *p = NULL,*q = NULL;
		p = arr[position];
		if(!p) return 0;
		if(key == p->key){  // TODO : == operator
			arr[position] = p->next;
			delete p;
		}else{
			q = p;
			p = q->next;
			while(p && (p->key != key)){ // TODO: != operator
				q = p;
				p = p->next;
			}
			if(p){
				q->next = p->next;
				delete p;
			}
		}
		count--;
		return 1;
	}


	void display(){
		// Write Lock
		WriteLock lock(m_lock);
		
		std::cout<<std::endl;
		std::cout<<"====Hash Table===="<<std::endl;
		DataEntry* p;
		for(int i=0; i<(int)arr.size();i++){
			if(!arr[i]){
				std::cout<<"[NULL]"<<std::endl;
			}else{
				p = arr[i];
				std::cout<<"[";
				while(p){
					std::cout<<"["<<p->key<<":"<<p->value<<"]->";
					p = p->next;
				}
				std::cout<<"NULL]"<<std::endl;
			}
		}
		std::cout<<"======END======"<<std::endl<<std::endl;
	}

	void clear(){
		// Write Lock
		WriteLock lock(m_lock);
		for(int i=0; i<arr.size();i++){
			DataEntry* p = arr[i],*q;
			while(p){
				q = p;
				p = p->next;
				delete q;
			}
		}
	}
};


#endif // __MY_HASH_H__
