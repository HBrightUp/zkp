#pragma once

#include<vector>
#include "../../common/include/common.h"

// 使用 埃拉托斯特尼筛法 查找 N 内的素数


 const  ull max_prime_find_support =  1024 * 1024* 1024;






class Prime 
{
    public:
        ~Prime();

        bool calc_gcd_with_euclidean(const ull a, const ull b, ull& gcd);
        bool extended_euclidean_algorithm(const long _a, const long _b, long& _gcd, long& bz_x, long& bz_y) ;

        bool is_prime(const ull n);
        bool is_prime_by_fermat(const ull n);
        bool is_prime_by_miller_rabin (const ull n);
        bool is_prime_by_baillie_psw(const ull P_N, const ull P_K);

        bool factorization(const ull n, std::vector<ull>& factor);

        bool find_prime_with_eratosthenes (const ull n, std::set<ull>& primes);
    
    
    private:
        ull pow(ull pow_a, ull pow_b, ull pow_c);
        bool MiillerTest(ull MT_dt, ull MT_num);

    
    public:
  

    private:


        
};