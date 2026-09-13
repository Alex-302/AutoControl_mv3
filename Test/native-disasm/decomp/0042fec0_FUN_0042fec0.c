// FUN_0042fec0 @ 0042fec0 size=612 callers=1

undefined1 * __cdecl FUN_0042fec0(undefined1 *param_1,void *param_2)

{
  uint nSize;
  LPCWSTR lpName;
  DWORD DVar1;
  LPWSTR ***ppppWVar2;
  LPSTR pCVar3;
  undefined1 *this;
  int iVar4;
  void *pvVar5;
  void *local_74 [5];
  uint local_60;
  void *local_5c [4];
  undefined4 local_4c;
  uint local_48;
  LPWSTR **local_44 [4];
  uint local_34;
  uint local_30;
  undefined1 *local_2c;
  undefined1 *local_28;
  undefined1 *local_20;
  undefined1 *local_1c;
  undefined4 local_18;
  undefined1 local_11;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047d591;
  local_10 = ExceptionList;
  local_18 = 0;
  local_30 = 7;
  local_34 = 0;
  local_44[0] = (LPWSTR **)((uint)local_44[0] & 0xffff0000);
  ExceptionList = &local_10;
  FUN_0043d830(local_44,100);
  iVar4 = 0x32;
  ppppWVar2 = local_44;
  if (7 < local_30) {
    ppppWVar2 = (LPWSTR ***)local_44[0];
  }
  for (; iVar4 != 0; iVar4 = iVar4 + -1) {
    *ppppWVar2 = (LPWSTR **)0x0;
    ppppWVar2 = ppppWVar2 + 1;
  }
  local_34 = 100;
  ppppWVar2 = local_44;
  if (7 < local_30) {
    ppppWVar2 = (LPWSTR ***)local_44[0];
  }
  *(WCHAR *)(ppppWVar2 + 0x32) = L'\0';
  local_8 = 0;
  do {
    nSize = local_34;
    FUN_00440d90(param_2,local_74);
    local_8 = CONCAT31(local_8._1_3_,1);
    lpName = FUN_00404640((LPWSTR)local_5c,(LPCSTR)local_74);
    ppppWVar2 = local_44;
    if (7 < local_30) {
      ppppWVar2 = (LPWSTR ***)local_44[0];
    }
    if (7 < *(uint *)(lpName + 10)) {
      lpName = *(LPCWSTR *)lpName;
    }
    DVar1 = GetEnvironmentVariableW(lpName,(LPWSTR)ppppWVar2,nSize);
    if (7 < local_48) {
      if ((0x7fffffff < local_48 + 1) ||
         ((pvVar5 = local_5c[0], 0xfff < (local_48 + 1) * 2 &&
          ((((((uint)local_5c[0] & 0x1f) != 0 ||
             (pvVar5 = *(void **)((int)local_5c[0] + -4), local_5c[0] <= pvVar5)) ||
            ((uint)((int)local_5c[0] - (int)pvVar5) < 4)) ||
           (0x23 < (uint)((int)local_5c[0] - (int)pvVar5))))))) goto LAB_0043011f;
      FID_conflict__free(pvVar5);
    }
    local_48 = 7;
    local_5c[0] = (void *)((uint)local_5c[0] & 0xffff0000);
    local_8 = local_8 & 0xffffff00;
    local_4c = 0;
    if (0xf < local_60) {
      pvVar5 = local_74[0];
      if ((0xfff < local_60 + 1) &&
         (((((uint)local_74[0] & 0x1f) != 0 ||
           (pvVar5 = *(void **)((int)local_74[0] + -4), local_74[0] <= pvVar5)) ||
          (((uint)((int)local_74[0] - (int)pvVar5) < 4 ||
           (0x23 < (uint)((int)local_74[0] - (int)pvVar5))))))) {
LAB_0043011f:
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      FID_conflict__free(pvVar5);
    }
    if (local_34 < DVar1) {
      FUN_0043a870(local_44,DVar1 - local_34,0);
    }
    else {
      ppppWVar2 = local_44;
      if (7 < local_30) {
        ppppWVar2 = (LPWSTR ***)local_44[0];
      }
      local_34 = DVar1;
      *(WCHAR *)((int)ppppWVar2 + DVar1 * 2) = L'\0';
    }
    if (DVar1 <= nSize) {
      pCVar3 = FUN_00404580((LPSTR)local_5c,(LPCWSTR)local_44,0x7fffffff);
      local_8._0_1_ = 2;
      *(undefined8 *)(param_1 + 8) = 0;
      *param_1 = 3;
      this = operator_new(0x18);
      local_2c = &local_11;
      local_8 = CONCAT31(local_8._1_3_,4);
      local_28 = this;
      local_20 = this;
      local_1c = this;
      if (this != (undefined1 *)0x0) {
        *(undefined4 *)(this + 0x14) = 0xf;
        *(undefined4 *)(this + 0x10) = 0;
        *this = 0;
        FUN_0043ade0(this,(undefined4 *)pCVar3,0,0xffffffff);
      }
      *(undefined1 **)(param_1 + 0xc) = local_28;
      *(undefined1 **)(param_1 + 8) = this;
      if (0xf < local_48) {
        FUN_00402430(local_5c[0],local_48 + 1,1);
      }
      local_48 = 0xf;
      local_4c = 0;
      local_5c[0] = (void *)((uint)local_5c[0] & 0xffffff00);
      if (7 < local_30) {
        FUN_00402430(local_44[0],local_30 + 1,2);
      }
      ExceptionList = local_10;
      return param_1;
    }
  } while( true );
}


