// __configthreadlocale @ 004680ca size=98 callers=1

/* Library Function - Single Match
    __configthreadlocale
   
   Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release */

int __cdecl __configthreadlocale(int _Flag)

{
  uint uVar1;
  __acrt_ptd *p_Var2;
  int *piVar3;
  uint uVar4;
  
  p_Var2 = FUN_0046aa74();
  uVar1 = *(uint *)(p_Var2 + 0x350);
  if (_Flag == -1) {
    DAT_0049d3f8 = 0xffffffff;
  }
  else if (_Flag != 0) {
    if (_Flag == 1) {
      uVar4 = uVar1 | 2;
    }
    else {
      if (_Flag != 2) {
        piVar3 = __errno();
        *piVar3 = 0x16;
        FUN_00465fa2();
        return -1;
      }
      uVar4 = uVar1 & 0xfffffffd;
    }
    *(uint *)(p_Var2 + 0x350) = uVar4;
  }
  return ((uVar1 & 2) == 0) + 1;
}


