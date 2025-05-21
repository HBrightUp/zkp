#include <iostream>
#include <cstring>
#include "./sdk/common/include/common.h"

// 使用 埃拉托斯特尼筛法 查找 N 内的素数
void sieve_of_eratosthenes (long n)
{
    bool primeNumber[n + 1];
    memset(primeNumber, true, sizeof(primeNumber));

    for (long  j = 2; j * j <= n; j++) {
        if (primeNumber[j]) {
    
            for (long k = j * j; k <= n; k += j) {
                primeNumber[k] = false;
                //std::cout << "K:" << k << std::endl;
            }
                
        }
    } 
    for (long i = 2; i <= n; i++)
        if (primeNumber[i])
            std::cout << i << " ";

    std::cout << std::endl;
}
// 使用 欧几理德算法查找两个数的最大公约数
long euclidean_algorithm(long a, long b) {

    if (a < b) {
        swap(a, b);
    } 

    if (b == 0) {
        return a;
    }

    long r = a % b;
    while (r) {
        a = b;
        b = r;
        r = a % b;
    }

    return b;
}

int main()
{
    sieve_of_eratosthenes(25);
    std::cout << "GCD(30, 24) = " << euclidean_algorithm(30,24) << std::endl;
    return 0;
} 

