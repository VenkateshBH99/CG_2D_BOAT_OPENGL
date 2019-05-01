
//main.cpp
//  Boat
//
//  Created by Venkatesh B h on 4/1/19.
//  Copyright © 2019 Apple Inc. All rights reserved.
//
#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <cstring>
#include <string.h>
#include <iostream>
#include <unistd.h>

using namespace std;

GLint window;
GLfloat x[100],y[100];
int view1=0;
int n;
int lam=2;
int r=100,xc,yc;
int a1,b1,xc1,yc1,ind=0;
float shift = 0,s1=0;
int clip1=0;
float xmin=250;
float ymin=320;
float xmax=700;
float ymax=800;
int term=0;
int rot=0;
int rot1=0;
int view=0;
int que=0;
double angle,angleRad=0;
char name3[]="PROJECT:  2D Project";
float xd1,yd1,xd2,yd2;
void display(void);
void draw_line(int x11,int y11,int x22,int y22);
void dotted_line(int x11,int y11,int x22,int y22);
void dash_line(int x11,int y11,int x22,int y22);
// a variable used to move the boat right and left

void init(void)
{
    glClearColor(0.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1000, 0.0, 1000);
    glutPostRedisplay();
}

void draw_pixel(int xx,int yy)
{
    glPointSize(1.0);
    glBegin(GL_POINTS);
    glVertex2i(xx, yy);
    glEnd();
}

void display_string(int x, int y, char *string, int font)
{
    int len,i;
    glColor3f(0.0,0.0,0.0);
    glRasterPos2f(x, y);
    len = (int) strlen(string);
    for (i = 0; i < len; i++)
    {
        if(font==1)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
        if(font==2)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,string[i]);
        if(font==3)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,string[i]);
        if(font==4)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,string[i]);
    }
}

