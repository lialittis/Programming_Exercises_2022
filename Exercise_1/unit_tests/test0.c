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
	printf("==================\n");

	my_free(numbers);
	return 0;

}
