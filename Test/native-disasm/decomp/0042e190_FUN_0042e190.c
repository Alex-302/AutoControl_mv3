// FUN_0042e190 @ 0042e190 size=834 callers=2

/* WARNING: Removing unreachable block (ram,0x0042e37c) */

undefined2 * __fastcall FUN_0042e190(undefined2 *param_1,undefined4 *param_2)

{
  LPBYTE pBVar1;
  LPCSTR ***lpSubKey;
  LSTATUS LVar2;
  LPWSTR ***ppppWVar3;
  LPCWSTR lpSrc;
  int iVar4;
  void *_Memory;
  undefined2 uVar5;
  void *in_stack_ffffff4c;
  uint uVar6;
  void *local_88 [5];
  uint local_74;
  LPCSTR **local_70 [5];
  uint local_5c;
  void *local_58 [4];
  undefined4 local_48;
  uint local_44;
  LPWSTR **local_40 [4];
  uint local_30;
  uint local_2c;
  undefined4 local_28;
  undefined2 *local_24;
  DWORD local_20;
  HKEY local_1c;
  undefined4 *local_18;
  DWORD local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047d1e8;
  local_10 = ExceptionList;
  local_28 = 0;
  local_2c = 7;
  local_30 = 0;
  local_40[0] = (LPWSTR **)((uint)local_40[0] & 0xffff0000);
  ExceptionList = &local_10;
  local_24 = param_1;
  local_18 = param_2;
  FUN_0043d830(local_40,200);
  iVar4 = 100;
  ppppWVar3 = local_40;
  if (7 < local_2c) {
    ppppWVar3 = (LPWSTR ***)local_40[0];
  }
  for (; iVar4 != 0; iVar4 = iVar4 + -1) {
    *ppppWVar3 = (LPWSTR **)0x0;
    ppppWVar3 = ppppWVar3 + 1;
  }
  local_30 = 200;
  ppppWVar3 = local_40;
  if (7 < local_2c) {
    ppppWVar3 = (LPWSTR ***)local_40[0];
  }
  *(undefined2 *)(ppppWVar3 + 100) = 0;
  local_8 = 0;
  iVar4 = 0;
  local_14 = 0;
  do {
    local_44 = 0xf;
    iVar4 = iVar4 + 1;
    local_48 = 0;
    local_58[0] = (void *)((uint)local_58[0] & 0xffffff00);
    FUN_0043ace0(local_58,(uint *)"AppEvents\\Schemes\\Apps\\%s\\%s\\.Current",0x25);
    local_8._0_1_ = 1;
    FUN_00435400(local_18);
    FUN_00442530(local_70,(char *)local_58);
    local_8 = CONCAT31(local_8._1_3_,3);
    if (0xf < local_44) {
      _Memory = local_58[0];
      if ((0xfff < local_44 + 1) &&
         ((((((uint)local_58[0] & 0x1f) != 0 ||
            (_Memory = *(void **)((int)local_58[0] + -4), local_58[0] <= _Memory)) ||
           ((uint)((int)local_58[0] - (int)_Memory) < 4)) ||
          (0x23 < (uint)((int)local_58[0] - (int)_Memory))))) goto LAB_0042e479;
      FID_conflict__free(_Memory);
    }
    local_44 = 0xf;
    lpSubKey = local_70;
    if (0xf < local_5c) {
      lpSubKey = (LPCSTR ***)local_70[0];
    }
    local_48 = 0;
    local_58[0] = (void *)((uint)local_58[0] & 0xffffff00);
    LVar2 = RegOpenKeyExA((HKEY)&DAT_80000001,(LPCSTR)lpSubKey,0,1,&local_1c);
    if (LVar2 == 0) {
      local_14 = local_30 * 2;
      ppppWVar3 = local_40;
      if (7 < local_2c) {
        ppppWVar3 = (LPWSTR ***)local_40[0];
      }
      LVar2 = RegQueryValueExW(local_1c,(LPCWSTR)0x0,(LPDWORD)0x0,&local_20,(LPBYTE)ppppWVar3,
                               &local_14);
      if ((LVar2 == 0) && ((local_20 == 1 || (local_20 == 2)))) {
        local_14 = local_14 >> 1;
        if (local_20 == 2) {
          ppppWVar3 = local_40;
          if (7 < local_2c) {
            ppppWVar3 = (LPWSTR ***)local_40[0];
          }
                    /* WARNING: Ignoring partial resolution of indirect */
          uVar5 = 0;
          uVar6 = local_30;
          FUN_0043a750(&stack0xffffff4c,local_40,0,0xffffffff);
          lpSrc = FUN_004425c0(local_88,in_stack_ffffff4c);
          if (7 < *(uint *)(lpSrc + 10)) {
            lpSrc = *(LPCWSTR *)lpSrc;
          }
          local_14 = ExpandEnvironmentStringsW(lpSrc,(LPWSTR)ppppWVar3,uVar6);
          if (7 < local_74) {
            FUN_00402430(local_88[0],local_74 + 1,2);
          }
        }
        local_8 = local_8 & 0xffffff00;
        if (0xf < local_5c) {
          FUN_00402430(local_70[0],local_5c + 1,1);
        }
        break;
      }
      local_14 = 0;
    }
    local_8 = local_8 & 0xffffff00;
    if (0xf < local_5c) {
      FUN_00402430(local_70[0],local_5c + 1,1);
    }
  } while (iVar4 < 2);
  if (local_30 < local_14) {
    FUN_0043a870(local_40,local_14 - local_30,0);
  }
  else {
    local_30 = local_14;
    ppppWVar3 = local_40;
    if (7 < local_2c) {
      ppppWVar3 = (LPWSTR ***)local_40[0];
    }
    pBVar1 = (LPBYTE)((int)ppppWVar3 + local_14 * 2);
    pBVar1[0] = '\0';
    pBVar1[1] = '\0';
  }
  iVar4 = FUN_00434e50((int *)local_40);
  uVar6 = iVar4 + 1;
  if (local_30 < uVar6) {
                    /* WARNING: Subroutine does not return */
    FUN_00458ee4("invalid string position");
  }
  ppppWVar3 = local_40;
  if (7 < local_2c) {
    ppppWVar3 = (LPWSTR ***)local_40[0];
  }
  pBVar1 = (LPBYTE)((int)ppppWVar3 + uVar6 * 2);
  local_30 = uVar6;
  pBVar1[0] = '\0';
  pBVar1[1] = '\0';
  *(undefined4 *)(param_1 + 10) = 7;
  *(undefined4 *)(param_1 + 8) = 0;
  *param_1 = 0;
  FUN_0043a750(param_1,local_40,0,0xffffffff);
  if (7 < local_2c) {
    if (0x7fffffff < local_2c + 1) {
LAB_0042e479:
                    /* WARNING: Subroutine does not return */
      FUN_00465fb2();
    }
    ppppWVar3 = (LPWSTR ***)local_40[0];
    if (0xfff < (local_2c + 1) * 2) {
      if (((uint)local_40[0] & 0x1f) != 0) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      ppppWVar3 = (LPWSTR ***)local_40[0][-1];
      if (local_40[0] <= ppppWVar3) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if ((uint)((int)local_40[0] - (int)ppppWVar3) < 4) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if (0x23 < (uint)((int)local_40[0] - (int)ppppWVar3)) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
    }
    FID_conflict__free(ppppWVar3);
  }
  ExceptionList = local_10;
  return param_1;
}


