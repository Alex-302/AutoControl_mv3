// FUN_004082c0 @ 004082c0 size=832 callers=1

uint * __fastcall FUN_004082c0(uint *param_1,HANDLE param_2,undefined4 param_3,short *param_4)

{
  short sVar1;
  short sVar2;
  uint *puVar3;
  uint *puVar4;
  short sVar5;
  byte bVar6;
  uint uVar7;
  uint uVar8;
  HANDLE *ppvVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  ushort uVar14;
  uint uVar15;
  HANDLE *local_38;
  HANDLE *local_34;
  uint local_30;
  int local_2c;
  short *local_28;
  uint local_24;
  int local_20;
  uint local_1c;
  HANDLE local_18;
  char local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00479885;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_18 = param_2;
  if ((*(int *)(*(int *)ThreadLocalStoragePointer + 8) < DAT_004a2e98) &&
     (ExceptionList = &local_10, FUN_0045a219(&DAT_004a2e98), DAT_004a2e98 == -1)) {
    local_8 = 1;
    local_38 = (HANDLE *)0x0;
    FUN_00436be0(&local_38);
    _atexit(thunk_FUN_00432cc0);
    FUN_0045a1da(&DAT_004a2e98);
  }
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  local_8 = 0;
  FUN_00436b40(&local_38,(byte *)&local_18);
  if (local_38 == DAT_004a2a64) {
    bVar6 = FUN_00407bc0(local_18);
    FUN_00436b40(&local_38,(byte *)&local_18);
    ppvVar9 = local_38;
    if (local_38 == DAT_004a2a64) {
      local_38 = &local_18;
      FUN_0044a730(ppvVar9,(int *)&local_34,ppvVar9,&local_38);
      local_38 = local_34;
    }
    *(byte *)(local_38 + 3) = bVar6;
  }
  else {
    bVar6 = *(byte *)(local_38 + 3);
  }
  if (bVar6 < 8) {
    local_2c = (int)(char)bVar6;
    iVar11 = 0;
    local_28 = param_4 + 0xb;
    uVar10 = local_2c * 0x3c + 0x20U | 0x200;
    local_30 = (int)&DAT_004a2e66 - (int)local_28;
    local_24 = uVar10;
    do {
      local_11 = ((char *)((int)local_28 + iVar11))[local_30];
      if (local_11 != *(char *)((int)local_28 + iVar11)) {
        uVar10 = uVar10 + iVar11;
        uVar8 = uVar10 & 0xffff;
        local_1c = DAT_004a28b0;
        DAT_004a23a2 = (*(uint *)(DAT_004a28b0 + (uVar8 >> 5) * 4) & 1 << ((byte)uVar8 & 0x1f)) != 0
        ;
        uVar7 = *(uint *)(DAT_004a28b0 + (uVar8 >> 5) * 4);
        if (local_11 == '\0') {
          uVar7 = uVar7 & ~(1 << (uVar10 & 0x1f));
        }
        else {
          uVar7 = uVar7 | 1 << (uVar10 & 0x1f);
        }
        *(uint *)(DAT_004a28b0 + (uVar8 >> 5) * 4) = uVar7;
        (&DAT_004a26ba)[local_2c] = (&DAT_004a26ba)[local_2c] + (local_11 != '\0') * '\x02' + -1;
        uVar14 = 0x400;
        if (local_11 != '\0') {
          uVar14 = 0;
        }
        local_38._0_2_ = (ushort)uVar10;
        local_38 = (HANDLE *)(uint)(uVar14 | (ushort)local_38);
        FUN_00433540(param_1,(undefined2 *)&local_38);
        uVar10 = local_24;
      }
      iVar11 = iVar11 + 1;
    } while (iVar11 < 0x20);
    local_20 = 0;
    ppvVar9 = (HANDLE *)((int)&DAT_004a2e50 - (int)param_4);
    local_38 = ppvVar9;
    do {
      sVar1 = *(short *)((int)ppvVar9 + (int)param_4);
      sVar2 = *param_4;
      if (sVar1 != sVar2) {
        sVar5 = sVar1;
        if (sVar1 == 0) {
          sVar5 = sVar2;
        }
        uVar7 = local_24 + local_20 * 2 + ((sVar1 != 0 || sVar2 != 0) && -1 < sVar5) + 0x20;
        uVar8 = uVar7 & 0xffff;
        uVar10 = (int)sVar2 >> 0x1f;
        iVar11 = ((int)sVar2 ^ uVar10) - uVar10;
        uVar10 = (int)sVar1 >> 0x1f;
        iVar12 = ((int)sVar1 ^ uVar10) - uVar10;
        iVar13 = iVar12 - iVar11;
        uVar15 = uVar7 & 0x1f;
        local_28 = (short *)DAT_004a28b0;
        uVar10 = *(uint *)(DAT_004a28b0 + (uVar8 >> 5) * 4);
        DAT_004a23a2 = (uVar10 & 1 << (sbyte)uVar15) != 0;
        if ((bool)DAT_004a23a2 != 0 < iVar13) {
          if (iVar13 < 1) {
            uVar10 = uVar10 & ~(1 << uVar15);
          }
          else {
            uVar10 = uVar10 | 1 << uVar15;
          }
          *(uint *)(DAT_004a28b0 + (uVar8 >> 5) * 4) = uVar10;
          (&DAT_004a26ba)[local_2c] = (&DAT_004a26ba)[local_2c] + (0 < iVar13) * '\x02' + -1;
        }
        uVar14 = 0x400;
        if (iVar12 != iVar11 && -1 < iVar13) {
          uVar14 = 0;
        }
        local_30._0_2_ = (ushort)uVar7;
        uVar14 = uVar14 | (ushort)local_30;
        local_1c = (uint)uVar14;
        puVar3 = (uint *)param_1[1];
        local_30 = uVar8;
        if (&local_1c < puVar3) {
          puVar4 = (uint *)*param_1;
          if (&local_1c < puVar4) goto LAB_004085b6;
          if (puVar3 == (uint *)param_1[2]) {
            FUN_004375a0((int *)param_1);
          }
          if ((undefined2 *)param_1[1] != (undefined2 *)0x0) {
            *(undefined2 *)param_1[1] =
                 *(undefined2 *)(*param_1 + ((int)&local_1c - (int)puVar4 >> 1) * 2);
          }
        }
        else {
LAB_004085b6:
          if (puVar3 == (uint *)param_1[2]) {
            FUN_004375a0((int *)param_1);
          }
          if ((ushort *)param_1[1] != (ushort *)0x0) {
            *(ushort *)param_1[1] = uVar14;
          }
        }
        param_1[1] = param_1[1] + 2;
        ppvVar9 = local_38;
      }
      local_20 = local_20 + 1;
      param_4 = param_4 + 1;
    } while (local_20 < 0xb);
  }
  ExceptionList = local_10;
  return param_1;
}


