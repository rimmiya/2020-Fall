/*
 * Copyright 2020. Heekuck Oh, all rights reserved
 * 이 프로그램은 한양대학교 ERICA 소프트웨어학부 재학생을 위한 교육용으로 제작되었습니다.
 */
#include <stdio.h>
#include <stdint.h>

#define PRIME 1
#define COMPOSITE 0

/*
 * mod_add() - computes a + b mod m
 * 프로그램 #3에서 구현한 것과 동일하다
 */
uint64_t mod_add(uint64_t a, uint64_t b, uint64_t m)
{
    a = a % m;
    b = b % m;
    if(a + b < b) b = b - m;
    return (a + b) % m;
}

/*
 * mod_mul() - computes a * b mod m
 * 프로그램 #3에서 구현한 것과 동일하다
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
 * 프로그램 #3에서 구현한 것과 동일하다
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

/*
 * miller_rabin() - Miller-Rabin Primality Test (deterministic version)
 * 결정적 밀러라빈 알고리즘을 사용하여 n이 소수이면 PRIME을, 합성수이면 COMPOSITE를 넘겨준다.
 * 결정적 밀러라빈 알고리즘은 n < 2^64일 때, 검증할 베이스 a의 값을 무작위로 선택하지 않고
 * 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37만 검증해도 알 수 있다는 것에 기반한다.
 */
int miller_rabin(uint64_t n)
{
    uint64_t a[12] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    uint64_t i, j, q, k, l, flg;

    for(i = 0; i < 12; i++){
        if(n == a[i]) return PRIME;
    }

    q = (n - 1);
    k = 0;

    while(k % 2 == 0){
        q = q / 2;
        k = k + 1;
    }

    for(i = 0; i < 12; i++){
        flg = COMPOSITE;
        if(mod_pow(a[i], q, n) == 1) flg = PRIME;
        l = 1;
        for(j = 0; j < k; j++){
            if(mod_pow(mod_pow(a[i], q, n),l, n) == n-1){
                flg = PRIME;
            }
            l *= 2;
        }
        if(flg == COMPOSITE) return COMPOSITE;
    }
    return flg;
}

int main(void)
{
    uint64_t x;
    int i;

    /*
     * 처음 10000개의 소수를 출력한다.
     */
    x = 2; i = 0;
    while (1) {
        if (miller_rabin(x)) {
            ++i;
            printf("%llu ", x);
            if (i % 10 == 0)
                printf("\n");
            if (i == 10000)
                break;
        }
        ++x;
    }
    /*
     * x = 0x8000000000000000부터 100개의 소수를 출력한다.
     */
    x = 0x8000000000000000; i = 0;
    while (1) {
        if (miller_rabin(x)) {
            ++i;
            printf("%llu ", x);
            if (i % 4 == 0)
                printf("\n");
            if (i == 100)
                break;
        }
        ++x;
    }
}
