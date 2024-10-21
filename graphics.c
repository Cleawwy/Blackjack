/*
A simple example of using the gfx library.
CSE 20211
9/7/2011
by Prof. Thain
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gfx.h"

int main()
{
	int r,g,b,x,y,flag=0;
	int ysize = 600;
	int xsize = 800;

	char c;

	srand(time(NULL));

	// Open a new window for drawing.
	gfx_open(xsize,ysize,"Example Bouncing Ball Program");

	// Set the current drawing color to green.
	gfx_color(255,0,0);

	x=xsize/2;
	y=30;	

	while(1)
	{
		if ( gfx_event_waiting())
		{
			break;
		}
		else
		{
			//printf("x=%d y=%d flag= %d \n",x,y,flag);

			if(y > ysize-30 || y <= 30)
				flag=!flag;

			gfx_circle(x,y,30);
			gfx_fillcircle(x,y,30);
			gfx_flush();

			usleep(25000);
			gfx_clear();

			if (flag)
				y=y+5;
			else
				y=y-5;

		}
	}
		

	return 0;
}