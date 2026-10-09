// FID_conflict:__dtest @ 0045f71f size=100 callers=2

/* Library Function - Multiple Matches With Different Base Names
    __Dtest
    __dtest
   
   Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release */

short __cdecl FID_conflict___dtest(double *param_1)

{
  ushort uVar1;
  
  uVar1 = *(ushort *)((int)param_1 + 6);
  if ((uVar1 & 0x7ff0) == 0x7ff0) {
    if ((((uVar1 & 0xf) == 0) && (*(short *)((int)param_1 + 4) == 0)) &&
       ((*(short *)((int)param_1 + 2) == 0 && (*(short *)param_1 == 0)))) {
      return 1;
    }
    return 2;
  }
  if (((((uVar1 & 0x7fff) == 0) && (*(short *)((int)param_1 + 4) == 0)) &&
      (*(short *)((int)param_1 + 2) == 0)) && (*(short *)param_1 == 0)) {
    return 0;
  }
  return ((uVar1 & 0x7ff0) != 0) - 2;
}


