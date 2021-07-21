/*
 * Copyright 2020. Heekuck Oh, all rights reserved
 * 이 프로그램은 한양대학교 ERICA 소프트웨어학부 재학생을 위한 교육용으로 제작되었습니다.
 */
#include <stdio.h>
#include <stdlib.h>

/*
 * gcd() - Euclidean algorithm
 *
 * 유클리드 알고리즘 gcd(a,b) = gcd(b,a mod b)를 사용하여 최대공약수를 계산한다.
 * 만일 a가 0이면 b가 최대공약수가 된다. 그 반대도 마찬가지이다.
 * a, b가 모두 음이 아닌 정수라고 가정한다.
 * 재귀함수 호출을 사용하지 말고 while 루프를 사용하여 구현하는 것이 빠르고 좋다.
 */
int gcd(int a, int b)
{
    int tmp;

    while(b != 0){
        tmp = a % b;
        a = b;
        b = tmp;
    }
    
    return a;
}

/*
 * xgcd() - Extended Euclidean algorithm
 *
 * 확장유클리드 알고리즘은 두 수의 최대공약수와 gcd(a,b) = ax + by 식을 만족하는
 * x와 y를 계산하는 알고리즘이다. 강의노트를 참조하여 구현한다.
 * a, b가 모두 음이 아닌 정수라고 가정한다.
 */
int xgcd(int a, int b, int *x, int *y)
{
    int d0 = a, d1 = b;
    int x0 = 1, x1 = 0;
    int y0 = 0, y1 = 1;
    int q, tmp;
    
    while(1){
        q = d0 / d1;

        tmp = d0 - q * d1;
        d0 = d1;
        d1 = tmp;

        tmp = x0 - q * x1;
        x0 = x1;
        x1 = tmp;

        tmp = y0 - q * y1;
        y0 = y1;
        y1 = tmp;

        if(d1 == 0){
            *x = x0;
            *y = y0;
            return d0;
        }
    }
}

/*
 * mul_inv() - computes multiplicative inverse a^-1 mod m
 *
 * 모듈로 m에서 a의 곱의 역인 a^-1 mod m을 구한다.
 * 만일 역이 존재하지 않는다면 0을 리턴해야 한다.
 * 확장유클리드 알고리즘을 약간 변형하면 구할 수 있다. 강의노트를 참조한다.
 */
int mul_inv(int a, int m)
{
    int d0 = a, d1 = m;
    int x0 = 1, x1 = 0;
    int q, tmp;

    while(d1 > 1){
        q = d0 / d1;

        tmp = d0 - q * d1;
        d0 = d1;
        d1 = tmp;

        tmp = x0 - q * x1;
        x0 = x1;
        x1 = tmp;
    }

    if(d1 == 1) return (x1 > 0 ? x1 : x1 + m);
    
    return 0;
}

int main(void)
{
    int a, b, x, y, d, count;
    
    /*
     * 기본 gcd 시험
     */
    a = 28; b = 0;
    printf("gcd(%d,%d) = %d\n", a, b, gcd(a,b));
    a = 0; b = 32;
    printf("gcd(%d,%d) = %d\n", a, b, gcd(a,b));
    a = 41370; b = 22386;
    printf("gcd(%d,%d) = %d\n", a, b, gcd(a,b));
    a = 22386; b = 41371;
    printf("gcd(%d,%d) = %d\n---\n", a, b, gcd(a,b));
    /*
     * 기본 xgcd, mul_inv 시험
     */
    a = 41370; b = 22386;
    d = xgcd(a, b, &x, &y);
    printf("%d = %d * %d + %d * %d\n", d, a, x, b, y);
    printf("%d^-1 mod %d = %d, %d^-1 mod %d = %d\n---\n", a, b, mul_inv(a,b), b, a, mul_inv(b,a));
    a = 41371; b = 22386;
    d = xgcd(a, b, &x, &y);
    printf("%d = %d * %d + %d * %d\n", d, a, x, b, y);
    printf("%d^-1 mod %d = %d, %d^-1 mod %d = %d\n", a, b, mul_inv(a,b), b, a, mul_inv(b,a));
    /*
     * 난수 a와 b를 발생시켜 xgcd를 계산하고, 최대공약수가 1이면 역이 존재하므로
     * 여기서 얻은 a^-1 mod b와 b^-1 mod a를 mul_inv를 통해 확인한다.
     * 이 과정을 8백만번 이상 반복하여 올바른지 확인한다.
     */
    printf("Random testing"); fflush(stdout);
    count = 0;
    do {
        arc4random_buf(&a, sizeof(int)); a &= 0x7fffffff;
        arc4random_buf(&b, sizeof(int)); b &= 0x7fffffff;
        d = xgcd(a, b, &x, &y);
        if (d == 1) {
            if (x < 0)
                x = x + b;
            else
                y = y + a;
            if (x != mul_inv(a, b) || y != mul_inv(b, a)) {
                printf("Inversion error\n");
                exit(1);
            }
        }
        if (++count % 0xffff == 0) {
            printf(".");
            fflush(stdout);
        }
    } while (count < 0xfffff);
    printf("No error found\n");
}
