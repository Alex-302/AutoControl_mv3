// FUN_0040d400 @ 0040d400 size=1465 callers=1

undefined4 * __fastcall FUN_0040d400(undefined4 *param_1,DWORD *param_2)

{
  DWORD *pDVar1;
  undefined3 uVar2;
  undefined1 uVar3;
  char cVar4;
  bool bVar5;
  LPCWSTR pWVar6;
  uint *puVar7;
  int iVar8;
  undefined4 *puVar9;
  void **ppvVar10;
  undefined4 *puVar11;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  void *pvVar12;
  undefined4 extraout_ECX_01;
  undefined4 uVar13;
  byte ****ppppbVar14;
  uint uVar15;
  DWORD *pDVar16;
  undefined4 *puVar17;
  undefined4 local_f8;
  void *local_f4 [4];
  undefined4 local_e4;
  uint local_e0;
  undefined4 local_dc;
  undefined1 local_d8;
  void *local_d4;
  int iStack_d0;
  int iStack_cc;
  undefined4 uStack_c8;
  undefined4 local_c4;
  undefined1 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined1 local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined1 local_a8;
  undefined4 *local_a4;
  byte ***local_a0;
  void *local_9c [4];
  undefined4 local_8c;
  uint local_88;
  void *local_84;
  undefined1 *puStack_80;
  undefined4 local_7c;
  void *local_78;
  undefined4 *local_74 [3];
  undefined4 local_68;
  int *local_64;
  byte ***local_60 [4];
  int local_50;
  uint local_4c;
  void *local_48 [4];
  undefined4 local_38;
  uint local_34;
  void *local_30 [4];
  undefined4 local_20;
  uint local_1c;
  int *local_18;
  uint local_14;
  DWORD *local_10;
  uint local_c;
  char local_5;
  
  local_7c = 0xffffffff;
  puStack_80 = &LAB_0047a247;
  local_84 = ExceptionList;
  uVar15 = 0;
  local_14 = 0;
  puVar9 = (undefined4 *)param_2[1];
  puVar17 = (undefined4 *)*param_2;
  ExceptionList = &local_84;
  ppvVar10 = &local_84;
  local_a4 = param_1;
  local_10 = param_2;
  if (puVar17 != puVar9) {
    do {
      puVar9 = puVar9 + -7;
      ppvVar10 = ExceptionList;
      if (puVar17 == puVar9) break;
      FUN_00452da0(puVar17,puVar9);
      puVar17 = puVar17 + 7;
      ppvVar10 = ExceptionList;
    } while (puVar17 != puVar9);
  }
  ExceptionList = ppvVar10;
  local_e0 = 0xf;
  local_e4 = 0;
  local_f4[0] = (void *)((uint)local_f4[0] & 0xffffff00);
  local_34 = 0xf;
  local_38 = 0;
  local_48[0] = (void *)((uint)local_48[0] & 0xffffff00);
  local_7c._1_3_ = 0;
  uVar2 = local_7c._1_3_;
  local_7c._0_1_ = 1;
  local_7c._1_3_ = 0;
  pDVar16 = (DWORD *)*local_10;
  pDVar1 = (DWORD *)local_10[1];
  if (pDVar16 != pDVar1) {
    local_10 = pDVar16 + 1;
    do {
      pWVar6 = (LPCWSTR)FUN_00407180(local_9c,*pDVar16);
      local_7c._0_1_ = 2;
      FUN_00404580((LPSTR)local_60,pWVar6,0x7fffffff);
      local_7c._0_1_ = 4;
      uVar3 = (undefined1)local_7c;
      local_7c._0_1_ = 4;
      if (7 < local_88) {
        if ((0x7fffffff < local_88 + 1) ||
           ((pvVar12 = local_9c[0], 0xfff < (local_88 + 1) * 2 &&
            ((((uVar3 = (undefined1)local_7c, ((uint)local_9c[0] & 0x1f) != 0 ||
               (pvVar12 = *(void **)((int)local_9c[0] + -4), local_9c[0] <= pvVar12)) ||
              ((uint)((int)local_9c[0] - (int)pvVar12) < 4)) ||
             (0x23 < (uint)((int)local_9c[0] - (int)pvVar12))))))) goto LAB_0040d848;
        FID_conflict__free(pvVar12);
      }
      local_88 = 7;
      local_8c = 0;
      local_9c[0] = (void *)((uint)local_9c[0] & 0xffff0000);
      local_64 = (int *)&DAT_0000000f;
      local_68 = 0;
      local_78 = (void *)((uint)local_78 & 0xffffff00);
      FUN_0043ace0(&local_78,(uint *)"%u ; %s ; %s",0xc);
      local_7c._0_1_ = 5;
      puVar7 = FUN_00441620(local_30,(char *)&local_78);
      local_7c._0_1_ = 6;
      FUN_00434c30(puVar7);
      local_7c._0_1_ = 5;
      uVar13 = extraout_ECX;
      if (0xf < local_1c) {
        pvVar12 = local_30[0];
        if ((0xfff < local_1c + 1) &&
           (((uVar3 = (undefined1)local_7c, ((uint)local_30[0] & 0x1f) != 0 ||
             (pvVar12 = *(void **)((int)local_30[0] + -4), local_30[0] <= pvVar12)) ||
            (((uint)((int)local_30[0] - (int)pvVar12) < 4 ||
             (0x23 < (uint)((int)local_30[0] - (int)pvVar12))))))) goto LAB_0040d848;
        FID_conflict__free(pvVar12);
        uVar13 = extraout_ECX_00;
      }
      local_7c._0_1_ = 4;
      local_1c = 0xf;
      local_20 = 0;
      local_30[0] = (void *)((uint)local_30[0] & 0xffffff00);
      if (&DAT_0000000f < local_64) {
        pvVar12 = local_78;
        if (((undefined1 *)0xfff < (undefined1 *)((int)local_64 + 1)) &&
           (((uVar3 = (undefined1)local_7c, ((uint)local_78 & 0x1f) != 0 ||
             (pvVar12 = *(void **)((int)local_78 + -4), local_78 <= pvVar12)) ||
            (((uint)((int)local_78 - (int)pvVar12) < 4 ||
             (0x23 < (uint)((int)local_78 - (int)pvVar12))))))) {
LAB_0040d848:
          local_7c._0_1_ = uVar3;
                    /* WARNING: Subroutine does not return */
          FUN_00465fb2();
        }
        FID_conflict__free(pvVar12);
        uVar13 = extraout_ECX_01;
      }
      local_dc = 0;
      local_d8 = 0;
      local_d4 = (void *)0x0;
      iStack_d0 = 0;
      iStack_cc = 0;
      uStack_c8 = 0;
      local_c4 = 0;
      local_c0 = 0;
      local_bc = 0;
      local_b8 = 0;
      local_b4 = 0;
      local_b0 = 0;
      local_ac = 0;
      local_a8 = 0;
      local_7c._0_1_ = 7;
      iVar8 = FUN_0043ab50(local_60,(byte *)"parent-window",uVar13,0xd);
      if (iVar8 == -1) {
LAB_0040d730:
        local_5 = '\0';
      }
      else {
        local_1c = 0xf;
        local_20 = 0;
        local_30[0] = (void *)((uint)local_30[0] & 0xffffff00);
        FUN_0043ace0(local_30,(uint *)"%s-%s%s(\\w+)",0xc);
        local_7c = CONCAT31(local_7c._1_3_,8);
        local_14 = uVar15 | 1;
        local_c = local_14;
        puVar9 = FUN_004416c0(local_9c,(char *)local_30);
        local_7c = 9;
        local_14 = uVar15 | 3;
        local_18 = FUN_00441760(local_74,puVar9);
        local_7c._0_1_ = 10;
        local_7c._1_3_ = 0;
        local_14 = uVar15 | 7;
        local_a0 = (byte ***)local_60;
        if (0xf < local_4c) {
          local_a0 = local_60[0];
        }
        ppppbVar14 = local_60;
        if (0xf < local_4c) {
          ppppbVar14 = (byte ****)local_60[0];
        }
        local_c = local_14;
        cVar4 = FUN_004466f0(&local_dc,local_18,(byte *)ppppbVar14,
                             (byte *)((int)local_a0 + local_50),ppppbVar14,local_a0);
        local_5 = '\x01';
        uVar15 = local_c;
        if (cVar4 == '\0') goto LAB_0040d730;
      }
      if ((uVar15 & 4) != 0) {
        local_14 = uVar15 & 0xfffffffb;
        local_c = local_14;
        if (local_74[0] != (undefined4 *)0x0) {
          LOCK();
          iVar8 = local_74[0][8] + -1;
          local_74[0][8] = iVar8;
          UNLOCK();
          puVar9 = local_74[0];
          if (iVar8 == 0) {
            while (puVar9 != (undefined4 *)0x0) {
              puVar17 = (undefined4 *)puVar9[3];
              puVar9[3] = 0;
              (**(code **)*puVar9)(1);
              puVar9 = puVar17;
            }
          }
        }
        uVar15 = local_c;
        local_74[0] = (undefined4 *)0x0;
        local_7c._0_1_ = 0xb;
        local_7c._1_3_ = 0;
        if ((local_64 != (int *)0x0) &&
           (puVar9 = (undefined4 *)(**(code **)(*local_64 + 8))(), puVar9 != (undefined4 *)0x0)) {
          (**(code **)*puVar9)(1);
        }
      }
      if ((uVar15 & 2) != 0) {
        uVar15 = uVar15 & 0xfffffffd;
        if (0xf < local_88) {
          FUN_00402430(local_9c[0],local_88 + 1,1);
        }
        local_88 = 0xf;
        local_8c = 0;
        local_9c[0] = (void *)((uint)local_9c[0] & 0xffffff00);
      }
      local_7c = 7;
      if (((uVar15 & 1) != 0) && (uVar15 = uVar15 & 0xfffffffe, 0xf < local_1c)) {
        FUN_00402430(local_30[0],local_1c + 1,1);
      }
      pvVar12 = local_d4;
      if (local_5 != '\0') {
        puVar9 = &local_b0;
        if (1 < (uint)((iStack_d0 - (int)local_d4) / 0xc)) {
          puVar9 = (undefined4 *)((int)local_d4 + 0xc);
        }
        ppvVar10 = (void **)FUN_00433a80(puVar9,(undefined1 *)local_30);
        if (local_48 != ppvVar10) {
          if (0xf < local_34) {
            FUN_00402430(local_48[0],local_34 + 1,1);
          }
          local_34 = 0xf;
          local_38 = 0;
          local_48[0] = (void *)((uint)local_48[0] & 0xffffff00);
          FUN_0043b1c0(local_48,(uint *)ppvVar10);
        }
        if (0xf < local_1c) {
          FUN_00402430(local_30[0],local_1c + 1,1);
        }
        if (pvVar12 != (void *)0x0) {
          FUN_00402430(pvVar12,(iStack_cc - (int)pvVar12) / 0xc,0xc);
        }
        local_7c._0_1_ = 1;
        uVar2 = local_7c._1_3_;
        if (0xf < local_4c) {
          FUN_00402430(local_60[0],local_4c + 1,1);
          uVar2 = local_7c._1_3_;
        }
        break;
      }
      bVar5 = FUN_004410a0((byte *)local_10,(byte *)"cmd.exe");
      if (bVar5) {
        FUN_0040d9c0(&local_f8,pDVar16);
      }
      FUN_004041d0((int)&local_dc);
      local_7c._0_1_ = 1;
      if (0xf < local_4c) {
        FUN_00402430(local_60[0],local_4c + 1,1);
      }
      local_10 = local_10 + 7;
      pDVar16 = pDVar16 + 7;
      uVar2 = local_7c._1_3_;
    } while (pDVar16 != pDVar1);
  }
  local_7c._1_3_ = uVar2;
  puVar17 = local_a4;
  puVar9 = local_a4 + 1;
  *local_a4 = local_f8;
  local_a4[6] = 0xf;
  local_a4[5] = 0;
  puVar11 = puVar9;
  if (0xf < (uint)local_a4[6]) {
    puVar11 = (undefined4 *)*puVar9;
  }
  *(undefined1 *)puVar11 = 0;
  FUN_0043ade0(puVar9,local_f4,0,0xffffffff);
  local_7c = CONCAT31(local_7c._1_3_,0xd);
  puVar17[0xc] = 0xf;
  puVar17[0xb] = 0;
  *(undefined1 *)(puVar17 + 7) = 0;
  FUN_0043ade0(puVar17 + 7,local_48,0,0xffffffff);
  if (0xf < local_34) {
    FUN_00402430(local_48[0],local_34 + 1,1);
  }
  local_34 = 0xf;
  local_38 = 0;
  local_48[0] = (void *)((uint)local_48[0] & 0xffffff00);
  if (0xf < local_e0) {
    FUN_00402430(local_f4[0],local_e0 + 1,1);
  }
  ExceptionList = local_84;
  return puVar17;
}


