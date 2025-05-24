#include<iostream>
#include<random>
#include<thread>
#include<chrono>
#include<set>
#include<memory>
#include<cassert>
#include"../include/prime_test.h"
#include"../include/prime.h"
#include "../../sdk/common/include/common.h"
#include "../../sdk/common/include/prime_table.h"
#include "../../sdk/maths/include/prime.h"
#include "../../sdk/common/include/errorcode.h"




struct PrimeFermatMiiller {
    ull num;
    bool is_prime_by_fermat;
    bool is_prime_by_miiller;

    bool operator<(const PrimeFermatMiiller &a) const;
};

bool PrimeFermatMiiller::operator<(const PrimeFermatMiiller& other) const
{
    if(this->num == other.num)
    {
        return false;
    }
    else
    {
        return this->num > other.num;
    }
}

void PrimeTest::test_gcd_euclidean() {

    std::shared_ptr<Prime> sp(new Prime());
    const ull a = 300;
    const ull b = 45;
    ull max_divisor = 0;

    ErrorCode err = sp->get_gcd_with_euclidean(a, b, max_divisor);
    if(err != ErrorCode::Success) {
        std::cout << "call calc_greatest_common_divisor failed." << std::endl;
        return ;
    } 

    assert(max_divisor == 15);
}

void PrimeTest::test_gcd__extend_euclidean() {

    const long a = 64;
    const long b = 23;
    long x = 0;
    long y = 0;
    long gcd = 0;

    std::shared_ptr<Prime> sp(new Prime());

    // calc Bayer formula and Modular Inverse
    ErrorCode err = sp->extended_euclidean( a, b, gcd, x, y );
    if (err != ErrorCode::Success) {
        std::cout << "call extended_euclidean failed." << std::endl;
        return ;
    }

    //std::cout << "gcd: " << gcd << ",x: " << x << " ,y: " << y << std::endl;
    assert(a * x + b * y == gcd);
}


// use eratosthenes produce primes and check it with  Baillie PSW and factorization.
void PrimeTest::test_eratosthenes() {
    std::shared_ptr<Prime> p(new Prime());

    // 5761455 primes exist within 1e8. 
    // 1229 primes exist within 1e4. 
    const ull max_range = 1e4;

    std::set<ull> primes;
    ErrorCode err = p->find_prime_with_eratosthenes(max_range, primes);
    if (err != ErrorCode::Success) {
        std::cout << "call  find_prime_with_eratosthenes failed.";
        return ;
    }

    std::cout << "Amount of primes within " << max_range << " : " << primes.size() << std::endl;

    //use Baillie PSW to check
    ull no = 0;
    std::vector<ull> factors;

    for( ull v : primes) {

        //std::cout << "start check: " << v << std::endl;

        if(!p->is_prime_by_baillie_psw(v, 47)) {
            std::cout << "check failed: " << v << std::endl;
            return ;
        }

        factors.clear();
        ErrorCode err = p->factorization(v, factors);
        if(err == ErrorCode::Success) {
            if (factors.empty()) {
                //std::cout << "Common check success: " << v << std::endl;
            } else {
                std::cout << "Common check failed: " << v << std::endl;
                return ;
            }
        } else {
            std::cout << "call factorization failed." << std::endl;
            return ;
        }

        ++no;
        //std::cout << "check prime success: " << v << " ,Serial Number: " << no << std::endl;
        
    }

    assert(no == 1229);
}


