// FUN_00416d60 @ 00416d60 size=192 callers=2

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_00416d60(int param_1)

{
  int cFormats;
  int iVar1;
  
  if (*(int *)(*(int *)ThreadLocalStoragePointer + 8) < DAT_004a2e94) {
    FUN_0045a219(&DAT_004a2e94);
    if (DAT_004a2e94 == -1) {
      _DAT_0049d9d0 = DAT_004a26f4;
      _DAT_0049d9d4 = 0xf;
      _DAT_0049d9d8 = 0xd;
      _DAT_0049d9dc = 1;
      FUN_0045a1da(&DAT_004a2e94);
    }
  }
  if (param_1 != DAT_004a26f4) {
    iVar1 = 2;
    if (param_1 != 1) {
      iVar1 = 0;
    }
    cFormats = (uint)(param_1 != 1) * 2 + 3;
    if (param_1 != 0x5b) goto LAB_00416da7;
  }
  iVar1 = 1;
  cFormats = 1;
LAB_00416da7:
  iVar1 = GetPriorityClipboardFormat((UINT *)(&DAT_0049d9cc + iVar1 * 4),cFormats);
  if (0 < iVar1) {
    if (iVar1 == DAT_004a26f4) {
      iVar1 = 0x5b;
    }
    return iVar1;
  }
  return 0;
}


