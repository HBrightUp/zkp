#include <iostream>
#include<memory>
#include"./test/include/prime_test.h"




int main()
{
    std::unique_ptr<PrimeTest> up(new PrimeTest());

    //test();
    //test_is_prime();
    up->test_eratosthenes();
    up->test_gcd_euclidean();
    up->test_gcd__extend_euclidean();
    up->test_chinese_remainder_theorem();
    up->test_get_amounts_coprime_within_n();
    up->test_get_unit_order();
    up->check_euler_theorem();
 
    return 0;
} 


