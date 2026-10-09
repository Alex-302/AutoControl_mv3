// FUN_0040c5e0 @ 0040c5e0 size=422 callers=1

uint * __fastcall FUN_0040c5e0(uint *param_1)

{
  ushort uVar1;
  uint *puVar2;
  uint *puVar3;
  SHORT SVar4;
  uint uVar5;
  uint vKey;
  uint local_2c [4];
  uint *local_1c;
  undefined4 local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00479fd5;
  local_10 = ExceptionList;
  local_18 = 0;
  ExceptionList = &local_10;
  local_1c = param_1;
  if (*(int *)(*(int *)ThreadLocalStoragePointer + 8) < DAT_004a3304) {
    ExceptionList = &local_10;
    FUN_0045a219(&DAT_004a3304);
    if (DAT_004a3304 == -1) {
      local_8 = 1;
      local_14 = local_14 & 0xffffff00;
      local_2c[0] = 0x5c005b;
      local_2c[1] = 0xa100a0;
      local_2c[2] = 0xa300a2;
      local_2c[3] = 0xa500a4;
      FUN_004473e0(local_2c,(int)&local_1c);
      _atexit(FUN_0047f200);
      FUN_0045a1da(&DAT_004a3304);
    }
  }
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  local_8 = 0;
  uVar5 = 0;
  local_18 = 1;
  if (DAT_004a3374 - DAT_004a3370 >> 1 != 0) {
    do {
      uVar1 = *(ushort *)(DAT_004a3370 + uVar5 * 2);
      vKey = (uint)uVar1;
      local_14 = vKey;
      SVar4 = GetAsyncKeyState(vKey);
      if (SVar4 < 0) {
        if ((((uVar1 == 0xa1) || (uVar1 == 0xa3)) || (uVar1 == 0xa5)) ||
           ((vKey == 0x5b || (vKey == 0x5c)))) {
          vKey = vKey | 0x100;
          local_14 = vKey;
        }
        puVar2 = (uint *)param_1[1];
        if (&local_14 < puVar2) {
          puVar3 = (uint *)*param_1;
          if (&local_14 < puVar3) goto LAB_0040c740;
          if (puVar2 == (uint *)param_1[2]) {
            FUN_004375a0((int *)param_1);
          }
          if ((undefined2 *)param_1[1] != (undefined2 *)0x0) {
            *(undefined2 *)param_1[1] =
                 *(undefined2 *)(*param_1 + ((int)&local_14 - (int)puVar3 >> 1) * 2);
          }
        }
        else {
LAB_0040c740:
          if (puVar2 == (uint *)param_1[2]) {
            FUN_004375a0((int *)param_1);
          }
          if ((undefined2 *)param_1[1] != (undefined2 *)0x0) {
            *(undefined2 *)param_1[1] = (short)vKey;
          }
        }
        param_1[1] = param_1[1] + 2;
      }
      uVar5 = uVar5 + 1;
    } while (uVar5 < (uint)(DAT_004a3374 - DAT_004a3370 >> 1));
  }
  ExceptionList = local_10;
  return param_1;
}


