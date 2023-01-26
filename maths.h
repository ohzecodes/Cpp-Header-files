#include <cmath>
using namespace std;
#ifndef maths_h
#define maths_h

template <typename T>
T GenerateRandomValue(T min, T max) {
    return rand() % (max - min + 1) + min;
}

/* in logₐ(b)
a=base 
b=nunuber
example: logwithbase(125, 5)=3;
*/
int logwithbase(int number, int base) {
    return log(number) / log(base);
}
template <typename T, typename E>
double pythagoreamthreorem(T num1, E num2) {
    return sqrt(pow(num1, 2) + pow(num2, 2));
}

int extractlastdigit(int num) {
    int rem;

    rem = num % 10;

    return rem;
}

int removelastdigit(int n) {
    return n / 10;
}

// recursive factorial

int factorial(int n) {
    if (n == 1) {
        return n;
    } else {
        return n * factorial(n - 1);
    }
}

int extractdigit(int num, int digit) {
    int p = 0;
    for (int i = 0; i < digit; i++) {
        p = extractlastdigit(num);
        num /= 10;
    }
    return p;
}

template <typename A, typename B, typename C>
bool betweenInclusive(A number, B min, C max) {
    return number >= min && number <= max;
}

template <typename A, typename B, typename C>
bool betweenExclusive(A number, B min, C max) {
    return number > min && number < max;
}
#endif