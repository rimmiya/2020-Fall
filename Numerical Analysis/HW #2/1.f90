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
    real * 8 :: x, y, z, tol, eN, pxN

    real * 8, external :: f, g, h
    double precision, dimension(3, 1):: px,fx,before,error
    double precision, dimension(3, 3):: jacobi

    integer :: info, job
    integer, dimension(3) :: ipiv

    double precision, dimension(3, 1) :: b
    x = 1
    y = 1.2
    z = 1.4
    b = reshape((/x,y,z/), (/3,1/))
    px = reshape((/x,y,z/), (/3,1/))

    tol = 1.0e-08
    10 fx = reshape((/f(x,y,z), g(x,y,z), h(x,y,z)/), (/3,1/))
    jacobi = reshape((/y*z, 2*x, 2*x, x*z, 2*y, 4*y, x*y, 2*z, real(0,8)/),(/3,3/))

    job = 0
    call dgefa(jacobi,3,3,ipiv,info)
    call dgesl(jacobi,3,3,ipiv,fx,job)

    before = px

    px = before - fx ! X(k+1)
    error = px-before
    eN = abs(error(1,1))+abs(error(2,1))+abs(error(3,1))
    pxN = abs(px(1,1))+abs(px(2,1))+abs(px(3,1))
    eN = eN/pxN
    
    x = px(1,1)
    y = px(2,1)
    z = px(3,1)
    if(eN > tol) then
        goto 10
    end if
    print *, "x =", x, "y =", y, "z =", z
    
    print *, "f =",f(x,y,z)
    print *, "g =",g(x,y,z)
    print *, "h =",h(x,y,z)
end subroutine