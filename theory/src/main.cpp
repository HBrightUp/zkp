#include <iostream>
#include<memory>
#include"./test/include/prime_test.h"
#include"./test/include/group_test.h"




int main()
{
    std::unique_ptr<PrimeTest> up(new PrimeTest());
    up->test_all();
    
    std::unique_ptr<GroupTest> ug(new GroupTest());
    ug->test_all();
 
    return 0;
} 


