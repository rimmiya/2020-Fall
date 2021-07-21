program problem5
    implicit none
    dimension :: a(1024, 1024)
    data A /1024*0./
    integer :: nx, n, i
    nx = 32
    n = nx ** 2

    do i = 1, n
        if(i .gt. 1) a(i, i-1) = -1.
        if(i .lt. n) a(i, i+1) = -1.
        a(i,i) = 4.5
        if(i+nx .le. n) a(i, i+nx) = -1.
        if(i-nx .ge. 1) a(i, i-nx) = -1.
        b(i) = cos(i+0.5)
    end do
    
end program problem5