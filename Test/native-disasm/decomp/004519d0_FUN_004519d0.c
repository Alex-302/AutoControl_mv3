// FUN_004519d0 @ 004519d0 size=777 callers=1

undefined1 __fastcall FUN_004519d0(int *param_1,undefined4 param_2,uint param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  void *pvVar6;
  uint *extraout_EDX;
  undefined4 extraout_EDX_00;
  uint *extraout_EDX_01;
  undefined1 uVar7;
  int *piVar8;
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
  int *local_18;
  int *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047e910;
  local_10 = ExceptionList;
  local_38 = *param_1;
  piVar8 = param_1 + 1;
  ExceptionList = &local_10;
  local_14 = param_1;
  FUN_00450ec0((int *)local_34,param_2,piVar8);
  local_28 = param_1[4];
  local_18 = param_1 + 5;
  local_8 = 0;
  FUN_00453540(local_24,local_18);
  local_8 = 1;
  do {
    if (param_3 == 0) {
      uVar7 = 0;
LAB_00451a69:
      if (local_24[0] != (void *)0x0) {
        uVar5 = local_1c - (int)local_24[0] >> 3;
        if (0x1fffffff < uVar5) {
                    /* WARNING: Subroutine does not return */
          FUN_00465fb2();
        }
        pvVar6 = local_24[0];
        if (0xfff < uVar5 << 3) {
          if (((uint)local_24[0] & 0x1f) != 0) {
                    /* WARNING: Subroutine does not return */
            FUN_00465fb2();
          }
          pvVar6 = *(void **)((int)local_24[0] + -4);
          if (local_24[0] <= pvVar6) {
                    /* WARNING: Subroutine does not return */
            FUN_00465fb2();
          }
          if ((uint)((int)local_24[0] - (int)pvVar6) < 4) {
                    /* WARNING: Subroutine does not return */
            FUN_00465fb2();
          }
          if (0x23 < (uint)((int)local_24[0] - (int)pvVar6)) {
                    /* WARNING: Subroutine does not return */
            FUN_00465fb2();
          }
        }
        FID_conflict__free(pvVar6);
      }
      if (local_34[0] != (void *)0x0) {
        uVar5 = local_2c - (int)local_34[0] >> 2;
        if (0x3fffffff < uVar5) {
                    /* WARNING: Subroutine does not return */
          FUN_00465fb2();
        }
        pvVar6 = local_34[0];
        if (0xfff < uVar5 << 2) {
          if (((uint)local_34[0] & 0x1f) != 0) {
                    /* WARNING: Subroutine does not return */
            FUN_00465fb2();
          }
          pvVar6 = *(void **)((int)local_34[0] + -4);
          if (local_34[0] <= pvVar6) {
                    /* WARNING: Subroutine does not return */
            FUN_00465fb2();
          }
          if ((uint)((int)local_34[0] - (int)pvVar6) < 4) {
                    /* WARNING: Subroutine does not return */
            FUN_00465fb2();
          }
          if (0x23 < (uint)((int)local_34[0] - (int)pvVar6)) {
                    /* WARNING: Subroutine does not return */
            FUN_00465fb2();
          }
        }
        FID_conflict__free(pvVar6);
      }
      ExceptionList = local_10;
      return uVar7;
    }
    *param_1 = local_38;
    param_1[4] = local_28;
    FUN_00450dd0(piVar8,(int *)local_34);
    FUN_004507e0(param_1 + 5,(int *)local_24);
    uVar4 = FUN_0044e410(param_1,extraout_EDX,*(uint **)(param_3 + 0xc));
    if ((char)uVar4 != '\0') {
      if ((char)param_1[0x1b] == '\0') {
        uVar7 = 1;
      }
      else {
        local_58 = *param_1;
        FUN_00450ec0((int *)local_54,extraout_EDX_00,piVar8);
        local_48 = param_1[4];
        local_8._0_1_ = 2;
        FUN_00453540(local_44,param_1 + 5);
        local_8 = CONCAT31(local_8._1_3_,3);
        iVar1 = *(int *)(param_3 + 0x18);
        param_3 = *param_1 - local_38;
        iVar3 = local_38;
        piVar8 = local_14;
        for (; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x18)) {
          *piVar8 = iVar3;
          piVar8[4] = local_28;
          FUN_00450dd0(piVar8 + 1,(int *)local_34);
          FUN_004507e0(piVar8 + 5,(int *)local_24);
          uVar4 = FUN_0044e410(piVar8,extraout_EDX_01,*(uint **)(iVar1 + 0xc));
          iVar3 = local_38;
          if ((char)uVar4 != '\0') {
            iVar2 = *piVar8;
            uVar5 = iVar2 - local_38;
            piVar8 = local_14;
            if (param_3 < uVar5) {
              local_48 = local_14[4];
              FUN_00450dd0(local_54,local_14 + 1);
              FUN_004507e0(local_44,local_18);
              piVar8 = local_14;
              param_3 = uVar5;
              local_58 = iVar2;
            }
          }
        }
        *local_14 = local_58;
        local_14[4] = local_48;
        FUN_00450dd0(local_14 + 1,(int *)local_54);
        FUN_004507e0(local_18,(int *)local_44);
        uVar7 = 1;
        if (local_44[0] != (void *)0x0) {
          uVar5 = local_3c - (int)local_44[0] >> 3;
          if (0x1fffffff < uVar5) {
                    /* WARNING: Subroutine does not return */
            FUN_00465fb2();
          }
          pvVar6 = local_44[0];
          if (0xfff < uVar5 << 3) {
            if (((uint)local_44[0] & 0x1f) != 0) {
                    /* WARNING: Subroutine does not return */
              FUN_00465fb2();
            }
            pvVar6 = *(void **)((int)local_44[0] + -4);
            if (local_44[0] <= pvVar6) {
                    /* WARNING: Subroutine does not return */
              FUN_00465fb2();
            }
            if ((uint)((int)local_44[0] - (int)pvVar6) < 4) {
                    /* WARNING: Subroutine does not return */
              FUN_00465fb2();
            }
            if (0x23 < (uint)((int)local_44[0] - (int)pvVar6)) {
                    /* WARNING: Subroutine does not return */
              FUN_00465fb2();
            }
          }
          FID_conflict__free(pvVar6);
        }
        if (local_54[0] != (void *)0x0) {
          uVar5 = local_4c - (int)local_54[0] >> 2;
          if (0x3fffffff < uVar5) {
                    /* WARNING: Subroutine does not return */
            FUN_00465fb2();
          }
          pvVar6 = local_54[0];
          if (0xfff < uVar5 << 2) {
            if (((uint)local_54[0] & 0x1f) != 0) {
                    /* WARNING: Subroutine does not return */
              FUN_00465fb2();
            }
            pvVar6 = *(void **)((int)local_54[0] + -4);
            if (local_54[0] <= pvVar6) {
                    /* WARNING: Subroutine does not return */
              FUN_00465fb2();
            }
            if ((uint)((int)local_54[0] - (int)pvVar6) < 4) {
                    /* WARNING: Subroutine does not return */
              FUN_00465fb2();
            }
            if (0x23 < (uint)((int)local_54[0] - (int)pvVar6)) {
                    /* WARNING: Subroutine does not return */
              FUN_00465fb2();
            }
          }
          FID_conflict__free(pvVar6);
        }
      }
      goto LAB_00451a69;
    }
    param_3 = *(uint *)(param_3 + 0x18);
  } while( true );
}


