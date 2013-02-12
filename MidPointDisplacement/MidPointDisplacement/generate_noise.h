//ARTHUR BROWN
/*Algorithm as described on wikipedia as Diamond-square
 *initial, overly complex implementation simplified
 *	with help from http://www.bluh.org/code-the-diamond-square-algorithm/
 *meant to be a header for use in other projects (should be kept as a single file)
 */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define RAND (frand()*scale)
#define BASE 'a'//makes output ascii
#define WRAPAROUND 0
static double*map=NULL,scale;static unsigned int size;

double frand(void)
{	return 2*(rand()/(double)RAND_MAX)-1; }//-1.0 to 1.0
//frand fails
void set_at (int x,int y,double val)
{	map[size*(x%size)+(y%size)]=val;
	return;
}
double val_at(int x,int y)
{	return map[size*(x%size)+(y%size)]; }//enables WRAPAROUND
void square_seed(int step,int x,int y)
{	int half=step/2,count=4,
		xa=x+half,xb=x-half,xc=x+half,xd=x-half,
		ya=y+half,yb=y+half,yc=y-half,yd=y-half;
	double a=0,b=0,c=0,d=0;
	if(WRAPAROUND)
	{	if(xa>=size)xa-=size;
		if(xb<0)xb+=size;
		if(xc>=size)xc-=size;
		if(xd<0)xd+=size;
		if(ya>=size)ya-=size;
		if(yb>=size)yb-=size;
		if(yc<0)yc+=size;
		if(yd<0)yd+=size;	  }
	if(xa<size&&ya<size){a=val_at(xa,ya);count++;}//printf("(%d,%d):",xa,ya);}
	if(xb>=0  &&yb<size){b=val_at(xb,yb);count++;}//printf("(%d,%d):",xb,yb);}
	if(xc<size&&yc>=0  ){c=val_at(xc,yc);count++;}//printf("(%d,%d):",xc,yc);}
	if(xd>=0  &&yd>=0  ){d=val_at(xd,yd);count++;}//printf("(%d,%d):",xd,yd);}
	set_at(x,y,(a+b+c+d)/(double)count+RAND);//printf("%.2f\n", val_at(x,y));
	return;
}
void diamond_seed (int step,int x,int y)
{	int half=step/2,count=0,
		xa=x-half,xb=x+half,yc=y-half,yd=y+half;
	double a=0,b=0,c=0,d=0;
	if(WRAPAROUND)
	{	if(xa<0)	xa+=size;//hardcoded WRAPAROUND
		if(xb>=size)xb-=size;//softcode with ?: operators?
		if(yc<0)	yc+=size;
		if(yd>=size)yd-=size; }
	if(xa>=0  ){a=val_at(xa,y);count++;}//printf("(%d,%d):",xa,y);}
	if(xb<size){b=val_at(xb,y);count++;}//printf("(%d,%d):",xb,y);}
	if(yc>=0  ){c=val_at(x,yc);count++;}//printf("(%d,%d):",x,yc);}
	if(yd<size){d=val_at(x,yd);count++;}//printf("(%d,%d):",x,yd);}
	set_at(x,y,(a+b+c+d)/(double)count+RAND);//printf("%.2f\n",val_at(x,y));
	return;
}
int fractal_noise(int n,int ni)//initialization
{	if (map!=NULL)free(map);//in final version, should pass pointer to data and not free, assume that outside will free when finished with
	size=(int)pow(2,(double)n)+!WRAPAROUND;//given n=4 and wrapping, size=16
	int step=(size-!WRAPAROUND)/(int)pow(2,(double)ni);//give n=4, ni=2, step=16/4=4, so, two iters will be fully randomized, making sharper terrain
	scale=1.0;
	map=(double*)malloc(size*size*sizeof(double));//square! (maybe do rect later)
	if(NULL==map)return 1;//fail state, can't fractal a null-ptr
	for(int x=0;x<size;x+=step)
		for(int y=0;y<size;y+=step)
		{	//printf("IN(%d,%d)",x,y);
			set_at(x,y,frand());
			//printf(":%.2f\n", val_at(x,y));
		}
	while(step>1)
	{	int half=step/2;
		//printf("RAND*:%.2lf:step_size:%d:\n",scale,step);
		for (int x=half;x<size;x+=step)//where 'set' grid is NxN, 'diamond' grid is (N-1)x(N-1)
			for (int y=half;y<size;y+=step)
			{	//printf("SQ:[%d,%d]->",x,y);
				square_seed(step,x,y);
			}
		for(int x=0;x<size;x+=step)
			for(int y=0;y<size;y+=step)
			{	//printf("DS:[%d,%d]->",x,y+half);
				diamond_seed(step,x,y+half);
				//printf("DS:[%d,%d]->",x+half,y);
				diamond_seed(step,x+half,y);
			}
		step/=2;
		scale/=2.0;//probably could include fractal zoom as an input (function of n?)
	}
	return 0;
}
double height_average(void)
{	double sum=0;int num=0;
	for (int i=0;i<size*size;i++)
	{	sum+=map[i];num++; }
	return sum/num;
}//only used in main currently, thinking of using stdev and avg for scaling to get height zones