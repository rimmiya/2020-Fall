real*8 function A1norm(A, M, N)
    real*8 A(M, N)
    real*8 :: max = 0, sum = 0
    integer :: M, N, i = 0, j
    Do While(j < N)
        j = j + 1
        i = 0
        sum = 0
        Do While(i < M)
            i = i + 1
            sum = sum + abs(A(i,j))
        End do
        IF(sum > max) Then
            max = sum
        End If
    End do
    A1norm = max
    return
END function

program test
    implicit none
    real*8 A(3, 4), A1norm
    integer :: i, j, k=1
    do i = 1, 3
        do j = 1, 4
            A(i,j) = -1 * k
            k = k + 1
        end do
    end do
    print*, A1norm(A, 3, 4)
end program
    