void display1(void)
{
    glClearColor(1.0 ,1.0 ,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    display_string(190,900,"National Institute of Technology Karnataka, Surathkal",1);
    display_string(300,850,name3,1);
    display_string(10,750,"Press 'c' for dotted clipping window",2);
    display_string(10,700,"Press 'C' for dash clipping window",2);
    display_string(10,650,"Press 'n' for normal clipping window",2);
    display_string(10,600,"Press 'q' for  not clipping window",2);
    display_string(10,550,"Press 'a,w,d,s' are movement key for clipping window",2);
    display_string(10,500,"Press 'm' for segmented shift of boat",2);
    display_string(10,450,"Press 'M' for reverse the segment effect",2);
    display_string(10,400,"Press 'z/Z' for Scaling of the Sun",2);
    display_string(10,350,"Press 'r/R' for Rotation",2);
    display_string(10,300,"Press standard arrow key for boat and sun movement",2);
    display_string(10,250,"press 'b' For Back to commands",2);
    display_string(10,200,"ESCAPE TO EXIT",2);

    display_string(250,150+30,"PRESS SPACE BAR TO ENTER",2);
    display_string(500,700,"Done by:",2);
    display_string(500,650,"Venkatesh B H (17IT248)",2);
    glutPostRedisplay();
    glutSwapBuffers();

}

void draw_pixelD(int xx,int yy)
{
    glPointSize(3.0);
    glBegin(GL_POINTS);
    glVertex2i(xx, yy);
    glEnd();
}

double round(double d)
{
    return floor(d + 0.5);
}

int code(float x,float y)
{
    int c=0;
    if(y>ymax)c=8;
    if(y<ymin)c=4;
    if(x>xmax)c=c|2;
    if(x<xmin)c=c|1;
    return c;
}

void cohen_Line(float x1,float y1,float x2,float y2)
{
    int c1=code(x1,y1);
    int c2=code(x2,y2);
    float m=(y2-y1)/(x2-x1);
    while((c1|c2)>0)
    {
        if((c1 & c2)>0)
        {
            xd2=xd1;
            yd2=yd1;
            break;
        }

        float xi=x1;float yi=y1;
        int c=c1;
        if(c==0)
        {
            c=c2;
            xi=x2;
            yi=y2;
        }
        float x,y;
        if((c & 8)>0)
        {
            y=ymax;
            x=xi+ 1.0/m*(ymax-yi);
        }
        else
            if((c & 4)>0)
            {
                y=ymin;
                x=xi+1.0/m*(ymin-yi);
            }
            else
                if((c & 2)>0)
                {
                    x=xmax;
                    y=yi+m*(xmax-xi);
                }
                else
                    if((c & 1)>0)
                    {
                        x=xmin;
                        y=yi+m*(xmin-xi);
                    }

        if(c==c1)
        {
            xd1=x;
            yd1=y;
            c1=code(xd1,yd1);
        }

        if(c==c2)
        {
            xd2=x;
            yd2=y;
            c2=code(xd2,yd2);
        }
    }
    display();
}

void display()
{
    if(clip1==0)
    {
    dotted_line(xmin, ymin, xmin, ymax);
    dotted_line(xmin, ymax, xmax, ymax);
    dotted_line(xmax, ymax, xmax, ymin);
    dotted_line(xmax, ymin, xmin, ymin);
    }
    else if(clip1==1)
    {
        dash_line(xmin, ymin, xmin, ymax);
        dash_line(xmin, ymax, xmax, ymax);
        dash_line(xmax, ymax, xmax, ymin);
        dash_line(xmax, ymin, xmin, ymin);
    }
    else if(clip1==2)
    {
    glBegin(GL_LINE_LOOP);
    glVertex2i(xmin,ymin);
    glVertex2i(xmin,ymax);
    glVertex2i(xmax,ymax);
    glVertex2i(xmax,ymin);
    glEnd();
    }
    glBegin(GL_LINES);
    glVertex2i(xd1,yd1);
    glVertex2i(xd2,yd2);
    glEnd();
}

void edgedetect(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2,int *le,int *re)
{
    float mx,x,temp;
    int i,k;
    if((y2-y1)<0)
    {
        temp=x1;
        x1=x2;
        x2=temp;
        temp=y1;
        y1=y2;
        y2=temp;
    }
    if((y2-y1)!=0)
        mx=(x2-x1)/(y2-y1);
    else
        mx=x2-x1;
    x=x1;
    for(i=(int)y1+1;i<(int)y2;i++)
    {
        int t=0;
        if(x<(float)le[i])
        {   if(le[i]!=1000){
               le[i]=(int)x;
               if(term==1){
                xd1=le[i];yd1=i;xd2=re[i];yd2=i;
          cohen_Line(le[i],i,re[i],i);
               }
               else
               draw_line(le[i],i,re[i],i);
               le[i]=1000;
               re[i]=0;
               t=1;
             }
             else
            le[i]=(int)x;
        }
        if(t==0)
        if(x>(float)re[i])
        {    if(re[i]!=0){
               re[i]=(int)x;
               if(term==1){
                xd1=le[i];yd1=i;xd2=re[i];yd2=i;
          cohen_Line(le[i],i,re[i],i);
               }
               else
               draw_line(le[i],i,re[i],i);
               le[i]=1000;
               re[i]=0;

             }
             else
            re[i]=(int)x;
        }
        x+=mx;
    }
}

void scanfill(GLfloat *x,GLfloat *y)
{
    int le[1000],re[1000];
    int i,j;
    for(i=0;i<1000;i++)
    {
        le[i]=1000;
        re[i]=0;
    }

    for(int k=0;k<n-1;k++)
    {
        edgedetect(x[k],y[k],x[k+1],y[k+1],le,re);

    }
    edgedetect(x[n-1],y[n-1],x[0],y[0],le,re);

    /*for(j=0;j<500;j++)
    {
     if(le[j]<=re[j])
        if(term==1)
        {
             xd1=le[j]+1;yd1=j;xd2=re[j]-1;yd2=j;
             cohen_Line(le[j]+1, j, re[j]-1, j);
        }
        else
            draw_line(le[j]+1, j, re[j]-1, j);
    }*/
}

void draw_line(int x11,int y11,int x22,int y22)
{
    //glClearColor(1.0, 0.0, 0.0, 1.0);
    int incx,incy,inc1,inc2;
    int dx,dy,a,b,e,i;
    dx=x22-x11;
    dy=y22-y11;
    if(dx<0) dx=-dx;
    if(dy<0) dy=-dy;
    incx=1;
    incy=1;
    if(x11>x22) incx=-incx;
    if(y11>y22) incy=-incy;
    a=x11;b=y11;
    draw_pixel(a, b);
    if(dx>dy)
    {
        e=2*dy-dx;
        inc1=2*(dy-dx);
        inc2=2*dy;
        for(i=0;i<dx;i++)
        {
            if(e>=0)
            {
                b+=incy;
                e+=inc2;
            }
            else
                e+=inc1;
            a+=incx;
            draw_pixel(a, b);
        }
    }
    else
    {
        e=2*dx-dy;
        inc1=2*(dx-dy);
        inc2=2*dx;
        for(i=0;i<dy;i++)
        {
            if(e>=0)
            {
                a+=incx;
                e+=inc2;
            }
            else
                e+=inc1;
            b+=incy;
            draw_pixel(a, b);
        }
    }
}

void dotted_line(int x11,int y11,int x22,int y22)
{
    //glClearColor(1.0, 0.0, 0.0, 1.0);
    int incx,incy,inc1,inc2;
    int dx,dy,a,b,e,i;
    dx=x22-x11;
    dy=y22-y11;
    if(dx<0)
        dx=-dx;
    if(dy<0)
    dy=-dy;
    incx=1;
    incy=1;
    if(x11>x22)
        incx=-incx;
    if(y11>y22)
        incy=-incy;
    a=x11;b=y11;
    draw_pixelD(a, b);
    if(dx>dy)
    {
        e=2*dy-dx;
        inc1=2*(dy-dx);
        inc2=2*dy;
        int flag=5;
        for(i=0;i<dx;i++)
        {
            if(e>=0)
            {
                b+=incy;
                e+=inc2;
            }
            else
                e+=inc1;
            a+=incx;
            if(flag<0)
            {
            draw_pixelD(a, b);
                flag=5;
            }
            else
                flag--;
        }
    }
    else
    {
        e=2*dx-dy;
        inc1=2*(dx-dy);
        inc2=2*dx;
        int flag=5;
        for(i=0;i<dy;i++)
        {
            if(e>=0)
            {
                a+=incx;
                e+=inc2;
            }
            else
                e+=inc1;
            b+=incy;
            if(flag<0)
            {
            draw_pixelD(a, b);
                flag=5;
            }
            else
            {
                flag--;
            }
        }
    }
}

void dash_line(int x11,int y11,int x22,int y22)
{
    //glClearColor(1.0, 0.0, 0.0, 1.0);
    int incx,incy,inc1,inc2;
    int dx,dy,a,b,e,i;
    dx=x22-x11;
    dy=y22-y11;
    if(dx<0)
        dx=-dx;
    if(dy<0)
        dy=-dy;
    incx=1;
    incy=1;
    if(x11>x22)
        incx=-incx;
    if(y11>y22)
        incy=-incy;
    a=x11;b=y11;
    draw_pixelD(a, b);
    if(dx>dy)
    {
        e=2*dy-dx;
        inc1=2*(dy-dx);
        inc2=2*dy;
        int flag=10;
        int c=0;
        for(i=0;i<dx;i++)
        {
            if(e>=0)
            {
                b+=incy;
                e+=inc2;
            }
            else
                e+=inc1;
            a+=incx;
            if(flag>0)
            {
                draw_pixelD(a, b);
                flag--;
            }
            else
            {
                if(c==10)
                {
                    flag=10;
                    c=0;
                }
                else
                    c+=1;
            }
        }
    }
    else
    {
        e=2*dx-dy;
        inc1=2*(dx-dy);
        inc2=2*dx;
        int flag=5;
        int c=0;
        for(i=0;i<dy;i++)
        {
            if(e>=0)
            {
                a+=incx;
                e+=inc2;
            }
            else
                e+=inc1;
            b+=incy;
            if(flag>0)
            {
                draw_pixelD(a, b);
                flag--;
            }
            else
            {
                if(c==10)
                {
                    c=0;
                    flag=10;
                }
                else
                    c++;
            }
        }
    }
}

void points(int xx,int yy)
{
    if(term==1)
    {
        xd1=xx+xc1;yd1= yy+yc1;xd2=-xx+xc1;yd2=yy+yc1;
        cohen_Line(xx+xc1, yy+yc1, -xx+xc1, yy+yc1);
        xd1=xx+xc1;yd1= -yy+yc1;xd2=-xx+xc1;yd2=-yy+yc1;
        cohen_Line(xx+xc1, -yy+yc1, -xx+xc1, -yy+yc1);
    }
    else
    {
    draw_line(xx+xc1, yy+yc1, -xx+xc1, yy+yc1);
    draw_line(xx+xc1, -yy+yc1, -xx+xc1, -yy+yc1);
    }
}

void draw_circle()
{
    float h=5/4-r;
    int xx=0,yy=r;
    draw_pixel(xx+xc, yy+yc);
    while(yy>xx)
    {
        if(h<0)
        {
            xx++;
            h+=2*xx+3;
        }
        else
        {
            xx++;
            yy--;
            h+=2*xx-2*yy+5;
        }
        if(term==1)
        {
            xd1=xx+xc;yd1=yy+yc;xd2=-xx+xc;yd2=yy+yc;
            cohen_Line(xx+xc, yy+yc, -xx+xc, yy+yc);
            xd1=yy+xc;yd1=xx+yc;xd2=-yy+xc;yd2=xx+yc;
            cohen_Line(yy+xc, xx+yc, -yy+xc, xx+yc);
            xd1=yy+xc;yd1=-xx+yc;xd2=-yy+xc;yd2=-xx+yc;
            cohen_Line(yy+xc, -xx+yc, -yy+xc, -xx+yc);
            xd1=xx+xc;yd1=-yy+yc;xd2=-xx+xc;yd2=-yy+yc;
            cohen_Line(xx+xc, -yy+yc, -xx+xc, -yy+yc);
        }
        else
        {
            draw_line(xx+xc, yy+yc, -xx+xc, yy+yc);
            draw_line(yy+xc, xx+yc, -yy+xc, xx+yc);
            draw_line(yy+xc, -xx+yc, -yy+xc, -xx+yc);
            draw_line(xx+xc, -yy+yc, -xx+xc, -yy+yc);
        }

    }
    if(term==1)
    {
        xd1=r+xc;yd1= yc;xd2=-r+xc;yd2=yc;
        cohen_Line(r+xc, yc, -r+xc, yc);
    }
    else
        draw_line(r+xc, yc, -r+xc, yc);
}

void draw_ellipse()
{
    double d2;
    int x=0,y=b1;
    int sa=a1*a1;
    int sb=b1*b1;
    double d1=sb-sa*b1+0.25*sa;
    if(rot==1)
    {
        points(round(x*cos(angleRad)-y*sin(angleRad)), round(x*sin(angleRad)+y*cos(angleRad)));
    }
    else
        points(x, y);
    while(sa*(y-0.5)>sb*(x+1))
    {
        if(d1<0)
        {
            d1+=sb*((x<<1)+3);
        }
        else
        {
            d1+=sb*((x<<1)+3)+sa*(-(y<<1)+2);
            y--;
        }
        x++;
        if(rot==1)
        {
            points(round(x*cos(angleRad)-y*sin(angleRad)), round(x*sin(angleRad)+y*cos(angleRad)));
        }
        else
            points(x, y);
    }
    d2=sb*(x)*(x)+sa*(y)*(y)-sa*sb;
    while(y>0)
    {
        if(d2<0)
        {
            d2+=sb*((x<<1)+2)+sa*(-(y<<1)+3);
            x++;
        }
        else
        {
            d2+=sa*(-(y<<1)+3);
        }
        y--;
        if(rot==1)
        {
            points(round(x*cos(angleRad)-y*sin(angleRad)), round(x*sin(angleRad)+y*cos(angleRad)));
        }
        else
            points(x, y);
    }
}

void hyperbola()
{
    double d2;
    int x=a1,y=0;
    int sa=a1*a1;
    int sb=b1*b1;
    int aa2=2*sa;
    int bb2=2*sb;
    double d1=a1*sb+sb/4-sa;
    double fx=bb2*a1,fy=0;
    if(rot==1)
    {
        points(round(x*cos(angleRad)-y*sin(angleRad)), round(x*sin(angleRad)+y*cos(angleRad)));
    }
    else
    points(x, y);
    while(fx>fy && x<=500)
    {
        y++;
        fy+=aa2;
        if(d1>=0)
        {
            d1-=sa*(2*y+1);
        }
        else
        {
            x++;
            fx+=bb2;
            d1+=bb2*x-sa*(2*y+1);
        }

        if(rot==1)
        {
            points(round(x*cos(angleRad)-y*sin(angleRad)), round(x*sin(angleRad)+y*cos(angleRad)));
        }
        else
            points(x, y);
    }
    d2=sb*(x+1)*(x+1)-sa*(y+0.5)*(y+0.5)-sa*sb;
    while(x<=500)
    {
        x++;
        if(d2<0)
        {
            d2+=sb*(1+2*x);

        }
        else
        {
            y++;
            d2+=sb*(1+2*x);
        }
        if(rot==1)
        {
            points(round(x*cos(angleRad)-y*sin(angleRad)), round(x*sin(angleRad)+y*cos(angleRad)));
        }
        else
            points(x, y);
    }
}

void drawing_moving_boats()
{
    // we want to draw moving boat
    glClear(GL_COLOR_BUFFER_BIT);
    if(view==0)
    {
        display1();
    }
    else
    {
    glClearColor(0.0, 1.0, 1.0, 1.0);
    glColor3f(0.6, 0.2, 0.3);
    a1=100;
    b1=50;
    xc1=500;yc1=600+s1;
    hyperbola();

    glColor3f(1, 0.5, 0.0);
    r=r;
    xc=500;yc=600+s1;
    draw_circle();

    glColor3f(0.93,0.28,0.16);
    for(int g=0;g<1000;g+=150)
    {
        if(rot1==1) rot=0;
        a1=100;
        b1=300;
        xc1=110+g;yc1=100;
        draw_ellipse();
    }
    if(rot1==1)
        rot=1;

    glColor3f(0.0, 0.3, 1);
    if(term==1)
    {
    xd1=1;yd1= 0;xd2=1;yd2=180;
    cohen_Line(1, 0, 1, 180);
    xd1=1;yd1= 180;xd2=1000;yd2=180;
    cohen_Line(1, 180, 1000, 180);
    xd1=1000;yd1= 180;xd2=1000;yd2=0;
    cohen_Line(1000, 180, 1000, 0);
    xd1=1000;yd1= 0;xd2=1;yd2=0;
    cohen_Line(1000, 0, 1, 0);
    }
    else
    {
    draw_line(1, 0, 1, 180);
    draw_line(1, 180, 1000, 180);
    draw_line(1000, 180, 1000, 0);
    draw_line(1000, 0, 1, 0);}
    x[0]=1;y[0]=0;
    x[1]=1;y[1]=180;
    x[2]=1000;y[2]=180;
    x[3]=1000;y[3]=0;
    n=4;
    scanfill(x,y);
    memset(x, 0, sizeof(x));
    memset(y, 0, sizeof(y));

    glColor3f(0.0, 1.0, 0.0);

    if(term==1)
    {
        xd1=450+shift;yd1= 200;xd2=50+shift;yd2=200;
        cohen_Line(450+shift, 200, 50+shift, 200);
        xd1=50+shift;yd1=200;xd2=150+shift;yd2=100;
        cohen_Line(50+shift, 200, 150+shift, 100);
        xd1=150+shift;yd1= 100;xd2= 350+shift;yd2=100;
        cohen_Line(150+shift, 100, 350+shift, 100);
        xd1=350+shift;yd1= 100;xd2=450+shift;yd2=200;
        cohen_Line(350+shift, 100, 450+shift, 200);
    }
    else
    {
    draw_line(450+shift, 200, 50+shift, 200);
    draw_line(50+shift, 200, 150+shift, 100);
    draw_line(150+shift, 100, 350+shift, 100);
    draw_line(350+shift, 100, 450+shift, 200);
    }
    x[0]=450+shift;y[0]=200;
    x[1]=50+shift;y[1]=200;
    x[2]=150+shift;y[2]=100;
    x[3]=350+shift;y[3]=100;
    n=4;
    scanfill(x,y);
    memset(x, 0, sizeof(x));
    memset(y, 0, sizeof(y));


    glColor3f(0.0, 1.0, 1.0);

    if(term==1)
    {
        xd1=150 + shift;yd1= 250;xd2= 250+shift;yd2=350;
        cohen_Line(150 + shift, 250, 250+shift, 350);
        xd1=250+shift;yd1= 350;xd2=250+shift;yd2=250;
        cohen_Line(250+shift, 350, 250+shift, 250);
        xd1=250+shift;yd1= 25;xd2=150 + shift;yd2=250;
        cohen_Line(250+shift, 250, 150 + shift, 250);
    }
    else
    {
    draw_line(150 + shift, 250, 250+shift, 350);
    draw_line(250+shift, 350, 250+shift, 250);
    draw_line(250+shift, 250, 150 + shift, 250);
    }
    x[0]=150+shift;y[0]=250;
    x[1]=250+shift;y[1]=350;
    x[2]=250+shift;y[2]=250;

    n=3;
    scanfill(x,y);
    memset(x, 0, sizeof(x));
    memset(y, 0, sizeof(y));

    glColor3f(0.0, 0.0, 0.0);

    if(term==1)
    {
         xd1=250+shift;yd1= 250;xd2=250+shift;yd2=200;
        cohen_Line(250+shift, 250.0, 250+shift, 200);
         xd1=250+shift;yd1= 200;xd2=230+shift;yd2=200;
        cohen_Line(250+shift, 200, 230+shift, 200);
         xd1=230+shift;yd1=200;xd2=230+shift;yd2=250;
        cohen_Line(230+shift, 200, 230+shift, 250);
         xd1=230+shift;yd1= 250;xd2=250+shift;250.0;
        cohen_Line(230+shift, 250, 250+shift, 250.0);
    }
    else
    {
    draw_line(250+shift, 250.0, 250+shift, 200);
    draw_line(250+shift, 200, 230+shift, 200);
    draw_line(230+shift, 200, 230+shift, 250);
    draw_line(230+shift, 250, 250+shift, 250.0);}
    x[0]=250+shift;y[0]=250;
    x[1]=250+shift;y[1]=200;
    x[2]=230+shift;y[2]=200;
    x[3]=230+shift;y[3]=250;
    n=4;
    scanfill(x,y);
    memset(x, 0, sizeof(x));
    memset(y, 0, sizeof(y));

    glColor3f(0.0, 0.0, 1.0);
    a1=100;
    b1=50;
    xc1=200+ind;yc1=700;
    draw_ellipse();

    a1=100;
    b1=50;
    xc1=800+ind;yc1=700;
    draw_ellipse();


    a1=100;
    b1=50;
    xc1=600+ind;yc1=500;
    draw_ellipse();


    a1=150;
    b1=50;
    xc1=500+ind;yc1=800;
    draw_ellipse();

    a1=100;
    b1=50;
    xc1=50+ind;yc1=600;
    draw_ellipse();
    if(que==1)
    {
        shift=(int)(shift+12)%1000;

        rot=1;
        rot1=1;
        angleRad+=90*3.1416/180;
    }
    ind=(int)(ind+5)%1000;
    glutSwapBuffers();
    }
    glFlush();
} /* function to make the user able to deal with the system */

void key(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_LEFT:
            shift-=10;
            glutPostRedisplay();
            break;

        case GLUT_KEY_RIGHT:
            shift+=10;
            glutPostRedisplay();
            break;

        case GLUT_KEY_UP:
            s1+=10;
            glutPostRedisplay();
            break;

        case GLUT_KEY_DOWN:
            s1-=10;
            glutPostRedisplay();
            break;
    }
}

