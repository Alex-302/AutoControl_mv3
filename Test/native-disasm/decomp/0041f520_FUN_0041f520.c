// FUN_0041f520 @ 0041f520 size=1257 callers=1

void __cdecl FUN_0041f520(UINT param_1,ULONG_PTR param_2)

{
  POINT Point;
  int *piVar1;
  ULONG_PTR UVar2;
  char cVar3;
  ushort uVar4;
  UINT UVar5;
  undefined *puVar6;
  uint uVar7;
  HMENU pHVar8;
  int iVar9;
  undefined1 auStack_108 [4];
  undefined4 uStack_104;
  HWND pHVar10;
  LPTPMPARAMS pTVar11;
  UINT local_e0;
  HBRUSH pHStack_dc;
  int *piStack_d8;
  ULONG_PTR UStack_d4;
  char local_d0 [16];
  undefined1 local_c0 [16];
  char local_b0 [4];
  undefined1 local_ac [12];
  UINT UStack_a0;
  HBRUSH pHStack_9c;
  int *piStack_98;
  ULONG_PTR local_94;
  char local_90 [8];
  undefined8 local_88;
  undefined1 local_80 [8];
  undefined8 local_78;
  char local_70 [8];
  undefined8 local_68;
  undefined1 local_60 [8];
  undefined8 local_58;
  undefined1 *local_50;
  HWND local_4c;
  char local_48 [8];
  int *local_40;
  ULONG_PTR local_3c;
  tagRECT local_38;
  char local_21;
  undefined1 *puStack_20;
  void *local_1c;
  undefined1 *puStack_18;
  undefined4 local_14;
  
  puStack_20 = &stack0xfffffffc;
  puStack_18 = &LAB_0047bae8;
  local_1c = ExceptionList;
  local_14 = 0;
  local_48[0] = '\0';
  ExceptionList = &local_1c;
  FUN_004381d0(&local_40,'\0');
  local_14 = 1;
  local_e0 = 0;
  pHStack_dc = (HBRUSH)0x0;
  piStack_d8 = (int *)0x0;
  UStack_d4 = 0;
  if (param_2 == 0xffff8000) {
    cVar3 = local_48[0];
    if (DAT_004a29c0 != 0) {
      puVar6 = FUN_00419890(DAT_004a29c0);
      uVar4 = FUN_0041d340(*(HMENU *)(puVar6 + 0x1c),DAT_004a29c0);
      local_38.left = 0;
      local_38.top = 0;
      local_38.right = 0;
      local_38.bottom = 0;
      GetMenuItemRect((HWND)0x0,*(HMENU *)(puVar6 + 0x1c),(uint)uVar4,&local_38);
      local_90[0] = '\0';
      local_e0 = local_38.left;
      pHStack_dc = (HBRUSH)local_38.top;
      piStack_d8 = (int *)local_38.right;
      UStack_d4 = local_38.bottom;
      param_2 = local_38.bottom;
      param_1 = local_38.left;
      local_88 = 0;
      FUN_00451110(local_90,(uint *)"itemId");
      local_80[0] = 0;
      local_78 = 0;
      FUN_00451040(local_80,DAT_004a29c0);
      local_14._0_1_ = 9;
      FUN_00434b50(local_d0,local_90,local_70,'\x01','\x02');
      local_14._0_1_ = 0xb;
      _eh_vector_destructor_iterator_(local_90,0x10,2,FUN_00434820);
      local_70[0] = '\0';
      local_68 = 0;
      FUN_00451110(local_70,(uint *)"parentId");
      local_ac._0_4_ = 0x1c;
      local_ac._4_4_ = 8;
      local_ac._8_4_ = 0;
      UStack_a0 = 0;
      pHStack_9c = (HBRUSH)0x0;
      piStack_98 = (int *)0x0;
      local_94 = 0;
      GetMenuInfo(*(HMENU *)(puVar6 + 0x1c),(LPMENUINFO)local_ac);
      local_60[0] = 0;
      local_58 = 0;
      FUN_00451040(local_60,local_94);
      local_14._0_1_ = 0xc;
      FUN_00434b50(local_c0,local_70,(char *)&local_50,'\x01','\x02');
      local_14._0_1_ = 0xe;
      _eh_vector_destructor_iterator_(local_70,0x10,2,FUN_00434820);
      local_14._0_1_ = 0xf;
      FUN_00434b50(&local_38,local_d0,local_b0,'\x01','\x02');
      UVar2 = local_3c;
      piVar1 = local_40;
      cVar3 = local_48[0];
      local_21 = (char)local_38.left;
      local_48[0] = (char)local_38.left;
      local_38.left = CONCAT31(local_38.left._1_3_,cVar3);
      local_40 = (int *)local_38.right;
      local_38.right = (LONG)piVar1;
      local_3c = local_38.bottom;
      local_38.bottom = UVar2;
      FUN_00434820((char *)&local_38);
      local_14 = CONCAT31(local_14._1_3_,1);
      _eh_vector_destructor_iterator_(local_d0,0x10,2,FUN_00434820);
      cVar3 = local_21;
    }
  }
  else {
    UVar5 = FUN_0041d3c0('\x01',param_1,param_2);
    cVar3 = local_48[0];
    if ((UVar5 != 0) && ((-1 < (int)UVar5 || (UVar5 == 0xfffffffe)))) {
      local_70[0] = '\0';
      local_68 = 0;
      FUN_00451110(local_70,(uint *)"itemId");
      local_60[0] = 0;
      local_58 = 0;
      FUN_00451040(local_60,UVar5);
      local_14._0_1_ = 2;
      FUN_00434b50(local_d0,local_70,(char *)&local_50,'\x01','\x02');
      local_14._0_1_ = 4;
      _eh_vector_destructor_iterator_(local_70,0x10,2,FUN_00434820);
      local_90[0] = '\0';
      local_88 = 0;
      FUN_00451110(local_90,(uint *)"parentId");
      Point.y = param_2;
      Point.x = param_1;
      local_4c = WindowFromPoint(Point);
      FUN_00435ec0(&local_50,(byte *)&local_4c);
      if (local_50 == DAT_004a24b4) {
        pHVar8 = (HMENU)0x0;
      }
      else {
        pHVar8 = *(HMENU *)(local_50 + 0xc);
      }
      local_ac._0_4_ = 0x1c;
      local_ac._4_4_ = 8;
      local_ac._8_4_ = 0;
      UStack_a0 = 0;
      pHStack_9c = (HBRUSH)0x0;
      piStack_98 = (int *)0x0;
      local_94 = 0;
      GetMenuInfo(pHVar8,(LPMENUINFO)local_ac);
      local_80[0] = 0;
      local_78 = 0;
      FUN_00451040(local_80,local_94);
      local_14._0_1_ = 5;
      FUN_00434b50(local_c0,local_90,local_70,'\x01','\x02');
      local_14._0_1_ = 7;
      _eh_vector_destructor_iterator_(local_90,0x10,2,FUN_00434820);
      local_14._0_1_ = 8;
      FUN_00434b50(&local_38,local_d0,local_b0,'\x01','\x02');
      UVar2 = local_3c;
      piVar1 = local_40;
      cVar3 = local_48[0];
      local_21 = (char)local_38.left;
      local_48[0] = (char)local_38.left;
      local_38.left = CONCAT31(local_38.left._1_3_,cVar3);
      local_40 = (int *)local_38.right;
      local_38.right = (LONG)piVar1;
      local_3c = local_38.bottom;
      local_38.bottom = UVar2;
      FUN_00434820((char *)&local_38);
      local_14 = CONCAT31(local_14._1_3_,1);
      _eh_vector_destructor_iterator_(local_d0,0x10,2,FUN_00434820);
      cVar3 = local_21;
    }
  }
  if (cVar3 != '\x01') goto LAB_0041f9ef;
  local_50 = &stack0xffffff08;
  local_14._0_1_ = 0x10;
  FUN_004381d0(&stack0xffffff10,'\0');
  local_14._0_1_ = 0x11;
  FUN_00434940(auStack_108,local_48);
  local_14._0_1_ = 1;
  FUN_00408a00(&local_38,0x30f);
  local_14 = CONCAT31(local_14._1_3_,0x12);
  uVar7 = local_38.left & 0xff;
  if (uVar7 != 0) {
    if (uVar7 == 1) {
      iVar9 = *(int *)(local_38.right + 4);
LAB_0041f981:
      if (iVar9 == 0) goto LAB_0041f9e7;
    }
    else if (uVar7 == 2) {
      iVar9 = *(int *)(local_38.right + 4) - *(int *)local_38.right >> 4;
      goto LAB_0041f981;
    }
    FUN_0041e810();
    pTVar11 = (LPTPMPARAMS)(local_ac + 8);
    DAT_004a2427 = 1;
    local_ac._8_4_ = 0x14;
    UStack_a0 = local_e0;
    pHStack_9c = pHStack_dc;
    piStack_98 = piStack_d8;
    local_94 = UStack_d4;
    pHVar10 = *(HWND *)(&DAT_004a2470 + *(int *)(*(int *)ThreadLocalStoragePointer + 4) * 4);
    UVar5 = 0x141;
    uStack_104 = 0x41f9d6;
    pHVar8 = FUN_0041b7b0(&local_38);
    uStack_104 = 0x41f9e0;
    TrackPopupMenuEx(pHVar8,UVar5,param_1,param_2,pHVar10,pTVar11);
    DAT_004a2427 = 0;
  }
LAB_0041f9e7:
  FUN_00434820((char *)&local_38);
LAB_0041f9ef:
  FUN_00434820(local_48);
  ExceptionList = local_1c;
  return;
}


