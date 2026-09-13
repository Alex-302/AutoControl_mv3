// FUN_00454620 @ 00454620 size=882 callers=1

char __fastcall FUN_00454620(int *param_1,undefined4 param_2,int param_3,char param_4)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  void *pvVar4;
  uint *puVar5;
  uint *extraout_EDX;
  uint *extraout_EDX_00;
  uint *extraout_EDX_01;
  int iVar6;
  int iVar7;
  int *piVar8;
  undefined8 uVar9;
  int local_58;
  void *local_54 [2];
  int local_4c;
  int local_48;
  void *local_44 [2];
  int local_3c;
  int local_38;
  void *local_34 [2];
  int local_2c;
  int local_28;
  void *local_24 [2];
  int local_1c;
  int local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  iVar1 = param_3;
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047ea20;
  local_10 = ExceptionList;
  iVar6 = 0;
  local_58 = *param_1;
  ExceptionList = &local_10;
  uVar9 = FUN_00450ec0((int *)local_54,param_2,param_1 + 1);
  local_48 = param_1[4];
  local_8 = 0;
  uVar9 = FUN_004534b0((int *)local_44,(int)((ulonglong)uVar9 >> 0x20),param_1 + 5);
  puVar5 = (uint *)((ulonglong)uVar9 >> 0x20);
  local_8 = 1;
  if (0 < *(int *)(param_3 + 0x14)) {
    do {
      iVar7 = *param_1;
      uVar2 = FUN_0044e860(param_1,puVar5,*(uint **)(param_3 + 0xc));
      if ((char)uVar2 == '\0') {
        *param_1 = local_58;
        param_1[4] = local_48;
        FUN_00450dd0(param_1 + 1,(int *)local_54);
        FUN_004506f0(param_1 + 5,(int *)local_44);
        param_3._3_1_ = '\0';
        goto LAB_004548c5;
      }
      if (iVar7 == *param_1) {
        iVar6 = *(int *)(param_3 + 0x14) + -1;
      }
      iVar6 = iVar6 + 1;
      puVar5 = extraout_EDX;
    } while (iVar6 < *(int *)(param_3 + 0x14));
  }
  local_38 = *param_1;
  uVar9 = FUN_00450ec0((int *)local_34,puVar5,param_1 + 1);
  local_28 = param_1[4];
  local_8._0_1_ = 2;
  uVar9 = FUN_004534b0((int *)local_24,(int)((ulonglong)uVar9 >> 0x20),param_1 + 5);
  local_8 = CONCAT31(local_8._1_3_,3);
  local_14 = *param_1;
  param_3 = 0;
  uVar2 = FUN_0044e860(param_1,(uint *)((ulonglong)uVar9 >> 0x20),
                       *(uint **)(*(int *)(iVar1 + 0x1c) + 0xc));
  if ((char)uVar2 != '\0') {
    if (param_4 == '\0') {
LAB_004547d9:
      param_3._3_1_ = '\x01';
      goto LAB_0045480d;
    }
    local_38 = *param_1;
    local_28 = param_1[4];
    FUN_00450dd0(local_34,param_1 + 1);
    FUN_004506f0(local_24,param_1 + 5);
    param_3 = 0x1000000;
  }
  while( true ) {
    iVar7 = iVar6;
    if ((*(int *)(iVar1 + 0x18) != -1) && (iVar7 = iVar6 + 1, *(int *)(iVar1 + 0x18) <= iVar6))
    break;
    *param_1 = local_14;
    param_1[4] = local_48;
    FUN_00450dd0(param_1 + 1,(int *)local_54);
    uVar2 = FUN_0044e860(param_1,extraout_EDX_00,*(uint **)(iVar1 + 0xc));
    if ((char)uVar2 == '\0') break;
    local_18 = *param_1;
    uVar2 = FUN_0044e860(param_1,extraout_EDX_01,*(uint **)(*(int *)(iVar1 + 0x1c) + 0xc));
    if ((char)uVar2 != '\0') {
      if (param_4 == '\0') goto LAB_004547d9;
      local_38 = *param_1;
      local_28 = param_1[4];
      FUN_00450dd0(local_34,param_1 + 1);
      FUN_004506f0(local_24,param_1 + 5);
      param_3 = 0x1000000;
    }
    if (local_14 == local_18) break;
    local_14 = local_18;
    iVar6 = iVar7;
  }
  piVar8 = &local_38;
  if (param_3._3_1_ == '\0') {
    piVar8 = &local_58;
  }
  *param_1 = *piVar8;
  param_1[4] = piVar8[4];
  FUN_00450dd0(param_1 + 1,piVar8 + 1);
  FUN_004506f0(param_1 + 5,piVar8 + 5);
