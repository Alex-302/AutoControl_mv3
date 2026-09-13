// __set_new_mode @ 00468de3 size=47 callers=1

/* Library Function - Single Match
    __set_new_mode
   
   Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release */

undefined4 __cdecl __set_new_mode(int param_1)

{
  undefined4 uVar1;
  int *piVar2;
  
  uVar1 = DAT_0049f7f8;
  if ((param_1 != 0) && (param_1 != 1)) {
    piVar2 = __errno();
    *piVar2 = 0x16;
    FUN_00465fa2();
    return 0xffffffff;
  }
  LOCK();
  DAT_0049f7f8 = param_1;
  UNLOCK();
  return uVar1;
}


