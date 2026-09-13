// ___scrt_acquire_startup_lock @ 0045a47b size=53 callers=1

/* Library Function - Single Match
    ___scrt_acquire_startup_lock
   
   Library: Visual Studio 2015 Release */

int ___scrt_acquire_startup_lock(void)

{
  int iVar1;
  bool bVar2;
  uint3 extraout_var;
  int iVar3;
  
  bVar2 = ___scrt_is_ucrt_dll_in_use();
  if (CONCAT31(extraout_var,bVar2) == 0) {
    return (uint)extraout_var << 8;
  }
  while( true ) {
    iVar3 = 0;
    LOCK();
    iVar1 = *(int *)((int)Self + 4);
    if (DAT_0049f13c != 0) {
      iVar3 = DAT_0049f13c;
      iVar1 = DAT_0049f13c;
    }
    DAT_0049f13c = iVar1;
    UNLOCK();
    if (iVar3 == 0) break;
    if (*(int *)((int)Self + 4) == iVar3) {
      return CONCAT31((int3)((uint)iVar3 >> 8),1);
    }
  }
  return 0;
}


