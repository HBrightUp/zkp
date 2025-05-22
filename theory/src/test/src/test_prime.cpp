#include<iostream>
#include<random>
#include<thread>
#include<chrono>
#include<set>
#include<memory>
#include "../../sdk/common/include/common.h"
#include "../../sdk/common/include/prime_table.h"
#include "../../sdk/maths/include/prime.h"
#include "../../sdk/maths/include/gcd.h"


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

void test_gcd_euclidean() {

    std::shared_ptr<Prime> sp(new Prime());
    const ull a = 300;
    const ull b = 240;
    ull max_divisor = 0;

    if(!sp->calc_gcd_with_euclidean(a, b, max_divisor)) {
        std::cout << "call calc_greatest_common_divisor failed." << std::endl;
        return ;
    } else {
        std::cout << "GCD(" << a << "," << b << ") = " << max_divisor << std::endl;
    }
}

void test_gcd__extend_euclidean() {

    const long a = 64;
    const long b = 23;
    long x = 0;
    long y = 0;
    long gcd = 0;

    std::shared_ptr<Prime> sp(new Prime());

    // calc Bayer formula and Modular Inverse
    bool bret = sp->extended_euclidean_algorithm( a, b, gcd, x, y );
    if (!bret) {
        std::cout << "call extended_euclidean_algorithm failed." << std::endl;
        return ;
    }

    std::cout << "gcd: " << gcd << ",x: " << x << " ,y: " << y << std::endl;
    if (a * x + b * y != gcd) {
        std::cout  << "check Bayer formula failed." << std::endl;
    }
}


// use eratosthenes produce primes and check it with  Baillie PSW and factorization.
void test_eratosthenes() {
    std::shared_ptr<Prime> p(new Prime());

    // 5761455 primes exist within 1e8. 
    const ull max_range = 100000000;

    std::set<ull> primes;
    bool bret = p->find_prime_with_eratosthenes(max_range, primes);
    if (!bret) {
        std::cout << "test eratosthenes failed.";
        return ;
    }

    std::cout << "Amount of primes within " << max_range << " : " << primes.size() << std::endl;

    //use Baillie PSW to check
    for( ull v : primes) {
        
        std::cout << "check prime: " << v << std::endl;

        if(!p->is_prime_by_baillie_psw(v, 47)) {
            std::cout << "check failed: " << v << std::endl;
            break;
        } else {
            //std::cout << "Baillie PSW check success: " << v << std::endl;
        }

        std::vector<ull> factors;
        if(p->factorization(v, factors)) {
            if (factors.empty()) {
                //std::cout << "Common check success: " << v << std::endl;
            } else {
                std::cout << "Common check failed: " << v << std::endl;
                break;
            }
        } else {
            std::cout << "call factorization failed." << std::endl;
            break;
        }
        
    }
}


/*
    Function:  Comparing two methods of determining prime numbers: Little Theorem and Baillie-PSW.
    Result:  Baillie-PSW is a superior method.
*/
void test_is_prime() {

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
