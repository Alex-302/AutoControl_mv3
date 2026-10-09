// FUN_00427950 @ 00427950 size=1083 callers=1

void __fastcall FUN_00427950(void *param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  char cVar3;
  undefined4 uVar4;
  char *pcVar5;
  int *piVar6;
  uint uVar7;
  void *this;
  void *_Memory;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  int iVar8;
  int *piVar9;
  void *local_a0 [5];
  uint local_8c;
  void *local_88;
  undefined1 *puStack_84;
  undefined4 local_80;
  int local_7c [4];
  undefined4 local_6c;
  undefined4 local_68;
  int *local_64;
  int *local_60;
  undefined4 *local_5c;
  undefined4 *local_58;
  int *local_54;
  int *local_50;
  int *local_4c;
  int *local_48;
  int local_44;
  undefined1 local_40;
  int local_3c;
  undefined1 local_38;
  void *local_34;
  int local_30;
  int local_2c;
  uint local_28;
  char *local_24;
  char *local_20;
  int *local_1c;
  int local_18;
  int local_14;
  uint *local_10;
  uint local_c;
  uint local_8;
  
  local_80 = 0xffffffff;
  puStack_84 = &LAB_0047c658;
  local_88 = ExceptionList;
  ExceptionList = &local_88;
  local_34 = param_1;
  if ((*(int *)(*(int *)ThreadLocalStoragePointer + 8) < DAT_004a2a84) &&
     (ExceptionList = &local_88, FUN_0045a219(&DAT_004a2a84), DAT_004a2a84 == -1)) {
    DAT_004a3360 = (uint *)0x0;
    DAT_004a3364 = (uint *)0x0;
    DAT_004a3368 = (uint *)0x0;
    _atexit(FUN_0047f700);
    FUN_0045a1da(&DAT_004a2a84);
  }
  FUN_00434120(param_1,&local_20);
  FUN_004340a0(this,local_7c);
  uVar4 = FUN_004383a0(&local_20,local_7c);
  cVar3 = (char)uVar4;
  piVar9 = local_1c;
  while( true ) {
    if (cVar3 != '\0') {
      ExceptionList = local_88;
      return;
    }
    pcVar5 = FUN_00433b30(&local_20,(undefined1 *)local_a0);
    local_80 = 0;
    if (0xf < *(uint *)(pcVar5 + 0x14)) {
      pcVar5 = *(char **)pcVar5;
    }
    piVar6 = __errno();
    *piVar6 = 0;
    uVar7 = _strtol(pcVar5,&local_24,10);
    if (pcVar5 == local_24) break;
    piVar6 = __errno();
    if (*piVar6 == 0x22) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ee4("stoi argument out of range");
    }
    local_80 = 0xffffffff;
    local_c = uVar7;
    if (0xf < local_8c) {
      _Memory = local_a0[0];
      if ((0xfff < local_8c + 1) &&
         ((((((uint)local_a0[0] & 0x1f) != 0 ||
            (_Memory = *(void **)((int)local_a0[0] + -4), local_a0[0] <= _Memory)) ||
           ((uint)((int)local_a0[0] - (int)_Memory) < 4)) ||
          (0x23 < (uint)((int)local_a0[0] - (int)_Memory))))) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      FID_conflict__free(_Memory);
    }
    FUN_00436350(&DAT_004a290c,(int *)&local_4c,(byte *)&local_c);
    iVar8 = 0;
    piVar6 = local_4c;
    if (local_4c != local_48) {
      do {
        piVar6 = (int *)*piVar6;
        iVar8 = iVar8 + 1;
      } while (piVar6 != local_48);
      if (iVar8 != 0) {
        if (0x1e < (uint)((int)DAT_004a3364 - (int)DAT_004a3360 >> 2)) {
          local_10 = (uint *)*DAT_004a3360;
          FUN_0045b0e0(DAT_004a3360,DAT_004a3360 + 1,(int)DAT_004a3364 - (int)(DAT_004a3360 + 1));
          DAT_004a3364 = DAT_004a3364 + -1;
          FUN_00436350(&DAT_004a292c,(int *)&local_54,(byte *)&local_10);
          for (piVar6 = local_54; piVar6 != local_50; piVar6 = (int *)*piVar6) {
          }
          FUN_00436410(&DAT_004a292c,&local_68,local_54,local_50);
        }
        pcVar5 = FUN_00433bc0(&local_20);
        if (*pcVar5 != '\0') {
          pcVar5 = FUN_00433bc0(&local_20);
          FUN_004536b0(pcVar5,&local_28);
          local_8 = local_28;
          if ((&local_8 < DAT_004a3364) && (DAT_004a3360 <= &local_8)) {
            iVar8 = (int)&local_8 - (int)DAT_004a3360;
            if (DAT_004a3364 == DAT_004a3368) {
              FUN_00435b90((int *)&DAT_004a3360);
            }
            if (DAT_004a3364 != (uint *)0x0) {
              *DAT_004a3364 = DAT_004a3360[iVar8 >> 2];
            }
          }
          else {
            if (DAT_004a3364 == DAT_004a3368) {
              FUN_00435b90((int *)&DAT_004a3360);
            }
            if (DAT_004a3364 != (uint *)0x0) {
              *DAT_004a3364 = local_8;
            }
          }
          DAT_004a3364 = DAT_004a3364 + 1;
          FUN_00436350(&DAT_004a290c,(int *)&local_5c,(byte *)&local_c);
          for (puVar2 = local_5c; puVar2 != local_58; puVar2 = (undefined4 *)*puVar2) {
          }
          FUN_00436250(&DAT_004a290c,&local_2c,(byte *)&local_c);
          if (local_2c == DAT_004a2910) {
            local_10 = &local_c;
            FUN_0044a600(&DAT_004a290c,&local_3c,extraout_ECX,&local_10);
          }
          else {
            local_3c = local_2c;
            local_38 = 0;
          }
          piVar6 = (int *)(local_3c + 0xc);
          FUN_00436250(&DAT_004a292c,&local_30,(byte *)&local_8);
          if (local_30 == DAT_004a2930) {
            local_10 = &local_8;
            FUN_0044a600(&DAT_004a292c,&local_44,extraout_ECX_00,&local_10);
          }
          else {
            local_44 = local_30;
            local_40 = 0;
          }
          piVar1 = (int *)(local_44 + 0xc);
          if (piVar1 != piVar6) {
            iVar8 = *piVar6;
            *piVar6 = 0;
            puVar2 = (undefined4 *)*piVar1;
            *piVar1 = iVar8;
            if (puVar2 != (undefined4 *)0x0) {
              (**(code **)*puVar2)(1);
            }
          }
        }
        FUN_00436350(&DAT_004a290c,(int *)&local_64,(byte *)&local_c);
        for (piVar6 = local_64; piVar6 != local_60; piVar6 = (int *)*piVar6) {
        }
        FUN_00436410(&DAT_004a290c,&local_6c,local_64,local_60);
      }
    }
    if (*local_20 == '\x01') {
      if (*(char *)((int)piVar9 + 0xd) == '\0') {
        piVar6 = (int *)piVar9[2];
        if (*(char *)((int)piVar6 + 0xd) == '\0') {
          cVar3 = *(char *)(*piVar6 + 0xd);
          piVar9 = piVar6;
          piVar6 = (int *)*piVar6;
          while (local_1c = piVar9, cVar3 == '\0') {
            cVar3 = *(char *)(*piVar6 + 0xd);
            piVar9 = piVar6;
            piVar6 = (int *)*piVar6;
          }
        }
        else {
          cVar3 = *(char *)(piVar9[1] + 0xd);
          piVar1 = (int *)piVar9[1];
          piVar6 = piVar9;
          while ((piVar9 = piVar1, local_1c = piVar9, cVar3 == '\0' && (piVar6 == (int *)piVar9[2]))
                ) {
            cVar3 = *(char *)(piVar9[1] + 0xd);
            piVar1 = (int *)piVar9[1];
            piVar6 = piVar9;
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
    FUN_004340a0(local_34,local_7c);
    uVar4 = FUN_004383a0(&local_20,local_7c);
    cVar3 = (char)uVar4;
  }
                    /* WARNING: Subroutine does not return */
  FUN_00458ea4("invalid stoi argument");
}


