#pragma once

#include<limits>
#include<vector>


typedef unsigned long long  ull;

// Get the max number of uul: 18446744073709551615
const ull Max_Ull_Number = std::numeric_limits<ull>::max();

 const  ull Max_Process_Prime_Support =  1e10;

void swap(long a, long b);

bool is_repeat(const std::vector<ull>& v);