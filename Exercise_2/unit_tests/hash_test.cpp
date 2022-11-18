#include <iostream>
#include "../my_hash.h"

using namespace std;

int main(){

	HashTable<int,int>* ht = new HashTable<int,int>(20);


	ht->insert(1,3);
	ht->insert(4,3);
	ht->insert(89,3);
	ht->insert(1,5);
	ht->insert(21,6);

	cout<<"HashTable Size and Count : "<<ht->get_size()<<" "<<ht->get_count()<<endl;
	cout<<ht->get(1)<<endl;
	cout<<ht->get(4)<<endl;
	cout<<ht->get(89)<<endl;
	cout<<ht->get(21)<<endl;
	
	ht->delete_key(1);
	ht->delete_key(3);
	ht->delete_key(21);
	cout<<"HashTable Size and Count : "<<ht->get_size()<<" "<<ht->get_count()<<endl;

	return 0;
}
