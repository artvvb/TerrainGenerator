#ifndef __POINT_H__
#define __POINT_H__

#include <stdlib.h> // used for point::rand_init()
#include <time.h>	// used for rand() initialization only right now
#include <stdio.h>  // used for testing display
#include <string.h> // used for testing display
#include <math.h>   // used for trig in point::rotate() and sqrt, pow in point::magnitude()

#define X 0	//index macro primarily for point::dim()
#define Y 1	//index macro primarily for point::dim()
#define PI 3.14159265 //for use in rotate, more exact value means more exact rotate exec

class point	{
	//includes only such functions as relate to ONE point, though >1 point have prototypes in this file too
protected:
	double location[2];
	int content;
public:
	void update_cont (int cont)
	{	content = cont; return;	}
	int get_cont (void)
	{return content;}
	void init (double x, double y);			//initializes location to the input values
	void operator= (point other);			//initializes location to the location of other
	double where_at (int i);				//returns the value of location at index [i]
	double magnitude (void);				//returns the magnitude of (point as a vector) as a point
	point operator+ (point other);			//returns a point with location initialized to the sum of each of *this's and other's location
	point operator- (point other);			//returns a point with location initialized to the difference between each of *this's and other's location (equivalent to *t + (o * -1))
	point operator* (double scalar);		//returns a point with location initialized to the product of each of *this's location and the scalar
	point operator/ (double scalar);		//returns a point with location initialized to the quotient of each of *this's location and the scalar (equivalent to *t * (1 / s))
	int operator== (point other);			//returns one if each of the *this's and others's location in the same index position are the same
	char *printable (void);					//returns a formatted string to allow the location of point to be printed to the command line in the form (X,Y), '\n' is not included
};
#endif