#pragma once

#include<vector>
#include "../../common/include/common.h"
#include "../../common/include/errorcode.h"




class Prime 
{
    public:
        ~Prime();
        ErrorCode find_prime_with_eratosthenes (const ull n, std::set<ull>& primes);

        ErrorCode calc_gcd_with_euclidean(const ull a, const ull b, ull& gcd);
        ErrorCode extended_euclidean(const long _a, const long _b, long& _gcd, long& bz_x, long& bz_y) ;

        bool is_prime(const ull n);
        bool is_prime_by_baillie_psw(const ull P_N, const ull P_K);

        ErrorCode factorization(const ull n, std::vector<ull>& factor);

        ErrorCode chinese_remainder_theorem(const std::vector<ull>& a, const std::vector<ull>& m, ull& ret);

        


        bool is_coprime(const std::vector<ull>& v);



        // WARNING: this method only for learn
        bool is_prime_by_fermat(const ull n);
        bool is_prime_by_miller_rabin (const ull n);



    
    private:
        ull pow(ull pow_a, ull pow_b, ull pow_c);
        bool MiillerTest(ull MT_dt, ull MT_num);
        bool calc_ti(const ull Mi, const ull mi, ull& ti);
        

    
    public:
  

    private:


        
};