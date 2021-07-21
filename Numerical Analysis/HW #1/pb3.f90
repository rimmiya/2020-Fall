real*8 function mycos(x)
    implicit none
    real*8 :: term, k, sign, cosx, x
    term = 1
    k = 0
    sign = 1
    cosx = 0

    Do while(abs(term) > real(10)**(-7))
        term = ((x ** k) / gamma(k + 1)) * sign
        sign = -1 * sign
        k = k + 2
        cosx = cosx + term
    End Do
    mycos = cosx
end function mycos

program test
    real*8 :: x = 0.5, mycos
    print*, mycos(x)
end program test
