#include "Noise.h"

int main (void) //test
{
	srand((unsigned int)time(NULL));//seed rand with time, small %'s only
	int*vals=NULL;
	int n=6, size=(int)pow(2,(double)n);
	int avg=0,count=0;
	while(1)
	{
		if(vals!=NULL)free(vals);
		vals=(int*)malloc(size*size*sizeof(int));
		fractal_noise(vals,n);
		avg=0;count=0;
		for(int i=0;i<size*size;i++) {
			avg+=vals[i];count++;
		}	avg/=count;
		for(int x=0;x<size;x++)
		{	for(int y=0;y<size;y++)
			{	if(vals[x*size+y]>=10)
					printf(":^");
				else if(vals[x*size+y]<0)
					printf(":-");
				else
					printf(":%d",vals[x*size+y]);
		
			}
			printf(":\n");
		}
		system("pause");
	}
}
