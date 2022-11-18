#include <stdio.h>
#include <stdlib.h>
#include "../my_malloc.h"

int main()
{	
	int len = 10;
	int* numbers = (int*)my_malloc(len*sizeof(int));
	
	for(int i=0;i<len;i++){
		numbers[i] = i;
	}
	while(len--){
		printf("==================\n");
		printf("%p : ",&numbers[len]);
		printf("%d\n",numbers[len]);
	}
	printf("==================\n\n");

	int len2 = 20;
	char* string = (char*)my_malloc(len2*sizeof(char));
	
	for(int i=0;i<len2;i++){
		string[i] = i + '0';
	}
	while(len2--){
		printf("==================\n");
		printf("%p : ",&string[len2]);
		printf("%d\n",string[len2]);
	}
	printf("==================\n\n");
	
	int len3 = 30;
	int* numbers2 = (int*)my_malloc(len3*sizeof(int));
	
	for(int i=0;i<len3;i++){
		numbers2[i] = i;
	}
	while(len3--){
		printf("==================\n");
		printf("%p : ",&numbers2[len3]);
		printf("%d\n",numbers2[len3]);
	}
	printf("==================\n\n");

	my_free(string);
	my_free(numbers);
	my_free(numbers2);

	return 0;

}
