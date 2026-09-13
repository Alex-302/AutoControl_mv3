// FUN_00430a30 @ 00430a30 size=61 callers=1

undefined4 FUN_00430a30(void)

{
  int iVar1;
  
  LOCK();
  UNLOCK();
  iVar1 = DAT_004a2464 + 1;
  *(int *)(*(int *)ThreadLocalStoragePointer + 4) = DAT_004a2464;
  DAT_004a2464 = iVar1;
  Sleep(100);
  FUN_00409120();
  PostThreadMessageA(DAT_004a245c,0x12,0,0);
  return 0;
}


