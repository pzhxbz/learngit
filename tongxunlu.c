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
        printf("����:%s\t����:%ld\n",name[j],tel[j]);
    }
    system("pause");
}
void shanchu(int a)
{
    printf("ɾ����\n");
    for(int j=a;j<i;j++)
    {
        tel[j]=tel[j+1];
        name[j]=name[j+1];
    }
    index_list=-1;
    printf("ɾ���ɹ�\n");
    i-=1;
    system("pause");
}
int look_for_name()
{
    char flag[10];
    printf("����������:");
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
            printf("������:%ld\t������:%s\n",tel[j],name[j]);
            return j;
        }
    }
    printf("�Ҳ������壩\n");
    return -1;
}
int look_for_tel()
{
    int flag;
    printf("������绰����:\n");
    scanf("%d",&flag);
    for(int j=0;j<i;j++)
    {
        if(flag==tel[j])
        {
            printf("������:%ld\t������:%s\n",tel[j],name[j]);
            return j;
        }
    }
    printf("�Ҳ������壩\n���򽫷������˵�\n");
    return -1;
}
void luru()
{
    system("cls");
    printf("������绰����:\n");
    scanf("%ld",&tel[i]);
    printf("����������:\n");
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
        printf("����������Ҫ���еĲ�����\n1Ϊ�����ϵ��;\n2Ϊ������ϵ��;\n3Ϊɾ����ϵ��;\n4Ϊ�г�������ϵ��;\n5Ϊ�˳�����\n");
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
            printf("���绰�������������0\n����������������1\n");
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
            printf("��������ɾ����ϵ��������1�����ݺ���ɾ����ϵ��������2\n");
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
                printf("ȷ��ɾ����\nȷ���밴1�������밴2\n");
                scanf("%d",&ok);
                if(ok==2)
                {
                    printf("���򽫷������˵�\n");
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
