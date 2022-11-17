#include <iostream>
#include "../my_hash.h"

using namespace std;

int main(){

	HashTable<int,int>* hm = new HashTable<int,int>(20);


	hm->insert(1,3);
	hm->insert(4,3);
	hm->insert(89,3);
	hm->insert(1,5);
	hm->insert(21,6);

	cout<<"HashTable Size and Count : "<<hm->get_size()<<" "<<hm->get_count()<<endl;
	cout<<hm->get(1)<<endl;
	cout<<hm->get(4)<<endl;
	cout<<hm->get(89)<<endl;
	cout<<hm->get(21)<<endl;
	
	hm->delete_key(1);
	hm->delete_key(3);
	hm->delete_key(21);
	cout<<"HashTable Size and Count : "<<hm->get_size()<<" "<<hm->get_count()<<endl;

	return 0;
}
