
#include <cstring>
#include<iostream>
#include<memory>
#include<set>
#include <algorithm>
#include "../include/prime.h"




Prime::~Prime() { }


// 使用 欧几理德算法查找两个数的最大公约数
bool Prime::find_prime_with_eratosthenes (const ull _n, std::set<ull>& primes)
{
    ull n = _n;

    if (n > max_prime_find_support) {
        return false;
    }

    std::shared_ptr<bool[]> sp(new bool[ n + 1]()); 
    memset(sp.get(), true, sizeof(bool) * (n + 1));

    for (ull  j = 2; j * j <= n; j++) {
        if (sp[j]) {
    
            for (ull k = j * j; k <= n; k += j) {
                sp[k] = false;
            }
                
        }
    } 

    for (long i = 2; i <= n; i++) {
        if (sp[i]) {
            primes.insert(i);
        }
            
    }
    
    std::cout << "finished" << std::endl;

    std::cout << std::endl;

    //WARNING: forgot write the return, core dumped.
   return true;
}




/*
    Function: Determine whether a number is prime with Baillie_PSW
    Parameters:
        n:    Determine whether n is a prime number.
    Return:    
        bool:  
    WARNING: Only handle numbers within 10e10.
*/
bool Prime::is_prime(const ull n) {
    if (n > 1e10) {
        std::cout << "number too large." << std::endl;
        return false;
    }

    return is_prime_by_baillie_psw(n, 83);
}



/*
    Function: Determine whether a number is prime with Little Theorem, 
    Parameters:
        n:    Determine whether n is a prime number.
    Return:    
        bool:  
    WARNING: The false positive rate of this method is a bit high, so it 
        should not be used in actual projects. It is only used for learning.
*/
bool Prime::is_prime_by_fermat(const ull n) {
    if (n <= 1) 
        return false;

    ull t = 1, m = 2, p = n;

    while(p) { 
        if (p % 2) t = (t * m) % n;
        m = (m * m) % n;
        p >>= 1;
    }
    t = (t - 2) % n;


    return t == 0;
}


/*
    Function: Determine whether a number is prime with Miller Rabin, 
    Parameters:
        n:    Determine whether n is a prime number.
    Return:    
        bool:  
    WARNING: This method can achieve deterministic primality checks, b
    but it has not yet been completed, so don't use it for now;
        
*/
const ull prime[10]={2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
bool Prime::is_prime_by_miller_rabin(const ull n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    int s = 0, t = n - 1;

    while (!(t % 2)) ++s, t >>= 1; // 求解 n-1=2^s*t

    for (int i = 0; i < 10 && prime[i] < n; ++i) {
        
        int a = prime[i];
        int b = 1, m = a, p = t;
        while (p) { //快速幂，求 b=a^t
            
            if (p % 2) b = ((long long) b * m) % n;
            m = ((long long)m * m) % n;
            p >>= 1;
        }
        if (b == 1) continue;
        for (int j = 1; j <= s; ++j) { // 进行 s 次二次检验
            int k = ((long long)b * b) % n;
            if(k == 1 && b != n-1) return false;
            b = k;
            
        }
        if (b != 1) return false;
    }

    
    return true;
}



/*
    function: Determine whether a number is prime with Baillie-PSW, it's a recommended method currently.
    Parameters:
        P_N:    Determine whether P_N is a prime number.
        P_K:  
    Return: 
        bool:   ture with a prime.  

*/
bool Prime::is_prime_by_baillie_psw(const ull P_N, const ull P_K) {
    if (P_N <= 1 || P_N == 4)
        return false;

    if (P_N <= 3)
        return true;

    ull P_D = P_N - 1;

    while (P_D % 2 == 0)
        P_D /= 2;

    for (int i = 0; i < P_K; ++i) {
        if (!MiillerTest(P_D, P_N))
            return false;
    }

    return true;
}

/*
    function: Factorize a number and return all its factors
    Parameters:
        n:    The number to be decomposed.
    Return: 
        factor: A collection of factors.  

*/
bool Prime::factorization(const ull n, std::vector<ull>& factor) {

    ull a = n;

    if (a < 4) 
        return true;

    if (!factor.empty()) {
        factor.clear();
    }

    for(int i = 2; i <= (n + 1) / 2 ; ++i) {
        while(a % i == 0) {
            factor.push_back(i);
            //std::cout << i << std::endl;
            a = a / i;
        }
    
    }
    
    return true;
}

/*
    function: Calculate the greatest common divisor of two numbers.
    Parameters:
        a:    N
        b:    N  
    Return: 
        factor: A collection of factors.  

*/
bool Prime::calc_gcd_with_euclidean(const ull _a, const ull _b, ull& _gcd) {

    ull a = _a;
    ull b = _b;

    if (a < b) {
        swap(a, b);
    } 

    if (b == 0) {
        _gcd = a;
        return true;
    }

    ull r = 0;
    while (b) {
        r = a % b;
        a = b;
        b = r;
    }

    _gcd = a;

    return true;
}

/*
    function: Calculate  Bayer formula and Modular Inverse
    Parameters:
        _a:    N
        _b:    N  
    Return: 
        factor: A collection of factors.  

*/
bool Prime::extended_euclidean_algorithm(const long _a, const long _b, long& _gcd, long& bz_x, long& bz_y) {

    long a = _a;
    long b = _b;

    ull gcd = 0;
    if(!calc_gcd_with_euclidean(a, b, gcd)) {
        return false;
    }

    // The result can only be calculated if a and b are coprime.
    if(gcd != 1) {
        return false;
    }

    long x1 = 0;
    long x2 = 1;
    long y1 = 1;
    long y2 = 0;

    long q,x,y;
    long r;

    while (b) {

        q = a / b;
        r = a % b;
        a = b;
        b = r;

        if (r != 0) {
            x = x2 - x1 * q;
            y = y2 - y1 * q;
            x2 = x1;
            x1 = x;
            y2 = y1;
            y1 = y;
        }
        
        
    }   

    std::cout << "x1: " << x1 << ", y1: " << y1 << ", x2: " << x2 << ", y2: " << y2 << std::endl;

    bz_x = x;
    bz_y = y;
    
    _gcd = a;

    return true;
}



ull Prime::pow(ull pow_a, ull pow_b, ull pow_c) {

    ull result = 1;
    pow_a = pow_a % pow_c;

    while (pow_b > 0) {

        if (pow_b & 1)
            result = (result * pow_a) % pow_c;

        pow_b = pow_b >> 1;
        pow_a = (pow_a * pow_a) % pow_c;
    }

   return result;
}

bool Prime::MiillerTest(ull MT_dt, ull MT_num) {

   ull MT_a = 2 + rand( ) % (MT_num - 4);
   ull MT_x = pow(MT_a, MT_dt, MT_num);

   if (MT_x == 1 || MT_x == MT_num - 1)
      return true;

   while (MT_dt != MT_num - 1) {

      MT_x = (MT_x * MT_x) % MT_num;
      MT_dt *= 2;
      if (MT_x == 1)
         return false;
      if (MT_x == MT_num - 1)
         return true;

   }

   return false;
}
