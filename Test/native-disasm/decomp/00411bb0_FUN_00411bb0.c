// FUN_00411bb0 @ 00411bb0 size=787 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00411bb0(int param_1)

{
  int *piVar1;
  ushort uVar2;
  int *piVar3;
  int iVar4;
  int *piVar5;
  DWORD DVar6;
  uint uVar7;
  undefined4 *puVar8;
  byte *pbVar9;
  undefined4 *puVar10;
  undefined1 local_15c [128];
  undefined4 local_dc [32];
  char local_5c [8];
  undefined1 local_54 [8];
  void *local_4c [4];
  undefined4 local_3c;
  uint local_38;
  undefined4 local_34;
  undefined4 local_24;
  uint local_20;
  undefined4 *local_1c;
  undefined4 *local_18;
  undefined4 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047aa36;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  piVar3 = FUN_0040b2d0((int *)&local_14);
  piVar1 = (int *)(param_1 + 0xc0);
  if (piVar1 != piVar3) {
    iVar4 = *piVar3;
    *piVar3 = 0;
    local_18 = (undefined4 *)*piVar1;
    *piVar1 = iVar4;
    if (local_18 != (undefined4 *)0x0) {
      GdipDeleteFont(*local_18);
      GdipFree(local_18);
    }
  }
  local_18 = local_14;
  if (local_14 != (undefined4 *)0x0) {
    GdipDeleteFont(*local_14);
    GdipFree(local_18);
  }
  local_14 = (undefined4 *)*piVar1;
  iVar4 = GdipGetFontSize(*local_14,&local_18);
  if (iVar4 != 0) {
    local_14[1] = iVar4;
  }
  local_14 = local_18;
  piVar5 = FUN_00441b30(&local_1c);
  piVar3 = (int *)(param_1 + 0xc4);
  if (piVar3 != piVar5) {
    iVar4 = *piVar5;
    *piVar5 = 0;
    local_14 = (undefined4 *)*piVar3;
    *piVar3 = iVar4;
    if (local_14 != (undefined4 *)0x0) {
      GdipDeleteFont(*local_14);
      GdipFree(local_14);
    }
  }
  local_14 = local_1c;
  if (local_1c != (undefined4 *)0x0) {
    GdipDeleteFont(*local_1c);
    GdipFree(local_14);
  }
  iVar4 = FUN_0040b420((undefined4 *)*piVar1);
  uVar2 = (ushort)iVar4;
  *(ushort *)(param_1 + 0xea) = uVar2;
  if (uVar2 < 0x10) {
    uVar2 = 0x10;
  }
  *(ushort *)(param_1 + 0xe8) = uVar2;
  iVar4 = GetSystemMetrics(0x47);
  *(short *)(param_1 + 0xec) = (short)iVar4;
  local_20 = 7;
  local_24 = 0;
  local_34 = (void *)((uint)local_34._2_2_ << 0x10);
  FUN_0043a650(&local_34,(uint *)&DAT_0048eb40,1);
  iVar4 = FUN_0040b4b0(&local_34,DAT_004a29a4);
  *(short *)(param_1 + 0xee) = (short)(int)((double)iVar4 * _DAT_0048f240);
  if (7 < local_20) {
    FUN_00402430(local_34,local_20 + 1,2);
  }
  DVar6 = GetSysColor(7);
  *(DWORD *)(param_1 + 200) =
       ((DVar6 & 0xff | 0xffffff00) << 8 | DVar6 >> 8 & 0xff) << 8 | DVar6 >> 0x10 & 0xff;
  DVar6 = GetSysColor(4);
  *(DWORD *)(param_1 + 0xcc) =
       ((DVar6 & 0xff | 0xffffff00) << 8 | DVar6 >> 8 & 0xff) << 8 | DVar6 >> 0x10 & 0xff;
  DVar6 = GetSysColor(0xe);
  *(DWORD *)(param_1 + 0xd0) =
       ((DVar6 & 0xff | 0xffffff00) << 8 | DVar6 >> 8 & 0xff) << 8 | DVar6 >> 0x10 & 0xff;
  DVar6 = GetSysColor(0xd);
  *(DWORD *)(param_1 + 0xd4) =
       ((DVar6 & 0xff | 0xffffff00) << 8 | DVar6 >> 8 & 0xff) << 8 | DVar6 >> 0x10 & 0xff;
  DVar6 = GetSysColor(0x11);
  local_38 = 0xf;
  *(DWORD *)(param_1 + 0xd8) =
       ((DVar6 & 0xff | 0xffffff00) << 8 | DVar6 >> 8 & 0xff) << 8 | DVar6 >> 0x10 & 0xff;
  uVar7 = 9;
  local_3c = 0;
  if (s__default__0048d508[0] == '\0') {
    uVar7 = 0;
  }
  local_4c[0] = (void *)((uint)local_4c[0] & 0xffffff00);
  FUN_0043ace0(local_4c,(uint *)"_default_",uVar7);
  local_8 = 1;
  local_5c[0] = '\0';
  FUN_004381d0(local_54,'\0');
  local_8 = CONCAT31(local_8._1_3_,2);
  puVar8 = FUN_004123b0(local_15c,local_5c);
  puVar10 = local_dc;
  for (iVar4 = 0x20; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar10 = *puVar8;
    puVar8 = puVar8 + 1;
    puVar10 = puVar10 + 1;
  }
  pbVar9 = FUN_00432630((void *)(param_1 + 0x8c),(byte *)local_4c);
  puVar8 = local_dc;
  for (iVar4 = 0x20; iVar4 != 0; iVar4 = iVar4 + -1) {
    *(undefined4 *)pbVar9 = *puVar8;
    puVar8 = puVar8 + 1;
    pbVar9 = pbVar9 + 4;
  }
  FUN_00434820(local_5c);
  if (0xf < local_38) {
    FUN_00402430(local_4c[0],local_38 + 1,1);
  }
  ExceptionList = local_10;
  return;
}


