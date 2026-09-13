// ___vcrt_initialize @ 0045ef74 size=41 callers=1

/* Library Function - Single Match
    ___vcrt_initialize
   
   Library: Visual Studio 2015 Release */

uint ___vcrt_initialize(void)

{
  uint uVar1;
  undefined4 uVar2;
  
  ___vcrt_initialize_pure_virtual_call_handler();
  ___vcrt_initialize_winapi_thunks();
  uVar1 = ___vcrt_initialize_locks();
  if ((char)uVar1 != '\0') {
    uVar2 = ___vcrt_initialize_ptd();
    if ((char)uVar2 != '\0') {
      return CONCAT31((int3)((uint)uVar2 >> 8),1);
    }
    uVar1 = ___vcrt_uninitialize_locks();
  }
  return uVar1 & 0xffffff00;
}


