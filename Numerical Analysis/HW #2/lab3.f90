! program assign3
!     call newton()
! end program lab3

! real*8 function f(x,y,z)
!     real*8 :: x,y,z
!     f = x**2 +2*y**2 +4*z**2 -7
! end function

! real*8 function g(x,y,z)
!     real*8 :: x,y,z
!     g = 2*x**2 +y**3 +6*z -10
! end function

! real*8 function h(x,y,z)
!     real*8 :: x,y,z
!     h = x*y*z + 1
! end function

! subroutine newton()
!     implicit none;
!     real*8 :: x,y,z,tol
!     real*8 :: errorx, errory, errorz

!     real*8, external :: f,g,h
!     double precision, dimension(3, 1):: px,fx,before,error
!     double precision, dimension(3, 3):: jacobi

!     integer :: info
!     integer, dimension(3) :: ipiv
!     double precision, dimension(3) :: work
!     double precision, dimension(3, 3) :: mat

!     real :: b(3,1)
!     x = 1
!     y = -1.
!     z = 1.2
!     px = reshape((/x,y,z/), (/3,1/))

!     tol = 1.0e-07
!     ! ------- till error occur
!     10 fx = reshape((/f(x,y,z),g(x,y,z),h(x,y,z)/), (/3,1/))
!     jacobi = reshape((/2*x,4*x,y*z,4*y,3*y**2,x*z,8*z,real(6,8),x*y/), (/3,3/))

!     call dgetrf(3,3,jacobi,3,ipiv,info)
!     call dgetri(3,jacobi,3,ipiv,work,3*3,info)

!     before = px

!     px = px - matmul(jacobi, fx)
!     error = px-before

!     x = px(1,1)
!     y = px(2,1)
!     z = px(3,1)
!     if(abs(error(1,1)) >= tol .and. abs(error(2,1)) >= tol .and. abs(error(3,1)) >= tol) then
!         goto 10
!     end if
!     print *, x,y,z
! end subroutine

program problem1
    implicit none
    call newton()
end program problem1

real * 8 function f(x,y,z)
    real * 8 :: x, y, z
    f = x * y * z - 1
end function

real * 8 function g(x,y,z)
    real * 8 :: x, y, z
    g = x**2 + y**2 + z**2 - 4
end function

real * 8 function h(x,y,z)
    real * 8 :: x, y, z
    h = x**2 + 2*y**2 - 3
end function

subroutine newton()
    implicit none
    real * 8 :: x, y, z, tol
    real * 8 :: errorx, errory, errorz

    real * 8, external :: f, g, h
    double precision, dimension(3, 1):: px,fx,before,error
    double precision, dimension(3, 3):: jacobi

    integer :: info
    integer :: job
    integer, dimension(3) :: ipiv
    double precision, dimension(3) :: work
    double precision, dimension(3, 3) :: mat

    real :: b(3, 1)
    x = 1
    y = 1.2
    z = 1.4
    px = reshape((/x,y,z/), (/3,1/))

    tol = 1.0e-08
    10 fx = reshape((/f(x,y,z), g(x,y,z), h(x,y,z)/), (/3,1/))
    jacobi = reshape((/y*z, 2*x, 2*x, x*z, 2*y, 4*y, x*y, 2*z, real(0,8)/),(/3,3/))

    job = 0
    call dgetrf(3,3,jacobi,3,ipiv,info)
    call dgetri(3,jacobi,3,ipiv,work,3*3,info)
    ! call dgefa(jacobi,3,3,ipiv,info)
    ! call dgesl(jacobi,3,3,ipiv,b,job)

    before = px

    px = px - matmul(jacobi, fx)
    error = (px-before)/px

    x = px(1,1)
    y = px(2,1)
    z = px(3,1)
    if(abs(error(1,1)) >= tol .and. abs(error(2,1)) >= tol .and. abs(error(3,1)) >= tol) then
        goto 10
    end if
    print *, x,y,z
end subroutine