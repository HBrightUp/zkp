#include <iostream>
#include "../include/gcd.h"
#include "../../common/include/common.h"



long extended_euclidean_algorithm(const long _a, const long _b, long* bz_x, long* bz_y) {

    long a = _a;
    long b = _b;

     if (a < b) {
        swap(a, b);
    } 

    if (b == 0) {
        return a;
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

    *bz_x = x;
    *bz_y = y;
    
    return a;
}
