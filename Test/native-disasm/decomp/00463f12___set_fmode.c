// __set_fmode @ 00463f12 size=61 callers=1

/* Library Function - Single Match
    __set_fmode
   
   Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release */

errno_t __cdecl __set_fmode(int _Mode)

{
  int *piVar1;
  
  if (((_Mode != 0x4000) && (_Mode != 0x8000)) && (_Mode != 0x10000)) {
    piVar1 = __errno();
    *piVar1 = 0x16;
    FUN_00465fa2();
    return 0x16;
  }
  LOCK();
  DAT_0049fb00 = _Mode;
  UNLOCK();
  return 0;
}


