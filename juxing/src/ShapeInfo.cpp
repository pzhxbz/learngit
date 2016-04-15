#include "ShapeInfo.h"
#include <glut.h>
#include <math.h>
#define SQUARE 0
#define CIRCLE 1
#define TRIANGLE 2
#define ELLIPSE 3
#define LINE 4
#define FREEDOM 5
#define PI acos(-1)
#define GRAPH 9
#define ERASER 6
float abs(float a)
{
    if(a<=0)
        return -a;
    return a;
}
int max(int a,int b)
{
    if(a>=b)
        return a;
    return b;
}
int min(int a,int b)
{
    if(a>=b)
        return b;
    return a;
}
bool fuhao(float a,float b)
{
    if(a<=0&&b<=0)
        return true;
    if(a>=0&&b>=0)
        return true;
    return false;
}
ShapeInfo::ShapeInfo()
{

}

ShapeInfo::~ShapeInfo()
{

}
void ShapeInfo::draw()
{
    if(info==SQUARE)
    {
        glBegin(GL_LINE_LOOP);
        glVertex2f(x1,y1);
        glVertex2f(x1,y2);
        glVertex2f(x2,y2);
        glVertex2f(x2,y1);
    }
    if(info==CIRCLE)
    {
        float circle_x=(x1+x2)/2;
        float circle_y=(y1+y2)/2;
        float R=sqrt((x2-x1)*(x2-x1)+(y1-y2)*(y1-y2))/2;
        glBegin(GL_LINE_LOOP);
        for(int i=0;i<72;++i)
        {
            glVertex2f(circle_x+R*cos(2*PI/72*i),circle_y+R*sin(2*PI/72*i));
        }
    }
    if(info==TRIANGLE)
    {
        float peak_x=(x1+x2)/2;
        float peak_y=y1;
        glBegin(GL_LINE_LOOP);
        glVertex2f(peak_x,peak_y);
        glVertex2f(x2,y2);
        glVertex2f(x1,y2);
    }
    if(info==ELLIPSE)
    {
        float center_x=(x1+x2)/2,center_y=(y1+y2)/2;
        float a=(x1-x2)/2,b=(y1-y2)/2;
        glBegin(GL_LINE_LOOP);
        for(int i=0;i<72;++i)
        {
            glVertex2f(center_x+a*cos(2*PI/72*i),center_y+b*sin(2*PI/72*i));
        }
    }
    if(info==LINE)
    {
        glBegin(GL_LINES);
        glVertex2f(x1,y1);
        glVertex2f(x2,y2);
    }
    /*if(a==FREEDOM)
    {
        glPointSize(cur_size);
        glColor3f(0.0,0.0,1.0);
        glBegin(GL_POINTS);
        glVertex2f(x2,y2);
    }
    if(a==ERASER)
    {
        glPointSize(cur_size);
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_POINTS);
        glVertex2f(x2,y2);
    }*/
    glEnd();
}
void ShapeInfo::draw_change()
{
    int x1=this->x1+change_x1,x2=this->x2+change_x1;
    int y1=this->y1+change_y1,y2=this->y2+change_y1;
    if(info==SQUARE)
    {
        glBegin(GL_LINE_LOOP);
        glVertex2f(x1,y1);
        glVertex2f(x1,y2);
        glVertex2f(x2,y2);
        glVertex2f(x2,y1);
    }
    if(info==CIRCLE)
    {
        float circle_x=(x1+x2)/2;
        float circle_y=(y1+y2)/2;
        float R=sqrt((x2-x1)*(x2-x1)+(y1-y2)*(y1-y2))/2;
        glBegin(GL_LINE_LOOP);
        for(int i=0;i<72;++i)
        {
            glVertex2f(circle_x+R*cos(2*PI/72*i),circle_y+R*sin(2*PI/72*i));
        }
    }
    if(info==TRIANGLE)
    {
        float peak_x=(x1+x2)/2;
        float peak_y=y1;
        glBegin(GL_LINE_LOOP);
        glVertex2f(peak_x,peak_y);
        glVertex2f(x2,y2);
        glVertex2f(x1,y2);
    }
    if(info==ELLIPSE)
    {
        float center_x=(x1+x2)/2,center_y=(y1+y2)/2;
        float a=(x1-x2)/2,b=(y1-y2)/2;
        glBegin(GL_LINE_LOOP);
        for(int i=0;i<72;++i)
        {
            glVertex2f(center_x+a*cos(2*PI/72*i),center_y+b*sin(2*PI/72*i));
        }
    }
    if(info==LINE)
    {
        glBegin(GL_LINES);
        glVertex2f(x1,y1);
        glVertex2f(x2,y2);
    }
    glEnd();
}
void ShapeInfo::print(int a,int x11,int y11,int x22,int y22)
{
    this->info=a;
    this->x1=x11;
    this->x2=x22;
    this->y1=y11;
    this->y2=y22;
    draw();
}
void ShapeInfo::print()
{
    if(info==-1)
    {
        return;
    }
    draw_change();
}
int ShapeInfo::load(int a)
{
    switch (a)
    {
        case 0:return this->info;
        case 1:return this->x1;
        case 2:return this->y1;
        case 3:return this->x2;
        case 4:return this->y2;
    }
}
bool ShapeInfo::is_in(int x,int y)
{
    int a1=max(x1,x2),a2=min(x1,x2);
    int b1=max(y1,y2),b2=min(y1,y2);
     if(info==SQUARE)
    {
        if(x<=a1&&x>=a2&&y>=b2&&y<=b1)
            return true;
    }
    if(info==CIRCLE)
    {
        float circle_x=(x1+x2)/2;
        float circle_y=(y1+y2)/2;
        float R=sqrt((x2-x1)*(x2-x1)+(y1-y2)*(y1-y2))/2;
        float d=sqrt((x-circle_x)*(x-circle_x)+(y-circle_y)*(y-circle_y));
        if(d<=R)
            return true;
    }
    if(info==TRIANGLE)
    {
        float peak_x=(x1+x2)/2;
        float peak_y=y1;
        float down_y=y2;
        float down_x1=x1,down_x2=x2;
        float k1=(peak_y-down_y)/(peak_x-down_x1);
        float k2=(peak_y-down_y)/(peak_x-down_x2);
        if(x-down_x1<=1e-6&&x-down_x1>=-1e-6)
            return false;
        if(x-down_x2<=1e-6&&x-down_x2>=-1e-6)
            return false;
        float kx1=(y-down_y)/(x-down_x1);
        float kx2=(y-down_y)/(x-down_x2);
        if(abs(kx1)<=abs(k1)&&abs(kx2)<=abs(k2)&&fuhao(kx1,k1)&&fuhao(kx2,k2))
            return true;
    }
    if(info==ELLIPSE)
    {
        float center_x=(x1+x2)/2,center_y=(y1+y2)/2;
        float a=(x1-x2)/2,b=(y1-y2)/2;
        if((x-center_x)*(x-center_x)/a/a+(y-center_y)*(y-center_y)/b/b<=1)
            return true;
    }
    if(info==LINE)
    {
        if(x1-x2<=1e-6&&x1-x2>=-1e-6)
        {
            if(y<=b1&&y>=b2)
                return true;
        }
        else
        {
            float k=(y2-y1)/(x2-x1);
            float b=-k*x1+y1;
            if(x*k+b-y<=1e-6&&x*k+b-y>=-1e-6)
                return true;
        }
    }
    return false;
}
void ShapeInfo::trans(int change_x,int change_y)
{
    this->change_x1=change_x;
    this->change_y1=change_y;
}
void ShapeInfo::add_change()
{
    x1+=change_x1;
    x2+=change_x1;
    y1+=change_y1;
    y2+=change_y1;
    change_x1=0;
    change_y1=0;
}

