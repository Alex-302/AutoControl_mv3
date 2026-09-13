// FUN_00466551 @ 00466551 size=49 callers=2

undefined4 FUN_00466551(void)

{
  undefined4 in_EAX;
  undefined4 extraout_EAX;
  int iVar1;
  LPCRITICAL_SECTION lpCriticalSection;
  
  if (DAT_0049f6a8 != 0) {
    lpCriticalSection = (LPCRITICAL_SECTION)(&DAT_0049f558 + DAT_0049f6a8 * 6);
    iVar1 = DAT_0049f6a8;
    do {
      DeleteCriticalSection(lpCriticalSection);
      DAT_0049f6a8 = DAT_0049f6a8 + -1;
      lpCriticalSection = lpCriticalSection + -1;
      iVar1 = iVar1 + -1;
      in_EAX = extraout_EAX;
    } while (iVar1 != 0);
  }
  return CONCAT31((int3)((uint)in_EAX >> 8),1);
}


