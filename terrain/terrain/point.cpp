#include "point.h"
void point::init (double x, double y)
{	location[X] = x;
	location[Y] = y;
	return;
}
void point::operator= (point other)
{	location[X] = other.location[X];
	location[Y] = other.location[Y];
	return;
}
double point::where_at (int i)
{	return location[i];
}
double point::magnitude (void)
{	return sqrt( pow(location[X], 2) + pow(location[Y], 2) );
}
point point::operator+ (point other)
{	point return_val;
	return_val.init( location[X] + other.where_at(X), location[Y] + other.where_at(Y) );
	return return_val;
}
point point::operator- (point other)
{	return *this + (other * -1);
}
point point::operator* (double scalar)
{	point return_val;
	return_val.init( location[X] * scalar, location[Y] * scalar );
	return return_val;
}
point point::operator/ (double scalar)
{	point return_val;
	return_val.init( location[X] / scalar, location[Y] / scalar );
	return return_val;
}
int point::operator== (point other)
{	if (other.where_at(X) == this->location[X]&& other.where_at(Y) == this->location[Y])
		return 1;
	return 0;
}
char *point::printable (void)
{	char *return_val = (char*) malloc (((2 + 1) * 4 + 2) * sizeof(char));
	char *temp = (char*) malloc (4 * sizeof(char));
	return_val[0] = '\0';
	strcat(return_val, "(");
	for (int i = 0; i < 2; i++)
	{	//if (location[i] == 0.0) location[i] = 0.0;//elims -0.0, or not...
		sprintf(temp, "%.2f", location[i]);
		strcat(return_val, temp);
		if (i < 2 - 1) strcat(return_val, ",");
	}
	strcat(return_val, ")");
	return return_val;
}