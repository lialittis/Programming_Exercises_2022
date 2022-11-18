#include <cstdint>
#include <functional>
#include <iostream>
#include <mutex>
#include <iostream>
#include <chrono>
#include <thread>

#include "my_hash.h"

using namespace std;

void testThread1(HashTable<int,int>& ht){
	
	cout<<"Starting Thread 1"<<endl;
	ht.insert(2,3);
	ht.insert(3,4);
	ht.insert(34,87);
	ht.insert(90,21);
	this_thread::sleep_for(chrono::seconds(1));

	int value;
	if(ht.get(20,value)) cout <<"Thread 1: found value "<<value<<endl;
	else cout<<"Thread 1: no key "<<20<<endl;
	if(ht.get(2,value)) cout <<"Thread 1: found value "<<value<<endl;
	else cout<<"Thread 1: no key "<<2<<endl;
	if(ht.get(34,value)) cout <<"Thread 1: found value "<<value<<endl;
	else cout<<"Thread 1: no key "<<34<<endl;
	if(ht.get(90,value)) cout <<"Thread 1: found value "<<value<<endl;
	else cout<<"Thread 1: no key "<<90<<endl;

	this_thread::sleep_for(chrono::seconds(1));
	ht.insert(24,312);
	ht.insert(398,43);
	ht.insert(3,82);
	ht.insert(20,23);

	ht.delete_key(2);
	ht.delete_key(398);

	if(ht.get(20,value)) cout <<"Thread 1: found value "<<value<<endl;
	else cout<<"Thread 1: no key "<<20<<endl;
	if(ht.get(2,value)) cout <<"Thread 1: found value "<<value<<endl;
	else cout<<"Thread 1: no key "<<2<<endl;
	if(ht.get(34,value)) cout <<"Thread 1: found value "<<value<<endl;
	else cout<<"Thread 1: no key "<<34<<endl;
	if(ht.get(90,value)) cout <<"Thread 1: found value "<<value<<endl;
	else cout<<"Thread 1: no key "<<90<<endl;

}

void testThread2(HashTable<int,int>& ht){
	
	cout<<"Starting Thread 2"<<endl;
	ht.insert(20,312);
	ht.insert(335,423);
	this_thread::sleep_for(chrono::seconds(1));
	ht.insert(134,8317);
	ht.insert(920,214);

	int value;
	if(ht.get(202,value)) cout <<"Thread 2: found value "<<value<<endl;
	else cout<<"Thread 2: no key "<<202<<endl;
	if(ht.get(2,value)) cout <<"Thread 2: found value "<<value<<endl;
	else cout<<"Thread 2: no key "<<2<<endl;
	if(ht.get(34,value)) cout <<"Thread 2: found value "<<value<<endl;
	else cout<<"Thread 2: no key "<<34<<endl;
	if(ht.get(90,value)) cout <<"Thread 2: found value "<<value<<endl;
	else cout<<"Thread 2: no key "<<90<<endl;

	this_thread::sleep_for(chrono::seconds(1));
	ht.insert(90,312);
	ht.insert(38,43);
	ht.insert(13,82);
	this_thread::sleep_for(chrono::seconds(1));
	ht.insert(350,23);

	ht.delete_key(20);
	ht.delete_key(398);

	if(ht.get(350,value)) cout <<"Thread 2: found value "<<value<<endl;
	else cout<<"Thread 2: no key "<<350<<endl;
	if(ht.get(13,value)) cout <<"Thread 2: found value "<<value<<endl;
	else cout<<"Thread 2: no key "<<13<<endl;
	if(ht.get(34,value)) cout <<"Thread 2: found value "<<value<<endl;
	else cout<<"Thread 2: no key "<<34<<endl;
	if(ht.get(134,value)) cout <<"Thread 2: found value "<<value<<endl;
	else cout<<"Thread 2: no key "<<134<<endl;

}


int main(){

	HashTable<int,int> ht;
	thread firstThread(testThread1,ref(ht));
	thread secondThread(testThread2,ref(ht));

	firstThread.join();
	secondThread.join();

	return 0;
}

