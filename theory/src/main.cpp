#include <iostream>
#include <cstring>

void Sieve_Of_Eratosthenes(int n);


int main()
{
    int n = 25;
    Sieve_Of_Eratosthenes(n);
    return 0;
} 

// 使用 埃拉托斯特尼筛法 查找 N 内的素数
void Sieve_Of_Eratosthenes(int n)
{
    bool primeNumber[n + 1];
    memset(primeNumber, true, sizeof(primeNumber));

    for (int j = 2; j * j <= n; j++) {
        if (primeNumber[j]) {
    
            for (int k = j * j; k <= n; k += j) {
                primeNumber[k] = false;
                //std::cout << "K:" << k << std::endl;
            }
                
        }
    } 
    for (int i = 2; i <= n; i++)
        if (primeNumber[i])
            std::cout << i << " ";
}