#include <stdio.h>
#include <stdlib.h>
#include <string.h>
long int tel[1000];
char *name[1000];
int i=0;
int index_list=-1;
void following()
{
    for(int j=0;j<i;j++)
    {
        printf("姓名:%s\t号码:%ld\n",name[j],tel[j]);
    }
    system("pause");
}
void shanchu(int a)
{
    printf("删除中\n");
    for(int j=a;j<i;j++)
    {
        tel[j]=tel[j+1];
        name[j]=name[j+1];
    }
    index_list=-1;
    printf("删除成功\n");
    i-=1;
    system("pause");
}
int look_for_name()
{
    char flag[10];
    printf("请输入名字:");
    scanf("%s",flag);
    if(i==1)
    {
        following();
        return 1;
    }
    for(int j=0;j<i;j++)
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
int look_for_tel()
{
    int flag;
    printf("请输入电话号码:\n");
    scanf("%d",&flag);
    for(int j=0;j<i;j++)
    {
        if(flag==tel[j])
        {
            printf("号码是:%ld\t名字是:%s\n",tel[j],name[j]);
            return j;
        }
    }
    printf("找不到（囧）\n程序将返回主菜单\n");
    return -1;
}
void luru()
{
    system("cls");
    printf("请输入电话号码:\n");
    scanf("%ld",&tel[i]);
    printf("请输入名字:\n");
    scanf("%s",name[i]);
    system("cls");
    i++;
}
int main()
{
    for(int k=0;k<1000;k++)
    {
        name[k]=(char*)malloc(sizeof(char)*10);
    }
    while(1)
    {
        printf("请输入你需要进行的操作：\n1为添加联系人;\n2为查找联系人;\n3为删除联系人;\n4为列出所有联系人;\n5为退出程序\n");
        int n;
        scanf("%d",&n);
        if(n==5)
        {
            for(int k=0;k<1000;k++)
            {
                name[k]=NULL;
            }
            exit(1);
        }
        if(n==1)
        {
            luru();
        }
        if(n==2)
        {
            system("cls");
            printf("按电话号码查找请输入0\n按姓名查找请输入1\n");
            int judge;
            scanf("%d",&judge);
            if(judge)
            {
                 look_for_name();
            }
            else
            {
                 look_for_tel();
            }
            system("pause");
            system("cls");
        }
        if(n==3)
        {
            system("cls");
            printf("根据姓名删除联系人请输入1；根据号码删除联系人请输入2\n");
            int m;
            scanf("%d",&m);
            int look_index,ok;
            if(m==1)
            {
                look_index=look_for_name();
            }
            if(m==2)
            {
                look_index=look_for_tel();
            }
                if(look_index==-1)
                {
                    continue;
                }
                printf("确定删除吗？\n确定请按1；反悔请按2\n");
                scanf("%d",&ok);
                if(ok==2)
                {
                    printf("程序将返回主菜单\n");
                    system("pause");
                }
                if(ok==1)
                {
                    shanchu(look_index);
                }
                system("cls");
        }
        if(n==4)
        {
            system("cls");
            following();
            system("cls");
        }
    }
    return 0;
}
