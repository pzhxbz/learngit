#include <iostream>
#include <time.h>
#include<omp.h>
void testb()
{
      int a = 0,j=1000000000;
      for (int i=0,n=j;i<n;i++)
          {
               a++;
          }
}
void testa()
{
      int a = 0,j=1000000000;
      for (int i=0;i<j;i++)
          {
               a++;
          }
}
int main()
 {
     #pragma omp parallel sections
     {
         #pragma omp section
         {
         clock_t t1 = clock();
         for(int i=0;i<8;i++)
             testa();
         clock_t t2 = clock();
         std::cout<<"int i=0;i<j;i++ "<<t2-t1<<std::endl;
         }
         #pragma omp section
         {
         clock_t t3 = clock();
         for (int i=0;i<8;i++)
             testb();
         clock_t t4 = clock();
         std::cout<<"int i=0,n=j;i<n;i++ "<<t4-t3<<std::endl;
         }
     }
     return 0;
 }
