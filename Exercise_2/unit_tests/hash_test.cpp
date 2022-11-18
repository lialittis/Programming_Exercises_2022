#include <iostream>
#include "my_hash.h"

using namespace std;

int main(){

	HashTable<int,int>* ht = new HashTable<int,int>(20);


	ht->insert(1,3);
	ht->insert(4,3);
	ht->insert(89,3);
	ht->insert(1,5);
	ht->insert(21,6);

	ht->display();
	int value;
	cout<<"HashTable Size and Count : "<<ht->get_size()<<" "<<ht->get_count()<<endl;
	ht->get(1,value);
	cout<<value<<endl;
	ht->get(4,value);
	cout<<value<<endl;
	ht->get(89,value);
	cout<<value<<endl;
	ht->get(21,value);
	cout<<value<<endl;
	
	ht->delete_key(1);
	ht->display();
	ht->delete_key(3);
	ht->display();
	ht->delete_key(21);
	cout<<"HashTable Size and Count : "<<ht->get_size()<<" "<<ht->get_count()<<endl;

	ht->display();

	return 0;
}
