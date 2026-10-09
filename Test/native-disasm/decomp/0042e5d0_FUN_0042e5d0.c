// FUN_0042e5d0 @ 0042e5d0 size=1303 callers=1

void * __cdecl FUN_0042e5d0(void *param_1)

{
  LPWSTR pWVar1;
  LSTATUS LVar2;
  LPSTR ***ppppCVar3;
  undefined2 *puVar4;
  LPWSTR ***ppppWVar5;
  LPSTR pCVar6;
  undefined1 *this;
  int iVar7;
  LPCWSTR pszDirectory;
  DWORD dwIndex;
  char *pcVar8;
  code *pcVar9;
  char cVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  uint uVar13;
  void *local_88 [5];
  uint local_74;
  undefined4 local_70;
  undefined4 local_60;
  uint local_5c;
  LPWSTR **local_58 [4];
  uint local_48;
  uint local_44;
  LPSTR **local_40 [4];
  uint local_30;
  uint local_2c;
  undefined1 *local_28;
  int local_24;
  undefined4 local_20;
  HKEY local_1c;
  HKEY local_18;
  DWORD local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047d27c;
  local_10 = ExceptionList;
  local_8 = 0;
  local_20 = 0;
  ExceptionList = &local_10;
  FUN_00434a40(param_1,(char *)0x0,(char *)0x0);
  local_8 = 0;
  local_20 = 1;
  local_5c = 7;
  local_60 = 0;
  local_70 = (LPWSTR)((uint)local_70._2_2_ << 0x10);
  FUN_0043d830(&local_70,100);
  iVar7 = 0x32;
  pWVar1 = (LPWSTR)&local_70;
  if (7 < local_5c) {
    pWVar1 = local_70;
  }
  for (; iVar7 != 0; iVar7 = iVar7 + -1) {
    pWVar1[0] = L'\0';
    pWVar1[1] = L'\0';
    pWVar1 = pWVar1 + 2;
  }
  local_60 = 100;
  pWVar1 = (LPWSTR)&local_70;
  if (7 < local_5c) {
    pWVar1 = local_70;
  }
  pWVar1[100] = L'\0';
  local_8 = 1;
  pWVar1 = (LPWSTR)&local_70;
  if (7 < local_5c) {
    pWVar1 = local_70;
  }
  GetSystemDirectoryW(pWVar1,100);
  local_24 = 0;
  pcVar8 = ".Default";
  pcVar9 = RegOpenKeyExA_exref;
  do {
    local_24 = local_24 + 1;
    local_44 = 0xf;
    local_48 = 0;
    local_58[0] = (LPWSTR **)((uint)local_58[0] & 0xffffff00);
    FUN_0043ace0(local_58,(uint *)"AppEvents\\Schemes\\Apps\\",0x17);
    local_8 = CONCAT31(local_8._1_3_,2);
    FUN_004412a0((undefined1 *)local_40,(uint *)local_58,(uint *)pcVar8);
    iVar7 = (*pcVar9)(0x80000001);
    if (0xf < local_2c) {
      ppppCVar3 = (LPSTR ***)local_40[0];
      if ((0xfff < local_2c + 1) &&
         ((((((uint)local_40[0] & 0x1f) != 0 ||
            (ppppCVar3 = (LPSTR ***)local_40[0][-1], local_40[0] <= ppppCVar3)) ||
           ((uint)((int)local_40[0] - (int)ppppCVar3) < 4)) ||
          (0x23 < (uint)((int)local_40[0] - (int)ppppCVar3))))) goto LAB_0042eae2;
      FID_conflict__free(ppppCVar3);
    }
    local_8 = CONCAT31(local_8._1_3_,1);
    local_2c = 0xf;
    local_30 = 0;
    local_40[0] = (LPSTR **)((uint)local_40[0] & 0xffffff00);
    if (0xf < local_44) {
      ppppWVar5 = (LPWSTR ***)local_58[0];
      if ((0xfff < local_44 + 1) &&
         (((((uint)local_58[0] & 0x1f) != 0 ||
           (ppppWVar5 = (LPWSTR ***)local_58[0][-1], local_58[0] <= ppppWVar5)) ||
          (((uint)((int)local_58[0] - (int)ppppWVar5) < 4 ||
           (0x23 < (uint)((int)local_58[0] - (int)ppppWVar5))))))) goto LAB_0042eae2;
      FID_conflict__free(ppppWVar5);
    }
    if (iVar7 == 0) {
      dwIndex = 0;
      while( true ) {
        local_2c = 0xf;
        local_30 = 0;
        local_40[0] = (LPSTR **)((uint)local_40[0] & 0xffffff00);
        FUN_0043f5f0(local_40,0x32);
        ppppCVar3 = local_40;
        if (0xf < local_2c) {
          ppppCVar3 = (LPSTR ***)local_40[0];
        }
        _memset(ppppCVar3,0,0x32);
        local_30 = 0x32;
        ppppCVar3 = local_40;
        if (0xf < local_2c) {
          ppppCVar3 = (LPSTR ***)local_40[0];
        }
        *(CHAR *)((int)ppppCVar3 + 0x32) = '\0';
        local_8._0_1_ = 3;
        local_14 = 0x32;
        ppppCVar3 = local_40;
        if (0xf < local_2c) {
          ppppCVar3 = (LPSTR ***)local_40[0];
        }
        LVar2 = RegEnumKeyExA(local_1c,dwIndex,(LPSTR)ppppCVar3,&local_14,(LPDWORD)0x0,(LPSTR)0x0,
                              (LPDWORD)0x0,(PFILETIME)0x0);
        if (LVar2 == 0x103) break;
        if (LVar2 == 0) {
          if (local_30 < local_14) {
            FUN_0043aef0(local_40,local_14 - local_30,'\0');
          }
          else {
            local_30 = local_14;
            ppppCVar3 = local_40;
            if (0xf < local_2c) {
              ppppCVar3 = (LPSTR ***)local_40[0];
            }
            *(CHAR *)((int)ppppCVar3 + local_14) = '\0';
          }
          puVar4 = FUN_0042e190((undefined2 *)local_88,local_40);
          iVar7 = *(int *)(puVar4 + 8);
          if (7 < local_74) {
            FUN_00402430(local_88[0],local_74 + 1,2);
          }
          if (iVar7 == 0) {
            local_8 = CONCAT31(local_8._1_3_,1);
            if (local_2c < 0x10) goto LAB_0042ea5d;
            FUN_00402430(local_40[0],local_2c + 1,1);
            dwIndex = dwIndex + 1;
          }
          else {
            FUN_00442660((uint *)local_88,(uint *)"AppEvents\\EventLabels\\",local_40);
            iVar7 = (*pcVar9)(0x80000001);
            if (0xf < local_74) {
              FUN_00402430(local_88[0],local_74 + 1,1);
            }
            if (iVar7 == 0) {
              local_44 = 7;
              local_48 = 0;
              local_58[0] = (LPWSTR **)((uint)local_58[0] & 0xffff0000);
              FUN_0043d830(local_58,100);
              iVar7 = 0x32;
              ppppWVar5 = local_58;
              if (7 < local_44) {
                ppppWVar5 = (LPWSTR ***)local_58[0];
              }
              for (; iVar7 != 0; iVar7 = iVar7 + -1) {
                *ppppWVar5 = (LPWSTR **)0x0;
                ppppWVar5 = ppppWVar5 + 1;
              }
              local_48 = 100;
              ppppWVar5 = local_58;
              if (7 < local_44) {
                ppppWVar5 = (LPWSTR ***)local_58[0];
              }
              *(WCHAR *)(ppppWVar5 + 0x32) = L'\0';
              local_8._0_1_ = 4;
              pszDirectory = (LPCWSTR)&local_70;
              if (7 < local_5c) {
                pszDirectory = local_70;
              }
              cVar10 = -0x38;
              ppppWVar5 = local_58;
              if (7 < local_44) {
                ppppWVar5 = (LPWSTR ***)local_58[0];
              }
              LVar2 = RegLoadMUIStringW(local_18,L"DispFileName",(LPWSTR)ppppWVar5,200,(LPDWORD)0x0,
                                        1,pszDirectory);
              RegCloseKey(local_18);
              if (LVar2 == 0) {
                ppppWVar5 = local_58;
                if (7 < local_44) {
                  ppppWVar5 = (LPWSTR ***)local_58[0];
                }
                uVar12 = 0xffffffff;
                uVar11 = 0x42ea0b;
                uVar13 = local_48;
                pCVar6 = FUN_004044f0((LPSTR)local_88,(LPCWSTR)ppppWVar5,-1,local_48);
                local_28 = &stack0xffffff5c;
                local_8._0_1_ = 5;
                FUN_00440c80(&stack0xffffff5c,(undefined4 *)pCVar6);
                local_8._0_1_ = 6;
                this = FUN_00434440(param_1,(byte *)local_40);
                local_8._0_1_ = 5;
                FUN_004348c0(this,cVar10,uVar11,uVar12,uVar13);
                FUN_004061c0(local_88);
              }
              FUN_00435170(local_58);
              local_8 = CONCAT31(local_8._1_3_,1);
              FUN_004061c0(local_40);
              pcVar9 = RegOpenKeyExA_exref;
              goto LAB_0042ea5d;
            }
            local_8 = CONCAT31(local_8._1_3_,1);
            if (local_2c < 0x10) goto LAB_0042ea5d;
            FUN_00402430(local_40[0],local_2c + 1,1);
            dwIndex = dwIndex + 1;
          }
        }
        else {
          local_8 = CONCAT31(local_8._1_3_,1);
          if (local_2c < 0x10) {
LAB_0042ea5d:
            dwIndex = dwIndex + 1;
          }
          else {
            ppppCVar3 = (LPSTR ***)local_40[0];
            if ((0xfff < local_2c + 1) &&
               ((((((uint)local_40[0] & 0x1f) != 0 ||
                  (ppppCVar3 = (LPSTR ***)local_40[0][-1], local_40[0] <= ppppCVar3)) ||
                 ((uint)((int)local_40[0] - (int)ppppCVar3) < 4)) ||
                (0x23 < (uint)((int)local_40[0] - (int)ppppCVar3))))) goto LAB_0042eae2;
            FID_conflict__free(ppppCVar3);
            dwIndex = dwIndex + 1;
          }
        }
      }
      local_8 = CONCAT31(local_8._1_3_,1);
      if (0xf < local_2c) {
        ppppCVar3 = (LPSTR ***)local_40[0];
        if ((0xfff < local_2c + 1) &&
           (((((uint)local_40[0] & 0x1f) != 0 ||
             (ppppCVar3 = (LPSTR ***)local_40[0][-1], local_40[0] <= ppppCVar3)) ||
            (((uint)((int)local_40[0] - (int)ppppCVar3) < 4 ||
             (0x23 < (uint)((int)local_40[0] - (int)ppppCVar3))))))) {
LAB_0042eae2:
                    /* WARNING: Subroutine does not return */
          FUN_00465fb2();
        }
        FID_conflict__free(ppppCVar3);
      }
      RegCloseKey(local_1c);
    }
    pcVar8 = "Explorer";
    if (1 < local_24) {
      if (7 < local_5c) {
        FUN_00402430(local_70,local_5c + 1,2);
      }
      ExceptionList = local_10;
      return param_1;
    }
  } while( true );
}


