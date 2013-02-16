#include "Noise.h"
static int wraparound;
static double *temp, scale;
static unsigned int step, size;
int call_count=0;
double frand(void) {
	return scale*(rand()/(double)RAND_MAX);
}// [0,1.0]
static void set_at (int x,int y,int val) {
	temp[size*(x%size)+(y%size)]=val; return;
}
static double val_at(int x,int y) {
	return temp[size*(x)+(y)];
}
static void square_seed(int x,int y) {
	int half=step/2,count=0,
		xa=x+half,xb=x-half,xc=x+half,xd=x-half,
		ya=y+half,yb=y+half,yc=y-half,yd=y-half;
	double a=0,b=0,c=0,d=0;
	if(wraparound) {//enables WRAPAROUND
		if(xa>=size)xa-=size;
		if(xb<0)xb+=size;
		if(xc>=size)xc-=size;
		if(xd<0)xd+=size;
		if(ya>=size)ya-=size;
		if(yb>=size)yb-=size;
		if(yc<0)yc+=size;
		if(yd<0)yd+=size;
	}
	if(xa<size&&ya<size) {
		a=val_at(xa,ya);count++;if(DISP)printf("(%d,%d):",xa,ya);
	}
	if(xb>=0  &&yb<size) {
		b=val_at(xb,yb);count++;if(DISP)printf("(%d,%d):",xb,yb);
	}
	if(xc<size&&yc>=0  ) {
		c=val_at(xc,yc);count++;if(DISP)printf("(%d,%d):",xc,yc);
	}
	if(xd>=0  &&yd>=0  ) {
		d=val_at(xd,yd);count++;if(DISP)printf("(%d,%d):",xd,yd);
	}
	set_at(x,y,(a+b+c+d)/(double)count+frand());
	if(DISP)printf("%.2f\n", val_at(x,y));
	return;
}
static void diamond_seed (int x,int y)
{	int half=step/2,count=0,
		xa=x-half,xb=x+half,yc=y-half,yd=y+half;
	double a=0,b=0,c=0,d=0;
	if(wraparound)
	{	if(xa<0)	xa+=size;//hardcoded WRAPAROUND
		if(xb>=size)xb-=size;//softcode with ?: operators?
		if(yc<0)	yc+=size;
		if(yd>=size)yd-=size; }
	if(xa>=0  ) {
		a=val_at(xa,y);count++;if(DISP)printf("(%d,%d):",xa,y);
	}
	if(xb<size) {
		b=val_at(xb,y);count++;if(DISP)printf("(%d,%d):",xb,y);
	}
	if(yc>=0  ) {
		c=val_at(x,yc);count++;if(DISP)printf("(%d,%d):",x,yc);
	}
	if(yd<size) {
		d=val_at(x,yd);count++;if(DISP)printf("(%d,%d):",x,yd);
	}
	set_at(x,y,(a+b+c+d)/(double)count+frand());
	if(DISP)printf("%.2f\n",val_at(x,y));
	return;
}
void fractal_noise (int *output,int n) {
	call_count=1; wraparound=0;
	scale=8;
	size=(int)pow(2,(double)n);
	step=(int)pow(2,(double)n-1);
	//printf("PREFREE\n");
	//if(temp!=NULL)free(temp);
	//printf("FREE\n");
	if(temp==NULL)temp=(double*)malloc(size*size*sizeof(double));//square! (maybe do rect later)
	if(NULL==temp)return;//fail state, can't fractal a null-ptr
	for(int x=0;x<size;x+=step)
		for(int y=0;y<size;y+=step)
		{	if(DISP)printf("%d: IN(%d,%d)",call_count++,x,y);
			set_at(x,y,frand());
			if(DISP)printf(":%.2f\n", val_at(x,y));
		}
	while(step>1)
	{	int half=step/2;
		for (int x=half;x<size;x+=step)//where 'set' grid is NxN, 'diamond' grid is (N-1)x(N-1)
			for (int y=half;y<size;y+=step)
			{	if(DISP)printf("%d: SQ:[%d,%d]->",call_count++,x,y);
				square_seed(x,y);
			}
		for(int x=0;x<size;x+=step)
			for(int y=0;y<size;y+=step)
			{	if(DISP)printf("%d: DS:[%d,%d]->",call_count++,x,y+half);
				diamond_seed(x,y+half);
				if(DISP)printf("%d: DS:[%d,%d]->",call_count++,x+half,y);
				diamond_seed(x+half,y);
			}
		step/=2;
		scale/=(scale==1?1:2);//probably could include fractal zoom as an input (function of n?)
	}
	for(int i=0;i<size*size;i++)
		output[i]=(int)temp[i];
	free(temp);temp=NULL;
	return;
}