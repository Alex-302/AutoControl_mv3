// FUN_004523a0 @ 004523a0 size=437 callers=1

byte __fastcall FUN_004523a0(int *param_1,undefined4 param_2,int param_3,char param_4,int param_5)

{
  bool bVar1;
  byte bVar2;
  undefined4 uVar3;
  uint *extraout_EDX;
  uint *extraout_EDX_00;
  uint *puVar4;
  undefined8 uVar5;
  uint *puVar6;
  int local_40;
  int local_3c [3];
  int local_30;
  int local_2c [3];
  int local_20;
  int *local_1c;
  int *local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047e930;
  local_10 = ExceptionList;
  if (*(int *)(param_3 + 0x24) == 1) {
    ExceptionList = &local_10;
    bVar2 = FUN_00454620(param_1,param_2,param_3,param_4);
    ExceptionList = local_10;
    return bVar2;
  }
  local_40 = *param_1;
  ExceptionList = &local_10;
  uVar5 = FUN_00450ec0(local_3c,param_2,param_1 + 1);
  local_30 = param_1[4];
  local_8 = 0;
  FUN_004534b0(local_2c,(int)((ulonglong)uVar5 >> 0x20),param_1 + 5);
  local_8 = 1;
  local_14 = *param_1;
  local_18 = (int *)(param_1[0x10] + *(int *)(param_3 + 0x20) * 8);
  local_20 = *local_18;
  local_1c = (int *)local_18[1];
  if ((param_5 == 0) || (*local_1c != local_14)) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  bVar2 = 0;
  puVar4 = *(uint **)(param_3 + 0x18);
  if (((int)puVar4 < 0) || (param_5 < (int)puVar4)) {
    if (param_5 < *(int *)(param_3 + 0x14)) {
      if (!bVar1) goto LAB_004524f4;
      *local_18 = param_5 + 1;
      local_18[1] = (int)&local_14;
      puVar6 = *(uint **)(param_3 + 0xc);
      goto LAB_004524fa;
    }
    if (param_4 != '\0') {
      if (bVar1) {
        *local_18 = param_5 + 1;
        local_18[1] = (int)&local_14;
        uVar3 = FUN_0044e860(param_1,puVar4,*(uint **)(param_3 + 0xc));
        bVar2 = (byte)uVar3;
        if (bVar2 != 0) goto LAB_0045252a;
      }
      else if (1 < param_5) goto LAB_00452507;
      *local_18 = local_20;
      local_18[1] = (int)local_1c;
      FUN_004506b0(param_1,&local_40);
      puVar4 = extraout_EDX_00;
      goto LAB_004524f4;
    }
    uVar3 = FUN_0044e860(param_1,puVar4,*(uint **)(*(int *)(param_3 + 0x1c) + 0xc));
    bVar2 = (byte)uVar3;
    if (bVar2 != 0) goto LAB_0045252a;
    if (bVar1) {
      FUN_004506b0(param_1,&local_40);
      *local_18 = param_5 + 1;
      local_18[1] = (int)&local_14;
      puVar6 = *(uint **)(param_3 + 0xc);
      puVar4 = extraout_EDX;
      goto LAB_004524fa;
    }
  }
  else {
LAB_004524f4:
    puVar6 = *(uint **)(*(int *)(param_3 + 0x1c) + 0xc);
LAB_004524fa:
    uVar3 = FUN_0044e860(param_1,puVar4,puVar6);
    bVar2 = (byte)uVar3;
    if (bVar2 != 0) goto LAB_0045252a;
  }
LAB_00452507:
  *param_1 = local_40;
  param_1[4] = local_30;
  FUN_00450dd0(param_1 + 1,local_3c);
  FUN_004506f0(param_1 + 5,local_2c);
LAB_0045252a:
  *local_18 = local_20;
  local_18[1] = (int)local_1c;
  FUN_00448330((int)&local_40);
  ExceptionList = local_10;
  return bVar2;
}


