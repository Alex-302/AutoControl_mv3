// FUN_0041b330 @ 0041b330 size=1150 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

HWND FUN_0041b330(void)

{
  POINT ptScreen;
  LONG LVar1;
  bool bVar2;
  UINT UVar3;
  undefined4 *puVar4;
  int iVar5;
  LPCSTR pCVar6;
  LPWSTR pWVar7;
  uint uVar8;
  undefined4 ***pppuVar9;
  int *this;
  HWND pHVar10;
  uint uVar11;
  float10 fVar12;
  undefined2 uVar13;
  undefined2 uVar14;
  undefined4 **local_10c [4];
  undefined4 local_fc;
  uint local_f8;
  undefined4 **local_f4 [4];
  undefined4 local_e4;
  uint local_e0;
  void *local_dc [4];
  undefined4 local_cc;
  uint local_c8;
  void *local_c4 [4];
  undefined4 local_b4;
  uint local_b0;
  void *local_ac [4];
  undefined4 local_9c;
  uint local_98;
  void *local_94 [4];
  undefined4 local_84;
  uint local_80;
  void *local_7c;
  undefined1 *puStack_78;
  uint local_74;
  void *local_70 [4];
  undefined4 local_60;
  uint local_5c;
  undefined4 local_58;
  undefined4 local_48;
  uint local_44;
  undefined4 **local_40 [4];
  uint local_30;
  uint local_2c;
  undefined4 local_28;
  int local_18;
  uint local_14;
  tagPOINT local_10;
  float local_8;
  
  local_74 = 0xffffffff;
  puStack_78 = &LAB_0047b78b;
  local_7c = ExceptionList;
  local_8 = 0.0;
  ExceptionList = &local_7c;
  GetCursorPos(&local_10);
  LVar1 = local_10.y;
  UVar3 = FUN_0041d3c0('\0',local_10.x,local_10.y);
  if (UVar3 != 0) {
    puVar4 = (undefined4 *)FUN_00419890(UVar3);
    ptScreen.y = LVar1;
    ptScreen.x = local_10.x;
    iVar5 = MenuItemFromPoint((HWND)0x0,(HMENU)puVar4[7],ptScreen);
    bVar2 = FUN_0041b060(puVar4,(ushort)iVar5);
    if (!bVar2) {
      puVar4 = FUN_00435260(local_94,(uint *)&DAT_0048d694);
      uVar11 = 2;
    }
    else {
      puVar4 = (undefined4 *)FUN_0041b1d0((undefined2 *)local_ac,puVar4);
      uVar11 = 1;
    }
    local_74 = (uint)!bVar2;
    local_58 = (void *)((uint)local_58._2_2_ << 0x10);
    local_44 = 7;
    local_48 = 0;
    local_8 = (float)uVar11;
    FUN_0043a750(&local_58,puVar4,0,0xffffffff);
    local_74 = 2;
    if ((uVar11 & 2) != 0) {
      uVar11 = uVar11 & 0xfffffffd;
      local_8 = (float)uVar11;
      if (7 < local_80) {
        FUN_00402430(local_94[0],local_80 + 1,2);
      }
      local_80 = 7;
      local_84 = 0;
      local_94[0] = (void *)((uint)local_94[0] & 0xffff0000);
    }
    local_74._0_1_ = 4;
    if ((uVar11 & 1) != 0) {
      uVar11 = uVar11 & 0xfffffffe;
      local_8 = (float)uVar11;
      if (7 < local_98) {
        FUN_00402430(local_ac[0],local_98 + 1,2);
      }
      local_98 = 7;
      local_9c = 0;
      local_ac[0] = (void *)((uint)local_ac[0] & 0xffff0000);
    }
    pCVar6 = (LPCSTR)FUN_00419e40(local_dc,UVar3);
    local_74._0_1_ = 5;
    pWVar7 = FUN_00404640((LPWSTR)local_c4,pCVar6);
    local_74 = CONCAT31(local_74._1_3_,6);
    FUN_0041b1d0((undefined2 *)local_70,(undefined4 *)pWVar7);
    if (7 < local_b0) {
      FUN_00402430(local_c4[0],local_b0 + 1,2);
    }
    local_b0 = 7;
    local_b4 = 0;
    local_c4[0] = (void *)((uint)local_c4[0] & 0xffff0000);
    local_74._0_1_ = 9;
    if (0xf < local_c8) {
      FUN_00402430(local_dc[0],local_c8 + 1,1);
    }
    local_c8 = 0xf;
    local_cc = 0;
    local_dc[0] = (void *)((uint)local_dc[0] & 0xffffff00);
    uVar8 = FUN_004443e0(&local_58,(ushort *)local_70);
    if (uVar8 == 0) {
      local_40[0] = (undefined4 **)((uint)local_40[0] & 0xffff0000);
      local_2c = 7;
      local_30 = uVar8;
      FUN_0043a750(local_40,&local_58,0,0xffffffff);
      pppuVar9 = local_40;
      local_74 = CONCAT31(local_74._1_3_,10);
      uVar11 = uVar11 | 4;
    }
    else {
      puVar4 = FUN_00441c70(local_10c,&local_58);
      local_74 = 0xb;
      local_8 = (float)(uVar11 | 8);
      pppuVar9 = (undefined4 ***)FUN_00441f50((undefined2 *)local_f4,puVar4,local_70);
      local_74 = 0xc;
      uVar11 = uVar11 | 0x18;
    }
    uVar13 = 0;
    uVar14 = 0;
    local_28 = (void *)((uint)local_28._2_2_ << 0x10);
    local_14 = 7;
    local_18 = 0;
    local_8 = (float)uVar11;
    FUN_0043a750(&local_28,pppuVar9,0,0xffffffff);
    uVar8 = CONCAT22(uVar14,uVar13);
    local_74 = 0xd;
    if ((uVar11 & 0x10) != 0) {
      uVar11 = uVar11 & 0xffffffef;
      if (7 < local_e0) {
        uVar8 = local_e0 + 1;
        pppuVar9 = (undefined4 ***)local_f4[0];
        FUN_00402430(local_f4[0],uVar8,2);
      }
      local_e0 = 7;
      local_e4 = 0;
      local_f4[0] = (undefined4 **)((uint)local_f4[0] & 0xffff0000);
    }
    if ((uVar11 & 8) != 0) {
      uVar11 = uVar11 & 0xfffffff7;
      if (7 < local_f8) {
        uVar8 = local_f8 + 1;
        pppuVar9 = (undefined4 ***)local_10c[0];
        FUN_00402430(local_10c[0],uVar8,2);
      }
      local_f8 = 7;
      local_fc = 0;
      local_10c[0] = (undefined4 **)((uint)local_10c[0] & 0xffff0000);
    }
    local_74 = CONCAT31(local_74._1_3_,0x10);
    if ((uVar11 & 4) != 0) {
      if (7 < local_2c) {
        uVar8 = local_2c + 1;
        pppuVar9 = (undefined4 ***)local_40[0];
        FUN_00402430(local_40[0],uVar8,2);
      }
      local_2c = 7;
      local_30 = 0;
      local_40[0] = (undefined4 **)((uint)local_40[0] & 0xffff0000);
    }
    this = FUN_00403760(&local_28,&DAT_0048cc44);
    iVar5 = 6;
    if (DAT_0048cc44 == 0) {
      iVar5 = 0;
    }
    uVar11 = FUN_0043a1d0(this,pppuVar9,uVar8,iVar5);
    FUN_00434f70(this,0,uVar11);
    if (local_18 != 0) {
      fVar12 = roundf((float)DAT_004a29c8 * _DAT_0048f218 * _DAT_0048f284);
      local_8 = (float)fVar12;
      pHVar10 = FUN_004058b0(&local_28,
                             *(undefined4 *)
                              (&DAT_004a2470 + *(int *)(*(int *)ThreadLocalStoragePointer + 4) * 4),
                             (undefined2)local_10.x,(short)((int)fVar12 + local_10.y));
      if (7 < local_14) {
        FUN_00402430(local_28,local_14 + 1,2);
      }
      local_14 = 7;
      local_28 = (void *)((uint)local_28 & 0xffff0000);
      local_18 = 0;
      if (7 < local_5c) {
        FUN_00402430(local_70[0],local_5c + 1,2);
      }
      local_5c = 7;
      local_70[0] = (void *)((uint)local_70[0] & 0xffff0000);
      local_60 = 0;
      if (7 < local_44) {
        FUN_00402430(local_58,local_44 + 1,2);
      }
      ExceptionList = local_7c;
      return pHVar10;
    }
    if (7 < local_14) {
      FUN_00402430(local_28,local_14 + 1,2);
    }
    local_14 = 7;
    local_18 = 0;
    local_28 = (void *)((uint)local_28 & 0xffff0000);
    FUN_00435170(local_70);
    FUN_00435170(&local_58);
  }
  ExceptionList = local_7c;
  return (HWND)0x0;
}


