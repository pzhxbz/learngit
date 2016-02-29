#include <iostream>
#include <time.h>
void testb()
{
      int a = 0;
      for (int i=1000000;i>0;i--)
          {
          for (int i=1000;i>0;i--)
          a++;
          }
      std::cout<<a<<std::endl;
}
void testa()
{
      int a = 0;
      for (int i=0;i<1000000;i++)
          {
          for (int i=0;i<1000;i++)
               a++;
          }
      std::cout<<a<<std::endl;
}
int main()
 {
    clock_t t1 = clock();
     for (int i=0;i<8;i++)
         testa();
     clock_t t2 = clock();
     std::cout<<" "<<t2-t1<<std::endl;
    clock_t t3 = clock();
     for (int i=0;i<8;i++)
         testb();
     clock_t t4 = clock();
     std::cout<<" "<<t4-t3<<std::endl;
     return 0;
 }
