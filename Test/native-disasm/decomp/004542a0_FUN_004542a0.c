// FUN_004542a0 @ 004542a0 size=890 callers=1

char __fastcall FUN_004542a0(int *param_1,undefined4 param_2,int param_3,char param_4)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  void *pvVar4;
  uint *extraout_EDX;
  uint *puVar5;
  uint *extraout_EDX_00;
  uint *extraout_EDX_01;
  uint *extraout_EDX_02;
  uint *extraout_EDX_03;
  char cVar6;
  int iVar7;
  int iVar8;
  int *piVar9;
  int *piVar10;
  int iVar11;
  bool bVar12;
  int local_64;
  void *local_60 [2];
  int local_58;
  int local_54;
  void *local_50 [2];
  int local_48;
  int local_44;
  void *local_40 [2];
  int local_38;
  int local_34;
  void *local_30 [2];
  int local_28;
  int *local_20;
  int *local_1c;
  int *local_18;
  char local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047e9f0;
  local_10 = ExceptionList;
  iVar7 = 0;
  local_64 = *param_1;
  piVar10 = param_1 + 1;
  ExceptionList = &local_10;
  local_1c = piVar10;
  local_18 = param_1;
  FUN_00450ec0((int *)local_60,param_2,piVar10);
  local_54 = param_1[4];
  local_20 = param_1 + 5;
  local_8 = 0;
  FUN_00453540(local_50,local_20);
  local_8 = 1;
  puVar5 = extraout_EDX;
  piVar9 = param_1;
  if (0 < *(int *)(param_3 + 0x14)) {
    do {
      param_1 = local_18;
      iVar11 = *piVar9;
      uVar2 = FUN_0044e410(local_18,puVar5,*(uint **)(param_3 + 0xc));
      if ((char)uVar2 == '\0') {
        *param_1 = local_64;
        param_1[4] = local_54;
        FUN_00450dd0(param_1 + 1,(int *)local_60);
        FUN_004507e0(param_1 + 5,(int *)local_50);
        cVar6 = '\0';
        goto LAB_0045454d;
      }
      if (iVar11 == *param_1) {
        iVar7 = *(int *)(param_3 + 0x14) + -1;
      }
      iVar7 = iVar7 + 1;
      puVar5 = extraout_EDX_00;
      piVar9 = param_1;
      piVar10 = local_1c;
    } while (iVar7 < *(int *)(param_3 + 0x14));
  }
  local_44 = *param_1;
  FUN_00450ec0((int *)local_40,puVar5,piVar10);
  local_34 = piVar10[3];
  local_8._0_1_ = 2;
  FUN_00453540(local_30,param_1 + 5);
  local_8 = CONCAT31(local_8._1_3_,3);
  iVar11 = *param_1;
  local_11 = '\0';
  uVar2 = FUN_0044e410(param_1,extraout_EDX_01,*(uint **)(*(int *)(param_3 + 0x1c) + 0xc));
  if ((char)uVar2 != '\0') {
    if (param_4 == '\0') {
LAB_0045445e:
      cVar6 = '\x01';
      goto LAB_00454495;
    }
    local_44 = *param_1;
    local_34 = param_1[4];
    FUN_00450dd0(local_40,param_1 + 1);
    FUN_004507e0(local_30,param_1 + 5);
    local_11 = '\x01';
  }
  do {
    iVar8 = iVar7;
    if ((*(int *)(param_3 + 0x18) != -1) && (iVar8 = iVar7 + 1, *(int *)(param_3 + 0x18) <= iVar7))
    break;
    *param_1 = iVar11;
    param_1[4] = local_54;
    FUN_00450dd0(param_1 + 1,(int *)local_60);
    uVar2 = FUN_0044e410(param_1,extraout_EDX_02,*(uint **)(param_3 + 0xc));
    if ((char)uVar2 == '\0') break;
    iVar1 = *param_1;
    uVar2 = FUN_0044e410(local_18,extraout_EDX_03,*(uint **)(*(int *)(param_3 + 0x1c) + 0xc));
    if ((char)uVar2 != '\0') {
      if (param_4 == '\0') goto LAB_0045445e;
      local_44 = *local_18;
      local_34 = local_1c[3];
      FUN_00450dd0(local_40,local_1c);
      FUN_004507e0(local_30,local_20);
      local_11 = '\x01';
    }
    bVar12 = iVar11 != iVar1;
    iVar7 = iVar8;
    param_1 = local_18;
    iVar11 = iVar1;
  } while (bVar12);
  cVar6 = local_11;
  piVar10 = &local_44;
  if (local_11 == '\0') {
    piVar10 = &local_64;
  }
  *local_18 = *piVar10;
  local_1c[3] = piVar10[4];
  FUN_00450dd0(local_1c,piVar10 + 1);
  FUN_004507e0(local_20,piVar10 + 5);
