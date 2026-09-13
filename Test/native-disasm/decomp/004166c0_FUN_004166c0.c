// FUN_004166c0 @ 004166c0 size=274 callers=3

void FUN_004166c0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
  int iVar1;
  undefined4 *puVar2;
  
  if (*(int *)(*(int *)ThreadLocalStoragePointer + 8) < DAT_004a2a80) {
    FUN_0045a219(&DAT_004a2a80);
    if (DAT_004a2a80 == -1) {
      _atexit(FUN_0047f480);
      FUN_0045a1da(&DAT_004a2a80);
    }
  }
  if (DAT_004a334c == DAT_004a3350) {
    FUN_00443c10();
  }
  puVar2 = DAT_004a334c;
  if (DAT_004a334c != (undefined4 *)0x0) {
    *DAT_004a334c = param_2;
    puVar2[1] = param_3;
    puVar2[2] = param_4;
    puVar2[3] = param_5;
    puVar2[4] = param_7;
  }
  DAT_004a334c = DAT_004a334c + 5;
  if ((uint)((int)DAT_004a334c + (-0x14 - (int)DAT_004a3348)) < 0x14) {
    do {
      FUN_00416270(DAT_004a3348);
      FUN_0045b0e0(DAT_004a3348,DAT_004a3348 + 5,(int)DAT_004a334c - (int)(DAT_004a3348 + 5));
      DAT_004a334c = DAT_004a334c + -5;
      iVar1 = (int)DAT_004a334c - (int)DAT_004a3348 >> 0x1f;
    } while (((int)DAT_004a334c - (int)DAT_004a3348) / 0x14 + iVar1 != iVar1);
  }
  return;
}


