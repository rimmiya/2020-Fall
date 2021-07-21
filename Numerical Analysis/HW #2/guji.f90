program p1
    implicit none
    real*8, dimension(0:2) :: jacobian
    real*8 :: answer, error
  
    jacobian = (/1,2,3/)
  
    jacobian((/1/)) = 1.0
    jacobian((/2/)) = 1.2
    jacobian((/3/)) = 1.4
  
    error = 1.0e-08
  
   write (*,*) jacobian
  
  end program p1
  
  real*8 function f(x,y,z)
    real*8 :: x, y, z
    f = x * y * z -1
  end function f
  
  real*8 function g(x,y,z)
    real*8 :: x, y, z
    g = x**2 + y**2  + z**2 -4
  end function g
  
  real*8 function h(x,y,z)
    real*8 :: x, y, z
    h = x**2  + 2*y**2 -3
  end function h