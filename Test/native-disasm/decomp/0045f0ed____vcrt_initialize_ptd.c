// ___vcrt_initialize_ptd @ 0045f0ed size=51 callers=1

/* Library Function - Single Match
    ___vcrt_initialize_ptd
   
   Library: Visual Studio 2015 Release */

uint ___vcrt_initialize_ptd(void)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = ___vcrt_FlsAlloc(FUN_0045f031);
  DAT_0049d0b0 = uVar1;
  if (uVar1 != 0xffffffff) {
    iVar2 = ___vcrt_FlsSetValue(uVar1,&DAT_0049f4d8);
    if (iVar2 != 0) {
      return CONCAT31((int3)((uint)iVar2 >> 8),1);
    }
    uVar1 = ___vcrt_uninitialize_ptd();
  }
  return uVar1 & 0xffffff00;
}