LAB_00454495:
  if (local_30[0] != (void *)0x0) {
    uVar3 = local_28 - (int)local_30[0] >> 3;
    if (0x1fffffff < uVar3) {
                    /* WARNING: Subroutine does not return */
      FUN_00465fb2();
    }
    pvVar4 = local_30[0];
    if (0xfff < uVar3 << 3) {
      if (((uint)local_30[0] & 0x1f) != 0) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      pvVar4 = *(void **)((int)local_30[0] + -4);
      if (local_30[0] <= pvVar4) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if ((uint)((int)local_30[0] - (int)pvVar4) < 4) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if (0x23 < (uint)((int)local_30[0] - (int)pvVar4)) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
    }
    FID_conflict__free(pvVar4);
  }
  if (local_40[0] != (void *)0x0) {
    uVar3 = local_38 - (int)local_40[0] >> 2;
    if (0x3fffffff < uVar3) {
                    /* WARNING: Subroutine does not return */
      FUN_00465fb2();
    }
    pvVar4 = local_40[0];
    if (0xfff < uVar3 << 2) {
      if (((uint)local_40[0] & 0x1f) != 0) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      pvVar4 = *(void **)((int)local_40[0] + -4);
      if (local_40[0] <= pvVar4) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if ((uint)((int)local_40[0] - (int)pvVar4) < 4) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if (0x23 < (uint)((int)local_40[0] - (int)pvVar4)) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
    }
    FID_conflict__free(pvVar4);
  }
LAB_0045454d:
  if (local_50[0] != (void *)0x0) {
    uVar3 = local_48 - (int)local_50[0] >> 3;
    if (0x1fffffff < uVar3) {
                    /* WARNING: Subroutine does not return */
      FUN_00465fb2();
    }
    pvVar4 = local_50[0];
    if (0xfff < uVar3 << 3) {
      if (((uint)local_50[0] & 0x1f) != 0) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      pvVar4 = *(void **)((int)local_50[0] + -4);
      if (local_50[0] <= pvVar4) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if ((uint)((int)local_50[0] - (int)pvVar4) < 4) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if (0x23 < (uint)((int)local_50[0] - (int)pvVar4)) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
    }
    FID_conflict__free(pvVar4);
  }
  if (local_60[0] != (void *)0x0) {
    uVar3 = local_58 - (int)local_60[0] >> 2;
    if (0x3fffffff < uVar3) {
                    /* WARNING: Subroutine does not return */
      FUN_00465fb2();
    }
    pvVar4 = local_60[0];
    if (0xfff < uVar3 << 2) {
      if (((uint)local_60[0] & 0x1f) != 0) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      pvVar4 = *(void **)((int)local_60[0] + -4);
      if (local_60[0] <= pvVar4) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if ((uint)((int)local_60[0] - (int)pvVar4) < 4) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if (0x23 < (uint)((int)local_60[0] - (int)pvVar4)) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
    }
    FID_conflict__free(pvVar4);
  }
  ExceptionList = local_10;
  return cVar6;
}


