// FUN_0042a250 @ 0042a250 size=806 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_0042a250(void *param_1)

{
  char cVar1;
  undefined4 *puVar2;
  int *piVar3;
  void *pvVar4;
  undefined4 uVar5;
  char *pcVar6;
  int *piVar7;
  uint uVar8;
  int iVar9;
  undefined4 extraout_ECX;
  void *_Memory;
  int *piVar10;
  void *local_a8 [5];
  uint local_94;
  int local_90 [4];
  void *local_80;
  undefined1 *puStack_7c;
  undefined4 local_78;
  undefined **local_74 [9];
  undefined ***local_50;
  void *local_4c [4];
  undefined4 local_3c;
  uint local_38;
  undefined4 *local_34;
  undefined1 local_30;
  uint *local_2c;
  undefined4 *local_28;
  char *local_24;
  char *local_20;
  int *local_1c;
  int local_18;
  int local_14;
  uint local_10;
  void *local_c;
  char local_5;
  
  local_78 = 0xffffffff;
  puStack_7c = &LAB_0047c978;
  local_80 = ExceptionList;
  ExceptionList = &local_80;
  local_c = param_1;
  pvVar4 = (void *)FUN_00440dd0(param_1,(uint *)"states");
  FUN_00434120(pvVar4,&local_20);
  piVar10 = local_1c;
  do {
    local_38 = 0xf;
    local_3c = 0;
    local_4c[0] = (void *)((uint)local_4c[0] & 0xffffff00);
    FUN_0043ace0(local_4c,(uint *)"states",6);
    local_78 = 0;
    pvVar4 = (void *)FUN_00439c60(param_1,(byte *)local_4c);
    local_78 = 0xffffffff;
    if (0xf < local_38) {
      _Memory = local_4c[0];
      if ((0xfff < local_38 + 1) &&
         ((((((uint)local_4c[0] & 0x1f) != 0 ||
            (_Memory = *(void **)((int)local_4c[0] + -4), local_4c[0] <= _Memory)) ||
           ((uint)((int)local_4c[0] - (int)_Memory) < 4)) ||
          (0x23 < (uint)((int)local_4c[0] - (int)_Memory))))) {
LAB_0042a4fa:
        local_78 = 0xffffffff;
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      FID_conflict__free(_Memory);
    }
    local_38 = 0xf;
    local_3c = 0;
    local_4c[0] = (void *)((uint)local_4c[0] & 0xffffff00);
    FUN_004340a0(pvVar4,local_90);
    uVar5 = FUN_004383a0(&local_20,local_90);
    if ((char)uVar5 != '\0') {
      if (DAT_004a29c4 != 0) {
        local_74[0] = &PTR_LAB_0048e7b8;
        local_78 = 2;
        local_50 = local_74;
        FUN_0040f6b0(DAT_004a23dc,(int *)local_74,0);
        if (local_50 != (undefined ***)0x0) {
          (*(code *)(*local_50)[4])(local_50 != local_74);
        }
      }
      ExceptionList = local_80;
      return;
    }
    pcVar6 = FUN_00433b30(&local_20,(undefined1 *)local_a8);
    local_78 = 1;
    if (0xf < *(uint *)(pcVar6 + 0x14)) {
      pcVar6 = *(char **)pcVar6;
    }
    piVar7 = __errno();
    *piVar7 = 0;
    uVar8 = _strtol(pcVar6,&local_24,10);
    if (pcVar6 == local_24) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ea4("invalid stoi argument");
    }
    piVar7 = __errno();
    if (*piVar7 == 0x22) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ee4("stoi argument out of range");
    }
    local_10 = uVar8 & 0xffff;
    pcVar6 = FUN_00433bc0(&local_20);
    FUN_00453610(pcVar6,&local_5);
    FUN_00436f60(&local_28,(byte *)&local_10);
    if (local_28 == DAT_004a2564) {
      puVar2 = (undefined4 *)*DAT_004a2564;
      local_2c = &local_10;
      iVar9 = FUN_004551d0(puVar2,(undefined4 *)puVar2[1],extraout_ECX,&local_2c);
      if (_DAT_004a2568 == 0x15555554) {
                    /* WARNING: Subroutine does not return */
        FUN_00458ec4("list<T> too long");
      }
      _DAT_004a2568 = _DAT_004a2568 + 1;
      puVar2[1] = iVar9;
      **(int **)(iVar9 + 4) = iVar9;
      FUN_0044fb80(&DAT_004a2560,(int *)&local_34,(byte *)((int *)*DAT_004a2564 + 2),
                   (int *)*DAT_004a2564);
    }
    else {
      local_34 = local_28;
      local_30 = 0;
    }
    *(char *)((int)local_34 + 10) = local_5;
    local_78 = 0xffffffff;
    if (0xf < local_94) {
      pvVar4 = local_a8[0];
      if ((0xfff < local_94 + 1) &&
         (((((uint)local_a8[0] & 0x1f) != 0 ||
           (pvVar4 = *(void **)((int)local_a8[0] + -4), local_a8[0] <= pvVar4)) ||
          (((uint)((int)local_a8[0] - (int)pvVar4) < 4 ||
           (0x23 < (uint)((int)local_a8[0] - (int)pvVar4))))))) goto LAB_0042a4fa;
      FID_conflict__free(pvVar4);
    }
    param_1 = local_c;
    if (*local_20 == '\x01') {
      if (*(char *)((int)piVar10 + 0xd) == '\0') {
        piVar7 = (int *)piVar10[2];
        if (*(char *)((int)piVar7 + 0xd) == '\0') {
          cVar1 = *(char *)(*piVar7 + 0xd);
          piVar10 = piVar7;
          piVar7 = (int *)*piVar7;
          while (local_1c = piVar10, cVar1 == '\0') {
            cVar1 = *(char *)(*piVar7 + 0xd);
            piVar10 = piVar7;
            piVar7 = (int *)*piVar7;
          }
        }
        else {
          cVar1 = *(char *)(piVar10[1] + 0xd);
          piVar3 = (int *)piVar10[1];
          piVar7 = piVar10;
          while ((piVar10 = piVar3, local_1c = piVar10, cVar1 == '\0' &&
                 (piVar7 == (int *)piVar10[2]))) {
            cVar1 = *(char *)(piVar10[1] + 0xd);
            piVar3 = (int *)piVar10[1];
            piVar7 = piVar10;
          }
        }
      }
    }
    else if (*local_20 == '\x02') {
      local_18 = local_18 + 0x10;
    }
    else {
      local_14 = local_14 + 1;
    }
  } while( true );
}


