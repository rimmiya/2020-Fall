/*
 * Copyright 2020. Heekuck Oh, all rights reserved
 * 이 프로그램은 한양대학교 ERICA 소프트웨어학부 재학생을 위한 교육용으로 제작되었습니다.
 */
#include <stdio.h>
#include <stdint.h>
/*
 * mod_add() - computes a+b mod m
 * 만일 a+b에서 오버플로가 발생하면 값이 틀리게 된다.
 * 이런 경우에는 m을 빼서 오버플로가 생기지 않게 한다. 즉, a+(b-m)을 계산하면 된다.
 * 오버플로는 a+b >= b가 성립하지 않을 때 발생한다.
 */
uint64_t mod_add(uint64_t a, uint64_t b, uint64_t m)
{
    if(a+b < b) b = b - m;
    return ((a % m) + (b % m)) % m;
}

/*
 * mod_sub() - computes a-b mod m
 * 만일 a < b이면 결과가 음수가 되므로 m을 더해서 양수로 만든다.
 */
uint64_t mod_sub(uint64_t a, uint64_t b, uint64_t m)
{
    if(a < b) return ((a % m) - (b % m) + m) % m;
    return ((a % m) - (b % m)) % m;
}

/*
 * mod_mul() - computes a*b mod m
 * a*b에서 오버플로가 발생할 수 있기 때문에 덧셈을 사용하여 빠르게 계산할 수 있는
 * "double addition" 알고리즘을 사용한다. 그 알고리즘은 다음과 같다.
 *     r = 0;
 *     while (b > 0) {
 *         if (b & 1)
 *             r = mod_add(r, a, m);
 *         b = b >> 1;
 *         a = mod_add(a, a, m);
 *     }
 */
uint64_t mod_mul(uint64_t a, uint64_t b, uint64_t m)
{
    uint64_t r = 0;
    while (b > 0) {
        if (b & 1)
            r = mod_add(r, a, m);
        b = b >> 1;
        a = mod_add(a, a, m);
    }
    return r;
}

/*
 * mod_pow() - computes a^b mod m
 * a^b에서 오버플로가 발생할 수 있기 때문에 곱셈을 사용하여 빠르게 계산할 수 있는
 * "square multiplication" 알고리즘을 사용한다. 그 알고리즘은 다음과 같다.
 *     r = 1;
 *     while (b > 0) {
 *         if (b & 1)
 *             r = mod_mul(r, a, m);
 *         b = b >> 1;
 *         a = mod_mul(a, a, m);
 *     }
 */
uint64_t mod_pow(uint64_t a, uint64_t b, uint64_t m)
{
    uint64_t r = 1;
    while (b > 0) {
        if (b & 1)
            r = mod_mul(r, a, m);
        b = b >> 1;
        a = mod_mul(a, a, m);
    }
    return r;
}

int main(void)
{
    uint64_t a, b, m;
    
    a = 1234; b = 5678; m = 3456;
    printf("<덧셈> ");
    printf("%llu + %llu mod %llu = %llu\n", a, b, m, mod_add(a,b,m));
    printf("<뺄셈> ");
    printf("%llu - %llu mod %llu = %llu\n", a, b, m, mod_sub(a,b,m));
    printf("<곱셈> ");
    printf("%llu * %llu mod %llu = %llu\n", a, b, m, mod_mul(a,b,m));
    printf("<지수> ");
    printf("%llu ^ %llu mod %llu = %llu\n", a, b, m, mod_pow(a,b,m));
    printf("---\n");
    a = 3684901700; b = 3904801120; m = 4294901760;
    printf("<덧셈> ");
    printf("%llu + %llu mod %llu = %llu\n", a, b, m, mod_add(a,b,m));
    printf("<뺄셈> ");
    printf("%llu - %llu mod %llu = %llu\n", a, b, m, mod_sub(a,b,m));
    printf("<곱셈> ");
    printf("%llu * %llu mod %llu = %llu\n", a, b, m, mod_mul(a,b,m));
    printf("<지수> ");
    printf("%llu ^ %llu mod %llu = %llu\n", a, b, m, mod_pow(a,b,m));
    printf("---\n");
    a = 18446744073709551360u;
    b = 18446744073709551598u;
    m = 18441921395520346504u;
    printf("<덧셈> ");
    printf("%llu + %llu mod %llu = %llu\n", a, b, m, mod_add(a,b,m));
    printf("<뺄셈> ");
    printf("%llu - %llu mod %llu = %llu\n", a, b, m, mod_sub(a,b,m));
    printf("<곱셈> ");
    printf("%llu * %llu mod %llu = %llu\n", a, b, m, mod_mul(a,b,m));
    printf("<지수> ");
    printf("%llu ^ %llu mod %llu = %llu\n", a, b, m, mod_pow(a,b,m));
}
