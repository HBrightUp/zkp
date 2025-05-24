
#include <cstring>
#include<iostream>
#include<memory>
#include<set>
#include <algorithm>
#include<cmath>
#include<cassert>
#include"../../common/include/errorcode.h"
#include "../include/prime.h"
#include "../include/errorcode.h"


Prime::~Prime() { }


/*
    Function: Use Eratosthenes algorithm to find prime numbers within N
    Parameters:
        _n:    
    Return:    
        ull:  error code. 0 means success.
    WARNING: Only handle numbers within 10e10.
*/
ErrorCode Prime::find_prime_with_eratosthenes (const ull _n, std::set<ull>& primes)
{
    ull n = _n;

    if (n < 2) {
        return ErrorCode::InvalidParameter;
    }

    if (n > Max_Process_Prime_Support) {
        return ErrorCode::ExceedProcessPrimeRange;
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

   return ErrorCode::Success;
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

    assert(n > 1 && n < Max_Process_Prime_Support );

    return is_prime_by_baillie_psw(n, 47);
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
    
    assert(n > 1 && n < Max_Process_Prime_Support );

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
ErrorCode Prime::factorization(const ull n, std::vector<ull>& factor) {


    ull a = n;

    if (a < 4) {
        return ErrorCode::Success;
    }

    if (!factor.empty()) {
        factor.clear();
    }

    for(int i = 2; i <= (n + 1) / 2 ; ++i) {
        while(a % i == 0) {
            factor.push_back(i);
            a = a / i;
        }
    
    }
    
    return ErrorCode::Success;
}

/*
    function: Calculate the greatest common divisor of two numbers.
    Parameters:
        a:    N
        b:    N  
    Return: 
        factor: A collection of factors.  

*/
ErrorCode Prime::get_gcd_with_euclidean(const ull _a, const ull _b, ull& _gcd) {

    ull a = _a;
    ull b = _b;

    if (a < b) {
        swap(a, b);
    } 

    if (b == 0) {
        _gcd = a;
        return ErrorCode::Success;
    }

    ull r = 0;
    while (b) {
        r = a % b;
        a = b;
        b = r;
    }

    _gcd = a;

    return ErrorCode::Success;
}


/*
    function: Calculate  Bayer formula and Modular Inverse
    Parameters:
        _a:    N
        _b:    N  
    Return: 
        factor: A collection of factors.  

*/
ErrorCode Prime::extended_euclidean(const long _a, const long _b, long& _gcd, long& bz_x, long& bz_y) {

    long a = _a;
    long b = _b;

    ull gcd = 0;
    ErrorCode err = get_gcd_with_euclidean(a, b, gcd);
    if( err != ErrorCode::Success) {
        return err;
    }

    // The result can only be calculated if a and b are coprime.
    if(gcd != 1) {
        return ErrorCode::NoCoprime;
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

    //std::cout << "x1: " << x1 << ", y1: " << y1 << ", x2: " << x2 << ", y2: " << y2 << std::endl;

    bz_x = x;

    // y is Modular Inverse.
    bz_y = y;
    
    // This expression should hold: gcd(_a,_b) == gcd && gcd == a && a == 1;
    _gcd = a;

    return ErrorCode::Success;
}


/*
    function: Compute the solution to the Chinese Remainder Theorem
    Parameters:
        _a:    a vector with all element a0 ~ ai.
        _m:    a vector with all element m0 ~ mi.
    Return: 
        _ret:  result.  

*/

ErrorCode Prime::chinese_remainder_theorem(const std::vector<ull>& _a, const std::vector<ull>& _m, ull& _ret){

    ull size = _a.size();
    if (size < 2) {
        return ErrorCode::InvalidParameter;
    }

    if (_a.size() != _m.size()) {
        return ErrorCode::InvalidParameter;
    }

    if (is_repeat(_m)) {
        return ErrorCode::InvalidParameter;
    }

    if (!is_coprime(_m)) {
        return ErrorCode::InvalidParameter;
    }

    // calc M
    ull M = 1;
    for(ull m : _m) {
        M *= m;

    }

    ull Mi = 0;
    ull ti =0;
    ull x = 0;
    for(ull i = 0; i< size; ++i) {
        Mi = M / _m[i];
        if(!calc_ti(Mi, _m[i], ti)) {
            return ErrorCode::CalcTiFailed;
        }
        x += _a[i] * Mi * ti;
    }
    
    _ret = x % M;

    return ErrorCode::Success;
}

/*
    function: Count the number which  coprime with N in  1 ~ N. use  Eular Totient  Function to solve it.
    Parameters:
        n:    
    Return: 
        amount:    

*/
ErrorCode Prime::get_amounts_coprime_within_n(const ull _n, ull& _amount) {

    ull n = _n;

    if (n == 1) {
        _amount = 1;
        return ErrorCode::Success;
    }

    // First case:  n is a prime.
    if(is_prime(n)) {
        _amount = n - 1;
        return ErrorCode::Success;
    }

    // secord case: n is a power of numbr.
    std::vector<ull> factor;
    ErrorCode err = factorization(n, factor);
    if (err != ErrorCode::Success) {
        return err;
    }

    // it's a square of a number at least
    const ull factor_size = factor.size();
    assert(factor_size >= 2);

    _amount = 0;
    const ull first = factor[0];  
    bool is_equal_all = true;

    for(ull v : factor) {
        if (first != v) {
            is_equal_all = false;
        }
    }

    if (is_equal_all) {
        _amount = std::pow(first, factor_size) - std::pow(first, factor_size - 1);
        return ErrorCode::Success;
    }

    // third case: It is the product of prime numbers. 
    if (is_coprime(factor)) {
        _amount = 1;
        for( ull v : factor) {
            _amount *= (v - 1);
        }

        return ErrorCode::Success;
    }


    return ErrorCode::Failed;
}


ErrorCode Prime::get_unit_order(const ull _a, const ull _n, ull& _x) {

    ull a = _a;
    ull n = _n;

    for(ull i = 1; i < Max_Ull_Number; ++i) {
        if (ull(std::pow(a, i)) % n == 1 ) {
            _x = i;
            break;
        }
    }

    return ErrorCode::Success;
}




// Determine whether all elements in a set are coprime
bool Prime::is_coprime(const std::vector<ull>& v) {
    
    const ull size = v.size(); 
    if (v.size() < 2) {
        return false;
    }

    ull gcd = 0;
    for(ull i = 0; i < size; ++i) {
        for(ull j = i + 1; j < size; ++j) {

            if(get_gcd_with_euclidean(v[i], v[j], gcd) != ErrorCode::Success) {
                return false;
            }

            if (gcd != 1) {
                return false;
            }
        }
    }

    return true;
}

bool Prime::calc_ti(const ull Mi, const ull mi, ull& ti) {
    
    // Mi * t1 = 1 (mod mi)
    // The equal sign here means congruence.

    const ull remainder = 1;

    for(ull i = 1; i < Max_Ull_Number; ++i) {
        if (Mi * i % mi == remainder) {
            ti = i;
            return true;
        }
    }

    return false;
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
