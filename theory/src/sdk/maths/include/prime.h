#pragma once

#include<vector>
#include "../../common/include/common.h"
#include "../../common/include/errorcode.h"




class Prime 
{
    public:
        ~Prime();

        // find prime within N
        ErrorCode find_prime_with_eratosthenes (const ull n, std::set<ull>& primes);

        // calc gcd
        ErrorCode get_gcd_with_euclidean(const ull a, const ull b, ull& gcd);

        // calc Bézout's lemma  or  module Inverse
        ErrorCode extended_euclidean(const long _a, const long _b, long& _gcd, long& bz_x, long& bz_y) ;

        //  is n a prime
        bool is_prime(const ull n);
        bool is_prime_by_baillie_psw(const ull P_N, const ull P_K);

        // get all factor of n 
        ErrorCode factorization(const ull n, std::vector<ull>& factor);

        // solove  remainder  theorem question.
        ErrorCode chinese_remainder_theorem(const std::vector<ull>& a, const std::vector<ull>& m, ull& ret);

        // Count the number of elements in 1 ~ (N - 1) that are coprime with N, use  Euler function.
        ErrorCode get_amounts_coprime_within_n(const ull n, ull& amount);

        // Determine whether all elements in a vector are coprime.
        bool is_coprime(const std::vector<ull>& v);


        ErrorCode get_unit_order(const ull a, const ull n, ull& x);


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