#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define RANGE 1001
#define clean system("cls")//清屏
#define pause system("pause")//暂停
#define pause_clear system("pause");system("cls")//暂停+清屏
long int tel[RANGE];//记录成员的电话
char *name[RANGE];//记录成员的名字
int num=0;//表示通讯录中成员的个数
int index_list=-1;//作为在特定时候指定成员编号的数
void intialize_memory()
{
    for(int k=0; k<RANGE; k++)
    {
        name[k]=(char*)malloc(sizeof(char)*10);
    }
}
void listing()
{
    for(int j=0; j<num; j++)
    {
        printf("姓名:%s\t号码:%ld\n",name[j],tel[j]);
    }
}
void cancel()
{
    int look_index,ok,judge;
    printf("根据姓名删除联系人请输入1；\n根据号码删除联系人请输入2\n");
    scanf("%d",&judge);
    if(judge==1)
    {
        look_index=locating_name();
    }
    else
    {
        look_index=locating_tel();
    }
    printf("确定删除吗？\n确定请按1；反悔请按2\n");
    scanf("%d",&ok);
    if(ok==2)
    {
        printf("删除取消\n");
        return;
    }
    else
    {
        printf("删除中\n");
        for(int j=look_index; j<num; j++)
        {
            tel[j]=tel[j+1];
            name[j]=name[j+1];
        }
        index_list=-1;
        printf("删除成功\n");
        num-=1;
        return;
    }
}
int locating_judge()
{
    int judge;
    printf("按电话号码查找请输入0\n按姓名查找请输入1\n");
    scanf("%d",&judge);
    return judge;
}
int locating_name()
{
    char flag[10];
    printf("请输入名字:");
    scanf("%s",flag);
    for(int j=0; j<num; j++)
    {
        if(!strcmp(name[j],flag))
        {
            printf("号码是:%ld\t名字是:%s\n",tel[j],name[j]);
            return j;
        }
    }
    printf("找不到（囧）\n");
    return -1;
}
int locating_tel()
{
    int flag;
    printf("请输入电话号码:\n");
    scanf("%d",&flag);
    for(int j=0; j<num; j++)
    {
        if(flag==tel[j])
        {
            printf("号码是:%ld\t名字是:%s\n",tel[j],name[j]);
            return j;
        }
    }
    printf("找不到（囧）\n");
    return -1;
}
void log_in()
{
    printf("请输入电话号码:\n");
    scanf("%ld",&tel[num]);
    printf("请输入名字:\n");
    scanf("%s",name[num]);
    printf("添加成功！\n");
    num++;//成员+1
}
int main()
{
    intialize_memory();
    while(1)
    {
        int n;
        printf("请输入你需要进行的操作：\n1为添加联系人;\n2为查找联系人;\n3为删除联系人;\n4为列出所有联系人;\n5为退出程序\n");
        scanf("%d",&n);
        clean;
        switch(n)
        {
            case 1:log_in();break;
            case 2:if(locating_judge())
            {
                locating_name();
            }
            else
            {
                locating_tel();
            }
            break;
            case 3:cancel();break;
            case 4:listing();break;
            case 5:exit(1);break;
        }
        pause_clear;
    }
    return 0;
}
