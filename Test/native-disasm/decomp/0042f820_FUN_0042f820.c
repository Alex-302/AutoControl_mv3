// FUN_0042f820 @ 0042f820 size=608 callers=1

undefined1 * __cdecl FUN_0042f820(undefined1 *param_1,void *param_2)

{
  uint *puVar1;
  char *pcVar2;
  uint uVar3;
  HWND pHVar4;
  byte *pbVar5;
  uint uVar6;
  undefined1 *puVar7;
  int *piVar8;
  uint uVar9;
  undefined **local_64;
  undefined8 local_60;
  uint local_58;
  undefined ***local_40;
  void *local_3c [2];
  char local_34 [4];
  uint local_30;
  uint uStack_2c;
  uint local_28;
  undefined4 local_20;
  uint local_1c;
  uint local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047d4a0;
  local_10 = ExceptionList;
  local_20 = 0;
  ExceptionList = &local_10;
  pcVar2 = (char *)FUN_00440e70(param_2,(uint *)"callback");
  FUN_00453810(pcVar2,&local_14);
  local_28 = 0xf;
  uStack_2c = 0;
  local_3c[0] = (void *)((uint)local_3c[0] & 0xffffff00);
  FUN_0043ace0(local_3c,(uint *)"timeout",7);
  local_8 = 0;
  uVar3 = FUN_004409d0(param_2,local_3c,500);
  local_8 = 0xffffffff;
  if (0xf < local_28) {
    FUN_00402430(local_3c[0],local_28 + 1,1);
  }
  local_28 = 0xf;
  uStack_2c = 0;
  local_3c[0] = (void *)((uint)local_3c[0] & 0xffffff00);
  FUN_0043ace0(local_3c,(uint *)"format",6);
  local_8 = 1;
  local_18 = FUN_004409d0(param_2,local_3c,1);
  local_8 = 0xffffffff;
  if (0xf < local_28) {
    FUN_00402430(local_3c[0],local_28 + 1,1);
  }
  pHVar4 = GetForegroundWindow();
  pbVar5 = (byte *)FUN_00404670((int *)local_3c,pHVar4);
  puVar1 = (uint *)(pbVar5 + 0x10);
  if (0xf < *(uint *)(pbVar5 + 0x14)) {
    pbVar5 = *(byte **)pbVar5;
  }
  uVar9 = *puVar1;
  uVar6 = 0x12;
  if (uVar9 < 0x12) {
    uVar6 = uVar9;
  }
  uVar6 = FUN_004023d0(pbVar5,(byte *)"ConsoleWindowClass",uVar6);
  if (uVar6 == 0) {
    if (uVar9 < 0x12) {
      uVar6 = 0xffffffff;
    }
    else {
      uVar6 = (uint)(0x12 < uVar9);
    }
  }
  if (0xf < local_28) {
    FUN_00402430(local_3c[0],local_28 + 1,1);
  }
  if (uVar6 == 0) {
    puVar7 = FUN_00434a40(local_34,(char *)0x0,(char *)0x0);
    local_8 = 2;
    FUN_00408760(local_14,puVar7);
    FUN_00434820(local_34);
    local_1c = local_1c & 0xffffff00;
    *(undefined8 *)(param_1 + 8) = 0;
    *(uint *)(param_1 + 8) = local_1c;
    *param_1 = 4;
    *(uint *)(param_1 + 0xc) = local_18;
    ExceptionList = local_10;
    return param_1;
  }
  if (uVar3 != 0) {
    uVar9 = 0;
    do {
      if (DAT_004a24f4 == 0) break;
      Sleep(100);
      uVar9 = uVar9 + 100;
    } while (uVar9 < uVar3);
  }
  local_30 = local_14;
  local_60 = CONCAT44(uVar3,local_14);
  local_58 = local_18;
  local_40 = &local_64;
  local_64 = &PTR_LAB_0048e4f0;
  local_8 = 3;
  uStack_2c = uVar3;
  piVar8 = FUN_0040f6b0(DAT_004a23dc,(int *)local_40,0);
  *(undefined8 *)(param_1 + 8) = 0;
  local_1c = CONCAT31(local_1c._1_3_,piVar8 != (int *)0x0);
  *(uint *)(param_1 + 8) = local_1c;
  *param_1 = 4;
  *(uint *)(param_1 + 0xc) = local_18;
  if (local_40 != (undefined ***)0x0) {
    (*(code *)(*local_40)[4])(local_40 != &local_64);
  }
  ExceptionList = local_10;
  return param_1;
}


