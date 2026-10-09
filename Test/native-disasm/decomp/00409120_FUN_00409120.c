// FUN_00409120 @ 00409120 size=1064 callers=1

/* WARNING: Removing unreachable block (ram,0x00409611) */

void FUN_00409120(void)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  FILE *pFVar4;
  size_t sVar5;
  char ****ppppcVar6;
  char *pcVar7;
  int iVar8;
  uint uVar9;
  double in_XMM0_Qa;
  undefined1 uVar10;
  void *pvVar11;
  char local_114 [80];
  double local_c4;
  char local_b8 [16];
  char local_a8 [8];
  undefined4 local_a0;
  undefined4 local_9c;
  char local_98 [8];
  undefined4 local_90;
  undefined4 local_8c;
  undefined1 *local_88;
  void *local_84;
  undefined1 *puStack_80;
  undefined4 local_7c;
  uint local_78;
  int local_74;
  uint local_70;
  char local_6c [8];
  undefined8 local_64;
  undefined1 local_5c [8];
  undefined8 local_54;
  char local_4c [8];
  undefined4 local_44;
  undefined4 local_40;
  char local_3c [8];
  undefined4 local_34;
  undefined4 local_30;
  char ***local_2c [4];
  uint local_1c;
  uint local_18;
  undefined8 local_14;
  uint local_c;
  char local_5;
  
  local_7c = 0xffffffff;
  puStack_80 = &LAB_00479ba1;
  local_84 = ExceptionList;
  local_88 = &stack0xfffffee0;
  ExceptionList = &local_84;
  __aulldiv(DAT_004a23a8,DAT_004a23ac,100,0);
  FUN_00477f00();
  local_c4 = DAT_0048f278;
  if (DAT_0048f278 <= in_XMM0_Qa) {
    local_c4 = in_XMM0_Qa;
  }
  local_18 = 0xf;
  local_1c = 0;
  local_2c[0] = (char ***)((uint)local_2c[0] & 0xffffff00);
  local_7c = 1;
  local_3c[0] = '\0';
  FUN_004381d0(&local_34,'\0');
  local_7c._0_1_ = 2;
  local_5 = '\0';
  do {
    pFVar4 = (FILE *)___acrt_iob_func(0);
    pvVar11 = (void *)0x4091ba;
    sVar5 = _fread(&local_c,1,4,pFVar4);
    if (sVar5 != 4) {
LAB_0040964f:
      FUN_00434820(local_3c);
      if (0xf < local_18) {
        ppppcVar6 = (char ****)local_2c[0];
        if (0xfff < local_18 + 1) {
          if (((uint)local_2c[0] & 0x1f) != 0) {
                    /* WARNING: Subroutine does not return */
            FUN_00465fb2();
          }
          ppppcVar6 = (char ****)local_2c[0][-1];
          if (local_2c[0] <= ppppcVar6) {
                    /* WARNING: Subroutine does not return */
            FUN_00465fb2();
          }
          if ((uint)((int)local_2c[0] - (int)ppppcVar6) < 4) {
                    /* WARNING: Subroutine does not return */
            FUN_00465fb2();
          }
          if (0x23 < (uint)((int)local_2c[0] - (int)ppppcVar6)) {
                    /* WARNING: Subroutine does not return */
            FUN_00465fb2();
          }
        }
        FID_conflict__free(ppppcVar6);
      }
      ExceptionList = local_84;
      return;
    }
    if ((local_c == 0) ||
       (local_c4 <= (double)(int)local_c + (double)(&DAT_0048f2d0)[-((int)local_c >> 0x1f)])) {
      local_6c[0] = '\0';
      local_64 = 0;
      FUN_00451110(local_6c,(uint *)"stdinMsgLen");
      local_5c[0] = 0;
      local_54 = 0;
      FUN_00451040(local_5c,local_c);
      local_7c._0_1_ = 0x11;
      FUN_00434b50(local_a8,local_6c,local_4c,'\x01','\x02');
      local_7c._0_1_ = 0x13;
      _eh_vector_destructor_iterator_(local_6c,0x10,2,FUN_00434820);
      local_7c._0_1_ = 0x14;
      FUN_00434b50(local_b8,local_a8,local_98,'\x01','\x02');
      local_7c._0_1_ = 0x15;
                    /* WARNING: Ignoring partial resolution of indirect */
      uVar10 = 0;
      FUN_0043ace0(&stack0xfffffec8,(uint *)"NH-badMsgLen",0xc);
      FUN_00408c90(local_b8,pvVar11);
      FUN_00434820(local_b8);
      local_7c._0_1_ = 2;
      _eh_vector_destructor_iterator_(local_a8,0x10,1,FUN_00434820);
      goto LAB_0040964f;
    }
    if (local_c < local_1c) {
      if (100000 < local_1c) {
        uVar9 = 5000;
        if (5000 < local_c + 1) {
          uVar9 = local_c + 1;
        }
        if (local_1c < uVar9) {
          FUN_0043aef0(local_2c,uVar9 - local_1c,'\0');
        }
        else {
          ppppcVar6 = local_2c;
          if (0xf < local_18) {
            ppppcVar6 = (char ****)local_2c[0];
          }
          local_1c = uVar9;
          *(char *)((int)ppppcVar6 + uVar9) = '\0';
        }
        FUN_00435410(local_2c);
      }
    }
    else {
      uVar9 = local_c + 1;
      if (local_1c < uVar9) {
        FUN_0043aef0(local_2c,uVar9 - local_1c,'\0');
      }
      else {
        ppppcVar6 = local_2c;
        if (0xf < local_18) {
          ppppcVar6 = (char ****)local_2c[0];
        }
        local_1c = uVar9;
        *(char *)((int)ppppcVar6 + uVar9) = '\0';
      }
    }
    ppppcVar6 = local_2c;
    if (0xf < local_18) {
      ppppcVar6 = (char ****)local_2c[0];
    }
    pFVar4 = (FILE *)___acrt_iob_func(0);
    pvVar11 = (void *)0x409285;
    sVar5 = _fread(ppppcVar6,1,local_c,pFVar4);
    if (sVar5 != local_c) goto LAB_0040964f;
    ppppcVar6 = local_2c;
    if (0xf < local_18) {
      ppppcVar6 = (char ****)local_2c[0];
    }
    *(char *)((int)ppppcVar6 + local_c) = '\0';
    ppppcVar6 = local_2c;
    if (0xf < local_18) {
      ppppcVar6 = (char ****)local_2c[0];
    }
    FUN_00440fd0(local_98,(char *)ppppcVar6);
    uVar3 = local_30;
    uVar2 = local_34;
    cVar1 = local_3c[0];
    local_3c[0] = local_98[0];
    local_98[0] = cVar1;
    local_34 = local_90;
    local_90 = uVar2;
    local_30 = local_8c;
    local_8c = uVar3;
    FUN_00434820(local_98);
    pcVar7 = (char *)FUN_00440e70(local_3c,(uint *)&DAT_0048cf60);
    FUN_004536b0(pcVar7,&local_70);
    DAT_0049da0c = local_70;
    FUN_00437970(&local_74);
    iVar8 = local_74;
    if (local_74 != DAT_004a2824) {
      local_7c._0_1_ = 3;
      local_4c[0] = '\0';
      FUN_004381d0(&local_44,'\0');
      local_7c = CONCAT31(local_7c._1_3_,5);
      FUN_00440e70(local_3c,(uint *)"content");
      pcVar7 = (char *)(**(code **)(iVar8 + 0xc))();
      local_14 = 0;
      cVar1 = *pcVar7;
      uVar2 = *(undefined4 *)(pcVar7 + 8);
      uVar3 = *(undefined4 *)(pcVar7 + 0xc);
      *pcVar7 = '\0';
      pcVar7[8] = '\0';
      pcVar7[9] = '\0';
      pcVar7[10] = '\0';
      pcVar7[0xb] = '\0';
      pcVar7[0xc] = '\0';
      pcVar7[0xd] = '\0';
      pcVar7[0xe] = '\0';
      pcVar7[0xf] = '\0';
      local_a8[0] = local_4c[0];
      local_9c = local_40;
      local_a0 = local_44;
      local_4c[0] = cVar1;
      local_44 = uVar2;
      local_40 = uVar3;
      FUN_00434820(local_a8);
      FUN_00434820(local_114);
      local_7c._0_1_ = 4;
      local_7c._1_3_ = 0;
      FUN_004355e0(&stack0xfffffec8,(uint *)"callback");
      iVar8 = FUN_004341b0(local_3c,pvVar11);
      if (iVar8 != 0) {
        pcVar7 = (char *)FUN_00440e70(local_3c,(uint *)"callback");
        FUN_00453810(pcVar7,&local_78);
        FUN_00408760(local_78,local_4c);
      }
      if (local_5 != '\0') {
        FUN_00434820(local_4c);
        goto LAB_0040964f;
      }
      local_7c._0_1_ = 2;
      FUN_00434820(local_4c);
    }
  } while( true );
}


