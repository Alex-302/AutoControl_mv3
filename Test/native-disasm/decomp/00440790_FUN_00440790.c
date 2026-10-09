// FUN_00440790 @ 00440790 size=94 callers=3

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined * FUN_00440790(void)

{
  if (*(int *)(*(int *)ThreadLocalStoragePointer + 8) < DAT_004a32f8) {
    FUN_0045a219(&DAT_004a32f8);
    if (DAT_004a32f8 == -1) {
      _DAT_004a2fb8 = &PTR_LAB_0048e568;
      _DAT_004a2fbc = 5;
      _atexit(FUN_0047f770);
      FUN_0045a1da(&DAT_004a32f8);
    }
  }
  return &DAT_004a2fb8;
}