LAB_0045480d:
  if (local_24[0] != (void *)0x0) {
    uVar3 = local_1c - (int)local_24[0] >> 3;
    if (0x1fffffff < uVar3) {
                    /* WARNING: Subroutine does not return */
      FUN_00465fb2();
    }
    pvVar4 = local_24[0];
    if (0xfff < uVar3 << 3) {
      if (((uint)local_24[0] & 0x1f) != 0) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      pvVar4 = *(void **)((int)local_24[0] + -4);
      if (local_24[0] <= pvVar4) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if ((uint)((int)local_24[0] - (int)pvVar4) < 4) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if (0x23 < (uint)((int)local_24[0] - (int)pvVar4)) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
    }
    FID_conflict__free(pvVar4);
  }
  if (local_34[0] != (void *)0x0) {
    uVar3 = local_2c - (int)local_34[0] >> 2;
    if (0x3fffffff < uVar3) {
                    /* WARNING: Subroutine does not return */
      FUN_00465fb2();
    }
    pvVar4 = local_34[0];
    if (0xfff < uVar3 << 2) {
      if (((uint)local_34[0] & 0x1f) != 0) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      pvVar4 = *(void **)((int)local_34[0] + -4);
      if (local_34[0] <= pvVar4) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if ((uint)((int)local_34[0] - (int)pvVar4) < 4) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if (0x23 < (uint)((int)local_34[0] - (int)pvVar4)) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
    }
    FID_conflict__free(pvVar4);
  }
LAB_004548c5:
  if (local_44[0] != (void *)0x0) {
    uVar3 = local_3c - (int)local_44[0] >> 3;
    if (0x1fffffff < uVar3) {
                    /* WARNING: Subroutine does not return */
      FUN_00465fb2();
    }
    pvVar4 = local_44[0];
    if (0xfff < uVar3 << 3) {
      if (((uint)local_44[0] & 0x1f) != 0) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      pvVar4 = *(void **)((int)local_44[0] + -4);
      if (local_44[0] <= pvVar4) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if ((uint)((int)local_44[0] - (int)pvVar4) < 4) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if (0x23 < (uint)((int)local_44[0] - (int)pvVar4)) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
    }
    FID_conflict__free(pvVar4);
  }
  if (local_54[0] != (void *)0x0) {
    uVar3 = local_4c - (int)local_54[0] >> 2;
    if (0x3fffffff < uVar3) {
                    /* WARNING: Subroutine does not return */
      FUN_00465fb2();
    }
    pvVar4 = local_54[0];
    if (0xfff < uVar3 << 2) {
      if (((uint)local_54[0] & 0x1f) != 0) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      pvVar4 = *(void **)((int)local_54[0] + -4);
      if (local_54[0] <= pvVar4) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if ((uint)((int)local_54[0] - (int)pvVar4) < 4) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if (0x23 < (uint)((int)local_54[0] - (int)pvVar4)) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
    }
    FID_conflict__free(pvVar4);
  }
  ExceptionList = local_10;
  return param_3._3_1_;
}


