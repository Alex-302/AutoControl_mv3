// FUN_00416fe0 @ 00416fe0 size=2051 callers=3

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void * __fastcall FUN_00416fe0(void *param_1,undefined4 *param_2,uint param_3)

{
  undefined1 uVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  BOOL BVar4;
  UINT UVar5;
  undefined4 *puVar6;
  LPSTR pCVar7;
  uint uVar8;
  UINT UVar9;
  int *piVar10;
  LPWSTR pWVar11;
  bool bVar12;
  int iVar13;
  HDROP pHVar14;
  void *pvVar15;
  bool bVar16;
  char cVar17;
  undefined ***pppuVar18;
  undefined4 uVar19;
  undefined4 uVar20;
  HDROP pHVar21;
  char *pcVar22;
  int local_100 [6];
  undefined4 local_e8 [6];
  undefined4 local_d0;
  undefined4 uStack_cc;
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  char local_c0 [8];
  undefined8 local_b8;
  undefined1 local_b0 [8];
  undefined8 local_a8;
  char local_a0 [16];
  undefined4 local_90;
  int local_8c [6];
  void *local_74;
  undefined1 *puStack_70;
  undefined4 local_6c;
  int local_68 [4];
  uint local_58;
  HGLOBAL local_50;
  HDROP local_4c;
  char local_48;
  undefined4 local_44;
  undefined4 local_3c [2];
  UINT local_34;
  uint local_30;
  void *local_2c;
  undefined1 local_25;
  uint local_24;
  undefined **local_20;
  UINT local_1c;
  undefined8 local_18;
  undefined4 *local_10;
  UINT local_c;
  HWND local_8;
  
  local_6c = 0xffffffff;
  puStack_70 = &LAB_0047b122;
  local_74 = ExceptionList;
  local_90 = 0;
  local_24 = *(uint *)ThreadLocalStoragePointer;
  iVar13 = 0;
  local_8 = *(HWND *)(&DAT_004a2470 + *(int *)(local_24 + 4) * 4);
  ExceptionList = &local_74;
  local_2c = param_1;
  local_10 = param_2;
  do {
    BVar4 = OpenClipboard(local_8);
    bVar16 = BVar4 != 0;
    local_25 = bVar16;
    if (bVar16) break;
    Sleep(10);
    iVar13 = iVar13 + 1;
  } while (iVar13 < 5);
  local_6c = 1;
  local_c0[0] = '\0';
  local_b8 = 0;
  FUN_00451110(local_c0,(uint *)"trueFmt");
  if ((*(int *)(local_24 + 8) < DAT_004a2e94) && (FUN_0045a219(&DAT_004a2e94), DAT_004a2e94 == -1))
  {
    _DAT_0049d9d0 = DAT_004a26f4;
    _DAT_0049d9d4 = 0xf;
    _DAT_0049d9d8 = 0xd;
    _DAT_0049d9dc = 1;
    FUN_0045a1da(&DAT_004a2e94);
  }
  iVar13 = 5;
  if (DAT_004a26f4 == 0) {
    iVar13 = 1;
  }
  iVar13 = GetPriorityClipboardFormat
                     ((UINT *)(&DAT_0049d9cc + (uint)(DAT_004a26f4 == 0) * 4),iVar13);
  if (iVar13 < 1) {
    iVar13 = 0;
  }
  else if (iVar13 == DAT_004a26f4) {
    iVar13 = 0x5b;
  }
  local_b0[0] = 0;
  local_a8 = 0;
  FUN_00451040(local_b0,iVar13);
  local_6c._0_1_ = 2;
  FUN_00434b50(&local_20,local_c0,local_a0,'\x01','\x02');
  local_6c._0_1_ = 4;
  _eh_vector_destructor_iterator_(local_c0,0x10,2,FUN_00434820);
  pvVar15 = local_2c;
  local_6c._0_1_ = 5;
  FUN_00434b50(local_2c,(char *)&local_20,(char *)&local_10,'\x01','\x02');
  pppuVar18 = &local_20;
  local_90 = 1;
  local_6c._0_1_ = 1;
  _eh_vector_destructor_iterator_(pppuVar18,0x10,1,FUN_00434820);
  cVar17 = (char)pppuVar18;
  UVar5 = FUN_00416d60((int)local_10);
  local_8 = (HWND)UVar5;
  if (UVar5 == 0) goto LAB_004177c5;
  uVar19 = 0x4171a4;
  FUN_00416c20(&local_25,&local_50,UVar5);
  pHVar14 = local_4c;
  local_6c._0_1_ = 6;
  if (local_50 == (HGLOBAL)0x0) {
LAB_004177a0:
    if (local_4c != (HDROP)0x0) {
      GlobalUnlock(local_4c);
    }
  }
  else if (local_4c != (HDROP)0x0) {
    local_20 = (undefined **)((uint)local_20 & 0xffffff00);
    local_18 = 0;
    FUN_00451040((undefined1 *)&local_20,UVar5);
    local_6c._0_1_ = 7;
    puVar6 = FUN_00440e70(local_2c,(uint *)"format");
    local_6c._0_1_ = 6;
    uVar1 = *(undefined1 *)puVar6;
    *(undefined1 *)puVar6 = local_20._0_1_;
    uVar20 = puVar6[2];
    local_20 = (undefined **)CONCAT31(local_20._1_3_,uVar1);
    uVar2 = puVar6[3];
    puVar6[2] = (undefined4)local_18;
    puVar6[3] = local_18._4_4_;
    local_18._0_4_ = uVar20;
    local_18._4_4_ = uVar2;
    FUN_00434820((char *)&local_20);
    pcVar22 = "content";
    uVar20 = 0x417222;
    local_10 = FUN_00440e70(local_2c,(uint *)"content");
    UVar5 = 0;
    switch(local_8) {
    case (HWND)0x1:
    case (HWND)0x5b:
      pHVar21 = pHVar14;
      do {
        piVar10 = &pHVar21->unused;
        pHVar21 = (HDROP)((int)&pHVar21->unused + 1);
      } while ((char)*piVar10 != '\0');
      UVar5 = (int)pHVar21 - (int)((int)&pHVar14->unused + 1);
      uVar8 = UVar5;
      if (param_3 < UVar5) {
        uVar8 = param_3;
      }
      if (uVar8 < 200000) {
        uVar19 = 0x417374;
        pCVar7 = FUN_00435630(local_8c,(uint *)pHVar14,uVar8);
        local_6c._0_1_ = 0xc;
        pHVar21 = pHVar14;
        param_3 = uVar8;
LAB_0041727e:
        FUN_00440c80(&stack0xfffffee4,(undefined4 *)pCVar7);
        FUN_004348c0(local_10,cVar17,uVar19,pHVar21,param_3);
        FUN_004061c0(local_8c);
      }
      else {
        FUN_00410550(&stack0xfffffee4,(int *)&local_c);
        FUN_004348c0(local_10,cVar17,uVar19,uVar20,pcVar22);
        local_8 = (HWND)0x0;
        if (UVar5 != 0) {
          do {
            local_30 = 0xf;
            uVar8 = UVar5 - (int)local_8;
            local_34 = 0;
            local_44 = (LPWSTR)((uint)local_44 & 0xffffff00);
            if (200000 < uVar8) {
              uVar8 = 200000;
            }
            FUN_0043ace0(&local_44,(uint *)((int)&pHVar14->unused + (int)local_8),uVar8);
            local_6c._0_1_ = 0xd;
            FUN_00440c80(&local_20,&local_44);
            local_6c._0_1_ = 0xe;
            FUN_004355e0(local_68,(uint *)&DAT_0048d624);
            local_6c._0_1_ = 0xf;
            FUN_00410660(local_c,local_68,(undefined1 *)&local_20);
            FUN_004061c0(local_68);
            FUN_00434820((char *)&local_20);
            local_6c._0_1_ = 6;
            FUN_004061c0(&local_44);
            local_8 = (HWND)((int)local_8 + 200000);
          } while (local_8 < UVar5);
        }
      }
      break;
    case (HWND)0x8:
      FUN_0040a7f0((int)pHVar14);
      local_20 = &PTR_FUN_0048ed48;
      local_8 = (HWND)0x0;
      cVar17 = '\0';
      uVar19 = GdipCreateBitmapFromGdiDib();
      local_18 = CONCAT44(local_18._4_4_,uVar19);
      local_1c = (UINT)local_8;
      local_6c._0_1_ = 0x15;
      FUN_00435260(local_e8,(uint *)&DAT_0048d62c);
      local_6c._0_1_ = 0x16;
      puVar6 = (undefined4 *)FUN_0040abb0(local_e8,local_3c);
      local_d0 = *puVar6;
      uStack_cc = puVar6[1];
      uStack_c8 = puVar6[2];
      uStack_c4 = puVar6[3];
      puVar6 = &local_d0;
      uVar19 = 0x417640;
      FUN_0040aa70(local_68,(int)&local_20,puVar6);
      local_6c._0_1_ = 0x18;
      uVar20 = 0x41764f;
      FUN_00435170(local_e8);
      if (local_58 < 0x30d41) {
        uVar20 = 0x417665;
        piVar10 = FUN_004043e0(local_8c,local_68);
        local_6c._0_1_ = 0x19;
        FUN_00440c80(&stack0xfffffee4,piVar10);
        FUN_004348c0(local_10,cVar17,uVar19,puVar6,uVar20);
        FUN_004061c0(local_8c);
      }
      else {
        FUN_00410550(&stack0xfffffee4,(int *)&local_c);
        FUN_004348c0(local_10,cVar17,uVar19,puVar6,uVar20);
        uVar8 = 0;
        if (local_58 != 0) {
          do {
            puVar6 = (undefined4 *)FUN_00435340(local_68,(undefined1 *)&local_b8,uVar8,200000);
            local_6c._0_1_ = 0x1a;
            piVar10 = FUN_004043e0(local_100,puVar6);
            local_6c._0_1_ = 0x1b;
            FUN_00440c80(local_a0,piVar10);
            local_6c._0_1_ = 0x1c;
            FUN_004355e0(local_8c,(uint *)&DAT_0048d634);
            local_6c._0_1_ = 0x1d;
            FUN_00410660(local_c,local_8c,local_a0);
            FUN_004061c0(local_8c);
            FUN_00434820(local_a0);
            FUN_004061c0(local_100);
            local_6c._0_1_ = 0x18;
            FUN_004061c0((undefined4 *)&local_b8);
            uVar8 = uVar8 + 200000;
          } while (uVar8 < local_58);
        }
      }
      FUN_004061c0(local_68);
      GdipDisposeImage();
      UVar5 = local_58;
      break;
    case (HWND)0xd:
      pHVar21 = pHVar14;
      do {
        piVar10 = &pHVar21->unused;
        pHVar21 = (HDROP)((int)&pHVar21->unused + 2);
      } while ((short)*piVar10 != 0);
      UVar5 = (int)pHVar21 - (int)((int)&pHVar14->unused + 2) >> 1;
      uVar8 = UVar5;
      if (param_3 < UVar5) {
        uVar8 = param_3;
      }
      local_c = UVar5;
      if (uVar8 < 200000) {
        pHVar21 = (HDROP)0xffffffff;
        uVar19 = 0x417277;
        pCVar7 = FUN_004044f0((LPSTR)local_8c,(LPCWSTR)pHVar14,-1,param_3);
        local_6c._0_1_ = 8;
        goto LAB_0041727e;
      }
      FUN_00410550(&stack0xfffffee4,(int *)&local_24);
      FUN_004348c0(local_10,cVar17,uVar19,uVar20,pcVar22);
      if (UVar5 != 0) {
        iVar13 = (UVar5 - 1) / 200000 + 1;
        pHVar14 = local_4c;
        do {
          pCVar7 = FUN_004044f0((LPSTR)local_8c,(LPCWSTR)pHVar14,-1,200000);
          local_6c._0_1_ = 9;
          FUN_00440c80(&local_20,(undefined4 *)pCVar7);
          local_6c._0_1_ = 10;
          FUN_004355e0(local_68,(uint *)&DAT_0048d624);
          local_6c._0_1_ = 0xb;
          FUN_00410660(local_24,local_68,(undefined1 *)&local_20);
          FUN_004061c0(local_68);
          FUN_00434820((char *)&local_20);
          local_6c._0_1_ = 6;
          FUN_004061c0(local_8c);
          pHVar14 = pHVar14 + 100000;
          iVar13 = iVar13 + -1;
          UVar5 = local_c;
        } while (iVar13 != 0);
      }
      break;
    case (HWND)0xf:
      pHVar21 = pHVar14;
      UVar5 = DragQueryFileW(pHVar14,0xffffffff,(LPWSTR)0x0,0);
      cVar17 = (char)pHVar21;
      uVar20 = 0;
      uVar19 = 0;
      uVar8 = 0x417467;
      FUN_00434b00(&local_20,(char *)0x0,(char *)0x0);
      local_30 = 7;
      local_34 = 0;
      local_44 = (LPWSTR)((uint)local_44._2_2_ << 0x10);
      local_6c._0_1_ = 0x11;
      bVar12 = false;
      local_8 = (HWND)0x0;
      local_24 = 0;
      if (UVar5 == 0) {
LAB_004175b4:
        FUN_00434900(&stack0xfffffee4,(undefined1 *)&local_20);
        FUN_004348c0(local_10,cVar17,uVar8,uVar19,uVar20);
      }
      else {
        do {
          UVar9 = DragQueryFileW(pHVar14,local_24,(LPWSTR)0x0,0);
          if (local_34 < UVar9) {
            FUN_0043a870(&local_44,UVar9 - local_34,0);
          }
          else {
            pWVar11 = (LPWSTR)&local_44;
            if (7 < local_30) {
              pWVar11 = local_44;
            }
            local_34 = UVar9;
            pWVar11[UVar9] = L'\0';
          }
          pWVar11 = (LPWSTR)&local_44;
          if (7 < local_30) {
            pWVar11 = local_44;
          }
          pHVar14 = local_4c;
          uVar8 = local_24;
          DragQueryFileW(local_4c,local_24,pWVar11,UVar9 + 1);
          cVar17 = (char)pHVar14;
          pCVar7 = FUN_00404580((LPSTR)local_8c,(LPCWSTR)&local_44,0x7fffffff);
          local_6c._0_1_ = 0x12;
          FUN_00440c80(local_a0,(undefined4 *)pCVar7);
          local_6c._0_1_ = 0x13;
          uVar19 = 0x41751d;
          FUN_00433e10(&local_20,local_a0);
          FUN_00434820(local_a0);
          local_6c._0_1_ = 0x11;
          uVar20 = 0x417531;
          FUN_004061c0(local_8c);
          local_8 = (HWND)((int)local_8 + UVar9);
          if (param_3 <= local_8) break;
          if ((199999 < local_8) || ((bVar12 && (local_24 == UVar5 - 1)))) {
            if (!bVar12) {
              FUN_00410550(&stack0xfffffee4,(int *)&local_c);
              FUN_004348c0(local_10,cVar17,uVar8,uVar19,uVar20);
              bVar12 = true;
            }
            FUN_004355e0(local_68,(uint *)&DAT_0048cf28);
            local_6c._0_1_ = 0x14;
            uVar19 = 0x41758d;
            FUN_00410660(local_c,local_68,(undefined1 *)&local_20);
            local_6c._0_1_ = 0x11;
            uVar20 = 0x41759c;
            FUN_004061c0(local_68);
            local_8 = (HWND)0x0;
          }
          local_24 = local_24 + 1;
          pHVar14 = local_4c;
        } while (local_24 < UVar5);
        if (!bVar12) goto LAB_004175b4;
      }
      FUN_00435170(&local_44);
      FUN_00434820((char *)&local_20);
    }
    local_20 = (undefined **)((uint)local_20 & 0xffffff00);
    local_18 = 0;
    FUN_00451040((undefined1 *)&local_20,UVar5);
    local_6c._0_1_ = 0x1e;
    puVar6 = FUN_00440e70(local_2c,(uint *)&DAT_0048d638);
    uVar1 = *(undefined1 *)puVar6;
    *(undefined1 *)puVar6 = local_20._0_1_;
    local_20 = (undefined **)CONCAT31(local_20._1_3_,uVar1);
    uVar3 = *(undefined8 *)(puVar6 + 2);
    puVar6[2] = (undefined4)local_18;
    puVar6[3] = local_18._4_4_;
    local_18 = uVar3;
    FUN_00434820((char *)&local_20);
    goto LAB_004177a0;
  }
  pvVar15 = local_2c;
  if ((local_50 != (HGLOBAL)0x0) && (local_48 != '\0')) {
    GlobalFree(local_50);
    pvVar15 = local_2c;
  }
LAB_004177c5:
  if (bVar16) {
    CloseClipboard();
  }
  ExceptionList = local_74;
  return pvVar15;
}


