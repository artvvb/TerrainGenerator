#include "generate_noise.h"
#include <time.h>
int main (void)//test-display function
{	int n=6,ni=1;
	clock_t one;
	char selection;int valid;
	srand((unsigned int)time(NULL));//seed rand with time, small %'s only
	do	{
		one=clock();
		if(fractal_noise(n,ni)==1)return 0;
		double avg=height_average();
		printf("runtime:%f\n", (clock()-one)/CLOCKS_PER_SEC);//so far haven't seen anything above 0.0000 sec
		printf("\n");
		for(int x=0;x<size;x++)
		{	printf("  ");
			for(int y=0;y<size;y++)
			{	if(val_at(x,y)>=avg)printf(":M");
				if(val_at(x,y)< avg)printf(":.");
			}
			printf(":\n");
		}
		do	{
			printf("\nh for options: ");
			selection=getc(stdin);
			if(selection=='h')printf("'q':[quit]\n'o':[change options]\n'g':[generate new map]\n");
			if(selection=='o')
			{	printf("total number of fractal iterations:");scanf("%d",&n);//NOT CHECKED, not sure what would happen if <=0
				printf("number of purely random iterations:");scanf("%d",&ni);//NOT CHECKED, will /0 if ni<0
			}
			if(selection!='q'&&selection!='o'&&selection!='g')valid=1;
		}	while(!valid);
	}	while(selection!='q');
}