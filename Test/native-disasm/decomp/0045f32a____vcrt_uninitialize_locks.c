// ___vcrt_uninitialize_locks @ 0045f32a size=47 callers=3

/* Library Function - Single Match
    ___vcrt_uninitialize_locks
   
   Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release */

undefined4 ___vcrt_uninitialize_locks(void)

{
  undefined4 in_EAX;
  undefined4 extraout_EAX;
  int iVar1;
  LPCRITICAL_SECTION lpCriticalSection;
  
  if (DAT_0049f518 != 0) {
    lpCriticalSection = (LPCRITICAL_SECTION)(&DAT_0049f4e8 + DAT_0049f518 * 0x18);
    iVar1 = DAT_0049f518;
    do {
      DeleteCriticalSection(lpCriticalSection);
      DAT_0049f518 = DAT_0049f518 + -1;
      lpCriticalSection = lpCriticalSection + -1;
      iVar1 = iVar1 + -1;
      in_EAX = extraout_EAX;
    } while (iVar1 != 0);
  }
  return CONCAT31((int3)((uint)in_EAX >> 8),1);
}


