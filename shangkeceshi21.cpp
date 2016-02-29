#include <iostream>
#include <time.h>
void testb()
{
      int a = 0;
      for (int i=0;i<1000;i++)
          {
          for (int i=0;i<1000000;i++)
               a++;
          }
}
void testa()
{
      int a = 0;
      for (int i=0;i<1000000;i++)
          {
          for (int i=0;i<1000;i++)
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
         std::cout<<"外层大内层小 "<<t2-t1<<std::endl;
         }
         #pragma omp section
         {
         clock_t t3 = clock();
         for (int i=0;i<8;i++)
             testb();
         clock_t t4 = clock();
         std::cout<<"外层小内层大 "<<t4-t3<<std::endl;
         }
     }
     return 0;
 }