/*
    Function:  Comparing two methods of determining prime numbers: Little Theorem and Baillie-PSW.
    Result:  Baillie-PSW is a superior method.
*/
void PrimeTest::test_is_prime() {

    std::shared_ptr<Prime> p(new Prime());

    std::mt19937 rng(std::random_device{}());
    ull counts = 0;
    ull rand_num = 0;
    const ull test_times = 10000;

    std::set<PrimeFermatMiiller> different_result;

    while(true) {
        if (++counts ==  test_times) {
            break;
        }

        rand_num = rng();

        // large number need to other method, here only less than 1e10  by support.  
        if (rand_num > 1e10) {
            continue;
        }
      
        bool is_fermat = p->is_prime_by_fermat(rand_num);
        bool is_miiller = p->is_prime_by_baillie_psw(rand_num, 50);

        if (is_fermat && is_miiller) {
            std::cout << rand_num << "  yes" << std::endl;
        } else if (!is_fermat && !is_miiller) {
            //std::cout << rand_num << " no" << std::endl;
        } else {

            std::cout << "Different result, is_fermat: " << is_fermat << " ,is_miiller: " << is_miiller << std::endl;
            different_result.insert(PrimeFermatMiiller{
                num: rand_num,
                is_prime_by_fermat: is_fermat,
                is_prime_by_miiller: is_miiller,
            });
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        if (different_result.size() == 1) {
            //break;
        }
        
        if (!is_fermat && is_miiller) {
            std::cout << "Different result, is_fermat: " << is_fermat << " ,is_miiller: " << is_miiller << std::endl;
            std::cout << "Different result, is_fermat: false , is_miiller: true "  << std::endl;
            std::cout << "counts: " << std::endl;
            break;
        }
    }

    // print result:
    for(PrimeFermatMiiller v: different_result){
        std::cout << "number: " << v.num << " ,fermat: " << v.is_prime_by_fermat << " ,miiller: " << v.is_prime_by_miiller << std::endl; 
        
        std::vector<ull> factor;
        p->factorization(v.num, factor);

        if (!factor.empty()) {
            for (ull f : factor) {
                std::cout  << "factor: " << f << std::endl;
            }
            //std::this_thread::sleep_for(std::chrono::milliseconds(10000));
        }
    }
}

void PrimeTest::test_chinese_remainder_theorem() {
    std::shared_ptr<Prime> sp(new Prime());

    std::vector<ull> a,m;

    a.push_back(2);
    a.push_back(3);
    a.push_back(2);
    m.push_back(3);
    m.push_back(5);
    m.push_back(7);

    ull x = 0;
    ErrorCode err = sp->chinese_remainder_theorem(a, m, x);
    assert(err == ErrorCode::Success);

    assert(x == 23);
}

void PrimeTest::test_get_amounts_coprime_within_n() {

    std::shared_ptr<Prime> sp(new Prime());

    ull  n = 1;
    ull count = 0;
    ErrorCode err = sp->get_amounts_coprime_within_n(n, count);
    assert(err == ErrorCode::Success);
    assert(count == 1);

    n = 2;
    err = sp->get_amounts_coprime_within_n(n, count);
    assert(err == ErrorCode::Success);
    assert(count == 1);

    n = 3;
    err = sp->get_amounts_coprime_within_n(n, count);
    assert(err == ErrorCode::Success);
    assert(count == 2);

    n = 5;
    err = sp->get_amounts_coprime_within_n(n, count);
    assert(err == ErrorCode::Success);
    assert(count == 4);

    n = 9;
    err = sp->get_amounts_coprime_within_n(n, count);
    assert(err == ErrorCode::Success);
    assert(count == 6);

    n = 15;
    err = sp->get_amounts_coprime_within_n(n, count);
    assert(err == ErrorCode::Success);
    assert(count == 8);
}

void PrimeTest::test_get_unit_order() {
    std::shared_ptr<Prime> sp(new Prime());

    const ull n  = 5;
    const ull a = 2;
    ull order = 0;
    ErrorCode err = sp->get_unit_order(a, n, order);
    assert(err == ErrorCode::Success);
    assert(order == 4);
}

void PrimeTest::check_euler_theorem() {

    std::shared_ptr<Prime> sp(new Prime());

    const ull a = 3;
    const ull n = 7;
    ull count = 0;
    ull gcd = 0;

    ErrorCode err = sp->get_gcd_with_euclidean(a, n, gcd);
    assert(err == ErrorCode::Success);
    assert(gcd == 1);

    err = sp->get_amounts_coprime_within_n(n, count);
    assert(err == ErrorCode::Success);
    assert( ull(std::pow(a, count)) % n == 1);

}

void PrimeTest::test_all() {

    test_eratosthenes();
    test_gcd_euclidean();
    test_gcd__extend_euclidean();
    test_chinese_remainder_theorem();
    test_get_amounts_coprime_within_n();
    test_get_unit_order();
    check_euler_theorem();
}