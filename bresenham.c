#include <GL/glut.h>
#include <stdio.h>

float xx1,xx2,yy1,yy2,m;
int xwmax,xwmin,ywmax,ywmin;
int done =0,plot_line =0;
const int top=0x08;
const int bottom=0x04;
const int right=0x02;
const int left = 0x01;

int code1 = 0 ,code2 = 0; //initializing the region codes to find out where the line points lies.


int inside(int code){
	return !code;
}

void swap_points()
{
	int tmpx = xx1;
	xx1=xx2;
	xx2=tmpx;
	int tmpy = yy1;
	yy1=yy2;
	yy2=tmpy;
}
void swap_codes()
{
	int tmpc=code1;
	code1 = code2;
	code2 = code1;
}

void set_bit1()
{
  if(xx1 <  xwmin)
    code1 = code1 | 1;
  if(xx1 > xwmax)
    code1 = code1 | 2;
  if(yy1 < ywmin)
    code1 = code1 | 4;
  if(yy1 > ywmax)
    code1 = code1 | 8;
  
}

void set_bit2()
{
  if(xx2 <  xwmin)
    code2 = code2 | 1;
  if(xx2 > xwmax)
    code2 = code2 | 2;
  if(yy2 < ywmin)
    code2 = code2 | 4;
  if(yy2 > ywmax)
    code2 = code2 | 8;
  
}


void myInit() 
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 500, 0, 500);
}
void draw_pixel(int x, int y) 
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}
void drawline(int startx, int starty,int endx, int endy) 
{
	int dx, dy, i, e;
	int incx, incy, inc1, inc2;
	int x,y;
	dx = endx-startx;
	dy = endy-starty;
	if (dx < 0) dx = -dx;
	if (dy < 0) dy = -dy;
	incx = 1;
	if (endx < startx) incx = -1;
		incy = 1;
	if (endy < starty) incy = -1;
		x = startx; y = starty;
	if (dx > dy) 
	{
		draw_pixel(x, y);
		e = 2 * dy-dx;
		inc1 = 2*(dy-dx);
		inc2 = 2*dy;

		for (i=0; i<dx; i++) 
		{

			if (e >= 0) 
			{
				y += incy;
				e += inc1;
			}
			else
				e += inc2;
			x += incx;
			draw_pixel(x, y);
		}
	} 
	else 
	{
		draw_pixel(x, y);
		e = 2*dx-dy;
		inc1 = 2*(dx-dy);
		inc2 = 2*dx;
		for (i=0; i<dy; i++) 
		{
			if (e >= 0) 
			{
				x += incx;
				e += inc1;
			}
			else
				e += inc2;
			y += incy;
			draw_pixel(x, y);
		}
	}
}
void myDisplay() {
	drawline(xwmin,ywmax,xwmax,ywmax);//top
  	drawline(xwmin,ywmin,xwmax,ywmin);//bottom
  	drawline(xwmin,ywmin,xwmin,ywmax);//left
  	drawline(xwmax,ywmin,xwmax,ywmax);//right boundary
	drawline(xx1,yy1,xx2,yy2);
	glFlush();
}
void check()
{
	//drawline(xx1,yy1,xx2,yy2);
	
	//printf("%d %d ",code1,code2);
	
	while(!done)
	{
		int xnew,ynew;
		set_bit1();
		set_bit2();
		if( !(code1 | code2) )
		{	
			done=1;
			plot_line=1;
			printf("Nothing to clip already inside \n");
			
		}
		else if((code1 & code2))
		{
			//drawline(xx1,yy1,xx2,yy2);	
			printf("Line discarded ! Out of Window \n");
			done=1;
		}
		else 
		{	
			printf("After clipping \n");
			if(inside(code1))
			{
				swap_points();
				swap_codes();
			}
			if(code1 & top )
			{
				if(xx1 !=xx2)
					xx1 += (ywmax-yy1)/m;
				yy1 = ywmax;
				printf("*");
				done = 1;
				plot_line=1;
				//drawline(xwmin,ynew,xx2,yy2);
			}
			else if(code1 & bottom )
			{
				if(xx1 != xx2)
					xx1 +=(ywmin-yy1)/m;
				yy1 = ywmin;
				done=1;
				plot_line=1;
				printf("#" );
				//drawline(xwmin,ynew,xx2,yy2);
			}
			else if(code1 & right )
			{
				yy1 +=(xwmax-xx1)*m;
				xx1=xwmax;
				done=1;
				plot_line=1;
				printf("$" );
				//drawline(xnew,ywmax,xx2,yy2);
			}
			else if(code1 & left )
			{
				yy1 +=(xwmin-xx1)*m;
				xx1=xwmin;
				done=1;
				plot_line=1;
				printf("@" );
				//drawline(xnew,ywmax,xx2,yy2);
			}
			
		}
	}
	

}


void main(int argc, char **argv) {

	printf("Enter line's both co-ordinates \n");
  	printf("----x1 \t y1---- \n");
  	scanf("%f %f",&xx1,&yy1);
  	printf("----x2 \t y2---- \n");
  	scanf("%f %f",&xx2,&yy2);
	printf( "Enter Window's LEFT and RIGHT boundaries:\n");
	scanf("%d %d", &xwmin,&xwmax);
	printf("Enter  Window's BOTTOM and TOP boundaries:\n");
	scanf("%d %d", &ywmin, &ywmax);
	if(xx2!=xx1)
	m=(yy2-yy1)/(xx2-xx1);
	else
		printf("m goes to ∞\n");
	check();
	if(plot_line)
	{	glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
		glutInitWindowSize(1000, 1000);
		glutInitWindowPosition(0, 0);
		glutCreateWindow("Cohen Sutherland Line Clip Algo");
		glutDisplayFunc(myDisplay);
		myInit();
		glutMainLoop();
		
	}
	
}