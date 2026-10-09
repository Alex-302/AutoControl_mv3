// __copysign @ 0046c6cc size=42 callers=1

/* Library Function - Single Match
    __copysign
   
   Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release */

double __cdecl __copysign(double _Number,double _Sign)

{
  return (double)CONCAT44((_Sign._4_4_ ^ _Number._4_4_) & 0x7fffffff ^ _Sign._4_4_,SUB84(_Number,0))
  ;
}


