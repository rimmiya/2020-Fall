/*
 * Copyright 2020. Heekuck Oh, all rights reserved
 * 이 프로그램은 한양대학교 ERICA 소프트웨어학부 재학생을 위한 교육용으로 제작되었습니다.
 */
#include <stdio.h>
#include <stdlib.h>

/*
 * gf8_mul(a, b) - a * b mod x^8+x^4+x^3+x+1
 *
 * 7차식 다항식 a와 b를 곱하고 결과를 8차식 x^8+x^4+x^3+x+1로 나눈 나머지를 계산한다.
 * x^8 = x^4+x^3+x+1 (mod x^8+x^4+x^3+x+1) 특성을 이용한다.
 */
unsigned char gf8_mul(unsigned char a, unsigned char b)
{
    u_int8_t r = 0;

    while(b > 0) {
        if(b & 1) r = r ^ a;
        b = b >> 1;
        a = ((a<<1)^((a>>7) & 1 ? 0x1B : 0));
    }
    return r;
}

/*
 * gf8_pow(a,b) - a^b mod x^8+x^4+x^3+x+1
 *
 * 7차식 다항식 a을 b번 지수승한 결과를 8차식 x^8+x^4+x^3+x+1로 나눈 나머지를 계산한다.
 * gf8_mul()과 "Square Multiplication" 알고리즘을 사용하여 구현한다.
 */
unsigned char gf8_pow(unsigned char a, unsigned char b)
{
    u_int8_t r = 1;

    while(b > 0){
        if(b & 1) r = gf8_mul(r, a);
        a = gf8_mul(a, a);
        b = b >> 1;
    }
    return r;
}

/*
 * gf8_inv(a) - a^-1 mod x^8+x^4+x^3+x+1
 *
 * 모둘러 x^8+x^4+x^3+x+1에서 a의 역을 구한다.
 * 역을 구하는 가장 효율적인 방법은 다항식 확장유클리드 알고리즘을 사용하는 것이다.
 * 다만 여기서는 복잡성을 피하기 위해 느리지만 알기 쉬운 지수를 사용하여 구현하였다.
 */
unsigned char gf8_inv(unsigned char a)
{
    return gf8_pow(a, 0xfe);
}

int main(void)
{
    int a, b;
    
    /*
     * 간단한 시험
     */
    a = 28; b = 7;
    printf("%d * %d = %d\n", a, b, gf8_mul(a,b));
    a = 127; b = 68;
    printf("%d * %d = %d\n", a, b, gf8_mul(a,b));
    /*
     * a를 1부터 255까지 a^-1를 구하고 a * a^-1 = 1인지 확인한다.
     */
    for (a = 1; a < 256; ++a) {
        if (a == 0) continue;
        b = gf8_inv(a);
        printf("a = %d, a^-1 = %d, a*a^-1 = %d\n", a, b, gf8_mul(a,b));
        if (gf8_mul(a,b) != 1) {
            printf("Logic error\n");
            exit(1);
        }
    }
    printf("No error found\n");
    return 0;
}

