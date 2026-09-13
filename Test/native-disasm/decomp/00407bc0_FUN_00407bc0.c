// FUN_00407bc0 @ 00407bc0 size=1607 callers=1

char __fastcall FUN_00407bc0(HANDLE param_1)

{
  char cVar1;
  uint uVar2;
  void *pvVar3;
  byte *pbVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  uint *puVar8;
  int *piVar9;
  char *pcVar10;
  undefined4 extraout_ECX;
  byte ****ppppbVar11;
  char cVar12;
  uint uVar13;
  bool bVar14;
  uint uVar15;
  void **ppvVar16;
  char local_8c [8];
  undefined8 local_84;
  undefined1 local_7c [8];
  undefined8 local_74;
  byte ***local_6c [4];
  uint local_5c;
  uint local_58;
  void *local_54 [2];
  char local_4c [4];
  undefined4 *local_48;
  undefined4 *local_44;
  uint local_40;
  void *local_3c [2];
  char local_34 [8];
  undefined1 *local_2c;
  undefined4 *local_28;
  undefined4 *local_24;
  int *local_20;
  undefined4 *local_1c;
  int local_18;
  undefined1 local_11;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00479854;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_004077b0((int *)local_6c,param_1);
  local_8 = 0;
  if (DAT_004a2748 == '\0') {
    local_18 = 0;
  }
  else if (DAT_004a2748 == '\x01') {
    local_18 = DAT_004a2750[1];
  }
  else if (DAT_004a2748 == '\x02') {
    local_18 = DAT_004a2750[1] - *DAT_004a2750 >> 4;
  }
  else {
    local_18 = 1;
  }
  cVar12 = '\0';
  if ('\0' < (char)local_18) {
    do {
      ppvVar16 = local_54;
      uVar15 = 0;
      pvVar3 = (void *)FUN_00434600(&DAT_004a2748,(int)cVar12);
      pvVar3 = (void *)FUN_00434600(pvVar3,uVar15);
      pbVar4 = (byte *)FUN_00440bb0(pvVar3,ppvVar16);
      puVar8 = (uint *)(pbVar4 + 0x10);
      if (0xf < *(uint *)(pbVar4 + 0x14)) {
        pbVar4 = *(byte **)pbVar4;
      }
      uVar15 = *puVar8;
      ppppbVar11 = local_6c;
      if (0xf < local_58) {
        ppppbVar11 = (byte ****)local_6c[0];
      }
      uVar13 = uVar15;
      if (local_5c < uVar15) {
        uVar13 = local_5c;
      }
      if (uVar13 == 0) {
LAB_00407cd4:
        if (local_5c < uVar15) {
          uVar13 = 0xffffffff;
        }
        else {
          uVar13 = (uint)(uVar15 < local_5c);
        }
      }
      else {
        while (uVar2 = uVar13 - 4, 3 < uVar13) {
          if (*ppppbVar11 != *(byte ****)pbVar4) goto LAB_00407c97;
          ppppbVar11 = ppppbVar11 + 1;
          pbVar4 = pbVar4 + 4;
          uVar13 = uVar2;
        }
        if (uVar2 == 0xfffffffc) {
LAB_00407ccb:
          uVar13 = 0;
        }
        else {
LAB_00407c97:
          bVar14 = *(byte *)ppppbVar11 < *pbVar4;
          if ((*(byte *)ppppbVar11 == *pbVar4) &&
             ((uVar2 == 0xfffffffd ||
              ((bVar14 = *(byte *)((int)ppppbVar11 + 1) < pbVar4[1],
               *(byte *)((int)ppppbVar11 + 1) == pbVar4[1] &&
               ((uVar2 == 0xfffffffe ||
                ((bVar14 = *(byte *)((int)ppppbVar11 + 2) < pbVar4[2],
                 *(byte *)((int)ppppbVar11 + 2) == pbVar4[2] &&
                 ((uVar2 == 0xffffffff ||
                  (bVar14 = *(byte *)((int)ppppbVar11 + 3) < pbVar4[3],
                  *(byte *)((int)ppppbVar11 + 3) == pbVar4[3])))))))))))) goto LAB_00407ccb;
          uVar13 = -(uint)bVar14 | 1;
        }
        if (uVar13 == 0) goto LAB_00407cd4;
      }
      if (0xf < local_40) {
        pvVar3 = local_54[0];
        if ((0xfff < local_40 + 1) &&
           ((((((uint)local_54[0] & 0x1f) != 0 ||
              (pvVar3 = *(void **)((int)local_54[0] + -4), local_54[0] <= pvVar3)) ||
             ((uint)((int)local_54[0] - (int)pvVar3) < 4)) ||
            (0x23 < (uint)((int)local_54[0] - (int)pvVar3))))) {
                    /* WARNING: Subroutine does not return */
          FUN_00465fb2();
        }
        FID_conflict__free(pvVar3);
      }
      if (uVar13 == 0) goto LAB_00408046;
      cVar12 = cVar12 + '\x01';
    } while (cVar12 < (char)local_18);
  }
  if ((char)local_18 < '\b') {
    local_8c[0] = '\x03';
    local_84 = 0;
    puVar5 = operator_new(0x18);
    local_2c = &local_11;
    local_8._0_1_ = 2;
    local_28 = puVar5;
    local_24 = puVar5;
    local_1c = puVar5;
    if (puVar5 != (undefined4 *)0x0) {
      puVar5[5] = 0xf;
      puVar5[4] = 0;
      puVar6 = puVar5;
      if (0xf < (uint)puVar5[5]) {
        puVar6 = (undefined4 *)*puVar5;
      }
      *(undefined1 *)puVar6 = 0;
      FUN_0043ade0(puVar5,local_6c,0,0xffffffff);
    }
    local_84 = CONCAT44(local_28,puVar5);
    local_8._0_1_ = 3;
    puVar5 = FUN_00407900(local_54,(LPCSTR)local_6c);
    local_8._0_1_ = 4;
    local_74 = 0;
    local_7c[0] = 3;
    puVar6 = operator_new(0x18);
    local_2c = &local_11;
    local_8 = CONCAT31(local_8._1_3_,6);
    local_28 = puVar6;
    local_24 = puVar6;
    local_1c = puVar6;
    if (puVar6 != (undefined4 *)0x0) {
      puVar6[5] = 0xf;
      puVar6[4] = 0;
      puVar7 = puVar6;
      if (0xf < (uint)puVar6[5]) {
        puVar7 = (undefined4 *)*puVar6;
      }
      *(undefined1 *)puVar7 = 0;
      FUN_0043ade0(puVar6,puVar5,0,0xffffffff);
    }
    local_74 = CONCAT44(local_28,puVar6);
    if (0xf < local_40) {
      FUN_00402430(local_54[0],local_40 + 1,1);
    }
    local_40 = 0xf;
    local_44 = (undefined4 *)0x0;
    local_54[0] = (void *)((uint)local_54[0] & 0xffffff00);
    local_8._0_1_ = 7;
    FUN_00433d40(&DAT_004a2748,local_8c,(char *)local_6c);
    local_8._0_1_ = 0;
    _eh_vector_destructor_iterator_(local_8c,0x10,2,FUN_00434820);
    local_8c[0] = '\0';
    local_84 = 0;
    FUN_00451110(local_8c,(uint *)&DAT_0048cf28);
    local_8._0_1_ = 8;
    FUN_00434940(local_7c,&DAT_004a2748);
    local_8._0_1_ = 9;
    FUN_00434b50(local_4c,local_8c,(char *)local_6c,'\x01','\x02');
    local_8._0_1_ = 0xb;
    _eh_vector_destructor_iterator_(local_8c,0x10,2,FUN_00434820);
    local_8._0_1_ = 0xc;
    FUN_00434b50(local_34,local_4c,(char *)local_3c,'\x01','\x02');
    local_8._0_1_ = 0xd;
    FUN_00408600(0x46,local_34);
    FUN_00434820(local_34);
    local_8 = (uint)local_8._1_3_ << 8;
    _eh_vector_destructor_iterator_(local_4c,0x10,1,FUN_00434820);
    cVar12 = (char)local_18;
  }
  else {
    local_20 = (int *)0x0;
    local_1c = (undefined4 *)0x0;
    local_20 = (int *)FUN_0043fc70();
    local_8._0_1_ = 0xe;
    FUN_00407a70(&local_48);
    puVar7 = local_24;
    puVar6 = local_44;
    local_8._0_1_ = 0xf;
    for (puVar5 = local_48; puVar5 != puVar6; puVar5 = puVar5 + 1) {
      puVar8 = (uint *)FUN_004077b0((int *)&local_84,(HANDLE)*puVar5);
      local_8._0_1_ = 0x10;
      FUN_00446ca0(&local_20,&local_2c,extraout_ECX,puVar8,puVar7);
      local_8._0_1_ = 0xf;
      if (0xf < local_74._4_4_) {
        FUN_00402430((void *)local_84,local_74._4_4_ + 1,1);
      }
    }
    local_8 = CONCAT31(local_8._1_3_,0xe);
    if (local_48 != (undefined4 *)0x0) {
      FUN_00402430(local_48,(int)(local_40 - (int)local_48) >> 2,4);
    }
    cVar12 = '\0';
    if ('\0' < (char)local_18) {
      do {
        ppvVar16 = local_54;
        uVar15 = 0;
        pvVar3 = (void *)FUN_00434600(&DAT_004a2748,(int)cVar12);
        pvVar3 = (void *)FUN_00434600(pvVar3,uVar15);
        FUN_00440d90(pvVar3,ppvVar16);
        piVar9 = (int *)FUN_00432d50(&local_20,(int *)&local_24,(byte *)local_54);
        bVar14 = (int *)*piVar9 == local_20;
        if (0xf < local_40) {
          FUN_00402430(local_54[0],local_40 + 1,1);
        }
        if (bVar14) {
          FUN_00440c80(local_8c,local_6c);
          local_8._0_1_ = 0x11;
          puVar5 = FUN_00407900(local_3c,(LPCSTR)local_6c);
          local_8 = CONCAT31(local_8._1_3_,0x12);
          FUN_00440c80(local_7c,puVar5);
          if (&DAT_0000000f < local_28) {
            FUN_00402430(local_3c[0],(int)local_28 + 1,1);
          }
          local_28 = (undefined4 *)&DAT_0000000f;
          local_2c = (undefined1 *)0x0;
          local_3c[0] = (void *)((uint)local_3c[0] & 0xffffff00);
          local_8._0_1_ = 0x13;
          FUN_00434b50(local_4c,local_8c,(char *)local_6c,'\x01','\x02');
          local_8._0_1_ = 0x14;
          pcVar10 = (char *)FUN_00434600(&DAT_004a2748,(int)cVar12);
          cVar1 = *pcVar10;
          *pcVar10 = local_4c[0];
          puVar5 = *(undefined4 **)(pcVar10 + 8);
          uVar15 = *(uint *)(pcVar10 + 0xc);
          *(undefined4 **)(pcVar10 + 8) = local_44;
          *(uint *)(pcVar10 + 0xc) = local_40;
          local_4c[0] = cVar1;
          local_44 = puVar5;
          local_40 = uVar15;
          FUN_00434820(local_4c);
          local_8._0_1_ = 0xe;
          _eh_vector_destructor_iterator_(local_8c,0x10,2,FUN_00434820);
          local_8c[0] = '\0';
          local_84 = 0;
          FUN_00451110(local_8c,(uint *)&DAT_0048cf28);
          local_8._0_1_ = 0x15;
          FUN_00434940(local_7c,&DAT_004a2748);
          local_8._0_1_ = 0x16;
          FUN_00434b50(local_4c,local_8c,(char *)local_6c,'\x01','\x02');
          local_8._0_1_ = 0x18;
          _eh_vector_destructor_iterator_(local_8c,0x10,2,FUN_00434820);
          local_8._0_1_ = 0x19;
          FUN_00434b50(local_34,local_4c,(char *)local_3c,'\x01','\x02');
          local_8._0_1_ = 0x1a;
          FUN_00408600(0x46,local_34);
          FUN_00434820(local_34);
          local_8 = CONCAT31(local_8._1_3_,0xe);
          _eh_vector_destructor_iterator_(local_4c,0x10,1,FUN_00434820);
          FUN_0043c700(&local_20,&local_24,(int *)*local_20,local_20);
          FUN_00402430(local_20,1,0x28);
          goto LAB_00408046;
        }
        cVar12 = cVar12 + '\x01';
      } while (cVar12 < (char)local_18);
    }
    FUN_0043c700(&local_20,&local_24,(int *)*local_20,local_20);
    FUN_00402430(local_20,1,0x28);
    cVar12 = -1;
  }
LAB_00408046:
  if (0xf < local_58) {
    FUN_00402430(local_6c[0],local_58 + 1,1);
  }
  ExceptionList = local_10;
  return cVar12;
}


