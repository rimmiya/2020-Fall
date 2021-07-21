PROGRAM palindrome_prime
    implicit none
    integer :: ans, temp, tf
    real :: n = 11, i
    Write(*,*) 'Palindromic Prime Number is ..'
    prime : Do While(n <= 10000)
        tf = 0
        i = 2
        Do While(i <= sqrt(n))
            IF(MOD(n, i) == 0) Then
                tf = 1
                Exit
            End If
            i = i + 1
        END Do
        IF(tf == 0) Then
            temp = int(n)
            ans = 0
            palin : Do While(temp > 0)
                ans = ans * 10
                ans = ans + MOD(temp,10)
                temp = temp / 10
            END Do palin
            if(n == ans) Write(*,*) int(n)
        END IF
        n = n + 1
    END Do prime
END PROGRAM palindrome_prime