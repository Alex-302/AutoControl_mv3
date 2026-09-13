// FUN_00421960 @ 00421960 size=1959 callers=1

int * __thiscall FUN_00421960(void *this,void *param_1)

{
  undefined4 *puVar1;
  int *piVar2;
  char **ppcVar3;
  int *piVar4;
  char cVar5;
  char *pcVar6;
  void *pvVar7;
  undefined4 uVar8;
  int *piVar9;
  long lVar10;
  int iVar11;
  void *this_00;
  char *extraout_ECX;
  undefined4 extraout_ECX_00;
  void *this_01;
  undefined4 *puVar12;
  uint uVar13;
  int *piVar14;
  int iVar15;
  ulonglong uVar16;
  void *local_bc [5];
  uint local_a8;
  int local_a4;
  undefined1 local_a0;
  int local_9c;
  uint local_98;
  char *local_94;
  void *local_90 [2];
  int local_88 [2];
  undefined4 local_80;
  uint local_7c;
  char *local_74;
  int *local_70;
  int local_6c;
  int local_68;
  char *local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  char **local_54;
  char **local_50;
  char **local_4c;
  undefined4 *local_48;
  ushort local_44 [2];
  char *local_40;
  char *local_3c;
  char *local_38;
  int *local_34;
  int local_30;
  int local_2c;
  char *local_28;
  int *local_24;
  int local_20;
  int local_1c;
  int *local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047bcc1;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *(undefined4 *)this = 0;
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  puVar12 = (undefined4 *)((int)this + 0xc);
  local_8 = 0;
  local_48 = puVar12;
  local_18 = this;
  FUN_00433450(puVar12);
  local_54 = (char **)((int)this + 0x2c);
  *(undefined4 *)((int)this + 0x2c) = 0;
  *(undefined4 *)((int)this + 0x30) = 0;
  *(undefined4 *)((int)this + 0x34) = 0;
  local_8 = CONCAT31(local_8._1_3_,2);
  pcVar6 = (char *)FUN_00440dd0(param_1,(uint *)&DAT_0048cf28);
  cVar5 = *pcVar6;
  if (cVar5 == '\0') {
    uVar13 = 0;
  }
  else if (cVar5 == '\x01') {
    uVar13 = *(uint *)(*(int *)(pcVar6 + 8) + 4);
  }
  else if (cVar5 == '\x02') {
    uVar13 = (*(int **)(pcVar6 + 8))[1] - **(int **)(pcVar6 + 8) >> 4;
  }
  else {
    uVar13 = 1;
  }
  if ((uint)((*(int *)((int)this + 8) - *(int *)this) / 0x24) < uVar13) {
    if (0x71c71c7 < uVar13) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ec4("vector<T> too long");
    }
    FUN_004374f0(this,uVar13);
  }
  pvVar7 = (void *)FUN_00440dd0(param_1,(uint *)&DAT_0048cf28);
  FUN_00434120(pvVar7,&local_28);
  FUN_004340a0(this_00,&local_38);
  uVar8 = FUN_004383a0(&local_28,(int *)&local_38);
  cVar5 = (char)uVar8;
  piVar14 = local_24;
  iVar11 = local_20;
  iVar15 = local_1c;
  while (cVar5 == '\0') {
    local_40 = FUN_00433bc0(&local_28);
    if (local_18[1] == local_18[2]) {
      FUN_00443dd0(local_18);
    }
    local_50 = (char **)local_18[1];
    local_8._0_1_ = 3;
    local_4c = local_50;
    if (local_50 != (char **)0x0) {
      FUN_00421210(local_50,local_40);
    }
    local_8 = CONCAT31(local_8._1_3_,2);
    local_18[1] = local_18[1] + 0x24;
    if (*local_28 == '\x01') {
      if (*(char *)((int)piVar14 + 0xd) == '\0') {
        piVar9 = (int *)piVar14[2];
        if (*(char *)((int)piVar9 + 0xd) == '\0') {
          cVar5 = *(char *)(*piVar9 + 0xd);
          piVar14 = piVar9;
          piVar9 = (int *)*piVar9;
          while (local_24 = piVar14, cVar5 == '\0') {
            cVar5 = *(char *)(*piVar9 + 0xd);
            piVar14 = piVar9;
            piVar9 = (int *)*piVar9;
          }
        }
        else {
          cVar5 = *(char *)(piVar14[1] + 0xd);
          piVar2 = (int *)piVar14[1];
          piVar9 = piVar14;
          while ((piVar14 = piVar2, local_24 = piVar14, cVar5 == '\0' &&
                 (piVar9 == (int *)piVar14[2]))) {
            cVar5 = *(char *)(piVar14[1] + 0xd);
            piVar2 = (int *)piVar14[1];
            piVar9 = piVar14;
          }
        }
      }
    }
    else if (*local_28 == '\x02') {
      iVar11 = iVar11 + 0x10;
      local_20 = iVar11;
    }
    else {
      iVar15 = iVar15 + 1;
      local_1c = iVar15;
    }
    uVar8 = FUN_004383a0(&local_28,(int *)&local_38);
    puVar12 = local_48;
    cVar5 = (char)uVar8;
  }
  DAT_004a2505 = 0;
  local_7c = 0xf;
  local_80 = 0;
  local_90[0] = (void *)((uint)local_90[0] & 0xffffff00);
  FUN_0043ace0(local_90,(uint *)&DAT_0048d7cc,3);
  local_8._0_1_ = 4;
  pcVar6 = (char *)FUN_00439c60(param_1,(byte *)local_90);
  local_8 = CONCAT31(local_8._1_3_,2);
  local_3c = pcVar6;
  if (0xf < local_7c) {
    pvVar7 = local_90[0];
    if (0xfff < local_7c + 1) {
      if (((uint)local_90[0] & 0x1f) != 0) {
LAB_00421bad:
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      pvVar7 = *(void **)((int)local_90[0] + -4);
      if (local_90[0] <= pvVar7) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if ((uint)((int)local_90[0] - (int)pvVar7) < 4) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if (0x23 < (uint)((int)local_90[0] - (int)pvVar7)) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
    }
    FID_conflict__free(pvVar7);
  }
  local_7c = 0xf;
  local_80 = 0;
  local_90[0] = (void *)((uint)local_90[0] & 0xffffff00);
  uVar16 = FUN_00477bf0();
  FUN_004373e0(puVar12,(uint)uVar16);
  FUN_00434120(pcVar6,&local_38);
  piVar14 = local_34;
  do {
    local_58 = 0;
    local_5c = 0;
    local_60 = 0;
    if (*pcVar6 == '\x01') {
      local_60 = **(undefined4 **)(pcVar6 + 8);
    }
    else if (*pcVar6 == '\x02') {
      local_5c = *(undefined4 *)(*(int *)(pcVar6 + 8) + 4);
    }
    else {
      local_58 = 1;
    }
    local_64 = pcVar6;
    uVar8 = FUN_004383a0(&local_38,(int *)&local_64);
    if ((char)uVar8 != '\0') {
      pvVar7 = (void *)FUN_00440dd0(param_1,(uint *)"urlTests");
      FUN_00434120(pvVar7,&local_38);
      FUN_004340a0(this_01,local_88);
      uVar8 = FUN_004383a0(&local_38,local_88);
      ppcVar3 = local_54;
      cVar5 = (char)uVar8;
      while (cVar5 == '\0') {
        pcVar6 = FUN_00433bc0(&local_38);
        if (ppcVar3[1] == ppcVar3[2]) {
          FUN_00443cc0((int *)ppcVar3);
        }
        local_54 = (char **)ppcVar3[1];
        local_8._0_1_ = 7;
        local_4c = local_54;
        if (local_54 != (char **)0x0) {
          FUN_00421850(local_54,pcVar6);
        }
        local_8 = CONCAT31(local_8._1_3_,2);
        ppcVar3[1] = ppcVar3[1] + 0x18;
        if (*local_38 == '\x01') {
          FUN_00447660((int *)&local_34);
        }
        else if (*local_38 == '\x02') {
          local_30 = local_30 + 0x10;
        }
        else {
          local_2c = local_2c + 1;
        }
        uVar8 = FUN_004383a0(&local_38,local_88);
        cVar5 = (char)uVar8;
      }
      ExceptionList = local_10;
      return local_18;
    }
    pcVar6 = FUN_00433b30(&local_38,(undefined1 *)local_bc);
    local_8._0_1_ = 5;
    if (0xf < *(uint *)(pcVar6 + 0x14)) {
      pcVar6 = *(char **)pcVar6;
    }
    piVar9 = __errno();
    *piVar9 = 0;
    lVar10 = _strtol(pcVar6,&local_94,10);
    if (pcVar6 == local_94) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ea4("invalid stoi argument");
    }
    piVar9 = __errno();
    if (*piVar9 == 0x22) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ee4("stoi argument out of range");
    }
    uVar13 = lVar10 - 0x5609;
    local_8 = CONCAT31(local_8._1_3_,2);
    local_98 = uVar13;
    if (0xf < local_a8) {
      pvVar7 = local_bc[0];
      if ((0xfff < local_a8 + 1) &&
         ((((((uint)local_bc[0] & 0x1f) != 0 ||
            (pvVar7 = *(void **)((int)local_bc[0] + -4), local_bc[0] <= pvVar7)) ||
           ((uint)((int)local_bc[0] - (int)pvVar7) < 4)) ||
          (0x23 < (uint)((int)local_bc[0] - (int)pvVar7))))) goto LAB_00421bad;
      FID_conflict__free(pvVar7);
    }
    if ((uVar13 == 0x850) || (uVar13 == 0x851)) {
      DAT_004a2505 = 1;
    }
    pcVar6 = FUN_00433bc0(&local_38);
    FUN_00434120(pcVar6,&local_74);
    local_1c = 0;
    local_20 = 0;
    local_24 = (int *)0x0;
    if (*extraout_ECX == '\x01') {
      local_24 = (int *)**(int **)(extraout_ECX + 8);
    }
    else if (*extraout_ECX == '\x02') {
      local_20 = *(int *)(*(int *)(extraout_ECX + 8) + 4);
    }
    else {
      local_1c = 1;
    }
    uVar8 = FUN_004383a0(&local_74,(int *)&local_28);
    cVar5 = (char)uVar8;
    piVar9 = local_70;
    puVar12 = local_48;
    pcVar6 = local_3c;
    while (local_3c = pcVar6, cVar5 == '\0') {
      pcVar6 = FUN_00433bc0(&local_74);
      FUN_00434940(local_88,pcVar6);
      local_8 = CONCAT31(local_8._1_3_,6);
      FUN_00453970((char *)local_88,local_44);
      local_4c = (char **)(uint)local_44[0];
      local_40 = (char *)(local_98 & 0xffff);
      FUN_00437350(puVar12,&local_9c,(byte *)&local_40);
      if (local_9c == puVar12[1]) {
        local_50 = &local_40;
        puVar1 = *(undefined4 **)puVar12[1];
        iVar11 = FUN_00455200(puVar1,(undefined4 *)puVar1[1],extraout_ECX_00,&local_50);
        puVar12 = local_48;
        if (local_18[5] == 0xaaaaaa9) {
                    /* WARNING: Subroutine does not return */
          FUN_00458ec4("list<T> too long");
        }
        local_18[5] = local_18[5] + 1;
        puVar1[1] = iVar11;
        **(int **)(iVar11 + 4) = iVar11;
        FUN_00443460(local_48,&local_a4,(byte *)(*(int **)local_48[1] + 2),*(int **)local_48[1]);
      }
      else {
        local_a4 = local_9c;
        local_a0 = 0;
      }
      FUN_00433540((void *)(local_a4 + 0xc),(undefined2 *)&local_4c);
      local_8 = CONCAT31(local_8._1_3_,2);
      FUN_00434820((char *)local_88);
      if (*local_74 == '\x01') {
        if (*(char *)((int)piVar9 + 0xd) == '\0') {
          piVar2 = (int *)piVar9[2];
          if (*(char *)((int)piVar2 + 0xd) == '\0') {
            cVar5 = *(char *)(*piVar2 + 0xd);
            piVar9 = piVar2;
            piVar2 = (int *)*piVar2;
            while (local_70 = piVar9, cVar5 == '\0') {
              cVar5 = *(char *)(*piVar2 + 0xd);
              piVar9 = piVar2;
              piVar2 = (int *)*piVar2;
            }
          }
          else {
            cVar5 = *(char *)(piVar9[1] + 0xd);
            piVar4 = (int *)piVar9[1];
            piVar2 = piVar9;
            while ((piVar9 = piVar4, local_70 = piVar9, cVar5 == '\0' &&
                   (piVar2 == (int *)piVar9[2]))) {
              cVar5 = *(char *)(piVar9[1] + 0xd);
              piVar4 = (int *)piVar9[1];
              piVar2 = piVar9;
            }
          }
        }
      }
      else if (*local_74 == '\x02') {
        local_6c = local_6c + 0x10;
      }
      else {
        local_68 = local_68 + 1;
      }
      uVar8 = FUN_004383a0(&local_74,(int *)&local_28);
      pcVar6 = local_3c;
      cVar5 = (char)uVar8;
    }
    if (*local_38 == '\x01') {
      if (*(char *)((int)piVar14 + 0xd) == '\0') {
        piVar9 = (int *)piVar14[2];
        if (*(char *)((int)piVar9 + 0xd) == '\0') {
          cVar5 = *(char *)(*piVar9 + 0xd);
          piVar14 = piVar9;
          piVar9 = (int *)*piVar9;
          while (local_34 = piVar14, cVar5 == '\0') {
            cVar5 = *(char *)(*piVar9 + 0xd);
            piVar14 = piVar9;
            piVar9 = (int *)*piVar9;
          }
        }
        else {
          cVar5 = *(char *)(piVar14[1] + 0xd);
          piVar2 = (int *)piVar14[1];
          piVar9 = piVar14;
          while ((piVar14 = piVar2, local_34 = piVar14, cVar5 == '\0' &&
                 (piVar9 == (int *)piVar14[2]))) {
            cVar5 = *(char *)(piVar14[1] + 0xd);
            piVar2 = (int *)piVar14[1];
            piVar9 = piVar14;
          }
        }
      }
    }
    else if (*local_38 == '\x02') {
      local_30 = local_30 + 0x10;
    }
    else {
      local_2c = local_2c + 1;
    }
  } while( true );
}


