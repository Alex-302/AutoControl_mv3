// __fpclass @ 0046c6f6 size=164 callers=1

/* Library Function - Single Match
    __fpclass
   
   Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release */

int __cdecl __fpclass(double _X)

{
  int iVar1;
  
  if ((_X._6_2_ & 0x7ff0) == 0x7ff0) {
    iVar1 = __sptype(_X._0_4_,(uint)((ulonglong)_X >> 0x20));
    if (iVar1 == 1) {
      return 0x200;
    }
    if (iVar1 == 2) {
      iVar1 = 4;
    }
    else {
      if (iVar1 != 3) {
        return 1;
      }
      iVar1 = 2;
    }
    return iVar1;
  }
  if ((((ulonglong)_X & 0x7ff0000000000000) == 0) &&
     ((((ulonglong)_X & 0xfffff00000000) != 0 || (_X._0_4_ != 0)))) {
    return (-(uint)(((ulonglong)_X & 0x8000000000000000) != 0) & 0xffffff90) + 0x80;
  }
  if (_X == 0.0) {
    return (-(uint)(((ulonglong)_X & 0x8000000000000000) != 0) & 0xffffffe0) + 0x40;
  }
  return (-(uint)(((ulonglong)_X & 0x8000000000000000) != 0) & 0xffffff08) + 0x100;
}


