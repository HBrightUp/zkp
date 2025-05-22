
long euclidean_algorithm(long a, long b);

// 使用贝组公式和欧几理德扩展算法计算最大公约数
// 此函数也可以用来求取模逆元，仅当返回值为1时存在，即 gcd(a,b) = 1, 此时，返回值 y 就是求取的逆元值;
long extended_euclidean_algorithm(long a, long b, long* x, long* y);

