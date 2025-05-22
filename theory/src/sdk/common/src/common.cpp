
void swap(long a, long b) {
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}