void mykey(unsigned char key,int x,int y)
{
    if(key==27)
    {
    cout<<"escape pressed. exit."<<endl;
    glutDestroyWindow(window);
    exit(0);
    }
    if(key=='c')
    {
        clip1=0;
        term=1;
        glutPostRedisplay();
    }
    if(key=='C')
    {
        clip1=1;
        term=1;
        glutPostRedisplay();

    }
    if(key=='n')
    {   clip1=2;
        term=1;
        glutPostRedisplay();
    }
    if(key=='q')
    {
        term=0;
        glutPostRedisplay();
    }
    if(key=='w')
    {
        if(term==1)
        {
            ymin+=7;
            ymax+=7;
            glutPostRedisplay();
        }
    }
    if(key=='s')
    {
        if(term==1)
        {
            ymin-=7;
            ymax-=7;
            glutPostRedisplay();

        }
    }
    if(key=='a')
    {
        if(term==1)
        {
            xmin-=7;
            xmax-=7;
            glutPostRedisplay();

        }
    }
    if(key=='d')
    {
        if(term==1)
        {
            xmin+=7;
            xmax+=7;
            glutPostRedisplay();

        }
    }
    if(key=='m')
    {
        int m1=0;
        que=1;

    }
    if(key=='M')
    {
        shift=0;
        ind=0;
        que=0;
        angleRad=0;
        rot=0;
        rot1=0;
        glutPostRedisplay();
    }
    if(key=='z')
    {
        r=lam*r;
        if(r>1000)
        {
            r=r/lam;
        }
        glutPostRedisplay();
    }
    if(key=='Z')
    {
        r=r/lam;
        if(r<2)
        {
            r=lam*r;
        }
        glutPostRedisplay();
    }
    if(key=='r')
    {
        rot=1;
        rot1=1;
        angle=90;
        angleRad=angle*3.1416/180;
        glutPostRedisplay();
    }
    if(key=='R')
    {
        rot=0;
        rot1=0;
        glutPostRedisplay();
    }
    if(key==' ')
    {
        view=1;
        glutPostRedisplay();
    }
    if(key=='b')
    {
        view=0;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv)
{
    cout << " please move the boat with left and right arrows" << endl;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(1000, 1000); //sets the initial window size
    glutCreateWindow(" Moving Boat"); // creates the window with name line
    init();
    glutDisplayFunc(drawing_moving_boats);
    glutIdleFunc(drawing_moving_boats);
    glutSpecialFunc(key);
    glutKeyboardFunc(mykey);
    glutMainLoop();
    return 0;// enters the GLUT event processing loop
}
