// FUN_00430c30 @ 00430c30 size=552 callers=2

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

LRESULT __fastcall FUN_00430c30(int param_1,WPARAM param_2,uint *param_3,byte param_4)

{
  int iVar1;
  void **ppvVar2;
  char cVar3;
  undefined4 uVar4;
  HWND pHVar5;
  BOOL BVar6;
  uint uVar7;
  HWND pHVar8;
  LRESULT LVar9;
  uint *puVar10;
  undefined **local_48;
  undefined2 local_44;
  undefined ***local_24;
  int local_20;
  tagPOINT local_1c;
  WPARAM local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047b1a8;
  local_10 = ExceptionList;
  ppvVar2 = &local_10;
  local_20 = param_1;
  local_14 = param_2;
  if (param_1 == 0) {
    if (param_2 == 0x200) {
      if (DAT_004a264b == 'S') {
        ppvVar2 = &local_10;
        if ((DAT_004a2447 != '\0') && (ppvVar2 = &local_10, param_3[5] != 0xd6c18935)) {
          return -1;
        }
      }
      else {
        ExceptionList = &local_10;
        FUN_00419190(&DAT_004a2614,(int *)param_3,'\0');
        ppvVar2 = ExceptionList;
      }
    }
    else {
      ExceptionList = &local_10;
      uVar4 = FUN_00412e10(param_2,param_3,param_4);
      iVar1 = DAT_004a26b4;
      local_1c.x._0_2_ = (short)uVar4;
      local_1c.x._2_1_ = (char)((uint)uVar4 >> 0x10);
      local_1c.x._3_1_ = (char)((uint)uVar4 >> 0x18);
      *(int *)(&DAT_004a23b0 + (char)param_4 * 4) = DAT_004a26b4;
      *(undefined4 *)(&DAT_004a2468 + (char)param_4 * 4) = 0;
      if (local_1c.x._2_1_ < '\0') {
        param_2 = local_14;
        ppvVar2 = ExceptionList;
        if (local_1c.x._2_1_ == -2) {
          ExceptionList = local_10;
          return -1;
        }
      }
      else {
        puVar10 = DAT_004a2534;
        if (local_1c.x._3_1_ == '\0') {
          DAT_004a2430 = 0;
          if (((ushort)((short)local_1c.x - 1U) < 6) && ((short)local_1c.x != 3)) {
            if (200 < (uint)(iVar1 - _DAT_004a32e8)) {
              GetCursorPos(&local_1c);
              DAT_004a2a48 = CONCAT13(local_1c.x._3_1_,CONCAT12(local_1c.x._2_1_,(short)local_1c.x))
              ;
              DAT_004a2a4c = CONCAT22(local_1c.y._2_2_,(undefined2)local_1c.y);
              _DAT_004a32e8 = DAT_004a26b4;
            }
            local_1c.x._0_2_ = (short)DAT_004a2a48;
            local_1c.x._2_1_ = (char)((uint)DAT_004a2a48 >> 0x10);
            local_1c.x._3_1_ = (char)((uint)DAT_004a2a48 >> 0x18);
            local_1c.y._0_2_ = (undefined2)DAT_004a2a4c;
            local_1c.y._2_2_ = (undefined2)((uint)DAT_004a2a4c >> 0x10);
            pHVar5 = FUN_00404e30(&local_1c,'\0');
            local_1c.y._0_2_ = SUB42(pHVar5,0);
            local_1c.y._2_2_ = (undefined2)((uint)pHVar5 >> 0x10);
            pHVar5 = GetAncestor(pHVar5,3);
            BVar6 = IsWindowEnabled(pHVar5);
            if ((BVar6 != 0) && (cVar3 = FUN_00409750(pHVar5), cVar3 != '\0')) {
              uVar7 = FUN_0040f470((int)pHVar5);
              DAT_004a26c5 = (undefined1)uVar7;
              pHVar8 = (HWND)FUN_00404e80();
              if (pHVar5 != pHVar8) {
                FUN_0040ee50((HWND)CONCAT22(local_1c.y._2_2_,(undefined2)local_1c.y));
              }
            }
          }
          uVar7 = FUN_00413390(uVar4,'\0');
          puVar10 = DAT_004a2534;
          *DAT_004a2534 = *DAT_004a2534 | uVar7;
        }
        param_2 = local_14;
        ppvVar2 = ExceptionList;
        if (DAT_0049d9f4 != '\0') {
          uVar7 = *puVar10;
          *puVar10 = 0;
          if (uVar7 == 2) {
            local_44 = DAT_004a26b0;
            local_24 = &local_48;
            local_48 = &PTR_LAB_0048e8f0;
            local_8 = 0;
            FUN_0040fab0((int *)local_24);
            FUN_0040fe40((int *)&local_48);
          }
          else {
            ppvVar2 = ExceptionList;
            if (uVar7 != 3) goto LAB_00430db7;
          }
          ExceptionList = local_10;
          return -1;
        }
      }
    }
  }
LAB_00430db7:
  ExceptionList = ppvVar2;
  LVar9 = CallNextHookEx((HHOOK)0x0,local_20,param_2,(LPARAM)param_3);
  ExceptionList = local_10;
  return LVar9;
}


