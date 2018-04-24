// jasprg5.cpp.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include<stdio.h>
#include<GL/glut.h>
float xmin=50,ymin=50,xmax=100,ymax=100;
float xvmin=200,yvmin=200,xvmax=400,yvmax=400;
int RIGHT=8,LEFT=2,TOP=4,BOTTOM=1;
float sx,sy,vx1,vy1,vx2,vy2;
float x1,y1,x2,y2,x3,y3,x4,y4,x5,y5,x6,y6;
int compute(float x,float y)
{
int code=0;
if(y>ymax)
code=TOP;
else if(y<ymin)
code=BOTTOM;
if(x>xmax)
code=RIGHT;
else if(x<xmin)
code=LEFT;
return code;
}
void cohen(float x1,float y1,float x2,float y2)
{
float x,y;
int accept=0,done=0,code_p,code_q,code;
code_p=compute(x1,y1);
code_q=compute(x2,y2);
do
{
if(!(code_p|code_q))
{
accept=1;
done=1;
}
else if(code_p & code_q)
done=1;
else
{
code=code_p ? code_p : code_q;
if(code & TOP)
{
x=x1+(x2-x1)*(ymax-y1)/(y2-y1);
y=ymax;
}
else if(code & BOTTOM)
{
x=x1+(x2-x1)*(ymin-y1)/(y2-y1);
y=ymin;
}
else if(code & RIGHT)
{
y=y1+(y2-y1)*(xmax-x1)/(x2-x1);
x=xmax;
}
else
{
y=y1+(y2-y1)*(xmin-x1)/(x2-x1);
x=xmin;
}
if(code==code_p)
{
x1=x;
y1=y;
code_p=compute(x1,y1);
}
else
{
x2=x;
y2=y;
code_q=compute(x2,y2);
}
}
}
while(!done);
if(accept)
{
sx=(xvmax-xvmin)/(xmax-xmin);
sy=(yvmax-yvmin)/(ymax-ymin);
vx1=xvmin+(x1-xmin)*sx;
vy1=xvmin+(y1-ymin)*sy;
vx2=xvmin+(x2-xmin)*sx;
vy2=xvmin+(y2-ymin)*sy;
}
}
void display()
{

//int i;
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1,1,1);
glLineWidth(2);
glBegin(GL_LINES);
glVertex2d(x1,y1);
glVertex2d(x2,y2);
glVertex2d(x3,y3);
glVertex2d(x4,y4);
glVertex2d(x5,y5);
glVertex2d(x6,y6);
glEnd();

glColor3f(1,1,1);
glBegin(GL_LINE_LOOP);
glVertex2f(xmin,ymin);
glVertex2f(xmax,ymin);
glVertex2f(xmax,ymax);
glVertex2f(xmin,ymax);
glEnd();

glColor3f(1,1,1);
glBegin(GL_LINE_LOOP);
glVertex2f(xvmin,yvmin);
glVertex2f(xvmax,yvmin);
glVertex2f(xvmax,yvmax);
glVertex2f(xvmin,yvmax);
glEnd();

cohen(x1,y1,x2,y2);
glColor3f(1,1,1);
glBegin(GL_LINES);
glVertex2d(vx1,vy1);
glVertex2d(vx2,vy2);
glEnd();

cohen(x3,y3,x4,y4);
glColor3f(1,1,1);
glBegin(GL_LINES);
glVertex2d(vx1,vy1);
glVertex2d(vx2,vy2);
glEnd();

cohen(x5,y5,x6,y6);
glColor3f(1,1,1);
glBegin(GL_LINES);
glVertex2d(vx1,vy1);
glVertex2d(vx2,vy2);
glEnd();

glFlush();

}
void init()
{
glClearColor(0,0,0,1);
gluOrtho2D(0,500,0,500);
}
void main()
{
printf("\n Enter the first 4 points\n");
scanf("%f%f%f%f",&x1,&y1,&x2,&y2);
printf("\n Enter the next 4 points\n");
scanf("%f%f%f%f",&x3,&y3,&x4,&y4);
printf("\n Enter the last 4 points\n");
scanf("%f%f%f%f",&x5,&y5,&x6,&y6);

glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowSize(500,500);
glutCreateWindow("Cohen Sutherland");

glutDisplayFunc(display);

init();
glutMainLoop();

}

