#include<windows.h>
#include<glut.h>
#include<iostream>
#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"ShapeInfo.h"
#define SQUARE 0
#define CIRCLE 1
#define TRIANGLE 2
#define ELLIPSE 3
#define LINE 4
#define FREEDOM 5
#define PI acos(-1)
#define GRAPH 9
#define ERASER 6
#define SAVE 7
#define OPEN 8
#define MOVE 250
//#define test (l-change_y+2400*change_x)
GLubyte *PixelData_move,*PxielData_change;
int x0,y0;
int x1,y1;
int x2,y2;
int x3,y3;
int width;
int height=500;
int first=500;
int winWidth=800,winHeight=600;     //窗口的宽度和高度
bool button_judge;
int shape=0;
int move_flag=0;
ShapeInfo *All,data[1000];
ShapeInfo *move_save;
int num=0;//图形数量
static float cur_size=5.0;
bool drag_judge;
void display();
void drag()
{
    /*GLint i,j;
    i=winWidth*3;
    while(i%4!=0)
    {
        ++i;
    }
    int change_x=x2-x0,change_y=y2-y0;
    GLint PixelLength_move;
    PixelLength_move=i*winHeight;
    PixelData_move=(GLubyte*)malloc(PixelLength_move);
    PxielData_change=(GLubyte*)malloc(PixelLength_move);
    glPixelStorei(GL_UNPACK_ALIGNMENT,4);
    glReadPixels(0,0,winWidth,winHeight,0x80E0,GL_UNSIGNED_BYTE,PixelData_move);
    for(int k=0;k<800;k++)
    {
        for(int l=0;l<601;l++)
        {
            PxielData_change[k][l]=255;
            if(k+change_x<0||l+change_y<0||k+change_x>=800||l+change_y>=800)
            {
                continue;
            }
            PxielData_change[k+change_x][l+change_y]=PixelData_move[k][l];
        }
    }
    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    //glTranslated((GLfloat)change_x,(GLfloat)change_y,0);
    //gluOrtho2D(-1+change_x,1+change_x,-1+change_y,1+change_y);
    for(int l=0;l<480000*3;l++)
    {
        //int o=l/3;
        int x=l/600;
        int y=600-l%600;
        if(test<480000*3&&test>=0)
        {
            if(PixelData_move[test]!=0)
            {
                PxielData_change[l]=PixelData_move[test];
            }
        }
        else
        {
            if(l==0)
            {
                PxielData_change[l]=255;
                PxielData_change[l+1]=255;
            }
            else if(l==480000*3)
            {
                PxielData_change[l]=255;
                PxielData_change[l-1]=255;
            }
            else
            {
                PxielData_change[l+1]=255;
                PxielData_change[l]=255;
                PxielData_change[l-1]=255;
            }
        }
    }
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawPixels(winWidth,winHeight,0x80E0,GL_UNSIGNED_BYTE,PxielData_change);
    glutSwapBuffers();
    glFlush();*/
    int change_x=x2-x0,change_y=y2-y0;
    if(move_flag==0)
    {
        for(int i=num-1;i>=0;i--)
        {
            drag_judge=data[i].is_in(x0,y0);
            if(drag_judge)
            {
                move_save=&data[i];
                move_flag=1;
                break;
            }
        }
    }
    move_save->trans(change_x,change_y);
    glClear(GL_COLOR_BUFFER_BIT);
    for(int i=0;i<num;i++)
    {
        if(&data[i]==move_save)
        {
            move_save->draw_change();
        }
        else
        {
            data[i].print();
        }
    }
    glFlush();
}
void open()
{
    /*GLint PixelLength_open;
    GLubyte *PixelData_open;
    GLint ImageWidth;
    GLint ImageHeight;
    FILE *pFile=fopen("new.bmp","rb");
    if(pFile==0)
    {
        exit(0);
    }
    fseek(pFile,0x0012,SEEK_SET);
    fread(&ImageWidth,sizeof(ImageWidth),1,pFile);
    fread(&ImageHeight,sizeof(ImageHeight),1,pFile);
    PixelLength_open=ImageWidth*3;
    while(PixelLength_open%4!=0)
    {
        ++PixelLength_open;
    }
    PixelLength_open*=ImageHeight;
    PixelData_open=(GLubyte*)malloc(PixelLength_open);
    if(PixelData_open==0)
    {
        return;
    }
    fseek(pFile,54,SEEK_SET);
    glPixelStorei(GL_UNPACK_ALIGNMENT,4);
    fread(PixelData_open,PixelLength_open,1,pFile);
    fclose(pFile);
    shape==FREEDOM;
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawPixels(ImageWidth,ImageHeight,0x80E0,GL_UNSIGNED_BYTE,PixelData_open);
    glutSwapBuffers();
    glFlush();*/
    All=data;
    for(int i=0;i<num;i++)
    {
        delete(All);
        All++;
    }
    glClear(GL_COLOR_BUFFER_BIT);
    All=data;
    FILE *open;
    open=fopen("save.txt","r");
    fscanf(open,"%d",&num);
    All=new ShapeInfo();
    for(int i=0;i<num;i++)
    {
        int info,x11,y11,x22,y22;
        fscanf(open,"%d %d %d %d %d",&info,&x11,&y11,&x22,&y22);
        data[i].print(info,x11,y11,x22,y22);
        glFlush();
        All++;
    }
    shape=0;
    fclose(open);
}
void save()
{
    /*FILE *pDummyFile;
    FILE *pWritingFile;
    GLubyte *pPixelData;
    GLubyte BMP_Header[54];
    GLint i,j;
    GLint PixelDataLengh;
    i=winWidth*3;
    while(i%4!=0)
    {
        ++i;
    }
    PixelDataLengh=i*winHeight;
    pPixelData=(GLubyte*)malloc(PixelDataLengh);
    if(pPixelData==0)
    {
        exit(0);
    }
    pDummyFile=fopen("dummy.bmp","rb");
    pWritingFile=fopen("new.bmp","wb");
    if(pDummyFile==0)
    {
        exit(0);
    }
    if(pWritingFile==0)
    {
        exit(0);
    }
    glPixelStorei(GL_UNPACK_ALIGNMENT,4);
    glReadPixels(0,0,winWidth,winHeight,0x80E0,GL_UNSIGNED_BYTE,pPixelData);//没定义GL_BGR_EXT
    fread(BMP_Header,sizeof(BMP_Header),1,pDummyFile);
    fwrite(BMP_Header,sizeof(BMP_Header),1,pWritingFile);
    fseek(pWritingFile,0x0012,SEEK_SET);
    i=winWidth;
    j=winHeight;
    fwrite(&i,sizeof(i),1,pWritingFile);
    fwrite(&j,sizeof(j),1,pWritingFile);
    fseek(pWritingFile,0,SEEK_END);
    fwrite(pPixelData,PixelDataLengh,1,pWritingFile);
    fclose(pDummyFile);
    fclose(pWritingFile);
    free(pPixelData);*/
    FILE *save;
    save=fopen("save.txt","w+");
    fprintf(save,"%d\n",num);
    for(int i=0;i<num;i++)
    {
        for(int j=0;j<=4;j++)
        {
            fprintf(save,"%d ",data[i].load(j));
        }
        fprintf(save,"\n");
    }
    fclose(save);
    exit(0);
}
void drawing()
{

    /*if(shape==SQUARE)
    {
        glBegin(GL_LINE_LOOP);
        glVertex2f(x0,y0);
        glVertex2f(x1,y1);
        glVertex2f(x2,y2);
        glVertex2f(x3,y3);
    }
    if(shape==CIRCLE)
    {
        float circle_x=(x0+x2)/2;
        float circle_y=(y0+y2)/2;
        float R=sqrt((x2-x0)*(x2-x0)+(y0-y2)*(y0-y2))/2;
        glBegin(GL_LINE_LOOP);
        for(int i=0;i<72;++i)
        {
            glVertex2f(circle_x+R*cos(2*PI/72*i),circle_y+R*sin(2*PI/72*i));
        }
    }
    if(shape==TRIANGLE)
    {
        float peak_x=(x0+x3)/2;
        float peak_y=(y0+y3)/2;
        glBegin(GL_LINE_LOOP);
        glVertex2f(peak_x,peak_y);
        glVertex2f(x2,y2);
        glVertex2f(x1,y1);
    }
    if(shape==ELLIPSE)
    {
        float center_x=(x0+x2)/2,center_y=(y0+y2)/2;
        float a=(x0-x2)/2,b=(y0-y2)/2;
        glBegin(GL_LINE_LOOP);
        for(int i=0;i<72;++i)
        {
            glVertex2f(center_x+a*cos(2*PI/72*i),center_y+b*sin(2*PI/72*i));
        }
    }
    if(shape==LINE)
    {
        glBegin(GL_LINES);
        glVertex2f(x0,y0);
        glVertex2f(x2,y2);
    }
    if(shape==FREEDOM)
    {
        glPointSize(cur_size);
        glColor3f(0.0,0.0,1.0);
        glBegin(GL_POINTS);
        glVertex2f(x2,y2);
    }
    if(shape==ERASER)
    {
        glPointSize(cur_size);
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_POINTS);
        glVertex2f(x2,y2);
    }*/
    data[num].print(shape,x0,y0,x2,y2);
    if(shape==MOVE)
    {
        drag();
    }
    glEnd();
    glFlush();
    glPointSize(1.0);
}
void mouse(int button,int state, int x,int y)
{
    glEnable(GL_LOGIC_OP);
    if(button==GLUT_RIGHT_BUTTON&& state == GLUT_DOWN)
    {
        button_judge=false;
    }
    else
    {
        button_judge=true;
    }
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        All=new ShapeInfo();
        All++;
        x1=x2=x3=x0=x;
        y1=y2=y3=y0=height-y;
        glColor3f(0.0,1.0,0.0);
        if(shape==ERASER)
        {
            glColor3b(1.0,1.0,1.0);
        }
        if(shape!=FREEDOM&&shape!=ERASER)
        {
            glLogicOp(GL_XOR);
        }
        first=0;
    }
    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        drawing();
        x2 = x;
        y2 = height-y;
        x1 = x0;
        y1 = y2;
        x3 = x;
        y3 = y0;
        glFlush();
        glColor3f(0.0,0.0,1.0);
        glLogicOp(GL_COPY);
        drawing();
        if(shape==MOVE)
        {
            move_flag=0;
            move_save->add_change();
        }
        num++;
    }
}
void move(int x,int y)
{
    if(!button_judge)
    {
        return;
    }
    if(first == 1)
    {
       drawing();
    }
    x2 = x;
    y2 = height-y;
    x1 = x0;
    y1 = y2;
    x3 = x;
    y3 = y0;
    drawing();
    first = 1;
}
void display()
{
    glClearColor(1.0,1.0,1.0,1.0);
    glEnable(GL_COLOR_LOGIC_OP);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0,1.0,1.0,1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glFlush();
}
void myReshape(int w,int h)
{
    glClearColor(1.0,1.0,1.0,1.0);
    glViewport(0,0,w,h);
    width=w;
    height=h;
    glMatrixMode(GL_PROJECTION);//投影矩阵
    glLoadIdentity();
    gluOrtho2D(0.0,(GLfloat)w,0.0,(GLfloat)h);
    glMatrixMode(GL_MODELVIEW);//矩阵堆栈
}
void processMenuEvents(int option)
{
    if(option==SAVE)
    {
        save();
    }
    if(option==OPEN)
    {
        open();
    }
    shape=option;
}
void processSubMenuEvents(int option)
{
    shape=option;
}
void size_choose(int potion)
{
    cur_size=potion;
}
void creat_menu()
{
    int menu,submenu,SizeMenu;
    submenu=glutCreateMenu(processSubMenuEvents);
    glutAddMenuEntry("矩形",SQUARE);
    glutAddMenuEntry("圆",CIRCLE);
    glutAddMenuEntry("三角形",TRIANGLE);
    glutAddMenuEntry("椭圆",ELLIPSE);
    glutAddMenuEntry("直线",LINE);
    SizeMenu=glutCreateMenu(size_choose);
    for(int i=1;i<=20;i++)
    {
        char j=char(i+64);
        char *p=&j;
        glutAddMenuEntry(p,i);
    }
    menu=glutCreateMenu(processMenuEvents);
    glutAddSubMenu("图形",submenu);
    glutAddSubMenu("自由绘画and橡皮擦大小",SizeMenu);
    glutAddMenuEntry("自由绘画(暂不支持)",FREEDOM);
    glutAddMenuEntry("橡皮擦（暂不支持）",ERASER);
    glutAddMenuEntry("拖动",MOVE);
    glutAddMenuEntry("保存",SAVE);
    glutAddMenuEntry("打开",OPEN);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

}
int main(int argc,char **argv)
{
    glutInit(&argc,argv);//初始化
    All=data;
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);//显示方式
    glutInitWindowSize(800,600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("画矩形");
    glutReshapeFunc(myReshape);//窗口改变的时候调用的函数，在这个里面可以根据缩放后的窗口重新设置
    creat_menu();
    glutDisplayFunc(display);//画图
    glutMotionFunc(move);
    glutMouseFunc(mouse);
    glutMainLoop();//窗口结束关闭
    return 0;
}
