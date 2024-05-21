#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void selection_sort(int arr[], int n) 
{
    int i, j, min_index;
    for (i = 0; i < n - 1; i++) 
	{
        min_index = i;
        for (j = i + 1; j < n; j++) 
		{
            if (arr[j] < arr[min_index]) 
			{
                min_index = j;
            }
        }
        int temp = arr[min_index];
        arr[min_index] = arr[i];
        arr[i] = temp;
    }

}


void* sort_th(void *param)
{
	int* arr = (int*)param;
	int n =10;
	selection_sort(arr,n);
	printf("Sorting Completed\n");
	pthread_exit(NULL);
}

int main()
{	
	int ret;
	int arr1[10]={48,198,5,63,42,2,0,17,5,8};
	
	pthread_t a1;
	ret = pthread_create(&a1,NULL,sort_th,(void*)arr1);
	if(ret < 0)
	{
		perror("pthread_create() failed");
		_exit(0);
	}

	pthread_join(a1,NULL);

	printf("Array in sorted form : ");
	for(int i = 0; i < 10; i++)
	{
		printf("%d ",arr1[i]);
	}

	printf("\n");
	return 0;
}

